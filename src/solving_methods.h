#ifndef SOLVING_METHODS_H
#define SOLVING_METHODS_H
#include "matrix.h"

struct matrix *create_test_matrix(double a1, double a2, double a3, int n);

struct matrix *create_b_vector(double f, int n);

struct matrix *jacobi(const struct matrix *A, const struct matrix *b);

struct matrix *gaussseidl(const struct matrix *A, const struct matrix *b);

void generate_LU(struct matrix* L, struct matrix* U )

#endif // SOLVING_METHODS_H
