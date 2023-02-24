#include "./s21_string.h"

s21_size_t s21_strlen(const char *str) {
  s21_size_t str_length = 0;
  while (*str) {
    str_length++;
    str++;
  }
  return str_length;
}

int s21_strcmp(const char *str1, const char *str2) {
  int result = 0;
  for (int i = 0; str1[i] || str2[i]; i++) {
    if (str1[i] != str2[i]) {
      result = str1[i] - str2[i];
      break;
    }
  }
  return result;
}

char *s21_strcpy(char *dest, const char *src) {
  int i;
  for (i = 0; src[i]; i++) {
    dest[i] = src[i];
  }
  dest[i] = '\0';
  return dest;
}

char *s21_strcat(char *dest, const char *src) {
  char *dest_start = dest;
  while (*dest) {
    dest++;
  }
  int i;
  for (i = 0; src[i]; i++) {
    dest[i] = src[i];
  }
  dest[i] = '\0';
  return dest_start;
}

char *s21_strchr(const char *str, int c) {
  int i = 0;
  int cont = 1;
  while (str[i] && cont) {
    if (str[i] == c) {
      cont = 0;
    }
    i++;
  }
  char *result = cont ? s21_NULL : (char *)&str[i - 1];
  return result;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = s21_NULL;
  int str_search_counter = 0;
  if (needle[str_search_counter] != '\0' && haystack != s21_NULL) {
    int i;
    for (i = 0; haystack[i]; i++) {
      if (haystack[i] == needle[str_search_counter]) {
        str_search_counter++;
      } else {
        i -= str_search_counter;
        str_search_counter = 0;
      }
      if (needle[str_search_counter] == '\0') {
        break;
      }
    }
    if (needle[str_search_counter] == '\0') {
      result = (char *)&haystack[i - str_search_counter + 1];
    }
  } else {
    if (haystack != s21_NULL) {
      result = (char *)haystack;
    }
  }
  return result;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t src_len = s21_check_len(n, src);
  n = n == src_len ? n : src_len + 1;
  s21_size_t dest_len = s21_strlen(dest);
  for (s21_size_t i = 0; i < n; i++) {
    dest[i] = src[i];
  }
  if (dest_len < n) {
    dest[n] = '\0';
  }
  return dest;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *p = (unsigned char *)str;
  unsigned char *isCharFind = s21_NULL;
  while ((str != s21_NULL) && (n--)) {
    if (*p != (unsigned char)c) {
      p++;
    } else {
      isCharFind = p;
      break;
    }
  }
  return isCharFind;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  unsigned char *arr1 = (unsigned char *)str1;
  unsigned char *arr2 = (unsigned char *)str2;
  int result = 0;
  s21_size_t i = 0;
  while (i < n) {
    if (arr1[i] != arr2[i]) {
      result = (arr1[i] - arr2[i]);
      break;
    }
    i++;
  }
  return result;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    if ((char *)src != (char *)dest) {
      *((char *)dest + i) = *((char *)src + i);
    }
  }
  return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char tmp_arr[4096] = {0};
  for (int i = 0; i < (int)n; ++i) tmp_arr[i] = *((char *)src + i);
  for (int i = 0; i < (int)n; ++i) *((char *)dest + i) = tmp_arr[i];
  return dest;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  n = s21_check_len(n, src);
  char *dest_end = dest + s21_strlen(dest);
  for (s21_size_t i = 0; i < n; i++) {
    dest_end[i] = src[i];
  }
  dest_end[n] = '\0';
  return dest;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  if (s21_strlen(str1) == s21_strlen(str2)) {
    n = s21_check_len(n, str1);
  }
  int result = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (str1[i] != str2[i]) {
      result = str1[i] - str2[i];
      break;
    }
  }
  return result;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  char *s = (char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    s[i] = c;
  }
  return str;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t razmer = 0;
  for (const char *a = str1; *a; a++) {
    unsigned short srabotal = 0;
    for (const char *b = str2; *b; b++) {
      if (*a == *b) {
        srabotal = 1;
        break;
      }
    }
    if (srabotal) {
      break;
    } else {
      razmer++;
    }
  }
  return razmer;
}

char *s21_strerror(int errnum) {
  char *err[] = ERROR;
  static char resnum[70];
  int max = 133;
  if (*err[0] == 'U') {
    max = 106;
  }
  if (errnum > -1 && errnum <= max) {
    s21_strcpy(resnum, err[errnum]);
  } else {
    char num[10] = {0};
    if (errnum < 0) {
      num[0] = '-';
      errnum *= -1;
    }
    s21_strcpy(resnum, "Unknown error: ");
    int resnum_last_symb = 15;
    if (max == 133) {
      resnum[13] = ' ';
      resnum[14] = '\0';
      resnum_last_symb = 14;
    }
    int i;
    for (i = 8; errnum != 0; errnum /= 10, i--) num[i] = errnum % 10 + '0';
    if (num[0] == '-') {
      resnum[resnum_last_symb] = '-';
      resnum[resnum_last_symb + 1] = '\0';
    }
    s21_strcat(resnum, num + i + 1);
  }
  return resnum;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *res = s21_NULL;
  for (const char *a = str1; *a; a++) {
    for (const char *b = str2; *b; b++) {
      if (*a == *b) {
        res = (char *)a;
        break;
      }
    }
    if (res) {
      break;
    }
  }
  return res;
}

