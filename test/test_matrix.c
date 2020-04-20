#include "unity.h"

#include "matrix.h"
#include <stdlib.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_when_comparing_same_matrix_return_true(void){
    //arrange
    int rows = 5;
    int cols = 4;
    //allocating array of pointer to rows
    float** mat = (float**)malloc(sizeof(float*)*rows);

    //allocating each rows
    for (int i = 0; i < rows; ++i) {
        mat[i] = (float*)malloc(sizeof(float)*cols);
    }

    struct matrix A = {
            .rows = rows,
            .cols = cols,
            .mat = mat
    };

    //assertions
    TEST_ASSERT_TRUE(equal_mat(&A,&A));
}

void test_when_create_new_matrix_return_valid_matrix(void){
    //arrange
    int rows = 5;
    int cols = 4;
    //allocating array of pointer to rows
    float** mat = (float**)malloc(sizeof(float*)*rows);

    //allocating each rows
    for (size_t i = 0; i < rows; ++i) {
        mat[i] = (float*)malloc(sizeof(float)*cols);

        for (size_t j = 0; j < cols; ++j) {
            //initiating value of each cell to zero
            mat[i][j] = 0;
        }
    }



    struct matrix A = {
            .rows = rows,
            .cols = cols,
            .mat = mat
    };

    //tested function
    struct matrix* B = new_mat(rows,cols);
//    PRINT_MAT(B);
//    PRINT_MAT(&A)
    //assertions
    TEST_ASSERT_TRUE(equal_mat(&A,B))
    delete_mat(B);

    //cleaning
    for (size_t k = 0; k < rows; ++k) {
        free(mat[k]);
    }
    free(mat);

}

void test_when_create_new_matrix_all_cells_are_zeros(void)
{
    int rows = 5;
    int cols = 4;
    bool zeros = true;
    struct matrix* A = new_mat(rows,cols);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (A->mat[i][j] != 0) {
                TEST_FAIL();
            }
        }
    }
    delete_mat(A);
    TEST_PASS();

}


