#ifndef SOLUTION_H
#define SOLUTION_H

#include "matrix.h"

void swap(float* a, float *b);
void swap_rows(Matrix* mat, int row1, int row2);
void build_echalon(Matrix* mat);
int get_rank(Matrix* mat);

#endif