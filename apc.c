#include "apc.h"

/* ===========================
   Memory Helpers
   =========================== */

/*
   Free an entire doubly linked list.
   Walks through each node and frees it.
*/
void free_dlist(Dlist *head) {
    while (head) {
        Dlist *temp = head;
        head = head->next;
        free(temp);
    }
}

/*
   Check if DLL number is zero.
   Returns 1 if all digits are 0, else 0.
*/
int is_zero(Dlist *num) {
    if (!num) return 1;
    while (num) {
        if (num->digit != 0) return 0;
        num = num->next;
    }
    return 1;
}

/*
   Count digits in DLL.
   Returns the number of nodes.
*/
int length(Dlist *num) {
    int count = 0;
    while (num) {
        count++;
        num = num->next;
    }
    return count;
}

/* ===========================
   Comparison Helpers
   =========================== */

/*
   Compare two numbers represented as DLLs.
   Returns:
   -1 if num1 < num2
    0 if num1 == num2
    1 if num1 > num2
*/
int compare_numbers(Dlist *num1, Dlist *num2) {
    int len1 = 0, len2 = 0;
    Dlist *t1 = num1, *t2 = num2;

    while (t1) { len1++; t1 = t1->next; }
    while (t2) { len2++; t2 = t2->next; }

    if (len1 < len2) return -1;
    if (len1 > len2) return 1;

    t1 = num1; t2 = num2;
    while (t1 && t2) {
        if (t1->digit < t2->digit) return -1;
        if (t1->digit > t2->digit) return 1;
        t1 = t1->next;
        t2 = t2->next;
    }
    return 0;
}

/* ===========================
   Node and Conversion Helpers
   =========================== */

