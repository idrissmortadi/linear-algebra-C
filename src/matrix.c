#include "matrix.h"
#include <math.h>
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

void lu_decomposition(Matrix *A, Matrix *L, Matrix *U) {
  size_t n = A->n_rows;

  for (size_t i = 0; i < n; i++) {
    for (size_t j = i; j < n; j++) {
      // Upper Triangular
      U->array[i * n + j] = A->array[i * n + j];
      for (size_t k = 0; k < i; k++) {
        U->array[i * n + j] -= L->array[i * n + k] * U->array[k * n + j];
      }
    }

    for (size_t j = i; j < n; j++) {
      if (i == j) {
        L->array[i * n + i] = 1; // Diagonal as 1
      } else {
        // Lower Triangular
        L->array[j * n + i] = A->array[j * n + i];
        for (size_t k = 0; k < i; k++) {
          L->array[j * n + i] -= L->array[j * n + k] * U->array[k * n + i];
        }
        L->array[j * n + i] /= U->array[i * n + i];
      }
    }
  }
}

float matrix_determinant(Matrix *mat) {
  if (mat->n_rows != mat->n_cols) {
    fprintf(stderr, "Error matrix_determinant: n_rows(%zu) != n_cols(%zu)\n",
            mat->n_rows, mat->n_cols);
    return NAN;
  }

  Matrix *lower = matrix_create(mat->n_rows, mat->n_cols);
  Matrix *upper = matrix_create(mat->n_rows, mat->n_cols);
  lu_decomposition(mat, lower, upper);

  float det = 1;

  for (size_t i = 0; i < upper->n_rows; i++) {
    det *= matrix_get(upper, i, i);
  };

  matrix_free(lower);
  matrix_free(upper);
  return det;
}

Matrix *matrix_identity(size_t n) {
  Matrix *I = matrix_create(n, n);

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      if (i == j) {
        matrix_set(I, i, j, 1);
      } else {
        matrix_set(I, i, j, 0);
      }
    }
  }

  return I;
}

void matrix_swap_rows(Matrix *mat, size_t row1, size_t row2) {
  if (row1 > mat->n_rows) {
    fprintf(stderr, "Error matrix_swap_rows: row1 (%zu) > matrix n_rows (%zu)",
            row1, mat->n_rows);
  } else if (row2 > mat->n_rows) {
    fprintf(stderr, "Error matrix_swap_rows: row2 (%zu) > matrix n_rows (%zu)",
            row2, mat->n_rows);
  };

  for (size_t j = 0; j < mat->n_cols; j++) {
    float temp_val = matrix_get(mat, row1, j);

    matrix_set(mat, row1, j, matrix_get(mat, row2, j));
    matrix_set(mat, row2, j, temp_val);
  }
}

Matrix *matrix_inverse(Matrix *mat) {
  if (mat->n_rows != mat->n_cols) {
    fprintf(stderr, "Error matrix_inverse: n_rows(%zu) != n_cols(%zu)\n",
            mat->n_rows, mat->n_cols);
    return NULL;
  }

  if (matrix_determinant(mat) == 0) {
    fprintf(stderr,
            "Error matrix_inverse: determinant is zero, no inverse exists\n");
    return NULL;
  }

  size_t n = mat->n_rows;

  // Copy mat into A
  Matrix *A = matrix_create(n, n);
  matrix_set_array(A, mat->array, n * n);

  // Create identity matrix I
  Matrix *I = matrix_identity(n);

  for (size_t j = 0; j < n; j++) {
    // Find pivot
    float pivot = 0.0;
    size_t pivot_index = j;
    for (size_t i = j; i < n; i++) {
      if (fabs(matrix_get(A, i, j)) > fabs(pivot)) {
        pivot = matrix_get(A, i, j);
        pivot_index = i;
      }
    }

    // Swap rows in A and I if pivot is not on the diagonal
    if (pivot_index != j) {
      matrix_swap_rows(A, j, pivot_index);
      matrix_swap_rows(I, j, pivot_index);
    }

    // Scale the pivot row
    float pivot_value = matrix_get(A, j, j);
    for (size_t k = 0; k < n; k++) {
      matrix_set(A, j, k, matrix_get(A, j, k) / pivot_value);
      matrix_set(I, j, k, matrix_get(I, j, k) / pivot_value);
    }

    // Eliminate the column entries below the pivot
    for (size_t i = j + 1; i < n; i++) {
      float factor = matrix_get(A, i, j);
      for (size_t k = 0; k < n; k++) {
        matrix_set(A, i, k, matrix_get(A, i, k) - factor * matrix_get(A, j, k));
        matrix_set(I, i, k, matrix_get(I, i, k) - factor * matrix_get(I, j, k));
      }
    }
  }

  // Back substitution to eliminate upper triangular elements
  for (size_t j = n; j-- > 0;) {
    for (size_t i = 0; i < j; i++) {
      float factor = matrix_get(A, i, j);
      for (size_t k = 0; k < n; k++) {
        matrix_set(A, i, k, matrix_get(A, i, k) - factor * matrix_get(A, j, k));
        matrix_set(I, i, k, matrix_get(I, i, k) - factor * matrix_get(I, j, k));
      }
    }
  }

  matrix_free(A);
  return I;
}

// Function to solve Ly = b using forward substitution
void forward_substitution(Matrix *L, Matrix *b, Matrix *y) {
  size_t n = L->n_rows;

  for (size_t i = 0; i < n; i++) {
    y->array[i] = b->array[i];
    for (size_t j = 0; j < i; j++) {
      y->array[i] -= L->array[i * n + j] * y->array[j];
    }
    y->array[i] /= L->array[i * n + i];
  }
}

// Function to solve Ux = y using backward substitution
void backward_substitution(Matrix *U, Matrix *y, Matrix *x) {
  size_t n = U->n_rows;

  for (int i = n - 1; i >= 0; i--) {
    x->array[i] = y->array[i];
    for (int j = i + 1; j < n; j++) {
      x->array[i] -= U->array[i * n + j] * x->array[j];
    }
    x->array[i] /= U->array[i * n + i];
  }
}

// Function to solve the system Ax = b using LU decomposition
Matrix *solve_using_LU(Matrix *A, Matrix *b) {
  size_t n = A->n_rows;

  Matrix *L = matrix_create(n, n);
  Matrix *U = matrix_create(n, n);
  Matrix *y = matrix_create(n, 1);
  Matrix *x = matrix_create(n, 1);

  lu_decomposition(A, L, U);
  forward_substitution(L, b, y);
  backward_substitution(U, y, x);

  matrix_free(L);
  matrix_free(U);
  matrix_free(y);

  return x;
}

Matrix *solve_lin_system(Matrix *A, Matrix *b) {
  size_t n = A->n_rows;
  size_t m = A->n_cols;

  if (A->n_rows != b->n_rows) {
    fprintf(
        stderr,
        "solve_lin_system: Error solve_lin_system: size mismatch of A and b");
    return NULL;
  }
  if (b->n_cols != 1) {
    fprintf(stderr, "solve_lin_system: b n_cols > 1, not a vector");
    return NULL;
  }

  if (n == m) {
    Matrix *x = solve_using_LU(A, b);
    return x;
  } else if (n > m) {
    printf("solve_lin_system: Overdetermined solution");
    Matrix *x =
        matrix_mult(matrix_mult(matrix_inverse(matrix_mult(matrix_trans(A), A)),
                                matrix_trans(A)),
                    b);
    return x;
  } else {
    // Handle underdetermined system or return an error
    fprintf(stderr,
            "solve_lin_system: Underdetermined system is not supported\n");
    return NULL;
  }

  return NULL;
}
