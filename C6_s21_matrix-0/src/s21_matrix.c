#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error_code = 0;
  if (result != NULL && rows > 0 && columns > 0) {
    result->matrix = (double **)malloc(rows * sizeof(double *));
    if (result->matrix != NULL) {
      int rows_alloc = 0;
      while (rows_alloc < rows && !error_code) {
        result->matrix[rows_alloc] = (double *)calloc(columns, sizeof(double));
        if (result->matrix[rows_alloc] == NULL) {
          error_code = 1;
        }
        rows_alloc++;
      }
      if (error_code) {
        free_rows(rows_alloc - 1, result);
        free(result->matrix);
      } else {
        result->rows = rows;
        result->columns = columns;
      }
    } else {
      error_code = 1;
    }
  } else {
    error_code = 1;
  }
  return error_code;
}

void s21_remove_matrix(matrix_t *A) {
  if (!s21_check_matrix(A)) {
    free_rows(A->rows, A);
    free(A->matrix);
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (!s21_check_matrix(A) && !s21_check_matrix(B)) {
    if (A->rows == B->rows && A->columns == B->columns) {
      for (int i = 0; i < A->rows && result; i++) {
        for (int j = 0; j < A->columns && result; j++) {
          if (fabs(fabs(A->matrix[i][j]) - fabs(B->matrix[i][j])) >= EPS ||
              A->matrix[i][j] != A->matrix[i][j] ||
              B->matrix[i][j] != B->matrix[i][j]) {
            result = FAILURE;
          }
        }
      }
    } else {
      result = FAILURE;
    }
  } else {
    result = FAILURE;
  }
  return result;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error_code = s21_sum_sub_matrix(A, B, result, 1.0);
  return error_code;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error_code = s21_sum_sub_matrix(A, B, result, -1.0);
  return error_code;
}

int s21_sum_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result, int minus) {
  int error_code = 0;
  if (!s21_check_matrix(A) && !s21_check_matrix(B)) {
    if (A->rows == B->rows && A->columns == B->columns) {
      error_code = s21_create_matrix(A->rows, A->columns, result);
      if (!error_code) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + (B->matrix[i][j] * minus);
          }
        }
      }
    } else {
      error_code = 2;
    }
  } else {
    error_code = 1;
  }
  return error_code;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error_code = 0;
  if (!s21_check_matrix(A)) {
    error_code = s21_create_matrix(A->rows, A->columns, result);
    if (!error_code) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  } else {
    error_code = 1;
  }
  return error_code;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error_code = 0;
  if (!s21_check_matrix(A) && !s21_check_matrix(B)) {
    if (A->columns == B->rows) {
      error_code = s21_create_matrix(A->rows, B->columns, result);
      if (!error_code) {
        for (int i = 0; i < result->rows; i++) {
          for (int j = 0; j < result->columns; j++) {
            for (int k = 0; k < A->columns; k++) {
              result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
          }
        }
      }
    } else {
      error_code = 2;
    }
  } else {
    error_code = 1;
  }
  return error_code;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error_code = 0;
  if (!s21_check_matrix(A)) {
    error_code = s21_create_matrix(A->columns, A->rows, result);
    if (!error_code) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    }
  } else {
    error_code = 1;
  }
  return error_code;
}

int s21_determinant(matrix_t *A, double *result) {
  int error_code = 0;
  if (!s21_check_matrix(A) && result != NULL) {
    double temp = *result;
    if (A->rows == A->columns) {
      if (A->rows == 1) {
        *result = A->matrix[0][0];
      } else {
        *result = s21_calc_determinant(*A, &error_code);
        if (error_code) {
          *result = temp;
        }
      }
    } else {
      error_code = 2;
    }
  } else {
    error_code = 1;
  }
  return error_code;
}

double s21_calc_determinant(matrix_t A, int *error_code) {
  double result = 0;
  if (A.rows == 2) {
    result = A.matrix[0][0] * A.matrix[1][1] - A.matrix[0][1] * A.matrix[1][0];
  } else {
    matrix_t temp;
    *error_code = s21_create_matrix(A.rows - 1, A.columns - 1, &temp);
    int sign = 1;
    for (int col = 0; col < A.columns && !*error_code; col++) {
      s21_fill_minor_matrix(A, &temp, 0, col);
      result +=
          A.matrix[0][col] * s21_calc_determinant(temp, error_code) * sign;
      sign *= -1;
    }
    if (!*error_code) {
      s21_remove_matrix(&temp);
    }
  }
  return result;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error_code = 0;
  if (!s21_check_matrix(A) && result != NULL) {
    if (A->rows == A->columns) {
      error_code = s21_create_matrix(A->rows, A->columns, result);
      if (!error_code) {
        if (result->rows == 1) {
          result->matrix[0][0] = A->matrix[0][0] ? 1.0 : 0.0;
        } else {
          matrix_t temp;
          error_code =
              s21_create_matrix(result->rows - 1, result->columns - 1, &temp);
          if (!error_code) {
            int sign = 1;
            for (int i = 0; i < result->rows && !error_code; i++) {
              if (i % 2) {
                sign = -1;
              }
              for (int j = 0; j < result->columns && !error_code; j++) {
                s21_fill_minor_matrix(*A, &temp, i, j);
                double det = 0;
                s21_determinant(&temp, &det);
                result->matrix[i][j] = det * sign;
                sign *= -1;
              }
            }
            s21_remove_matrix(&temp);
          } else {
            s21_remove_matrix(result);
          }
        }
      }
    } else {
      error_code = 2;
    }
  } else {
    error_code = 1;
  }
  return error_code;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error_code = 0;
  if (!s21_check_matrix(A) && result != NULL) {
    double det = 0;
    error_code = s21_determinant(A, &det);
    if (det != 0 && !error_code) {
      matrix_t comp;
      error_code = s21_calc_complements(A, &comp);
      if (!error_code) {
        matrix_t comp_trans;
        error_code = s21_transpose(&comp, &comp_trans);
        s21_remove_matrix(&comp);
        if (!error_code) {
          error_code = s21_mult_number(&comp_trans, 1 / det, result);
          s21_remove_matrix(&comp_trans);
        }
      }
    } else {
      error_code = error_code ? error_code : 2;
    }
  } else {
    error_code = 1;
  }
  return error_code;
}

void s21_fill_minor_matrix(matrix_t A, matrix_t *M, int row, int col) {
  int M_row = 0;
  for (int i = 0; i < A.rows; i++) {
    int M_col = 0;
    if (i != row) {
      for (int j = 0; j < A.columns; j++) {
        if (j != col) {
          M->matrix[M_row][M_col] = A.matrix[i][j];
          M_col++;
        }
      }
      M_row++;
    }
  }
}

int s21_check_matrix(matrix_t *A) {
  int error_code = 1;
  if (A != NULL) {
    if (A->matrix != NULL) {
      if (A->rows > 0 && A->columns > 0) {
        error_code = 0;
      }
    }
  }
  return error_code;
}

void free_rows(int rows, matrix_t *A) {
  int i = 0;
  while (i < rows) {
    free(A->matrix[i]);
    i++;
  }
  A->rows = 0;
  A->columns = 0;
}
