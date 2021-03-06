#ifndef MATRIX_H
#define MATRIX_H

typedef struct mat
{
    int n, m;
    float** data;
} Matrix;

Matrix* create_matrix(int n, int m);
void destroy_matrix(Matrix* mat);
void copy_matrix_data(Matrix* from, Matrix* to, int to_x, int to_y);

#endif