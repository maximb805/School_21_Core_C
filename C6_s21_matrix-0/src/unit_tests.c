#include <check.h>

#include "s21_matrix.h"

// EQ TESTS START -->
START_TEST(test_eq1) {
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(5, 5, &matrix1);
  s21_create_matrix(5, 5, &matrix2);
  int result_int;
  result_int = s21_eq_matrix(&matrix1, &matrix2);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_eq2) {
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(5, 5, &matrix1);
  s21_create_matrix(5, 4, &matrix2);
  int result_int;
  result_int = s21_eq_matrix(&matrix1, &matrix2);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_eq3) {
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(5, 5, &matrix1);
  s21_create_matrix(5, 5, &matrix2);
  matrix2.matrix[2][4] = 15.0;
  int result_int;
  result_int = s21_eq_matrix(&matrix1, &matrix2);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_eq4) {
  matrix_t matrix1;
  s21_create_matrix(5, 5, &matrix1);
  int result_int;
  result_int = s21_eq_matrix(&matrix1, NULL);
  s21_remove_matrix(&matrix1);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_eq5) {
  matrix_t matrix1;
  s21_create_matrix(5, 5, &matrix1);
  int result_int;
  result_int = s21_eq_matrix(NULL, &matrix1);
  s21_remove_matrix(&matrix1);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_eq6) {
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(5, 5, &matrix1);
  s21_create_matrix(5, 5, &matrix2);
  matrix1.matrix[2][4] = 15.9999999;
  matrix2.matrix[2][4] = 15.9999998;
  int result_int;
  result_int = s21_eq_matrix(&matrix1, &matrix2);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_eq7) {
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(5, 5, &matrix1);
  s21_create_matrix(5, 5, &matrix2);
  matrix1.matrix[2][4] = 15.99999991;
  matrix2.matrix[2][4] = 15.99999994;
  int result_int;
  result_int = s21_eq_matrix(&matrix1, &matrix2);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_eq8) {
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(5, 5, &matrix1);
  s21_create_matrix(5, 5, &matrix2);
  matrix1.matrix[2][4] = -15.99999991;
  matrix2.matrix[2][4] = -15.99999994;
  int result_int;
  result_int = s21_eq_matrix(&matrix1, &matrix2);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_eq9) {
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(5, 5, &matrix1);
  s21_create_matrix(5, 5, &matrix2);
  matrix1.matrix[2][4] = -15.99999991;
  matrix2.matrix[2][4] = 15.99999994;
  int result_int;
  result_int = s21_eq_matrix(&matrix1, &matrix2);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_eq10) {
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(5, 5, &matrix1);
  s21_create_matrix(5, 5, &matrix2);
  matrix1.matrix[2][4] = 15.99999991;
  matrix2.matrix[2][4] = -15.99999994;
  int result_int;
  result_int = s21_eq_matrix(&matrix1, &matrix2);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_eq11) {
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(5, 5, &matrix1);
  s21_create_matrix(5, 5, &matrix2);
  matrix1.matrix[2][4] = -15.9999999;
  matrix2.matrix[2][4] = -15.9999998;
  int result_int;
  result_int = s21_eq_matrix(&matrix1, &matrix2);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_eq12) {
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(5, 5, &matrix1);
  s21_create_matrix(5, 5, &matrix2);
  matrix1.matrix[2][4] = -15.9999999;
  matrix2.matrix[2][4] = 15.9999998;
  int result_int;
  result_int = s21_eq_matrix(&matrix1, &matrix2);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_eq13) {
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(5, 5, &matrix1);
  s21_create_matrix(5, 5, &matrix2);
  matrix1.matrix[2][4] = 15.9999999;
  matrix2.matrix[2][4] = -15.9999998;
  int result_int;
  result_int = s21_eq_matrix(&matrix1, &matrix2);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_eq14) {
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(5, 5, &matrix1);
  s21_create_matrix(5, 5, &matrix2);
  matrix1.matrix[2][4] = 1.0;
  matrix2.matrix[2][4] = 3.0 / 3.00000000000001;
  int result_int;
  result_int = s21_eq_matrix(&matrix1, &matrix2);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST
// EQ TESTS END <--

// SUM TESTS START -->
START_TEST(test_sum1) {
  matrix_t matrix1;
  matrix_t matrix2;
  matrix_t result;
  matrix_t expected_result;
  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  s21_create_matrix(3, 3, &expected_result);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i;
    }
  }
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] = j;
    }
  }
  for (int i = 0; i < expected_result.rows; i++) {
    for (int j = 0; j < expected_result.columns; j++) {
      expected_result.matrix[i][j] = i + j;
    }
  }
  s21_sum_matrix(&matrix1, &matrix2, &result);
  int result_int;
  result_int = s21_eq_matrix(&result, &expected_result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_sum2) {
  matrix_t matrix1;
  matrix_t matrix2;
  matrix_t result;
  matrix_t expected_result;
  s21_create_matrix(5, 5, &matrix1);
  s21_create_matrix(5, 5, &matrix2);
  s21_create_matrix(5, 5, &expected_result);
  int counter = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = counter;
      counter++;
    }
  }
  counter = 0;
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] = counter;
      counter--;
    }
  }
  s21_sum_matrix(&matrix1, &matrix2, &result);
  int result_int;
  result_int = s21_eq_matrix(&result, &expected_result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_sum_err1) {
  matrix_t matrix1;
  matrix_t matrix2;
  matrix_t result;
  s21_create_matrix(5, 5, &matrix1);
  s21_create_matrix(4, 5, &matrix2);
  int counter = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = counter;
      counter++;
    }
  }
  counter = 0;
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] = counter;
      counter--;
    }
  }
  int result_err;
  result_err = s21_sum_matrix(&matrix1, &matrix2, &result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  ck_assert_int_eq(result_err, 2);
}
END_TEST

