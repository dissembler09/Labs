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
        printf("6. Узнать элемент по индексу?\n");
        printf("7. Удалить элемент по индексу?\n");
        printf("8. Вставить элемент по индексу?\n");
        printf("9. Закончить работу программы?\n");
        

        printf("Введите номер команды: ");
        scanf("%d", &choice);
        int ind;
        double elem;

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
                int check = removeNode(list, y);
                if (check) {
        	        printf("Удалён элемент со значением %lf\n", y);
                } else {
                    printf("Такого элемента нет!\n");
                }
                break;
            case 3:
                printf("Вы выбрали команду: Распечатать список\n");
                List* rlist = reversed_list(list);
               	printlist(rlist);
                clearList(rlist);
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
                printf("Вы выбрали команду: узнать элемент по индексу\n");
                scanf("%d", &ind);
                if (ind < 0 || ind >= list->size) {
                    printf("Некорректный индекс!\n");
                } else {
                    printf("%lf\n", get_element(list, list->size - ind));
                }
                break;
            case 7:
                printf("Вы выбрали команду: удалить элемент по индексу\n");
                scanf("%d", &ind);
                if (ind < 0 || ind >= list->size) {
                    printf("Некорректный индекс!\n");
                } else {
                    delete_elem_ind(list, list->size - ind);
                }
                break;
            case 8:
                printf("Вы выбрали команду: вставить элемент по индексу\n");
                printf("Введите значение элемента:\n");
                scanf("%lf", &elem);
                printf("Введите индекс:\n");
                scanf("%d", &ind);
                if (ind < 0 || ind > list->size) {
                    printf("Некорректный индекс!\n");
                } else {
                    insert_elem_ind(list, elem, list->size - ind + 1);
                }
                break;
            case 9:
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
