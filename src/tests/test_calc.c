#include "tests.h"

START_TEST(test_add_1) {
  char *input = "5 + 10 + 97 + ln( 12 )";
  double res = 0;
  double res1 = 5 + 10 + 97 + log(12);
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_1) {
  char *input = "5+2*2^3";
  double res = 0;
  double res1 = 21;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_2) {
  char *input = "5^2*2-3";
  double res = 0;
  double res1 = 47;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_3) {
  char *input = "(5+2)*2^3";
  double res = 0;
  double res1 = 56;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_4) {
  char *input = "5+(2*2)^3";
  double res = 0;
  double res1 = 69;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_5) {
  char *input = "3 mod 9 + 1 * 9 mod 2";
  double res = 0;
  double res1 = 3 % 9 + 1 * 9 % 2;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_6) {
  char *input = "1 +2 /2 *23 - 8 /1.2 ^ 1.12 ";
  double res = 0;
  double res1 = 1.0 + 2.0 / 2.0 * 23.0 - 8.0 / pow(1.2, 1.12);
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_7) {
  char *input = "cos(12+ 123) - 33 * 12 / tan(0.001)";
  double res = 0;
  double res1 = cos(12 + 123) - 33.0 * 12.0 / tan(0.001);
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_8) {
  char *input = "sin(0)*cos(1)*sin(2)^cos(13)";
  double res = 0;
  double res1 = pow(sin(0) * cos(1) * sin(2), cos(13));
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_9) {
  char *input = "acos(12) + 12.23  - 13.2";
  double res = 0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, RESISNAN);
}
END_TEST

START_TEST(test_calc_10) {
  char *input = "atan(1) + asin(-1) - acos(0)";
  double res = 0;
  double res1 = atan(1) + asin(-1) - acos(0);
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_11) {
  char *input = "sqrt(ln(log(cos(1.2))))";
  double res = 0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, RESISNAN);
}
END_TEST

START_TEST(test_calc_12) {
  char *input = "sqrt(ln(log(cos(3.1415))))";
  double res = 0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, RESISNAN);
}
END_TEST

START_TEST(test_calc_13) {
  char *input = "ln(123)+log(123)";
  double res = 0;
  double res1 = log(123) + log10(123);
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_14) {
  char *input = "1+acos(-3)";
  double res = 0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, RESISNAN);
}
END_TEST

START_TEST(test_calc_15) {
  char *input = "ln(123)+log(123) - sin(1.2)^(log(ln(sqrt(456))))";
  double res = 0;
  double res1 = log(123) + log10(123) - pow(sin(1.2), (log10(log(sqrt(456)))));
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_16) {
  char *input = "-1-2-3-4-5-6";
  double res = 0;
  double res1 = -1 - 2 - 3 - 4 - 5 - 6;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_17) {
  char *input = "acos(-1.0001)";
  double res = 0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, RESISNAN);
}
END_TEST

START_TEST(test_calc_18) {
  char *input = "ln(-1)";
  double res = 0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, RESISNAN);
}
END_TEST

START_TEST(test_calc_19) {
  char *input = "+1 - asin(-0.5) + acos(-0.1) * 12 ^ 0.5 -(-(-3))";
  double res = 0;
  double res1 = +1.0 - asin(-0.5) + acos(-0.1) * pow(12, 0.5) - (-(-3));
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_20) {
  char *input = "sqrt(-(-(-(-1))))";
  double res = 0;
  double res1 = 1;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_21) {
  char *input = "cos(-(-(-(-(-(0.5))))))*acos(-(-(-(-0.5))))";
  double res = 0;
  double res1 = cos(-(-(-(-(-(0.5)))))) * acos(-(-(-(-0.5))));
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_22) {
  char *input = "(-4)^12";
  double res = 0;
  double res1 = pow(-4, 12);
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_incorrect_1) {
  char *input = "12.23.3";
  double res = 0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_incorrect_2) {
  char *input = "sin3";
  double res = 0.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_incorrect_3) {
  char *input = "six";
  double res = 0.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_incorrect_4) {
  char *input = "sin()";
  double res = 0.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_incorrect_5) {
  char *input = "cos(12sin(2))";
  double res = 0.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_incorrect_6) {
  char *input = "-(-1)+1(";
  double res = 0.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_incorrect_7) {
  char *input = ")1(";
  double res = 0.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_incorrect_8) {
  char *input = "a cos(1)";
  double res = 0.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_incorrect_9) {
  char *input = "*-1";
  double res = 0.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_incorrect_10) {
  char *input = "+-1";
  double res = 0.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_incorrect_11) {
  char *input = "1 mod";
  double res = 0.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_incorrect_12) {
  char *input = "mod             1";
  double res = 0.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_incorrect_13) {
  char *input = "-1                 + 2";
  double res = 0.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, 1, ACCURACY);
}
END_TEST