char *s21_strrchr(const char *str, int c) {
  char *res = s21_NULL;
  s21_size_t len = s21_strlen(str);

  for (int i = len; i >= 0; i--) {
    if (str[i] == c) {
      res = ((char *)str) + i;
      break;
    }
  }
  return res;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t counter = 0;
  for (const char *a = str1; *a; a++) {
    unsigned short was = 0;
    for (const char *b = str2; *b; b++) {
      if (*a == *b) {
        counter++;
        was = 1;
        break;
      }
    }
    if (!was) break;
  }
  return counter;
}

char *s21_strtok(char *str, const char *delim) {
  static int next_null, tok;
  static s21_size_t ind;
  static char *max_ptr;
  static char *addr;

  if (str) {
    tok = 1;
    ind = 0, next_null = 0;
    addr = str + s21_strspn(str, delim);
    max_ptr = str + s21_strlen(str);
  }
  char *res = s21_NULL;
  if (!(addr >= max_ptr || next_null)) {
    int non_delim = 1;
    for (int i = 0; addr[i]; i++) {
      s21_size_t step = s21_strspn(addr + i, delim);
      if (step) {
        non_delim = 0;
        for (s21_size_t j = i; j < i + step; j++) addr[j] = '\0';

        ind = step + i;
        break;
      }
    }
    if (tok == 1 && non_delim) next_null = 1;
    res = addr;
    addr += ind;
  }
  ++tok;
  return res;
}

s21_size_t s21_check_len(s21_size_t n, const char *str) {
  s21_size_t str_len = s21_strlen(str);
  if (n > str_len) {
    n = str_len;
  }
  return n;
}

void *s21_to_upper(const char *str) {
  char *tmp_str;
  if (str != s21_NULL) {
    int str_len = s21_strlen(str) + 1;
    int i = 0;
    tmp_str = (char *)calloc(str_len, sizeof(char));
    if (tmp_str) {
      while (i < str_len) {
        if (str[i] >= 'a' && str[i] <= 'z') {
          tmp_str[i] = str[i] - 32;
        } else {
          tmp_str[i] = str[i];
        }
        ++i;
      }
    }
  } else {
    tmp_str = s21_NULL;
  }
  return tmp_str;
}

void *s21_to_lower(const char *str) {
  char *tmp_str;
  if (str != s21_NULL) {
    int str_len = s21_strlen(str) + 1;
    int i = 0;
    tmp_str = (char *)calloc(str_len, sizeof(char));
    if (tmp_str) {
      while (i < str_len) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
          tmp_str[i] = str[i] + 32;
        } else {
          tmp_str[i] = str[i];
        }
        ++i;
      }
    }
  } else {
    tmp_str = s21_NULL;
  }
  return tmp_str;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *new_str = s21_NULL;
  if (src && str && s21_strlen(src) >= start_index) {
    new_str = (char *)calloc(
        (s21_strlen(src) + s21_strlen(str) + 1) * sizeof(char), 1);
    if (new_str) {
      s21_strncpy(new_str, src, start_index);
      //*(new_str + start_index) = '\0';
      s21_strcat(new_str, str);
      s21_strcat(new_str, src + start_index);
    }
  }
  return (void *)new_str;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *new_str = s21_NULL;
  if (src && trim_chars) {
    char *ptr_str = (char *)src;
    char *end_str = (char *)src + s21_strlen(src);
    for (; *ptr_str && s21_strchr(trim_chars, *ptr_str); ptr_str++) {
    }
    for (; end_str != ptr_str && s21_strchr(trim_chars, *(end_str - 1));
         end_str--) {
    }
    new_str = (char *)calloc((end_str - ptr_str + 1) * sizeof(char), 1);
    if (new_str) {
      s21_strncpy(new_str, ptr_str, end_str - ptr_str);
      *(new_str + (end_str - ptr_str)) = '\0';
    }
  }
  return (void *)new_str;
}

