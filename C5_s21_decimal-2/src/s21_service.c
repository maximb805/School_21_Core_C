#include "./s21_decimal.h"

void s21_zero_decimal(s21_decimal *decimal) {
  for (int j = 0; j < 4; j++) {
    decimal->bits[j] = 0;
  }
}

void s21_multiply_by_ten(s21_decimal *dst) {
  long long int buffer;
  unsigned int overflow = 0;
  for (int i = 0; i < 3; i++) {
    buffer = (unsigned int)dst->bits[i];
    buffer *= 10;
    buffer += overflow;
    overflow = buffer >> 32;
    dst->bits[i] = (unsigned int)buffer;
  }
}

int s21_mod_ten(s21_decimal src) {
  long long int buffer = (unsigned int)src.bits[2];
  for (int i = 2; i >= 0; i--) {
    buffer = buffer % 10;
    if (i) {
      buffer = buffer << 32;
      buffer += (unsigned int)src.bits[i - 1];
    }
  }
  return (int)buffer;
}

void s21_div_ten(s21_decimal *src) {
  long long int buffer = (unsigned int)src->bits[2];
  long long int mod_res;
  for (int i = 2; i >= 0; i--) {
    mod_res = buffer % 10;
    src->bits[i] = (unsigned int)(buffer / 10);
    if (i) {
      buffer = mod_res << 32;
      buffer += (unsigned int)src->bits[i - 1];
    }
  }
}

int s21_get_exp(s21_decimal src) {
  src.bits[3] &= ~(1 << 31);
  return src.bits[3] >> 16;
}

int s21_is_zero(s21_decimal src) {
  return src.bits[0] == 0 && src.bits[1] == 0 && src.bits[2] == 0;
}

int s21_dec_is_negative(s21_decimal src) {
  return (src.bits[3] &= 1 << 31) != 0;
}

void s21_cut_zeros(s21_decimal *src) {
  int exp = s21_get_exp(*src);
  while (exp && !s21_mod_ten(*src)) {
    s21_div_ten(src);
    s21_set_exp(src, --exp);
  }
}

void s21_set_exp(s21_decimal *src, int exp) {
  exp = exp << 16;
  if (s21_dec_is_negative(*src)) {
    exp |= 1 << 31;
  }
  src->bits[3] = exp;
}

void s21_copy_decimal(s21_decimal *src, s21_decimal *dst) {
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = src->bits[i];
  }
}

void s21_round_precision(s21_decimal *src, int digits_count) {
  if (digits_count) {
    int exp = s21_get_exp(*src);
    while (digits_count > 1) {
      s21_div_ten(src);
      digits_count--;
      exp--;
    }
    int mod_res = s21_mod_ten(*src);
    s21_div_ten(src);
    exp--;
    if (mod_res > 4) {
      s21_decimal one;
      if (s21_dec_is_negative(*src)) {
        s21_from_int_to_decimal(-1, &one);
      } else {
        s21_from_int_to_decimal(1, &one);
      }
      s21_set_exp(src, exp);
      s21_add(*src, one, src);
    } else {
      s21_set_exp(src, exp);
    }
  }
}

void s21_decimal_abs(s21_decimal *src) { src->bits[3] &= ~(1 << 31); }
