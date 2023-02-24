#include <check.h>

#include "./s21_decimal.h"

// ADD TESTS START -->
START_TEST(test_s21_add_negative) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  int result_int;
  s21_from_int_to_decimal(-43, &test_value_1);
  s21_from_int_to_decimal(-50, &test_value_2);
  s21_add(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, -93);
}
END_TEST

START_TEST(test_s21_add_large) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  char result_str[32];
  char correct_str[32] = "+00000000000000000004294967294";
  s21_from_int_to_decimal(2147483647, &test_value_1);
  s21_from_int_to_decimal(2147483647, &test_value_2);
  s21_add(test_value_1, test_value_2, &result_dec);
  s21_decimal_to_string(result_str, 32, result_dec);
  ck_assert_str_eq(result_str, correct_str);
}
END_TEST

START_TEST(test_s21_add_max_neg_max_pos) {
  s21_decimal test_value_1 = {{-1, -1, -1, 0}};
  s21_decimal test_value_2 = {{-1, -1, -1, 0}};
  s21_decimal result_dec;
  int result_int;
  s21_negate(test_value_1, &test_value_1);
  s21_add(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_add_zero1) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  int result_int;
  s21_from_int_to_decimal(0, &test_value_1);
  s21_from_int_to_decimal(0, &test_value_2);
  s21_add(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_add_zero2) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  int result_int;
  s21_from_int_to_decimal(1, &test_value_1);
  s21_from_int_to_decimal(100, &test_value_2);
  s21_negate(test_value_1, &test_value_1);
  s21_add(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 99);
}
END_TEST

START_TEST(test_s21_add_zero3) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  int result_int;
  s21_from_int_to_decimal(1, &test_value_1);
  s21_from_int_to_decimal(-100, &test_value_2);
  s21_add(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, -99);
}
END_TEST

START_TEST(test_s21_add_zero4) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  int result_int;
  s21_from_int_to_decimal(0, &test_value_1);
  s21_from_int_to_decimal(-100, &test_value_2);
  s21_negate(test_value_1, &test_value_1);
  s21_add(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, -100);
}
END_TEST

START_TEST(test_s21_add_zero5) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  int result_int;
  s21_from_int_to_decimal(0, &test_value_1);
  s21_from_int_to_decimal(100, &test_value_2);
  s21_add(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 100);
}
END_TEST

START_TEST(test_s21_add1) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  int result_int;
  s21_from_int_to_decimal(10, &test_value_1);
  s21_from_int_to_decimal(23, &test_value_2);
  s21_add(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 33);
}
END_TEST

START_TEST(test_s21_add2) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  float result_float;
  s21_from_float_to_decimal(0.5, &test_value_1);
  s21_from_float_to_decimal(0.5, &test_value_2);
  s21_add(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_float(result_dec, &result_float);
  ck_assert_float_eq(result_float, 1.0);
}
END_TEST

START_TEST(test_s21_add3) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  float result_float;
  s21_from_float_to_decimal(100.323, &test_value_1);
  s21_from_float_to_decimal(-0.5, &test_value_2);
  s21_add(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_float(result_dec, &result_float);
  ck_assert_float_eq(result_float, 99.823);
}
END_TEST

START_TEST(test_s21_add4) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  int result_int;
  s21_from_int_to_decimal(-23, &test_value_1);
  s21_from_int_to_decimal(10, &test_value_2);
  s21_add(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, -13);
}
END_TEST
// ADD TESTS END <--

// SUB TESTS START -->
START_TEST(test_s21_sub_large) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  int result_int;
  s21_from_int_to_decimal(2147483647, &test_value_1);
  s21_from_int_to_decimal(2147483647, &test_value_2);
  s21_sub(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_sub_max_pos) {
  s21_decimal test_value_1 = {{-1, -1, -1, 0}};
  s21_decimal test_value_2 = {{-1, -1, -1, 0}};
  s21_decimal result_dec;
  int result_int;
  s21_sub(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_sub_zero_max_pos) {
  s21_decimal test_value_1 = {{0, 0, 0, 0}};
  s21_decimal test_value_2 = {{-1, -1, -1, 0}};
  s21_decimal result_dec;
  char result_str[32];
  char correct_str[32] = "-79228162514264337593543950335";
  s21_sub(test_value_1, test_value_2, &result_dec);
  s21_decimal_to_string(result_str, 32, result_dec);
  ck_assert_str_eq(result_str, correct_str);
}
END_TEST

START_TEST(test_s21_sub_zero_max_neg) {
  s21_decimal test_value_1 = {{-1, -1, -1, 0}};
  s21_decimal test_value_2 = {{-1, -1, -1, 0}};
  s21_decimal result_dec;
  int result_int;
  s21_sub(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  s21_negate(test_value_1, &test_value_1);
  s21_negate(test_value_2, &test_value_2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_sub_zero1) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  int result_int;
  s21_from_int_to_decimal(0, &test_value_1);
  s21_from_int_to_decimal(-23, &test_value_2);
  s21_negate(test_value_1, &test_value_1);
  s21_sub(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 23);
}
END_TEST

START_TEST(test_s21_sub_zero2) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  int result_int;
  s21_from_int_to_decimal(0, &test_value_1);
  s21_from_int_to_decimal(23, &test_value_2);
  s21_negate(test_value_1, &test_value_1);
  s21_sub(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, -23);
}
END_TEST

START_TEST(test_s21_sub_zero3) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  int result_int;
  s21_from_int_to_decimal(23, &test_value_1);
  s21_from_int_to_decimal(0, &test_value_2);
  s21_negate(test_value_2, &test_value_2);
  s21_sub(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 23);
}
END_TEST

