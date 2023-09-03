#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_math.h"

#define LEN_ARR(arr) (int)(sizeof(arr)/sizeof(arr[0]))

//#define ASSERT(f21, f, value) ck_assert_ldouble_eq_tol(f21(value), (long double)(f(value)), EPSILON)

#define ASSERT_MSG_FMT  "%s %.7lf: s21: %.7Lf f: %.7Lf, equal = %d\n"

static inline void PRINT(long double (*f21)(double), double (*f)(double), double value) {
    long double out21 = f21(value);
    long double out = (long double)f(value);
    int equal = EQUAL(out21, out);
    printf(ASSERT_MSG_FMT, "", value, out21, out, equal);
}

static inline void ASSERT(long double (*f21)(double), double (*f)(double), double value) {
    long double out21 = f21(value);
    long double out = (long double)f(value);
    int equal = EQUAL(out21, out);
    ck_assert_msg(equal, ASSERT_MSG_FMT, "failed on value", value, out21, out, equal);
}

#define ASSERT_ARGS(f21, f) assert_args(args, LEN_ARR(args), f21, f)


static inline void assert_args(double *args, int args_size,
    long double (*f21)(double), double (*f)(double)) {

    for (int i = 0; i < args_size; i++) {
        ASSERT(f21, f, args[i]);
    }
}

START_TEST(s21_ceil_f) {
    double args[] = {1.5, 0.45, -3.01, -0, 1234567};
    assert_args(args, LEN_ARR(args), s21_ceil, ceil);
}
END_TEST

START_TEST(s21_floor_f) {
    double args[] = {1.5, 0.45, -3.01, -0, 1234567};
    assert_args(args, LEN_ARR(args), s21_floor, floor);
}
END_TEST

static inline void assert_trigonometry(long double (*f21)(double),
    double (*f)(double)) {

    for (double i = -100; i < 100; i += 2) {
        ASSERT(f21, f, i);
    }
    for (double i = M_PI * 1; i <= M_PI; i += 0.01) {
        ASSERT(f21, f, i);
    }
}

static inline void assert_trigonometry_arc(long double (*f21)(double),
    double (*f)(double)) {

    for (double i = -1; i <= 1; i += 0.01) {
        ASSERT(f21, f, i);
    }
}

START_TEST(s21_tan_f) {
    assert_trigonometry(s21_tan, tan);
}
END_TEST

START_TEST(s21_cos_f) {
    assert_trigonometry(s21_cos, cos);
}
END_TEST

START_TEST(s21_sin_f) {
    assert_trigonometry(s21_sin, sin);
}
END_TEST

START_TEST(s21_atan_f) {
    assert_trigonometry_arc(s21_atan, atan);
}
END_TEST

START_TEST(s21_acos_f) {
    assert_trigonometry_arc(s21_acos, acos);
}
END_TEST

START_TEST(s21_asin_f) {
    assert_trigonometry_arc(s21_asin, asin);
}
END_TEST

START_TEST(s21_fmod_f) {
    ck_assert_ldouble_eq_tol(s21_fmod(456.87678, 3.7), fmod(456.87678, 3.7), EPSILON);
    ck_assert_ldouble_eq_tol(s21_fmod(36677.546546, 4.1), fmod(36677.546546, 4.1), EPSILON);
    ck_assert_ldouble_eq_tol(s21_fmod(23.456, 4.355), fmod(23.456, 4.355), EPSILON);
}
END_TEST

START_TEST(s21_exp_f) {
    ASSERT(s21_exp, exp, 5.);
    ASSERT(s21_exp, exp, -2.);
    ASSERT(s21_exp, exp, -1234567.);
    //ck_assert_ldouble_eq_tol(s21_exp(1234567.), exp(1234567.), EPSILON);
    //ASSERT(s21_exp, exp, 1234567.);
    for (double i = -10; i < 10; i++) {
        ASSERT(s21_exp, exp, i);
    }
}
END_TEST

START_TEST(s21_log_f) {
    ASSERT(s21_log, log, 12356);
    ASSERT(s21_log, log, 1.1);
    for (double i = 0.1; i < 10; i += 0.1) {
        ASSERT(s21_log, log, i);
    }
    for (double i = 0.1; i < 2; i += 0.01) {
        ASSERT(s21_log, log, i);
    }
}
END_TEST

START_TEST(s21_sqrt_f) {
    double args[] = {16.0, 45.43, 5., 0};
    //assert_args(args, LEN_ARR(args), s21_ceil, ceil);
    ASSERT_ARGS(s21_sqrt, sqrt);

    for (double i = -1.; i < 100000; i += 10) {
        ASSERT(s21_sqrt, sqrt, i);
    }
    for (double i = 0; i < 1; i += 0.001) {
        ASSERT(s21_sqrt, sqrt, i);
    }
}
END_TEST