int s21_sprintf(char *str, char *format, ...) {
  str[0] = '\0';
  FORMAT fformat;
  int check = -1;
  char *buffer = (char *)calloc(s21_strlen(format) + 1, 1);
  char *buffer_start = buffer;
  if (buffer != s21_NULL) {
    check = 0;
    buffer = s21_strcpy(buffer, format);
    va_list arg_list;
    va_start(arg_list, format);
    do {
      s21_set_zeroes(&fformat);
      buffer = s21_parser(str, buffer, &fformat, &arg_list);
      if (fformat.spec) {
        if (fformat.spec == 'n') {
          int *n = (int *)va_arg(arg_list, void *);
          *n = (int)s21_strlen(str);
        } else {
          char *str1 = s21_main_executable_module(fformat, &arg_list);
          if (str1) {
            str = s21_strcat(str, str1);
            free(str1);
          } else {
            check = -1;
          }
        }
      }
    } while (fformat.spec && check != -1);
    free(buffer_start);
    va_end(arg_list);
    if (check != -1) {
      check = (int)s21_strlen(str);
    }
  }
  return check;
}

char *s21_main_executable_module(FORMAT fformat, va_list *arg_list) {
  char *str1 = s21_NULL;
  switch (fformat.spec) {
    case 'c':
      str1 = s21_char_to_string(arg_list, fformat);
      break;
    case 'i':
    case 'd':
      str1 = s21_int_format(fformat, arg_list);
      break;
    case 'f':
      str1 = s21_f_format(fformat, arg_list);
      break;
    case 's':
      str1 = s21_str_to_string(fformat, arg_list);
      break;
    case 'u':
      str1 = s21_u_format(fformat, arg_list);
      break;
    case '%':
      str1 = s21_percent_to_string();
      break;
    case 'G':
    case 'g':
      str1 = s21_g_format(fformat, arg_list);
      break;
    case 'E':
    case 'e':
      str1 = s21_e_format(fformat, arg_list);
      break;
    case 'x':
    case 'X':
      str1 = s21_x_format(fformat, arg_list);
      break;
    case 'o':
      str1 = s21_o_format(fformat, arg_list);
      break;
    case 'p':
      str1 = s21_p_format(fformat, arg_list);
      break;
    default:
      break;
  }
  return str1;
}

char *s21_g_format(FORMAT fformat, va_list *arg_list) {
  char *str1 = s21_NULL;
  str1 = (char *)calloc(1000, 1);
  if (str1) {
    switch (fformat.length) {
      case 'l': {
        if (fformat.double_len) {
          str1 = s21_g_to_str(str1, va_arg(*arg_list, long double), &fformat);
        } else {
          str1 = s21_g_to_str(str1, va_arg(*arg_list, double), &fformat);
        }
        break;
      }
      default: {
        double g_number = va_arg(*arg_list, double);
        str1 = s21_g_to_str(str1, g_number, &fformat);
      }
    }
    s21_g_precision(str1, &fformat);
    s21_uns_precision(str1, fformat);
    s21_width_flag(str1, fformat);
  }
  return str1;
}

void s21_g_precision(char *str, FORMAT *fformat) {
  if (!fformat->sharp) {
    s21_size_t len = s21_strlen(str);
    int cont = 1;
    while (cont) {
      if (str[len - 1] == '0' || str[len - 1] == '.') {
        if (str[len - 1] == '.') {
          cont--;
        }
        str[len - 1] = '\0';
        fformat->precision--;
      } else {
        cont--;
      }
      len--;
    }
  }
}

char *s21_g_to_str(char *str, long double number, FORMAT *fformat) {
  int int_len = s21_calc_int_length(labs((long long int)s21_round(number, 0)));
  int count = 0;
  fformat->precision = fformat->precision < 0 ? 6 : fformat->precision;
  fformat->precision = fformat->precision == 0 ? 1 : fformat->precision;
  if (int_len == 0 && fpclassify(number) != FP_ZERO) {
    count = s21_get_count(number);
  }
  if (fformat->precision < int_len || (count > 4 && count < 500)) {
    fformat->spec = fformat->spec == 'G' ? 'E' : 'e';
    fformat->precision = count > 0 ? 0 : fformat->precision - 1;
    s21_e_to_str(str, number, fformat);
  } else {
    fformat->precision =
        fformat->precision < count ? count : fformat->precision - int_len;
    s21_f_to_str(str, number, *fformat);
  }
  return str;
}

int s21_get_count(long double number) {
  int count = 0;
  while (number < 1 && count < 500) {
    number *= 10;
    count++;
  }
  return count;
}

char *s21_int_format(FORMAT fformat, va_list *arg_list) {
  char *str1 = s21_NULL;
  if (!fformat.length) {
    str1 = s21_int_to_string(fformat, va_arg(*arg_list, int));
  } else if (fformat.length == 'l') {
    if (fformat.double_len) {
      str1 = s21_int_to_string(fformat, va_arg(*arg_list, long long int));
    } else {
      str1 = s21_int_to_string(fformat, va_arg(*arg_list, long int));
    }
  } else if (fformat.length == 'h') {
    if (fformat.double_len) {
      char num = va_arg(*arg_list, long long int);
      str1 = s21_int_to_string(fformat, num);
    } else {
      short num = va_arg(*arg_list, long long int);
      str1 = s21_int_to_string(fformat, num);
    }
  }
  return str1;
}

