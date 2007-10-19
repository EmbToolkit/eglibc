#include <stdio.h>
#include <stdint.h>
#define __STDC_WANT_DEC_FP__ 1
#include <math.h>

#ifndef FUNCTION
#define FUNCTION floor
#endif

#define FUNCTION_CALL(type)	PASTE(FUNCTION,type)
#define PASTE(x,y)	PASTE1(x,y)
#define PASTE1(x,y)	x##y

int main() {
	_Decimal32 d32;
	_Decimal32 fd32;
	_Decimal64 d64;
	_Decimal64 fd64;
	_Decimal128 d128;
	_Decimal128 fd128;
	
	d32  = -19.54DF;
	fd32  = 0.0DF;

	d64  = -19.54DD;
	fd64 = 0.0DD;

	d128 = -19.54DL;
	fd128 = 0.0DL;

	fd32 = FUNCTION_CALL(d32)(d32);
	printf("%Hf = floord32(%Hf)\n", fd32, d32);
	d32  = 19.54DF;
	fd32 = FUNCTION_CALL(d32)(d32);
	printf("%Hf = floord32(%Hf)\n", fd32, d32);

	fd64 = FUNCTION_CALL(d64)(d64);
	printf("%Df = floord64(%Df)\n", fd64, d64);
	d64  = 19.54DD;
	fd64 = FUNCTION_CALL(d64)(d64);
	printf("%Df = floord64(%Df)\n", fd64, d64);

	fd128 = FUNCTION_CALL(d128)(d128);
	printf("%DDf = floord128(%DDf)\n", fd128, d128);
	d128 = 19.54DL;
	fd128 = FUNCTION_CALL(d128)(d128);
	printf("%DDf = floord128(%DDf)\n", fd128, d128);
}
