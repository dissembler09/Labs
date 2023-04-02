#ifndef MYSTACK
#define MYSTACK
#include <stdlib.h>

typedef struct stack{
    int value;
    struct stack* next;
} Stack;

void stack_push(Stack **s, int value);
int stack_pop(Stack **s);
void delete_node(Stack** head, Stack* node_del);
Stack* get_last(Stack* s);
void stack_print(Stack* s);
int stack_size(Stack** stack);
#endif
