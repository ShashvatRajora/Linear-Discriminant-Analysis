#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#include "pure_math.h"
#include "lda_2d.h"

void normalize_vector(double* v, int dim) {
    double norm = 0.0;
    for (int i = 0; i < dim; i++) norm += v[i] * v[i];
    norm = sqrt(norm);
    for (int i = 0; i < dim; i++) v[i] /= norm;
}

void orthogonalize(double* v, double* base, int dim) {
    double dot = 0.0;
    for (int i = 0; i < dim; i++) dot += v[i] * base[i];
    for (int i = 0; i < dim; i++) v[i] -= dot * base[i];
}

void lda_solve_2d(double** SB, int dim, double** X_original) {
    double** A = alloc_matrix(dim, dim);
    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            A[i][j] = SB[i][j];

    double* v1 = calloc(dim, sizeof(double));
    double* v2 = calloc(dim, sizeof(double));
    power_iteration(A, dim, v1, 1000);

    // Generate second vector orthogonal to v1 using Gram-Schmidt
    for (int i = 0; i < dim; i++) v2[i] = rand() / (double)RAND_MAX;
    orthogonalize(v2, v1, dim);
    normalize_vector(v2, dim);

    // Export 2D projection
    FILE* out = fopen("lda_2d_projection.csv", "w");
    if (out) {
        for (int i = 0; i < 80; i++) {
            double dot1 = 0.0, dot2 = 0.0;
            for (int j = 0; j < dim; j++) {
                dot1 += X_original[i][j] * v1[j];
                dot2 += X_original[i][j] * v2[j];
            }
            int label = (i < 40) ? 0 : 1;
            fprintf(out, "%f,%f,%d\n", dot1, dot2, label);
        }
        fclose(out);
        printf("✅ 2D LDA projection saved to lda_2d_projection.csv\n");
    }

    free_matrix(A, dim);
    free(v1);
    free(v2);
}
