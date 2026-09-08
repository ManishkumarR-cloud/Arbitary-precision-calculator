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

/* ===========================
   Helper Function Prototypes
   =========================== */
Dlist* create_node(int digit);              // create a new DLL node
Dlist* create_number(const char *str);      // convert string to DLL
void   print_number(Dlist *head);           // print DLL as number
int    compare_numbers(Dlist *num1, Dlist *num2); // compare two DLL numbers
void   dll_to_string(Dlist *num, char *buf);      // convert DLL to string
long   dll_to_long(Dlist *num);             // convert DLL to long (basic)

// Helpers for multiplication/division
int is_zero(Dlist *num);     // check if number is zero
int length(Dlist *num);      // count digits in DLL
void free_dlist(Dlist *head);   // free a DLL

/* ===========================
   Arithmetic Function Prototypes
   =========================== */
Dlist* add_numbers(Dlist *num1, Dlist *num2);                     // addition
Dlist* sub_numbers(Dlist *num1, Dlist *num2, int *is_negative);   // subtraction with negative flag
Dlist* mul_numbers(Dlist *num1, Dlist *num2);                     // multiplication
Dlist* div_numbers(Dlist *num1, Dlist *num2);                     // division

#endif
