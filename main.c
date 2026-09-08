#include <stdio.h>
#include <string.h>
#include "apc.h"
#include "validation.h"
#include "sign.h"   // sign parsing helper

int main(int argc, char *argv[])
{
    if (validate_args(argc, argv) == FAILURE) {
        return FAILURE;
    }

    // Parse signs and strip them
    int sign1 = get_sign(&argv[1]);
    int sign2 = get_sign(&argv[3]);

    // Convert to DLL numbers (digits only now)
    Dlist *num1 = create_number(argv[1]);
    Dlist *num2 = create_number(argv[3]);
    Dlist *result = NULL;
    int is_negative = 0;

    // Dispatch based on operator and signs
    if (strcmp(argv[2], "+") == 0) {
        if (sign1 == sign2) {                 // + + or - - → addition
            result = add_numbers(num1, num2);
            if (sign1 == -1) is_negative = 1; // both negative → result negative
        } else {                              // + - or - + → subtraction
            result = sub_numbers(num1, num2, &is_negative);
            if (is_negative && sign1 == +1) is_negative = 0;
            else if (!is_negative && sign1 == -1) is_negative = 1;
        }
    } else if (strcmp(argv[2], "-") == 0) {
        if (sign1 == +1 && sign2 == -1) {     // (+) - (-) → addition, positive
            result = add_numbers(num1, num2);
            is_negative = 0;
        } else if (sign1 == -1 && sign2 == +1) { // (-) - (+) → addition, negative
            result = add_numbers(num1, num2);
            is_negative = 1;
        } else {                              // (+) - (+) or (-) - (-) → subtraction
            result = sub_numbers(num1, num2, &is_negative);
        }
    } else if (strcmp(argv[2], "x") == 0) {
        result = mul_numbers(num1, num2);     // multiplication
        if (!is_zero(result) && sign1 != sign2) is_negative = 1;
    } else if (strcmp(argv[2], "/") == 0) {
        result = div_numbers(num1, num2);     // division
        if (!is_zero(result) && sign1 != sign2) is_negative = 1;
    } else {
        printf("Invalid operator!\n");
        return FAILURE;
    }

    // Print result with sign (avoid -0)
    printf("Result: ");
    if (is_negative && !is_zero(result)) printf("-");
    print_number(result);
    printf("\n");

    return SUCCESS;
}
