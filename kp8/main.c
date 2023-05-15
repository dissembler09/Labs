#include <stdio.h>
#include <stdlib.h>
#include "mylist.h"

int main() {
    List* list = createList();
    int choice;
    while (1) {
    	printf("1. Добавить элемент в список?\n");
        printf("2. Удалить элемент?\n");
        printf("3. Распечатать список?\n");
        printf("4. Узнать размер списка?\n");
        printf("5. Удалить несколько последних элементов?\n");
        printf("6. Закончить работу программы?\n");

        printf("Введите номер команды: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Вы выбрали команду: Добавить элемент в список\n");
                printf("Введите значение элемента: ");
                double x;
                scanf("%lf", &x);
        	insertList(list, x);
                break;
            case 2:
                printf("Вы выбрали команду: Удалить элемент\n");
        	printf("Введите значение элемента: ");
                double y;
                scanf("%lf", &y);
                removeNode(list, y);
        	printf("Удалён элемент со значением %lf\n", y);
                break;
            case 3:
                printf("Вы выбрали команду: Распечатать список\n");
               	printlist(list);
               	printf("\n");
                break;
            case 4:
                printf("Узнать размер списка\n");
                printf("%d\n", sizeList(list));
                break;
            case 5:
                printf("Удалить несколько последних элементов\n");
                printf("Введите количество элементов: ");
                int k;
                scanf("%d", &k);
                removeLastKNodes(list, k);
                break;
            case 6:
                printf("Вы выбрали команду: Закончить работу программы\n");
                clearList(list);
    		return 0;
                break;
            default:
                printf("Ошибка: неправильный ввод. Попробуйте еще раз.\n");
                break;
        }
	}
    return 0;
}