char *s21_int_to_string(FORMAT fformat, long long int num) {
  fformat.zero = fformat.precision > -1 ? 0 : fformat.zero;
  int is_negative = s21_is_negative(&fformat, &num);
  int int_length = s21_calc_int_length(num);
  int zeroes_count =
      fformat.precision > int_length ? fformat.precision - int_length : 0;
  int spaces_count = 0;
  if (fformat.width >
      (int_length + (is_negative || fformat.plus || fformat.space) +
       zeroes_count)) {
    spaces_count =
        fformat.width -
        (int_length + (is_negative || fformat.plus || fformat.space) +
         zeroes_count);
  }
  int mem_need = (is_negative || fformat.plus || fformat.space) + int_length +
                 zeroes_count + spaces_count + 1;
  char *num_str = (char *)calloc(mem_need, 1);
  if (num_str != s21_NULL) {
    if (!fformat.minus) {
      while (spaces_count) {
        if (fformat.zero) {
          num_str = s21_strcat(num_str, "0");
        } else {
          num_str = s21_strcat(num_str, " ");
        }
        spaces_count--;
      }
    }
    if (is_negative) {
      num_str = s21_strcat(num_str, "-");
    } else if (fformat.plus) {
      num_str = s21_strcat(num_str, "+");
    } else if (fformat.space) {
      num_str = s21_strcat(num_str, " ");
    }
    while (zeroes_count) {
      num_str = s21_strcat(num_str, "0");
      zeroes_count--;
    }
    int i = 0;
    char reverted_num_str[30] = {0};
    while (num > 0) {
      reverted_num_str[i] = (char)(num % 10 + '0');
      num /= 10;
      i++;
    }
    s21_reverse_u_str(reverted_num_str);
    num_str = s21_strcat(num_str, reverted_num_str);
    while (spaces_count) {
      num_str = s21_strcat(num_str, " ");
      spaces_count--;
    }
  }
  return num_str;
}

int s21_is_negative(FORMAT *fformat, long long int *num) {
  int is_negative = 0;
  if (*num < 0) {
    *num *= -1;
    is_negative = 1;
  }
  if (is_negative) {
    fformat->plus = 0;
    fformat->space = 0;
  } else {
    if (fformat->plus) {
      fformat->space = 0;
    }
  }
  if (fformat->precision == -1) {
    fformat->precision = 1;
  }
  return is_negative;
}

int s21_calc_int_length(long long int num) {
  int length = 0;
  while (num > 0) {
    num /= 10;
    length++;
  }
  return length;
}

char *s21_char_to_string(va_list *arg_list, FORMAT fformat) {
  char *char_result = (char *)calloc(2 + fformat.width, 1);
  if (char_result) {
    char ch = (char)va_arg(*arg_list, int);
    char_result[0] = ch;
    char_result = s21_width_flag(char_result, fformat);
  }
  return char_result;
}

char *s21_f_format(FORMAT fformat, va_list *arg_list) {
  char *str1 = s21_NULL;
  str1 = (char *)calloc(1000, 1);
  if (str1) {
    switch (fformat.length) {
      case 'l': {
        if (fformat.double_len) {
          str1 = s21_f_to_str(str1, va_arg(*arg_list, long double), fformat);
        } else {
          str1 = s21_f_to_str(str1, va_arg(*arg_list, double), fformat);
        }
        break;
      }
      default: {
        double u_number = va_arg(*arg_list, double);
        str1 = s21_f_to_str(str1, u_number, fformat);
      }
    }
    s21_uns_precision(str1, fformat);
    s21_width_flag(str1, fformat);
  }
  return str1;
}

