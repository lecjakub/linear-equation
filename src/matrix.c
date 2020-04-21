#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

struct matrix* new_mat(int rows,int cols){

    //allocating array of pointer to rows
    float** mat = (float**)malloc(sizeof(float*)*rows);


    for (int i = 0; i < rows; ++i) {
        //allocating each rows
        mat[i] = (float*)malloc(sizeof(float)*cols);

        for (size_t j = 0; j < cols; ++j) {
            //initiating value of each cell to zero
            mat[i][j] = 0;
        }
    }

    //allocating memory for new struct
    struct matrix* A =(struct matrix*)malloc(sizeof(struct matrix));

    A->rows = rows;
    A->cols = cols;
    A->mat = mat;

    return A;
}

bool delete_mat(struct matrix* A){
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

bool valid_boundaries(struct matrix* A, int row, int col){
    return row >= 0 && row < A->rows &&\
            col >= 0 && col < A->cols;
}

bool set_elem_mat(struct matrix* A, int row, int col,float value){
    if(valid_boundaries(A,row,col)){
        A->mat[row][col] = value;
        return true;
    }
    return false;
}

struct matrix* add_mat(const struct matrix* A, const struct matrix* B){
    if(equal_shape_mat(A,B)){
        struct matrix* result = new_mat(A->rows,A->cols);

        for (size_t i = 0; i < A->rows; ++i){
            for (size_t j = 0; j < A->cols; ++j){
                result->mat[i][j] = A->mat[i][j] + B->mat[i][j];
            }
        }
        return result;
    }
    return NULL;
}

struct matrix* subtract_mat(const struct matrix* A, const struct matrix* B){
    if(equal_shape_mat(A,B)){
        struct matrix* result = new_mat(A->rows,A->cols);

        for (size_t i = 0; i < A->rows; ++i){
            for (size_t j = 0; j < A->cols; ++j){
                result->mat[i][j] = A->mat[i][j] - B->mat[i][j];
            }
        }
        return result;
    }
    return NULL;
}

struct matrix* multiply_mat(const struct matrix* A, const struct matrix* B){
    if (A->cols == B->rows ) {

        //creating new matrix
        struct matrix* result = new_mat(A->rows,B->cols);

        for (size_t r = 0; r < A->rows; ++r) {
            for (size_t c = 0; c < B->cols; ++c) {
                float total=0;
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
struct matrix* fs_mat(const struct matrix* A, const struct matrix* b){
    struct matrix* result = new_mat(A->rows,1);

    for (size_t i = 0; i < A->rows; ++i) {
        float leftside = 0;
        for (size_t j = 0; j < i; ++j) {
            leftside += A->mat[i][j] * result->mat[j][0];
        }
        result->mat[i][0] = (b->mat[i][0] - leftside)/A->mat[i][i];
    }
    return result;
}

struct matrix* triu(const struct matrix* A){
    struct matrix* result = new_mat(A->rows, A->cols);

    for (size_t i = 0; i < A->cols; ++i) {
        for (size_t j = 0; j < i; ++j) {
            result->mat[j][i] = A->mat[j][i];
        }
    }

    return result;
}

struct matrix* tril(const struct matrix* A){
    struct matrix* result = new_mat(A->rows, A->cols);

    for (size_t i = 0; i < A->rows; ++i) {
        for (size_t j = 0; j < i; ++j) {
            result->mat[i][j] = A->mat[i][j];
        }
    }
    return result;
}
struct matrix* diag(const struct matrix* A){
    struct matrix* result = new_mat(A->rows, A->cols);

    for (size_t i = 0; i < A->rows; ++i) {
        result->mat[i][i] = A->mat[i][i];
    }
    return result;
}

bool equal_mat(const struct matrix* A, const struct matrix* B){
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

bool equal_shape_mat(const struct matrix* A, const struct matrix* B){
    return A->rows == B->rows && A->cols == B->cols;
}

void print_mat(const struct matrix* A){
    printf("\n[rows:%d, cols:%d]\n",A->rows,A->cols);
    printf("values:\n");
    for (size_t i = 0; i < A->rows; ++i) {
        for (size_t j = 0; j < A->cols; ++j) {
            printf("%f ",A->mat[i][j]);
        }
        printf("\n");
    }
}