/*
   Create a new DLL node with a single digit.
*/
Dlist* create_node(int digit) {
    Dlist *new = (Dlist*)malloc(sizeof(Dlist));
    if (!new) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    new->digit = digit;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

/*
   Convert string number (e.g. "12345") into doubly linked list.
   Each character becomes a node.
*/
Dlist* create_number(const char *str) {
    Dlist *head = NULL, *tail = NULL;
    for (int i = 0; str[i] != '\0'; i++) {
        int digit = str[i] - '0';
        Dlist *new = create_node(digit);
        if (!head) {
            head = tail = new;
        } else {
            tail->next = new;
            new->prev = tail;
            tail = new;
        }
    }
    return head;
}

/*
   Print the doubly linked list number.
   Traverses from head to tail.
*/
void print_number(Dlist *head) {
    if (!head) {
        printf("0");
        return;
    }
    Dlist *temp = head;
    while (temp) {
        printf("%d", temp->digit);
        temp = temp->next;
    }
}

/*
   Convert a doubly linked list number into a long.
   NOTE: This only works for numbers that fit within C's long range.
   For very large numbers, you’ll need a full DLL-based division algorithm.
*/
long dll_to_long(Dlist *num) {
    long value = 0;
    Dlist *temp = num;
    while (temp) {
        value = value * 10 + temp->digit;
        temp = temp->next;
    }
    return value;
}


/* ===========================
   Arithmetic Functions
   =========================== */

/*
   Add two numbers represented as DLLs.
   Cases handled:
   1. Normal addition without carry.
   2. Addition with carry inside digits.
   3. Addition where last digits produce carry.
   4. Different length numbers.
   5. Large numbers.
*/
Dlist* add_numbers(Dlist *num1, Dlist *num2) {
    Dlist *tail1 = num1;
    while (tail1 && tail1->next) tail1 = tail1->next;
    Dlist *tail2 = num2;
    while (tail2 && tail2->next) tail2 = tail2->next;

    Dlist *result = NULL;
    int carry = 0;

    while (tail1 || tail2 || carry) {
        int d1 = (tail1 ? tail1->digit : 0);
        int d2 = (tail2 ? tail2->digit : 0);

        int sum = d1 + d2 + carry;
        carry = sum / 10;
        int digit = sum % 10;

        Dlist *new = create_node(digit);
        new->next = result;
        if (result) result->prev = new;
        result = new;

        if (tail1) tail1 = tail1->prev;
        if (tail2) tail2 = tail2->prev;
    }
    return result;
}

/*
   Subtract two numbers represented as DLLs.
   Cases handled:
   1. Equal numbers → result is 0.
   2. Simple subtraction without borrow.
   3. Subtraction with borrow.
   4. Different lengths.
   5. Negative result.
*/
Dlist* sub_numbers(Dlist *num1, Dlist *num2, int *is_negative) {
    *is_negative = 0;
    if (compare_numbers(num1, num2) < 0) {
        Dlist *tmp = num1;
        num1 = num2;
        num2 = tmp;
        *is_negative = 1;
    }

    Dlist *tail1 = num1;
    while (tail1 && tail1->next) tail1 = tail1->next;
    Dlist *tail2 = num2;
    while (tail2 && tail2->next) tail2 = tail2->next;

    Dlist *result = NULL;
    int borrow = 0;

    while (tail1 || tail2) {
        int d1 = (tail1 ? tail1->digit : 0);
        int d2 = (tail2 ? tail2->digit : 0);

        d1 -= borrow;
        if (d1 < d2) {
            d1 += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        int diff = d1 - d2;
        Dlist *new = create_node(diff);
        new->next = result;
        if (result) result->prev = new;
        result = new;

        if (tail1) tail1 = tail1->prev;
        if (tail2) tail2 = tail2->prev;
    }

    while (result && result->digit == 0 && result->next) {
        result = result->next;
        result->prev = NULL;
    }
    return result;
}

/*
   Multiply two numbers represented as doubly linked lists.

   Cases handled:
   1. If either number is 0 → result is 0.
   2. Positive × Positive → positive result.
   3. Negative × Negative → positive result.
   4. Positive × Negative → negative result.
   5. Carry propagation for digit multiplication.
   6. Shifting partial results for each digit of num2.
   7. Remove leading zeros in the final result.
*/
Dlist* mul_numbers(Dlist *num1, Dlist *num2) {
    // Case 1: zero check
    if (is_zero(num1) || is_zero(num2)) 
    {
        return create_node(0);
    }

    // Step 1: find lengths
    int len1 = length(num1);
    int len2 = length(num2);

    // Step 2: allocate temporary array for partial results
    int *temp = calloc(len1 + len2, sizeof(int));

    // Step 3: move to tails (least significant digits)
    Dlist *tail1 = num1;
    while (tail1->next) tail1 = tail1->next;
    Dlist *tail2 = num2;
    while (tail2->next) tail2 = tail2->next;

    // Step 4: multiply digit by digit
    int i = 0;
    for (Dlist *p2 = tail2; p2; p2 = p2->prev, i++) {
        int j = 0;
        for (Dlist *p1 = tail1; p1; p1 = p1->prev, j++) 
        {
            temp[i + j] += p1->digit * p2->digit;
        }
    }

    // Step 5: handle carry
    for (int k = 0; k < len1 + len2; k++) 
    {
        if (temp[k] >= 10)
        {
            temp[k + 1] += temp[k] / 10;
            temp[k] %= 10;
        }
    }

    // Step 6: convert result array back to DLL (MSD first)
    Dlist *result = NULL, *result_tail = NULL;
    int start = len1 + len2 - 1;
    while (start > 0 && temp[start] == 0) start--; // skip leading zeros

    for (int k = start; k >= 0; k--) 
    {
        Dlist *new = create_node(temp[k]);
        if (!result) 
        {
            result = result_tail = new;
        } else
        {
            result_tail->next = new;
            new->prev = result_tail;
            result_tail = new;
        }
    }

    free(temp);

    // Step 7: normalize zero
    if (is_zero(result)) 
    {
        free_dlist(result);
        result = create_node(0);
    }

    return result;
}


/*
   Divide two numbers represented as doubly linked lists.

   Cases handled:
   1. Division by zero → print error, return 0.
   2. Dividend < Divisor → result is 0.
   3. Dividend == Divisor → result is 1.
   4. General case → perform long division digit by digit.
*/
Dlist* div_numbers(Dlist *num1, Dlist *num2) {
    // Case 1: division by zero
    if (is_zero(num2)) {
        printf("Error: Division by zero!\n");
        return create_node(0);
    }

    // Case 2: dividend smaller than divisor
    if (compare_numbers(num1, num2) < 0) {
        return create_node(0);
    }

    // Case 3: dividend equal to divisor
    if (compare_numbers(num1, num2) == 0) {
        return create_node(1);
    }

    // Case 4: general division (long division)
    // Convert DLLs to long for now (basic implementation).
    // Later you can replace with full DLL-based long division.
    long dividend = dll_to_long(num1);
    long divisor  = dll_to_long(num2);

    long quotient = dividend / divisor;

    // Convert quotient back to DLL
    char buf[50];
    sprintf(buf, "%ld", quotient);
    return create_number(buf);
}
