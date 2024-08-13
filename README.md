# Matrix Library README

## Overview

This library is a work-in-progress (WIP) project aimed at learning and mastering C programming. The library provides basic matrix operations, including creation, manipulation, and solving linear systems, and serves as a foundation for eventually implementing data science and artificial intelligence (AI) algorithms from scratch. 

The goal of this project is to challenge myself and deepen my understanding of mathematics, AI, and their implementation at a low level in C.

## Motivation

This project is part of my journey to learn C programming and develop a solid understanding of mathematical concepts and artificial intelligence. By implementing these operations from scratch, I aim to gain deeper insights into the algorithms and techniques that underpin data science and AI, ultimately preparing myself for more advanced projects in these fields.

## Features

- Matrix creation, manipulation, and deletion
- Matrix operations: addition, subtraction, multiplication, scaling, and transposition
- Matrix utility functions: identity matrix, determinant, and inverse
- Solving linear systems of equations
- Matrix comparison with tolerance

## Functions

### Matrix Operations

- **`Matrix *matrix_create(size_t n_rows, size_t n_cols);`**
  - Creates a matrix with a specified number of rows and columns.
  
- **`void matrix_free(Matrix *mat);`**
  - Frees the memory allocated for the matrix.

- **`void matrix_set(Matrix *mat, size_t row, size_t col, float value);`**
  - Sets the value of a specific element in the matrix.

- **`void matrix_set_array(Matrix *mat, float array[], size_t size);`**
  - Sets the matrix values from a flat array.

- **`float matrix_get(Matrix *mat, size_t row, size_t col);`**
  - Gets the value of a specific element in the matrix.

- **`void matrix_print(Matrix *mat);`**
  - Prints the matrix to standard output.

- **`Matrix *matrix_scale(float scalar, Matrix *mat);`**
  - Scales the matrix by a scalar value.

- **`Matrix *matrix_add(Matrix *mat1, Matrix *mat2);`**
  - Adds two matrices.

- **`Matrix *matrix_subtract(Matrix *mat1, Matrix *mat2);`**
  - Subtracts one matrix from another.

- **`Matrix *matrix_mult(Matrix *mat1, Matrix *mat2);`**
  - Multiplies two matrices.

- **`Matrix *matrix_trans(Matrix *mat1);`**
  - Computes the transpose of a matrix.

- **`Matrix *matrix_identity(size_t n);`**
  - Creates an identity matrix of size `n x n`.

### Matrix Utilities

- **`float matrix_determinant(Matrix *mat1);`**
  - Computes the determinant of a square matrix.

- **`Matrix *matrix_inverse(Matrix *mat);`**
  - Computes the inverse of a square matrix.

- **`Matrix *solve_lin_system(Matrix *A, Matrix *b);`**
  - Solves the linear system `Ax = b` using the least squares method.

### Utilities

- **`int matrices_are_approx_equal(Matrix *A, Matrix *B, float tolerance);`**
  - Checks if two matrices are approximately equal within a given tolerance.

- **`int compare_floats(float a, float b, float tolerance);`**
  - Compares two floating-point numbers within a given tolerance.

## Example Usage

```c
#include "matrix.h"
#include <stdio.h>

int main() {
    Matrix *A = matrix_create(2, 2);
    Matrix *B = matrix_create(2, 2);
    
    matrix_set(A, 0, 0, 1.0);
    matrix_set(A, 0, 1, 2.0);
    matrix_set(A, 1, 0, 3.0);
    matrix_set(A, 1, 1, 4.0);
    
    matrix_set(B, 0, 0, 5.0);
    matrix_set(B, 0, 1, 6.0);
    matrix_set(B, 1, 0, 7.0);
    matrix_set(B, 1, 1, 8.0);
    
    Matrix *C = matrix_add(A, B);
    matrix_print(C);
    
    matrix_free(A);
    matrix_free(B);
    matrix_free(C);
    
    return 0;
}
```

