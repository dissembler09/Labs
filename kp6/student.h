#ifndef _STUDENT_H_
#include <stdint.h>
#define _STUDENT_H_

#define STR_SIZE 24

typedef struct {
    char surname[STR_SIZE];
    char initials[3];
    char gender[1];
    char group[1];
    char course[2];
    char job[STR_SIZE];
    char vuz[STR_SIZE];
} Student;

typedef struct _list {
    int id;
    int counter;
    Student st;
    struct _list *prev;
} List;

void list_destroy(List *l);
int searching(List* l, char* surname);
int get_answer(List *l);
List *create_table(FILE *in);
int info_student(FILE *in, char *surname, char *initials);
List *add_student(FILE *add_file, List *l);
void remove_student(char *file, char *surname, char *initials, List **list);
#endif
