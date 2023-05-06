#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"


void list_destroy(List *l)
{
    if (l->prev) {
        list_destroy(l->prev);
    }
    free(l);
    l = NULL;
}

int searching(List* l, char* surname)
{
    int c = 0;
    while (l->prev) {
        if (!strcmp(l->st.surname, surname)) {
            c += 1;
        }
        l = l->prev;
    }
    return c;
}

int get_answer(List *l)
{
    while (l->prev) {
        if (l->counter > 0) {
            return 1;
        }
        l = l->prev;
    }
    return 0;
}

List *create_table(FILE *in)
{
    List *l = (List *)malloc(sizeof(List));
    l->id = 0;
    l->prev = NULL;
    l->counter = 0;
    Student stud;
    while (student_read_bin(&stud, in)) {
        List *new = (List *)malloc(sizeof(List));
        new->st = stud;
        new->id = l->id + 1;
        new->prev = l;
        new->counter = searching(l, stud.surname);
        l = new;
    }
    return l;
}

int info_student(FILE *in, char *surname, char *initials)
{
    Student st;
    int k = 0;
    while (student_read_bin(&st, in)) {
        if (!strcmp(st.surname, surname) && !strcmp(st.initials, initials)) {
            k = 1;
            printf("Имя: %s %s\nПол: %s\nНомер класса: %s\nБуква класса:  %s\nВУЗ:  %s\nМесто работы:  %s\n", st.surname, st.initials, st.gender, st.course, st.group, st.vuz, st.job);
        }
    }
    return k;
}

List *add_student(FILE *add_file, List *l)
{
    Student student;
    memset(&student, 0, sizeof(Student));
    fscanf(stdin, "%s", student.surname);
    if (feof(stdin)) {
        return;
    }
    fscanf(stdin, "%s", student.initials);
    if (feof(stdin)) {
        return;
    }
    fscanf(stdin, "%s", student.gender);
    if (feof(stdin)) {
        return;
    }
    fscanf(stdin, "%s", student.course);
    if (feof(stdin)) {
        return;
    }
    fscanf(stdin, "%s", student.group);
    if (feof(stdin)) {
        return;
    }
    fscanf(stdin, "%s", student.vuz);
    if (feof(stdin)) {
        return;
    }
    fscanf(stdin, "%s", student.job);
    if (feof(stdin)) {
        return;
    }
    student_write_bin(&student, add_file);
    List *new = (List *)malloc(sizeof(List));
    new->st = student;
    new->id = l->id + 1;
    new->prev = l;
    new->counter = searching(l, student.surname);
    l = new;
    return l;
}

void remove_student(char *file, char *surname, char *initials, List *l)
{
    FILE *in = fopen(file, "r");
        if (!in) {
            printf("I/O Error: can't open file.\n");
            exit(1);
        }
    FILE *tmp = fopen("tmp", "w");
    Student student;
    while (student_read_bin(&student, in)) {
        if (strcmp(student.surname, surname)) {
            student_write_bin(&student, tmp);
        } else if (strcmp(student.initials, initials)) {
            student_write_bin(&student, tmp);
        }
    }
    fclose(in);
    fclose(tmp);

    in = fopen(file, "w");
    if (!in) {
        printf("I/O Error: can't open file.\n");
        exit(1);
    }
    tmp = fopen("tmp", "r");
    while (student_read_bin(&student, tmp)) {
        if (strcmp(student.surname, surname) != 0) {
            student_write_bin(&student, in);
        } else if (strcmp(student.initials, initials) != 0) {
            student_write_bin(&student, in);
        }
    }
    fclose(in);
    fclose(tmp);
    remove("tmp");
}