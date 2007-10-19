#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <fenv.h>


void reset() {
  feclearexcept(FE_ALL_EXCEPT);
}

void report() {
  int set_excepts;
  set_excepts = fetestexcept(FE_ALL_EXCEPT);
  if (set_excepts & FE_INVALID) printf(" FE_INVALID");
  if (set_excepts & FE_OVERFLOW) printf(" FE_OVERFLOW");
  if (set_excepts & FE_UNDERFLOW) printf(" FE_UNDERFLOW");
  if (set_excepts & FE_INEXACT) printf(" FE_INEXACT");
  if (set_excepts & FE_DIVBYZERO) printf(" FE_DIVBYZERO");
  if (!set_excepts) printf(" none");
  printf("\n");
}

#define TEST(x)  printf(#x ":"); reset(); x; report();

int
main (void)
{
  _Decimal32 d;
  _Decimal128 d128;
  double f64;
  float f32;

TEST( acosd32 (2.0DF) )

TEST( sqrtd32 (-1.0DF) )
  
TEST( d=powd32(2e10DF, 2e10DF) );

TEST( d=powd32(2e-1DF, 2e10DF) );

TEST( d=1.DF / 0.DF );

d128 = powd128(10, 309);
TEST( f64 = d128 );
TEST( f32 = d128 );

//  printf("%Hf\n", d);
//  printf("%f\n", f32);
//  printf("%DDf\n", d128);
  return 0;
}

