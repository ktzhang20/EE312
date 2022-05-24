// matrix-multiplication <Project2.cpp>
// EE 312 Project 2 submission by
// Ken Zhang
// ktz85
// Slip days used: <0>
// Fall 2021
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "MatrixMultiply.h"

void multiplyMatrices(
        double a[],
        const uint32_t a_rows,
        const uint32_t a_cols,
        double b[],
        const uint32_t b_cols,
        double c[]) {
    // https://en.wikipedia.org/wiki/Row-_and_column-major_order
    for(int i = 0; i < a_rows; i++){
      for(int j = 0; j < b_cols; j++){
        c[i*b_cols+j] = 0.0;
        for(int k = 0; k < a_cols; k++){
          c[i*b_cols+j] += a[i*a_cols+k] * b[k*b_cols+j];
          
        }
      }
    }

}

double** multiplyMatricesPtr(
        double** a,
        const uint32_t a_rows,
        const uint32_t a_cols,
        double** b,
        const uint32_t b_cols) {
    double** arr = (double **) malloc(a_rows * sizeof(double*));
    for(int i = 0; i < a_rows; i++){
      arr[i] = (double *) malloc(b_cols * sizeof(double));
    }
    for(int i = 0; i < a_rows; i++){
      for(int j = 0; j < b_cols; j++){
        arr[i][j] = 0;
        for(int k = 0; k < a_cols; k++){
          arr[i][j] += a[i][k] * b[k][j];
        }
      }
    }
    return arr;
}

// https://en.wikipedia.org/wiki/Transpose
double** transposeMatrix(
         double** a,
         const uint32_t a_rows,
         const uint32_t a_cols) {
    double** arr = (double **) malloc(a_cols * sizeof(double*));
    for(int i = 0; i < a_cols; i++){
      arr[i] = (double *) malloc(a_rows * sizeof(double));
    }
    for(int i = 0; i < a_rows; i++){
      for(int j = 0; j < a_cols; j++){
        arr[j][i] = a[i][j];
      }
    }

    return arr;
}