char *s21_f_to_str(char *str, long double number, FORMAT fformat) {
  if (fformat.precision < 0) fformat.precision = 6;
  char num1_str[1000] = "", *p1 = s21_NULL;
  p1 = num1_str;
  char num2_str[1000] = "", *p2 = s21_NULL;
  p2 = num2_str;
  long double mantis, right = 0.0L, pow = 1L, pow_t = 1.0L;
  int sign = s21_check_sign_flags(&fformat, number);
  if (fpclassify(number) < 4) {
    s21_d_class_to_str(num1_str, number, fformat);
    if (sign < 0 && fpclassify(number) != 1) s21_strcat(str, "-");
    s21_strcat(str, num1_str);
    fformat.zero = 0;
    if (fpclassify(number) == 2 && fformat.sharp && !fformat.precision) {
      s21_strcat(str, ".");
    }
  } else {
    number = s21_round(number, fformat.precision);
    mantis = modfl(fabsl(number), &right);

    while (truncl(right / pow) > 0) {
      int digit;
      digit = (int)truncl(fmodl(truncl(right), pow * (long double)10L) / (pow));
      *(p1++) = (char)(digit + '0');
      pow *= 10L;
    }

    if (sign < 0) *(p1++) = '-';
    *p1 = '\0';

    for (int i = 0; i < fformat.precision; i++) pow_t *= 10;

    mantis = roundl(mantis * pow_t);
    pow = 1.0L;

    while (pow < pow_t) {
      int digit;
      digit =
          (int)truncl(fmodl(truncl(mantis), pow * (long double)10L) / (pow));
      *(p2++) = (char)(digit + '0');
      pow *= 10L;
    }

    *p2 = '\0';
    if (fformat.plus) {
      s21_strcat(str, "+");
    }
    if (fformat.space) {
      s21_strcat(str, " ");
    }
    s21_reverse_u_str(num1_str);
    if (s21_strlen(num1_str) == 0) s21_strcat(str, "0");
    s21_strcat(str, num1_str);
    if (fformat.precision > 0 || fformat.sharp == 1) s21_strcat(str, ".");
    if (fformat.precision > 0) {
      s21_reverse_u_str(num2_str);
      s21_strcat(str, num2_str);
    }
  }
  return str;
}

char *s21_d_class_to_str(char *str, long double x, FORMAT fformat) {
  switch (fpclassify(x)) {
    case FP_NAN:
      s21_strcat(str, "nan");
      break;
    case FP_INFINITE:
      s21_strcat(str, "inf");
      break;
    case FP_ZERO:
      if (fformat.plus) {
        s21_strcat(str, "+");
      }
      if (fformat.space) {
        s21_strcat(str, " ");
      }
      s21_strcat(str, "0");
      if (fformat.precision > 0) {
        s21_strcat(str, ".");
        while (fformat.precision--) s21_strcat(str, "0");
      }
      break;
  }
  return str;
}

int s21_check_sign_flags(FORMAT *fformat, long double number) {
  int sign = 1;
  if (signbit(number) == 0) {
    fformat->space = fformat->plus ? 0 : fformat->space;
  } else {
    sign = -1;
    fformat->plus = 0;
    fformat->space = 0;
  }
  return sign;
}

long double s21_round(long double x, int tolerance) {
  long double right = 0.0;
  long double x1 = modfl(fabsl(x), &right);
  int mul = 0;
  int sign = signbit(x) == 0 ? 1 : -1;
  for (int i = 0; i < tolerance; i++) mul--;

  if (roundl(x1 / powl(10, mul)) > truncl(x1 / powl(10, mul))) {
    x = x + (5 * powl(10, mul - 1)) * sign;
  }
  if (tolerance <= 6 && x1 > 0) {
    x = x / powl(10, mul);
    x = powl(10, mul) * truncl(x);
  }
  return x;
}

char *s21_str_to_string(FORMAT fformat, va_list *argList) {
  char *p = s21_NULL;
  char *result_str = s21_NULL;
  p = va_arg(*argList, char *);
  if (p) {
    result_str = (char *)calloc(s21_strlen(p) + fformat.width + 1, 1);
    s21_str_format(result_str, p, fformat);
  } else {
    result_str = (char *)calloc(7, 1);
    s21_str_format(result_str, s21_NULL, fformat);
  }
  return result_str;
}

char *s21_str_format(char *result_str, char *p, FORMAT fformat) {
  if (!p) {
    if (fformat.precision >= 6 || fformat.precision == -1) {
      s21_strcat(result_str, "(null)");
    }
  } else {
    if (fformat.precision > -1) {
      s21_strncat(result_str, p, fformat.precision);
    } else {
      s21_strcat(result_str, p);
    }
  }
  result_str = s21_width_flag(result_str, fformat);
  return result_str;
}

char *s21_u_format(FORMAT fformat, va_list *arg_list) {
  char *str1 = s21_NULL;
  switch (fformat.length) {
    case 'h': {
      if (fformat.double_len) {
        unsigned char uhh_number =
            (unsigned char)va_arg(*arg_list, unsigned int);
        str1 = s21_uns_to_str(fformat, str1, uhh_number);
      } else {
        unsigned short uh_number =
            (unsigned short)va_arg(*arg_list, unsigned int);
        str1 = s21_uns_to_str(fformat, str1, uh_number);
      }
      break;
    }
    case 'l': {
      if (fformat.double_len) {
        str1 =
            s21_uns_to_str(fformat, str1, va_arg(*arg_list, unsigned long int));
      } else {
        str1 = s21_uns_to_str(fformat, str1,
                              va_arg(*arg_list, unsigned long long int));
      }
      break;
    }
    default: {
      unsigned int u_number = (unsigned int)va_arg(*arg_list, unsigned int);
      str1 = s21_uns_to_str(fformat, str1, u_number);
    }
  }
  if (str1 != s21_NULL) {
    s21_uns_precision(str1, fformat);
    str1 = s21_width_flag(str1, fformat);
  }
  return str1;
}

