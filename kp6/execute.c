#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#include "io.h"

int main(int argc, char *argv[])
{
    FILE *in = fopen(argv[1], "r");
    if (!in) {
        printf("I/O Error: can't open file.\n");
        exit(1);
    }
    List *list = create_table(in);
    fclose(in);

    char what_do[STR_SIZE];
    if (argc != 2) {
        printf("Usage:\n\t./execute DB_FILE\n");
        exit(0);
    }
    printf("\tresult - есть ли в школе однофамильцы?\n");
    printf("\tadd    [фамилия] [инициалы] [пол] [номер класса] [буква класса] [место учёбы] [место работы] - добавить выпускника\n");
    printf("\tremove    [фамилия] [инициалы] - удалить выпускника\n");
    printf("\tinfo    [фамилия] [инициалы] - информация о выпускнике\n");
    printf("\texit - завершение программы\n");
    while (!feof(stdin)) {
        fscanf(stdin, "%s", what_do);
        if (feof(stdin)) {
            break;
        }
        if (!strcmp(what_do, "result")) {
                int result = get_answer(list);
                if (result == 1) {
                    printf("Однофамильцы есть.\n");
                } else {
                    printf("Однофамильцев нет.\n");
                }
        }else if (!strcmp(what_do, "add")) {
            FILE *add_file = fopen(argv[1], "a");
            if (!add_file) {
            printf("I/O Error: can't open file.\n");
                exit(1);
            }
            if (feof(stdin)) {
                fclose(add_file);
                break;
            }
            list = add_student(add_file, list);
            fclose(add_file);
            printf("Выпускник добавлен.\n");
        } else if (!strcmp(what_do, "remove")) {
            char surname[STR_SIZE];
            char initials[STR_SIZE];
            fscanf(stdin, "%s", surname);
            if (feof(stdin)) {
                break;
            }
            fscanf(stdin, "%s", initials);
            remove_student(argv[1], surname, initials, &list);
            if (feof(stdin)) {
                break;
            }
        } else if (!strcmp(what_do, "close") || !strcmp(what_do, "exit")) {
            break;
        } else if (!strcmp(what_do, "info")) {
            FILE *in = fopen(argv[1], "r");
            if (!in) {
                printf("I/O Error: can't open file.\n");
                exit(1);
            }
            char surname[STR_SIZE];
            char initials[3];
            fscanf(stdin, "%s", &surname);
            if (feof(stdin)) {
                break;
            }
            fscanf(stdin, "%s", &initials);
            if (feof(stdin)) {
                fclose(in);
                break;
            }
            int check = info_student(in, surname, initials);
            if (!check) {
                printf("Таких выпускников нет.\n");
            }
            fclose(in);
        }
    }
    list_destroy(list);
    return 0;
}
