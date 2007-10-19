#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif
#include <stdio.h>
#include <stdint.h>

#include "test_math.h"

int main() {

//	TEST_f(scalbnd64, 500.0DD,%Df,5.0DD,2);

//	TEST_f_f_i_all(scalbn,500.0,5.0,2);
	TEST_f_f_i_all(scalbn,100000.0,100.0,3);
//	TEST_f_f_i_all(scalbn,0.003,3.0,-3);
/*
	TEST_f_f_i_all(scalbn,100000.0,100.0,3);
	TEST_f_f_i_all(scalbn,0.003,3.0,-3);


 do { do { typeof(500.0DF) res = scalbnd32 (5.0DF, 2); if(res == 500.0DF || ((!((_Decimal128)(__typeof__(500.0DF))1.E-50DL == 1.E-50DL) ? ((sizeof (500.0DF) == sizeof (float) ? __isnanf (500.0DF) : sizeof (500.0DF) == sizeof (double) ? __isnan (500.0DF) : __isnanl (500.0DF))) : (sizeof (500.0DF) == sizeof (_Decimal128) ? __isnand128(500.0DF) : (sizeof (500.0DF) == sizeof (_Decimal64) ? __isnand64(500.0DF) : __isnand32(500.0DF))) ) && (!((_Decimal128)(__typeof__(res))1.E-50DL == 1.E-50DL) ? ((sizeof (res) == sizeof (float) ? __isnanf (res) : sizeof (res) == sizeof (double) ? __isnan (res) : __isnanl (res))) : (sizeof (res) == sizeof (_Decimal128) ? __isnand128(res) : (sizeof (res) == sizeof (_Decimal64) ? __isnand64(res) : __isnand32(res))) ))) printf("Success: ""%Hf"" = ""scalbnd32"" (""5.0DF, 2"")\n",res); else printf("Error: ""%Hf"" = ""scalbnd32"" (""5.0DF, 2"") : should be ""500.0DF""\n", res); } while(0);
      do { typeof(500.0DD) res = scalbnd64 (5.0DD, 2); if(res == 500.0DD || ((!((_Decimal128)(__typeof__(500.0DD))1.E-50DL == 1.E-50DL) ? ((sizeof (500.0DD) == sizeof (float) ? __isnanf (500.0DD) : sizeof (500.0DD) == sizeof (double) ? __isnan (500.0DD) : __isnanl (500.0DD))) : (sizeof (500.0DD) == sizeof (_Decimal128) ? __isnand128(500.0DD) : (sizeof (500.0DD) == sizeof (_Decimal64) ? __isnand64(500.0DD) : __isnand32(500.0DD))) ) && (!((_Decimal128)(__typeof__(res))1.E-50DL == 1.E-50DL) ? ((sizeof (res) == sizeof (float) ? __isnanf (res) : sizeof (res) == sizeof (double) ? __isnan (res) : __isnanl (res))) : (sizeof (res) == sizeof (_Decimal128) ? __isnand128(res) : (sizeof (res) == sizeof (_Decimal64) ? __isnand64(res) : __isnand32(res))) ))) printf("Success: ""%Df"" = ""scalbnd64"" (""5.0DD, 2"")\n",res); else printf("Error: ""%Df"" = ""scalbnd64"" (""5.0DD, 2"") : should be ""500.0DD""\n", res); } while(0); } while(0);
      */
}

