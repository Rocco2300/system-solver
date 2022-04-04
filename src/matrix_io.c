#include "matrix_io.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_size(int* n, int* m)
{
    printf("Enter the number of equations(n) and variables(m): ");
    scanf("%d %d", n, m);
}

void read_matrix(Matrix* mat)
{

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

void destroy_str_arr(char** arr, int size)
{
    if(arr == NULL)
        return;
    
    for(int i = 0; i < size; i++)
    {
        if(arr[i] != NULL)
            free(arr[i]);
    }
    free(arr);
}

char** create_str_arr(int size)
{
    char** sol = malloc(size * sizeof(char*));

    if(sol == NULL)
        return NULL;

    for(int i = 0; i < size; i++)
    {
        sol[i] = malloc(31 * sizeof(char));

        if(sol[i] == NULL)
        {
            destroy_str_arr(sol, size);
            return NULL;
        }

        sol[i][0] = '\0';
    }

    return sol;
}

/*
Concatenates to the string the indexed variable x
*/
void concat_xVar(char* str, int index)
{
    strcat(str, "x");
    char sub_idx[2];
    itoa(index, sub_idx, 10); 
    strcat(str, sub_idx);
}

/*
This function takes a solution matrix
and prints off the solution in a human
readable way
*/
void print_solution(Matrix* sol_coeff)
{
    char** sol = create_str_arr(sol_coeff->m - 1);

    for(int row = sol_coeff->n - 1; row >= 0; row--)
    {
        int cnt = 0;
        concat_xVar(sol[row], row+1);
        strcat(sol[row], " = ");

        for(int col = 0; col < sol_coeff->m; col++)
        {
            if(sol_coeff->data[row][col] == 0)
            {
                cnt++;
                continue;
            }
        
            // If this isn't the first term, add the sign in front
            if(sol_coeff->data[row][col-1] != 0 && col > 0 && sol_coeff->data[row][col] < 0)
            {
                strcat(sol[row], " - ");
                sol_coeff->data[row][col] *= -1;
            }
            else if(sol_coeff->data[row][col-1] && col > 0 && sol_coeff->data[row][col] > 0)
                strcat(sol[row], " + ");

            char buf[100];
            sprintf_s(buf, sizeof(buf), "%.2f", sol_coeff->data[row][col]);
            strcat(sol[row], buf);
            if(col != sol_coeff->m - 1)

            if(col != sol_coeff->m - 1)
            {
                strcat(sol[row], "*");
                concat_xVar(sol[row], col+1);
            }
        }

        if(cnt == sol_coeff->m)
            concat_xVar(sol[row], row+1);
    }

    printf("The solution is:\n");
    for(int i = 0; i < sol_coeff->m - 1; i++)
    {
        printf("%s\n", sol[i]);
    }

    destroy_str_arr(sol, sol_coeff->m - 1);
}