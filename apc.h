#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>

// Common return codes
#define SUCCESS 0
#define FAILURE -1

// Doubly linked list node structure
typedef struct node {
    int digit;              // single digit (0–9)
    struct node *prev;      // pointer to previous node
    struct node *next;      // pointer to next node
} Dlist;

// Function prototypes
Dlist* create_number(const char *str);   // convert string to DLL
void print_number(Dlist *head);          // print DLL as number

// Arithmetic operations
Dlist* add_numbers(Dlist *num1, Dlist *num2);   // addition
Dlist* sub_numbers(Dlist *num1, Dlist *num2);   // subtraction
Dlist* mul_numbers(Dlist *num1, Dlist *num2);   // multiplication
Dlist* div_numbers(Dlist *num1, Dlist *num2);   // division

#endif
