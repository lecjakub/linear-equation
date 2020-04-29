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

struct matrix* copy_mat(const struct matrix* A);

struct matrix* eye(int n);

bool delete_mat(struct matrix* A);

bool set_elem_mat(struct matrix* A, int row, int col,double value);

double get_elem_mat(const struct matrix* A,int row,int col);

struct matrix* add_mat(const struct matrix* A, const struct matrix* B);

struct matrix* subtract_mat(const struct matrix* A, const struct matrix* B);

struct matrix* multiply_mat(const struct matrix* A, const struct matrix* B);

struct matrix* scal_mat(const struct matrix* A,double scal);

//forward substitution
struct matrix* fs_mat(const struct matrix* A, const struct matrix* b);

//backward substitution
struct matrix* bs_mat(const struct matrix* A, const struct matrix* b);

struct matrix* triu(const struct matrix* A);

struct matrix* tril(const struct matrix* A);

struct matrix* diag(const struct matrix* A);

double norm(const struct matrix* A);

bool equal_mat(const struct matrix* A, const struct matrix* B);

bool equal_shape_mat(const struct matrix* A, const struct matrix* B);

void print_mat(const struct matrix* A);

#endif // MATRIX_H

