#include <stdio.h>
#include <stdint.h>
#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif
#include <math.h>

#ifndef FUNCTION
#define FUNCTION isnan
#endif

#define FUNCTION_CALL(type)	PASTE(FUNCTION,type)
#define PASTE(x,y)	PASTE1(x,y)
#define PASTE1(x,y)	x##y

int main() {
	_Decimal32 d32;
	_Decimal64 d64;
	_Decimal128 d128;
	int inf;

	d32 = -1.20DF;
	inf = FUNCTION_CALL()(d32);
	printf("%d = isnan(%Hf)\n", inf, d32);

	d32 = NAN;
	inf = FUNCTION_CALL()(d32);
	printf("%d = isnan(%Hf)\n", inf, d32);

	d64  = -0.00DD/0.0DD;
	inf = FUNCTION_CALL()(d64);
	printf("%d = isnan(%Df)\n", inf, d64);

	d64  = NAN;
	inf = FUNCTION_CALL()(d64);
	printf("%d = isnan(%Df)\n", inf, d64);

	d128 = -1.20DL;
	inf = FUNCTION_CALL()(d128);
	printf("%d = isnan(%DDf)\n", inf, d128);

	d128 = NAN;
	inf = FUNCTION_CALL()(d128);
	printf("%d = isnan(%DDf)\n", inf, d128);
}
