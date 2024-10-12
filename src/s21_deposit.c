#include "s21_calc.h"

int s21_calculate_deposit_interest(DEPOSIT* s21_dep, int days_in_year,
                                   int day_in_last) {
  int status = 0;
  if (s21_dep->add_or_sub > 0 && day_in_last != 0) {
    s21_dep->ful_sum = s21_dep->ful_sum - s21_dep->add_or_sub;
  }
  s21_dep->money_month = s21_dep->ful_sum * s21_dep->persent_year *
                         day_in_last / days_in_year / 100;
  s21_dep->money = s21_dep->money + s21_dep->money_month;
  s21_dep->money_year = s21_dep->money_year + s21_dep->money_month;
  if (s21_dep->type == 2) {
    s21_dep->ful_sum = s21_dep->ful_sum + s21_dep->money_month;
    s21_dep->payments = 0;
    s21_dep->delta = s21_dep->money_month;
  } else {
    s21_dep->payments = s21_dep->money_month;
    s21_dep->delta = 0;
  }
  if (s21_dep->add_or_sub > 0) {
    if (day_in_last != 0) {
      s21_dep->ful_sum = s21_dep->ful_sum + s21_dep->add_or_sub;
    }
    s21_dep->add_or_sub = 0;
  }
  return status;
}