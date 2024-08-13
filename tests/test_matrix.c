#include "matrix.h"
#include <math.h>
#include <stdio.h>

// Define a small tolerance for floating-point comparisons
#define TOLERANCE 1e-6

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

void test_matrix_determinant() {
  printf("\n=== TESTING test_matrix_determinant ===\n");
  Matrix *mat = matrix_create(3, 3);
  // Set values for mat
  float array1[9] = {1., 2., 3., 0., 4, 5., 1., 0., 6.};
  matrix_set_array(mat, array1, 9);
  matrix_print(mat);

  float det1 = matrix_determinant(mat);
  printf("Determinant = %f, expected 22\n", det1);

  float array2[9] = {2., 5., 3., 1., -2., 4., 3., 6., 1.};
  matrix_set_array(mat, array2, 9);
  matrix_print(mat);

  float det2 = matrix_determinant(mat);
  printf("Determinant = %f, expected 39\n", det2);

  matrix_free(mat);
}

void test_matrix_inverse() {

  printf("\n=== TESTING test_matrix_determinant ===\n");
  // Define a 3x3 test matrix
  float test_array[] = {4, 7, 2, 3, 6, 1, 2, 5, 2};

  Matrix *test_matrix = matrix_create(3, 3);
  matrix_set_array(test_matrix, test_array, 9);

  // Expected inverse (calculated manually or using a tool like NumPy)
  float expected_inverse[] = {1.1666666666666665,
                              -0.6666666666666665,
                              -0.8333333333333333,
                              -0.6666666666666666,
                              0.6666666666666666,
                              0.3333333333333333,
                              0.5,
                              -1.0,
                              0.5};

  // Compute the inverse using your function
  Matrix *computed_inverse = matrix_inverse(test_matrix);

  // Compare each element of the computed inverse to the expected values
  int success = 1;
  float tolerance = 1e-5;
  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < 3; j++) {
      float expected_value = expected_inverse[i * 3 + j];
      float computed_value = matrix_get(computed_inverse, i, j);
      if (!compare_floats(expected_value, computed_value, tolerance)) {
        printf("Test failed at position (%zu, %zu): expected %f, got %f\n", i,
               j, expected_value, computed_value);
        success = 0;
      }
    }
  }

  if (success) {
    printf("Test passed: matrix inverse is correct.\n");
  }

  // Free memory
  matrix_free(test_matrix);
  matrix_free(computed_inverse);
}

// Function to test solve_lin_system for square matrix case
void test_solve_lin_system() {
  printf("\n=== TESTING test_solve_lin_system ===\n");
  // Define matrix A and vector b
  size_t n = 3;
  Matrix *A = matrix_create(n, n);
  Matrix *b = matrix_create(n, 1);

  // Example data
  float A_data[] = {2, 1, -1, -3, -1, 2, -2, 1, 2};
  float b_data[] = {8, -11, -3};

  matrix_set_array(A, A_data, n * n);
  matrix_set_array(b, b_data, n);

  // Solve the system
  Matrix *x = solve_lin_system(A, b);

  // Check if the result is correct
  if (x == NULL) {
    fprintf(stderr, "solve_lin_system failed\n");
    matrix_free(A);
    matrix_free(b);
    return;
  }

  // Compute Ax
  Matrix *Ax = matrix_mult(A, x);

  // Check if Ax is approximately equal to b
  if (matrices_are_approx_equal(Ax, b, TOLERANCE)) {
    printf("Test passed\n");
    printf("Expected b:\n");
    matrix_print(b);
    printf("Computed Ax:\n");
    matrix_print(Ax);
  } else {
    printf("Test failed\n");
    printf("Expected b:\n");
    matrix_print(b);
    printf("Computed Ax:\n");
    matrix_print(Ax);
  }

  // Free matrices
  matrix_free(A);
  matrix_free(b);
  matrix_free(x);
  matrix_free(Ax);
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
  test_matrix_determinant();
  test_matrix_inverse();
  test_solve_lin_system();

  return 0;
}
