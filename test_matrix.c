#include "matrix.h"
#include <stdio.h>

void test_matrix_create_free() {
  printf("\n=== TESTING test_matrix_create_free ===\n");
  Matrix *mat = matrix_create(2, 3);
  if (mat != NULL) {
    printf("Matrix created with %zu rows and %zu cols.\n", mat->n_rows,
           mat->n_cols);
    matrix_free(mat);
    printf("Matrix freed successfully.\n");
  } else {
    printf("Failed to create matrix.\n");
  }
}

void test_matrix_set_get() {
  printf("\n=== TESTING test_matrix_set_get ===\n");
  Matrix *mat = matrix_create(2, 3);
  if (mat != NULL) {
    matrix_set(mat, 0, 0, 1.0);
    matrix_set(mat, 1, 2, 2.5);
    printf("Value at (0, 0): %.2f\n", matrix_get(mat, 0, 0));
    printf("Value at (1, 2): %.2f\n", matrix_get(mat, 1, 2));
    matrix_free(mat);
  } else {
    printf("Failed to create matrix.\n");
  }
}

void test_matrix_print() {
  printf("\n=== TESTING test_matrix_print ===\n");
  Matrix *mat = matrix_create(2, 3);
  if (mat != NULL) {
    matrix_set(mat, 0, 0, 1.0);
    matrix_set(mat, 0, 1, 2.0);
    matrix_set(mat, 0, 2, 3.0);
    matrix_set(mat, 1, 0, 4.0);
    matrix_set(mat, 1, 1, 5.0);
    matrix_set(mat, 1, 2, 6.0);
    matrix_print(mat);
    matrix_free(mat);
  } else {
    printf("Failed to create matrix.\n");
  }
}

void test_matrix_scale() {
  printf("\n=== TESTING test_matrix_scale ===\n");
  Matrix *mat = matrix_create(2, 2);
  if (mat != NULL) {
    matrix_set(mat, 0, 0, 1.0);
    matrix_set(mat, 0, 1, 2.0);
    matrix_set(mat, 1, 0, 3.0);
    matrix_set(mat, 1, 1, 4.0);

    Matrix *res = matrix_scale(2.0, mat);

    printf("Matrix after scaling by 2.0:\n");
    matrix_print(mat);

    matrix_free(mat);
    matrix_free(res);
  } else {
    printf("Failed to create matrix.\n");
  }
}

void test_matrix_add() {
  printf("\n=== TESTING test_matrix_add ===\n");
  Matrix *mat1 = matrix_create(2, 2);
  Matrix *mat2 = matrix_create(2, 2);
  if (mat1 != NULL && mat2 != NULL) {
    matrix_set(mat1, 0, 0, 1.0);
    matrix_set(mat1, 0, 1, 2.0);
    matrix_set(mat1, 1, 0, 3.0);
    matrix_set(mat1, 1, 1, 4.0);

    matrix_set(mat2, 0, 0, 5.0);
    matrix_set(mat2, 0, 1, 6.0);
    matrix_set(mat2, 1, 0, 7.0);
    matrix_set(mat2, 1, 1, 8.0);

    Matrix *res = matrix_add(mat1, mat2);
    if (res != NULL) {
      printf("Matrix addition result:\n");
      matrix_print(res);
      matrix_free(res);
    } else {
      printf("Failed to add matrices.\n");
    }

    matrix_free(mat1);
    matrix_free(mat2);
  } else {
    printf("Failed to create matrices.\n");
  }
}

