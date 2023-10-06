#include <math.h>
#include <stdio.h>

#include "s21_math.h"

#define X 2.5, -0.4

int main() {
  long double x = -2, z = 5;
  printf("atan TESTS!!!\n\n Original: %.11Lf\n ", powl(X));
  // printf("S21_test: %Lf\n ", s21_sqrt_test(x));
  printf("s21:      %.11Lf\n", s21_pow(X));
  // printf("TESTS!!!\n\n Original: %ld.\n S21: %ld\n\n\n", sin(-3),
  // s21_sin_test(-3)); printf("TESTS!!!\n\n Original: %ld.\n S21: %ld\n\n\n",
  // s21_sin(-3), s21_sin(-3));

  return 0;
}

//  gcc main.c s21_math.c -o math_test

// s21_N_NAN s21_NAN s21_N_INF s21_INF