#include "tests.h"

START_TEST(test_dep_1) {
  DEPOSIT s21_dep = {0};
  double balance = 300000.0;
  s21_dep.persent_year = 10;
  s21_dep.ful_sum = 300000.0;
  s21_dep.num_month = 6;
  s21_dep.type_pay = 3;
  s21_dep.type = 2;
  int day[6] = {29, 31, 30, 31, 30, 31};
  double pay[6] = {2377.05, 2561.12, 2499.49, 2603.98, 2541.32, 2647.56};
  for (int i = 0; i < 6; i++) {
    s21_calculate_deposit_interest(&s21_dep, 366, day[i]);
    balance = balance + pay[i];
    ck_assert_double_eq_tol(s21_dep.money_month, pay[i], 0.1);
    ck_assert_double_eq_tol(s21_dep.ful_sum, balance, 0.1);
  }
}
END_TEST

START_TEST(test_dep_2) {
  DEPOSIT s21_dep = {0};
  s21_dep.persent_year = 10;
  s21_dep.ful_sum = 300000.0;
  s21_dep.num_month = 6;
  s21_dep.type_pay = 3;
  s21_dep.type = 1;
  int day[6] = {29, 31, 30, 31, 30, 31};
  double pay[6] = {2377.05, 2540.98, 2459.02, 2540.98, 2459.02, 2540.98};
  double balans[6] = {300000.0, 300000.0, 300000.0,
                      300000.0, 300000.0, 300000.0};
  for (int i = 0; i < 6; i++) {
    s21_calculate_deposit_interest(&s21_dep, 366, day[i]);
    ck_assert_double_eq_tol(s21_dep.payments, pay[i], 0.1);
    ck_assert_double_eq_tol(s21_dep.ful_sum, balans[i], 0.1);
  }
}
END_TEST

START_TEST(test_dep_3) {
  DEPOSIT s21_dep = {0};
  s21_dep.persent_year = 10;
  s21_dep.ful_sum = 300000.0;
  s21_dep.num_month = 6;
  s21_dep.type_pay = 3;
  s21_dep.type = 3;
  s21_dep.add_or_sub = 1000.0;
  s21_dep.ful_sum = 301000.0;
  s21_calculate_deposit_interest(&s21_dep, 366, 30);
  ck_assert_double_eq_tol(s21_dep.ful_sum, 301000.0, 0.1);
  ck_assert_double_eq_tol(s21_dep.add_or_sub, 0, 0.1);
}
END_TEST

Suite *test_calc_dep(void) {
  Suite *s = suite_create("\033[45m-=s21_deposit_tests=-\033[0m");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_dep_1);
  tcase_add_test(tc_core, test_dep_2);
  tcase_add_test(tc_core, test_dep_3);
  suite_add_tcase(s, tc_core);

  return s;
}
