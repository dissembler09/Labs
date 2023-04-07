#include "mystack.h"

#include <stdio.h>

int stack_empty(Stack* s) {
    return (s->size == 0);
} //является ли стек пустым

Stack* stack_new() {
    Stack* result = (Stack*)malloc(sizeof(Stack));
    result->top = NULL;
    result->size = 0;
    return result;
}//функция создания стека

void stack_destroy(Stack *s) {
    while (!stack_empty(s)) {
        stack_pop(s);
    }
    free(s);
}//удаления стека с очисткой всей используемой памяти

void stack_push(Stack* s, int value)
{
	StackNode* n = (StackNode*)malloc(sizeof(StackNode));
    n->prev = s->top;
    n->value = value;
    s->top = n;
    s->size++;
}//функция добавления элемента в стек

void stack_print(Stack* s)
{
	StackNode* cur = s->top;
    while (cur) {
        printf("%d ", cur->value);
        cur = cur->prev;
    }
}//функция печати стека

int stack_top(Stack* s) {
    if (stack_empty(s)) {
    	printf("Stack is empty!");
    	return 0;
    }
    return s->top->value;
}//возвращает вершину стека

int stack_pop(Stack* s) {
	if (stack_empty(s)) {
    	printf("Stack is empty!");
    	return 0;
    }
    int result = stack_top(s);
    StackNode* tmp = s->top;
    s->top = s->top->prev;
    free(tmp);
    s->size--;
    return result;
}//возвращаем и удаляем вершину стека

int stack_size(Stack* stack){
    return stack->size;
}//размер стека
