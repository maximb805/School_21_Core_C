#ifndef S21_SMART_CALC_H
#define S21_SMART_CALC_H

#define STACK_SIZE 255
#define BUFFER_SIZE 272
#define IS_DIGIT(ch) ((ch) >= '0' && (ch) <= '9')
#define IS_FUNC(ch) \
  ((ch) == 'c' || (ch) == 's' || (ch) == 't' || (ch) == 'a' || (ch) == 'l')
#define IS_OPERATOR(ch)                                                       \
  ((ch) == '+' || (ch) == '-' || (ch) == '*' || (ch) == '/' || (ch) == '^' || \
   (ch) == 'm' || (ch) == 'u' || (ch) == 'p')
#define IS_CHAR_FUNC(ch)                                                      \
  ((ch) == 'c' || (ch) == 's' || (ch) == 't' || (ch) == 'a' || (ch) == 'r' || \
   (ch) == 'k' || (ch) == 'q' || (ch) == 'l' || (ch) == 'n')

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef union {
  double operand;
  char operat;
} s21_oper;

typedef struct {
  int top;
  s21_oper array[STACK_SIZE];
} s21_stack;

// c - cos
// s - sin
// t - tan
// a - asin
// r - acos
// k - atan
// q - sqrt
// l - log
// n - ln

// s21_deposit_calc.c
void s21_calculate_credit_annuity(double total, double term, double rate,
                                  char *total_payment_str, char *monthly_str,
                                  char *overpayment_str);
void s21_calculate_credit_differentiated(double total, double term, double rate,
                                         char *total_payment_str,
                                         char *monthly_str,
                                         char *overpayment_str);
void s21_round_double(double *value);

// s21_smart_calc.c
int s21_get_field_borders(char *Ox1_str, char *Ox2_str, char *Oy1_str,
                          char *Oy2_str, double *Ox1, double *Ox2, double *Oy1,
                          double *Oy2);
void s21_append_buffer(char *text, char *buffer);
void s21_backspace(char *output_buffer);
void s21_check_for_func(char *text, char *output_buffer);
int s21_check_for_operator(char *text, char *output_buffer);
int s21_check_for_unary(char *text, char *output_buffer);
int s21_simple_check_buff_for_operator(char *text, char *output_buffer);
void s21_check_closed_br(char *text, char *output_buffer);
void s21_check_for_point(char *text, char *output_buffer);
void s21_check_for_x(char *text, char *output_buffer);
void s21_put_mul_operator(char *text, char last);
void s21_check_for_zero(char *text, char *output_buffer);
void s21_check_for_open_br(char *text, char *output_buffer);
void s21_zero_buffer(char *str);
void s21_zero_text(char *text);

// s21_stack.c
void s21_stack_init(s21_stack *stack);
int s21_push(s21_stack *stack, s21_oper value);
int s21_pop(s21_stack *stack, s21_oper *value);
int s21_peek(s21_stack *stack, s21_oper *value);

// s21_parser.c
int s21_get_postfix(const char *src, char *dst);
double s21_get_answer(char *result_str, char *postfix, double x, int is_grad);
int s21_to_postfix(const char *src, s21_stack *operators, char *dst);
int s21_calculate_postfix(const char *postfix, s21_stack *operands, double x,
                          int is_grad);
void s21_calc_bin_oper(s21_oper *oper_1, s21_oper *oper_2, char operat);
void s21_calc_func(s21_oper *oper, char func, int is_grad);
int s21_operators_in_brackets_to_dst(s21_stack *operators, char *dst,
                                     int *dst_pos);
void s21_check_operators_stack(s21_stack *operators, s21_oper oper, char *dst,
                               int *dst_pos);
int s21_from_stack_to_dst(s21_stack *operators, s21_oper *top_oper, char *dst,
                          int *dst_pos);
void s21_unary_to_char(char *str);
void s21_func_to_char(char *str, int *pos, s21_oper *operat);
int s21_check_brackets(char *str);
void s21_get_double(const char *str, int *pos, s21_oper *operand);
double s21_str_to_double(char *str);
int s21_is_double(char *str);
int s21_get_priority(s21_oper operat);
int s21_is_function(char *str);
void s21_cut_trailing_zeros(char *str);

#endif /* S21_SMART_CALC_H */