char *s21_uns_to_str(FORMAT fformat, char *str, unsigned long long int number) {
  str = (char *)calloc(21 + fformat.width + fformat.precision, 1);
  if (str != s21_NULL) {
    char *p = s21_NULL;
    int flag = 1;
    p = str;
    while (flag) {
      int digit;
      if (number > 0) {
        digit = (int)(number % 10);
        number = (number - digit) / 10;
        *(p++) = (char)(digit + '0');
      } else {
        flag = 0;
      }
    }
    *p = '\0';
    s21_reverse_u_str(str);
  }
  return str;
}

char *s21_percent_to_string() {
  char *result_perc = (char *)calloc(3, 1);
  s21_strcat(result_perc, "%");
  return result_perc;
}

char *s21_e_format(FORMAT fformat, va_list *arg_list) {
  char *str1 = s21_NULL;
  str1 = (char *)calloc(1000, 1);
  if (str1) {
    switch (fformat.length) {
      case 'l': {
        if (fformat.double_len) {
          str1 = s21_e_to_str(str1, va_arg(*arg_list, long double), &fformat);
        } else {
          str1 = s21_e_to_str(str1, va_arg(*arg_list, double), &fformat);
        }
        break;
      }
      default: {
        double e_number = va_arg(*arg_list, double);
        str1 = s21_e_to_str(str1, e_number, &fformat);
      }
    }
    s21_uns_precision(str1, fformat);
    s21_width_flag(str1, fformat);
  }
  return str1;
}

char *s21_e_to_str(char *str, long double number, FORMAT *fformat) {
  if (fformat->precision < 0) fformat->precision = 6;
  long double right = 0.0, mantis;
  int pow = 0;
  mantis = modfl(fabsl(number), &right);
  if (fpclassify(number) > 3) {
    while (right >= 10) {
      pow++;
      right /= 10;
    }
    if (pow == 0 && right < 1) {
      while (truncl(mantis * powl(10, pow * -1)) < 1) {
        pow--;
      }
    }
  }
  if (fpclassify(number) > 1) {
    number = number / powl(10, pow);
    s21_sprintf(str, fformat->sharp ? "%#.*Lfe%+.2d" : "%.*Lfe%+.2d",
                fformat->precision, number, pow);
  } else {
    s21_sprintf(str, "%Lf");
  }
  fformat->precision = 0;
  int sign = signbit(number);
  if (sign != 0 || fformat->space) {
    s21_reverse_u_str(str);
    if (fformat->space) {
      s21_strcat(str, " ");
    }
    if (sign != 0 && fpclassify(number) < 2) {
      s21_strcat(str, "-");
    }
    s21_reverse_u_str(str);
  }
  if (fformat->spec == 'E') {
    char *p = s21_NULL;
    p = s21_strchr(str, 'e');
    if (p) *p = 'E';
  }
  return str;
}

char *s21_x_format(FORMAT fformat, va_list *arg_list) {
  char *str1 = s21_NULL;
  str1 = (char *)calloc(1000, 1);
  if (str1) {
    switch (fformat.length) {
      case 'h': {
        if (fformat.double_len) {
          unsigned char xhh_number =
              (unsigned char)va_arg(*arg_list, unsigned int);
          str1 = s21_x_to_str(str1, xhh_number, fformat);
        } else {
          unsigned short xh_number =
              (unsigned short)va_arg(*arg_list, unsigned int);
          str1 = s21_x_to_str(str1, xh_number, fformat);
        }
        break;
      }
      case 'l': {
        if (fformat.double_len) {
          str1 = s21_x_to_str(str1, va_arg(*arg_list, unsigned long long int),
                              fformat);
        } else {
          str1 =
              s21_x_to_str(str1, va_arg(*arg_list, unsigned long int), fformat);
        }
        break;
      }
      default: {
        unsigned int x_number = va_arg(*arg_list, unsigned int);
        str1 = s21_x_to_str(str1, x_number, fformat);
      }
    }
    s21_uns_precision(str1, fformat);
    str1 = s21_width_flag(str1, fformat);
  }
  return str1;
}

char *s21_x_to_str(char *str, unsigned long long number, FORMAT fformat) {
  char *p = s21_NULL;
  int flag = 1, shift;
  p = str;
  shift = fformat.spec == 'x' ? 32 : 0;
  while (flag) {
    unsigned int digit;
    if (number > 15) {
      digit = number % 16;
      number = (number - digit) / 16;
    } else {
      digit = number;
      flag = 0;
    }
    if (digit < 10)
      *(p++) = (char)(digit + '0');
    else
      *(p++) = (char)(digit + 'A' + shift - 10);
  }
  *p = '\0';
  s21_reverse_u_str(str);
  return str;
}

