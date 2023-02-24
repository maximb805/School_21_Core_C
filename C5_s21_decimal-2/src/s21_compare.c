#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int result = s21_compare_decimals(value_1, value_2);
  return result == 1;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = s21_compare_decimals(value_1, value_2);
  return result == 1 || result == 0;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int result = s21_compare_decimals(value_1, value_2);
  return result == -1;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = s21_compare_decimals(value_1, value_2);
  return result == -1 || result == 0;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = s21_compare_decimals(value_1, value_2);
  return result == 0;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = s21_compare_decimals(value_1, value_2);
  return result != 0;
}

int s21_compare_decimals(s21_decimal value_1, s21_decimal value_2) {
  int result;
  s21_buffer_decimal buffer1;
  s21_buffer_decimal buffer2;
  s21_decimal_to_buffer(value_1, &buffer1);
  s21_decimal_to_buffer(value_2, &buffer2);
  result = s21_compare_buffers(buffer1, buffer2);
  return result;
}

int s21_compare_buffers(s21_buffer_decimal buffer1,
                        s21_buffer_decimal buffer2) {
  int result;
  s21_buffer_check_zero(&buffer1);
  s21_buffer_check_zero(&buffer2);
  if (s21_buffer_is_negative(buffer1)) {
    if (s21_buffer_is_negative(buffer2)) {
      result = s21_compare_bits(buffer1, buffer2);
      result *= -1;
    } else {
      result = 1;
    }
  } else {
    if (s21_buffer_is_negative(buffer2)) {
      result = -1;
    } else {
      result = s21_compare_bits(buffer1, buffer2);
    }
  }
  return result;
}

int s21_compare_bits(s21_buffer_decimal value_1, s21_buffer_decimal value_2) {
  int result = 0;
  s21_buffer_exp_equalizer(&value_1, &value_2);
  for (int i = 5; i >= 0 && !result; i--) {
    if (value_1.bits[i] != value_2.bits[i]) {
      if ((unsigned int)value_1.bits[i] > (unsigned int)value_2.bits[i]) {
        result = -1;
      } else {
        result = 1;
      }
    }
  }
  return result;
}
