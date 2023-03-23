#include <check.h>

#include "s21_smart_calc.h"

typedef struct {
  char *sin;
  char *cos;
  char *tan;
  char *asin;
  char *acos;
  char *atan;
  char *log;
  char *ln;
  char *sqrt;
  char *mod;
  char *zero;
  char *one;
  char *two;
  char *three;
  char *four;
  char *five;
  char *six;
  char *seven;
  char *eight;
  char *nine;
  char *x;
  char *point;
  char *pow;
  char *cl_bracket;
  char *op_bracket;
  char *div;
  char *mul;
  char *minus;
  char *plus;
  char *result;
  char *clear;
  char *backspace;
} s21_buttons;

s21_buttons buttons = {"sin", "cos",  "tan",   "asin", "acos", "atan", "log",
                       "ln",  "sqrt", " mod ", "0",    "1",    "2",    "3",
                       "4",   "5",    "6",     "7",    "8",    "9",    "x",
                       ".",   "^",    ")",     "(",    " / ",  " * ",  " - ",
                       " + ", "=",    "C",     "<--"};

void s21_click_button(char *button, char *output) {
  char button_text[10] = {0};
  strncpy(button_text, button, strlen(button));
  s21_append_buffer(button_text, output);
}

// SMART_CALC TESTS START -->
START_TEST(test_normal_expression_1) {
  char *input = "15.23 + 55.512 - 512.567 * 56.9873 / 32^2 * sin(15.067)";
  char output[BUFFER_SIZE] = {0};
  char *expected_output = "53.6848463";
  s21_get_postfix(input, output);
  s21_get_answer(output, output, 0.0 / 0.0, 0);
  ck_assert_str_eq(output, expected_output);
}
END_TEST

START_TEST(test_normal_expression_2) {
  char *input = "sin(cos(tan(ln(1789.25))))";
  char output[BUFFER_SIZE] = {0};
  char *expected_output = "-0.762874";
  s21_get_postfix(input, output);
  s21_get_answer(output, output, 0.0 / 0.0, 0);
  ck_assert_str_eq(output, expected_output);
}
END_TEST

START_TEST(test_normal_expression_3) {
  char *input = "-125 + (-152) * 15.5 - (-0.0)";
  char output[BUFFER_SIZE] = {0};
  char *expected_output = "-2481";
  s21_get_postfix(input, output);
  s21_get_answer(output, output, 0.0 / 0.0, 0);
  ck_assert_str_eq(output, expected_output);
}
END_TEST

START_TEST(test_normal_expression_4) {
  char *input = "sqrt(1678) * (-log(15616.1236)) mod (+15)";
  char output[BUFFER_SIZE] = {0};
  char *expected_output = "8.2169892";
  s21_get_postfix(input, output);
  s21_get_answer(output, output, 0.0 / 0.0, 0);
  ck_assert_str_eq(output, expected_output);
}
END_TEST

START_TEST(test_normal_expression_5) {
  char *input = "125125.235 / 152.521 * (+cos(52.2^4)) / tan(170.2)";
  char output[BUFFER_SIZE] = {0};
  char *expected_output = "811.0892279";
  s21_get_postfix(input, output);
  s21_get_answer(output, output, 0.0 / 0.0, 0);
  ck_assert_str_eq(output, expected_output);
}
END_TEST

START_TEST(test_normal_expression_6) {
  char *input = "atan(-16789.162) + asin(-0.516123) - acos(0.999999)";
  char output[BUFFER_SIZE] = {0};
  char *expected_output = "-121.1501633";
  s21_get_postfix(input, output);
  s21_get_answer(output, output, 0.0 / 0.0, 1);
  ck_assert_str_eq(output, expected_output);
}
END_TEST

START_TEST(test_normal_expression_7) {
  char *input = "15 mod 2";
  char output[BUFFER_SIZE] = {0};
  char *expected_output = "1";
  s21_get_postfix(input, output);
  s21_get_answer(output, output, 0.0 / 0.0, 1);
  ck_assert_str_eq(output, expected_output);
}
END_TEST