START_TEST(test_incorrect_14) {
  char *input = "1-";
  double res = 0.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_incorrect_15) {
  char *input = "sqrt(1.2+)";
  double res = 0.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_incorrect_16) {
  char *input = "=";
  double res = 0.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_incorrect_17) {
  char *input = "zrada";
  double res = 0.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_incorrect_18) {
  char *input = "-";
  double res = 0.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_incorrect_19) {
  char *input = "+";
  double res = 0.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_incorrect_20) {
  char *input = "a^2";
  double res = 0.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_add_1_x) {
  char *input = "5 + x + 97 + ln( 12 )";
  double res = 10.0;
  double res1 = 5 + 10 + 97 + log(12);
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_1_x) {
  char *input = "5+x*x^3";
  double res = 2.0;
  double res1 = 21;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_2_x) {
  char *input = "5^x*x-3";
  double res = 2.0;
  double res1 = 47;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_3_x) {
  char *input = "(5+x)*x^3";
  double res = 2.0;
  double res1 = 56;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_4_x) {
  char *input = "5+(x*x)^3";
  double res = 2.0;
  double res1 = 69;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_5_x) {
  char *input = "3 mod x + 1 * x mod 2";
  double res = 9.0;
  double res1 = 3 % 9 + 1 * 9 % 2;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_6_x) {
  char *input = "1 +x /x *23 - 8 /1.2 ^ 1.12 ";
  double res = 2.0;
  double res1 = 1.0 + 2.0 / 2.0 * 23.0 - 8.0 / pow(1.2, 1.12);
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_7_x) {
  char *input = "cos(x+ 123) - 33 * x / tan(0.001)";
  double res = 12.0;
  double res1 = cos(12 + 123) - 33.0 * 12.0 / tan(0.001);
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_8_x) {
  char *input = "sin(x)*cos(1)*sin(2)^cos(13)";
  double res = 0;
  double res1 = pow(sin(0) * cos(1) * sin(2), cos(13));
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_9_x) {
  char *input = "acos(12) + x  - 13.2";
  double res = 12.23;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, RESISNAN);
}
END_TEST

START_TEST(test_calc_10_x) {
  char *input = "atan(x) + asin(-x) - acos(0)";
  double res = 1.0;
  double res1 = atan(1) + asin(-1) - acos(0);
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_11_x) {
  char *input = "sqrt(ln(log(cos(x))))";
  double res = 1.2;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, RESISNAN);
}
END_TEST

START_TEST(test_calc_12_x) {
  char *input = "sqrt(ln(log(cos(x))))";
  double res = 3.1415;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, RESISNAN);
}
END_TEST

START_TEST(test_calc_13_x) {
  char *input = "ln(x)+log(x)";
  double res = 123.0;
  double res1 = log(123) + log10(123);
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_14_x) {
  char *input = "x+acos(-3)";
  double res = 1.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, RESISNAN);
}
END_TEST

START_TEST(test_calc_15_x) {
  char *input = "ln(x)+log(x) - sin(1.2)^(log(ln(sqrt(456))))";
  double res = 123.0;
  double res1 = log(123) + log10(123) - pow(sin(1.2), (log10(log(sqrt(456)))));
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_16_x) {
  char *input = "-1-2-3-4-x-6";
  double res = 5.0;
  double res1 = -1 - 2 - 3 - 4 - 5 - 6;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_17_x) {
  char *input = "acos(-x)";
  double res = -1.0001;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, RESISNAN);
}
END_TEST

START_TEST(test_calc_18_x) {
  char *input = "ln(-x)";
  double res = 1.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, RESISNAN);
}
END_TEST