START_TEST(test_sum_err2) {
  matrix_t matrix1;
  matrix_t result;
  s21_create_matrix(5, 5, &matrix1);
  int result_err;
  result_err = s21_sum_matrix(&matrix1, NULL, &result);
  s21_remove_matrix(&matrix1);
  ck_assert_int_eq(result_err, 1);
}
END_TEST
// SUM TESTS END <--

// SUB TESTS START -->
START_TEST(test_sub1) {
  matrix_t matrix1;
  matrix_t matrix2;
  matrix_t result;
  matrix_t expected_result;
  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  s21_create_matrix(3, 3, &expected_result);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i;
    }
  }
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] = j;
    }
  }
  for (int i = 0; i < expected_result.rows; i++) {
    for (int j = 0; j < expected_result.columns; j++) {
      expected_result.matrix[i][j] = i - j;
    }
  }
  s21_sub_matrix(&matrix1, &matrix2, &result);
  int result_int;
  result_int = s21_eq_matrix(&result, &expected_result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_sub2) {
  matrix_t matrix1;
  matrix_t matrix2;
  matrix_t result;
  matrix_t expected_result;
  s21_create_matrix(5, 5, &matrix1);
  s21_create_matrix(5, 5, &matrix2);
  s21_create_matrix(5, 5, &expected_result);
  int counter = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = counter;
      counter++;
    }
  }
  counter = 0;
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] = counter;
      counter--;
    }
  }
  counter = 0;
  for (int i = 0; i < expected_result.rows; i++) {
    for (int j = 0; j < expected_result.columns; j++) {
      expected_result.matrix[i][j] = counter + counter;
      counter++;
    }
  }
  s21_sub_matrix(&matrix1, &matrix2, &result);
  int result_int;
  result_int = s21_eq_matrix(&result, &expected_result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_sub_err1) {
  matrix_t matrix1;
  matrix_t matrix2;
  matrix_t result;
  s21_create_matrix(5, 5, &matrix1);
  s21_create_matrix(4, 5, &matrix2);
  int counter = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = counter;
      counter++;
    }
  }
  counter = 0;
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] = counter;
      counter--;
    }
  }
  int result_err;
  result_err = s21_sub_matrix(&matrix1, &matrix2, &result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  ck_assert_int_eq(result_err, 2);
}
END_TEST

START_TEST(test_sub_err2) {
  matrix_t matrix1;
  matrix_t result;
  s21_create_matrix(5, 5, &matrix1);
  int result_err;
  result_err = s21_sub_matrix(&matrix1, NULL, &result);
  s21_remove_matrix(&matrix1);
  ck_assert_int_eq(result_err, 1);
}
END_TEST
// SUB TESTS END <--

