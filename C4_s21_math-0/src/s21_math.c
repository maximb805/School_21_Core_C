#include "./s21_math.h"

long double s21_asin(double x) {
  return s21_fabs(x) > 1 ? -S21_NAN : s21_atan(x / s21_sqrt((1.0 - (x * x))));
}

long double s21_acos(double x) {
  return s21_fabs(x) > 1 ? -S21_NAN : S21_PI / 2 - s21_asin(x);
}

long double s21_atan(double x) {
  long double result;
  if (x == x && s21_fabs(x) != S21_INF) {
    if (x == -1) {
      result = -S21_PI / 4;
    } else if (x == 1) {
      result = S21_PI / 4;
    } else {
      result = s21_calc_trig(x, 1, 1);
    }
  } else {
    if (x != x) {
      result = S21_NAN;
    } else if (x == S21_INF) {
      result = S21_PI / 2;
    } else {
      result = -S21_PI / 2;
    }
  }
  return result;
}

long double s21_sin(double x) {
  long double result;
  if (x == x && s21_fabs(x) != S21_INF) {
    result = s21_calc_trig(x, 1, 0);
  } else {
    result = S21_NAN;
  }
  return result;
}

long double s21_cos(double x) {
  long double result;
  if (x == x && s21_fabs(x) != S21_INF) {
    result = s21_calc_trig(x, 0, 0);
  } else {
    result = S21_NAN;
  }
  return result;
}

long double s21_tan(double x) {
  long double result;
  if (x == x) {
    result = s21_sin(x) / s21_cos(x);
    if (result != result) {
      result = S21_NAN;
    }
  } else {
    result = S21_NAN;
  }
  return result;
}

long double s21_calc_trig(double x, int shift, int isArctg) {
  long double result = 0.0;
  double x_temp;
  if (!isArctg) {
    x_temp = s21_fmod(x, 2 * S21_PI);
  } else {
    x_temp = s21_fabs(x) > 1 ? 1.0 / x : x;
  }
  long double sub_result;
  int j = 1;
  do {
    sub_result = s21_pow(x_temp, shift);
    if (!isArctg) {
      sub_result = s21_div_fib(sub_result, shift);
    } else {
      sub_result /= shift;
    }
    if (!(j % 2)) {
      sub_result *= -1;
    }
    result += sub_result;
    shift += 2;
    j++;
  } while (s21_fabs(sub_result) > S21_ZERO);
  if (isArctg && s21_fabs(x) > 1) {
    result = (S21_PI / 2) * (s21_fabs(x_temp) / x_temp) - result;
  }
  return result;
}

long double s21_div_fib(long double x, int i) {
  while (i > 0) {
    x /= i;
    i--;
  }
  return x;
}

int s21_abs(int x) { return x < 0 ? -x : x; }

long double s21_floor(double x) {
  long long int i = (long long int)x;
  long double res;
  if (x < (double)i && x < 0.0) {
    res = (long double)(i - 1);
  } else {
    res = (long double)i;
  }
  return res;
}

long double s21_ceil(double x) {
  long long int i = (long long int)x;
  long double res;
  if (x > (double)i && x > 0.0) {
    res = (long double)(i + 1);
  } else {
    res = (long double)i;
  }
  return res;
}

long double s21_exp(double x) { return s21_pow(S21_E, x); }

long double s21_fabs(double x) {
  return x < 0 ? (long double)-x : (long double)x;
}

long double s21_fmod(double x, double y) {
  long double res;
  long long int tmp;
  if (y == 0.0) {
    res = S21_NAN;
  } else if (x == 0.0 && y != 0.0) {
    res = 0;
  } else {
    tmp = (long long int)(x / y);
    res = (long double)x - tmp * (long double)y;
  }
  return res;
}