START_TEST(test_s21_sub_zero4) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  int result_int;
  s21_from_int_to_decimal(-23, &test_value_1);
  s21_from_int_to_decimal(0, &test_value_2);
  s21_negate(test_value_2, &test_value_2);
  s21_sub(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, -23);
}
END_TEST

START_TEST(test_s21_sub1) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  int result_int;
  s21_from_int_to_decimal(10, &test_value_1);
  s21_from_int_to_decimal(23, &test_value_2);
  s21_sub(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, -13);
}
END_TEST

START_TEST(test_s21_sub2) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  int result_int;
  s21_from_int_to_decimal(-10, &test_value_1);
  s21_from_int_to_decimal(-23, &test_value_2);
  s21_sub(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 13);
}
END_TEST

START_TEST(test_s21_sub3) {
  s21_decimal test_value_1 = {{-1, -1, -1, 0}};
  s21_decimal test_value_2;
  s21_decimal result_dec;
  char result_str[32];
  char correct_str[32] = "+79228162514264337593543950334";
  s21_from_float_to_decimal(0.5, &test_value_2);
  s21_sub(test_value_1, test_value_2, &result_dec);
  s21_decimal_to_string(result_str, 32, result_dec);
  ck_assert_str_eq(result_str, correct_str);
}
END_TEST

START_TEST(test_s21_sub4) {
  s21_decimal test_value_1 = {{0, 0, 1, 0}};
  s21_decimal test_value_2 = {{1, 0, 0, 0}};
  s21_decimal result_dec;
  s21_decimal correct_dec = {{-1, -1, 0, 0}};
  int result_int;
  s21_sub(test_value_1, test_value_2, &result_dec);
  result_int = s21_is_equal(result_dec, correct_dec);
  ck_assert_int_eq(result_int, 1);
}
END_TEST
// SUB TESTS END <--

// MUL TESTS START -->
START_TEST(test_s21_mul1) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  int result_int;
  s21_from_int_to_decimal(10, &test_value_1);
  s21_from_int_to_decimal(10, &test_value_2);
  s21_mul(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 100);
}
END_TEST

START_TEST(test_s21_mul2) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  int result_int;
  s21_from_int_to_decimal(-10, &test_value_1);
  s21_from_int_to_decimal(-10, &test_value_2);
  s21_mul(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 100);
}
END_TEST

START_TEST(test_s21_mul3) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  int result_int;
  s21_from_int_to_decimal(0, &test_value_1);
  s21_from_int_to_decimal(-10, &test_value_2);
  s21_negate(test_value_1, &test_value_1);
  s21_mul(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_mul4) {
  s21_decimal test_value_1 = {{-1, -1, -1, 28 << 16}};
  s21_decimal test_value_2 = {{-1, -1, -1, 28 << 16}};
  s21_decimal result_dec;
  char result_str[32];
  char correct_str[32] = "+62.771017353866807638357894230";
  s21_mul(test_value_1, test_value_2, &result_dec);
  s21_decimal_to_string(result_str, 32, result_dec);
  ck_assert_str_eq(result_str, correct_str);
}
END_TEST

START_TEST(test_s21_mul5) {
  s21_decimal test_value_1 = {{-1, -1, -1, 28 << 16}};
  s21_decimal test_value_2 = {{-1, -1, -1, 28 << 16}};
  s21_decimal result_dec;
  char result_str[32];
  char correct_str[32] = "-62.771017353866807638357894230";
  s21_negate(test_value_1, &test_value_1);
  s21_mul(test_value_1, test_value_2, &result_dec);
  s21_decimal_to_string(result_str, 32, result_dec);
  ck_assert_str_eq(result_str, correct_str);
}
END_TEST

START_TEST(test_s21_mul6) {
  s21_decimal test_value_1 = {{-1, -1, -1, 28 << 16}};
  s21_decimal test_value_2 = {{-1, -1, -1, 28 << 16}};
  s21_decimal result_dec;
  char result_str[32];
  char correct_str[32] = "+62.771017353866807638357894230";
  s21_negate(test_value_1, &test_value_1);
  s21_negate(test_value_2, &test_value_2);
  s21_mul(test_value_1, test_value_2, &result_dec);
  s21_decimal_to_string(result_str, 32, result_dec);
  ck_assert_str_eq(result_str, correct_str);
}
END_TEST

START_TEST(test_s21_mul7) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  int result_int;
  s21_from_int_to_decimal(0, &test_value_1);
  s21_from_int_to_decimal(-10, &test_value_2);
  s21_mul(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_mul_error1) {
  s21_decimal test_value_1 = {{-1, -1, -1, 0}};
  s21_decimal test_value_2 = {{-1, -1, -1, 0}};
  s21_decimal result_dec = {{2, 2, 2, 0}};
  char given_str[32];
  char result_str[32];
  int result_error;
  s21_decimal_to_string(given_str, 32, result_dec);
  result_error = s21_mul(test_value_1, test_value_2, &result_dec);
  s21_decimal_to_string(result_str, 32, result_dec);
  ck_assert_int_eq(result_error, 1);
  ck_assert_str_eq(given_str, result_str);
}
END_TEST

