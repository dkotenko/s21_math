#pragma once

#include <limits.h>
#include <stdint.h>
#include <stdio.h>

#define s21_PI 3.14159265358979324
#define s21_N_PI -3.14159265358979324
#define s21_EPS 1e-17
#define s21_ln10 2.30258509299404590109
#define s21_INF 1.0 / 0.0
#define s21_N_INF -1.0 / 0.0
#define s21_NAN 0.0 / 0.0
#define s21_N_NAN -0.0 / 0.0
#define s21_MAX_double 1.7976931348623157e308
#define EPSILON 1e-10
#define s21_E 2.7182818284590452354

#define EQUAL(out21, out) (long double)out21 - (long double)out < EPSILON

long int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_acos_test(double x);
long double s21_asin_test(double x);
long double s21_atan_test(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_pow(double base, double exp);
long double s21_sin(double x);
long double s21_sin_test(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);
long double s21_log(double x);
int s21_factrial(int x);
long double s21_sqrt_test(double x);

// Function checks if double agruments are infinite, or other NaN values.
//  Exceptions: 0 - inf; 1 - neg inf; 2 - NaN; 3 - neg NaN
int input_check(double x1, double x2, double* exception1, double* exception2);
double normalize_radian(double x);
long double checker(double x);