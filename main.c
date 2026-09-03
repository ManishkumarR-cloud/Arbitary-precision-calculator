#include <stdio.h>
#include <string.h>
#include "apc.h"
#include "validation.h"

int main(int argc, char *argv[])
{
    // Step 1: Validate command line arguments
    if (validate_args(argc, argv) == FAILURE)
    {
        return FAILURE;
    }

    // Step 2: Convert input strings into doubly linked list numbers
    Dlist *num1 = create_number(argv[1]);
    Dlist *num2 = create_number(argv[3]);
    Dlist *result = NULL;

    // Step 3: Perform the chosen operation
    if (strcmp(argv[2], "+") == 0)
    {
        result = add_numbers(num1, num2);
    }
    else if (strcmp(argv[2], "-") == 0)
    {
        result = sub_numbers(num1, num2);
    }
    else if (strcmp(argv[2], "x") == 0)
    {
        result = mul_numbers(num1, num2);
    }
    else if (strcmp(argv[2], "/") == 0)
    {
        result = div_numbers(num1, num2);
    }

    // Step 4: Print the result
    printf("Result: ");
    print_number(result);
    printf("\n");

    return SUCCESS;
}