START_TEST(test_normal_expression_8) {
  char *input =
      "15.6 * 356 + 152 - (-246 * 2 + 3^2^4 / 3^4) + ((15 * 2^5^(-2))^4^(-3))";
  char output[BUFFER_SIZE] = {0};
  char *expected_output = "-525242.3563267";
  s21_get_postfix(input, output);
  s21_get_answer(output, output, 0.0 / 0.0, 1);
  ck_assert_str_eq(output, expected_output);
}
END_TEST

START_TEST(test_with_x_expression_1) {
  char *input = "15 mod 2 * x";
  char output[BUFFER_SIZE] = {0};
  char *x_str = "-12";
  double x = 0.0 / 0.0;
  if (s21_is_double(x_str)) {
    x = s21_str_to_double(x_str);
  }
  char *expected_output = "-12";
  s21_get_postfix(input, output);
  s21_get_answer(output, output, x, 1);
  ck_assert_str_eq(output, expected_output);
}
END_TEST

START_TEST(test_with_x_expression_2) {
  char *input = "x * x + (+sin(x * 32.1) - 5.2)";
  char output[BUFFER_SIZE] = {0};
  char *x_str = "+12.1612";
  double x = 0.0 / 0.0;
  if (s21_is_double(x_str)) {
    x = s21_str_to_double(x_str);
  }
  char *expected_output = "143.2004356";
  s21_get_postfix(input, output);
  s21_get_answer(output, output, x, 1);
  ck_assert_str_eq(output, expected_output);
}
END_TEST

START_TEST(test_with_x_expression_3) {
  char *input = "+x^(-3) + acos(-x)";
  char output[BUFFER_SIZE] = {0};
  char *x_str = "0.3623";
  double x = 0.0 / 0.0;
  if (s21_is_double(x_str)) {
    x = s21_str_to_double(x_str);
  }
  char *expected_output = "22.9693869";
  s21_get_postfix(input, output);
  s21_get_answer(output, output, x, 0);
  ck_assert_str_eq(output, expected_output);
}
END_TEST

