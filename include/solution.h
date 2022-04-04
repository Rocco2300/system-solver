#ifndef SOLUTION_H
#define SOLUTION_H

#include "matrix.h"

void build_echalon(Matrix* mat);
int get_rank(Matrix* mat);
void bareiss_algorithm(Matrix* mat);
Matrix* build_solution(Matrix* echalon);

#endif