char *s21_o_format(FORMAT fformat, va_list *arg_list) {
  char *str1 = s21_NULL;
  str1 = (char *)calloc(1000, 1);
  if (str1) {
    switch (fformat.length) {
      case 'h': {
        if (fformat.double_len) {
          unsigned char ohh_number =
              (unsigned char)va_arg(*arg_list, unsigned int);
          str1 = s21_o_to_str(str1, ohh_number, fformat);
        } else {
          unsigned short oh_number =
              (unsigned short)va_arg(*arg_list, unsigned int);
          str1 = s21_o_to_str(str1, oh_number, fformat);
        }
        break;
      }
      case 'l': {
        if (fformat.double_len) {
          str1 = s21_o_to_str(str1, va_arg(*arg_list, unsigned long long int),
                              fformat);
        } else {
          str1 =
              s21_o_to_str(str1, va_arg(*arg_list, unsigned long int), fformat);
        }
        break;
      }
      default: {
        unsigned int o_number = va_arg(*arg_list, unsigned int);
        str1 = s21_o_to_str(str1, o_number, fformat);
      }
    }
    if (str1 != s21_NULL) {
      s21_uns_precision(str1, fformat);
      str1 = s21_width_flag(str1, fformat);
    }
  }
  return str1;
}

char *s21_o_to_str(char *str, unsigned long long number, FORMAT fformat) {
  char *p = s21_NULL;
  int flag = 1;
  p = str;
  while (flag) {
    unsigned int digit;
    if (number > 7) {
      digit = number % 8;
      number = (number - digit) / 8;
    } else {
      digit = number;
      flag = 0;
    }
    *(p++) = (char)(digit + '0');
  }

  if (fformat.sharp == 1) *(p++) = '0';
  *p = '\0';
  s21_reverse_u_str(str);
  return str;
}

char *s21_p_format(FORMAT fformat, va_list *arg_list) {
  char *str1 = s21_NULL;
  str1 = (char *)calloc(1000, 1);
  if (str1) {
    char *err[] = s21_NULL_PTR;
    int *p = va_arg(*arg_list, int *);
    char buf[6] = "x0";
    if (p == s21_NULL) {
      s21_strcpy(buf, err[0]);
    }
    unsigned long int n = (unsigned long int)p;
    fformat.spec = 'x';
    if (p != s21_NULL) {
      s21_x_to_str(str1, n, fformat);
    }
    s21_reverse_u_str(str1);
    s21_strcat(str1, buf);
    s21_reverse_u_str(str1);
    s21_width_flag(str1, fformat);
  }
  return str1;
}

char *s21_reverse_u_str(char *str) {
  s21_size_t str_len = s21_strlen(str);
  char ch;
  for (s21_size_t i = 0; i < str_len / 2; i++) {
    ch = str[i];
    str[i] = str[str_len - 1 - i];
    str[str_len - 1 - i] = ch;
  }
  return str;
}

char *s21_uns_precision(char *str, FORMAT fformat) {
  char *num_str = (char *)calloc(400 + fformat.width + fformat.precision, 1);
  fformat.precision = fformat.precision == -1 ? 1 : fformat.precision;
  if (num_str) {
    s21_size_t str_len = s21_strlen(str);
    int shift;
    char *p = s21_NULL;
    char *s = s21_NULL;
    p = num_str;
    s = str;
    if (fformat.zero == 1) {
      fformat.precision = (fformat.precision > fformat.width)
                              ? fformat.precision
                              : fformat.width;
    }
    fformat.precision =
        fformat.precision > (int)str_len ? fformat.precision : (int)str_len;
    for (int i = 0; i < fformat.precision; i++) {
      if (i >= fformat.precision - ((int)str_len))
        *(p++) = *(s++);
      else
        *(p++) = '0';
    }
    shift = fformat.spec == 'x' && fformat.sharp == 1 ? 32 : 0;
    if (fformat.sharp == 1 && fformat.spec == (char)('X' + shift)) {
      if (!(str_len == 1 && *str == '0')) {
        s21_reverse_u_str(num_str);
        *(p++) = (char)('X' + shift);
        *(p++) = '0';
        s21_reverse_u_str(num_str);
      }
    }
    *p = '\0';
    s21_strcpy(str, num_str);
    free(num_str);
  }
  return str;
}

