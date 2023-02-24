#include "s21_decimal.h"

int s21_get_buffer_exp(s21_buffer_decimal src) {
  return (src.bits[6] & ~(1 << 31)) >> 16;
}

void s21_set_buffer_exp(s21_buffer_decimal *src, int exp) {
  exp = exp << 16;
  if (s21_buffer_is_negative(*src)) {
    exp |= 1 << 31;
  }
  src->bits[6] = exp;
}

int s21_buffer_is_negative(s21_buffer_decimal src) { return src.bits[6] < 0; }

void s21_copy_buffer(s21_buffer_decimal src, s21_buffer_decimal *dst) {
  for (int i = 0; i < 7; i++) {
    dst->bits[i] = src.bits[i];
  }
}

void s21_decimal_to_buffer(s21_decimal src, s21_buffer_decimal *dst) {
  s21_zero_buffer(dst);
  for (int i = 0; i < 3; i++) {
    dst->bits[i] = src.bits[i];
  }
  dst->bits[6] = src.bits[3];
}

void s21_zero_buffer(s21_buffer_decimal *result) {
  for (int i = 0; i < 7; i++) {
    result->bits[i] = 0;
  }
}

int s21_buffer_is_zero(s21_buffer_decimal src) {
  int result = 1;
  for (int i = 0; i < 6 && result; i++) {
    if (src.bits[i]) {
      result = 0;
    }
  }
  return result;
}

void s21_buffer_negate(s21_buffer_decimal *src) { src->bits[6] ^= (1 << 31); }

void s21_buffer_mul(s21_buffer_decimal value_1, s21_buffer_decimal value_2,
                    s21_buffer_decimal *result) {
  unsigned long long int buffer = 0;
  unsigned int overflow = 0;
  int result_exp = s21_get_buffer_exp(value_1) + s21_get_buffer_exp(value_2);
  int result_sign =
      s21_buffer_is_negative(value_1) ^ s21_buffer_is_negative(value_2);
  s21_buffer_decimal temp1;
  s21_buffer_decimal temp2;
  s21_zero_buffer(&temp1);
  s21_zero_buffer(&temp2);
  s21_zero_buffer(result);
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      buffer = (unsigned int)value_1.bits[j];
      buffer *= (unsigned int)value_2.bits[i];
      buffer += overflow;
      overflow = (unsigned long long int)buffer >> 32;
      temp1.bits[j] = (unsigned int)buffer;
    }
    s21_shift_temp(&temp1, i);
    s21_buffer_bits_add(temp2, temp1, &temp2);
  }
  s21_set_buffer_exp(&temp2, result_exp);
  if (result_sign) {
    s21_buffer_negate(&temp2);
  }
  s21_copy_buffer(temp2, result);
}

s21_buffer_decimal s21_buffer_div(s21_buffer_decimal value_1,
                                  s21_buffer_decimal value_2,
                                  s21_buffer_decimal *result) {
  s21_zero_buffer(result);
  int result_sign =
      s21_buffer_is_negative(value_1) ^ s21_buffer_is_negative(value_2);
  s21_buffer_decimal real_mod = {{0, 0, 0, 0, 0, 0, 0}};
  s21_buffer_abs(&value_1);
  s21_buffer_abs(&value_2);
  s21_buffer_decimal one = {{1, 0, 0, 0, 0, 0, 0}};
  if (!s21_buffer_is_zero(value_1)) {
    if (!s21_compare_buffers(value_1, value_2)) {
      result->bits[0] = 1;
    } else {
      s21_buffer_exp_equalizer(&value_1, &value_2);
      int exp = s21_get_buffer_exp(value_1);
      s21_set_buffer_exp(&value_1, 0);
      s21_set_buffer_exp(&value_2, 0);
      if (!s21_compare_buffers(value_2, one)) {
        *result = value_1;
      } else {
        if (s21_compare_buffers(value_1, value_2) < 0) {
          s21_buffer_add(value_1, one, result);
          s21_buffer_div_two(result);
          s21_search_int_div_ans(value_1, one, value_1, value_2, result);
        }
        s21_buffer_decimal mod;
        s21_buffer_decimal mul_result;
        s21_buffer_mul(*result, value_2, &mul_result);
        s21_buffer_sub(value_1, mul_result, &mod);
        real_mod = mod;
        s21_set_buffer_exp(&real_mod, exp);
        if (!s21_buffer_is_zero(mod)) {
          s21_div_mod(mod, value_2, result);
        }
      }
    }
  }
  if (result_sign) {
    s21_buffer_negate(result);
  }
  return real_mod;
}

