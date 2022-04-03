#include "matrix_io.h"
#include "solution.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, m;
    read_size(&n, &m);
    Matrix* coef_mat = create_matrix(n, m);
    printf("Enter the coefficient matrix:\n");
    read_matrix(coef_mat);
    Matrix* free_mat = create_matrix(n, 1);
    printf("Enter the free term vector:\n");
    read_matrix(free_mat);
    Matrix* aug_mat = create_matrix(n, m+1);
    copy_matrix_data(coef_mat, aug_mat, 0, 0);
    copy_matrix_data(free_mat, aug_mat, m, 0);

    int coef_rank = get_rank(coef_mat);
    int aug_rank = get_rank(aug_mat);

    if(coef_rank != aug_rank)
    {
        printf("The system of equations is inconsistent. \n");
        return EXIT_SUCCESS;
    }
    
    if(coef_rank < m)
        printf("The equation system is undetermined and consistent. \n");
    else
        printf("The equation system is determined and consistent. \n");

    bareiss_algorithm(aug_mat);
    print_solution(aug_mat);
    destroy_matrix(coef_mat);
    destroy_matrix(free_mat);
    destroy_matrix(aug_mat);
    return EXIT_SUCCESS;
}