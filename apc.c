#include "apc.h"

/* ===========================
   Helper Functions
   =========================== */

/* Create a new DLL node with a single digit */
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

/* Convert string number (e.g. "12345") into doubly linked list */
Dlist* create_number(const char *str) {
    Dlist *head = NULL, *tail = NULL;

    for (int i = 0; str[i] != '\0'; i++) {
        int digit = str[i] - '0';   // convert char → int
        Dlist *new = create_node(digit);

        if (head == NULL) {
            head = tail = new;      // first node
        } else {
            tail->next = new;       // link new node at end
            new->prev = tail;       // back-link to previous
            tail = new;             // update tail
        }
    }
    return head;
}

/* Print the doubly linked list number */
void print_number(Dlist *head) {
    if (head == NULL) {
        printf("0");
        return;
    }
    Dlist *temp = head;
    while (temp) {
        printf("%d", temp->digit);
        temp = temp->next;
    }
}

/* ===========================
   Addition Function
   =========================== */

/*
   Add two numbers represented as doubly linked lists.
   Possible cases handled:
   1. Normal addition without carry (e.g. 123 + 456 = 579).
   2. Addition with carry inside digits (e.g. 59 + 7 = 66).
   3. Addition where last digits produce carry (e.g. 9 + 9 = 18).
      → creates an extra node for carry.
   4. Different length numbers (e.g. 123 + 9 = 132).
   5. Large numbers (e.g. 999 + 1 = 1000).
*/
Dlist* add_numbers(Dlist *num1, Dlist *num2) {
    // Step 1: move to the tail of both lists (least significant digit)
    Dlist *tail1 = num1;
    while (tail1 && tail1->next) tail1 = tail1->next;

    Dlist *tail2 = num2;
    while (tail2 && tail2->next) tail2 = tail2->next;

    Dlist *result = NULL;   // head of result list
    int carry = 0;

    // Step 2: add digits from right to left
    while (tail1 || tail2 || carry) {
        int d1 = (tail1 ? tail1->digit : 0);
        int d2 = (tail2 ? tail2->digit : 0);

        int sum = d1 + d2 + carry;
        carry = sum / 10;          // calculate carry
        int digit = sum % 10;      // store only single digit

        // Step 3: create new node for result digit
        Dlist *new = create_node(digit);
        new->next = result;        // insert at front
        if (result) result->prev = new;
        result = new;

        // Step 4: move left in both lists
        if (tail1) tail1 = tail1->prev;
        if (tail2) tail2 = tail2->prev;
    }
    return result;  // head of result list
}

/* ===========================
   Placeholders for other operations
   =========================== */

Dlist* sub_numbers(Dlist *num1, Dlist *num2) {
    // TODO: implement subtraction with borrow
    printf("Subtraction not implemented yet.\n");
    return NULL;
}

Dlist* mul_numbers(Dlist *num1, Dlist *num2) {
    // TODO: implement multiplication (long multiplication style)
    printf("Multiplication not implemented yet.\n");
    return NULL;
}

Dlist* div_numbers(Dlist *num1, Dlist *num2) {
    // TODO: implement division (long division style)
    printf("Division not implemented yet.\n");
    return NULL;
}
