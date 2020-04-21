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
    double** mat = (double**)malloc(sizeof(double*)*rows);

    //allocating each rows
    for (int i = 0; i < rows; ++i) {
        mat[i] = (double*)malloc(sizeof(double)*cols);
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
    double** mat = (double**)malloc(sizeof(double*)*rows);

    //allocating each rows
    for (size_t i = 0; i < rows; ++i) {
        mat[i] = (double *) malloc(sizeof(double) * cols);

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
    struct matrix* B = new_mat(rows,cols,0);
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
    struct matrix* A = new_mat(rows,cols,0);

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

void test_when_valid_matrices_given_multiply_correct(){

    struct matrix* A = new_mat(2,3,0);
    set_elem_mat(A,0,0,1);set_elem_mat(A,0,1,2);set_elem_mat(A,0,2,3);
    set_elem_mat(A,1,0,4);set_elem_mat(A,1,1,5);set_elem_mat(A,1,2,6);

    struct matrix* B = new_mat(3,2,0);
    set_elem_mat(B,0,0,7);set_elem_mat(B,0,1,8);
    set_elem_mat(B,1,0,9);set_elem_mat(B,1,1,10);
    set_elem_mat(B,2,0,11);set_elem_mat(B,2,1,12);

    struct matrix* expected_result = new_mat(2,2,0);
    set_elem_mat(expected_result,0,0,58);set_elem_mat(expected_result,0,1,64);
    set_elem_mat(expected_result,1,0,139);set_elem_mat(expected_result,1,1,154);

    struct matrix* result = multiply_mat(A,B);

    TEST_ASSERT_TRUE(equal_mat(result,expected_result))

    delete_mat(A);
    delete_mat(B);
    delete_mat(expected_result);
    delete_mat(result);

}

void test_fs_mat_function(void){
    struct matrix* A = new_mat(3,3,0);
    set_elem_mat(A,0,0,2);set_elem_mat(A,0,1,0);set_elem_mat(A,0,2,0);
    set_elem_mat(A,1,0,1);set_elem_mat(A,1,1,1);set_elem_mat(A,1,2,0);
    set_elem_mat(A,2,0,2);set_elem_mat(A,2,1,1);set_elem_mat(A,2,2,1);

    struct matrix* b = new_mat(3,1,0);
    set_elem_mat(b,0,0,2);
    set_elem_mat(b,1,0,3);
    set_elem_mat(b,2,0,7);

    struct matrix* expected_result = new_mat(3,1,0);
    set_elem_mat(expected_result,0,0,1);
    set_elem_mat(expected_result,1,0,2);
    set_elem_mat(expected_result,2,0,3);

    struct matrix* result = fs_mat(A,b);
//    PRINT_MAT(result)
    TEST_ASSERT_TRUE(equal_mat(result,expected_result))
    delete_mat(A);
    delete_mat(b);
    delete_mat(expected_result);
    delete_mat(result);
}

void test_triu_function(void){
    struct matrix* A = new_mat(3,3,0);
    set_elem_mat(A,0,0,2);set_elem_mat(A,0,1,4);set_elem_mat(A,0,2,7);
    set_elem_mat(A,1,0,1);set_elem_mat(A,1,1,1);set_elem_mat(A,1,2,0);
    set_elem_mat(A,2,0,2);set_elem_mat(A,2,1,1);set_elem_mat(A,2,2,1);

    struct matrix* expected_result = new_mat(3,3,0);
    set_elem_mat(expected_result,0,0,0);set_elem_mat(expected_result,0,1,4);set_elem_mat(expected_result,0,2,7);
    set_elem_mat(expected_result,1,0,0);set_elem_mat(expected_result,1,1,0);set_elem_mat(expected_result,1,2,0);
    set_elem_mat(expected_result,2,0,0);set_elem_mat(expected_result,2,1,0);set_elem_mat(expected_result,2,2,0);

    struct matrix* result = triu(A);

    TEST_ASSERT_TRUE(equal_mat(result,expected_result))

    delete_mat(A);
    delete_mat(expected_result);
    delete_mat(result);
}

void test_tril_function(){
    struct matrix* A = new_mat(3,3,0);
    set_elem_mat(A,0,0,2);set_elem_mat(A,0,1,4);set_elem_mat(A,0,2,7);
    set_elem_mat(A,1,0,1);set_elem_mat(A,1,1,1);set_elem_mat(A,1,2,0);
    set_elem_mat(A,2,0,2);set_elem_mat(A,2,1,1);set_elem_mat(A,2,2,1);

    struct matrix* expected_result = new_mat(3,3,0);
    set_elem_mat(expected_result,0,0,0);set_elem_mat(expected_result,0,1,0);set_elem_mat(expected_result,0,2,0);
    set_elem_mat(expected_result,1,0,1);set_elem_mat(expected_result,1,1,0);set_elem_mat(expected_result,1,2,0);
    set_elem_mat(expected_result,2,0,2);set_elem_mat(expected_result,2,1,1);set_elem_mat(expected_result,2,2,0);

    struct matrix* result = tril(A);

    TEST_ASSERT_TRUE(equal_mat(result,expected_result))

    delete_mat(A);
    delete_mat(expected_result);
    delete_mat(result);
}




