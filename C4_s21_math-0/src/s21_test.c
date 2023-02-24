#include <check.h>
#include <math.h>
#include <stdlib.h>

#include "./s21_math.h"

// s21_abs ->
START_TEST(test_abs_negative) { ck_assert_int_eq(abs(-1), s21_abs(-1)); }
END_TEST

START_TEST(test_abs_zero) { ck_assert_int_eq(abs(0), s21_abs(0)); }
END_TEST

START_TEST(test_abs_int32_max) {
  ck_assert_int_eq(abs(INT32_MAX), s21_abs(INT32_MAX));
}
END_TEST

START_TEST(test_abs_int32_min) {
  ck_assert_int_eq(abs(INT32_MIN), s21_abs(INT32_MIN));
}

START_TEST(test_abs_char_kek) { ck_assert_int_eq(abs('a'), s21_abs('a')); }
END_TEST
// s21_abs <-

// s21_exp ->
START_TEST(test_exp_negative) { ck_assert_ldouble_eq(exp(-2), s21_exp(-2)); }
END_TEST

START_TEST(test_exp_negative2) {
  ck_assert_ldouble_eq_tol(exp(-20), s21_exp(-20), 1e-6);
}
END_TEST

START_TEST(test_exp_normal) {
  ck_assert_ldouble_eq_tol(exp(10), s21_exp(10), 1e-6);
}
END_TEST

START_TEST(test_exp_zero1) {
  ck_assert_ldouble_eq_tol(exp(0.000000), s21_exp(0.000000), 1e-6);
}
END_TEST

START_TEST(test_exp_zero2) {
  ck_assert_ldouble_eq_tol(exp(0), s21_exp(0), 1e-6);
}
END_TEST

START_TEST(test_exp_normal2) {
  ck_assert_ldouble_eq_tol(exp(1.333333), s21_exp(1.333333), 1e-6);
}
END_TEST

START_TEST(test_exp_negative3) {
  ck_assert_ldouble_eq_tol(exp(-1.151515), s21_exp(-1.151515), 1e-6);
}
END_TEST

START_TEST(test_exp_nenormal) {
  ck_assert_ldouble_eq_tol(exp(.000000), s21_exp(.000000), 1e-6);
}
END_TEST
// s21_exp <-

// s21_fabs ->
START_TEST(test_fabs_negative) {
  ck_assert_double_eq(fabs(-1.111111), s21_fabs(-1.111111));
}
END_TEST

START_TEST(test_fabs_zero) {
  ck_assert_double_eq(fabs(0.000000), s21_fabs(0.000000));
}
END_TEST

START_TEST(test_fabs_dbl_max) {
  ck_assert_double_eq(fabs(DBL_MAX), s21_fabs(DBL_MAX));
}
END_TEST

START_TEST(test_fabs_dbl_min) {
  ck_assert_double_eq(fabs(DBL_MIN), s21_fabs(DBL_MIN));
}

START_TEST(test_fabs_char_kek) {
  ck_assert_double_eq(fabs((double)'a'), s21_fabs((double)'a'));
}
END_TEST
START_TEST(test_fabs_nenormal) {
  ck_assert_double_eq(fabs(.000000), s21_fabs(.000000));
}
END_TEST
// s21_fabs <-

// s21_floor ->
START_TEST(test_floor_negative) {
  ck_assert_ldouble_eq(floor(-1.111111), s21_floor(-1.111111));
}
END_TEST

START_TEST(test_floor_negative2) {
  ck_assert_ldouble_eq(floor(-899898989898.123456),
                       s21_floor(-899898989898.123456));
}
END_TEST

START_TEST(test_floor_normal1) {
  ck_assert_ldouble_eq(floor(3456.666666), s21_floor(3456.666666));
}
END_TEST

START_TEST(test_floor_normal2) {
  ck_assert_ldouble_eq(floor(899898989898.123456),
                       s21_floor(899898989898.123456));
}
END_TEST

START_TEST(test_floor_dbl_min) {
  ck_assert_ldouble_eq(floor(DBL_MIN), s21_floor(DBL_MIN));
}
END_TEST

START_TEST(test_floor_zero) { ck_assert_ldouble_eq(floor(0), s21_floor(0)); }
END_TEST

START_TEST(test_floor_zero2) {
  ck_assert_ldouble_eq(floor(0.000000), s21_floor(0.000000));
}
END_TEST

START_TEST(test_floor_zero_after_point_neg) {
  ck_assert_ldouble_eq(floor(-3.000000), s21_floor(-3.000000));
}
END_TEST

START_TEST(test_floor_zero_after_point_pos) {
  ck_assert_ldouble_eq(floor(2.000000), s21_floor(2.000000));
}
END_TEST
// s21_floor <-

// s21_ceil ->
START_TEST(test_ceil_negative) {
  ck_assert_ldouble_eq(ceil(-1.111111), s21_ceil(-1.111111));
}
END_TEST

START_TEST(test_ceil_negative2) {
  ck_assert_ldouble_eq(ceil(-899898989898.123456),
                       s21_ceil(-899898989898.123456));
}
END_TEST

START_TEST(test_ceil_normal1) {
  ck_assert_ldouble_eq(ceil(3456.666666), s21_ceil(3456.666666));
}
END_TEST

START_TEST(test_ceil_normal2) {
  ck_assert_ldouble_eq(ceil(899898989898.123456),
                       s21_ceil(899898989898.123456));
}
END_TEST

START_TEST(test_ceil_dbl_min) {
  ck_assert_ldouble_eq(ceil(DBL_MIN), s21_ceil(DBL_MIN));
}
END_TEST

