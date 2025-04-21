#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

double** alloc_matrix(int rows, int cols) {
    double** mat = malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++)
        mat[i] = calloc(cols, sizeof(double));
    return mat;
}

void free_matrix(double** mat, int rows) {
    for (int i = 0; i < rows; i++)
        free(mat[i]);
    free(mat);
}

void print_matrix(double** mat, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%lf ", mat[i][j]);
        printf("\n");
    }
}

void matrix_transpose(double** src, double** dst, int rows, int cols) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            dst[j][i] = src[i][j];
}

void matrix_multiply(double** A, int A_rows, int A_cols, double** B, int B_rows, int B_cols, double** result) {
    for (int i = 0; i < A_rows; i++) {
        for (int j = 0; j < B_cols; j++) {
            result[i][j] = 0;
            for (int k = 0; k < A_cols; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matrix_subtract(double** A, double** B, double** result, int rows, int cols) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result[i][j] = A[i][j] - B[i][j];
}
