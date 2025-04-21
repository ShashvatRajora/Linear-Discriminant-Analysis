#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "pure_math.h"

int invert_matrix(double** A, int n, double** inverse) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            inverse[i][j] = (i == j) ? 1.0 : 0.0;

    for (int i = 0; i < n; i++) {
        // 🔁 If pivot is near zero, try to swap rows
        if (fabs(A[i][i]) < 1e-10) {
            int found = 0;
            for (int r = i + 1; r < n; r++) {
                if (fabs(A[r][i]) > 1e-10) {
                    // swap rows i and r in A and inverse
                    double* tempA = A[i];
                    A[i] = A[r];
                    A[r] = tempA;

                    double* tempI = inverse[i];
                    inverse[i] = inverse[r];
                    inverse[r] = tempI;

                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("❌ Matrix is singular at row %d — no pivot found\n", i);
                return 0;
            }
        }

        double pivot = A[i][i];
        for (int j = 0; j < n; j++) {
            A[i][j] /= pivot;
            inverse[i][j] /= pivot;
        }

        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = A[k][i];
                for (int j = 0; j < n; j++) {
                    A[k][j] -= factor * A[i][j];
                    inverse[k][j] -= factor * inverse[i][j];
                }
            }
        }
    }
    return 1;
}

void power_iteration(double** A, int n, double* eigenvector, int max_iter) {
    double* b = calloc(n, sizeof(double));
    for (int i = 0; i < n; i++) b[i] = 1.0;

    for (int iter = 0; iter < max_iter; iter++) {
        double* b_next = calloc(n, sizeof(double));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                b_next[i] += A[i][j] * b[j];
            }
        }

        // Normalize
        double norm = 0.0;
        for (int i = 0; i < n; i++) norm += b_next[i] * b_next[i];
        norm = sqrt(norm);
        if(norm == 0.0 || isnan(norm)){
            printf("Norm is zero or NaN - matrix may be bad\n");
            free(b_next);
            free(b);
            return;
        }

        for (int i = 0; i < n; i++) b[i] = b_next[i] / norm;

        free(b_next);
    }

    for (int i = 0; i < n; i++) eigenvector[i] = b[i];
    free(b);
}
