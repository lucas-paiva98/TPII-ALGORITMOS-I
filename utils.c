#include "utils.h"

double **allocateMatrixDouble(int lines, int collumns) {
  double **matrix = (double **)malloc(lines * sizeof(double *));

  for (int i = 0; i < lines; i++) {
    matrix[i] = (double *)malloc(collumns * sizeof(double));
    for (int j = 0; j < collumns; j++) {
      matrix[i][j] = -1;
    }
  }
  return matrix;
}

int **allocateMatrix(int lines, int collumns) {
  int **matrix = (int **)malloc(lines * sizeof(int *));

  for (int i = 0; i < lines; i++) {
    matrix[i] = (int *)malloc(collumns * sizeof(int));
    for (int j = 0; j < collumns; j++) {
      matrix[i][j] = -1;
    }
  }
  return matrix;
}

int *allocateVector(int size) {
  int *vector = (int *)malloc(size * sizeof(int));
  return vector;
}