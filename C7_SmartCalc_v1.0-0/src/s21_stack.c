#include "s21_smart_calc.h"

void s21_stack_init(s21_stack *stack) {
  stack->top = -1;
  for (int i = 0; i < STACK_SIZE; i++) {
    stack->array[i].operand = 0;
  }
}

int s21_push(s21_stack *stack, s21_oper value) {
  int error_code = 0;
  if (stack->top < STACK_SIZE - 1) {
    stack->top++;
    stack->array[stack->top] = value;
  } else {
    error_code = 1;
  }
  return error_code;
}

int s21_pop(s21_stack *stack, s21_oper *value) {
  int error_code = 0;
  if (stack->top > -1) {
    *value = stack->array[stack->top];
    stack->top--;
  } else {
    error_code = 1;
  }
  return error_code;
}

int s21_peek(s21_stack *stack, s21_oper *value) {
  int error_code = 0;
  if (stack->top > -1) {
    *value = stack->array[stack->top];
  } else {
    error_code = 1;
  }
  return error_code;
}
