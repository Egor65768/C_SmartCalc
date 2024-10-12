#include "s21_calc.h"

int s21_calculate_credit_payment(CREDIT* credit_stac) {
  int res = 0;
  double month_pr = credit_stac->persent_year / 12 / 100;
  if (credit_stac->current_month == 0) {
    credit_stac->remains = credit_stac->ful_sum;
  }
  credit_stac->month_persent = credit_stac->remains * month_pr;
  if (credit_stac->type == 1) {
    double K = (month_pr * pow(1 + month_pr, credit_stac->num_mont)) /
               (pow(1 + month_pr, credit_stac->num_mont) - 1);
    credit_stac->month_sum = credit_stac->ful_sum * K;
    credit_stac->main_pay = credit_stac->month_sum - credit_stac->month_persent;
    credit_stac->remains = credit_stac->remains - credit_stac->main_pay;
  } else {
    credit_stac->main_pay = credit_stac->ful_sum / credit_stac->num_mont;
    double main_remains = credit_stac->ful_sum -
                          credit_stac->main_pay * credit_stac->current_month;
    credit_stac->month_persent =
        main_remains * (credit_stac->persent_year / 12 / 100);
    credit_stac->month_sum = credit_stac->month_persent + credit_stac->main_pay;
    credit_stac->remains = credit_stac->remains - credit_stac->main_pay;
  }
  credit_stac->current_month++;
  credit_stac->all_pay = credit_stac->all_pay + credit_stac->month_sum;
  if (credit_stac->current_month == credit_stac->num_mont) {
    res = 1;
  }
  return res;
}