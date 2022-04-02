#include "matrix_io.h"
#include "solution.h"

int main()
{
    int n, m;
    read_size(&n, &m);
    Matrix* mat = create_matrix(n, m);
    read_matrix(mat);
    Matrix* mat2 = create_matrix(n+2, m+1);
    copy_matrix_data_to(mat, mat2, 1, 2);
    print_matrix(mat2);
    // int rank = get_rank(mat);
    // build_echalon(mat);
    // print_matrix(mat);
    // printf("%d\n", rank);
    destroy_matrix(mat2);
    destroy_matrix(mat);
    return 0;
}