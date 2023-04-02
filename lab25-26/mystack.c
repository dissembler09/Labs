#include "mystack.h"

#include <stdio.h>

void stack_push(Stack** s, int new_value)
{
	Stack* p = (Stack*)malloc(sizeof(Stack));
	p->value = new_value;
	p->next = *s;
	*s = p;
}

void delete_node(Stack** head, Stack* node_del) {
	if(*head == node_del) {
		*head = node_del->next;
	} else {
		Stack* current = *head;
		while (current->next != node_del) {
			current = current->next;
		}
		current->next = node_del->next;
	}
	free(node_del);
}

void stack_print(Stack* s) 
{
	while (s) {
		printf("%d ", s->value);
		s = s->next;
	}
}

Stack* get_last(Stack* s){
    while(s && s->next){
        s = s->next;
    }
    return s;
}

int stack_pop(Stack** s) {
    Stack* current = *s;
    while (current->next != NULL && current->next->next != NULL) {
    	current = current->next;
    }
    int data = current->next->value;
    delete_node(s, current->next);
    return data;
}

int stack_size(Stack** stack){
    int size = 0;
    Stack* current = *stack;

    while(current != NULL){
        size++;
        current = current->next;
    }
    return size;
}
