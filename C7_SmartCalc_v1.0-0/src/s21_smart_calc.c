#include "./s21_smart_calc.h"

int s21_get_field_borders(char *Ox1_str, char *Ox2_str, char *Oy1_str,
                          char *Oy2_str, double *Ox1, double *Ox2, double *Oy1,
                          double *Oy2) {
  int error_code = 0;
  if (!s21_is_double(Ox1_str) || !s21_is_double(Ox2_str) ||
      !s21_is_double(Oy1_str) || !s21_is_double(Oy2_str)) {
    error_code = 1;
  } else {
    *Ox1 = s21_str_to_double(Ox1_str);
    *Ox2 = s21_str_to_double(Ox2_str);
    *Oy1 = s21_str_to_double(Oy1_str);
    *Oy2 = s21_str_to_double(Oy2_str);
    if (fabs(*Ox1) > 1000000.0 || fabs(*Ox2) > 1000000.0 ||
        fabs(*Oy1) > 1000000.0 || fabs(*Oy2) > 1000000.0) {
      error_code = 2;
    }
    if (*Ox1 >= *Ox2 || *Oy1 >= *Oy2) {
      error_code = 3;
    }
    if (error_code) {
      *Ox1 = 0.0 / 0.0;
      *Ox2 = 0.0 / 0.0;
      *Oy1 = 0.0 / 0.0;
      *Oy2 = 0.0 / 0.0;
    }
  }
  return error_code;
}

void s21_append_buffer(char *text, char *buffer) {
  if (!strcmp("<--", text)) {
    s21_backspace(buffer);
  } else if (!strcmp("C", text)) {
    text[0] = 0;
    s21_zero_buffer(buffer);
  } else {
    if (!strcmp("sin", text) || !strcmp("cos", text) || !strcmp("tan", text) ||
        !strcmp("asin", text) || !strcmp("acos", text) ||
        !strcmp("atan", text) || !strcmp("sqrt", text) || !strcmp("ln", text) ||
        !strcmp("log", text)) {
      s21_check_for_func(text, buffer);
    } else if (!strcmp(" / ", text) || !strcmp(" * ", text) ||
               !strcmp(" mod ", text) || !strcmp(" + ", text) ||
               !strcmp(" - ", text) || !strcmp("^", text)) {
      s21_check_for_operator(text, buffer);
    } else if (!strcmp(")", text)) {
      s21_check_closed_br(text, buffer);
    } else if (!strcmp(".", text)) {
      s21_check_for_point(text, buffer);
    } else if (!strcmp("x", text) || IS_DIGIT(text[strlen(text) - 1])) {
      s21_check_for_x(text, buffer);
      if (IS_DIGIT(text[0])) {
        s21_check_for_zero(text, buffer);
      }
    } else if (!strcmp("(", text)) {
      s21_check_for_open_br(text, buffer);
    }
    strcat(buffer, text);
  }
}

void s21_backspace(char *output_buffer) {
  int last = strlen(output_buffer) - 1;
  if (last > -1) {
    char last_ch = output_buffer[last];
    memset(&output_buffer[last], 0, 1);
    last--;
    if (last_ch == '(') {
      while (last > -1 && output_buffer[last] > 96 &&
             output_buffer[last] < 123) {
        memset(&output_buffer[last], 0, 1);
        last--;
      }
    } else if (last_ch == ' ') {
      while (output_buffer[last] != ' ') {
        memset(&output_buffer[last], 0, 1);
        last--;
      }
      memset(&output_buffer[last], 0, 1);
    }
  }
}

void s21_check_for_func(char *text, char *output_buffer) {
  int buffer_len = strlen(output_buffer);
  if (buffer_len) {
    if (output_buffer[buffer_len - 1] == '.' ||
        output_buffer[buffer_len - 1] == 'x' ||
        IS_DIGIT(output_buffer[buffer_len - 1]) ||
        output_buffer[buffer_len - 1] == ')') {
      int shift = output_buffer[buffer_len - 1] == '.' ? 4 : 3;
      int text_len = strlen(text);
      while (text_len > 0) {
        text[text_len + shift - 1] = text[text_len - 1];
        text_len--;
      }
      text[shift - 1] = ' ';
      text[shift - 2] = '*';
      text[shift - 3] = ' ';
      if (shift == 4) {
        text[0] = '0';
      }
    }
  }
  text[strlen(text)] = '(';
}

int s21_check_for_operator(char *text, char *output_buffer) {
  char ch = text[1];
  int is_unary = 0;
  int error_code = 0;
  if (ch == '-' || ch == '+') {
    is_unary = s21_check_for_unary(text, output_buffer);
  }
  if (!is_unary) {
    error_code = s21_simple_check_buff_for_operator(text, output_buffer);
  }
  return error_code;
}

