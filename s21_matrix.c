#include "s21_matrix.h"

// Создание матрицы (create_matrix)
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows < 0 || columns < 0) return INCORRECT_MATRIX;

  int flag = OK;
  result->rows = rows;
  result->columns = columns;
  result->matrix = calloc(rows, sizeof(double *));
  if (result) {
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = calloc(columns, sizeof(double));
      if (!(result->matrix[i])) {
        flag = INCORRECT_MATRIX;
        break;
      }
    }
  }
  return flag;
}

// Очистка матриц (remove_matrix)
void s21_remove_matrix(matrix_t *A) {
  if (A) {
    for (int i = 0; i < A->rows; i++) free(A->matrix[i]);
    free(A->matrix);
  }
}

// Сравнение матриц (eq_matrix)
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (!A || !B || !A->matrix || !B->matrix) return FAILURE;

  int flag = SUCCESS;
  if (A->columns != B->columns || A->rows != B->rows) flag = FAILURE;
  if (flag) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
          flag = FAILURE;
          break;
        }
      }
    }
  }
  return flag;
}

// Сложение (sum_matrix)
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!A || !B || !result || !A->matrix || !B->matrix) return INCORRECT_MATRIX;
  if (A->columns != B->columns || A->rows != B->rows)
    return CALCULATION__MATRIX_ERROR;

  if (!s21_create_matrix(A->rows, A->columns, result)) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return OK;
}

// вычитание матриц (sub_matrix)
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!A || !B || !result || !A->matrix || !B->matrix) return INCORRECT_MATRIX;
  if (A->columns != B->columns || A->rows != B->rows)
    return CALCULATION__MATRIX_ERROR;

  if (!s21_create_matrix(A->rows, A->columns, result)) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return OK;
}

// Умножение матрицы на число (mult_number)
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (!A || !result || !A->matrix) return INCORRECT_MATRIX;

  if (!s21_create_matrix(A->rows, A->columns, result)) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return OK;
}

// Умножение двух матриц (mult_matrix)
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!A || !B || !result || !A->matrix || !B->matrix) return INCORRECT_MATRIX;
  if (A->columns != B->rows) return CALCULATION__MATRIX_ERROR;

  if (!s21_create_matrix(A->rows, B->columns, result)) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        double buffer = 0;
        for (int k = 0; k < A->columns; k++) {
          buffer += A->matrix[i][k] * B->matrix[k][j];
        }
        result->matrix[i][j] = buffer;
      }
    }
  }
  return OK;
}

// Транспонирование матрицы (transpose)
int s21_transpose(matrix_t *A, matrix_t *result) {
  if (!A || !result || !A->matrix) return INCORRECT_MATRIX;

  if (!s21_create_matrix(A->columns, A->rows, result)) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return OK;
}

// Минор матрицы и матрица алгебраических дополнений (calc_complements)
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (!A || !result) return INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALCULATION__MATRIX_ERROR;
  int size = A->rows;

  if (!s21_create_matrix(size, size, result)) {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        matrix_t m_minor = {};
        int minor_size = size - 1;
        int minor_rows = 0;
        int minor_columns = 0;
        if (!s21_create_matrix(minor_size, minor_size, &m_minor)) {
          for (int k = 0; k < size; k++) {
            if (k == i) continue;
            for (int m = 0; m < size; m++) {
              if (m == j) continue;
              m_minor.matrix[minor_rows][minor_columns] = A->matrix[k][m];
              minor_columns++;
              if (minor_columns == minor_size) {
                minor_columns = 0;
                minor_rows++;
              }
            }
          }
          result->matrix[i][j] = s21_findDeterminant(&m_minor, minor_size) *
                                 pow(-1, (i + 1 + j + 1));
        }
        s21_remove_matrix(&m_minor);
      }
    }
  }
  return 0;
}

double s21_findDeterminant(matrix_t *A, int size) {
  if (size == 1) {
    return A->matrix[0][0];
  } else if (size == 2) {
    return (A->matrix[0][0] * A->matrix[1][1] -
            A->matrix[0][1] * A->matrix[1][0]);
  } else {
    int determinant = 0;
    for (int k = 0; k < size; k++) {
      matrix_t minor = {};
      if (!s21_create_matrix(size - 1, size - 1, &minor)) {
        for (int i = 1; i < size; i++) {
          int t = 0;
          for (int j = 0; j < size; j++) {
            if (j == k) continue;
            minor.matrix[i - 1][t] = A->matrix[i][j];
            t++;
          }
        }
      }
      determinant += pow(-1, k + 2) * A->matrix[0][k] *
                     s21_findDeterminant(&minor, size - 1);
      s21_remove_matrix(&minor);
    }
    return determinant;
  }
}

// Определитель матрицы (determinant)
int s21_determinant(matrix_t *A, double *result) {
  if (!A || !result || !A->matrix) return INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALCULATION__MATRIX_ERROR;

  *result = s21_findDeterminant(A, A->rows);

  return OK;
}

// Обратная матрица (inverse_matrix)
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!A || !result || !A->matrix) return INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALCULATION__MATRIX_ERROR;

  int flag = 0;
  double determinant = 0.0;
  s21_determinant(A, &determinant);
  if (!determinant) {
    flag = CALCULATION__MATRIX_ERROR;
  } else {
    matrix_t complenents = {};
    matrix_t t_complenents = {};
    s21_calc_complements(A, &complenents);
    s21_transpose(&complenents, &t_complenents);
    s21_mult_number(&t_complenents, 1.0 / determinant, result);
    s21_remove_matrix(&complenents);
    s21_remove_matrix(&t_complenents);
  }
  return flag;
}
