#include "s21_smart_calc.h"

int s21_to_postfix(char *str, s21_stack *operators, char *dst) {
  int error_code = 0;
  s21_oper oper;
  s21_unary_to_char(str);
  int str_pos = 0;
  int dst_pos = 0;
  if (!s21_check_brackets(str)) {
    while (str[str_pos] && !error_code) {
      if (IS_DIGIT(str[str_pos])) {
        while (IS_DIGIT(str[str_pos]) || str[str_pos] == '.') {
          dst[dst_pos++] = str[str_pos++];
        }
        dst[dst_pos++] = ' ';
      }
      if (str[str_pos] == 'x') {
        dst[dst_pos++] = str[str_pos];
      } else if (IS_FUNC(str[str_pos])) {
        s21_func_to_char(str, &str_pos, &oper);
        s21_push(operators, oper);
      } else if (str[str_pos] == '(') {
        oper.operat = str[str_pos];
        s21_push(operators, oper);
      } else if (IS_OPERATOR(str[str_pos])) {
        oper.operat = str[str_pos];
        s21_check_operators_stack(operators, oper, dst, &dst_pos);
        s21_push(operators, oper);
      } else if (str[str_pos] == ')') {
        error_code = s21_operators_in_brackets_to_dst(operators, dst, &dst_pos);
      }
      str_pos++;
    }
    if (!error_code) {
      int stop_cycle = s21_peek(operators, &oper);
      while (!stop_cycle && !error_code) {
        if (oper.operat != '(') {
          stop_cycle = s21_from_stack_to_dst(operators, &oper, dst, &dst_pos);
        } else {
          error_code = 1;
        }
      }
    }
  } else {
    error_code = 1;
  }
  return error_code;
}

int s21_calculate_postfix(char *dst, s21_stack *operands, double x) {
  int error_code = 0;
  s21_oper oper_1;
  s21_oper oper_2;
  int dst_pos = 0;
  while (dst[dst_pos] && !error_code) {
    int did_smth = 0;
    if (IS_DIGIT(dst[dst_pos]) || dst[dst_pos] == 'x') {
      if (dst[dst_pos] != 'x') {
        s21_get_double(dst, &dst_pos, &oper_1);
        dst_pos--;
      } else {
        if (x != x) {
          error_code = 3;
        } else {
          oper_1.operand = x;
        }
      }
      did_smth = 1;
    } else if (IS_OPERATOR(dst[dst_pos])) {
      error_code = s21_pop(operands, &oper_1);
      if (!error_code) {
        if (dst[dst_pos] == 'u' || dst[dst_pos] == 'p') {
          oper_1.operand = dst[dst_pos] == 'u' ? oper_1.operand * -1.0 : oper_1.operand;
        } else {
          error_code = s21_pop(operands, &oper_2);
          if (!error_code) {
            s21_calc_bin_oper(&oper_1, &oper_2, dst[dst_pos]);
          }
        }
      }
      did_smth = 1;
    } else if (IS_CHAR_FUNC(dst[dst_pos])) {
      error_code = s21_pop(operands, &oper_1);
      if (!error_code) {
        s21_calc_func(&oper_1, dst[dst_pos]);
      }
      did_smth = 1;
    }
    if (did_smth) {
      if (oper_1.operand != oper_1.operand) {
        error_code = 2;
      } else {
        s21_push(operands, oper_1);
      }
    }
    dst_pos++;
  }
  if (!error_code && operands->top != 0) {
    error_code = 1;
  }
  return error_code;
}

void s21_calc_bin_oper(s21_oper *oper_1, s21_oper *oper_2, char operat) {
  switch (operat) {
    case '-':
      oper_1->operand = oper_2->operand - oper_1->operand;
      break;
    case '+':
      oper_1->operand = oper_2->operand + oper_1->operand;
      break;
    case '*':
      oper_1->operand = oper_2->operand * oper_1->operand;
      break;
    case '/':
      oper_1->operand = oper_2->operand / oper_1->operand;
      break;
    case 'm':
      oper_1->operand = fmod(oper_2->operand, oper_1->operand);
      break;
    case '^':
      oper_1->operand = pow(oper_2->operand, oper_1->operand);
      break;
  }
}

void s21_calc_func(s21_oper *oper, char func) {
  switch (func) {
    case 's':
      oper->operand = sin(oper->operand);
      break;
    case 'c':
      oper->operand = cos(oper->operand);
      break;
    case 't':
      oper->operand = tan(oper->operand);
      break;
    case 'a':
      oper->operand = asin(oper->operand);
      break;
    case 'r':
      oper->operand = acos(oper->operand);
      break;
    case 'k':
      oper->operand = atan(oper->operand);
      break;
    case 'q':
      oper->operand = sqrt(oper->operand);
      break;
    case 'l':
      oper->operand = log10(oper->operand);
      break;
    case 'n':
      oper->operand = log(oper->operand);
      break;
  }
}

