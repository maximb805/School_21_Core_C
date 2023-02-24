#include "./s21_decimal.h"

void s21_decimal_to_string(char *str, int str_len, s21_decimal src) {
  s21_zero_str(str, str_len);
  int exp = s21_get_exp(src);
  if (s21_dec_is_negative(src)) {
    str[0] = '-';
  } else {
    str[0] = '+';
  }
  int i = 30;
  if (!exp) {
    i--;
  }
  while (i > 0) {
    if (exp && (30 - i) == exp) {
      str[i] = '.';
    } else {
      str[i] = s21_mod_ten(src) + '0';
      s21_div_ten(&src);
    }
    i--;
  }
}

void s21_zero_str(char *str, int len) {
  for (int i = 0; i < len; i++) {
    str[i] = 0;
  }
}
