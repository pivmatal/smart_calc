#include "s21_smartcalc.h"

void push_stack(char x[], stack_n** top){
    stack_n *new_node = (stack_n*)malloc(sizeof(stack_n));
    new_node->data = (char *)malloc(strlen(x) * sizeof(char));
    strcpy(new_node->data, x);
    new_node->link = *top;
    *top = new_node;
}

void pop_stack(stack_n** top){
    if (*top == NULL)
        return;
    stack_n *tmp = (*top)->link;
    free((*top)->data);
    free(*top);
    *top = tmp;
}

void print_stack(stack_n** top) {
    stack_n* tmp = *top;
    while (tmp != NULL) {
        // printf("%s\n", tmp->data);
        tmp = tmp->link;
    }
}
