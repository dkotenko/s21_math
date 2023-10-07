#include "tests.h"

/*
** TWO ARGS
*/

#define ASSERT_POW(v1, v2) ck_assert_ldouble_eq_tol(v1, v2, EPSILON);

START_TEST(s21_pow_f) {
  ck_assert_ldouble_eq_tol(s21_pow(2.6, 3.45), pow(2.6, 3.45), EPSILON);
  ck_assert_ldouble_eq_tol(s21_pow(3.0, 14.0), pow(3.0, 14.0), EPSILON);
  ck_assert_ldouble_eq_tol(s21_pow(31.456, 4.3), pow(31.456, 4.3), EPSILON);
  ck_assert_ldouble_eq_tol(s21_pow(31.456, 0.3), pow(31.456, 0.3), EPSILON);
  ck_assert_ldouble_eq_tol(s21_pow(4.3, 4.3), pow(4.3, 4.3), EPSILON);
  ck_assert_ldouble_eq_tol(s21_pow(-1234, 4.0), pow(-1234, 4.0), EPSILON);
  ck_assert_ldouble_eq_tol(s21_pow(1234, -4.3), pow(1234, -4.3), EPSILON);

  ASSERT_POW(s21_pow(0, 1), pow(0, 1));
  ASSERT_POW(s21_pow(0, 2), pow(0, 2));

  ASSERT_POW(s21_pow(0, 2), pow(0, 2));

  ck_assert_double_infinite(s21_pow(
      0, s21_N_INF));  // pow(0, s21_N_INF) = inf, по этому, проверяем так.
  ASSERT_POW(s21_pow(-1, s21_N_INF), pow(-1, s21_N_INF));
  ASSERT_POW(s21_pow(-1, s21_INF), pow(-1, s21_INF));
}
END_TEST

START_TEST(s21_pow_zero_base_nan_exp) {
  ASSERT_POW(s21_pow(0, s21_NAN), pow(0, s21_NAN));
}
END_TEST

START_TEST(s21_pow_zero_base_nnan_exp) {
  ASSERT_POW(s21_pow(0, s21_N_NAN), pow(0, s21_N_NAN));
}
END_TEST

START_TEST(s21_pow_zero_base_zero_exp) { ASSERT_POW(s21_pow(0, 0), pow(0, 0)); }
END_TEST

Suite *pow_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("pow");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_pow_f);
  tcase_add_test(tc_core, s21_pow_zero_base_zero_exp);
  tcase_add_test(tc_core, s21_pow_zero_base_nan_exp);
  tcase_add_test(tc_core, s21_pow_zero_base_nnan_exp);
  suite_add_tcase(s, tc_core);

  return s;
}
