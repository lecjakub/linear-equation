/*! @file matrix.h
 * @brief provide basic structure and arithmetic correlated with matrices
 * */
#ifndef MATRIX_H
#define MATRIX_H
#include <stdbool.h>

#define PRINT_MAT(mat) printf("\nMatrix %s:\n",#mat);\
        print_mat(mat);

struct matrix {
    float** mat;
    int rows;
    int cols;

};

struct matrix* new_mat(int rows, int cols);

bool delete_mat(struct matrix* A);

struct matrix* multiply_mat(const struct matrix* A, const struct matrix* B);

struct matrix* add_mat(const struct matrix* A, const struct matrix* B);

struct matrix* subtract_mat(const struct matrix* A, const struct matrix* B);

struct matrix* inv_mat(const struct matrix* A);

bool equal_mat(const struct matrix* A, const struct matrix* B);

void print_mat(const struct matrix* A);

#endif // MATRIX_H

