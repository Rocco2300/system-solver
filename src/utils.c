#include "utils.h"

#include "stdlib.h"
#include "math.h"

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

int get_digit_number(float number)
{
    return floor(log10(floor(number))) + 1;
}