START_TEST(test_ceil_zero) { ck_assert_ldouble_eq(ceil(0), s21_ceil(0)); }
END_TEST

START_TEST(test_ceil_zero2) {
  ck_assert_ldouble_eq(ceil(0.000000), s21_ceil(0.000000));
}
END_TEST

START_TEST(test_ceil_zero_after_point_neg) {
  ck_assert_ldouble_eq(ceil(-3.000000), s21_ceil(-3.000000));
}
END_TEST

START_TEST(test_ceil_zero_after_point_pos) {
  ck_assert_ldouble_eq(ceil(2.000000), s21_ceil(2.000000));
}
END_TEST
// s21_ceil <-

// s21_fmod ->
START_TEST(test_fmod_negative) {
  ck_assert_ldouble_eq(fmod(-1, -1), s21_fmod(-1, -1));
}
END_TEST

START_TEST(test_fmod_normal1) {
  ck_assert_ldouble_eq(fmod(5.4945, 3.333333), s21_fmod(5.4945, 3.333333));
}
END_TEST

START_TEST(test_fmod_normal2) {
  ck_assert_ldouble_eq_tol(fmod(1641645.666666, 4.123123),
                           s21_fmod(1641645.666666, 4.123123), 1e-6);
}
END_TEST

START_TEST(test_fmod_zero) { ck_assert_ldouble_nan(s21_fmod(0, 0)); }
END_TEST

START_TEST(test_fmod_zero2) { ck_assert_ldouble_nan(s21_fmod(0.0000, 0.0000)); }
END_TEST

START_TEST(test_fmod_zero3) {
  ck_assert_ldouble_eq(fmod(0, 1), s21_fmod(0, 1));
}
END_TEST

START_TEST(test_fmod_nan) { ck_assert_ldouble_nan(s21_fmod(-50, 0.0000)); }
END_TEST

START_TEST(test_fmod_normal3) {
  ck_assert_ldouble_eq_tol(fmod(0.000005, 0.000005),
                           s21_fmod(0.000005, 0.000005), 1e-6);
}
END_TEST

START_TEST(test_fmod_normal4) {
  ck_assert_ldouble_eq(fmod(-50, 4), s21_fmod(-50, 4));
}
END_TEST

START_TEST(test_fmod_normal5) { ck_assert_ldouble_nan(s21_fmod(2000, 0)); }
END_TEST
// s21_fmod <-

// s21_log ->
START_TEST(test_log_negative) { ck_assert_ldouble_nan(s21_log(-2)); }
END_TEST

START_TEST(test_log_normal) { ck_assert_ldouble_eq_tol(log(8), s21_log(8), 6); }
END_TEST

START_TEST(test_log_normal2) {
  ck_assert_ldouble_eq_tol(log(666), s21_log(666), 1e-6);
}
END_TEST

START_TEST(test_log_normal3) {
  ck_assert_ldouble_eq_tol(log(6666), s21_log(6666), 1e-6);
}
END_TEST

START_TEST(test_log_normal4) {
  ck_assert_ldouble_eq_tol(log(0.898989), s21_log(0.898989), 1e-6);
}
END_TEST

START_TEST(test_log_normal5) {
  ck_assert_ldouble_eq_tol(log(0.00000005), s21_log(0.00000005), 1e-6);
}
END_TEST

START_TEST(test_log_normal6) {
  ck_assert_ldouble_eq_tol(log(6666666), s21_log(6666666), 1e-6);
}
END_TEST

START_TEST(test_log_zero1) { ck_assert_ldouble_infinite(s21_log(0)); }
END_TEST

START_TEST(test_log_zero2) { ck_assert_ldouble_infinite(s21_log(0.000000)); }
END_TEST

START_TEST(test_log_char) {
  ck_assert_ldouble_eq_tol(log('a'), s21_log('a'), 1e-6);
}
END_TEST

START_TEST(test_log_nenormal) {
  ck_assert_ldouble_eq_tol(log(.0003), s21_log(.0003), 1e-6);
}
END_TEST

START_TEST(test_log_normal7) {
  ck_assert_ldouble_eq_tol(log(0.5), s21_log(0.5), 1e-6);
}
END_TEST
// s21_log <-

// s21_pow ->
START_TEST(test_pow_negative) { ck_assert_ldouble_nan(s21_pow(-50.0, 1.2)); }
END_TEST

START_TEST(test_pow_normal) { ck_assert_ldouble_eq(pow(1, 1), s21_pow(1, 1)); }
END_TEST

START_TEST(test_pow_normal2) {
  ck_assert_ldouble_eq_tol(pow(0.555, 4), s21_pow(0.555, 4), 1e-6);
}
END_TEST

START_TEST(test_pow_normal3) {
  ck_assert_ldouble_eq_tol(pow(10, 2), s21_pow(10, 2), 1e-6);
}
END_TEST

START_TEST(test_pow_zero) {
  ck_assert_ldouble_eq_tol(pow(0, 0), s21_pow(0, 0), 1e-6);
}
END_TEST

START_TEST(test_pow_zero2) {
  ck_assert_ldouble_eq_tol(pow(0.000000, 0.000000), s21_pow(0.000000, 0.000000),
                           1e-6);
}
END_TEST

START_TEST(test_pow_normal4) {
  ck_assert_ldouble_eq_tol(pow(100.000000, 0.000000),
                           s21_pow(100.000000, 0.000000), 1e-6);
}
END_TEST

START_TEST(test_pow_normal5) {
  ck_assert_ldouble_eq_tol(pow(0.000200, 0.000200), s21_pow(0.000200, 0.000200),
                           1e-6);
}
END_TEST

