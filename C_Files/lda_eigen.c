#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "pure_math.h"

// void lda_solve_eigen(double** SW, double** SB, int dim, int top_k, double** X_original) {
//     // 1. Invert SW
//     double** SW_copy = alloc_matrix(dim, dim);
//     double** SW_inv = alloc_matrix(dim, dim);
//     for (int i = 0; i < dim; i++)
//         for (int j = 0; j < dim; j++)
//             SW_copy[i][j] = SW[i][j];

//     if (!invert_matrix(SW_copy, dim, SW_inv)) {
//         printf("Matrix inversion failed!\n");
//         return;
//     }

//     // 2. Compute A = SW^-1 * SB
//     double** A = alloc_matrix(dim, dim);
//     matrix_multiply(SW_inv, dim, dim, SB, dim, dim, A);

//     // 3. Compute dominant eigenvector of A using power iteration
//     double* eigenvector = calloc(dim, sizeof(double));
//     power_iteration(A, dim, eigenvector, 1000);

//     // 4. Project data onto eigenvector
//     printf("\nProjection onto top LDA direction:\n");
//     for (int i = 0; i < 5; i++) {
//         double dot = 0.0;
//         for (int j = 0; j < dim; j++)
//             dot += X_original[i][j] * eigenvector[j];
//         printf("Sample %d: %f\n", i, dot);
//     }

//     free(eigenvector);
//     free_matrix(A, dim);
//     free_matrix(SW_inv, dim);
//     free_matrix(SW_copy, dim);
// }

/* The issue with this piece of code is that , sine features are more than samples, the inversion is not taking place corectly
so , we are trying to handle it by skipping the inversion part and directly using the SB*/

void lda_solve_eigen(double **SW, double **SB, int dim, int top_k, double **X_original)
{
    // Step 1: Use SB directly
    double **A = alloc_matrix(dim, dim);
    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            A[i][j] = SB[i][j];

    // Step 2: Power iteration on SB directly
    double *eigenvector = calloc(dim, sizeof(double));
    power_iteration(A, dim, eigenvector, 1000);

    /* Step 3: Project original data , this code just prints 5 best samples from 1024 in the terminal
    its just better to put up a .csv for further analysis . */
    // printf("\nProjection onto SB's top direction:\n");
    // for (int i = 0; i < 5; i++) {
    //     double dot = 0.0;
    //     for (int j = 0; j < dim; j++)
    //         dot += X_original[i][j] * eigenvector[j];
    //     printf("Sample %d: %f\n", i, dot);
    // }

    // Step 3: Project original data and save to file
    FILE *out = fopen("lda_projection.csv", "w");
    if (out)
    {
        for (int i = 0; i < 80; i++)
        {
            double dot = 0.0;
            for (int j = 0; j < dim; j++)
                dot += X_original[i][j] * eigenvector[j];

            int label = (i < 40) ? 0 : 1;
            fprintf(out, "%f,%d\n", dot, label);
        }
        fclose(out);
        printf("✅ Projections saved to lda_projection.csv\n");
    }
    else
    {
        printf("❌ Could not write to lda_projection.csv\n");
    }

    free(eigenvector);
    free_matrix(A, dim);
}