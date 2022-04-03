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
    printf("Enter the elements:\n");

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

void destroy_sol(char** arr, int size)
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

char** create_sol(int size)
{
    char** sol = malloc(size * sizeof(char*));

    if(sol == NULL)
        return NULL;

    for(int i = 0; i < size; i++)
    {
        sol[i] = malloc(31 * sizeof(char));

        if(sol[i] == NULL)
        {
            destroy_sol(sol, size);
            return NULL;
        }

        sol[i][0] = '\0';
    }

    return sol;
}


// This function takes a matrix that
// has been made in echalon by bareiss
// algorithm and prints the solution
void print_solution(Matrix* mat)
{
    char** sol = create_sol(mat->m - 1);

    for(int var = mat->m - 2; var >= 0; var--)
    {
        strcat(sol[var], "x");
        char sub_idx[2];
        itoa(var+1, sub_idx, 10); 
        strcat(sol[var], sub_idx);
        strcat(sol[var], " = ");

        for(int eq = mat->n - 1; eq >= 0; eq--)
        {
            if(mat->data[eq][var] == 0)
                continue;
            
            if(var >= 1 && mat->data[eq][var-1] != 0)
            {
                strcat(sol[var], "x");
                strcat(sol[var], sub_idx);
            }
            else 
            {
                int divisor = mat->data[eq][var];
                for(int i = mat->m - 1; i > var; i--)
                {
                    if(mat->data[eq][i] == 0)
                        continue;

                    char buf[100];
                    float coeff = mat->data[eq][i] / divisor;
                    char op[4] = "\0";
                    char variable[4] = "\0";
                    if(i != mat->m - 1)
                    {
                        coeff *= -1;
                        if(coeff < 0)
                        {
                            strcat(op, " - ");
                            coeff *= -1;
                        }
                        else 
                            strcat(op, " + ");

                        if(coeff != 1)
                            strcat(variable, "*x");
                        else
                            strcat(variable, "x");
                        char sub_idx[2];
                        itoa(i+1, sub_idx, 10); 
                        strcat(variable, sub_idx);
                    }
                    
                    strcat(sol[var], op);
                    if(coeff != 1)
                    {
                        sprintf_s(buf, sizeof(buf), "%.2f", coeff);
                        strcat(sol[var], buf);
                    }
                    strcat(sol[var], variable);
                }
            }
            break;
        }
    }

    for(int i = 0; i < mat->m - 1; i++)
    {
        printf("%s\n", sol[i]);
    }

    destroy_sol(sol, mat->m - 1);
}