#include "apc.h"        // for SUCCESS / FAILURE macros
#include "validation.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
   Validate command line arguments:
   1. Must have exactly 4 arguments.
   2. Operator must be one of +, -, x, /.
   3. Both numbers must contain only digits (after optional single sign).
   4. Reject multiple signs (++,+-,-+,--).
*/
int validate_args(int argc, char *argv[]) 
{
    if (argc != 4) 
    {
        printf("Usage: ./a.out <number1> <operator> <number2>\n");
        printf("Operators: +  -  x  /\n");
        return FAILURE;
    }

    // Validate operator
    if (!(strcmp(argv[2], "+") == 0 ||
          strcmp(argv[2], "-") == 0 ||
          strcmp(argv[2], "x") == 0 ||
          strcmp(argv[2], "/") == 0)) {
        printf("Error: Invalid operator '%s'.\n", argv[2]);
        return FAILURE;
    }

    // --- Validate first operand ---
    int sign_count = 0;
    int i = 0;
    while (argv[1][i] == '+' || argv[1][i] == '-') 
    {
        sign_count++;
        i++;
    }
    if (sign_count > 1) 
    {
        printf("Error: First number has multiple signs.\n");
        return FAILURE;
    }
    for (; argv[1][i]; i++) 
    {
        if (!isdigit(argv[1][i])) 
        {
            printf("Error: First number contains non-digit characters.\n");
            return FAILURE;
        }
    }

    // --- Validate second operand ---
    sign_count = 0;
    i = 0;
    while (argv[3][i] == '+' || argv[3][i] == '-') 
    {
        sign_count++;
        i++;
    }
    if (sign_count > 1) 
    {
        printf("Error: Second number has multiple signs.\n");
        return FAILURE;
    }
    for (; argv[3][i]; i++) 
    {
        if (!isdigit(argv[3][i])) 
        {
            printf("Error: Second number contains non-digit characters.\n");
            return FAILURE;
        }
    }

    return SUCCESS;
}