// MULT_NUM TESTS START -->
START_TEST(test_mult_num1) {
  matrix_t matrix1;
  matrix_t result;
  matrix_t expected_result;
  s21_create_matrix(5, 5, &matrix1);
  s21_create_matrix(5, 5, &expected_result);
  int counter = 0;
  for (int i = 0; i < expected_result.rows; i++) {
    for (int j = 0; j < expected_result.columns; j++) {
      counter++;
      expected_result.matrix[i][j] = counter * 5.5;
    }
  }
  counter = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      counter++;
      matrix1.matrix[i][j] = counter;
    }
  }
  s21_mult_number(&matrix1, 5.5, &result);
  int result_int = s21_eq_matrix(&result, &expected_result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_mult_num2) {
  matrix_t matrix1;
  matrix_t result;
  matrix_t expected_result;
  s21_create_matrix(5, 5, &matrix1);
  s21_create_matrix(5, 5, &expected_result);
  int counter = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      counter++;
      matrix1.matrix[i][j] = counter;
    }
  }
  s21_mult_number(&matrix1, 0, &result);
  int result_int = s21_eq_matrix(&result, &expected_result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_mult_num_err1) {
  matrix_t result;
  int result_err = s21_mult_number(NULL, 1.1, &result);
  ck_assert_int_eq(result_err, 1);
}
END_TEST

START_TEST(test_mult_num_err2) {
  matrix_t matrix1;
  s21_create_matrix(5, 5, &matrix1);
  int result_err = s21_mult_number(&matrix1, 1.1, NULL);
  s21_remove_matrix(&matrix1);
  ck_assert_int_eq(result_err, 1);
}
END_TEST
// MULT_NUM TESTS END <--

