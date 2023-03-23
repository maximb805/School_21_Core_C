#ifndef S21_SMART_CALC_H
#define S21_SMART_CALC_H

#define STACK_SIZE 255
#define IS_DIGIT(ch) ((ch) >= '0' && (ch) <= '9')
#define IS_FUNC(ch) ((ch) == 'c' || (ch) == 's' || (ch) == 't' || (ch) == 'a' || (ch) == 'l')
#define IS_OPERATOR(ch) ((ch) == '+' || (ch) == '-' || (ch) == '*' || (ch) == '/' || \
                        (ch) == '^'  || (ch) == 'm' || (ch) == 'u'  || (ch) == 'p')
#define IS_BRACKET(ch) ((ch) == '(' || (ch) == ')')
#define IS_CHAR_FUNC(ch) ((ch) == 'c' || (ch) == 's' || (ch) == 't' || (ch) == 'a' || \
                        (ch) == 'r'  || (ch) == 'k' || (ch) == 'q'  || (ch) == 'l'  || (ch) == 'n')

#include <stdbool.h>
#include <gtk/gtk.h>
#include <cairo.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

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

void s21_print_mesh(cairo_t *cr, gdouble clip_x1,
                    gdouble clip_x2, gdouble clip_y1,
                    gdouble clip_y2, gdouble x1,
                    gdouble x2, gdouble y1, gdouble y2, gdouble dx, gdouble dy,
                    gdouble step_x, gdouble step_y);
void s21_print_zero_lines(cairo_t *cr, gdouble x1, gdouble x2, gdouble y1, gdouble y2,
                          gdouble clip_x1, gdouble clip_x2, gdouble clip_y1, gdouble clip_y2,
                          gdouble dx, gdouble dy, gdouble step_x, gdouble step_y,
                          int *zero_x_printed, int *zero_y_printed);
void s21_print_verticals(cairo_t *cr, gdouble start, gdouble clip_x1, gdouble clip_x2,
                         gdouble clip_y1, gdouble clip_y2, gdouble pixels_step);
void s21_print_horizontals(cairo_t *cr, gdouble start, gdouble clip_x1, gdouble clip_x2,
                                gdouble clip_y1, gdouble clip_y2, gdouble pixels_step);
void s21_set_lower_step(gdouble *mesh_step);
void s21_get_steps(gdouble *mesh_step_x, gdouble *mesh_step_y, gdouble x_dim_len, gdouble y_dim_len);
void s21_zero_buffer(char *str);



int s21_check_input_str(char *text, char *output_buffer);
int s21_simple_check_buff_for_operator(char *text, char *output_buffer);
void s21_zero_text(char *text);
void s21_check_closed_br(char *text, char *output_buffer);
void s21_check_for_point(char *text, char *output_buffer);
int s21_check_for_unary(char *text, char *output_buffer);
void s21_put_mul_operator(char *text, char last);
void s21_check_for_x(char *text, char *output_buffer);
void s21_check_for_open_br(char *text, char *output_buffer);
void s21_check_for_func(char *text, char *output_buffer);
double s21_get_answer(char *result_str, char *postfix, double x);
int s21_get_postfix(char *str, char *dst);
void s21_backspase(char *output_buffer);
int s21_is_function(char *str);
void s21_check_for_zero(char *text, char *output_buffer);

// s21_stack.c
void s21_stack_init(s21_stack *stack);
int s21_push(s21_stack *stack, s21_oper value);
int s21_pop(s21_stack *stack, s21_oper *value);
int s21_peek(s21_stack *stack, s21_oper *value);
void s21_print_operands_stack(s21_stack stack);
void s21_print_operators_stack(s21_stack stack);

// s21_parser.c
int s21_to_postfix(char *str, s21_stack *operators, char *dst);
int s21_calculate_postfix(char *dst, s21_stack *operands, double x);
int s21_check_brackets(char *str);
void s21_get_double(char *str, int *pos, s21_oper *operand);
void s21_func_to_char(char *str, int *pos, s21_oper *operat);
void s21_unary_to_char(char *str);
int s21_get_priority(s21_oper operat);
void s21_check_operators_stack(s21_stack *operators, s21_oper oper, char *dst, int *dst_pos);
int s21_operators_in_brackets_to_dst(s21_stack *operators, char *dst, int *dst_pos);
int s21_from_stack_to_dst(s21_stack *operators, s21_oper *top_oper, char *dst, int *dst_pos);
void s21_calc_func(s21_oper *oper, char func);
void s21_calc_bin_oper(s21_oper *oper_1, s21_oper *oper_2, char operat);
int s21_is_double(char *str);
double s21_str_to_double(char *str);

#endif /* S21_SMART_CALC_H */