#include <stdio.h>
#include <stdlib.h>
#include "mystack.h"

#include <stdio.h>
#include <stdlib.h>


void concat(Stack* stack1, Stack* stack2, int pivot) {
    Stack* tmp = stack_new();
    while (!stack_empty(stack2)) {
        stack_push(tmp, stack_pop(stack2));
    }

    stack_push(stack1, pivot);

    while (!stack_empty(tmp)) {
        stack_push(stack1, stack_pop(tmp));
    }

    stack_destroy(tmp);
    stack_destroy(stack2);
}/*объединяет два стека, закидывая элемент-разделитель между ними и переносит
элементы из временного стека в первый стек*/

void partition(Stack* stack, Stack** stack1, Stack** stack2, int pivot) {
    *stack1 = stack_new();
    *stack2 = stack_new();
    while (!stack_empty(stack)) {
        int cur = stack_pop(stack);
        if (cur <= pivot) {
            stack_push(*stack1, cur);
        } else {
            stack_push(*stack2, cur);
        }
    }
}/*разбивает стек на два: один содержит все элементы меньшие или равные
заданному разделителю, другой - все элементы большие разделителя*/

void quickSort(Stack** stack) {
    if (stack_size(*stack) <= 1)
    	return;
    Stack *stack1, *stack2;
    int pivot = stack_pop(*stack);//опорным элементом берём вершину текущего стека
    partition(*stack, &stack1, &stack2, pivot);//разделяем стек на 2 стека
    quickSort(&stack1);//рекурсивно сортируем 1-ый стек
    quickSort(&stack2);//рекурсивно сортируем 2-ой стек
    Stack* tmp = *stack;
    concat(stack1, stack2, pivot);//объединяем стеки
    *stack = stack1;
    stack_destroy(tmp);
}//алгоритм быстрой сортировки


int main() {
    Stack* st = stack_new();
    int choice;
    while (1) {
    	printf("1. Добавить элемент стека?\n");
        printf("2. Удалить последний элемент?\n");
        printf("3. Распечатать стек?\n");
        printf("4. Отсортировать стек?\n");
        printf("5. Закончить работу программы?\n");

        printf("Введите номер команды: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Вы выбрали команду: Добавить элемент стека\n");
                printf("Введите значение элемента: ");
                int x;
                scanf("%d", &x);
        		stack_push(st, x);
                break;
            case 2:
                printf("Вы выбрали команду: Удалить последний элемент\n");
        	int y = stack_pop(st);
        	printf("Удалён элемент со значением %d\n", y);
                break;
            case 3:
                printf("Вы выбрали команду: Распечатать стек\n");
               	stack_print(st);
               	printf("\n");
                break;
            case 4:
                printf("Отсортировать стек\n");
                quickSort(&st);
                break;
            case 5:
                printf("Вы выбрали команду: Закончить работу программы\n");
                stack_destroy(st);
    		return 0;
                break;
            default:
                printf("Ошибка: неправильный ввод. Попробуйте еще раз.\n");
                break;
        }
	}
    return 0;
}