START_TEST(test_pow_normal6) {
  ck_assert_ldouble_eq_tol(pow(10.1234, -0.000200), s21_pow(10.1234, -0.000200),
                           1e-6);
}
END_TEST

START_TEST(test_pow_normal7) {
  ck_assert_ldouble_eq_tol(pow(2, 50), s21_pow(2, 50), 1e-6);
}
END_TEST

START_TEST(test_pow_char) {
  ck_assert_ldouble_eq_tol(pow('a', 1.2), s21_pow('a', 1.2), 1e-6);
}
END_TEST

START_TEST(test_pow_nenormal) { ck_assert_ldouble_infinite(s21_pow(.0, -1.2)); }
END_TEST

START_TEST(test_pow_neg_base_zero_exp) {
  ck_assert_ldouble_eq_tol(pow(-1, 0), s21_pow(-1, 0), 1e-6);
}
END_TEST

START_TEST(test_pow_neg_base_nan_exp) {
  ck_assert_ldouble_nan(s21_pow(-1, S21_NAN));
}
END_TEST

START_TEST(test_pow_neg_base_inf_exp) {
  ck_assert_ldouble_eq_tol(pow(-1, S21_INF), s21_pow(-1, S21_INF), 1e-6);
}
END_TEST

START_TEST(test_pow_neg_base_neg_inf_exp) {
  ck_assert_ldouble_eq_tol(pow(-1, -S21_INF), s21_pow(-1, -S21_INF), 1e-6);
}
END_TEST

START_TEST(test_pow_neg_one_base_neg_one_exp) {
  ck_assert_ldouble_eq_tol(pow(-1, -1), s21_pow(-1, -1), 1e-6);
}
END_TEST

START_TEST(test_pow_neg_one_base_pos_one_exp) {
  ck_assert_ldouble_eq_tol(pow(-1, 1), s21_pow(-1, 1), 1e-6);
}
END_TEST

START_TEST(test_pow_neg_one_base_pos_num_exp) {
  ck_assert_ldouble_eq_tol(pow(-1, 44), s21_pow(-1, 44), 1e-6);
}
END_TEST

START_TEST(test_pow_neg_one_base_neg_num_exp) {
  ck_assert_ldouble_eq_tol(pow(-1, -44), s21_pow(-1, -44), 1e-6);
}
END_TEST

START_TEST(test_pow_neg_one_base_pos_small_num_exp) {
  ck_assert_ldouble_nan(s21_pow(-1, 0.90354));
}
END_TEST

START_TEST(test_pow_neg_one_base_neg_small_num_exp) {
  ck_assert_ldouble_nan(s21_pow(-1, -0.90354));
}
END_TEST

START_TEST(test_pow_zero_base_nan_exp) {
  ck_assert_ldouble_nan(s21_pow(0, S21_NAN));
}
END_TEST

START_TEST(test_pow_nan_base_nan_exp) {
  ck_assert_ldouble_nan(s21_pow(S21_NAN, S21_NAN));
}
END_TEST

START_TEST(test_pow_inf_base_nan_exp) {
  ck_assert_ldouble_nan(s21_pow(S21_INF, S21_NAN));
}
END_TEST

START_TEST(test_pow_neg_inf_base_nan_exp) {
  ck_assert_ldouble_nan(s21_pow(-S21_INF, S21_NAN));
}
END_TEST

START_TEST(test_pow_pos_one_base_nan_exp) {
  ck_assert_ldouble_eq_tol(pow(1, S21_NAN), s21_pow(1, S21_NAN), 1e-6);
}
END_TEST

START_TEST(test_pow_pos_num_base_nan_exp) {
  ck_assert_ldouble_nan(s21_pow(44, S21_NAN));
}
END_TEST

START_TEST(test_pow_neg_num_base_nan_exp) {
  ck_assert_ldouble_nan(s21_pow(-44, S21_NAN));
}
END_TEST

START_TEST(test_pow_pos_small_num_base_nan_exp) {
  ck_assert_ldouble_nan(s21_pow(0.90354, S21_NAN));
}
END_TEST

START_TEST(test_pow_neg_small_num_base_nan_exp) {
  ck_assert_ldouble_nan(s21_pow(-0.90354, S21_NAN));
}
END_TEST

START_TEST(test_pow_neg_num_base_inf_exp) {
  ck_assert_ldouble_eq(pow(-11, S21_INF), s21_pow(-11, S21_INF));
}
END_TEST

START_TEST(test_pow_pos_num_base_inf_exp) {
  ck_assert_ldouble_eq(pow(11, S21_INF), s21_pow(-11, S21_INF));
}
END_TEST

START_TEST(test_pow_neg_small_num_base_inf_exp) {
  ck_assert_ldouble_eq_tol(pow(-0.3, S21_INF), s21_pow(-0.3, S21_INF), 1e-6);
}
END_TEST

START_TEST(test_pow_pos_small_num_base_inf_exp) {
  ck_assert_ldouble_eq_tol(pow(0.3, S21_INF), s21_pow(0.3, S21_INF), 1e-6);
}
END_TEST

START_TEST(test_pow_nan_base_inf_exp) {
  ck_assert_ldouble_nan(s21_pow(S21_NAN, S21_INF));
}
END_TEST

START_TEST(test_pow_neg_num_base_neg_inf_exp) {
  ck_assert_ldouble_eq_tol(pow(-11, -S21_INF), s21_pow(-11, -S21_INF), 1e-6);
}
END_TEST

START_TEST(test_pow_pos_num_base_neg_inf_exp) {
  ck_assert_ldouble_eq_tol(pow(11, -S21_INF), s21_pow(11, -S21_INF), 1e-6);
}
END_TEST