START_TEST(test_s21_mul_error2) {
  s21_decimal test_value_1 = {{1, 0, 0, 28 << 16}};
  s21_decimal test_value_2 = {{1, 0, 0, 28 << 16}};
  s21_decimal result_dec;
  int result_error;
  int result_int;
  result_error = s21_mul(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_error, 0);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_mul_error3) {
  s21_decimal test_value_1 = {{-1, -1, -1, 2 << 16}};
  s21_decimal test_value_2 = {{-1, -1, -1, 2 << 16}};
  s21_decimal result_dec = {{2, 2, 2, 0}};
  char given_str[32];
  char result_str[32];
  int result_error;
  s21_decimal_to_string(given_str, 32, result_dec);
  result_error = s21_mul(test_value_1, test_value_2, &result_dec);
  s21_decimal_to_string(result_str, 32, result_dec);
  ck_assert_int_eq(result_error, 1);
  ck_assert_str_eq(given_str, result_str);
}
END_TEST

START_TEST(test_s21_mul_error4) {
  s21_decimal test_value_1 = {{-1, -1, -1, 0}};
  s21_decimal test_value_2;
  s21_decimal result_dec;
  int result_error;
  s21_negate(test_value_1, &test_value_1);
  s21_from_int_to_decimal(2, &test_value_2);
  result_error = s21_mul(test_value_1, test_value_2, &result_dec);
  ck_assert_int_eq(result_error, 2);
}
END_TEST

START_TEST(test_s21_mul_error5) {
  s21_decimal test_value_1 = {{-1, -1, -1, 2 << 16}};
  s21_decimal test_value_2;
  s21_decimal result_dec;
  int result_error;
  s21_negate(test_value_1, &test_value_1);
  s21_from_int_to_decimal(1111111138, &test_value_2);
  result_error = s21_mul(test_value_1, test_value_2, &result_dec);
  ck_assert_int_eq(result_error, 2);
}
END_TEST
// MUL TESTS END <--

