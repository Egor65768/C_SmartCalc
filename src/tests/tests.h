#ifndef TESTS_H
#define TESTS_H

#include <check.h>

#include "../s21_calc.h"

#define ACCURACY 1e-06

enum status { OK, INCORRECT, RESISNAN };

Suite *test_calc_complements(void);
Suite *test_calc_credit(void);
Suite *test_calc_dep(void);

#endif