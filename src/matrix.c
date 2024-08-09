#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Matrix *matrix_create(size_t n_rows, size_t n_cols) {
  Matrix *mat = malloc(sizeof(Matrix));

  if (mat == NULL)
    return NULL;

  mat->n_rows = n_rows;
  mat->n_cols = n_cols;
  mat->array = malloc(n_rows * n_cols * sizeof(float));

  if (mat->array == NULL) {
    free(mat);
    return NULL;
  }

  return mat;
}

void matrix_free(Matrix *mat) {
  if (mat != NULL) {
    free(mat->array);
    free(mat);
  }
}

void matrix_set(Matrix *mat, size_t row, size_t col, float value) {
  if (row < mat->n_rows && col < mat->n_cols) {
    mat->array[row * mat->n_cols + col] = value;
  } else {
    fprintf(stderr,
            "Error: row (%zu) or col (%zu) is bigger than n_rows (%zu) or "
            "n_cols (%zu)\n",
            row, col, mat->n_rows, mat->n_cols);
  }
}

// array is 1D
void matrix_set_array(Matrix *mat, float array[], size_t size) {
  // Check if the provided array size matches the matrix's size
  if (size != mat->n_rows * mat->n_cols) {
    fprintf(
        stderr,
        "Error matrix_set_array: mat array size %zu != input array size %zu\n",
        mat->n_rows * mat->n_cols, size);
    return; // Exit the function if sizes don't match
  }

  // Copy the contents of the input array into the matrix's array
  memcpy(mat->array, array, size * sizeof(float));
}

float matrix_get(Matrix *mat, size_t row, size_t col) {
  if (row < mat->n_rows && col < mat->n_cols) {
    return mat->array[row * mat->n_cols + col];
  } else {
    fprintf(stderr,
            "Error: row (%zu) or col (%zu) is bigger than n_rows (%zu) or "
            "n_cols (%zu)\n",
            row, col, mat->n_rows, mat->n_cols);
    return 0.0;
  }
}

void matrix_print(Matrix *mat) {
  for (size_t i = 0; i < mat->n_rows; ++i) {
    for (size_t j = 0; j < mat->n_cols; ++j) {
      printf("%.1f ", matrix_get(mat, i, j));
    }
    printf("\n");
  }
}

Matrix *matrix_scale(float scalar, Matrix *mat) {
  Matrix *res = matrix_create(mat->n_rows, mat->n_cols);
  if (res == NULL)
    return NULL;

  for (size_t i = 0; i < mat->n_rows * mat->n_cols; ++i) {
    res->array[i] = scalar * mat->array[i];
  }

  return res;
}

Matrix *matrix_add(Matrix *mat1, Matrix *mat2) {
  if (mat1->n_rows != mat2->n_rows || mat1->n_cols != mat2->n_cols) {
    fprintf(stderr, "Error: size mismatch\n");
    return NULL;
  }
  Matrix *res = matrix_create(mat1->n_rows, mat2->n_cols);
  if (res == NULL)
    return NULL;

  for (size_t i = 0; i < mat1->n_rows * mat1->n_cols; ++i) {
    res->array[i] = mat1->array[i] + mat2->array[i];
  }

  return res;
}

Matrix *matrix_subtract(Matrix *mat1, Matrix *mat2) {
  if (mat1->n_rows != mat2->n_rows || mat1->n_cols != mat2->n_cols) {
    fprintf(stderr, "Error: size mismatch\n");
    return NULL;
  }
  Matrix *res = matrix_create(mat1->n_rows, mat2->n_cols);
  if (res == NULL)
    return NULL;

  for (size_t i = 0; i < mat1->n_rows * mat1->n_cols; ++i) {
    res->array[i] = mat1->array[i] - mat2->array[i];
  }

  return res;
}

Matrix *matrix_mult(Matrix *mat1, Matrix *mat2) {
  // Check if the matrices can be multiplied
  if (mat1->n_cols != mat2->n_rows) {
    fprintf(stderr, "Error: size mismatch\n");
    return NULL;
  }

  // Create result matrix
  Matrix *res = matrix_create(mat1->n_rows, mat2->n_cols);
  if (res == NULL) {
    fprintf(stderr, "Error: memory allocation failed\n");
    return NULL;
  }

  // Initialize the result matrix with zeros
  for (size_t i = 0; i < res->n_rows; ++i) {
    for (size_t j = 0; j < res->n_cols; ++j) {
      float val = 0.0f; // Initialize val to 0
      for (size_t k = 0; k < mat1->n_cols; ++k) {
        val += matrix_get(mat1, i, k) * matrix_get(mat2, k, j);
      }
      matrix_set(res, i, j, val);
    }
  }

  return res;
}

Matrix *matrix_trans(Matrix *mat) {
  Matrix *res = matrix_create(mat->n_cols, mat->n_rows);

  for (size_t i = 0; i < res->n_rows; ++i) {
    for (size_t j = 0; j < res->n_cols; ++j) {
      matrix_set(res, i, j, matrix_get(mat, j, i));
    }
  }

  return res;
}

float *matrix_determinant(Matrix *mat) {
  if (mat->n_rows != mat->n_cols) {
    fprintf(stderr, "Error matrix_determinant: n_rows(%zu) != n_cols(%zu)\n",
            mat->n_rows, mat->n_cols);
    return NULL;
  }

  return 0;
}