// COMPARE TESTS START -->
START_TEST(test_s21_is_less1) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_int_to_decimal(0, &test_value_1);
  s21_from_int_to_decimal(0, &test_value_2);
  result_int = s21_is_less(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_is_less2) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_int_to_decimal(10, &test_value_1);
  s21_from_int_to_decimal(0, &test_value_2);
  result_int = s21_is_less(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_is_less3) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_int_to_decimal(0, &test_value_1);
  s21_from_int_to_decimal(-10, &test_value_2);
  result_int = s21_is_less(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_is_less4) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_float_to_decimal(-1.55551, &test_value_1);
  s21_from_float_to_decimal(-1.5555, &test_value_2);
  result_int = s21_is_less(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_less5) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_float_to_decimal(0.0, &test_value_1);
  s21_from_float_to_decimal(0.0, &test_value_2);
  s21_negate(test_value_1, &test_value_1);
  result_int = s21_is_less(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_is_less6) {
  int result_int;
  s21_decimal test_value_1 = {{-1, -1, -1, 0}};
  s21_decimal test_value_2 = {{-1, -1, -1, 0}};
  s21_negate(test_value_2, &test_value_2);
  s21_negate(test_value_1, &test_value_1);
  result_int = s21_is_less(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_is_less7) {
  int result_int;
  s21_decimal test_value_1 = {{-1, -1, -1, 0}};
  s21_decimal test_value_2 = {{-1, -1, -1, 0}};
  s21_negate(test_value_1, &test_value_1);
  result_int = s21_is_less(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal1) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_int_to_decimal(0, &test_value_1);
  s21_from_int_to_decimal(0, &test_value_2);
  result_int = s21_is_less_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal2) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_int_to_decimal(10, &test_value_1);
  s21_from_int_to_decimal(0, &test_value_2);
  result_int = s21_is_less_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_is_less_or_equal3) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_int_to_decimal(0, &test_value_1);
  s21_from_int_to_decimal(-10, &test_value_2);
  result_int = s21_is_less_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_is_less_or_equal4) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_float_to_decimal(-1.55551, &test_value_1);
  s21_from_float_to_decimal(-1.5555, &test_value_2);
  result_int = s21_is_less_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal5) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_float_to_decimal(0.0, &test_value_1);
  s21_from_float_to_decimal(0.0, &test_value_2);
  s21_negate(test_value_1, &test_value_1);
  result_int = s21_is_less_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal6) {
  int result_int;
  s21_decimal test_value_1 = {{-1, -1, -1, 0}};
  s21_decimal test_value_2 = {{-1, -1, -1, 0}};
  s21_negate(test_value_2, &test_value_2);
  s21_negate(test_value_1, &test_value_1);
  result_int = s21_is_less_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal7) {
  int result_int;
  s21_decimal test_value_1 = {{-1, -1, -1, 0}};
  s21_decimal test_value_2 = {{-1, -1, -1, 0}};
  s21_negate(test_value_1, &test_value_1);
  result_int = s21_is_less_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal8) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_int_to_decimal(0, &test_value_1);
  s21_from_int_to_decimal(0, &test_value_2);
  s21_negate(test_value_1, &test_value_1);
  result_int = s21_is_less_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal9) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_int_to_decimal(0, &test_value_1);
  s21_from_int_to_decimal(0, &test_value_2);
  s21_negate(test_value_1, &test_value_1);
  s21_negate(test_value_2, &test_value_2);
  result_int = s21_is_less_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal10) {
  int result_int;
  s21_decimal test_value_1 = {{1, 0, 0, 28 << 16}};
  s21_decimal test_value_2;
  s21_from_float_to_decimal(0.0, &test_value_2);
  result_int = s21_is_less_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_is_greater1) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_int_to_decimal(0, &test_value_1);
  s21_from_int_to_decimal(0, &test_value_2);
  result_int = s21_is_greater(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_is_greater2) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_int_to_decimal(10, &test_value_1);
  s21_from_int_to_decimal(0, &test_value_2);
  result_int = s21_is_greater(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_greater3) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_int_to_decimal(0, &test_value_1);
  s21_from_int_to_decimal(-10, &test_value_2);
  result_int = s21_is_greater(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_greater4) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_float_to_decimal(1.55551, &test_value_1);
  s21_from_float_to_decimal(1.5555, &test_value_2);
  result_int = s21_is_greater(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_greater5) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_float_to_decimal(0.0, &test_value_1);
  s21_from_float_to_decimal(0.0, &test_value_2);
  s21_negate(test_value_1, &test_value_1);
  result_int = s21_is_greater(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_is_greater6) {
  int result_int;
  s21_decimal test_value_1 = {{-1, -1, -1, 0}};
  s21_decimal test_value_2 = {{-1, -1, -1, 0}};
  s21_negate(test_value_2, &test_value_2);
  s21_negate(test_value_1, &test_value_1);
  result_int = s21_is_greater(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_is_greater7) {
  int result_int;
  s21_decimal test_value_1 = {{-1, -1, -1, 0}};
  s21_decimal test_value_2 = {{-1, -1, -1, 0}};
  s21_negate(test_value_1, &test_value_1);
  result_int = s21_is_greater(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal1) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_int_to_decimal(0, &test_value_1);
  s21_from_int_to_decimal(0, &test_value_2);
  result_int = s21_is_greater_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal2) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_int_to_decimal(10, &test_value_1);
  s21_from_int_to_decimal(0, &test_value_2);
  result_int = s21_is_greater_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal3) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_int_to_decimal(0, &test_value_1);
  s21_from_int_to_decimal(-10, &test_value_2);
  result_int = s21_is_greater_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal4) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_float_to_decimal(1.55551, &test_value_1);
  s21_from_float_to_decimal(1.5555, &test_value_2);
  result_int = s21_is_greater_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal5) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_float_to_decimal(0.0, &test_value_1);
  s21_from_float_to_decimal(0.0, &test_value_2);
  s21_negate(test_value_1, &test_value_1);
  result_int = s21_is_greater_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal6) {
  int result_int;
  s21_decimal test_value_1 = {{-1, -1, -1, 0}};
  s21_decimal test_value_2 = {{-1, -1, -1, 0}};
  s21_negate(test_value_2, &test_value_2);
  s21_negate(test_value_1, &test_value_1);
  result_int = s21_is_greater_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal7) {
  int result_int;
  s21_decimal test_value_1 = {{-1, -1, -1, 0}};
  s21_decimal test_value_2 = {{-1, -1, -1, 0}};
  s21_negate(test_value_1, &test_value_1);
  result_int = s21_is_greater_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal8) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_int_to_decimal(0, &test_value_1);
  s21_from_int_to_decimal(0, &test_value_2);
  s21_negate(test_value_1, &test_value_1);
  result_int = s21_is_greater_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal9) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_int_to_decimal(0, &test_value_1);
  s21_from_int_to_decimal(0, &test_value_2);
  s21_negate(test_value_1, &test_value_1);
  s21_negate(test_value_2, &test_value_2);
  result_int = s21_is_greater_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal10) {
  int result_int;
  s21_decimal test_value_1 = {{1, 0, 0, 28 << 16}};
  s21_decimal test_value_2;
  s21_from_float_to_decimal(0.0, &test_value_2);
  result_int = s21_is_greater_or_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_equal1) {
  s21_decimal test_value_1 = {{1, 0, 0, 28 << 16}};
  s21_decimal test_value_2 = {{1, 0, 0, 28 << 16}};
  int result_int;
  s21_negate(test_value_1, &test_value_1);
  s21_negate(test_value_2, &test_value_2);
  result_int = s21_is_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_equal2) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_float_to_decimal(0.0, &test_value_1);
  s21_from_float_to_decimal(0.0, &test_value_2);
  result_int = s21_is_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_equal3) {
  s21_decimal test_value_1 = {{1, 0, 0, 28 << 16}};
  s21_decimal test_value_2;
  int result_int;
  s21_from_float_to_decimal(0.0, &test_value_2);
  result_int = s21_is_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_is_equal4) {
  s21_decimal test_value_1 = {{-1, -1, -1, 28 << 16}};
  s21_decimal test_value_2 = {{-1, -1, -1, 28 << 16}};
  int result_int;
  s21_negate(test_value_1, &test_value_1);
  s21_negate(test_value_2, &test_value_2);
  result_int = s21_is_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_equal5) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_int_to_decimal(-2147483647, &test_value_1);
  s21_from_int_to_decimal(-2147483647, &test_value_2);
  result_int = s21_is_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_equal6) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_float_to_decimal(0.0, &test_value_1);
  s21_from_float_to_decimal(0.0, &test_value_2);
  s21_negate(test_value_1, &test_value_1);
  result_int = s21_is_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_equal7) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_float_to_decimal(0.0, &test_value_1);
  s21_from_float_to_decimal(0.0, &test_value_2);
  s21_negate(test_value_2, &test_value_2);
  result_int = s21_is_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_not_equal1) {
  s21_decimal test_value_1 = {{1, 0, 0, 28 << 16}};
  s21_decimal test_value_2 = {{1, 0, 0, 28 << 16}};
  int result_int;
  s21_negate(test_value_1, &test_value_1);
  s21_negate(test_value_2, &test_value_2);
  result_int = s21_is_not_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_is_not_equal2) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_float_to_decimal(0.0, &test_value_1);
  s21_from_float_to_decimal(0.0, &test_value_2);
  result_int = s21_is_not_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_is_not_equal3) {
  s21_decimal test_value_1 = {{1, 0, 0, 28 << 16}};
  s21_decimal test_value_2;
  int result_int;
  s21_from_float_to_decimal(0.0, &test_value_2);
  result_int = s21_is_not_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_is_not_equal4) {
  s21_decimal test_value_1 = {{-1, -1, -1, 28 << 16}};
  s21_decimal test_value_2 = {{-1, -1, -1, 28 << 16}};
  int result_int;
  s21_negate(test_value_1, &test_value_1);
  s21_negate(test_value_2, &test_value_2);
  result_int = s21_is_not_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_is_not_equal5) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_int_to_decimal(-2147483647, &test_value_1);
  s21_from_int_to_decimal(-2147483647, &test_value_2);
  result_int = s21_is_not_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_is_not_equal6) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_float_to_decimal(0.0, &test_value_1);
  s21_from_float_to_decimal(0.0, &test_value_2);
  s21_negate(test_value_1, &test_value_1);
  result_int = s21_is_not_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(test_s21_is_not_equal7) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  int result_int;
  s21_from_float_to_decimal(0.0, &test_value_1);
  s21_from_float_to_decimal(0.0, &test_value_2);
  s21_negate(test_value_2, &test_value_2);
  result_int = s21_is_not_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 0);
}
END_TEST
// COMPARE TESTS END <--

