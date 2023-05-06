#include <stdio.h>
#include <stdlib.h>

#include "student.h"
#include "io.h"

int student_read_txt(Student *s, FILE *in)
{
    fscanf(in, "%s", s->surname);
    fscanf(in, "%s", s->initials);
    fscanf(in, "%s", s->gender);
    fscanf(in, "%s", s->group);
    fscanf(in, "%s", s->course);
    fscanf(in, "%s", s->job);
    fscanf(in, "%s", s->vuz);
    return !feof(in);
}

void student_write_txt(Student *s, FILE *file)
{
    fprintf(file, "%s\t", s->surname);
    fprintf(file, "%s\t", s->initials);
    fprintf(file, "%s\t ", s->gender);
    fprintf(file, "%s\t", s->group);
    fprintf(file, "%s\t", s->course);
    fprintf(file, "%s\t", s->job);
    fprintf(file, "%s\t", s->vuz);
    fprintf(file, "\n");
}

int student_read_bin(Student *s, FILE *in)
{
    fread(s->surname,      sizeof(char), STR_SIZE, in);
    fread(s->initials,     sizeof(char), STR_SIZE, in);
    fread(s->gender,       sizeof(char), STR_SIZE, in);
    fread(s->group,        sizeof(char), STR_SIZE, in);
    fread(s->course,        sizeof(char), STR_SIZE, in);
    fread(s->job,        sizeof(char), STR_SIZE, in);
    fread(s->vuz,        sizeof(char), STR_SIZE, in);
    return !feof(in);
}

void student_write_bin(Student *s, FILE *out)
{
    fwrite(s->surname,  sizeof(char), STR_SIZE, out);
    fwrite(s->initials, sizeof(char), STR_SIZE, out);
    fwrite((s->gender), sizeof(char), STR_SIZE, out);
    fwrite((s->group),  sizeof(char), STR_SIZE, out);
    fwrite((s->course),  sizeof(char), STR_SIZE, out);
    fwrite((s->job),  sizeof(char), STR_SIZE, out);
    fwrite((s->vuz),  sizeof(char), STR_SIZE, out);
}
