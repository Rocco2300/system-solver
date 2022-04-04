#ifndef MATRIX_IO_H
#define MATRIX_IO_H

#include "matrix.h"

void read_size(int* n, int* m);
void read_matrix(Matrix* mat);
void print_matrix(Matrix* mat);
void print_solution(Matrix* mat);

#endif