START_TEST(s21_fabs_f) {
    double args[] = {0, -1, 1, INT_MAX, INT_MIN, s21_INF};
    
    ASSERT_ARGS(s21_fabs, fabs);
}
END_TEST

START_TEST(s21_abs_f) {
    int args[] = {0, -1, 1, INT_MAX, INT_MIN};
    for (int i = 0; i < LEN_ARR(args); i++) {
        ck_assert_int_eq(s21_abs(args[i]), abs(args[i]));
    }
}
END_TEST

/*
** TWO ARGS
*/

START_TEST(s21_pow_f) {
    ck_assert_ldouble_eq_tol(s21_pow(2.6, 3.45), pow(2.6, 3.45), EPSILON);
    ck_assert_ldouble_eq_tol(s21_pow(3.0, 14.0), pow(3.0, 14.0), EPSILON);
    ck_assert_ldouble_eq_tol(s21_pow(31.456, 4.3), pow(31.456, 4.3), EPSILON);
    ck_assert_ldouble_eq_tol(s21_pow(31.456, 0.3), pow(31.456, 0.3), EPSILON);
    ck_assert_ldouble_eq_tol(s21_pow(4.3, 4.3), pow(4.3, 4.3), EPSILON);
    printf("f21: %Lf, f: %lf\n", s21_pow(-1234, 4), pow(-1234, 4));
    ck_assert_ldouble_eq_tol(s21_pow(-1234, 4.0), pow(-1234, 4.0), EPSILON);
    ck_assert_ldouble_eq_tol(s21_pow(1234, -4.3), pow(1234, -4.3), EPSILON);
}
END_TEST

Suite *lib_suite(void) {
    Suite *s;
    s = suite_create("Func Check");

    TCase *tc_ceil;
    TCase *tc_floor;
    TCase *tc_tan;
    TCase *tc_cos;
    TCase *tc_sin;
    TCase *tc_abs;
    TCase *tc_atan;
    TCase *tc_acos;
    TCase *tc_asin;
    TCase *tc_fmod;
    TCase *tc_exp;
    TCase *tc_log;
    TCase *tc_sqrt;
    TCase *tc_pow;
    TCase *tc_fabs;
    TCase *tc_t_double;

    tc_fabs = tcase_create("Fabs");
    suite_add_tcase(s, tc_fabs);
    tcase_add_test(tc_fabs, s21_fabs_f);

    tc_pow = tcase_create("Pow");
    suite_add_tcase(s, tc_pow);
    tcase_add_test(tc_pow, s21_pow_f);

    tc_sqrt = tcase_create("Sqrt");
    suite_add_tcase(s, tc_sqrt);
    tcase_add_test(tc_sqrt, s21_sqrt_f);

    tc_log = tcase_create("Log");
    suite_add_tcase(s, tc_log);
    tcase_add_test(tc_log, s21_log_f);

    tc_exp = tcase_create("Exp");
    suite_add_tcase(s, tc_exp);
    tcase_add_test(tc_exp, s21_exp_f);

    tc_fmod = tcase_create("Fmod");
    suite_add_tcase(s, tc_fmod);
    tcase_add_test(tc_fmod, s21_fmod_f);

    tc_asin = tcase_create("Asin");
    suite_add_tcase(s, tc_asin);
    tcase_add_test(tc_asin, s21_asin_f);

    tc_acos = tcase_create("Acos");
    suite_add_tcase(s, tc_acos);
    tcase_add_test(tc_acos, s21_acos_f);

    tc_atan = tcase_create("Atan");
    suite_add_tcase(s, tc_atan);
    tcase_add_test(tc_atan, s21_atan_f);

    tc_abs = tcase_create("Abs");
    suite_add_tcase(s, tc_abs);
    tcase_add_test(tc_abs, s21_abs_f);

    tc_sin = tcase_create("Sin");
    suite_add_tcase(s, tc_sin);
    tcase_add_test(tc_sin, s21_sin_f);

    tc_cos = tcase_create("Cos");
    suite_add_tcase(s, tc_cos);
    tcase_add_test(tc_cos, s21_cos_f);

    tc_tan = tcase_create("Tan");
    suite_add_tcase(s, tc_tan);
    tcase_add_test(tc_tan, s21_tan_f);

    tc_floor = tcase_create("Floor");
    suite_add_tcase(s, tc_floor);
    tcase_add_test(tc_floor, s21_floor_f);

    tc_ceil = tcase_create("Ceil");
    suite_add_tcase(s, tc_ceil);
    tcase_add_test(tc_ceil, s21_ceil_f);

    return s;
}

int main(void) {
    Suite *s;
    SRunner *sr;

    s = lib_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_VERBOSE);
    srunner_free(sr);
    return 0;
}