// MULT_MATRIX TESTS START -->
START_TEST(test_mult_matrix1) {
  matrix_t matrix1;
  matrix_t matrix2;
  matrix_t result;
  matrix_t expected_result;
  s21_create_matrix(5, 3, &matrix1);
  s21_create_matrix(3, 5, &matrix2);
  s21_create_matrix(5, 5, &expected_result);
  int counter = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      counter++;
      matrix1.matrix[i][j] = counter;
    }
  }
  counter = 0;
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      counter++;
      matrix2.matrix[i][j] = counter;
    }
  }
  expected_result.matrix[0][0] = 46.0;
  expected_result.matrix[0][1] = 52.0;
  expected_result.matrix[0][2] = 58.0;
  expected_result.matrix[0][3] = 64.0;
  expected_result.matrix[0][4] = 70.0;
  expected_result.matrix[1][0] = 100.0;
  expected_result.matrix[1][1] = 115.0;
  expected_result.matrix[1][2] = 130.0;
  expected_result.matrix[1][3] = 145.0;
  expected_result.matrix[1][4] = 160.0;
  expected_result.matrix[2][0] = 154.0;
  expected_result.matrix[2][1] = 178.0;
  expected_result.matrix[2][2] = 202.0;
  expected_result.matrix[2][3] = 226.0;
  expected_result.matrix[2][4] = 250.0;
  expected_result.matrix[3][0] = 208.0;
  expected_result.matrix[3][1] = 241.0;
  expected_result.matrix[3][2] = 274.0;
  expected_result.matrix[3][3] = 307.0;
  expected_result.matrix[3][4] = 340.0;
  expected_result.matrix[4][0] = 262.0;
  expected_result.matrix[4][1] = 304.0;
  expected_result.matrix[4][2] = 346.0;
  expected_result.matrix[4][3] = 388.0;
  expected_result.matrix[4][4] = 430.0;
  s21_mult_matrix(&matrix1, &matrix2, &result);
  int result_int = s21_eq_matrix(&result, &expected_result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_mult_matrix2) {
  matrix_t matrix1;
  matrix_t matrix2;
  matrix_t result;
  matrix_t expected_result;
  s21_create_matrix(3, 4, &matrix1);
  s21_create_matrix(4, 3, &matrix2);
  s21_create_matrix(3, 3, &expected_result);
  int counter = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      counter++;
      matrix1.matrix[i][j] = counter * 1.2;
    }
  }
  s21_mult_matrix(&matrix1, &matrix2, &result);
  int result_int = s21_eq_matrix(&result, &expected_result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_mult_matrix3) {
  matrix_t matrix1;
  matrix_t matrix2;
  matrix_t result;
  matrix_t expected_result;
  s21_create_matrix(5, 4, &matrix1);
  s21_create_matrix(4, 2, &matrix2);
  s21_create_matrix(5, 2, &expected_result);
  int counter = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      counter++;
      matrix1.matrix[i][j] = counter * 1.2;
    }
  }
  counter = 0;
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      counter++;
      matrix2.matrix[i][j] = counter * -2.8;
    }
  }
  expected_result.matrix[0][0] = -168;
  expected_result.matrix[0][1] = -201.6;
  expected_result.matrix[1][0] = -383.04;
  expected_result.matrix[1][1] = -470.4;
  expected_result.matrix[2][0] = -598.08;
  expected_result.matrix[2][1] = -739.2;
  expected_result.matrix[3][0] = -813.12;
  expected_result.matrix[3][1] = -1008;
  expected_result.matrix[4][0] = -1028.16;
  expected_result.matrix[4][1] = -1276.8;
  s21_mult_matrix(&matrix1, &matrix2, &result);
  int result_int = s21_eq_matrix(&result, &expected_result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_mult_matrix4) {
  matrix_t matrix1;
  matrix_t matrix2;
  matrix_t result;
  matrix_t expected_result;
  s21_create_matrix(1, 1, &matrix1);
  s21_create_matrix(1, 1, &matrix2);
  s21_create_matrix(1, 1, &expected_result);
  matrix1.matrix[0][0] = 5.0;
  matrix2.matrix[0][0] = 7.0;
  expected_result.matrix[0][0] = 35.0;
  s21_mult_matrix(&matrix1, &matrix2, &result);
  int result_int = s21_eq_matrix(&result, &expected_result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_mult_matrix_err1) {
  matrix_t result;
  matrix_t matrix2;
  s21_create_matrix(2, 2, &matrix2);
  int result_err = s21_mult_matrix(NULL, &matrix2, &result);
  ck_assert_int_eq(result_err, 1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(test_mult_matrix_err2) {
  matrix_t result;
  matrix_t matrix1;
  s21_create_matrix(2, 2, &matrix1);
  int result_err = s21_mult_matrix(&matrix1, NULL, &result);
  ck_assert_int_eq(result_err, 1);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(test_mult_matrix_err3) {
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(2, 2, &matrix1);
  s21_create_matrix(2, 2, &matrix2);
  int result_err = s21_mult_matrix(&matrix1, &matrix2, NULL);
  ck_assert_int_eq(result_err, 1);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(test_mult_matrix_err4) {
  matrix_t result;
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(4, 4, &matrix2);
  int result_err = s21_mult_matrix(&matrix1, &matrix2, &result);
  ck_assert_int_eq(result_err, 2);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST
// MULT_MATRIX TESTS END <--

// TRANSPOSE TESTS START -->
START_TEST(test_transpose1) {
  matrix_t matrix1;
  matrix_t result;
  matrix_t expected_result;
  s21_create_matrix(5, 4, &matrix1);
  s21_create_matrix(4, 5, &expected_result);
  int counter = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      counter++;
      matrix1.matrix[i][j] = counter;
    }
  }
  counter = 0;
  for (int j = 0; j < expected_result.columns; j++) {
    for (int i = 0; i < expected_result.rows; i++) {
      counter++;
      expected_result.matrix[i][j] = counter;
    }
  }
  s21_transpose(&matrix1, &result);
  int result_int = s21_eq_matrix(&result, &expected_result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_transpose2) {
  matrix_t matrix1;
  matrix_t result;
  matrix_t expected_result;
  s21_create_matrix(1, 5, &matrix1);
  s21_create_matrix(5, 1, &expected_result);
  int counter = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      counter++;
      matrix1.matrix[i][j] = counter;
    }
  }
  expected_result.matrix[0][0] = 1.0;
  expected_result.matrix[1][0] = 2.0;
  expected_result.matrix[2][0] = 3.0;
  expected_result.matrix[3][0] = 4.0;
  expected_result.matrix[4][0] = 5.0;
  s21_transpose(&matrix1, &result);
  int result_int = s21_eq_matrix(&result, &expected_result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_transpose3) {
  matrix_t matrix1;
  matrix_t result;
  matrix_t expected_result;
  s21_create_matrix(1, 1, &matrix1);
  s21_create_matrix(1, 1, &expected_result);
  matrix1.matrix[0][0] = 5;
  expected_result.matrix[0][0] = 5;
  s21_transpose(&matrix1, &result);
  int result_int = s21_eq_matrix(&result, &expected_result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_transpose_err1) {
  matrix_t matrix1;
  s21_create_matrix(3, 3, &matrix1);
  int result_err = s21_transpose(&matrix1, NULL);
  ck_assert_int_eq(result_err, 1);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(test_transpose_err2) {
  matrix_t result;
  int result_err = s21_transpose(NULL, &result);
  ck_assert_int_eq(result_err, 1);
}
END_TEST
// TRANSPOSE TESTS END <--

// DETERMINANT TESTS START -->
START_TEST(test_determinant1) {
  matrix_t matrix1;
  double result;
  double expected_result = 0;
  s21_create_matrix(5, 5, &matrix1);
  int counter = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      counter++;
      matrix1.matrix[i][j] = counter * 1.2;
    }
  }
  s21_determinant(&matrix1, &result);
  s21_remove_matrix(&matrix1);
  ck_assert_double_eq_tol(result, expected_result, 1E-7);
}
END_TEST

START_TEST(test_determinant2) {
  matrix_t matrix1;
  double result;
  double expected_result = -82978775.55372475;
  s21_create_matrix(3, 3, &matrix1);
  matrix1.matrix[0][0] = 127.0;
  matrix1.matrix[0][1] = 2476.7;
  matrix1.matrix[0][2] = 845.673;
  matrix1.matrix[1][0] = -161.67;
  matrix1.matrix[1][1] = 516.23;
  matrix1.matrix[1][2] = -1.341;
  matrix1.matrix[2][0] = 0;
  matrix1.matrix[2][1] = 651.225;
  matrix1.matrix[2][2] = 12.76;
  s21_determinant(&matrix1, &result);
  s21_remove_matrix(&matrix1);
  ck_assert_double_eq_tol(result, expected_result, 1E-7);
}
END_TEST

START_TEST(test_determinant3) {
  matrix_t matrix1;
  double result;
  double expected_result = 5.5;
  s21_create_matrix(1, 1, &matrix1);
  matrix1.matrix[0][0] = 5.5;
  s21_determinant(&matrix1, &result);
  s21_remove_matrix(&matrix1);
  ck_assert_double_eq_tol(result, expected_result, 1E-7);
}
END_TEST

START_TEST(test_determinant_err1) {
  matrix_t matrix1;
  double result;
  s21_create_matrix(3, 4, &matrix1);
  int result_err = s21_determinant(&matrix1, &result);
  ck_assert_int_eq(result_err, 2);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(test_determinant_err2) {
  double result;
  int result_err = s21_determinant(NULL, &result);
  ck_assert_int_eq(result_err, 1);
}
END_TEST

START_TEST(test_determinant_err3) {
  matrix_t matrix1;
  s21_create_matrix(4, 4, &matrix1);
  int result_err = s21_determinant(&matrix1, NULL);
  ck_assert_int_eq(result_err, 1);
  s21_remove_matrix(&matrix1);
}
END_TEST
// DETERMINANT TESTS END <--

// COMPLEMENTS TESTS START -->
START_TEST(test_complements1) {
  matrix_t matrix1;
  matrix_t result;
  matrix_t expected_result;
  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &expected_result);

  matrix1.matrix[0][0] = 0.73;
  matrix1.matrix[0][1] = -0.19;
  matrix1.matrix[0][2] = -0.12;
  matrix1.matrix[1][0] = -0.07;
  matrix1.matrix[1][1] = 0.72;
  matrix1.matrix[1][2] = -0.17;
  matrix1.matrix[2][0] = -0.12;
  matrix1.matrix[2][1] = -0.15;
  matrix1.matrix[2][2] = -0.92;

  expected_result.matrix[0][0] = -0.6879;
  expected_result.matrix[0][1] = -0.044;
  expected_result.matrix[0][2] = 0.0969;
  expected_result.matrix[1][0] = -0.1568;
  expected_result.matrix[1][1] = -0.686;
  expected_result.matrix[1][2] = 0.1323;
  expected_result.matrix[2][0] = 0.1187;
  expected_result.matrix[2][1] = 0.1325;
  expected_result.matrix[2][2] = 0.5123;

  s21_calc_complements(&matrix1, &result);
  int result_int = s21_eq_matrix(&result, &expected_result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_complements2) {
  matrix_t matrix1;
  matrix_t result;
  matrix_t expected_result;
  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &expected_result);

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[0][2] = 3;
  matrix1.matrix[1][0] = 0;
  matrix1.matrix[1][1] = 4;
  matrix1.matrix[1][2] = 2;
  matrix1.matrix[2][0] = 5;
  matrix1.matrix[2][1] = 2;
  matrix1.matrix[2][2] = 1;

  expected_result.matrix[0][0] = 0;
  expected_result.matrix[0][1] = 10;
  expected_result.matrix[0][2] = -20;
  expected_result.matrix[1][0] = 4;
  expected_result.matrix[1][1] = -14;
  expected_result.matrix[1][2] = -8;
  expected_result.matrix[2][0] = -8;
  expected_result.matrix[2][1] = -2;
  expected_result.matrix[2][2] = 4;

  s21_calc_complements(&matrix1, &result);
  int result_int = s21_eq_matrix(&result, &expected_result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_complements3) {
  matrix_t matrix1;
  matrix_t result;
  matrix_t expected_result;
  s21_create_matrix(2, 2, &matrix1);
  s21_create_matrix(2, 2, &expected_result);

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[1][0] = 0;
  matrix1.matrix[1][1] = 4;

  expected_result.matrix[0][0] = 4;
  expected_result.matrix[0][1] = 0;
  expected_result.matrix[1][0] = -2;
  expected_result.matrix[1][1] = 1;

  s21_calc_complements(&matrix1, &result);
  int result_int = s21_eq_matrix(&result, &expected_result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_complements4) {
  matrix_t matrix1;
  matrix_t result;
  matrix_t expected_result;
  s21_create_matrix(1, 1, &matrix1);
  s21_create_matrix(1, 1, &expected_result);
  matrix1.matrix[0][0] = -8;
  expected_result.matrix[0][0] = 1;
  s21_calc_complements(&matrix1, &result);
  int result_int = s21_eq_matrix(&result, &expected_result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_complements_err1) {
  matrix_t matrix1;
  matrix_t result;
  s21_create_matrix(3, 4, &matrix1);
  int result_err = s21_calc_complements(&matrix1, &result);
  ck_assert_int_eq(result_err, 2);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(test_complements_err2) {
  matrix_t result;
  int result_err = s21_calc_complements(NULL, &result);
  ck_assert_int_eq(result_err, 1);
}
END_TEST

START_TEST(test_complements_err3) {
  matrix_t matrix1;
  s21_create_matrix(4, 4, &matrix1);
  int result_err = s21_calc_complements(&matrix1, NULL);
  ck_assert_int_eq(result_err, 1);
  s21_remove_matrix(&matrix1);
}
END_TEST
// COMPLEMENTS TESTS END <--

// INVERSE TESTS START -->
START_TEST(test_inverse1) {
  matrix_t matrix1;
  matrix_t result;
  matrix_t expected_result;
  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &expected_result);

  matrix1.matrix[0][0] = 0.73;
  matrix1.matrix[0][1] = -0.19;
  matrix1.matrix[0][2] = -0.12;
  matrix1.matrix[1][0] = -0.07;
  matrix1.matrix[1][1] = 0.72;
  matrix1.matrix[1][2] = -0.17;
  matrix1.matrix[2][0] = -0.12;
  matrix1.matrix[2][1] = -0.15;
  matrix1.matrix[2][2] = -0.92;

  expected_result.matrix[0][0] = 1.3610058662;
  expected_result.matrix[0][1] = 0.3102278236;
  expected_result.matrix[0][2] = -0.2348472108;
  expected_result.matrix[1][0] = 0.0870537260;
  expected_result.matrix[1][1] = 1.3572467281;
  expected_result.matrix[1][2] = -0.2621504249;
  expected_result.matrix[2][0] = -0.1917160466;
  expected_result.matrix[2][1] = -0.2617547261;
  expected_result.matrix[2][2] = -1.0135823597;

  s21_inverse_matrix(&matrix1, &result);
  int result_int = s21_eq_matrix(&result, &expected_result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_inverse2) {
  matrix_t matrix1;
  matrix_t result;
  matrix_t expected_result;
  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &expected_result);

  matrix1.matrix[0][0] = 2;
  matrix1.matrix[0][1] = 5;
  matrix1.matrix[0][2] = 7;
  matrix1.matrix[1][0] = 6;
  matrix1.matrix[1][1] = 3;
  matrix1.matrix[1][2] = 4;
  matrix1.matrix[2][0] = 5;
  matrix1.matrix[2][1] = -2;
  matrix1.matrix[2][2] = -3;

  expected_result.matrix[0][0] = 1;
  expected_result.matrix[0][1] = -1;
  expected_result.matrix[0][2] = 1;
  expected_result.matrix[1][0] = -38;
  expected_result.matrix[1][1] = 41;
  expected_result.matrix[1][2] = -34;
  expected_result.matrix[2][0] = 27;
  expected_result.matrix[2][1] = -29;
  expected_result.matrix[2][2] = 24;

  s21_inverse_matrix(&matrix1, &result);
  int result_int = s21_eq_matrix(&result, &expected_result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_inverse3) {
  matrix_t matrix1;
  matrix_t result;
  matrix_t expected_result;
  s21_create_matrix(2, 2, &matrix1);
  s21_create_matrix(2, 2, &expected_result);

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[1][0] = 0;
  matrix1.matrix[1][1] = 4;

  expected_result.matrix[0][0] = 1;
  expected_result.matrix[0][1] = -0.5;
  expected_result.matrix[1][0] = 0;
  expected_result.matrix[1][1] = 0.25;

  s21_inverse_matrix(&matrix1, &result);
  int result_int = s21_eq_matrix(&result, &expected_result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_inverse4) {
  matrix_t matrix1;
  matrix_t result;
  matrix_t expected_result;
  s21_create_matrix(1, 1, &matrix1);
  s21_create_matrix(1, 1, &expected_result);
  matrix1.matrix[0][0] = -8;
  expected_result.matrix[0][0] = -1 / 8.0;
  s21_inverse_matrix(&matrix1, &result);
  int result_int = s21_eq_matrix(&result, &expected_result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_inverse5) {
  matrix_t matrix1;
  matrix_t result;
  matrix_t expected_result;
  s21_create_matrix(1, 1, &matrix1);
  s21_create_matrix(1, 1, &expected_result);
  matrix1.matrix[0][0] = 1;
  expected_result.matrix[0][0] = 1;
  s21_inverse_matrix(&matrix1, &result);
  int result_int = s21_eq_matrix(&result, &expected_result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_inverse_err1) {
  matrix_t matrix1;
  matrix_t result;
  s21_create_matrix(3, 4, &matrix1);
  int result_err = s21_inverse_matrix(&matrix1, &result);
  ck_assert_int_eq(result_err, 2);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(test_inverse_err2) {
  matrix_t result;
  int result_err = s21_inverse_matrix(NULL, &result);
  ck_assert_int_eq(result_err, 1);
}
END_TEST

START_TEST(test_inverse_err3) {
  matrix_t matrix1;
  s21_create_matrix(4, 4, &matrix1);
  int result_err = s21_inverse_matrix(&matrix1, NULL);
  ck_assert_int_eq(result_err, 1);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(test_inverse_err4) {
  matrix_t matrix1;
  matrix_t result;
  s21_create_matrix(2, 2, &matrix1);
  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[1][0] = 2;
  matrix1.matrix[1][1] = 4;
  int result_err = s21_inverse_matrix(&matrix1, &result);
  ck_assert_int_eq(result_err, 2);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(test_inverse_err5) {
  matrix_t matrix1;
  matrix_t result;
  s21_create_matrix(1, 1, &matrix1);
  matrix1.matrix[0][0] = 0;
  int result_err = s21_inverse_matrix(&matrix1, &result);
  ck_assert_int_eq(result_err, 2);
  s21_remove_matrix(&matrix1);
}
END_TEST
// INVERSE TESTS END <--

Suite *suite_insert(void) {
  Suite *s = suite_create("Start tests");
  TCase *tc = tcase_create("insert_tc");

  // EQ TESTS START -->
  tcase_add_test(tc, test_eq1);
  tcase_add_test(tc, test_eq2);
  tcase_add_test(tc, test_eq3);
  tcase_add_test(tc, test_eq4);
  tcase_add_test(tc, test_eq5);
  tcase_add_test(tc, test_eq6);
  tcase_add_test(tc, test_eq7);
  tcase_add_test(tc, test_eq8);
  tcase_add_test(tc, test_eq9);
  tcase_add_test(tc, test_eq10);
  tcase_add_test(tc, test_eq11);
  tcase_add_test(tc, test_eq12);
  tcase_add_test(tc, test_eq13);
  tcase_add_test(tc, test_eq14);
  // EQ TESTS END <--

  // SUM TESTS START -->
  tcase_add_test(tc, test_sum1);
  tcase_add_test(tc, test_sum2);
  tcase_add_test(tc, test_sum_err1);
  tcase_add_test(tc, test_sum_err2);
  // SUM TESTS END <--

  // SUB TESTS START -->
  tcase_add_test(tc, test_sub1);
  tcase_add_test(tc, test_sub2);
  tcase_add_test(tc, test_sub_err1);
  tcase_add_test(tc, test_sub_err2);
  // SUB TESTS END <--

  // MULT_NUM TESTS START -->
  tcase_add_test(tc, test_mult_num1);
  tcase_add_test(tc, test_mult_num2);
  tcase_add_test(tc, test_mult_num_err1);
  tcase_add_test(tc, test_mult_num_err2);
  // MULT_NUM TESTS END <--

  // MULT_MATRIX TESTS START -->
  tcase_add_test(tc, test_mult_matrix1);
  tcase_add_test(tc, test_mult_matrix2);
  tcase_add_test(tc, test_mult_matrix3);
  tcase_add_test(tc, test_mult_matrix4);
  tcase_add_test(tc, test_mult_matrix_err1);
  tcase_add_test(tc, test_mult_matrix_err2);
  tcase_add_test(tc, test_mult_matrix_err3);
  tcase_add_test(tc, test_mult_matrix_err4);
  // MULT_MATRIX TESTS END <--

  // TRANSPOSE TESTS START -->
  tcase_add_test(tc, test_transpose1);
  tcase_add_test(tc, test_transpose2);
  tcase_add_test(tc, test_transpose3);
  tcase_add_test(tc, test_transpose_err1);
  tcase_add_test(tc, test_transpose_err2);
  // TRANSPOSE TESTS END <--

  // DETERMINANT TESTS START -->
  tcase_add_test(tc, test_determinant1);
  tcase_add_test(tc, test_determinant2);
  tcase_add_test(tc, test_determinant3);
  tcase_add_test(tc, test_determinant_err1);
  tcase_add_test(tc, test_determinant_err2);
  tcase_add_test(tc, test_determinant_err3);
  // DETERMINANT TESTS END <--

  // COMPLEMENTS TESTS START -->
  tcase_add_test(tc, test_complements1);
  tcase_add_test(tc, test_complements2);
  tcase_add_test(tc, test_complements3);
  tcase_add_test(tc, test_complements4);
  tcase_add_test(tc, test_complements_err1);
  tcase_add_test(tc, test_complements_err2);
  tcase_add_test(tc, test_complements_err3);
  // COMPLEMENTS TESTS END <--

  // INVERSE TESTS START -->
  tcase_add_test(tc, test_inverse1);
  tcase_add_test(tc, test_inverse2);
  tcase_add_test(tc, test_inverse3);
  tcase_add_test(tc, test_inverse4);
  tcase_add_test(tc, test_inverse5);
  tcase_add_test(tc, test_inverse_err1);
  tcase_add_test(tc, test_inverse_err2);
  tcase_add_test(tc, test_inverse_err3);
  tcase_add_test(tc, test_inverse_err4);
  tcase_add_test(tc, test_inverse_err5);
  // INVERSE TESTS END <--

  suite_add_tcase(s, tc);
  return s;
}

int main(void) {
  Suite *s1;
  SRunner *sr;
  s1 = suite_insert();
  sr = srunner_create(s1);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);
  srunner_free(sr);
  return 0;
}
