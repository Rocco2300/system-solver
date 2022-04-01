#include <stdio.h>
#include <stdlib.h>

typedef struct mat
{
    int n, m;
    float** data;
} Matrix;

void swap(float* a, float *b)
{
    float aux = *a;
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

void read_size(int* n, int* m)
{
    printf("Enter the number of equations(n) and variables(m): ");
    scanf("%d %d", n, m);
}

void read_matrix(Matrix* mat)
{
    printf("Enter the matrix of the system:\n");

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
        int nonZeroPivotRow = pivotRow;

        for(int i = pivotRow; i < mat->n; i++)
        {
            if(mat->data[i][pivotCol] != 0)
            {
                pivot = mat->data[i][pivotCol];
                nonZeroPivotRow = i;
                break;
            }
        }
        printf("%.2f\n", pivot);

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

int main()
{
    int n, m;
    read_size(&n, &m);
    Matrix* mat = create_matrix(n, m);
    read_matrix(mat);
    build_echalon(mat);
    print_matrix(mat);
    return 0;
}