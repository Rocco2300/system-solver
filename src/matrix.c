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

void copy_matrix_data(Matrix* from, Matrix* to, int to_x, int to_y)
{
    if(from->n > to->n || from->m > to->m)
        return;
    
    if(to_x < 0 || to_x >= to->m || to_y < 0 || to_y >= to->n)
        return;

    for(int i = 0; i < from->n; i++)
    {
        for(int j = 0; j < from->m; j++)
        {
            to->data[i + to_y][j + to_x] = from->data[i][j];
        }
    }
}