// DIV TESTS START -->
START_TEST(test_s21_div1) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  int result_int;
  s21_from_int_to_decimal(25, &test_value_1);
  s21_from_int_to_decimal(5, &test_value_2);
  s21_div(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 5);
}
END_TEST

START_TEST(test_s21_div2) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  char result_str[32];
  char str[32] = "+3.3333333333333333333333333333";
  s21_from_int_to_decimal(10, &test_value_1);
  s21_from_int_to_decimal(3, &test_value_2);
  s21_div(test_value_1, test_value_2, &result_dec);
  s21_decimal_to_string(result_str, 32, result_dec);
  ck_assert_str_eq(str, result_str);
}
END_TEST

START_TEST(test_s21_div3) {
  s21_decimal test_value_1 = {{-1, -1, -1, 0}};
  s21_decimal test_value_2 = {{-1, -1, -1, 0}};
  s21_decimal result_dec;
  s21_div(test_value_1, test_value_2, &result_dec);
  int result_int;
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_div4) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  float result_float;
  s21_from_float_to_decimal(1.55551, &test_value_1);
  s21_from_float_to_decimal(0.5, &test_value_2);
  s21_div(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_float(result_dec, &result_float);
  ck_assert_float_eq(result_float, 3.11102);
}
END_TEST

START_TEST(test_s21_div5) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  float result_float;
  s21_from_int_to_decimal(0, &test_value_1);
  s21_from_float_to_decimal(0.5, &test_value_2);
  s21_div(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_float(result_dec, &result_float);
  ck_assert_float_eq(result_float, 0.0);
}
END_TEST

START_TEST(test_s21_div6) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  float result_float;
  s21_from_int_to_decimal(-5, &test_value_1);
  s21_from_int_to_decimal(20, &test_value_2);
  s21_div(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_float(result_dec, &result_float);
  ck_assert_float_eq(result_float, -0.25);
}
END_TEST

START_TEST(test_s21_div7) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  float result_float;
  s21_from_int_to_decimal(-5, &test_value_1);
  s21_from_int_to_decimal(-20, &test_value_2);
  s21_div(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_float(result_dec, &result_float);
  ck_assert_float_eq(result_float, 0.25);
}
END_TEST

START_TEST(test_s21_div8) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  float result_float;
  s21_from_int_to_decimal(5, &test_value_1);
  s21_from_int_to_decimal(-20, &test_value_2);
  s21_div(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_float(result_dec, &result_float);
  ck_assert_float_eq(result_float, -0.25);
}
END_TEST

START_TEST(test_s21_div9) {
  s21_decimal test_value_1 = {{1, -4, -1, 0}};
  s21_decimal test_value_2 = {{876, 0, 0, 0}};
  s21_decimal correct_result = {{1882725390, 1372820596, 490293070, 2 << 16}};
  s21_decimal result_dec;
  s21_div(test_value_1, test_value_2, &result_dec);
  int result_int;
  s21_from_decimal_to_int(result_dec, &result_int);
  result_int = s21_is_equal(correct_result, result_dec);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_div_error1) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  int result_error;
  s21_from_int_to_decimal(5, &test_value_1);
  s21_from_int_to_decimal(0, &test_value_2);
  result_error = s21_div(test_value_1, test_value_2, &result_dec);
  ck_assert_float_eq(result_error, 3);
}
END_TEST