START_TEST(test_pow_neg_small_num_base_neg_inf_exp) {
  ck_assert_ldouble_eq(pow(-0.3, -S21_INF), s21_pow(-0.3, -S21_INF));
}
END_TEST

START_TEST(test_pow_pos_small_num_base_neg_inf_exp) {
  ck_assert_ldouble_eq(pow(0.3, -S21_INF), s21_pow(0.3, -S21_INF));
}
END_TEST

START_TEST(test_pow_nan_base_neg_inf_exp) {
  ck_assert_ldouble_nan(s21_pow(S21_NAN, -S21_INF));
}
END_TEST

START_TEST(test_pow_neg_inf_base_neg_one_exp) {
  ck_assert_ldouble_eq_tol(pow(-S21_INF, -1), s21_pow(-S21_INF, -1), 1e-6);
}
END_TEST

START_TEST(test_pow_neg_inf_base_pos_one_exp) {
  ck_assert_ldouble_eq(pow(-S21_INF, 1), s21_pow(-S21_INF, 1));
}
END_TEST

START_TEST(test_pow_neg_inf_base_zero_exp) {
  ck_assert_ldouble_eq_tol(pow(-S21_INF, 0), s21_pow(-S21_INF, 0), 1e-6);
}
END_TEST

START_TEST(test_pow_neg_inf_base_neg_inf_exp) {
  ck_assert_ldouble_eq_tol(pow(-S21_INF, -S21_INF), s21_pow(-S21_INF, -S21_INF),
                           1e-6);
}
END_TEST

START_TEST(test_pow_neg_inf_base_pos_inf_exp) {
  ck_assert_ldouble_eq(pow(-S21_INF, S21_INF), s21_pow(-S21_INF, S21_INF));
}
END_TEST

START_TEST(test_pow_neg_inf_base_neg_num_exp) {
  ck_assert_ldouble_eq_tol(pow(-S21_INF, -11), s21_pow(-S21_INF, -11), 1e-6);
}
END_TEST

START_TEST(test_pow_neg_inf_base_pos_num_exp) {
  ck_assert_ldouble_eq(pow(-S21_INF, 12), s21_pow(-S21_INF, 12));
}
END_TEST

START_TEST(test_pow_neg_inf_base_small_pos_num_exp) {
  ck_assert_ldouble_eq(pow(-S21_INF, 0.001), s21_pow(-S21_INF, 0.001));
}
END_TEST

START_TEST(test_pow_neg_inf_base_small_neg_num_exp) {
  ck_assert_ldouble_eq_tol(pow(-S21_INF, -0.001), s21_pow(-S21_INF, -0.001),
                           1e-6);
}
END_TEST
// s21_pow <-

// s21_sqrt ->
START_TEST(test_sqrt_normal_pos) {
  ck_assert_ldouble_eq_tol(s21_sqrt(1050.156), sqrt(1050.156), 1e-6);
}
END_TEST

START_TEST(test_sqrt_normal_neg) { ck_assert_ldouble_nan(s21_sqrt(-1050.156)); }
END_TEST

START_TEST(test_sqrt_little_neg) {
  ck_assert_ldouble_nan(s21_sqrt(-0.00000324));
}
END_TEST

START_TEST(test_sqrt_little_pos) {
  ck_assert_ldouble_eq_tol(s21_sqrt(0.000023), sqrt(0.000023), 1e-6);
}
END_TEST

START_TEST(test_sqrt_zero) {
  ck_assert_ldouble_eq_tol(s21_sqrt(0), sqrt(0), 1e-6);
}
END_TEST

START_TEST(test_sqrt_pos_inf) { ck_assert_ldouble_infinite(s21_sqrt(S21_INF)); }
END_TEST

START_TEST(test_sqrt_neg_inf) { ck_assert_ldouble_nan(s21_sqrt(-S21_INF)); }
END_TEST
// s21_sqrt <-

// s21_sin ->
START_TEST(test_sin_normal_pos) {
  ck_assert_ldouble_eq_tol(s21_sin(1254.12), sin(1254.12), 1e-6);
}
END_TEST

START_TEST(test_sin_normal_neg) {
  ck_assert_ldouble_eq_tol(s21_sin(-512.1612), sin(-512.1612), 1e-6);
}
END_TEST

START_TEST(test_sin_little_neg) {
  ck_assert_ldouble_eq_tol(s21_sin(-0.0001525), sin(-0.0001525), 1e-6);
}
END_TEST

START_TEST(test_sin_little_pos) {
  ck_assert_ldouble_eq_tol(s21_sin(0.000172), sin(0.000172), 1e-6);
}
END_TEST

START_TEST(test_sin_zero) {
  ck_assert_ldouble_eq_tol(s21_sin(0), sin(0), 1e-6);
}
END_TEST

START_TEST(test_sin_pos_inf) { ck_assert_ldouble_nan(s21_sin(S21_INF)); }
END_TEST

START_TEST(test_sin_neg_inf) { ck_assert_ldouble_nan(s21_sin(-S21_INF)); }
END_TEST

START_TEST(test_sin_nan) { ck_assert_ldouble_nan(s21_sin(S21_NAN)); }
END_TEST

START_TEST(test_sin_mult_PI) {
  ck_assert_ldouble_eq_tol(s21_sin(S21_PI * 5.661), sin(S21_PI * 5.661), 1e-6);
}
END_TEST

START_TEST(test_sin_PI) {
  ck_assert_ldouble_eq_tol(s21_sin(S21_PI), sin(S21_PI), 1e-6);
}
END_TEST
// s21_sin <-

