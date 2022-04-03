#include "solution.h"
#include "matrix_io.h"

#include <stdio.h>

void swap(float* a, float *b)
{
    float aux = *a;
    *a = *b;
    *b = aux;
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

void build_echalon(Matrix* mat)
{
    float pivot;
    int pivotRow = 0;
    int pivotCol = 0;

    while(pivotRow < mat->n && pivotCol < mat->m)
    {
        int nonZeroPivotRow = -1;

        for(int i = pivotRow; i < mat->n; i++)
        {
            if(mat->data[i][pivotCol] != 0)
            {
                pivot = mat->data[i][pivotCol];
                nonZeroPivotRow = i;
                break;
            }
        }

        if(nonZeroPivotRow == -1)
        {
            pivotCol++;
            continue;
        }

        swap_rows(mat, pivotRow, nonZeroPivotRow);
        for(int i = pivotRow+1; i < mat->n; i++)
        {
            float a = -mat->data[i][pivotCol] / pivot;
            for(int j = pivotCol; j < mat->m; j++)
            {
                mat->data[i][j] += a * mat->data[pivotRow][j];
            }
        }

        pivotRow ++;
        pivotCol ++;
    }
}

int get_rank(Matrix* mat)
{
    Matrix* echalon = create_matrix(mat->n, mat->m);
    copy_matrix_data(mat, echalon, 0, 0);
    build_echalon(echalon);

    int rank = echalon->n;
    for(int i = 0; i < echalon->n; i++)
    {
        int cnt = 0;
        for(int j = 0; j < echalon->m; j++)
        {
            if(echalon->data[i][j] == 0)
                cnt++;
        }

        if(cnt == echalon->m)
            rank--;
    }

    destroy_matrix(echalon);
    return rank;
}

void bareiss_algorithm(Matrix* mat)
{
    Matrix* output = create_matrix(mat->n, mat->m);

    float pivot = 1;
    int pivotRow = 0;
    int pivotCol = 0;

    while(pivotRow < mat->n && pivotCol < mat->m)
    {
        int nonZeroPivotRow = -1;

        for(int i = pivotRow; i < mat->n; i++)
        {
            if(mat->data[i][pivotCol] != 0)
            {
                nonZeroPivotRow = i;
                break;
            }
        }

        if(nonZeroPivotRow == -1)
        {
            pivotCol++;
            continue;
        }

        swap_rows(mat, pivotRow, nonZeroPivotRow);
        copy_matrix_data(mat, output, 0, 0);
        for(int i = 0; i < mat->n; i++)
        {
            if(i == pivotRow)
                continue;

            for(int j = 0; j < mat->m; j++)
            {
                output->data[i][j] = ( 
                    mat->data[pivotRow][pivotCol] * mat->data[i][j] - 
                    mat->data[i][pivotCol] * mat->data[pivotRow][j]
                );
                output->data[i][j] /= pivot;
            }
        }
        copy_matrix_data(output, mat, 0, 0);

        pivot = mat->data[pivotRow][pivotCol];
        pivotRow++;
        pivotCol++;
    }

    destroy_matrix(output);
}