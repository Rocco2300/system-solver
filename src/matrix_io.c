#include "matrix_io.h"

#include <stdio.h>

void read_size(int* n, int* m)
{
    printf("Enter the number of equations(n) and variables(m): ");
    scanf("%d %d", n, m);
}

void read_matrix(Matrix* mat)
{
    printf("Enter the elements:\n");

    for(int i = 0; i < mat->n; i++)
    {
        for(int j = 0; j < mat->m; j++)
        {
            scanf("%f", &mat->data[i][j]);
        }
    }
}

void print_matrix(Matrix* mat)
{
    printf("Matrix:\n");
    
    for(int i = 0; i < mat->n; i++)
    {
        for(int j = 0; j < mat->m; j++)
        {
            printf("%.2f ", mat->data[i][j]);
        }
        printf("\n");
    }
}

// This function takes a matrix that
// has been made in echalon by bareiss
// algorithm and prints the solution
void print_solution(Matrix* mat)
{
    
}