int s21_operators_in_brackets_to_dst(s21_stack *operators, char *dst, int *dst_pos) {
  int error_code = 0;
  s21_oper top_oper;
  error_code = s21_peek(operators, &top_oper);
  while (!error_code && top_oper.operat != '(') {
    error_code = s21_from_stack_to_dst(operators, &top_oper, dst, dst_pos);
  }
  if (!error_code) {
    s21_pop(operators, &top_oper);
  }
  int empty = s21_peek(operators, &top_oper);
  if (!error_code && !empty && IS_CHAR_FUNC(top_oper.operat)) {
    s21_pop(operators, &top_oper);
    dst[*dst_pos] = top_oper.operat;
    *dst_pos = *dst_pos + 1;
  }
  return error_code;
}

void s21_check_operators_stack(s21_stack *operators, s21_oper oper, char *dst, int *dst_pos) {
  int priority = s21_get_priority(oper);
  s21_oper top_oper;
  int error_code = s21_peek(operators, &top_oper);
  while (!error_code && top_oper.operat != '(' && s21_get_priority(top_oper) >= priority) {
    error_code = s21_from_stack_to_dst(operators, &top_oper, dst, dst_pos);
  }
}

int s21_from_stack_to_dst(s21_stack *operators, s21_oper *top_oper, char *dst, int *dst_pos) {
  int error_code = 0;
  error_code = s21_pop(operators, top_oper);
  if (!error_code) {
    dst[*dst_pos] = top_oper->operat;
    *dst_pos = *dst_pos + 1;
    error_code = s21_peek(operators, top_oper);
  }
  return error_code;
}

void s21_unary_to_char(char *str) {
  char prev_lex = 0;
  while (*str) {
    if ((*str == '-' || *str == '+') && (prev_lex == '(' || prev_lex == 0)) {
      *str = *str == '-' ? 'u' : 'p';
    }
    prev_lex = *str;
    str++;
  }
}

void s21_func_to_char(char *str, int *pos, s21_oper *operat) {
  switch (str[*pos]) {
    case 'c':
      operat->operat = 'c';
      *pos = *pos + 2;
      break;
    case 't':
      operat->operat = 't';
      *pos = *pos + 2;
      break;
    case 's':
      *pos = *pos + 1;
      if (str[*pos] == 'q') {
        operat->operat = 'q';
        *pos = *pos + 1;
      } else {
        operat->operat = 's';
      }
      *pos = *pos + 1;
      break;
    case 'a':
      *pos = *pos + 1;
      if (str[*pos] == 's') {
        operat->operat = 'a';
      } else if (str[*pos] == 'c') {
        operat->operat = 'r';
      } else {
        operat->operat = 'k';
      }
      *pos = *pos + 2;
      break;
    case 'l':
      *pos = *pos + 1;
      if (str[*pos] == 'o') {
        operat->operat = 'l';
        *pos = *pos + 1;
      } else {
        operat->operat = 'n';
      }
      break;
  }
}

int s21_check_brackets(char *str) {
  int result = 0;
  while (*str) {
    if (*str == '(') {
      result++;
    }
    if (*str == ')') {
      result--;
    }
    str++;
  }
  return result;
}

void s21_get_double(char *str, int *pos, s21_oper *operand) {
  int got_point = 0;
  double result = 0.0;
  double sub_res = 0.0;
  int digits_after_point = 0;
  while (IS_DIGIT(str[*pos]) || (str[*pos] == '.' && !got_point)) {
    if (str[*pos] == '.') {
      got_point = 1;
    } else {
      sub_res = (double) (str[*pos] - '0');
      if (got_point) {
        for (int i = 0; i <= digits_after_point; i++) {
          sub_res /= 10.0;
        }
        digits_after_point++;
      } else {
        result *= 10.0;
      }
      result += sub_res;
    }
    *pos = *pos + 1;
  }
  operand->operand = result;
}

double s21_str_to_double(char *str) {
  double result = 1;
  int pos = 0;
  if (str[0] == '-') {
    result *= -1;
    pos++;
  }
  if (str[0] == '+'){
    pos++;
  }
  s21_oper oper;
  s21_get_double(str, &pos, &oper);
  result *= oper.operand;
  return result;
}

int s21_is_double(char *str) {
  int result = 0;
  int len = strlen(str);
  if (len > 0) {
    if (((str[0] == '+' || str[0] == '-') && len > 1) || IS_DIGIT(str[0])) {
      result = 1;
      int got_point = 0;
      for(int i = 1; i < len && result; i++) {
        if (str[i] == '.' && !got_point) {
          got_point = 1;
        } else {
          if (!IS_DIGIT(str[i])) {
            result = 0;
          }
        }
      }
    }
  }
  return result;
}

int s21_get_priority(s21_oper operat) {
  int priority = 0;
  switch (operat.operat) {
    case 'p': // unary plus
    case 'u': // unary minus
      priority = 4;
      break;
    case '^':
      priority = 3;
      break;
    case '/':
    case '*':
    case 'm': // mod
      priority = 2;
      break;
    case '-':
    case '+':
      priority = 1;
      break;
  }
  return priority;
}
