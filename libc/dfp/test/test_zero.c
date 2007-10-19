#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <fenv.h>










volatile _Decimal32 sd;
volatile _Decimal64 dd;
volatile float sf;
volatile double df;

void
f1 (void)
{
  dd = -0.DD;
  df = dd;
  printf ("expected -0, got %f, signbit = %d\n",
          df, (__builtin_signbit (df) != 0));
}

void
f2 (void)
{
  sd = 0.DD;
  df = sd;
  printf ("expected 0, got %f, signbit = %d\n",
          df, (__builtin_signbit (df) != 0));
}

void
f3 (void)
{
  sd = __builtin_infd32 ();
  df = sd;
  printf ("expected inf, got %f, signbit = %d\n",
          df, (__builtin_signbit (df) != 0));
}

int
main ()
{
  

  f1 ();
  f2 ();
  f3 ();

  return 0;
}