char *s21_width_flag(char *str, FORMAT fformat) {
  int str_len = (int)s21_strlen(str);
  if (fformat.width > (int)str_len) {
    char *tmp_str = (char *)calloc(str_len + fformat.width + 10, 1);
    if (tmp_str) {
      for (int i = 0; i < fformat.width; i++) {
        if (fformat.minus == 1) {
          if (i < str_len) {
            tmp_str[i] = str[i];
          } else {
            tmp_str[i] = ' ';
          }
        } else {
          if (i < fformat.width - str_len) {
            tmp_str[i] = ' ';
          } else {
            tmp_str[i] = str[i - (fformat.width - str_len)];
          }
        }
      }
      tmp_str[fformat.width] = '\0';
      str = s21_strcpy(str, tmp_str);
      free(tmp_str);
    }
  }
  return str;
}

char *s21_parser(char *str, char *format_str, FORMAT *fformat,
                 va_list *arg_list) {
  int cont = 1;
  while (*format_str && cont) {
    s21_set_zeroes(fformat);
    fformat->precision = -1;
    if (*format_str == '%') {
      char *temp_ptr = format_str;
      cont = 1;
      format_str++;
      int check = 0;
      int got_num = 0;
      while (cont && !fformat->error) {
        if (s21_IS_NUMERIC(*format_str) && !got_num) {
          if (*format_str != '0' || fformat->point) {
            check = 1;
            got_num = 1;
            format_str = s21_set_numeric(format_str, fformat);
          }
        }
        if (s21_IS_STAR(*format_str) && !got_num) {
          got_num = 1;
          check = 1;
          fformat->error = s21_set_star_val(fformat, arg_list);
        }
        if (s21_IS_SPEC(*format_str)) {
          check = 1;
          fformat->spec = (unsigned char)*format_str;
          cont = 0;
        }
        if (s21_IS_LENGTH(*format_str)) {
          check = 1;
          fformat->error = s21_set_length(format_str, fformat);
        }
        if (s21_IS_FLAG(*format_str)) {
          check = 1;
          fformat->error = s21_set_flag(format_str, fformat);
        }
        if (*format_str == '.') {
          got_num = 0;
          check = 1;
          fformat->error = s21_set_point(fformat);
        }
        if (!check) {
          fformat->error = 1;
        }
        format_str++;
      }
      if (fformat->error) {
        char ch = *format_str;
        *format_str = 0;
        str = s21_strcat(str, temp_ptr);
        *format_str = ch;
        cont = 1;
      }
    } else {
      char ch[2] = {*format_str, '\0'};
      str = s21_strcat(str, ch);
      format_str++;
    }
  }
  return format_str;
}

int s21_set_point(FORMAT *fformat) {
  int error = 1;
  if (!fformat->point && !fformat->length) {
    fformat->point = 1;
    fformat->precision = 0;
    error = 0;
  }
  return error;
}

char *s21_set_numeric(char *format_str, FORMAT *fformat) {
  if (!fformat->length) {
    int num = 0;
    while (s21_IS_NUMERIC(*format_str)) {
      num *= 10;
      num += (int)(*format_str - '0');
      format_str++;
    }
    if (fformat->point) {
      fformat->precision = num;
    } else {
      fformat->width = num;
    }
  } else {
    fformat->error = 1;
  }
  return format_str;
}

int s21_set_star_val(FORMAT *fformat, va_list *arg_list) {
  int error = 1;
  if (!fformat->length) {
    error = 0;
    if (fformat->point) {
      fformat->precision = va_arg(*arg_list, int);
      fformat->precision = fformat->precision > -1 ? fformat->precision : -1;
    } else {
      fformat->width = va_arg(*arg_list, int);
      fformat->width = fformat->width > -1 ? fformat->width : 0;
    }
  }
  return error;
}

int s21_set_flag(char *format_str, FORMAT *fformat) {
  int error = 1;
  if (!fformat->width && !fformat->point && !fformat->length) {
    if (*format_str == ' ') {
      fformat->space = 1;
    }
    if (*format_str == '+') {
      fformat->plus = 1;
    }
    if (*format_str == '-') {
      fformat->minus = 1;
    }
    if (*format_str == '#') {
      fformat->sharp = 1;
    }
    if (*format_str == '0') {
      fformat->zero = 1;
    }
    error = 0;
  }
  return error;
}

int s21_set_length(char *format_str, FORMAT *fformat) {
  int error = 1;
  if (!fformat->length) {
    if (*format_str == 'L') {
      *format_str = 'l';
      fformat->double_len = 1;
    }
    fformat->length = (unsigned char)*format_str;
    error = 0;
  } else if (!fformat->double_len && fformat->length == *format_str) {
    fformat->double_len = 1;
    error = 0;
  }
  return error;
}

void s21_set_zeroes(FORMAT *fformat) {
  fformat->spec = 0;
  fformat->space = 0;
  fformat->minus = 0;
  fformat->plus = 0;
  fformat->point = 0;
  fformat->width = 0;
  fformat->length = 0;
  fformat->double_len = 0;
  fformat->precision = 0;
  fformat->zero = 0;
  fformat->sharp = 0;
  fformat->error = 0;
}
