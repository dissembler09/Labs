#include <stdio.h>
#include <stdlib.h>
#include "mystack.h"

#include <stdio.h>
#include <stdlib.h>

// Функция для деления стека на две части
Stack* partition(Stack* head, Stack* end, Stack** newHead, Stack** newEnd) {
    Stack* pivot = end;  // Выбираем последний узел в качестве опорного
    Stack* prev = NULL;
    Stack* cur = head;
    Stack* tail = pivot;

    // Перебираем все узлы до опорного
    while (cur != pivot) {
        if (cur->value < pivot->value) {
            /* Если значение текущего узла меньше опорного,
            то меняем местами значения текущего и предыдущего узлов*/
            if (*newHead == NULL)
                *newHead = cur;
            prev = cur;
            cur = cur->next;
        } else {
            // Иначе перемещаем текущий узел в конец стека
            if (prev)
                prev->next = cur->next;
            Stack* tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    // Если опорный узел был самым большим, то его перемещаем в конец стека
    if (*newHead == NULL)
        *newHead = pivot;

    *newEnd = tail;

    return pivot;
}

// Функция для быстрой сортировки стека
Stack* quickSort(Stack* head, Stack* end) {
    if (!head || head == end)
        return head;

    Stack* newHead = NULL;
    Stack* newEnd = NULL;

    // Делим стек на две части и выбираем опорный элемент
    Stack* pivot = partition(head, end, &newHead, &newEnd);

    // Если опорный элемент не первый в списке, то рекурсивно вызываем сортировку
    if (newHead != pivot) {
        Stack* tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;

        newHead = quickSort(newHead, tmp);

        tmp = get_last(newHead);
        tmp->next = pivot;
    }

    // Рекурсивно вызываем сортировку для второй части стека
    pivot->next = quickSort(pivot->next, newEnd);
	// Возвращаем указаьель на начало стека
    return newHead;
}

int main() {
    Stack* st = NULL;
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
        		stack_push(&st, x);
                break;
            case 2:
                printf("Вы выбрали команду: Удалить последний элемент\n");
        		int y = stack_pop(&st);
        		printf("Удалён элемент со значением %d\n", y);
                break;
            case 3:
                printf("Вы выбрали команду: Распечатать стек\n");
               	stack_print(st);
               	printf("\n");
                break;
            case 4:
                printf("Отсортировать стек\n");
                st = quickSort(st, get_last(st));
                break;
            case 5:
                printf("Вы выбрали команду: Закончить работу программы\n");
    			return 0;
                break;
            default:
                printf("Ошибка: неправильный ввод. Попробуйте еще раз.\n");
                break;
        }
	}
    return 0;
}
