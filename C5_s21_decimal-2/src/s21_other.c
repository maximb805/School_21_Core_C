#include "./s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error_code = 0;
  s21_cut_zeros(&value);
  int exp = s21_get_exp(value);
  if (exp) {
    s21_round_precision(&value, exp - 1);
    s21_div_ten(&value);
    s21_set_exp(&value, 0);
    if (s21_dec_is_negative(value)) {
      s21_decimal minus_one;
      s21_from_int_to_decimal(-1, &minus_one);
      s21_add(value, minus_one, &value);
    }
  }
  s21_copy_decimal(&value, result);
  return error_code;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int error_code = 0;
  int exp = s21_get_exp(value);
  if (exp) {
    s21_round_precision(&value, exp);
  }
  s21_copy_decimal(&value, result);
  return error_code;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error_code = 0;
  int exp = s21_get_exp(value);
  while (exp) {
    s21_div_ten(&value);
    exp--;
  }
  s21_set_exp(&value, exp);
  s21_copy_decimal(&value, result);
  return error_code;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error_code = 0;
  value.bits[3] ^= (1 << 31);
  s21_copy_decimal(&value, result);
  return error_code;
}