// s21_cos ->
START_TEST(test_cos_normal_pos) {
  ck_assert_ldouble_eq_tol(s21_cos(1254.12), cos(1254.12), 1e-6);
}
END_TEST

START_TEST(test_cos_normal_neg) {
  ck_assert_ldouble_eq_tol(s21_cos(-512.1612), cos(-512.1612), 1e-6);
}
END_TEST

START_TEST(test_cos_little_neg) {
  ck_assert_ldouble_eq_tol(s21_cos(-0.0001525), cos(-0.0001525), 1e-6);
}
END_TEST

START_TEST(test_cos_little_pos) {
  ck_assert_ldouble_eq_tol(s21_cos(0.000172), cos(0.000172), 1e-6);
}
END_TEST

START_TEST(test_cos_zero) {
  ck_assert_ldouble_eq_tol(s21_cos(0), cos(0), 1e-6);
}
END_TEST

START_TEST(test_cos_pos_inf) { ck_assert_ldouble_nan(s21_cos(S21_INF)); }
END_TEST

START_TEST(test_cos_neg_inf) { ck_assert_ldouble_nan(s21_cos(-S21_INF)); }
END_TEST

START_TEST(test_cos_nan) { ck_assert_ldouble_nan(s21_cos(S21_NAN)); }
END_TEST

START_TEST(test_cos_mult_PI) {
  ck_assert_ldouble_eq_tol(s21_cos(S21_PI * 5.661), cos(S21_PI * 5.661), 1e-6);
}
END_TEST

START_TEST(test_cos_PI) {
  ck_assert_ldouble_eq_tol(s21_cos(S21_PI), cos(S21_PI), 1e-6);
}
END_TEST
// s21_cos <-

// s21_tan ->
START_TEST(test_tan_normal_pos) {
  ck_assert_ldouble_eq_tol(s21_tan(1254.12), tan(1254.12), 1e-6);
}
END_TEST

START_TEST(test_tan_normal_neg) {
  ck_assert_ldouble_eq_tol(s21_tan(-512.1612), tan(-512.1612), 1e-6);
}
END_TEST

START_TEST(test_tan_little_neg) {
  ck_assert_ldouble_eq_tol(s21_tan(-0.0001525), tan(-0.0001525), 1e-6);
}
END_TEST

START_TEST(test_tan_little_pos) {
  ck_assert_ldouble_eq_tol(s21_tan(0.000172), tan(0.000172), 1e-6);
}
END_TEST

START_TEST(test_tan_zero) {
  ck_assert_ldouble_eq_tol(s21_tan(0), tan(0), 1e-6);
}
END_TEST

START_TEST(test_tan_pos_inf) { ck_assert_ldouble_nan(s21_tan(S21_INF)); }
END_TEST

START_TEST(test_tan_neg_inf) { ck_assert_ldouble_nan(s21_tan(-S21_INF)); }
END_TEST

START_TEST(test_tan_nan) { ck_assert_ldouble_nan(s21_tan(S21_NAN)); }
END_TEST

START_TEST(test_tan_mult_PI) {
  ck_assert_ldouble_eq_tol(s21_tan(S21_PI * 5.661), tan(S21_PI * 5.661), 1e-6);
}
END_TEST

START_TEST(test_tan_PI) {
  ck_assert_ldouble_eq_tol(s21_tan(S21_PI), tan(S21_PI), 1e-6);
}
END_TEST
// s21_tan <-

// s21_atan ->
START_TEST(test_atan_normal_pos) {
  ck_assert_ldouble_eq_tol(s21_atan(1254.12), atan(1254.12), 1e-6);
}
END_TEST

START_TEST(test_atan_normal_neg) {
  ck_assert_ldouble_eq_tol(s21_atan(-512.1612), atan(-512.1612), 1e-6);
}
END_TEST

START_TEST(test_atan_little_neg) {
  ck_assert_ldouble_eq_tol(s21_atan(-0.0001525), atan(-0.0001525), 1e-6);
}
END_TEST

START_TEST(test_atan_little_pos) {
  ck_assert_ldouble_eq_tol(s21_atan(0.000172), atan(0.000172), 1e-6);
}
END_TEST

START_TEST(test_atan_zero) {
  ck_assert_ldouble_eq_tol(s21_atan(0), atan(0), 1e-6);
}
END_TEST

START_TEST(test_atan_pos_inf) {
  ck_assert_ldouble_eq_tol(s21_atan(S21_INF), atan(S21_INF), 1e-6);
}
END_TEST

START_TEST(test_atan_neg_inf) {
  ck_assert_ldouble_eq_tol(s21_atan(-S21_INF), atan(-S21_INF), 1e-6);
}
END_TEST

START_TEST(test_atan_nan) { ck_assert_ldouble_nan(s21_atan(S21_NAN)); }
END_TEST

START_TEST(test_atan_mult_PI) {
  ck_assert_ldouble_eq_tol(s21_atan(S21_PI * 5.661), atan(S21_PI * 5.661),
                           1e-6);
}
END_TEST

START_TEST(test_atan_PI) {
  ck_assert_ldouble_eq_tol(s21_atan(S21_PI), atan(S21_PI), 1e-6);
}
END_TEST

START_TEST(test_atan_one) {
  ck_assert_ldouble_eq_tol(s21_atan(1), atan(1), 1e-6);
}
END_TEST

START_TEST(test_atan_minus_one) {
  ck_assert_ldouble_eq_tol(s21_atan(-1), atan(-1), 1e-6);
}
END_TEST

START_TEST(test_atan_normal_lower_one) {
  ck_assert_ldouble_eq_tol(s21_atan(0.987), atan(0.987), 1e-6);
}
END_TEST

