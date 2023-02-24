#ifndef S21_MATH_H_
#define S21_MATH_H_

#define S21_ZERO 0.0000000000001
#define S21_NAN (0.0 / 0.0)
#define S21_INF (1.0 / 0.0)
#define S21_E 2.71828182845904523536
#define S21_PI 3.14159265358979323846
#define S21_LOG_05 -0.693147180559945286227

int s21_abs(int x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_ceil(double x);
long double s21_fmod(double x, double y);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_exp(double x);
long double s21_sqrt(double x);
long double s21_sin(double x);
long double s21_cos(double x);
long double s21_tan(double x);
long double s21_atan(double x);
long double s21_asin(double x);
long double s21_acos(double x);

long double s21_int_pow(double x, long long int exp);
long double s21_binary_search(long double min, long double max, double x);
long double s21_div_fib(long double sub_result, int i);
long double s21_calc_trig(double x, int shift, int isArctg);
double s21_calc_interval(double x, int *pow_of_two);
int s21_check_base_exp(double base, double exp, long double *result);

#endif  // S21_MATH_H_
