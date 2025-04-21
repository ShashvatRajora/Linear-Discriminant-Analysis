#ifndef MATRIX_H
#define MATRIX_H

double** alloc_matrix(int rows, int cols);
void free_matrix(double** mat, int rows);
void print_matrix(double** mat, int rows, int cols);
void matrix_transpose(double** src, double** dst, int rows, int cols);
void matrix_multiply(double** A, int A_rows, int A_cols, double** B, int B_rows, int B_cols, double** result);
void matrix_subtract(double** A, double** B, double** result, int rows, int cols);

#endif