START_TEST(test_atan_normal_lower_one_neg) {
  ck_assert_ldouble_eq_tol(s21_atan(-0.678), atan(-0.678), 1e-6);
}
END_TEST
// s21_atan <-

// s21_asin ->
START_TEST(test_asin_normal_pos) { ck_assert_ldouble_nan(s21_asin(1254.12)); }
END_TEST

START_TEST(test_asin_normal_neg) { ck_assert_ldouble_nan(s21_asin(-512.1612)); }
END_TEST

START_TEST(test_asin_one) {
  ck_assert_ldouble_eq_tol(s21_asin(1), asin(1), 1e-6);
}
END_TEST

START_TEST(test_asin_minus_one) {
  ck_assert_ldouble_eq_tol(s21_asin(-1), asin(-1), 1e-6);
}
END_TEST

START_TEST(test_asin_normal_lower_one) {
  ck_assert_ldouble_eq_tol(s21_asin(0.987), asin(0.987), 1e-6);
}
END_TEST

START_TEST(test_asin_normal_lower_one_neg) {
  ck_assert_ldouble_eq_tol(s21_asin(-0.678), asin(-0.678), 1e-6);
}
END_TEST

START_TEST(test_asin_little_neg) {
  ck_assert_ldouble_eq_tol(s21_asin(-0.0001525), asin(-0.0001525), 1e-6);
}
END_TEST

START_TEST(test_asin_little_pos) {
  ck_assert_ldouble_eq_tol(s21_asin(0.000172), asin(0.000172), 1e-6);
}
END_TEST

START_TEST(test_asin_zero) {
  ck_assert_ldouble_eq_tol(s21_asin(0), asin(0), 1e-6);
}
END_TEST

START_TEST(test_asin_pos_inf) { ck_assert_ldouble_nan(s21_asin(S21_INF)); }
END_TEST

START_TEST(test_asin_neg_inf) { ck_assert_ldouble_nan(s21_asin(-S21_INF)); }
END_TEST

START_TEST(test_asin_nan) { ck_assert_ldouble_nan(s21_asin(S21_NAN)); }
END_TEST

START_TEST(test_asin_mult_PI) {
  ck_assert_ldouble_nan(s21_asin(S21_PI * 5.661));
}
END_TEST
// s21_asin <-

// s21_acos ->
START_TEST(test_acos_normal_pos) { ck_assert_ldouble_nan(s21_acos(1254.12)); }
END_TEST

START_TEST(test_acos_normal_neg) { ck_assert_ldouble_nan(s21_acos(-512.1612)); }
END_TEST

START_TEST(test_acos_one) {
  ck_assert_ldouble_eq_tol(s21_acos(1), acos(1), 1e-6);
}
END_TEST

START_TEST(test_acos_minus_one) {
  ck_assert_ldouble_eq_tol(s21_acos(-1), acos(-1), 1e-6);
}
END_TEST

START_TEST(test_acos_normal_lower_one) {
  ck_assert_ldouble_eq_tol(s21_acos(0.987), acos(0.987), 1e-6);
}
END_TEST

START_TEST(test_acos_normal_lower_one_neg) {
  ck_assert_ldouble_eq_tol(s21_acos(-0.678), acos(-0.678), 1e-6);
}
END_TEST

START_TEST(test_acos_little_neg) {
  ck_assert_ldouble_eq_tol(s21_acos(-0.0001525), acos(-0.0001525), 1e-6);
}
END_TEST

START_TEST(test_acos_little_pos) {
  ck_assert_ldouble_eq_tol(s21_acos(0.000172), acos(0.000172), 1e-6);
}
END_TEST

START_TEST(test_acos_zero) {
  ck_assert_ldouble_eq_tol(s21_acos(0), acos(0), 1e-6);
}
END_TEST

START_TEST(test_acos_pos_inf) { ck_assert_ldouble_nan(s21_acos(S21_INF)); }
END_TEST

START_TEST(test_acos_neg_inf) { ck_assert_ldouble_nan(s21_acos(-S21_INF)); }
END_TEST

START_TEST(test_acos_nan) { ck_assert_ldouble_nan(s21_acos(S21_NAN)); }
END_TEST

START_TEST(test_acos_mult_PI) {
  ck_assert_ldouble_nan(s21_acos(S21_PI * 5.661));
}
END_TEST
// s21_acos <-

