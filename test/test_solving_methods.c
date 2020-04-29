#include "unity.h"
#include <stdlib.h>
#include <time.h>

#include "solving_methods.h"
#include "matrix.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_generate_LU(void){
    struct matrix* A = new_mat(4,4,0);

    srand((unsigned) time(NULL));

    for (size_t r = 0; r < A->rows; ++r) {
        for (size_t c = 0; c < A->cols; ++c) {
            set_elem_mat(A,r,c,rand());
        }
    }

    struct matrix* L = eye(A->rows);
    struct matrix* U = copy_mat(A);

    generate_LU(L,U);
    struct matrix* LU = multiply_mat(L,U);
    struct matrix* ALU = subtract_mat(A,LU);

    PRINT_MAT(L)
    PRINT_MAT(U)
    PRINT_MAT(A)
    PRINT_MAT(LU)
    PRINT_MAT(ALU)

    TEST_ASSERT_TRUE(equal_mat(ALU,new_mat(4,4,0)));

}
