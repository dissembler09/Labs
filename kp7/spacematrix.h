#ifndef __SPMATRIX_H__
#define __SPMATRIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    int* data;//индекс начала строки в векторе А
    int size;
    int capacity;
} Mas_M;

typedef struct {
    int column; //номер столбца ненулевого элемента
    float value;//значение ненулевого элемента
    int next_ind;//индекс следующего ненудевого элемента или -1 если в строке нет ненудевых элементов больше
} Elem;

typedef struct {
    Elem* data;
    int size; 
    int capacity;
} VectorA;

VectorA init_vec_a();
void push_vec_a(VectorA* vec, int column, float value, int index);
void push_mas_M(Mas_M* mas, int element);
void fill_mas_vector(VectorA* vector, Mas_M* mas, FILE* file);
void print_matrix(VectorA* vec, Mas_M* mas, FILE* file);
void print_vec(VectorA* vec);
void print_mas(Mas_M* mas);
void multiply(VectorA* vec, Mas_M* mas, float* x, int size);
void free_vector_a(VectorA* vec);
void free_mas(Mas_M* mas);
#endif
