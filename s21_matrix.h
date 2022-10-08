#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

#define OK 0;
#define INCORRECT_MATRIX 1;
#define CALCULATION__MATRIX_ERROR 2;
#define EPS 1e-7

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Создание матрицы (create_matrix)
int s21_create_matrix(int rows, int columns, matrix_t *result);

// Очистка матриц (remove_matrix)
void s21_remove_matrix(matrix_t *A);

// Сравнение матриц (eq_matrix)
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// Сложение (sum_matrix)
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// вычитание матриц (sub_matrix)
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Умножение матрицы на число (mult_number)
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

// Умножение двух матриц (mult_matrix)
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Транспонирование матрицы (transpose)
int s21_transpose(matrix_t *A, matrix_t *result);

// Минор матрицы и матрица алгебраических дополнений (calc_complements)
int s21_calc_complements(matrix_t *A, matrix_t *result);
double s21_findDeterminant(matrix_t *A, int size);

// Определитель матрицы (determinant)
int s21_determinant(matrix_t *A, double *result);

// Обратная матрица (inverse_matrix)
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#endif  // SRC_S21_MATRIX_H_
