#ifndef LDA_EIGEN_H
#define LDA_EIGEN_H

void lda_solve_eigen(double** SW, double** SB, int dim, int top_k, double** X_original);

#endif
