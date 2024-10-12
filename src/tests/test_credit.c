#include "tests.h"

START_TEST(test_credit_an) {
  CREDIT credit1_an = {0};
  credit1_an.ful_sum = 200000;
  credit1_an.num_mont = 6;
  credit1_an.persent_year = 15.0;
  credit1_an.type = 1;
  double main_pay[6] = {32306.76, 32710.59, 33119.48,
                        33533.47, 33952.64, 34377.05};
  double remains[6] = {167693.24, 134982.65, 101863.17,
                       68329.7,   34377.06,  0.01};
  int res = 0, i = 0;
  while (res == 0) {
    res = s21_calculate_credit_payment(&credit1_an);
    ck_assert_double_eq_tol(credit1_an.main_pay, main_pay[i], 0.1);
    ck_assert_double_eq_tol(credit1_an.month_sum, 34806.76, 0.1);
    ck_assert_double_eq_tol(credit1_an.remains, remains[i], 0.1);
    i++;
  }
}
END_TEST

START_TEST(test_credit_dif) {
  CREDIT credit1_an = {0};
  credit1_an.ful_sum = 200000;
  credit1_an.num_mont = 6;
  credit1_an.persent_year = 15.0;
  credit1_an.type = 2;
  double month_pay[6] = {35833.33, 35416.67, 35000.00,
                         34583.33, 34166.67, 33750.00};
  double remains[6] = {166666.67, 133333.33, 100000.00, 66666.67, 33333.33, 0};
  int res = 0, i = 0;
  while (res == 0) {
    res = s21_calculate_credit_payment(&credit1_an);
    ck_assert_double_eq_tol(credit1_an.main_pay, 33333.33, 0.1);
    ck_assert_double_eq_tol(credit1_an.month_sum, month_pay[i], 0.1);
    ck_assert_double_eq_tol(credit1_an.remains, remains[i], 0.1);
    i++;
  }
}
END_TEST

Suite *test_calc_credit(void) {
  Suite *s =
      suite_create("\033[45m-=s21_calculate_credit_payment_tests=-\033[0m");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_credit_an);
  tcase_add_test(tc_core, test_credit_dif);
  suite_add_tcase(s, tc_core);

  return s;
}
