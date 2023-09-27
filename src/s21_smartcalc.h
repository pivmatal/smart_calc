#ifndef SRC_S21_SMARTCALC_H_
#define SRC_S21_SMARTCALC_H_
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    char *data;
    struct node* link;
};
typedef struct node stack_n;


// stack functions
void push_stack(char x[], stack_n** top);
void pop_stack(stack_n** top);
void print_stack(stack_n** top);

// polish functions
int is_digit(char op);
int is_operator(char op);
int unar_operation(char op) ;
int is_valid(char expression[]);
int get_operator_priority(char op);
void parser(char expression[], char result_mass[]);
void transform_mass(char expression[]);

// calc functions
double calculation(char expression[]);
double start(char expression[],char x[]);
void from_x_to_func(char expression[], char x[]);

#endif  // SRC_S21_SMARTCALC_H_
