#include "s21_smart_calc.h"

void s21_calculate_credit_annuity(double total, double term, double rate,
                                  char *total_payment_str, char *monthly_str,
                                  char *overpayment_str) {
  rate /= 1200.0;
  double monthly = total * (rate / (1.0 - (1.0 / pow(1.0 + rate, term))));
  s21_round_double(&monthly);
  double total_payment = monthly * term;
  double overpayment = total_payment - total;
  sprintf(total_payment_str, "%.2lf", total_payment);
  sprintf(monthly_str, "%.2lf", monthly);
  sprintf(overpayment_str, "%.2lf", overpayment);
}

void s21_calculate_credit_differentiated(double total, double term, double rate,
                                         char *total_payment_str,
                                         char *monthly_str,
                                         char *overpayment_str) {
  double payment_main = total / term;
  double payment_rate = 0;
  double first_payment = 0;
  double last_payment = 0;
  double total_payment = 0;
  double overpayment = 0.0 - total;
  for (int i = 0; i < term; i++) {
    payment_rate = (total * (rate / 100.0)) / 12.0;
    total_payment += payment_rate + payment_main;
    total -= payment_main;
    if (i == 0) {
      first_payment = payment_main + payment_rate;
    }
    if (i == term - 1) {
      last_payment = payment_main + payment_rate;
    }
  }
  s21_round_double(&first_payment);
  s21_round_double(&last_payment);
  s21_round_double(&total_payment);
  overpayment += total_payment;
  sprintf(total_payment_str, "%.2lf", total_payment);
  sprintf(monthly_str, "%.2lf ... %.2lf", first_payment, last_payment);
  sprintf(overpayment_str, "%.2lf", overpayment);
}

void s21_round_double(double *value) {
  long sub_value = (long)(*value * 1000);
  if (sub_value % 10 >= 5) {
    sub_value += 10;
  }
  sub_value /= 10;
  *value = (double)sub_value;
  *value /= 100;
}
