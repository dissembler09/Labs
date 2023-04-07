#ifndef MYSTACK
#define MYSTACK
#include <stdlib.h>

typedef struct stackNode {
    int value;
    struct stackNode *prev;
} StackNode; //обозначим структуру на которой будет базироваться стек

typedef struct stack {
    StackNode* top;
    int size;
} Stack;//структура самого стека

int stack_empty(Stack *s);
Stack* stack_new();
void stack_destroy(Stack *s);
void stack_push(Stack *s, int value);
int stack_pop(Stack *s);
int stack_top(Stack* s);
void stack_print(Stack* s);
int stack_size(Stack* stack);
#endif