START_TEST(test_normal_expression_error_1) {
  char *input = "1 + (2 + (3 + 4)";
  char output[BUFFER_SIZE] = {0};
  int error = s21_get_postfix(input, output);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(test_normal_expression_error_2) {
  char *input = "3 + 2 /";
  char output[BUFFER_SIZE] = {0};
  s21_get_postfix(input, output);
  s21_stack operands;
  s21_stack_init(&operands);
  int error = s21_calculate_postfix(output, &operands, 0.0 / 0.0, 0);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(test_normal_expression_error_3) {
  char *input = "tan(15) + acos(4)";
  char output[BUFFER_SIZE] = {0};
  s21_get_postfix(input, output);
  s21_stack operands;
  s21_stack_init(&operands);
  int error = s21_calculate_postfix(output, &operands, 0.0 / 0.0, 0);
  ck_assert_int_eq(2, error);
}
END_TEST

START_TEST(test_normal_expression_error_4) {
  char *input = "tan(15) + acos(0.5) 5";
  char output[BUFFER_SIZE] = {0};
  s21_get_postfix(input, output);
  s21_stack operands;
  s21_stack_init(&operands);
  int error = s21_calculate_postfix(output, &operands, 0.0 / 0.0, 0);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(test_wrong_x_error) {
  char *input = "x + 4";
  char output[BUFFER_SIZE] = {0};
  char *x_str = "1asd";
  double x = 0.0 / 0.0;
  if (s21_is_double(x_str)) {
    x = s21_str_to_double(x_str);
  }
  s21_get_postfix(input, output);
  s21_stack operands;
  s21_stack_init(&operands);
  int error = s21_calculate_postfix(output, &operands, x, 0);
  ck_assert_int_eq(3, error);
}
END_TEST

START_TEST(test_buttons_1) {
  char output[BUFFER_SIZE] = {0};
  s21_click_button(buttons.x, output);
  s21_click_button(buttons.x, output);
  s21_click_button(buttons.point, output);
  s21_click_button(buttons.one, output);
  s21_click_button(buttons.five, output);
  s21_click_button(buttons.sin, output);
  s21_click_button(buttons.three, output);
  s21_click_button(buttons.mod, output);
  s21_click_button(buttons.point, output);
  s21_click_button(buttons.eight, output);
  s21_click_button(buttons.cl_bracket, output);
  char *expected_output = "x * x * 0.15 * sin(3 mod 0.8)";
  ck_assert_str_eq(expected_output, output);
}
END_TEST

START_TEST(test_buttons_2) {
  char output[BUFFER_SIZE] = {0};
  s21_click_button(buttons.zero, output);
  s21_click_button(buttons.zero, output);
  s21_click_button(buttons.five, output);
  s21_click_button(buttons.point, output);
  s21_click_button(buttons.sin, output);
  s21_click_button(buttons.cos, output);
  s21_click_button(buttons.minus, output);
  s21_click_button(buttons.minus, output);
  s21_click_button(buttons.five, output);
  s21_click_button(buttons.cl_bracket, output);
  s21_click_button(buttons.cl_bracket, output);
  s21_click_button(buttons.cl_bracket, output);
  s21_click_button(buttons.cl_bracket, output);
  char *expected_output = "5.0 * sin(cos(-(-5)))";
  ck_assert_str_eq(expected_output, output);
}
END_TEST

START_TEST(test_buttons_3) {
  char output[BUFFER_SIZE] = {0};
  s21_click_button(buttons.op_bracket, output);
  s21_click_button(buttons.point, output);
  s21_click_button(buttons.nine, output);
  s21_click_button(buttons.pow, output);
  s21_click_button(buttons.x, output);
  s21_click_button(buttons.cl_bracket, output);
  s21_click_button(buttons.seven, output);
  s21_click_button(buttons.point, output);
  s21_click_button(buttons.point, output);
  s21_click_button(buttons.acos, output);
  s21_click_button(buttons.zero, output);
  s21_click_button(buttons.point, output);
  s21_click_button(buttons.one, output);
  s21_click_button(buttons.cl_bracket, output);
  char *expected_output = "(0.9^x) * 7.0 * acos(0.1)";
  ck_assert_str_eq(expected_output, output);
}
END_TEST

START_TEST(test_buttons_4) {
  char output[BUFFER_SIZE] = {0};
  s21_click_button(buttons.point, output);
  s21_click_button(buttons.op_bracket, output);
  s21_click_button(buttons.nine, output);
  s21_click_button(buttons.mul, output);
  s21_click_button(buttons.eight, output);
  s21_click_button(buttons.minus, output);
  s21_click_button(buttons.plus, output);
  s21_click_button(buttons.three, output);
  s21_click_button(buttons.cl_bracket, output);
  s21_click_button(buttons.cl_bracket, output);
  char *expected_output = "0.0 * (9 * 8 - (+3))";
  ck_assert_str_eq(expected_output, output);
}
END_TEST

START_TEST(test_buttons_5) {
  char output[BUFFER_SIZE] = {0};
  s21_click_button(buttons.five, output);
  s21_click_button(buttons.point, output);
  s21_click_button(buttons.div, output);
  s21_click_button(buttons.pow, output);
  s21_click_button(buttons.mul, output);
  s21_click_button(buttons.four, output);
  s21_click_button(buttons.mul, output);
  s21_click_button(buttons.cl_bracket, output);
  s21_click_button(buttons.op_bracket, output);
  s21_click_button(buttons.mul, output);
  s21_click_button(buttons.six, output);
  s21_click_button(buttons.point, output);
  s21_click_button(buttons.mul, output);
  s21_click_button(buttons.cl_bracket, output);
  s21_click_button(buttons.five, output);
  s21_click_button(buttons.point, output);
  s21_click_button(buttons.cl_bracket, output);
  char *expected_output = "5.0 / 4 * (6.0 * 5.0)";
  ck_assert_str_eq(expected_output, output);
}
END_TEST

START_TEST(test_buttons_6) {
  char output[BUFFER_SIZE] = {0};
  s21_click_button(buttons.five, output);
  s21_click_button(buttons.point, output);
  s21_click_button(buttons.div, output);
  s21_click_button(buttons.pow, output);
  s21_click_button(buttons.mul, output);
  s21_click_button(buttons.four, output);
  s21_click_button(buttons.mul, output);
  s21_click_button(buttons.cl_bracket, output);
  s21_click_button(buttons.op_bracket, output);
  s21_click_button(buttons.mul, output);
  s21_click_button(buttons.six, output);
  s21_click_button(buttons.point, output);
  s21_click_button(buttons.mul, output);
  s21_click_button(buttons.cl_bracket, output);
  s21_click_button(buttons.five, output);
  s21_click_button(buttons.point, output);
  s21_click_button(buttons.cl_bracket, output);
  s21_click_button(buttons.backspace, output);
  s21_click_button(buttons.backspace, output);
  s21_click_button(buttons.backspace, output);
  s21_click_button(buttons.backspace, output);
  s21_click_button(buttons.backspace, output);
  char *expected_output = "5.0 / 4 * (6.0";
  ck_assert_str_eq(expected_output, output);
}
END_TEST

START_TEST(test_buttons_7) {
  char output[BUFFER_SIZE] = {0};
  s21_click_button(buttons.five, output);
  s21_click_button(buttons.point, output);
  s21_click_button(buttons.div, output);
  s21_click_button(buttons.pow, output);
  s21_click_button(buttons.mul, output);
  s21_click_button(buttons.four, output);
  s21_click_button(buttons.mul, output);
  s21_click_button(buttons.cl_bracket, output);
  s21_click_button(buttons.op_bracket, output);
  s21_click_button(buttons.mul, output);
  s21_click_button(buttons.six, output);
  s21_click_button(buttons.point, output);
  s21_click_button(buttons.mul, output);
  s21_click_button(buttons.cl_bracket, output);
  s21_click_button(buttons.five, output);
  s21_click_button(buttons.point, output);
  s21_click_button(buttons.cl_bracket, output);
  s21_click_button(buttons.minus, output);
  s21_click_button(buttons.clear, output);
  char *expected_output = "";
  ck_assert_str_eq(expected_output, output);
}
END_TEST

START_TEST(test_buttons_8) {
  char output[BUFFER_SIZE] = {0};
  s21_click_button(buttons.op_bracket, output);
  s21_click_button(buttons.point, output);
  s21_click_button(buttons.nine, output);
  s21_click_button(buttons.pow, output);
  s21_click_button(buttons.x, output);
  s21_click_button(buttons.cl_bracket, output);
  s21_click_button(buttons.seven, output);
  s21_click_button(buttons.point, output);
  s21_click_button(buttons.point, output);
  s21_click_button(buttons.acos, output);
  s21_click_button(buttons.zero, output);
  s21_click_button(buttons.point, output);
  s21_click_button(buttons.one, output);
  s21_click_button(buttons.cl_bracket, output);
  s21_click_button(buttons.backspace, output);
  s21_click_button(buttons.backspace, output);
  s21_click_button(buttons.backspace, output);
  s21_click_button(buttons.backspace, output);
  s21_click_button(buttons.backspace, output);
  s21_click_button(buttons.backspace, output);
  s21_click_button(buttons.backspace, output);
  s21_click_button(buttons.backspace, output);
  s21_click_button(buttons.backspace, output);
  s21_click_button(buttons.backspace, output);
  s21_click_button(buttons.backspace, output);
  s21_click_button(buttons.backspace, output);
  char *expected_output = "(0.9^";
  ck_assert_str_eq(expected_output, output);
}
END_TEST

START_TEST(test_buttons_9) {
  char output[BUFFER_SIZE] = {0};
  s21_click_button(buttons.zero, output);
  s21_click_button(buttons.zero, output);
  s21_click_button(buttons.point, output);
  s21_click_button(buttons.zero, output);
  s21_click_button(buttons.zero, output);
  s21_click_button(buttons.eight, output);
  s21_click_button(buttons.sin, output);
  s21_click_button(buttons.x, output);
  s21_click_button(buttons.cl_bracket, output);
  s21_click_button(buttons.zero, output);
  s21_click_button(buttons.zero, output);
  s21_click_button(buttons.five, output);
  char *expected_output = "0.008 * sin(x) * 5";
  ck_assert_str_eq(expected_output, output);
}
END_TEST

START_TEST(test_error_show_1) {
  char *input = "+x^(-3) + acos(-x) - (-425.2 + 15.23)";
  char output[BUFFER_SIZE] = {0};
  char *x_str = "";
  double x = 0.0 / 0.0;
  if (s21_is_double(x_str)) {
    x = s21_str_to_double(x_str);
  }
  char *expected_output = "Wrong X value";
  int error = s21_get_postfix(input, output);
  if (error) {
    sprintf(output, "Wrong expression");
  } else {
    s21_get_answer(output, output, x, 0);
  }
  ck_assert_str_eq(output, expected_output);
}
END_TEST

START_TEST(test_error_show_2) {
  char *input = "+x^(-3) + acos(-x) - (-425.2 + ";
  char output[BUFFER_SIZE] = {0};
  char *x_str = "0.12";
  double x = 0.0 / 0.0;
  if (s21_is_double(x_str)) {
    x = s21_str_to_double(x_str);
  }
  char *expected_output = "Wrong expression";
  int error = s21_get_postfix(input, output);
  if (error) {
    sprintf(output, "Wrong expression");
  } else {
    s21_get_answer(output, output, x, 0);
  }
  ck_assert_str_eq(output, expected_output);
}
END_TEST

START_TEST(test_error_show_3) {
  char *input = "+x^(-3) + acos(-x) - (-425.2 + 5)";
  char output[BUFFER_SIZE] = {0};
  char *x_str = "12";
  double x = 0.0 / 0.0;
  if (s21_is_double(x_str)) {
    x = s21_str_to_double(x_str);
  }
  char *expected_output = "Calc error";
  int error = s21_get_postfix(input, output);
  if (error) {
    sprintf(output, "Wrong expression");
  } else {
    s21_get_answer(output, output, x, 0);
  }
  ck_assert_str_eq(output, expected_output);
}
END_TEST

START_TEST(test_error_show_4) {
  char *input = "3 + 2 +";
  char output[BUFFER_SIZE] = {0};
  char *x_str = "";
  double x = 0.0 / 0.0;
  if (s21_is_double(x_str)) {
    x = s21_str_to_double(x_str);
  }
  char *expected_output = "Wrong expression";
  int error = s21_get_postfix(input, output);
  if (error) {
    sprintf(output, "Wrong expression");
  } else {
    s21_get_answer(output, output, x, 0);
  }
  ck_assert_str_eq(output, expected_output);
}
END_TEST

START_TEST(test_is_function_1) {
  char *input = "3 + 2 + sin(4)";
  int is_function = s21_is_function(input);
  ck_assert_int_eq(0, is_function);
}
END_TEST

START_TEST(test_is_function_2) {
  char *input = "3 + 2 + x * sin(4)";
  int is_function = s21_is_function(input);
  ck_assert_int_eq(1, is_function);
}
END_TEST

START_TEST(test_set_borders_1) {
  char *Ox1_str = "-52.1";
  char *Ox2_str = "12.231";
  char *Oy1_str = "-123";
  char *Oy2_str = "123";
  double Ox1 = 0;
  double Ox2 = 0;
  double Oy1 = 0;
  double Oy2 = 0;
  s21_get_field_borders(Ox1_str, Ox2_str, Oy1_str, Oy2_str, &Ox1, &Ox2, &Oy1,
                        &Oy2);
  char coords[100] = {0};
  sprintf(coords, "%lf %lf %lf %lf", Ox1, Ox2, Oy1, Oy2);
  char *expected_str = "-52.100000 12.231000 -123.000000 123.000000";
  ck_assert_str_eq(expected_str, coords);
}
END_TEST

START_TEST(test_set_borders_2) {
  char *Ox1_str = "-0.15125";
  char *Ox2_str = "5125.231";
  char *Oy1_str = "125.2513612";
  char *Oy2_str = "116126.24234";
  double Ox1 = 0;
  double Ox2 = 0;
  double Oy1 = 0;
  double Oy2 = 0;
  s21_get_field_borders(Ox1_str, Ox2_str, Oy1_str, Oy2_str, &Ox1, &Ox2, &Oy1,
                        &Oy2);
  char coords[100] = {0};
  sprintf(coords, "%lf %lf %lf %lf", Ox1, Ox2, Oy1, Oy2);
  char *expected_str = "-0.151250 5125.231000 125.251361 116126.242340";
  ck_assert_str_eq(expected_str, coords);
}
END_TEST

START_TEST(test_set_borders_error_1) {
  char *Ox1_str = "-0.151a25";
  char *Ox2_str = "";
  char *Oy1_str = "125.2513612";
  char *Oy2_str = "116126.24234";
  double Ox1 = 0;
  double Ox2 = 0;
  double Oy1 = 0;
  double Oy2 = 0;
  int error = s21_get_field_borders(Ox1_str, Ox2_str, Oy1_str, Oy2_str, &Ox1,
                                    &Ox2, &Oy1, &Oy2);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(test_set_borders_error_2) {
  char *Ox1_str = "-10000001";
  char *Ox2_str = "1541251265";
  char *Oy1_str = "125";
  char *Oy2_str = "116126.2434";
  double Ox1 = 0;
  double Ox2 = 0;
  double Oy1 = 0;
  double Oy2 = 0;
  int error = s21_get_field_borders(Ox1_str, Ox2_str, Oy1_str, Oy2_str, &Ox1,
                                    &Ox2, &Oy1, &Oy2);
  ck_assert_int_eq(2, error);
}
END_TEST

START_TEST(test_set_borders_error_3) {
  char *Ox1_str = "-123";
  char *Ox2_str = "123";
  char *Oy1_str = "125.2513612";
  char *Oy2_str = "124";
  double Ox1 = 0;
  double Ox2 = 0;
  double Oy1 = 0;
  double Oy2 = 0;
  int error = s21_get_field_borders(Ox1_str, Ox2_str, Oy1_str, Oy2_str, &Ox1,
                                    &Ox2, &Oy1, &Oy2);
  ck_assert_int_eq(3, error);
}
END_TEST
// SMART_CALC TESTS END <--

// CREDIT_CALC TESTS START -->
START_TEST(test_calculate_annuity_1) {
  double total = 10000000;
  double term = 28;
  double rate = 12.56;
  char total_str[100] = {0};
  char monthly[100] = {0};
  char overpayment[100] = {0};
  s21_calculate_credit_annuity(total, term, rate, total_str, monthly,
                               overpayment);
  char *expected_result = "11588676.68 413881.31 1588676.68";
  char result[300];
  sprintf(result, "%s %s %s", total_str, monthly, overpayment);
  ck_assert_str_eq(expected_result, result);
}
END_TEST

START_TEST(test_calculate_annuity_2) {
  double total = 13261236.25;
  double term = 56;
  double rate = 5.1623;
  char total_str[100] = {0};
  char monthly[100] = {0};
  char overpayment[100] = {0};
  s21_calculate_credit_annuity(total, term, rate, total_str, monthly,
                               overpayment);
  char *expected_result = "14951041.84 266982.89 1689805.59";
  char result[300];
  sprintf(result, "%s %s %s", total_str, monthly, overpayment);
  ck_assert_str_eq(expected_result, result);
}
END_TEST

START_TEST(test_calculate_annuity_3) {
  double total = 234623462346.2;
  double term = 215;
  double rate = 23.9;
  char total_str[100] = {0};
  char monthly[100] = {0};
  char overpayment[100] = {0};
  s21_calculate_credit_annuity(total, term, rate, total_str, monthly,
                               overpayment);
  char *expected_result = "1019363813230.20 4741227038.28 784740350884.00";
  char result[300];
  sprintf(result, "%s %s %s", total_str, monthly, overpayment);
  ck_assert_str_eq(expected_result, result);
}
END_TEST

START_TEST(test_calculate_diff_1) {
  double total = 10000000;
  double term = 28;
  double rate = 12.56;
  char total_str[100] = {0};
  char monthly[100] = {0};
  char overpayment[100] = {0};
  s21_calculate_credit_differentiated(total, term, rate, total_str, monthly,
                                      overpayment);
  char *expected_result = "11517666.67 461809.52 ... 360880.95 1517666.67";
  char result[300];
  sprintf(result, "%s %s %s", total_str, monthly, overpayment);
  ck_assert_str_eq(expected_result, result);
}
END_TEST

START_TEST(test_calculate_diff_2) {
  double total = 13261236.25;
  double term = 56;
  double rate = 5.1623;
  char total_str[100] = {0};
  char monthly[100] = {0};
  char overpayment[100] = {0};
  s21_calculate_credit_differentiated(total, term, rate, total_str, monthly,
                                      overpayment);
  char *expected_result = "14887125.15 293856.52 ... 237826.52 1625888.90";
  char result[300];
  sprintf(result, "%s %s %s", total_str, monthly, overpayment);
  ck_assert_str_eq(expected_result, result);
}
END_TEST

START_TEST(test_calculate_diff_3) {
  double total = 23462346234.2;
  double term = 215;
  double rate = 23.9;
  char total_str[100] = {0};
  char monthly[100] = {0};
  char overpayment[100] = {0};
  s21_calculate_credit_differentiated(total, term, rate, total_str, monthly,
                                      overpayment);
  char *expected_result =
      "73929852983.96 576418920.95 ... 111300641.69 50467506749.76";
  char result[300];
  sprintf(result, "%s %s %s", total_str, monthly, overpayment);
  ck_assert_str_eq(expected_result, result);
}
END_TEST
// CREDIT_CALC TESTS END <--

Suite *suite_insert(void) {
  Suite *s = suite_create("Start tests");
  TCase *tc = tcase_create("insert_tc");

  // SMART_CALC TESTS START -->
  tcase_add_test(tc, test_normal_expression_1);
  tcase_add_test(tc, test_normal_expression_2);
  tcase_add_test(tc, test_normal_expression_3);
  tcase_add_test(tc, test_normal_expression_4);
  tcase_add_test(tc, test_normal_expression_5);
  tcase_add_test(tc, test_normal_expression_6);
  tcase_add_test(tc, test_normal_expression_7);
  tcase_add_test(tc, test_normal_expression_8);

  tcase_add_test(tc, test_with_x_expression_1);
  tcase_add_test(tc, test_with_x_expression_2);
  tcase_add_test(tc, test_with_x_expression_3);
  tcase_add_test(tc, test_with_x_expression_3);

  tcase_add_test(tc, test_normal_expression_error_1);
  tcase_add_test(tc, test_normal_expression_error_2);
  tcase_add_test(tc, test_normal_expression_error_3);
  tcase_add_test(tc, test_normal_expression_error_4);
  tcase_add_test(tc, test_wrong_x_error);

  tcase_add_test(tc, test_buttons_1);
  tcase_add_test(tc, test_buttons_2);
  tcase_add_test(tc, test_buttons_3);
  tcase_add_test(tc, test_buttons_4);
  tcase_add_test(tc, test_buttons_5);
  tcase_add_test(tc, test_buttons_6);
  tcase_add_test(tc, test_buttons_7);
  tcase_add_test(tc, test_buttons_8);
  tcase_add_test(tc, test_buttons_9);

  tcase_add_test(tc, test_error_show_1);
  tcase_add_test(tc, test_error_show_2);
  tcase_add_test(tc, test_error_show_3);
  tcase_add_test(tc, test_error_show_4);

  tcase_add_test(tc, test_is_function_1);
  tcase_add_test(tc, test_is_function_2);

  tcase_add_test(tc, test_set_borders_1);
  tcase_add_test(tc, test_set_borders_2);

  tcase_add_test(tc, test_set_borders_error_1);
  tcase_add_test(tc, test_set_borders_error_2);
  tcase_add_test(tc, test_set_borders_error_3);
  // SMART_CALC TESTS END <--

  // CREDIT_CALC TESTS START -->
  tcase_add_test(tc, test_calculate_annuity_1);
  tcase_add_test(tc, test_calculate_annuity_2);
  tcase_add_test(tc, test_calculate_annuity_3);

  tcase_add_test(tc, test_calculate_diff_1);
  tcase_add_test(tc, test_calculate_diff_2);
  tcase_add_test(tc, test_calculate_diff_3);
  // CREDIT_CALC TESTS END <--

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
