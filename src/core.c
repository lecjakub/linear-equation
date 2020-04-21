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

#define A1 12
#define A2 -1
#define A3 -1
#define F 5
#define MAT_SIZE 1000

struct matrix *create_test_matrix(double a1, double a2, double a3, int n);
struct matrix* create_b_vector(double f, int n);
struct matrix* jacobi(const struct matrix* A, const struct matrix* b);
struct matrix* gaussseidl(const struct matrix* A, const struct matrix* b);

int main(int argc, char **argv) {

    argparser_t *argpar;
    //initiating parser
    argpar = argparser_init(&argc, argv);

    //generating configuration
    config_t *config;
    config = argparser_parse_args(argpar);

    struct matrix *A = create_test_matrix(A1, A2, A3, MAT_SIZE);
    struct matrix *b = create_b_vector(F, MAT_SIZE);

    struct matrix* xjacobi = jacobi(A,b);
    struct matrix* xgaussseild = gaussseidl(A,b);

    for (size_t i = 0; i < MAT_SIZE; ++i) {
        printf("jacobi: %f ",xjacobi->mat[i][0]);
        printf("gauss-seidl: %f\n",xgaussseild->mat[i][0]);
    }
}

struct matrix *create_test_matrix(double a1, double a2, double a3, int n) {
    struct matrix *result = new_mat(n, n,0);

    for (int i = 0; i < n; ++i) {
        set_elem_mat(result, i, i, a1);

        set_elem_mat(result, i, i + 1, a2);
        set_elem_mat(result, i + 1, i, a2);

        set_elem_mat(result, i, i + 2, a3);
        set_elem_mat(result, i + 2, i, a3);
    }
    return result;
}

struct matrix* create_b_vector(double f, int n) {
    struct matrix *b = new_mat(n, 1,0);
    for (int i = 0; i < n; ++i) {
        set_elem_mat(b, i, 0, sin(i * (f + 1)));
    }
    return b;
}
struct matrix* jacobi(const struct matrix* A, const struct matrix* b){
    //lower matrix triangle
    struct matrix* L = tril(A);
    //upper matrix triangle
    struct matrix* U = triu(A);
    //L + U
    struct matrix* LU = add_mat(L,U);
    //diagonal matrix
    struct matrix* D = diag(A);
    //-D
    struct matrix* mD = scal_mat(D,-1);
    //D\b
    struct matrix* Db = fs_mat(D,b);

    //vector of variables
    struct matrix* x = new_mat(A->rows,1,1);

    double res_norm = 0;
    clock_t start,end;
    start = clock();
    //logic
    do{
        //(L + U) * x
        struct matrix*LUx = multiply_mat(LU,x);

        //-D \ (L + U) * x;
        struct matrix* mDLUx = fs_mat(mD,LUx);

        struct matrix* new_x = add_mat(mDLUx,Db);

        struct matrix* Ax = multiply_mat(A,new_x);
        struct matrix* res = subtract_mat(Ax,b);
        res_norm = norm(res);

        delete_mat(LUx);
        delete_mat(mDLUx);
        delete_mat(x);
        delete_mat(Ax);
        delete_mat(res);

        x = new_x;
    }while(res_norm > 1e-9);
    end = clock();
    printf("czas jacobi: %f\n",(double)((end-start))/CLOCKS_PER_SEC);

    delete_mat(L);
    delete_mat(U);
    delete_mat(LU);
    delete_mat(D);
    delete_mat(mD);
    delete_mat(Db);

    return x;
}

struct matrix* gaussseidl(const struct matrix* A, const struct matrix* b){
    //lower matrix triangle
    struct matrix* L = tril(A);
    //upper matrix triangle
    struct matrix* U = triu(A);
    //diagonal matrix
    struct matrix* D = diag(A);
    //D+L
    struct matrix* DL = add_mat(D,L);
    //-(D+L)
    struct matrix* mDL = scal_mat(DL,-1);
    //(D+L)\b
    struct matrix* DLb = fs_mat(DL,b);

    //vector of variables
    struct matrix* x = new_mat(A->rows,1,1);

    double res_norm = 0;
    clock_t start,end;
    start = clock();
    do{
        //U*x
        struct matrix* Ux = multiply_mat(U,x);
        //-(D+L)\(U*x)
        struct matrix* mDLUx = fs_mat(mDL,Ux);

        struct matrix* new_x = add_mat(mDLUx,DLb);

        struct matrix* Ax = multiply_mat(A,new_x);
        struct matrix* res = subtract_mat(Ax,b);
        res_norm = norm(res);

        delete_mat(Ux);
        delete_mat(mDLUx);
        delete_mat(x);
        delete_mat(Ax);
        delete_mat(res);

        x = new_x;
    }while(res_norm > 1e-9);

    end = clock();
    printf("czas gauss-seidl: %f\n",(double)((end-start))/CLOCKS_PER_SEC);

    delete_mat(L);
    delete_mat(U);
    delete_mat(D);
    delete_mat(DL);
    delete_mat(mDL);
    delete_mat(DLb);
    return x;
}