#define _GNU_SOURCE
#define __USE_GNU
#define __STDC_WANT_DEC_FP__ 1
#include <fenv.h>
#include <math.h>
#include <float.h>
#include <stdio.h>

int main() {
  _Decimal64 d164;
  _Decimal64 d264;
  _Decimal64 res;
  int exc;

  exc = feenableexcept(FE_DIVBYZERO);

  d164 = 35.0DD;
  d264 = 0.0DD;

  res = d164/d264;

  printf ("res: %Df\n", res);

  return 0;
}
