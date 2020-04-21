/*! @file core.c
 * @brief application core
 * this file is application core
*/
#include "core.h"
#include <stdio.h>
#include <stdlib.h>
#include <libconfig.h>
#include <math.h>
#include <time.h>
#include "argparser.h"
#include "matrix.h"
#include "solving_methods.c"

#define A1 12
#define A2 -1
#define A3 -1
#define F 5
#define MAT_SIZE 1000


int main(int argc, char **argv) {

    argparser_t *argpar;
    //initiating parser
    argpar = argparser_init(&argc, argv);

    //generating configuration
    config_t *config;
    config = argparser_parse_args(argpar);

    struct matrix *A = create_test_matrix(A1, A2, A3, MAT_SIZE);
    struct matrix *b = create_b_vector(F, MAT_SIZE);

    struct matrix *xjacobi = jacobi(A, b);
    struct matrix *xgaussseild = gaussseidl(A, b);


//    for (size_t i = 0; i < MAT_SIZE; ++i) {
//        printf("jacobi: %f ",xjacobi->mat[i][0]);
//        printf("gauss-seidl: %f\n",xgaussseild->mat[i][0]);
//    }
}


struct matrix *factorLU(const struct matrix *A, const struct matrix *b) {
    struct matrix *U = copy_mat(A);
    struct matrix *L = eye(A->rows);
    int m = A->rows;
    PRINT_MAT(L)
    PRINT_MAT(U)
    for (int k = 0; k < m - 1; ++k) {
        for (int j = k + 1; j < m; ++j) {
            L->mat[j][k] = (U->mat[j][k]) / (U->mat[k][k]);
//            set_elem_mat(L, j, k, get_elem_mat(U, j, k) / get_elem_mat(U, k, k));

            for (int i = k; i < m; ++i) {
                U->mat[j][i] = U->mat[j][i] - (L->mat[j][k]) * (U->mat[k][i]);
//                set_elem_mat(U, j, i, get_elem_mat(U, j, i) - get_elem_mat(L,j,k)*get_elem_mat(U, k, i));
            }
            PRINT_MAT(L)
            PRINT_MAT(U)
        }
    }
    PRINT_MAT(L)
    PRINT_MAT(U)
    return A;

}