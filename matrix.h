#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>
#include <stdlib.h>

typedef struct matrix {
  float *array;
  size_t n_rows;
  size_t n_cols;
} Matrix;

Matrix *matrix_create(size_t n_rows, size_t n_cols);

void matrix_free(Matrix *mat);

void matrix_set(Matrix *mat, size_t row, size_t col, float value);

void matrix_set_array(Matrix *mat, float array[], size_t size);

float matrix_get(Matrix *mat, size_t row, size_t col);

void matrix_print(Matrix *mat);

Matrix *matrix_scale(float scalar, Matrix *mat);

Matrix *matrix_add(Matrix *mat1, Matrix *mat2);

Matrix *matrix_subtract(Matrix *mat1, Matrix *mat2);

Matrix *matrix_mult(Matrix *mat1, Matrix *mat2);

Matrix *matrix_trans(Matrix *mat1);

float *matrix_detrminant(Matrix *mat1);

#endif // !LINALGLIB_H