void s21_div_mod(s21_buffer_decimal mod, s21_buffer_decimal value,
                 s21_buffer_decimal *result) {
  int max_exp = 30;
  int result_digits = s21_get_buffer_digits_count(*result);
  if (result_digits > 28) {
    max_exp = 58 - result_digits + 1;
  }
  s21_buffer_decimal div_result = {{0, 0, 0, 0, 0, 0, 0}};
  int exp = 0;
  while (exp < max_exp && !s21_buffer_is_zero(mod)) {
    while (s21_compare_buffers(mod, value) < 0) {
      s21_buffer_sub(mod, value, &mod);
      div_result.bits[0] += 1;
    }
    s21_buffer_multiply_by_ten(&mod);
    s21_buffer_multiply_by_ten(&div_result);
    exp++;
  }
  s21_set_buffer_exp(&div_result, exp);
  s21_buffer_add(*result, div_result, result);
}

int s21_get_buffer_digits_count(s21_buffer_decimal result) {
  int count = 0;
  if (s21_buffer_is_zero(result)) {
    count = 1;
  } else {
    while (!s21_buffer_is_zero(result)) {
      s21_buffer_div_ten(&result);
      count++;
    }
  }
  return count;
}

void s21_search_int_div_ans(s21_buffer_decimal max, s21_buffer_decimal min,
                            s21_buffer_decimal value_1,
                            s21_buffer_decimal value_2,
                            s21_buffer_decimal *result) {
  s21_buffer_decimal sub_res = *result;
  s21_buffer_mul(value_2, sub_res, &sub_res);
  int compare_res = s21_compare_buffers(sub_res, value_1);
  if (compare_res) {
    if (compare_res < 0) {
      max = *result;
      s21_buffer_add(max, min, result);
      s21_buffer_div_two(result);
      if (s21_compare_buffers(max, *result) < 0) {
        s21_search_int_div_ans(max, min, value_1, value_2, result);
      }
    } else {
      min = *result;
      s21_buffer_add(max, min, result);
      s21_buffer_div_two(result);
      if (s21_compare_buffers(min, *result) > 0) {
        s21_search_int_div_ans(max, min, value_1, value_2, result);
      }
    }
  }
  s21_buffer_mul(*result, value_2, &sub_res);
  compare_res = s21_compare_buffers(sub_res, value_1);
  if (compare_res < 0) {
    s21_buffer_decimal one = {{1, 0, 0, 0, 0, 0, 0}};
    s21_buffer_sub(*result, one, result);
  }
}

void s21_buffer_add(s21_buffer_decimal value_1, s21_buffer_decimal value_2,
                    s21_buffer_decimal *result) {
  unsigned int overflow = 0;
  long long int buffer = 0;
  s21_buffer_decimal temp;
  s21_zero_buffer(result);
  s21_copy_buffer(*result, &temp);
  s21_buffer_exp_equalizer(&value_1, &value_2);
  int exp = s21_get_buffer_exp(value_1);
  for (int i = 0; i < 6; i++) {
    buffer += (unsigned int)value_1.bits[i];
    buffer += (unsigned int)value_2.bits[i];
    buffer += overflow;
    overflow = (unsigned long long int)buffer >> 32;
    temp.bits[i] = (unsigned int)buffer;
    buffer = 0;
  }
  s21_set_buffer_exp(&temp, exp);
  s21_copy_buffer(temp, result);
}

