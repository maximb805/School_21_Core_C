#include "./s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error_code = 0;
  s21_buffer_decimal buffer1;
  s21_buffer_decimal buffer2;
  s21_buffer_decimal result_buffer;
  int sign_1 = s21_dec_is_negative(value_1);
  int sign_2 = s21_dec_is_negative(value_2);
  if (sign_1 == sign_2) {
    s21_decimal_to_buffer(value_1, &buffer1);
    s21_decimal_to_buffer(value_2, &buffer2);
    s21_buffer_abs(&buffer1);
    s21_buffer_abs(&buffer2);
    s21_buffer_add(buffer1, buffer2, &result_buffer);
    if (sign_1) {
      s21_buffer_negate(&result_buffer);
    }
    error_code = s21_buffer_to_decimal(result_buffer, result);
  } else {
    s21_negate(value_2, &value_2);
    error_code = s21_sub(value_1, value_2, result);
  }
  return error_code;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error_code = 0;
  s21_buffer_decimal buffer1;
  s21_buffer_decimal buffer2;
  s21_buffer_decimal result_buffer;
  int sign_1 = s21_dec_is_negative(value_1);
  int sign_2 = s21_dec_is_negative(value_2);
  if (sign_1 == sign_2) {
    s21_decimal_to_buffer(value_1, &buffer1);
    s21_decimal_to_buffer(value_2, &buffer2);
    s21_buffer_abs(&buffer1);
    s21_buffer_abs(&buffer2);
    s21_decimal_abs(&value_1);
    s21_decimal_abs(&value_2);
    if (s21_is_greater_or_equal(value_1, value_2)) {
      s21_buffer_sub(buffer1, buffer2, &result_buffer);
      if (sign_1) {
        s21_buffer_negate(&result_buffer);
      }
    } else {
      s21_buffer_sub(buffer2, buffer1, &result_buffer);
      if (!sign_1) {
        s21_buffer_negate(&result_buffer);
      }
    }
    error_code = s21_buffer_to_decimal(result_buffer, result);
  } else {
    s21_negate(value_2, &value_2);
    error_code = s21_add(value_1, value_2, result);
  }
  return error_code;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error_code = 0;
  s21_buffer_decimal buffer1;
  s21_buffer_decimal buffer2;
  s21_buffer_decimal result_buffer;
  s21_decimal_to_buffer(value_1, &buffer1);
  s21_decimal_to_buffer(value_2, &buffer2);
  s21_buffer_mul(buffer1, buffer2, &result_buffer);
  s21_cut_buffer_zeros(&result_buffer);
  error_code = s21_buffer_to_decimal(result_buffer, result);
  return error_code;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error_code = 0;
  if (s21_is_zero(value_2)) {
    error_code = 3;
  } else {
    s21_buffer_decimal buffer1;
    s21_buffer_decimal buffer2;
    s21_buffer_decimal result_buffer;
    s21_decimal_to_buffer(value_1, &buffer1);
    s21_decimal_to_buffer(value_2, &buffer2);
    s21_buffer_div(buffer1, buffer2, &result_buffer);
    error_code = s21_buffer_to_decimal(result_buffer, result);
  }
  return error_code;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error_code = 0;
  if (s21_is_zero(value_2)) {
    error_code = 3;
  } else {
    s21_buffer_decimal buffer1;
    s21_buffer_decimal buffer2;
    s21_buffer_decimal result_buffer;
    s21_decimal_to_buffer(value_1, &buffer1);
    s21_decimal_to_buffer(value_2, &buffer2);
    result_buffer = s21_buffer_div(buffer1, buffer2, &result_buffer);
    error_code = s21_buffer_to_decimal(result_buffer, result);
    if (s21_buffer_is_negative(buffer1) && !error_code) {
      s21_negate(*result, result);
    }
  }
  return error_code;
}
