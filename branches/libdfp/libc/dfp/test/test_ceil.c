#include <stdio.h>
#include <stdint.h>
#define __STDC_WANT_DEC_FP__ 1
#include <math.h>

#ifndef FUNCTION
#define FUNCTION ceil
#endif

#define FUNCTION_CALL(type)	PASTE(FUNCTION,type)
#define PASTE(x,y)	PASTE1(x,y)
#define PASTE1(x,y)	x##y

int main() {
	_Decimal32 d32;
	_Decimal32 cd32;
	_Decimal64 d64;
	_Decimal64 cd64;
	_Decimal128 d128;
	_Decimal128 cd128;
	
	d32  = -19.54DF;
	cd32  = 0.0DF;

	d64  = -19.54DD;
	cd64 = 0.0DD;

	d128 = -19.54DL;
	cd128 = 0.0DL;

	cd32 = FUNCTION_CALL(d32)(d32);
	printf("%Hf = ceild32(%Hf)\n", cd32, d32);
	d32  = 19.54DF;
	cd32 = FUNCTION_CALL(d32)(d32);
	printf("%Hf = ceild32(%Hf)\n", cd32, d32);

	cd64 = FUNCTION_CALL(d64)(d64);
	printf("%Df = ceild64(%Df)\n", cd64, d64);
	d64  = 19.54DD;
	cd64 = FUNCTION_CALL(d64)(d64);
	printf("%Df = ceild64(%Df)\n", cd64, d64);

	cd128 = FUNCTION_CALL(d128)(d128);
	printf("%DDf = ceild128(%DDf)\n", cd128, d128);
	d128 = 19.54DL;
	cd128 = FUNCTION_CALL(d128)(d128);
	printf("%DDf = ceild128(%DDf)\n", cd128, d128);
}
