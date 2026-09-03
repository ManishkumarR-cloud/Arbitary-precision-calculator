#include "apc.h"        // for SUCCESS / FAILURE macros
#include "validation.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
   Validate command line arguments:
   1. Must have exactly 4 arguments.
   2. Operator must be one of +, -, x, /.
   3. Both numbers must contain only digits.
*/
int validate_args(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: ./a.out <number1> <operator> <number2>\n");
        printf("Operators: +  -  x  /\n");
        return FAILURE;
    }

    if (!(strcmp(argv[2], "+") == 0 ||
          strcmp(argv[2], "-") == 0 ||
          strcmp(argv[2], "x") == 0 ||
          strcmp(argv[2], "/") == 0)) {
        printf("Error: Invalid operator '%s'.\n", argv[2]);
        return FAILURE;
    }

    for (int i = 0; argv[1][i]; i++) {
        if (!isdigit(argv[1][i])) {
            printf("Error: First number contains non-digit characters.\n");
            return FAILURE;
        }
    }
    for (int i = 0; argv[3][i]; i++) {
        if (!isdigit(argv[3][i])) {
            printf("Error: Second number contains non-digit characters.\n");
            return FAILURE;
        }
    }

    return SUCCESS;
}
