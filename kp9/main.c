#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "table.h"

int main(int argc, char *argv[]) {
    List* l = create_list();
    FILE *in = fopen(argv[1], "r");
    if (!in) {
        printf("I/O Error: can't open file.\n");
        free_List(l);
        exit(1);
    }
    read_table(l, in);
    fclose(in);

    if (is_list_sorted(l, true)) {
        l->sorted = 1;
    } else if (is_list_sorted(l, false)) {
        l->sorted = -1;
    } else {
        l->sorted = 0;
    }

    char what_do[STR_SIZE];
    printf("\tprint - Напечатать таблицу\n");
    printf("\tadd [ключ] [значение] - добавить запись в таблицу\n");
    printf("\tremove - удалить последнюю запись\n");
    printf("\tfind [ключ] - найти значение по ключу\n");
    printf("\tsort - отсортировать таблицу\n");
    printf("\tissort? - отсортирован ли список?\n");
    printf("\texit - завершение программы\n");
    while (!feof(stdin)) {
        fscanf(stdin, "%s", what_do);
        if (feof(stdin)) {
            break;
        }
        if (!strcmp(what_do, "print")) {
            table_print(l);
        }else if (!strcmp(what_do, "add")) {
            char key[7];
            char data[STR_SIZE];
            scanf("%s", key);
            scanf("%s", data);
            add_to_list(l, key, data);
            l->sorted = 0;
            printf("Запись добавлена.\n");
        } else if (!strcmp(what_do, "remove")) {
            table_pop(l);
            printf("Последняя запись удалена.\n");
        } else if (!strcmp(what_do, "close") || !strcmp(what_do, "exit")) {
            FILE* f1 = fopen("new_table.txt", "w");
            write_list(f1, l);
            ShakerSort(l);
            FILE* f2 = fopen("new_sorted_table.txt", "w");
            write_list(f2, l);
            reverse_list(l);
            FILE* f3 = fopen("new_sorted_reversed_table.txt", "w");
            write_list(f3, l);
            fclose(f1);
            fclose(f2);
            fclose(f3);
            printf("В файле <new_table.txt> содержится обновлённый список, в файле <new_sorted_table.txt> - отсортированный список,\nв файле <new_sorted_reversed_table.txt> - отсортированный в обратном порядке список\n");
            break;
        } else if (!strcmp(what_do, "find")) {
            char key[7];
            scanf("%s", key);
            if (l->sorted == 0) {
                printf("Отсортируйте, пожалуйста, список!\n");
            } else if (l->sorted == -1) {
                reverse_list(l);
                char* result = binary_search(l, key);
                if (result == NULL) {
                    printf("Нет данного ключа!\n");
                } else {
                    printf("%s\n", result);
                }
            } else {
                char* result = binary_search(l, key);
                if (result == NULL) {
                    printf("Нет данного ключа!\n");
                } else {
                    printf("%s\n", result);
                }
            }
        } else if (!strcmp(what_do, "sort")) {
            ShakerSort(l);
            l->sorted = 1;
            printf("Список отсортирован:)\n");
        } else if (!strcmp(what_do, "issort?")) {
            if (l->sorted == 1) {
                printf("Список отсортирован по возрастанию!\n");
            } else if (l->sorted == -1) {
                printf("Список отсортирован по убыванию!\n");
            } else {
                printf("Список не отсортирован :(\n");
            }
        } else {
            printf("Непонятная команда!!!\n");
        }
    }
    free_List(l);
}