Suite *suite_insert(void) {
  Suite *s = suite_create("suite_insert");
  TCase *tc = tcase_create("insert_tc");
  // s21_abs ->
  tcase_add_test(tc, test_abs_negative);
  tcase_add_test(tc, test_abs_zero);
  tcase_add_test(tc, test_abs_int32_max);
  tcase_add_test(tc, test_abs_int32_min);
  tcase_add_test(tc, test_abs_char_kek);
  // // s21_abs <-

  // s21_exp ->
  tcase_add_test(tc, test_exp_negative);
  tcase_add_test(tc, test_exp_negative2);
  tcase_add_test(tc, test_exp_normal);
  tcase_add_test(tc, test_exp_zero1);
  tcase_add_test(tc, test_exp_zero2);
  tcase_add_test(tc, test_exp_normal2);
  tcase_add_test(tc, test_exp_negative3);
  tcase_add_test(tc, test_exp_nenormal);
  // s21_exp <-

  // s21_fabs ->
  tcase_add_test(tc, test_fabs_negative);
  tcase_add_test(tc, test_fabs_zero);
  tcase_add_test(tc, test_fabs_dbl_max);
  tcase_add_test(tc, test_fabs_dbl_min);
  tcase_add_test(tc, test_fabs_char_kek);
  tcase_add_test(tc, test_fabs_nenormal);
  // s21_fabs <-

  // s21_floor ->
  tcase_add_test(tc, test_floor_negative);
  tcase_add_test(tc, test_floor_negative2);
  tcase_add_test(tc, test_floor_normal1);
  tcase_add_test(tc, test_floor_normal2);
  tcase_add_test(tc, test_floor_dbl_min);
  tcase_add_test(tc, test_floor_zero);
  tcase_add_test(tc, test_floor_zero2);
  tcase_add_test(tc, test_floor_zero_after_point_neg);
  tcase_add_test(tc, test_floor_zero_after_point_pos);
  // s21_floor <-

  // s21_ceil ->
  tcase_add_test(tc, test_ceil_negative);
  tcase_add_test(tc, test_ceil_negative2);
  tcase_add_test(tc, test_ceil_normal1);
  tcase_add_test(tc, test_ceil_normal2);
  tcase_add_test(tc, test_ceil_dbl_min);
  tcase_add_test(tc, test_ceil_zero);
  tcase_add_test(tc, test_ceil_zero2);
  tcase_add_test(tc, test_ceil_zero_after_point_neg);
  tcase_add_test(tc, test_ceil_zero_after_point_pos);
  // s21_ceil <-

  // s21_fmod ->
  tcase_add_test(tc, test_fmod_negative);
  tcase_add_test(tc, test_fmod_normal1);
  tcase_add_test(tc, test_fmod_normal2);
  tcase_add_test(tc, test_fmod_zero);
  tcase_add_test(tc, test_fmod_zero2);
  tcase_add_test(tc, test_fmod_zero3);
  tcase_add_test(tc, test_fmod_nan);
  tcase_add_test(tc, test_fmod_normal3);
  tcase_add_test(tc, test_fmod_normal4);
  tcase_add_test(tc, test_fmod_normal5);
  // s21_fmod <-

  // s21_log ->
  tcase_add_test(tc, test_log_negative);
  tcase_add_test(tc, test_log_normal);
  tcase_add_test(tc, test_log_normal2);
  tcase_add_test(tc, test_log_normal3);
  tcase_add_test(tc, test_log_normal4);
  tcase_add_test(tc, test_log_normal5);
  tcase_add_test(tc, test_log_normal6);
  tcase_add_test(tc, test_log_zero1);
  tcase_add_test(tc, test_log_zero2);
  tcase_add_test(tc, test_log_char);
  tcase_add_test(tc, test_log_nenormal);
  tcase_add_test(tc, test_log_normal7);
  // s21_log <-

  // s21_pow ->
  tcase_add_test(tc, test_pow_negative);
  tcase_add_test(tc, test_pow_normal);
  tcase_add_test(tc, test_pow_normal2);
  tcase_add_test(tc, test_pow_normal3);
  tcase_add_test(tc, test_pow_zero);
  tcase_add_test(tc, test_pow_zero2);
  tcase_add_test(tc, test_pow_normal4);
  tcase_add_test(tc, test_pow_normal5);
  tcase_add_test(tc, test_pow_normal6);
  tcase_add_test(tc, test_pow_normal7);
  tcase_add_test(tc, test_pow_char);
  tcase_add_test(tc, test_pow_nenormal);
  tcase_add_test(tc, test_pow_neg_base_zero_exp);
  tcase_add_test(tc, test_pow_neg_base_nan_exp);
  tcase_add_test(tc, test_pow_neg_base_inf_exp);
  tcase_add_test(tc, test_pow_neg_base_neg_inf_exp);
  tcase_add_test(tc, test_pow_neg_one_base_neg_one_exp);
  tcase_add_test(tc, test_pow_neg_one_base_pos_one_exp);
  tcase_add_test(tc, test_pow_neg_one_base_pos_num_exp);
  tcase_add_test(tc, test_pow_neg_one_base_neg_num_exp);
  tcase_add_test(tc, test_pow_neg_one_base_pos_small_num_exp);
  tcase_add_test(tc, test_pow_neg_one_base_neg_small_num_exp);
  tcase_add_test(tc, test_pow_zero_base_nan_exp);
  tcase_add_test(tc, test_pow_nan_base_nan_exp);
  tcase_add_test(tc, test_pow_inf_base_nan_exp);
  tcase_add_test(tc, test_pow_neg_inf_base_nan_exp);
  tcase_add_test(tc, test_pow_pos_one_base_nan_exp);
  tcase_add_test(tc, test_pow_pos_num_base_nan_exp);
  tcase_add_test(tc, test_pow_neg_num_base_nan_exp);
  tcase_add_test(tc, test_pow_pos_small_num_base_nan_exp);
  tcase_add_test(tc, test_pow_neg_small_num_base_nan_exp);
  tcase_add_test(tc, test_pow_neg_num_base_inf_exp);
  tcase_add_test(tc, test_pow_pos_num_base_inf_exp);
  tcase_add_test(tc, test_pow_neg_small_num_base_inf_exp);
  tcase_add_test(tc, test_pow_pos_small_num_base_inf_exp);
  tcase_add_test(tc, test_pow_nan_base_inf_exp);
  tcase_add_test(tc, test_pow_neg_num_base_neg_inf_exp);
  tcase_add_test(tc, test_pow_pos_num_base_neg_inf_exp);
  tcase_add_test(tc, test_pow_neg_small_num_base_neg_inf_exp);
  tcase_add_test(tc, test_pow_pos_small_num_base_neg_inf_exp);
  tcase_add_test(tc, test_pow_nan_base_neg_inf_exp);
  tcase_add_test(tc, test_pow_neg_inf_base_neg_one_exp);
  tcase_add_test(tc, test_pow_neg_inf_base_pos_one_exp);
  tcase_add_test(tc, test_pow_neg_inf_base_zero_exp);
  tcase_add_test(tc, test_pow_neg_inf_base_neg_inf_exp);
  tcase_add_test(tc, test_pow_neg_inf_base_pos_inf_exp);
  tcase_add_test(tc, test_pow_neg_inf_base_neg_num_exp);
  tcase_add_test(tc, test_pow_neg_inf_base_pos_num_exp);
  tcase_add_test(tc, test_pow_neg_inf_base_small_pos_num_exp);
  tcase_add_test(tc, test_pow_neg_inf_base_small_neg_num_exp);
  // s21_pow <-

  // s21_sqrt ->
  tcase_add_test(tc, test_sqrt_normal_pos);
  tcase_add_test(tc, test_sqrt_normal_neg);
  tcase_add_test(tc, test_sqrt_little_neg);
  tcase_add_test(tc, test_sqrt_little_pos);
  tcase_add_test(tc, test_sqrt_zero);
  tcase_add_test(tc, test_sqrt_pos_inf);
  tcase_add_test(tc, test_sqrt_neg_inf);
  // s21_sqrt <-

  // s21_sin ->
  tcase_add_test(tc, test_sin_normal_pos);
  tcase_add_test(tc, test_sin_normal_neg);
  tcase_add_test(tc, test_sin_little_neg);
  tcase_add_test(tc, test_sin_little_pos);
  tcase_add_test(tc, test_sin_zero);
  tcase_add_test(tc, test_sin_pos_inf);
  tcase_add_test(tc, test_sin_neg_inf);
  tcase_add_test(tc, test_sin_nan);
  tcase_add_test(tc, test_sin_mult_PI);
  tcase_add_test(tc, test_sin_PI);
  // s21_sin <-

  // s21_cos ->
  tcase_add_test(tc, test_cos_normal_pos);
  tcase_add_test(tc, test_cos_normal_neg);
  tcase_add_test(tc, test_cos_little_neg);
  tcase_add_test(tc, test_cos_little_pos);
  tcase_add_test(tc, test_cos_zero);
  tcase_add_test(tc, test_cos_pos_inf);
  tcase_add_test(tc, test_cos_neg_inf);
  tcase_add_test(tc, test_cos_nan);
  tcase_add_test(tc, test_cos_mult_PI);
  tcase_add_test(tc, test_cos_PI);
  // s21_cos <-

  // s21_tan ->
  tcase_add_test(tc, test_tan_normal_pos);
  tcase_add_test(tc, test_tan_normal_neg);
  tcase_add_test(tc, test_tan_little_neg);
  tcase_add_test(tc, test_tan_little_pos);
  tcase_add_test(tc, test_tan_zero);
  tcase_add_test(tc, test_tan_pos_inf);
  tcase_add_test(tc, test_tan_neg_inf);
  tcase_add_test(tc, test_tan_nan);
  tcase_add_test(tc, test_tan_mult_PI);
  tcase_add_test(tc, test_tan_PI);
  // s21_tan <-

  // s21_atan ->
  tcase_add_test(tc, test_atan_normal_pos);
  tcase_add_test(tc, test_atan_normal_neg);
  tcase_add_test(tc, test_atan_little_neg);
  tcase_add_test(tc, test_atan_little_pos);
  tcase_add_test(tc, test_atan_zero);
  tcase_add_test(tc, test_atan_pos_inf);
  tcase_add_test(tc, test_atan_neg_inf);
  tcase_add_test(tc, test_atan_nan);
  tcase_add_test(tc, test_atan_mult_PI);
  tcase_add_test(tc, test_atan_PI);
  tcase_add_test(tc, test_atan_one);
  tcase_add_test(tc, test_atan_minus_one);
  tcase_add_test(tc, test_atan_normal_lower_one);
  tcase_add_test(tc, test_atan_normal_lower_one_neg);
  // s21_atan <-

  // s21_asin ->
  tcase_add_test(tc, test_asin_normal_pos);
  tcase_add_test(tc, test_asin_normal_neg);
  tcase_add_test(tc, test_asin_little_neg);
  tcase_add_test(tc, test_asin_little_pos);
  tcase_add_test(tc, test_asin_zero);
  tcase_add_test(tc, test_asin_pos_inf);
  tcase_add_test(tc, test_asin_neg_inf);
  tcase_add_test(tc, test_asin_nan);
  tcase_add_test(tc, test_asin_mult_PI);
  tcase_add_test(tc, test_asin_one);
  tcase_add_test(tc, test_asin_minus_one);
  tcase_add_test(tc, test_asin_normal_lower_one);
  tcase_add_test(tc, test_asin_normal_lower_one_neg);
  // s21_asin <-

  // s21_acos ->
  tcase_add_test(tc, test_acos_normal_pos);
  tcase_add_test(tc, test_acos_normal_neg);
  tcase_add_test(tc, test_acos_little_neg);
  tcase_add_test(tc, test_acos_little_pos);
  tcase_add_test(tc, test_acos_zero);
  tcase_add_test(tc, test_acos_pos_inf);
  tcase_add_test(tc, test_acos_neg_inf);
  tcase_add_test(tc, test_acos_nan);
  tcase_add_test(tc, test_acos_mult_PI);
  tcase_add_test(tc, test_acos_one);
  tcase_add_test(tc, test_acos_minus_one);
  tcase_add_test(tc, test_acos_normal_lower_one);
  tcase_add_test(tc, test_acos_normal_lower_one_neg);
  // s21_acos <-

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