int s21_check_for_unary(char *text, char *output_buffer) {
  int is_unary = 0;
  int buffer_len = strlen(output_buffer);
  if (buffer_len == 0 || output_buffer[buffer_len - 1] == '(') {
    text[0] = text[1];
    text[1] = 0;
    text[2] = 0;
    is_unary = 1;
  } else if (output_buffer[buffer_len - 1] == ' ' ||
             IS_OPERATOR(output_buffer[buffer_len - 1])) {
    text[0] = '(';
    text[2] = 0;
    is_unary = 1;
  }
  return is_unary;
}

int s21_simple_check_buff_for_operator(char *text, char *output_buffer) {
  int buffer_len = strlen(output_buffer);
  int error_code = 0;
  if (buffer_len == 0 || (!IS_DIGIT(output_buffer[buffer_len - 1]) &&
                          output_buffer[buffer_len - 1] != ')' &&
                          output_buffer[buffer_len - 1] != 'x' &&
                          output_buffer[buffer_len - 1] != '.')) {
    error_code = 1;
    s21_zero_text(text);
  } else if (output_buffer[buffer_len - 1] == '.') {
    int text_len = strlen(text);
    while (text_len > 0) {
      text[text_len] = text[text_len - 1];
      text_len--;
    }
    text[0] = '0';
  }
  return error_code;
}

void s21_check_closed_br(char *text, char *output_buffer) {
  int counter = 0;
  int len = strlen(output_buffer);
  for (int i = 0; output_buffer[i]; i++) {
    if (output_buffer[i] == '(' || output_buffer[i] == ')') {
      counter = output_buffer[i] == '(' ? counter + 1 : counter - 1;
    }
  }
  if (counter <= 0) {
    s21_zero_text(text);
  }
  if (output_buffer[len - 1] == ' ' || output_buffer[len - 1] == '^' ||
      output_buffer[len - 1] == '+' || output_buffer[len - 1] == '-' ||
      output_buffer[len - 1] == '(') {
    s21_zero_text(text);
  } else if (output_buffer[len - 1] == '.') {
    text[0] = '0';
    text[1] = ')';
  }
}

void s21_check_for_point(char *text, char *output_buffer) {
  int buffer_len = strlen(output_buffer);
  if (!buffer_len || output_buffer[buffer_len - 1] == ' ' ||
      output_buffer[buffer_len - 1] == '(' ||
      output_buffer[buffer_len - 1] == '-' ||
      output_buffer[buffer_len - 1] == '+' ||
      output_buffer[buffer_len - 1] == '^') {
    text[0] = '0';
    text[1] = '.';
  } else {
    while (buffer_len > 0 && IS_DIGIT(output_buffer[buffer_len - 1])) {
      buffer_len--;
    }
    if (buffer_len > 0) {
      if (output_buffer[buffer_len - 1] == '.') {
        s21_zero_text(text);
      } else if (output_buffer[buffer_len - 1] == ')' ||
                 output_buffer[buffer_len - 1] == 'x') {
        text[0] = ' ';
        text[1] = '*';
        text[2] = ' ';
        text[3] = '0';
        text[4] = '.';
      }
    }
  }
}

void s21_check_for_x(char *text, char *output_buffer) {
  int buffer_len = strlen(output_buffer);
  if (buffer_len) {
    char ch = output_buffer[buffer_len - 1];
    s21_put_mul_operator(text, ch);
  }
}

void s21_put_mul_operator(char *text, char last) {
  if (last == 'x' || last == ')' ||
      (IS_DIGIT(last) && (text[0] == '(' || text[0] == 'x'))) {
    text[3] = text[0];
    text[0] = ' ';
    text[1] = '*';
    text[2] = ' ';
  } else if (last == '.' && !IS_DIGIT(text[0])) {
    text[4] = text[0];
    text[0] = '0';
    text[1] = ' ';
    text[2] = '*';
    text[3] = ' ';
  }
}

void s21_check_for_zero(char *text, char *output_buffer) {
  int last = strlen(output_buffer) - 1;
  if (last > -1) {
    if (output_buffer[last] == '0') {
      if (!(last > 0 && (IS_DIGIT(output_buffer[last - 1]) ||
                         output_buffer[last - 1] == '.'))) {
        output_buffer[last] = text[0];
        text[0] = 0;
      }
    }
  }
}

void s21_check_for_open_br(char *text, char *output_buffer) {
  int buffer_len = strlen(output_buffer);
  if (buffer_len) {
    char ch = output_buffer[buffer_len - 1];
    s21_put_mul_operator(text, ch);
  }
}

void s21_zero_buffer(char *str) {
  for (int i = 0; i < BUFFER_SIZE; i++) {
    str[i] = 0;
  }
}

void s21_zero_text(char *text) {
  int i = strlen(text) - 1;
  while (i >= 0) {
    text[i] = 0;
    i--;
  }
}