long double s21_log(double x) {
  long double result;
  if (x >= 0) {
    if (x <= S21_ZERO) {
      result = -S21_INF;
    } else if (x == 0.5) {
      result = S21_LOG_05;
    } else {
      int pow_of_two = 0;
      x = s21_calc_interval(x, &pow_of_two);
      double ex = (x - 1.0) / (x + 1.0);
      result = ex;
      double i = 3.0;
      double step = ex;
      double pow_add = ex * ex;
      while (s21_fabs(step) > S21_ZERO) {
        ex *= pow_add;
        step = ex / i;
        result += step;
        i += 2;
      }
      result = result * 2.0;
      result = result - (pow_of_two * S21_LOG_05);
    }
  } else {
    result = S21_NAN;
  }
  return result;
}

double s21_calc_interval(double x, int *pow_of_two) {
  int sign = 1;
  if (x < 1.0) {
    sign = -1;
    while (x * 2 < 1.0) {
      *pow_of_two = *pow_of_two + 1;
      x *= 2;
    }
  } else {
    while (x / 2 > 0.5) {
      *pow_of_two = *pow_of_two + 1;
      x /= 2;
    }
  }
  *pow_of_two *= sign;
  return x;
}

long double s21_pow(double base, double exp) {
  long double result = 1.0;
  int check = s21_check_base_exp(base, exp, &result);
  if (check && s21_fabs(exp) > S21_ZERO && base != 1.0) {
    if (s21_fabs(base) > S21_ZERO) {
      if (base > 0 ||
          (s21_fabs(exp - (long long int)exp) < S21_ZERO && base < 0)) {
        result = s21_int_pow(base, (long long int)exp);
        long double e_pow =
            (s21_fabs(exp - (long long int)exp) * s21_log(s21_fabs(base)));
        int i = 1;
        double step = 1.0;
        double step_buff = 1;
        double sub_result = 1.0;
        while (s21_fabs(step) > S21_ZERO) {
          step_buff *= e_pow;
          step = step_buff;
          step = s21_div_fib(step, i);
          sub_result += step;
          i++;
        }
        sub_result = exp < 0 ? 1.0 / sub_result : sub_result;
        result *= sub_result;
      } else {
        result = S21_NAN;
      }
    } else {
      result = exp > 0 ? 0.0 : S21_INF;
    }
  }
  return result;
}

int s21_check_base_exp(double base, double exp, long double *result) {
  int check = 1;
  if (s21_fabs(exp) == S21_INF) {
    check = 0;
    if (base == 0 || base == 1.0 || base == -1.0) {
      *result = base * base;
    } else if (base == base) {
      if (exp == S21_INF) {
        *result = s21_fabs(base) < 1.0 ? 0.0 : S21_INF;
      } else {
        *result = s21_fabs(base) < 1.0 ? S21_INF : 0.0;
      }
    } else {
      *result = S21_NAN;
    }
  }
  if (check && exp != exp && base != 1.0) {
    check = 0;
    *result = S21_NAN;
  }
  if (check && s21_fabs(base) == S21_INF) {
    check = 0;
    if (exp != 0.0) {
      *result = exp > 0 ? S21_INF : 1.0 / S21_INF;
      if (exp - (long long int)exp < S21_ZERO &&
          (long long int)exp % 2 != 0.0) {
        *result = *result == s21_fabs(base) ? base : *result;
        *result = *result == 0.0 ? -0.0 : *result;
      }
    } else {
      *result = 1.0;
    }
  }
  return check;
}

long double s21_int_pow(double x, long long int exp) {
  if (exp == 0) {
    x = 1.0;
  } else {
    double step = x;
    long long int i = exp < 0 ? exp * -1 : exp;
    while (i > 1) {
      x *= step;
      i--;
    }
  }
  return exp < 0 ? 1.0 / x : x;
}

long double s21_sqrt(double x) {
  long double result;
  if (x < 0) {
    result = S21_NAN;
  } else if (x == 1.0 || x == 0.0) {
    result = x;
  } else {
    long double max = x < 1.0 ? 1.0 : x;
    result = s21_binary_search(0.0, max, x);
  }
  return result;
}

long double s21_binary_search(long double min, long double max, double x) {
  long double med = (max + min) / 2.0;
  if (max - min > S21_ZERO) {
    if (med * med > x) {
      med = s21_binary_search(min, med - S21_ZERO, x);
    } else {
      med = s21_binary_search(med + S21_ZERO, max, x);
    }
  }
  return med;
}
