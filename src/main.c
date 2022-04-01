#include <stdio.h>
#include <stdlib.h>

int** create_matrix(int n, int m)
{
    int** mat;
    mat = calloc(n, sizeof(int*));

    if(mat == NULL)
    {
        free(mat);
        return NULL;
    }

    for (int i = 0; i < n; i++)
    {
        mat[i] = calloc(m, sizeof(int));

        if(mat[i] == NULL)
        {
            destroy_matrix(mat, n, m);
            return NULL;
        }
    }

    return mat;
}

void destroy_matrix(int** mat, int n, int m)
{
    if(mat == NULL)
        return;
    
    for(int i = 0; i < n; i++)
    {
        if(mat[i] != NULL)
            free(mat[i]);
    }

    free(mat);
}

void read_size(int* n, int* m)
{
    printf("Enter the number of equations(n) and variables(m): ");
    scanf("%d %d", n, m);
}

void read_matrix(int** mat, int n, int m)
{
    printf("Enter the matrix of the system: ");

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            scanf("%d", &mat[i][j]);
        }
    }
}

void print_matrix(int** mat, int n, int m)
{
    printf("Matrix: ");
    
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    return 0;
}