START_TEST(test_calc_19_x) {
  char *input = "+1 - asin(-x) + acos(-0.1) * 12 ^ x -(-(-3))";
  double res = 0.5;
  double res1 = +1.0 - asin(-0.5) + acos(-0.1) * pow(12, 0.5) - (-(-3));
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_20_x) {
  char *input = "sqrt(-(-(-(-x))))";
  double res = 1.0;
  double res1 = 1;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_21_x) {
  char *input = "cos(-(-(-(-(-(x))))))*acos(-(-(-(-x))))";
  double res = 0.5;
  double res1 = cos(-(-(-(-(-(0.5)))))) * acos(-(-(-(-0.5))));
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_22_x) {
  char *input = "(-4)^x";
  double res = 12.0;
  double res1 = pow(-4, 12);
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_23_x) {
  char *input = "ln(-xxx)";
  double res = 1.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_calc_24_x) {
  char *input = "xx";
  double res = 1.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_calc_25_x) {
  char *input = "six";
  double res = 1.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_calc_26_x) {
  char *input = "sinx";
  double res = 1.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_calc_27_x) {
  char *input = "sqxt";
  double res = 1.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_calc_28_x) {
  char *input = "lx";
  double res = 1.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_calc_29_x) {
  char *input = "xmodsinx";
  double res = 1.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_calc_30_x) {
  char *input = "x / sin(x)";
  double res = 12.0;
  double res1 = 12.0 / sin(12.0);
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_31_x) {
  char *input = "x mod sin(x)";
  double res = 3.12;
  double res1 = fmod(3.12, sin(3.12));
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_32_x) {
  char *input = "m";
  double res = 1.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_calc_33_x) {
  char *input = "2 mod sin(2)";
  double res = 12.0;
  double res1 = fmod(2.0, sin(2.0));
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_34_x) {
  char *input = "2 mod 2";
  double res = 12.0;
  double res1 = fmod(2.0, 2.0);
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_35_x) {
  char *input = "sin(5) mod 2";
  double res = 12.0;
  double res1 = fmod(sin(5.0), 2.0);
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_36_x) {
  char *input = "sin(x) mod x";
  double res = 13.0;
  double res1 = fmod(sin(13.0), 13.0);
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_37_x) {
  char *input = "sin(x) mod sin(x)";
  double res = 22.0;
  double res1 = fmod(sin(22.0), sin(22.0));
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_38_x) {
  char *input = "x mod sin(x)";
  double res = 1.2344;
  double res1 = fmod(1.2344, sin(1.2344));
  int error = calculator(input, &res);
  ck_assert_int_eq(error, OK);
  ck_assert_double_eq_tol(res, res1, ACCURACY);
}
END_TEST

START_TEST(test_calc_39_x) {
  char *input = "4x";
  double res = 1.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_calc_40_x) {
  char *input = "x4";
  double res = 1.0;
  int error = calculator(input, &res);
  ck_assert_int_eq(error, INCORRECT);
}
END_TEST

START_TEST(test_calc_1_havex) {
  char *input = "x+4";
  int error = check_for_x(input);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_calc_2_havex) {
  char *input = "sin(x)+4";
  int error = check_for_x(input);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_calc_3_havex) {
  char *input = "x+2mod3";
  int error = check_for_x(input);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_calc_4_havex) {
  char *input = "2+3+4+sin";
  int error = check_for_x(input);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calc_5_havex) {
  char *input = "1+2+3+x";
  int error = check_for_x(input);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_calc_dop_1) {
  double res = 0.0;
  char *input = "(11+2)+ 2) + 2)";
  int error = calculator(input, &res);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_calc_dop_2) {
  double res = 0.0;
  char *input = "coc(2)";
  int error = calculator(input, &res);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_calc_dop_3) {
  double res = 0.0;
  char *input = "six(2)";
  int error = calculator(input, &res);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_calc_dop_4) {
  double res = 0.0;
  char *input = "lom(2)";
  int error = calculator(input, &res);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_calc_dop_5) {
  double res = 0.0;
  char *input = "sinx(2)";
  int error = calculator(input, &res);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_calc_dop_6) {
  double res = 0.0;
  char *input = "qwer(2)";
  int error = calculator(input, &res);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_calc_dop_7) {
  double res = 0.0;
  char *input = "sin(x)";
  int error = calculator(input, &res);
  ck_assert_int_eq(error, 0);
}
END_TEST