void s21_buffer_div_two(s21_buffer_decimal *src) {
  long long int buffer = (unsigned int)src->bits[5];
  long long int mod_res;
  for (int i = 5; i >= 0; i--) {
    mod_res = buffer % 2;
    src->bits[i] = (unsigned int)(buffer / 2);
    if (i) {
      buffer = mod_res << 32;
      buffer += (unsigned int)src->bits[i - 1];
    }
  }
}

void s21_buffer_sub(s21_buffer_decimal value_1, s21_buffer_decimal value_2,
                    s21_buffer_decimal *result) {
  unsigned long long int buffer = 0;
  s21_zero_buffer(result);
  s21_buffer_exp_equalizer(&value_1, &value_2);
  int exp = s21_get_buffer_exp(value_1);
  for (int i = 0; i < 6; i++) {
    buffer += (unsigned int)value_1.bits[i];
    if (buffer < (unsigned int)value_2.bits[i]) {
      int j;
      for (j = i + 1; j < 6; j++) {
        if (value_1.bits[j]) {
          value_1.bits[j] = (unsigned int)value_1.bits[j] - 1;
          break;
        }
      }
      j--;
      while (j > i - 1) {
        value_1.bits[j] = 4294967295;
        j--;
      }
      buffer += 4294967296;
    }
    buffer -= value_2.bits[i];

    result->bits[i] = (unsigned int)buffer;
    buffer = 0;
  }
  s21_set_buffer_exp(result, exp);
  s21_cut_buffer_zeros(result);
}

void s21_shift_temp(s21_buffer_decimal *temp, int i) {
  if (i) {
    int counter = 5;
    while (counter - i >= 0) {
      temp->bits[counter] = temp->bits[counter - i];
      counter--;
    }
    while (i) {
      temp->bits[i - 1] = 0;
      i--;
    }
  }
}

void s21_buffer_check_zero(s21_buffer_decimal *src) {
  if (s21_buffer_is_zero(*src) && s21_buffer_is_negative(*src)) {
    s21_buffer_negate(src);
  }
}

void s21_buffer_bits_add(s21_buffer_decimal value_1, s21_buffer_decimal value_2,
                         s21_buffer_decimal *result) {
  long long int buffer = 0;
  unsigned int overflow = 0;
  s21_buffer_decimal temp;
  s21_zero_buffer(&temp);
  for (int i = 0; i < 6; i++) {
    buffer += (unsigned int)value_1.bits[i];
    buffer += (unsigned int)value_2.bits[i];
    buffer += overflow;
    overflow = (unsigned long long int)buffer >> 32;
    temp.bits[i] = (unsigned int)buffer;
    buffer = 0;
  }
  s21_copy_buffer(temp, result);
}

void s21_buffer_multiply_by_ten(s21_buffer_decimal *src) {
  long long int buffer;
  unsigned int overflow = 0;
  for (int i = 0; i < 6; i++) {
    buffer = (unsigned int)src->bits[i];
    buffer *= 10;
    buffer += overflow;
    overflow = (unsigned long long int)buffer >> 32;
    src->bits[i] = (unsigned int)buffer;
  }
}

int s21_buffer_mod_ten(s21_buffer_decimal src) {
  long long int buffer = (unsigned int)src.bits[5];
  for (int i = 5; i >= 0; i--) {
    buffer = buffer % 10;
    if (i) {
      buffer = buffer << 32;
      buffer += (unsigned int)src.bits[i - 1];
    }
  }
  return (int)buffer;
}

void s21_buffer_div_ten(s21_buffer_decimal *src) {
  long long int buffer = (unsigned int)src->bits[5];
  long long int mod_res;
  for (int i = 5; i >= 0; i--) {
    mod_res = buffer % 10;
    src->bits[i] = (unsigned int)(buffer / 10);
    if (i) {
      buffer = mod_res << 32;
      buffer += (unsigned int)src->bits[i - 1];
    }
  }
}

