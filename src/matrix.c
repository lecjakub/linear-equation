#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct matrix *new_mat(int rows, int cols, double init_value) {

    //allocating array of pointer to rows
    double **mat = (double **) malloc(sizeof(double *) * rows);


    for (int i = 0; i < rows; ++i) {
        //allocating each rows
        mat[i] = (double *) malloc(sizeof(double) * cols);

        for (size_t j = 0; j < cols; ++j) {
            //initiating value of each cell to zero
            mat[i][j] = init_value;
        }
    }

    //allocating memory for new struct
    struct matrix *A = (struct matrix *) malloc(sizeof(struct matrix));

    A->rows = rows;
    A->cols = cols;
    A->mat = mat;

    return A;
}

bool delete_mat(struct matrix *A) {
    for (size_t i = 0; i < A->rows; ++i) {
//        deallocate every row
        free(A->mat[i]);
    }
    //deallocate array of rows
    free(A->mat);

    //deallocate whole struct
    free(A);
    return true;
}

struct matrix* copy_mat(const struct matrix* A){
    struct matrix* result = new_mat(A->rows, A->cols,0);

    for (size_t i = 0; i < A->rows; ++i) {
        for (size_t j = 0; j < A->cols; ++j) {
            result->mat[i][j] = A->mat[i][j];
        }
    }
    return result;
}

struct matrix* eye(int n){
    struct matrix* result = new_mat(n,n,0);
    for (size_t i = 0; i < n; ++i) {
        result->mat[i][i] = 1;
    }
    return result;
}

bool valid_boundaries(const struct matrix *A, int row, int col) {
    return row >= 0 && row < A->rows && \
            col >= 0 && col < A->cols;
}

bool set_elem_mat(struct matrix *A, int row, int col, double value) {
    if (valid_boundaries(A, row, col)) {
        A->mat[row][col] = value;
        return true;
    }
    return false;
}

double get_elem_mat(const struct matrix* A,int row,int col){
    if(valid_boundaries(A,row,col)){
        return A->mat[row][col];
    }
    return 0;
}


struct matrix *add_mat(const struct matrix *A, const struct matrix *B) {
    if (equal_shape_mat(A, B)) {
        struct matrix *result = new_mat(A->rows, A->cols,0);

        for (size_t i = 0; i < A->rows; ++i) {
            for (size_t j = 0; j < A->cols; ++j) {
                result->mat[i][j] = A->mat[i][j] + B->mat[i][j];
            }
        }
        return result;
    }
    return NULL;
}

struct matrix *subtract_mat(const struct matrix *A, const struct matrix *B) {
    if (equal_shape_mat(A, B)) {
        struct matrix *result = new_mat(A->rows, A->cols,0);

        for (size_t i = 0; i < A->rows; ++i) {
            for (size_t j = 0; j < A->cols; ++j) {
                result->mat[i][j] = A->mat[i][j] - B->mat[i][j];
            }
        }
        return result;
    }
    return NULL;
}

struct matrix *multiply_mat(const struct matrix *A, const struct matrix *B) {
    if (A->cols == B->rows) {

        //creating new matrix
        struct matrix *result = new_mat(A->rows, B->cols,0);

        for (size_t r = 0; r < A->rows; ++r) {
            for (size_t c = 0; c < B->cols; ++c) {
                double total = 0;
                for (size_t i = 0; i < B->rows; ++i) {
                    total += A->mat[r][i] * B->mat[i][c];
                }
                result->mat[r][c] = total;
            }
        }
        return result;
    }
    return NULL;
}

struct matrix *fs_mat(const struct matrix *A, const struct matrix *b) {
    struct matrix *result = new_mat(A->rows, 1,0);

    for (size_t i = 0; i < A->rows; ++i) {
        double leftside = 0;
        for (size_t j = 0; j < i; ++j) {
            leftside += A->mat[i][j] * result->mat[j][0];
        }
        result->mat[i][0] = (b->mat[i][0] - leftside) / A->mat[i][i];
    }
    return result;
}

struct matrix *triu(const struct matrix *A) {
    struct matrix *result = new_mat(A->rows, A->cols,0);

    for (size_t i = 0; i < A->cols; ++i) {
        for (size_t j = 0; j < i; ++j) {
            result->mat[j][i] = A->mat[j][i];
        }
    }

    return result;
}

struct matrix *tril(const struct matrix *A) {
    struct matrix *result = new_mat(A->rows, A->cols,0);

    for (size_t i = 0; i < A->rows; ++i) {
        for (size_t j = 0; j < i; ++j) {
            result->mat[i][j] = A->mat[i][j];
        }
    }
    return result;
}

struct matrix *diag(const struct matrix *A) {
    struct matrix *result = new_mat(A->rows, A->cols,0);

    for (size_t i = 0; i < A->rows; ++i) {
        result->mat[i][i] = A->mat[i][i];
    }
    return result;
}

struct matrix *scal_mat(const struct matrix *A, double scal) {
    struct matrix *result = new_mat(A->rows, A->cols,0);
    for (size_t i = 0; i < A->rows; ++i) {
        for (size_t j = 0; j < A->cols; ++j) {
            result->mat[i][j] = A->mat[i][j] * scal;
        }
    }
    return result;
}

double norm(const struct matrix *A) {
    double sum = 0;
    for (size_t i = 0; i < A->rows; ++i) {
        sum += pow(A->mat[i][0], 2);
    }
    return sqrt(sum);
}

bool equal_mat(const struct matrix *A, const struct matrix *B) {
    if (A->rows == B->rows) {
        if (A->cols == B->cols) {
            for (size_t i = 0; i < A->rows; ++i) {
                for (size_t j = 0; j < A->cols; ++j) {
                    if (A->mat[i][j] != B->mat[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }
    }
    return false;
}

bool equal_shape_mat(const struct matrix *A, const struct matrix *B) {
    return A->rows == B->rows && A->cols == B->cols;
}

void print_mat(const struct matrix *A) {
    printf("\n[rows:%d, cols:%d]\n", A->rows, A->cols);
    printf("values:\n");
    for (size_t i = 0; i < A->rows; ++i) {
        for (size_t j = 0; j < A->cols; ++j) {
            printf("%f ", A->mat[i][j]);
        }
        printf("\n");
    }
}
