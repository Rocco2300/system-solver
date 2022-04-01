#include "matrix_io.h"
#include "utils.h"

int main()
{
    int n, m;
    read_size(&n, &m);
    Matrix* mat = create_matrix(n, m);
    read_matrix(mat);
    int rank = get_rank(mat);
    print_matrix(mat);
    printf("%d\n", rank);
    destroy_matrix(mat);
    return 0;
}