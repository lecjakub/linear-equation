/*! @file matrix.h
 * @brief provide basic structure and arithmetic correlated with matrices
 * */
#ifndef MATRIX_H
#define MATRIX_H
#include <stdbool.h>

#define PRINT_MAT(mat) printf("\nMatrix %s:\n",#mat);\
        print_mat(mat);

struct matrix {
    double** mat;
    int rows;
    int cols;

};

struct matrix* new_mat(int rows, int cols,double init_value);

bool delete_mat(struct matrix* A);

bool set_elem_mat(struct matrix* A, int row, int col,double value);

struct matrix* add_mat(const struct matrix* A, const struct matrix* B);

struct matrix* subtract_mat(const struct matrix* A, const struct matrix* B);

struct matrix* multiply_mat(const struct matrix* A, const struct matrix* B);
struct matrix* scal_mat(const struct matrix* A,double scal);

struct matrix* fs_mat(const struct matrix* A, const struct matrix* B);

struct matrix* triu(const struct matrix* A);
struct matrix* tril(const struct matrix* A);
struct matrix* diag(const struct matrix* A);
double norm(const struct matrix* A);

bool equal_mat(const struct matrix* A, const struct matrix* B);

bool equal_shape_mat(const struct matrix* A, const struct matrix* B);

void print_mat(const struct matrix* A);

#endif // MATRIX_H