void test_matrix_subtract() {
  printf("\n=== TESTING test_matrix_subtract ===\n");
  Matrix *mat1 = matrix_create(2, 2);
  Matrix *mat2 = matrix_create(2, 2);
  if (mat1 != NULL && mat2 != NULL) {
    matrix_set(mat1, 0, 0, 5.0);
    matrix_set(mat1, 0, 1, 6.0);
    matrix_set(mat1, 1, 0, 7.0);
    matrix_set(mat1, 1, 1, 8.0);

    matrix_set(mat2, 0, 0, 1.0);
    matrix_set(mat2, 0, 1, 2.0);
    matrix_set(mat2, 1, 0, 3.0);
    matrix_set(mat2, 1, 1, 4.0);

    Matrix *res = matrix_subtract(mat1, mat2);
    if (res != NULL) {
      printf("Matrix subtraction result:\n");
      matrix_print(res);
      matrix_free(res);
    } else {
      printf("Failed to subtract matrices.\n");
    }

    matrix_free(mat1);
    matrix_free(mat2);
  } else {
    printf("Failed to create matrices.\n");
  }
}

void test_matrix_mult() {
  printf("Testing matrix multiplication...\n");

  // Create two matrices for multiplication
  Matrix *mat1 = matrix_create(2, 3);
  Matrix *mat2 = matrix_create(3, 2);
  if (mat1 == NULL || mat2 == NULL) {
    printf("Failed to create matrices.\n");
    return;
  }

  // Set values for mat1
  matrix_set(mat1, 0, 0, 1.0);
  matrix_set(mat1, 0, 1, 2.0);
  matrix_set(mat1, 0, 2, 3.0);
  matrix_set(mat1, 1, 0, 4.0);
  matrix_set(mat1, 1, 1, 5.0);
  matrix_set(mat1, 1, 2, 6.0);

  // Set values for mat2
  matrix_set(mat2, 0, 0, 7.0);
  matrix_set(mat2, 0, 1, 8.0);
  matrix_set(mat2, 1, 0, 9.0);
  matrix_set(mat2, 1, 1, 10.0);
  matrix_set(mat2, 2, 0, 11.0);
  matrix_set(mat2, 2, 1, 12.0);

  // Multiply matrices
  Matrix *res = matrix_mult(mat1, mat2);
  if (res != NULL) {
    printf("Matrix multiplication result:\n");
    matrix_print(res);

    // Expected result
    // mat1 * mat2 = [ 1*7 + 2*9 + 3*11, 1*8 + 2*10 + 3*12 ]
    //                [ 4*7 + 5*9 + 6*11, 4*8 + 5*10 + 6*12 ]

    printf("Expected result:\n");
    printf("58.0  64.0\n");
    printf("139.0  154.0\n");

    matrix_free(res);
  } else {
    printf("Failed to multiply matrices.\n");
  }

  matrix_free(mat1);
  matrix_free(mat2);
}

void test_matrix_trans() {
  printf("\n=== TESTING test_matrix_trans ===\n");
  Matrix *mat = matrix_create(2, 3);
  // Set values for mat1
  matrix_set(mat, 0, 0, 1.0);
  matrix_set(mat, 0, 1, 2.0);
  matrix_set(mat, 0, 2, 3.0);
  matrix_set(mat, 1, 0, 4.0);
  matrix_set(mat, 1, 1, 5.0);
  matrix_set(mat, 1, 2, 6.0);

  printf("Initial matrix: \n");
  matrix_print(mat);

  Matrix *mat_t = matrix_trans(mat);
  printf("Transposed matrix:\n");
  matrix_print(mat_t);

  matrix_free(mat);
  matrix_free(mat_t);
}

void test_matrix_set_array() {
  printf("\n=== TESTING test_matrix_set_array ===\n");
  Matrix *mat = matrix_create(2, 3);

  float array1[] = {1, 2, 3, 4, 5, 6};

  matrix_set_array(mat, array1, 6);

  printf("Setting matrix->array to\n");
  for (int i = 0; i < 6; i++) {
    printf("%.1f ", array1[i]);
  }
  printf("\nResult:\n");
  matrix_print(mat);

  matrix_free(mat);
}

int main() {
  test_matrix_create_free();
  test_matrix_set_get();
  test_matrix_print();
  test_matrix_scale();
  test_matrix_add();
  test_matrix_subtract();
  test_matrix_mult();
  test_matrix_trans();
  test_matrix_set_array();

  return 0;
}
