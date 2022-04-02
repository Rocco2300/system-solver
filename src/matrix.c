#include "matrix.h"

#include <stdlib.h>

Matrix* create_matrix(int n, int m)
{
    Matrix* mat = malloc(sizeof(Matrix*));
    if(mat == NULL)
        return NULL;

    mat->n = n;
    mat->m = m;
    mat->data = calloc(n, sizeof(float*));

    if(mat->data == NULL)
    {
        free(mat);
        return NULL;
    }

    for (int i = 0; i < n; i++)
    {
        mat->data[i] = calloc(m, sizeof(float));

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

void copy_data(Matrix* mat1, Matrix* mat2)
{
    if(mat1->n > mat2->n || mat1->m > mat2->m)
        return;
    
    for(int i = 0; i < mat1->n; i++)
    {
        for(int j = 0; j < mat1->m; j++)
        {
            mat2->data[i][j] = mat1->data[i][j];
        }
    }
}