#include <stdio.h>
#include <stdint.h>
#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif
#include <math.h>

#ifndef FUNCTION
#define FUNCTION isunordered
#endif

#define FUNCTION_CALL(type)	PASTE(FUNCTION,type)
#define PASTE(x,y)	PASTE1(x,y)
#define PASTE1(x,y)	x##y

int main() {
	_Decimal32 d32;
	_Decimal32 e32;
	_Decimal64 d64;
	_Decimal64 e64;
	_Decimal128 d128;
	_Decimal128 e128;
	int unordered;

	d32 = -1.20DF;
	e32 = 1.0DF;
	unordered = FUNCTION_CALL()(d32,e32);
	printf("%d = isunordered(%Hf,%Hf)\n", unordered, d32, e32);

	d32 = NAN;
	e32 = 1.0DD;
	unordered = FUNCTION_CALL()(d32,e32);
	printf("%d = isunordered(%Hf,%Hf)\n", unordered, d32, e32);

	d64  = -1.20DD;
	e64 = 1.0DD;
	unordered = FUNCTION_CALL()(d64,e64);
	printf("%d = isunordered(%Df,%Df)\n", unordered, d64, e64);

	d64  = NAN;
	e64 = 1.0DL;
	unordered = FUNCTION_CALL()(d64,e64);
	printf("%d = isunordered(%Df,%Df)\n", unordered, d64, e64);

	d128 = -1.20DL;
	e128 = 1.0DL;
	unordered = FUNCTION_CALL()(d128,e128);
	printf("%d = isunordered(%DDf,%DDf)\n", unordered, d128, e128);

	d128 = NAN;
	e128 = 1.0DL;
	unordered = FUNCTION_CALL()(d128,e128);
	printf("%d = isunordered(%DDf,%DDf)\n", unordered, d128, e128);
}
