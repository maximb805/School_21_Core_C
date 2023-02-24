#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DECIMAL 7.9228162514264337593543950335e28

typedef struct {
  int bits[4];
} s21_decimal;

typedef struct {
  int bits[7];
} s21_buffer_decimal;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

int s21_compare_bits(s21_buffer_decimal value_1, s21_buffer_decimal value_2);
int s21_compare_decimals(s21_decimal value_1, s21_decimal value_2);
int s21_compare_buffers(s21_buffer_decimal buffer1, s21_buffer_decimal buffer2);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

void s21_check_zero(s21_decimal *src);
int s21_is_zero(s21_decimal src);
void s21_copy_decimal(s21_decimal *src, s21_decimal *dst);
void s21_set_exp(s21_decimal *dst, int exp);
int s21_mod_ten(s21_decimal src);
void s21_multiply_by_ten(s21_decimal *dst);
void s21_zero_decimal(s21_decimal *decimal);
void s21_div_ten(s21_decimal *src);
int s21_get_exp(s21_decimal src);
int s21_dec_is_negative(s21_decimal src);
void s21_cut_zeros(s21_decimal *src);
void s21_round_precision(s21_decimal *src, int digits_count);
void s21_decimal_abs(s21_decimal *src);

void s21_zero_buffer(s21_buffer_decimal *result);
void s21_decimal_to_buffer(s21_decimal src, s21_buffer_decimal *dst);
void s21_copy_buffer(s21_buffer_decimal src, s21_buffer_decimal *dst);
int s21_buffer_is_negative(s21_buffer_decimal src);
void s21_set_buffer_exp(s21_buffer_decimal *src, int exp);
int s21_get_buffer_exp(s21_buffer_decimal src);
int s21_buffer_is_zero(s21_buffer_decimal src);
void s21_buffer_negate(s21_buffer_decimal *src);
void s21_buffer_multiply_by_ten(s21_buffer_decimal *src);
int s21_buffer_mod_ten(s21_buffer_decimal src);
void s21_buffer_div_ten(s21_buffer_decimal *src);
void s21_cut_buffer_zeros(s21_buffer_decimal *src);
void s21_round_buffer_decimals(s21_buffer_decimal *src, int count);
int s21_buffer_to_decimal(s21_buffer_decimal result_buffer,
                          s21_decimal *result);
void s21_buffer_check_zero(s21_buffer_decimal *src);
void s21_buffer_div_two(s21_buffer_decimal *src);
void s21_div_mod(s21_buffer_decimal mod, s21_buffer_decimal value,
                 s21_buffer_decimal *result);
void s21_search_int_div_ans(s21_buffer_decimal max, s21_buffer_decimal min,
                            s21_buffer_decimal value_1,
                            s21_buffer_decimal value_2,
                            s21_buffer_decimal *result);
int s21_get_buffer_digits_count(s21_buffer_decimal result);

void s21_buffer_mul(s21_buffer_decimal value_1, s21_buffer_decimal value_2,
                    s21_buffer_decimal *result);
void s21_shift_temp(s21_buffer_decimal *temp, int i);
void s21_buffer_bits_add(s21_buffer_decimal value_1, s21_buffer_decimal value_2,
                         s21_buffer_decimal *result);
void s21_buffer_add(s21_buffer_decimal value_1, s21_buffer_decimal value_2,
                    s21_buffer_decimal *result);
int s21_copy_buffer_to_decimal(s21_buffer_decimal buffer, s21_decimal *result);
void s21_buffer_add_trailing_zeros(s21_buffer_decimal *src, int zeros_count,
                                   int exp);
void s21_buffer_exp_equalizer(s21_buffer_decimal *value_1,
                              s21_buffer_decimal *value_2);
void s21_buffer_sub(s21_buffer_decimal buffer1, s21_buffer_decimal buffer2,
                    s21_buffer_decimal *result_buffer);
void s21_buffer_abs(s21_buffer_decimal *src);
s21_buffer_decimal s21_buffer_div(s21_buffer_decimal value_1,
                                  s21_buffer_decimal value_2,
                                  s21_buffer_decimal *result);

void s21_decimal_to_string(char *str, int str_len, s21_decimal src);
void s21_zero_str(char *str, int len);

#endif /* S21_DECIMAL_H */