START_TEST(test_s21_div_error2) {
  s21_decimal test_value_1 = {{-1, -1, -1, 0}};
  s21_decimal test_value_2 = {{785, 0, 0, 4 << 16}};
  s21_decimal result_dec;
  int result_error;
  result_error = s21_div(test_value_1, test_value_2, &result_dec);
  ck_assert_int_eq(result_error, 1);
}
END_TEST
// DIV TESTS END <--

// MOD TESTS START -->
START_TEST(test_s21_mod1) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  int result_int;
  s21_from_int_to_decimal(10, &test_value_1);
  s21_from_int_to_decimal(3, &test_value_2);
  s21_mod(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_mod2) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  int result_int;
  s21_from_int_to_decimal(225226, &test_value_1);
  s21_from_int_to_decimal(41, &test_value_2);
  s21_mod(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 13);
}
END_TEST

START_TEST(test_s21_mod3) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec;
  float result_float;
  s21_from_float_to_decimal(-14.5564, &test_value_1);
  s21_from_int_to_decimal(2, &test_value_2);
  s21_mod(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_float(result_dec, &result_float);
  ck_assert_int_eq(result_float, -0.5564);
}
END_TEST

START_TEST(test_s21_mod4) {
  s21_decimal test_value_1 = {{-1, -1, -1, 0}};
  s21_decimal test_value_2;
  s21_decimal result_dec;
  float result_float;
  s21_from_float_to_decimal(-41.566, &test_value_2);
  s21_mod(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_float(result_dec, &result_float);
  ck_assert_float_eq(result_float, 12.39);
}
END_TEST

START_TEST(test_s21_mod5) {
  s21_decimal test_value_1 = {{-1, -1, -1, 0}};
  s21_decimal test_value_2 = {{-1, -1, -1, 0}};
  s21_decimal result_dec;
  float result_float;
  s21_mod(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_float(result_dec, &result_float);
  ck_assert_float_eq(result_float, 0.0);
}
END_TEST

START_TEST(test_s21_mod6) {
  s21_decimal test_value_1 = {{1879048192, 3003322535, 3794707603, 0}};
  s21_decimal test_value_2 = {{1, 0, 0, 3 << 16}};
  s21_decimal result_dec;
  float result_float;
  s21_mod(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_float(result_dec, &result_float);
  ck_assert_float_eq(result_float, 0);
}
END_TEST

START_TEST(test_s21_mod7) {
  s21_decimal test_value_1 = {{-1, -1, -1, 0}};
  s21_decimal test_value_2;
  s21_decimal result_dec;
  float result_float;
  s21_negate(test_value_1, &test_value_1);
  s21_from_float_to_decimal(41.566, &test_value_2);
  s21_mod(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_float(result_dec, &result_float);
  ck_assert_float_eq(result_float, -12.39);
}
END_TEST

START_TEST(test_s21_mod_error) {
  s21_decimal test_value_1;
  s21_decimal test_value_2;
  s21_decimal result_dec = {{1, 1, 1, 0}};
  float result_float;
  int result_error;
  s21_from_int_to_decimal(5, &test_value_1);
  s21_from_int_to_decimal(0, &test_value_2);
  result_error = s21_mod(test_value_1, test_value_2, &result_dec);
  s21_from_decimal_to_float(result_dec, &result_float);
  ck_assert_float_eq(result_error, 3);
}
END_TEST
// MOD TESTS END <--

// OTHER TESTS START -->
START_TEST(test_s21_floor1) {
  s21_decimal test_value_1 = {{1, 0, 0, 28 << 16}};
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  int result_int;
  s21_floor(test_value_1, &test_value_1);
  result_int = s21_is_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_floor2) {
  s21_decimal test_value_1 = {{1, 0, 0, 28 << 16}};
  s21_decimal test_value_2 = {{1, 0, 0, 0}};
  int result_int;
  s21_negate(test_value_1, &test_value_1);
  s21_negate(test_value_2, &test_value_2);
  s21_floor(test_value_1, &test_value_1);
  result_int = s21_is_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_floor3) {
  s21_decimal test_value_1;
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  int result_int;
  s21_from_int_to_decimal(0, &test_value_1);
  s21_floor(test_value_1, &test_value_1);
  result_int = s21_is_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_floor4) {
  s21_decimal test_value_1;
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  int result_int;
  s21_from_int_to_decimal(0, &test_value_1);
  s21_negate(test_value_1, &test_value_1);
  s21_floor(test_value_1, &test_value_1);
  result_int = s21_is_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_floor5) {
  s21_decimal test_value_1;
  s21_decimal test_value_2 = {{15, 0, 0, 0}};
  int result_int;
  s21_from_float_to_decimal(15.5, &test_value_1);
  s21_floor(test_value_1, &test_value_1);
  result_int = s21_is_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_floor6) {
  s21_decimal test_value_1;
  s21_decimal test_value_2 = {{16, 0, 0, 0}};
  int result_int;
  s21_from_float_to_decimal(15.5, &test_value_1);
  s21_negate(test_value_1, &test_value_1);
  s21_negate(test_value_2, &test_value_2);
  s21_floor(test_value_1, &test_value_1);
  result_int = s21_is_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_round1) {
  s21_decimal test_value_1 = {{1, 0, 0, 28 << 16}};
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  int result_int;
  s21_round(test_value_1, &test_value_1);
  result_int = s21_is_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_round2) {
  s21_decimal test_value_1 = {{1, 0, 0, 28 << 16}};
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  int result_int;
  s21_negate(test_value_1, &test_value_1);
  s21_round(test_value_1, &test_value_1);
  result_int = s21_is_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_round3) {
  s21_decimal test_value_1;
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  int result_int;
  s21_from_int_to_decimal(0, &test_value_1);
  s21_round(test_value_1, &test_value_1);
  result_int = s21_is_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_round4) {
  s21_decimal test_value_1;
  s21_decimal test_value_2 = {{0, 0, 0, 0}};
  int result_int;
  s21_from_int_to_decimal(0, &test_value_1);
  s21_negate(test_value_1, &test_value_1);
  s21_round(test_value_1, &test_value_1);
  result_int = s21_is_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_round5) {
  s21_decimal test_value_1;
  s21_decimal test_value_2 = {{16, 0, 0, 0}};
  int result_int;
  s21_from_float_to_decimal(15.5, &test_value_1);
  s21_round(test_value_1, &test_value_1);
  result_int = s21_is_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST

START_TEST(test_s21_round6) {
  s21_decimal test_value_1;
  s21_decimal test_value_2 = {{16, 0, 0, 0}};
  int result_int;
  s21_from_float_to_decimal(15.5, &test_value_1);
  s21_negate(test_value_1, &test_value_1);
  s21_negate(test_value_2, &test_value_2);
  s21_round(test_value_1, &test_value_1);
  result_int = s21_is_equal(test_value_1, test_value_2);
  ck_assert_int_eq(result_int, 1);
}
END_TEST
// OTHER TESTS END <--

// CONVERT TESTS START -->
START_TEST(test_s21_float_to_decimal1) {
  s21_decimal test_value_1;
  int result_error;
  result_error =
      s21_from_float_to_decimal(80000000000000000000000000000.0, &test_value_1);
  ck_assert_int_eq(result_error, 1);
}
END_TEST

START_TEST(test_s21_float_to_decimal2) {
  s21_decimal test_value_1;
  int result_error;
  result_error = s21_from_float_to_decimal(0.0000000000000000000000000000000001,
                                           &test_value_1);
  ck_assert_int_eq(result_error, 1);
}
END_TEST

START_TEST(test_s21_float_to_decimal3) {
  s21_decimal test_value_1;
  float result_float;
  s21_from_float_to_decimal(0.0000000000000000000000000000000001,
                            &test_value_1);
  s21_from_decimal_to_float(test_value_1, &result_float);
  ck_assert_float_eq(result_float, 0.0);
}
END_TEST

START_TEST(test_s21_float_to_decimal4) {
  s21_decimal test_value_1;
  float result_float;
  s21_from_float_to_decimal(8000000000000000.0, &test_value_1);
  s21_from_decimal_to_float(test_value_1, &result_float);
  ck_assert_float_eq(result_float, 8000000000000000.0);
}
END_TEST
// CONVERT TESTS END <--

Suite *suite_insert(void) {
  Suite *s = suite_create("Поiхали");
  TCase *tc = tcase_create("insert_tc");

  // ADD TESTS START -->
  tcase_add_test(tc, test_s21_add_negative);
  tcase_add_test(tc, test_s21_add_large);
  tcase_add_test(tc, test_s21_add_max_neg_max_pos);
  tcase_add_test(tc, test_s21_add_zero1);
  tcase_add_test(tc, test_s21_add_zero2);
  tcase_add_test(tc, test_s21_add_zero3);
  tcase_add_test(tc, test_s21_add_zero4);
  tcase_add_test(tc, test_s21_add_zero5);
  tcase_add_test(tc, test_s21_add1);
  tcase_add_test(tc, test_s21_add2);
  tcase_add_test(tc, test_s21_add3);
  tcase_add_test(tc, test_s21_add4);
  // ADD TESTS END <--

  // SUB TESTS START -->
  tcase_add_test(tc, test_s21_sub_large);
  tcase_add_test(tc, test_s21_sub_max_pos);
  tcase_add_test(tc, test_s21_sub_zero_max_pos);
  tcase_add_test(tc, test_s21_sub_zero_max_neg);
  tcase_add_test(tc, test_s21_sub_zero1);
  tcase_add_test(tc, test_s21_sub_zero2);
  tcase_add_test(tc, test_s21_sub_zero3);
  tcase_add_test(tc, test_s21_sub_zero4);
  tcase_add_test(tc, test_s21_sub1);
  tcase_add_test(tc, test_s21_sub2);
  tcase_add_test(tc, test_s21_sub3);
  tcase_add_test(tc, test_s21_sub4);
  // SUB TESTS END <--

  // MUL TESTS START -->
  tcase_add_test(tc, test_s21_mul1);
  tcase_add_test(tc, test_s21_mul2);
  tcase_add_test(tc, test_s21_mul3);
  tcase_add_test(tc, test_s21_mul4);
  tcase_add_test(tc, test_s21_mul5);
  tcase_add_test(tc, test_s21_mul6);
  tcase_add_test(tc, test_s21_mul7);
  tcase_add_test(tc, test_s21_mul_error1);
  tcase_add_test(tc, test_s21_mul_error2);
  tcase_add_test(tc, test_s21_mul_error3);
  tcase_add_test(tc, test_s21_mul_error4);
  tcase_add_test(tc, test_s21_mul_error5);
  // MUL TESTS END <--

  // DIV TESTS START -->
  tcase_add_test(tc, test_s21_div1);
  tcase_add_test(tc, test_s21_div2);
  tcase_add_test(tc, test_s21_div3);
  tcase_add_test(tc, test_s21_div4);
  tcase_add_test(tc, test_s21_div5);
  tcase_add_test(tc, test_s21_div6);
  tcase_add_test(tc, test_s21_div7);
  tcase_add_test(tc, test_s21_div8);
  tcase_add_test(tc, test_s21_div9);
  tcase_add_test(tc, test_s21_div_error1);
  tcase_add_test(tc, test_s21_div_error2);
  // DIV TESTS END <--

  // MOD TESTS START -->
  tcase_add_test(tc, test_s21_mod1);
  tcase_add_test(tc, test_s21_mod2);
  tcase_add_test(tc, test_s21_mod3);
  tcase_add_test(tc, test_s21_mod4);
  tcase_add_test(tc, test_s21_mod5);
  tcase_add_test(tc, test_s21_mod6);
  tcase_add_test(tc, test_s21_mod7);
  tcase_add_test(tc, test_s21_mod_error);
  // MOD TESTS END <--

  // CONVERT TESTS START -->
  tcase_add_test(tc, test_s21_float_to_decimal1);
  tcase_add_test(tc, test_s21_float_to_decimal2);
  tcase_add_test(tc, test_s21_float_to_decimal3);
  tcase_add_test(tc, test_s21_float_to_decimal4);
  // CONVERT TESTS END <--

  // COMPARE TESTS START -->
  tcase_add_test(tc, test_s21_is_less1);
  tcase_add_test(tc, test_s21_is_less2);
  tcase_add_test(tc, test_s21_is_less3);
  tcase_add_test(tc, test_s21_is_less4);
  tcase_add_test(tc, test_s21_is_less5);
  tcase_add_test(tc, test_s21_is_less6);
  tcase_add_test(tc, test_s21_is_less7);
  tcase_add_test(tc, test_s21_is_less_or_equal1);
  tcase_add_test(tc, test_s21_is_less_or_equal2);
  tcase_add_test(tc, test_s21_is_less_or_equal3);
  tcase_add_test(tc, test_s21_is_less_or_equal4);
  tcase_add_test(tc, test_s21_is_less_or_equal5);
  tcase_add_test(tc, test_s21_is_less_or_equal6);
  tcase_add_test(tc, test_s21_is_less_or_equal7);
  tcase_add_test(tc, test_s21_is_less_or_equal8);
  tcase_add_test(tc, test_s21_is_less_or_equal9);
  tcase_add_test(tc, test_s21_is_less_or_equal10);
  tcase_add_test(tc, test_s21_is_greater1);
  tcase_add_test(tc, test_s21_is_greater2);
  tcase_add_test(tc, test_s21_is_greater3);
  tcase_add_test(tc, test_s21_is_greater4);
  tcase_add_test(tc, test_s21_is_greater5);
  tcase_add_test(tc, test_s21_is_greater6);
  tcase_add_test(tc, test_s21_is_greater7);
  tcase_add_test(tc, test_s21_is_greater_or_equal1);
  tcase_add_test(tc, test_s21_is_greater_or_equal2);
  tcase_add_test(tc, test_s21_is_greater_or_equal3);
  tcase_add_test(tc, test_s21_is_greater_or_equal4);
  tcase_add_test(tc, test_s21_is_greater_or_equal5);
  tcase_add_test(tc, test_s21_is_greater_or_equal6);
  tcase_add_test(tc, test_s21_is_greater_or_equal7);
  tcase_add_test(tc, test_s21_is_greater_or_equal8);
  tcase_add_test(tc, test_s21_is_greater_or_equal9);
  tcase_add_test(tc, test_s21_is_greater_or_equal10);
  tcase_add_test(tc, test_s21_is_equal1);
  tcase_add_test(tc, test_s21_is_equal2);
  tcase_add_test(tc, test_s21_is_equal3);
  tcase_add_test(tc, test_s21_is_equal4);
  tcase_add_test(tc, test_s21_is_equal5);
  tcase_add_test(tc, test_s21_is_equal6);
  tcase_add_test(tc, test_s21_is_equal7);
  tcase_add_test(tc, test_s21_is_not_equal1);
  tcase_add_test(tc, test_s21_is_not_equal2);
  tcase_add_test(tc, test_s21_is_not_equal3);
  tcase_add_test(tc, test_s21_is_not_equal4);
  tcase_add_test(tc, test_s21_is_not_equal5);
  tcase_add_test(tc, test_s21_is_not_equal6);
  tcase_add_test(tc, test_s21_is_not_equal7);
  // COMPARE TESTS END <--

  // OTHER TESTS START -->
  tcase_add_test(tc, test_s21_floor1);
  tcase_add_test(tc, test_s21_floor2);
  tcase_add_test(tc, test_s21_floor3);
  tcase_add_test(tc, test_s21_floor4);
  tcase_add_test(tc, test_s21_floor5);
  tcase_add_test(tc, test_s21_floor6);
  tcase_add_test(tc, test_s21_round1);
  tcase_add_test(tc, test_s21_round2);
  tcase_add_test(tc, test_s21_round3);
  tcase_add_test(tc, test_s21_round4);
  tcase_add_test(tc, test_s21_round5);
  tcase_add_test(tc, test_s21_round6);
  // OTHER TESTS END <--

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
