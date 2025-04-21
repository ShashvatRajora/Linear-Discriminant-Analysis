#include <stdio.h>
#include <stdlib.h>
#include "lda.h"
#include "lda_2d.h"
#include "matrix.h"
#include "lda_eigen.h"

void lda_run(unsigned char image[80][1024], int num_classes, int class_size) {
    int samples = num_classes * class_size;
    int features = 1024;
    // features = 10; // just for testing purpose 

    double** X = alloc_matrix(samples, features);
    for (int i = 0; i < samples; i++)
        for (int j = 0; j < features; j++)
            X[i][j] = (double)image[i][j];

    double** class_means = alloc_matrix(num_classes, features);
    for (int c = 0; c < num_classes; c++) {
        for (int i = 0; i < class_size; i++) {
            int idx = c * class_size + i;
            for (int j = 0; j < features; j++) {
                class_means[c][j] += X[idx][j];
            }
        }
        for (int j = 0; j < features; j++)
            class_means[c][j] /= class_size;
    }

    double* mean_total = calloc(features, sizeof(double));
    for (int c = 0; c < num_classes; c++)
        for (int j = 0; j < features; j++)
            mean_total[j] += class_means[c][j] / num_classes;

    double** SW = alloc_matrix(features, features);
    double** SB = alloc_matrix(features, features);

    for (int c = 0; c < num_classes; c++) {
        for (int i = 0; i < class_size; i++) {
            int idx = c * class_size + i;
            for (int j = 0; j < features; j++) {
                for (int k = 0; k < features; k++) {
                    SW[j][k] += (X[idx][j] - class_means[c][j]) * (X[idx][k] - class_means[c][k]);
                }
            }
        }
        for (int j = 0; j < features; j++) {
            for (int k = 0; k < features; k++) {
                SB[j][k] += class_size * (class_means[c][j] - mean_total[j]) * (class_means[c][k] - mean_total[k]);
            }
        }
    }

    lda_solve_eigen(SW, SB, features, 2, X);
    lda_solve_2d(SB, features, X);


    free_matrix(X, samples);
    free_matrix(class_means, num_classes);
    free(mean_total);
    free_matrix(SW, features);
    free_matrix(SB, features);
}
