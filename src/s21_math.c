#include "s21_math.h"

#define POW_2(x): x * x

long int s21_abs(int x) {
  if (x < 0) x *= -1;
  return x;
}

long double s21_fabs(double x) {
  if (x < 0) x *= -1;
  return x;
}

double normalize_radian(double x) {
  while (x > s21_PI || x < -s21_PI) {
    x += x > s21_PI ? -2 * s21_PI : 2 * s21_PI;
  }
  return x;
}
// sin
long double s21_sin(double x) {
  x = normalize_radian(x);
  long double rez = x, y = x;
  long double i = 1.;
  while (s21_fabs(rez) > s21_EPS) {
    rez = -1 * rez * x * x / (2 * i * (2 * i + 1));
    i += 1.;
    y += rez;
  }
  return y;
}
// cos
long double s21_cos(double x) {
  x = normalize_radian(x);
  return s21_sin((s21_PI / 2.0) - x);
}
// tan
long double s21_tan(double x) {
  x = normalize_radian(x);
  return s21_sin(x) / s21_cos(x);
}

// arcsin
long double s21_asin(double x) {
  long double rez = x, y = x;
  long double i = 1;
  while (s21_fabs(rez) > s21_EPS) {
    if (x < -1 || x > 1) {
      y = s21_NAN;
      break;
    }
    if (x == 1 || x == -1) {
      y = s21_PI / 2 * x;
      break;
    }
    rez *= x * x * (2 * i - 1) * (2 * i - 1) / ((2 * i + 1) * 2 * i);
    i += 1;
    y += rez;
  }
  return y;
}
// arccos
long double s21_acos(double x) {
  if (x <= 1 && x >= -1) {
    x = s21_PI / 2. - s21_asin(x);
  } else {
    x = s21_NAN;
  }
  return x;
}
// arctan
long double s21_atan(double x) {
  long double y = 0;
  y = (x < 1 && x > -1) ? checker(x) : y;
  y = x == 1 ? s21_PI / 4 : x == -1 ? s21_N_PI / 4 : x == 0 ? 0 : y;
  y = x > 1    ? s21_PI / 2 - checker(1 / x)
      : x < -1 ? s21_N_PI / 2 - checker(1 / x)
               : y;
  return y;
}
// 1 > arctan > -1
long double checker(double x) {
  long double rez = x, y = x, i = 1;
  while (s21_fabs(rez) > s21_EPS) {
    rez = -1 * rez * x * x * (2 * i - 1) / (2 * i + 1);
    i += 1;
    y += rez;
  }
  return y;
}
// nearest int larger or equal
long double s21_ceil(double num) {
  if (num >= LLONG_MAX || num <= LLONG_MIN || num != num) {
    return num;
  }
  long long n = (long long)num;
  double d = (double)n;
  if (d == num || num <= 0)
    return d;
  else
    return d + 1;
}
// nearest int less or equal
long double s21_floor(double num) {
  if (num >= LLONG_MAX || num <= LLONG_MIN || num != num) {
    return num;
  }
  long long n = (long long)num;
  double d = (double)n;
  if (d == num || num >= 0)
    return d;
  else
    return d - 1;
}
// e raised to xth power
long double s21_exp(double x) {
  /*
  int a = 0, b = n > 0;
  double c = 1, d = 1, e = 1;
  for (b || (n = -n); e + s21_EPS < (e += (d *= n) / (c *= ++a)););
  return b ? e : (double)1 / e;
  */

  long double rez = 1, y = 1;
  long double i = 1;
  int flag = 0;
  if (x < 0) {
    x *= -1;
    flag = 1;
  }
  while (s21_fabs(rez) > s21_EPS) {
    rez *= x / i;
    i++;
    y += rez;
    if (y > s21_MAX_double) {
      y = s21_INF;
      break;
    }
  }
  y = flag == 1 ? y > s21_MAX_double ? 0 : 1. / y : y;
  return y = y > s21_MAX_double ? s21_INF : y;
}
// remainder x / y
long double s21_fmod(double x, double y) {
  long double rez = s21_fabs(x);
  y = s21_fabs(y);
  int i = 1;
  while (rez > y) {
    rez = s21_fabs(x) - y * i;
    i++;
  }
  return x < 0 ? -rez : rez;
}

// logarithm
long double s21_log(double n) {
  int a = 0, b;
  double c, d, e, f;
  if (n < 0)
    c = s21_NAN;
  else if (n == 0) {
    c = s21_N_INF;
  } else {
    for (; (d = n / s21_E) > 1; ++a, n = d)
      ;
    for (; (d = n * s21_E) < 1; --a, n = d)
      ;
    d = (double)1 / (n - 1), d = d + d + 1, e = d * d, c = 0;
    for (b = 1, f = 1; c + s21_EPS < (c += (double)1 / (b * f)); b += 2, f *= e)
      ;
    c *= 2 / d;
  }
  return (double)a + c;
}

// base raised to the power of exp
// binary pow algorithm
long double s21_pow_binary(double base, double exp) {
  double y = 1.0;
  unsigned long long exp_buf = exp;
  while (exp_buf != 0) {
    if (exp_buf & 1) {  // Проверка на нечётность
      y *= base;
    }
    base *= base;
    exp_buf >>= 1;  // Целочисленное деление на 2
  }
  return y;
}

long double s21_pow_fraction(double base, double exp) {
  double y = 1;
  if (exp < 0) {
    exp = -exp;
    y = s21_exp(exp * s21_log(exp));
    if (s21_fmod(exp, 2) != 0) {
      y = -y;
    }
  } else {
    y = s21_exp(exp * s21_log(base));
  }

  return y;
}

// base raised to the power of exp
// Mixed algorithm
long double s21_pow(double base, double exp) {
  double y = 1;
  int even = 0;
  int neg = 0;
  if (base < 0.0) {
    neg = 1;
    base *= -1;
    if ((int)exp % 2 == 0) even = 1;
  }
  if (base != 1.0 || exp != 0.0) {
    double exp_abs = s21_fabs(exp);

    unsigned long int exp_integer_part = (long int)exp_abs;
    double exp_fraction_part = exp_abs - exp_integer_part;

    y = s21_pow_fraction(base, exp_fraction_part) *
        s21_pow_binary(base, exp_integer_part);

    if (exp < 0.0) y = 1.0 / y;
  }
  if (neg && !even) y *= -1;
  return y;
}

// square root of x
long double s21_sqrt(double x) {
  double y_last = 0, y = 1.0;

  while (s21_fabs(y_last - y) >= EPSILON)  // Считаем до нужной точности.
  {
    if (x < 0) {
      y = s21_N_NAN;
      break;
    }
    y_last = y;
    y = (y + x / y) / 2;
  }

  return y;
}

int s21_factrial(int x) {
  int y = 0;

  if (x > 0)
    y *= s21_factrial(x - 1);
  else if (x == 0)
    y = 1;

  return y;
}