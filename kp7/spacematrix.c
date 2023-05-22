#include "spacematrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

VectorA init_vec_a() {
    VectorA vec;
    vec.size = 0;
    vec.capacity = 1;
    vec.data = malloc(vec.capacity * sizeof(Elem));
    return vec;
}

Mas_M init_mas_m() {
    Mas_M mas;
    mas.size = 0;
    mas.capacity = 1;
    mas.data = malloc(mas.capacity * sizeof(int));
    return mas;
}

void push_vec_a(VectorA* vec, int column, float value, int index) {
    if (vec->size == vec->capacity) {
        vec->capacity *= 2;
        vec->data = (Elem*)realloc(vec->data, vec->capacity * sizeof(Elem));
    }
 
    vec->data[vec->size].column = column;
    vec->data[vec->size].value = value;
    vec->data[vec->size].next_ind = index;
    vec->size++;   
}

void push_mas_M(Mas_M* mas, int element) {
    if (mas->size == mas->capacity) {
        mas->capacity *= 2;
        mas->data = (int*)realloc(mas->data, mas->capacity * sizeof(int));
    }
  
    mas->data[mas->size] = element;
    mas->size++;   
}

void update_vector(VectorA* vector, FILE* file) {
    int n, m;
    fscanf(file, "%d%d", &n, &m); 
    for (int i = 0; i < n; i++) {
        int nz = 0;
        int last_index = -1;
        for (int j = 0; j < m; j++) {
            float num;
            fscanf(file, "%f", &num);
            if (num != 0) {
                int column_num = j;
                float value_num = num;
                int index_num = -1;
                push_vec_a(vector, column_num, value_num, index_num);
                nz++;
                if (last_index != -1) {
                    vector->data[last_index].next_ind = vector->size - 1;
                }
                last_index = vector->size - 1;
            }
        }
        if (nz == 0 && last_index != -1) {
            vector->data[last_index].next_ind = -1;
        }
    }
    fseek(file, 0, SEEK_SET);
}

void update_mas(Mas_M* mas, VectorA* vector, FILE* file) {
    int n, m;
    fscanf(file, "%d%d", &n, &m); 
    VectorA vec_x = init_vec_a();
    for (int i = 0; i < vector->size; i++) {
        push_vec_a(&vec_x, vector->data[i].column, vector->data[i].value, vector->data[i].next_ind);
    }
    for (int i = 0; i < n; i++) {
        int ch = 0;
        float tmp = 0;
        for (int j = 0; j < m; j++) {
            float val;
            fscanf(file, "%f", &val);
            if ((val != 0) && (ch == 0)) {
                tmp = val;
                ch = 1;
            }
        }
        if (ch == 0) {
            push_mas_M(mas, -1);
        } else {
            int new_ind = -1;
            for (int k = 0; k < vec_x.size; k++) {
                if ((tmp == vec_x.data[k].value) && (vec_x.data[k].column != -1)) {
                    new_ind = k;
                    vec_x.data[k].column = -1;
                    break;
                }
            }
            if (new_ind != -1) {
                push_mas_M(mas, new_ind);
            }
        }
    }
    free_vector_a(&vec_x);
    fseek(file, 0, SEEK_SET);
}

void print_matrix(VectorA* vec, Mas_M* mas, FILE* file) {
    int n, m;
    fscanf(file, "%d%d", &n, &m); 
    for (int i = 0; i < n; i++) {
        int index_m = -1;
        if (mas->data[i] != -1) {
            index_m = mas->data[i];
        }
        int count = 0;
        for (int r = index_m; r != -1; r = vec->data[r].next_ind) {
            count++;
        }
        int xind = index_m;
        for (int j = 0; j < m; j++) {
            if (xind != -1 && vec->data[xind].column == j) {
                printf("%.1f ", vec->data[xind].value);
                xind = vec->data[xind].next_ind;
            } else {
                printf("0.0 ");
            }
        }
        printf("\n");
    }
}

void print_vec(VectorA* vec) {
    if (vec->size == 0) {
        printf("Извините, вектор пустой!\n");
    } else {
        printf("A: ");
        for (int i = 0; i < vec->size; i++) {
            printf("(%d;%lf;%d) ", vec->data[i].column, vec->data[i].value, vec->data[i].next_ind);
        }
        printf("\n");
    }
}

void print_mas(Mas_M* mas) {
    if (mas->size == 0) {
        printf("Извините, массив пустой!\n");
    } else {
        printf("M: ( ");
        for (int i = 0; i < mas->size; i++) {
            printf("%d ", mas->data[i]);
        }
        printf(")\n");
    }
}

void multiply(VectorA vec, Mas_M mas, float* vector, int size) {
    float result[size];
    for (int i = 0; i < size; i++) {
        result[i] = 0;
    }
    for (int i = 0; i < mas.size; i++) {     
        int start = mas.data[i];
        int end = (i == mas.size - 1) ? vec.size : mas.data[i+1];
        for (int j = start; j < end; j++) {
            int column = vec.data[j].column;
            float value = vec.data[j].value; 
            result[i] += value * vector[column];
        }
    }

    printf("Результат:\n");
    int count = 0;
    FILE* fout = fopen("out.txt", "w");
    fprintf(fout, "Результат умножения:\n");
    for (int i = 0; i < size; i++) {
        if (result[i] != 0.0) {
            count++;
        }
        fprintf(fout, "%lf\n", result[i]);
        printf("%lf ", result[i]);
    }
    fclose(fout);
    printf("\nКоличество ненулевых элементов: %d\n", count);
}

void free_vector_a(VectorA* vec) {
    if (vec->data) {
        free(vec->data);
    }
    vec->size = 0;
    vec->capacity = 0;
}

void free_mas(Mas_M* mas) {
    if (mas->data) {
        free(mas->data);
    }
    mas->size = 0;
    mas->capacity = 0;
}
