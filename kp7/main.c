#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "spacematrix.h"

int main(int argc, char* argv[])
{
    FILE *in = fopen(argv[1], "r");
    if (!in) {
        printf("I/O Error: can't open file.\n");
        exit(1);
    }
    

    VectorA vec = init_vec_a();
    Mas_M mas;
    fill_mas_vector(&vec, &mas, in);
    int nx, mx;
    fscanf(in, "%d%d", &nx, &mx);
    fseek(in, 0, SEEK_SET);
    
    printf("Матрица в обычном виде:\n");
    print_matrix(&vec, &mas, in);
               
    printf("Матрица согласно схеме представления:\n");
    print_vec(&vec);
    print_mas(&mas);

    printf("Умножение матрицы на вектор-столбец:\n");
    printf("Введите количество элементов столбца:\n");
    int amount;
    scanf("%d", &amount);
    if (amount != mx) {
        printf("Некорректное количество элементов!\n");
    } else {
        printf("Введите значения элементов столбца:\n");
        float v[amount];
        for (int i = 0; i < amount; i++) {
            scanf("%f", &v[i]);
        }
        multiply(&vec, &mas, v, nx);
    }
    free_vector_a(&vec);
    free_mas(&mas);
    fclose(in);
    return 0;
}

