#include <stdio.h>
#include <stdlib.h>

typedef struct mat
{
    int n, m;
    int** data;
} Matrix;

void swap(int* a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

void destroy_matrix(Matrix* mat);

Matrix* create_matrix(int n, int m)
{
    Matrix* mat = malloc(sizeof(Matrix*));
    if(mat == NULL)
        return NULL;

    mat->n = n;
    mat->m = m;
    mat->data = calloc(n, sizeof(int*));

    if(mat->data == NULL)
    {
        free(mat);
        return NULL;
    }

    for (int i = 0; i < n; i++)
    {
        mat->data[i] = calloc(m, sizeof(int));

        if(mat->data[i] == NULL)
        {
            destroy_matrix(mat);
            return NULL;
        }
    }

    return mat;
}

void destroy_matrix(Matrix* mat)
{
    if(mat == NULL)
        return;
    
    for(int i = 0; i < mat->n; i++)
    {
        if(mat->data[i] != NULL)
            free(mat->data[i]);
    }

    free(mat->data);
}

void read_size(int* n, int* m)
{
    printf("Enter the number of equations(n) and variables(m): ");
    scanf("%d %d", n, m);
}

void read_matrix(Matrix* mat)
{
    printf("Enter the matrix of the system:\n");

    for(int i = 0; i < mat->m; i++)
    {
        for(int j = 0; j < mat->n; j++)
        {
            scanf("%d", &mat->data[i][j]);
        }
    }
}

void print_matrix(Matrix* mat)
{
    printf("Matrix:\n");
    
    for(int i = 0; i < mat->m; i++)
    {
        for(int j = 0; j < mat->n; j++)
        {
            printf("%d ", mat->data[i][j]);
        }
        printf("\n");
    }
}

void swap_rows(Matrix* mat, int row1, int row2)
{
    if(row1 >= mat->n || row2 >= mat->n || row1 < 0 || row2 < 0)
        return;

    for(int i = 0; i < mat->m; i++)
    {
        swap(&mat->data[row1][i], &mat->data[row2][i]);
    }
}

// void get_echalon(int** mat, int n, int m)
// {

// }

int main()
{
    int n, m;
    read_size(&n, &m);
    Matrix* mat = create_matrix(n, m);
    read_matrix(mat);
    swap_rows(mat, 0, 1);
    print_matrix(mat);
    return 0;
}