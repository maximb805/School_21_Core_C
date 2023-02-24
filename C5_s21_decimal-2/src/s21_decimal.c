#include "./s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error_code = 0;
  s21_zero_decimal(dst);
  if (src < 0) {
    s21_negate(*dst, dst);
    src *= -1;
  }
  dst->bits[0] = src;
  return error_code;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error_code = 0;
  if (src != src || fabs(src) > MAX_DECIMAL) {
    error_code = 1;
  } else if (fabs(src) < 1e-28 && fabs(src) > 0) {
    error_code = 1;
    s21_zero_decimal(dst);
  } else {
    double result = src;
    int exp = 0;
    s21_zero_decimal(dst);
    if (result < 0) {
      s21_negate(*dst, dst);
      result *= -1.0;
    }
    while (result < 999999.9 && exp < 28) {
      exp++;
      result *= 10;
    }
    while (result >= 9999999.9) {
      result /= 10;
      exp--;
    }
    dst->bits[0] = (int)round(result);
    if (exp > 0) {
      s21_set_exp(dst, exp);
    }
    while (exp < 0) {
      s21_multiply_by_ten(dst);
      exp++;
    }
    s21_cut_zeros(dst);
  }
  return error_code;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error_code = 0;
  s21_truncate(src, &src);
  *dst = src.bits[0];
  if (s21_dec_is_negative(src)) {
    *dst *= -1;
  }
  return error_code;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error_code = 0;
  double result = 0;
  for (int i = 2; i >= 0; i--) {
    result *= pow(2, 32);
    result += (unsigned int)src.bits[i];
  }
  int exp = s21_get_exp(src);
  result /= pow(10, exp);
  *dst = (float)result;
  if (s21_dec_is_negative(src)) {
    *dst *= -1;
  }
  return error_code;
}