Suite *test_calc_complements(void) {
  Suite *s = suite_create("\033[45m-=s21_smartcalc_tests=-\033[0m");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_add_1);
  tcase_add_test(tc_core, test_calc_1);
  tcase_add_test(tc_core, test_calc_2);
  tcase_add_test(tc_core, test_calc_3);
  tcase_add_test(tc_core, test_calc_4);
  tcase_add_test(tc_core, test_calc_5);
  tcase_add_test(tc_core, test_calc_6);
  tcase_add_test(tc_core, test_calc_7);
  tcase_add_test(tc_core, test_calc_8);
  tcase_add_test(tc_core, test_calc_9);
  tcase_add_test(tc_core, test_calc_10);
  tcase_add_test(tc_core, test_calc_11);
  tcase_add_test(tc_core, test_calc_12);
  tcase_add_test(tc_core, test_calc_13);
  tcase_add_test(tc_core, test_calc_14);
  tcase_add_test(tc_core, test_calc_15);
  tcase_add_test(tc_core, test_calc_16);
  tcase_add_test(tc_core, test_calc_17);
  tcase_add_test(tc_core, test_calc_18);
  tcase_add_test(tc_core, test_calc_19);
  tcase_add_test(tc_core, test_calc_20);
  tcase_add_test(tc_core, test_calc_21);
  tcase_add_test(tc_core, test_calc_22);
  tcase_add_test(tc_core, test_incorrect_1);
  tcase_add_test(tc_core, test_incorrect_2);
  tcase_add_test(tc_core, test_incorrect_3);
  tcase_add_test(tc_core, test_incorrect_4);
  tcase_add_test(tc_core, test_incorrect_5);
  tcase_add_test(tc_core, test_incorrect_6);
  tcase_add_test(tc_core, test_incorrect_7);
  tcase_add_test(tc_core, test_incorrect_8);
  tcase_add_test(tc_core, test_incorrect_9);
  tcase_add_test(tc_core, test_incorrect_10);
  tcase_add_test(tc_core, test_incorrect_11);
  tcase_add_test(tc_core, test_incorrect_12);
  tcase_add_test(tc_core, test_incorrect_13);
  tcase_add_test(tc_core, test_incorrect_14);
  tcase_add_test(tc_core, test_incorrect_15);
  tcase_add_test(tc_core, test_incorrect_16);
  tcase_add_test(tc_core, test_incorrect_17);
  tcase_add_test(tc_core, test_incorrect_18);
  tcase_add_test(tc_core, test_incorrect_19);
  tcase_add_test(tc_core, test_incorrect_20);
  tcase_add_test(tc_core, test_add_1_x);
  tcase_add_test(tc_core, test_calc_1_x);
  tcase_add_test(tc_core, test_calc_2_x);
  tcase_add_test(tc_core, test_calc_3_x);
  tcase_add_test(tc_core, test_calc_4_x);
  tcase_add_test(tc_core, test_calc_5_x);
  tcase_add_test(tc_core, test_calc_6_x);
  tcase_add_test(tc_core, test_calc_7_x);
  tcase_add_test(tc_core, test_calc_8_x);
  tcase_add_test(tc_core, test_calc_9_x);
  tcase_add_test(tc_core, test_calc_10_x);
  tcase_add_test(tc_core, test_calc_11_x);
  tcase_add_test(tc_core, test_calc_12_x);
  tcase_add_test(tc_core, test_calc_13_x);
  tcase_add_test(tc_core, test_calc_14_x);
  tcase_add_test(tc_core, test_calc_15_x);
  tcase_add_test(tc_core, test_calc_16_x);
  tcase_add_test(tc_core, test_calc_17_x);
  tcase_add_test(tc_core, test_calc_18_x);
  tcase_add_test(tc_core, test_calc_19_x);
  tcase_add_test(tc_core, test_calc_20_x);
  tcase_add_test(tc_core, test_calc_21_x);
  tcase_add_test(tc_core, test_calc_22_x);
  tcase_add_test(tc_core, test_calc_23_x);
  tcase_add_test(tc_core, test_calc_24_x);
  tcase_add_test(tc_core, test_calc_25_x);
  tcase_add_test(tc_core, test_calc_26_x);
  tcase_add_test(tc_core, test_calc_27_x);
  tcase_add_test(tc_core, test_calc_28_x);
  tcase_add_test(tc_core, test_calc_29_x);
  tcase_add_test(tc_core, test_calc_30_x);
  tcase_add_test(tc_core, test_calc_31_x);
  tcase_add_test(tc_core, test_calc_32_x);
  tcase_add_test(tc_core, test_calc_33_x);
  tcase_add_test(tc_core, test_calc_34_x);
  tcase_add_test(tc_core, test_calc_35_x);
  tcase_add_test(tc_core, test_calc_36_x);
  tcase_add_test(tc_core, test_calc_37_x);
  tcase_add_test(tc_core, test_calc_38_x);
  tcase_add_test(tc_core, test_calc_39_x);
  tcase_add_test(tc_core, test_calc_40_x);
  tcase_add_test(tc_core, test_calc_1_havex);
  tcase_add_test(tc_core, test_calc_2_havex);
  tcase_add_test(tc_core, test_calc_3_havex);
  tcase_add_test(tc_core, test_calc_4_havex);
  tcase_add_test(tc_core, test_calc_5_havex);
  tcase_add_test(tc_core, test_calc_dop_1);
  tcase_add_test(tc_core, test_calc_dop_2);
  tcase_add_test(tc_core, test_calc_dop_3);
  tcase_add_test(tc_core, test_calc_dop_4);
  tcase_add_test(tc_core, test_calc_dop_5);
  tcase_add_test(tc_core, test_calc_dop_6);
  tcase_add_test(tc_core, test_calc_dop_7);
  suite_add_tcase(s, tc_core);

  return s;
}
