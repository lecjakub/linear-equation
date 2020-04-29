/*! @file core.c
 * @brief application core
 * this file is application core
*/
#include <stdio.h>
#include "solving_methods.h"

#define A1 9
#define A2 -1
#define A3 -1
#define F 5
#define MAT_SIZE 994

void taskB();
void taskC();
void taskD();
void taskE();

int main(int argc, char **argv) {
    taskB();
    taskC();
    taskD();
    taskE();
    return 0;
}

void taskB(){
    printf("\n\nTASK B:\n");
    //taskA
    struct matrix *A = create_test_matrix(A1, A2, A3, MAT_SIZE);
    struct matrix *b = create_b_vector(F, MAT_SIZE);

    //taskB
    struct matrix *xjacobi = jacobi(A, b);
    struct matrix *xgaussseild = gaussseidl(A, b);


//    for (size_t i = 0; i < MAT_SIZE; ++i) {
//    printf("jacobi: %f | ",xjacobi->mat[i][0]);
//    printf("gauss-seidl: %f | ",xgaussseild->mat[i][0]);
//    printf("factorLU: %f\n",xfactorLU->mat[i][0]);

    delete_mat(A);
    delete_mat(b);
    delete_mat(xjacobi);
    delete_mat(xgaussseild);
}

void taskC(){
    printf("\n\nTASK C:\n");
    struct matrix *A = create_test_matrix(3, -1, -1, MAT_SIZE);
    struct matrix *b = create_b_vector(F, MAT_SIZE);

    struct matrix *xjacobi = jacobi(A, b);
    if (xjacobi == NULL){
        printf("jacobi method is not coincident\n");
    }
    struct matrix *xgaussseild = gaussseidl(A, b);
    if(xgaussseild == NULL){
        printf("gausseidl method is not coincident\n");
    }

    delete_mat(A);
    delete_mat(b);
    if (xjacobi != NULL)delete_mat(xjacobi);
    if(xgaussseild != NULL)delete_mat(xgaussseild);
}

void taskD(){
    printf("\n\nTASK D:\n");
    struct matrix *A = create_test_matrix(3, -1, -1, MAT_SIZE);
    struct matrix *b = create_b_vector(F, MAT_SIZE);

    struct matrix *xfactorLU = factorLU(A,b);

    struct matrix* Ax = multiply_mat(A,xfactorLU);
    struct matrix *res = subtract_mat(Ax, b);
    double res_norm = norm(res);
    printf("Residuum norm for LU factorization: %e",res_norm);

    delete_mat(A);
    delete_mat(b);
    delete_mat(xfactorLU);
    delete_mat(Ax);
    delete_mat(res);
}

void taskE(){
    printf("\n\nTASK E:\n");

    int N[] ={100,500,1000,2000,3000,6000};
    int n_num = sizeof(N)/sizeof(N[0]);
    for (int i = 0; i < n_num; ++i){
        printf("\nN: %d\n",N[i]);
        struct matrix *A = create_test_matrix(A1, A2, A3, N[i]);
        struct matrix *b = create_b_vector(F, N[i]);

        struct matrix *xjacobi = jacobi(A, b);
        if (xjacobi == NULL){
            printf("jacobi method is not coincident\n");
        }
        struct matrix *xgaussseild = gaussseidl(A, b);
        if(xgaussseild == NULL){
            printf("gaussseidl method is not coincident\n");
        }

        struct matrix *xfactorLU = factorLU(A,b);

        delete_mat(A);
        delete_mat(b);
        if (xjacobi != NULL)delete_mat(xjacobi);
        if(xgaussseild != NULL)delete_mat(xgaussseild);
        delete_mat(xfactorLU);
    }
}