void s21_cut_buffer_zeros(s21_buffer_decimal *src) {
  int exp = s21_get_buffer_exp(*src);
  int counter = 0;
  while (exp - counter && !s21_buffer_mod_ten(*src)) {
    s21_buffer_div_ten(src);
    counter++;
  }
  if (counter) {
    s21_set_buffer_exp(src, exp - counter);
  }
}

void s21_round_buffer_decimals(s21_buffer_decimal *src, int count) {
  if (count > 0) {
    int sign = s21_buffer_is_negative(*src);
    int exp = s21_get_buffer_exp(*src) - count;
    while (count - 1 > 0) {
      s21_buffer_div_ten(src);
      count--;
    }
    int last_digit = s21_buffer_mod_ten(*src);
    s21_buffer_div_ten(src);
    if (last_digit >= 5) {
      if (last_digit > 5 || s21_buffer_mod_ten(*src) % 2) {
        s21_buffer_decimal one;
        s21_zero_buffer(&one);
        one.bits[0] = 1;
        s21_buffer_bits_add(*src, one, src);
        if (sign) {
          s21_buffer_negate(src);
        }
      }
    }
    s21_set_buffer_exp(src, exp);
  }
}

int s21_buffer_to_decimal(s21_buffer_decimal buffer, s21_decimal *result) {
  int error_code = 0;
  int sign = s21_buffer_is_negative(buffer);
  if (!s21_buffer_is_zero(buffer)) {
    s21_cut_buffer_zeros(&buffer);
    int buff_exp = s21_get_buffer_exp(buffer);
    if (!buff_exp && (buffer.bits[5] || buffer.bits[4] || buffer.bits[3])) {
      if (sign) {
        error_code = 2;
      } else {
        error_code = 1;
      }
    } else if (buffer.bits[5] || buffer.bits[4] || buffer.bits[3]) {
      s21_buffer_decimal temp;
      s21_copy_buffer(buffer, &temp);
      int counter = 0;
      while (temp.bits[5] || temp.bits[4] || temp.bits[3]) {
        s21_buffer_div_ten(&temp);
        counter++;
      }
      if (counter > buff_exp) {
        if (sign) {
          error_code = 2;
        } else {
          error_code = 1;
        }
      } else {
        s21_round_buffer_decimals(&buffer, counter);
        error_code = s21_copy_buffer_to_decimal(buffer, result);
      }
    } else {
      error_code = s21_copy_buffer_to_decimal(buffer, result);
    }
  } else {
    s21_zero_decimal(result);
    if (sign) {
      s21_negate(*result, result);
    }
  }
  return error_code;
}

int s21_copy_buffer_to_decimal(s21_buffer_decimal buffer, s21_decimal *result) {
  int error_code = 0;
  int buff_exp = s21_get_buffer_exp(buffer);
  s21_round_buffer_decimals(&buffer, buff_exp - 28);
  for (int i = 0; i < 3; i++) {
    result->bits[i] = buffer.bits[i];
  }
  result->bits[3] = buffer.bits[6];
  return error_code;
}

void s21_buffer_exp_equalizer(s21_buffer_decimal *value_1,
                              s21_buffer_decimal *value_2) {
  int exp_1 = s21_get_buffer_exp(*value_1);
  int exp_2 = s21_get_buffer_exp(*value_2);
  if (exp_1 != exp_2) {
    if (exp_1 > exp_2) {
      s21_buffer_add_trailing_zeros(value_2, exp_1 - exp_2, exp_2);
    } else {
      s21_buffer_add_trailing_zeros(value_1, exp_2 - exp_1, exp_1);
    }
  }
}

void s21_buffer_add_trailing_zeros(s21_buffer_decimal *src, int zeros_count,
                                   int exp) {
  s21_set_buffer_exp(src, exp + zeros_count);
  while (zeros_count > 0) {
    s21_buffer_multiply_by_ten(src);
    zeros_count--;
  }
}

void s21_buffer_abs(s21_buffer_decimal *src) { src->bits[6] &= ~(1 << 31); }
