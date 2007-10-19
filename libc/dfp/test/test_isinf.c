#include <stdio.h>
#include <stdint.h>
#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif
#include <math.h>

#ifndef FUNCTION
#define FUNCTION isinf
#endif

#define FUNCTION_CALL(type)	PASTE(FUNCTION,type)
#define PASTE(x,y)	PASTE1(x,y)
#define PASTE1(x,y)	x##y

#define DEC_INFINITYDF	DEC_INFINITY
#define DEC_INFINITYDD	(_Decimal64)DEC_INFINITY
#define DEC_INFINITYDL	(_Decimal128)DEC_INFINITY

int main() {
	_Decimal32 d32;
	_Decimal64 d64;
	_Decimal128 d128;
	int inf;

	d32 = -1.20DF;
	inf = FUNCTION_CALL()(d32);
	printf("%d = isinf(%Hf)\n", inf, d32);

	d32 = DEC_INFINITY;
	inf = FUNCTION_CALL()(d32);
	printf("%d = isinf(%Hf)\n", inf, d32);

	d32 = DEC_INFINITYDF;
	inf = FUNCTION_CALL()(d32);
	printf("%d = isinf(%Hf)\n", inf, d32);

	d32 = -DEC_INFINITYDF;
	inf = FUNCTION_CALL()(d32);
	printf("%d = isinf(%Hf)\n", inf, d32);

	d64  = -1.20DD;
	inf = FUNCTION_CALL()(d64);
	printf("%d = isinf(%Df)\n", inf, d64);

	d64  = DEC_INFINITY;
	inf = FUNCTION_CALL()(d64);
	printf("%d = isinf(%Df)\n", inf, d64);

	d64  = DEC_INFINITYDD;
	inf = FUNCTION_CALL()(d64);
	printf("%d = isinf(%Df)\n", inf, d64);

	d64  = -DEC_INFINITYDD;
	inf = FUNCTION_CALL()(d64);
	printf("%d = isinf(%Df)\n", inf, d64);

	d128 = -1.20DL;
	inf = FUNCTION_CALL()(d128);
	printf("%d = isinf(%DDf)\n", inf, d128);

	d128 = DEC_INFINITY;
	inf = FUNCTION_CALL()(d128);
	printf("%d = isinf(%DDf)\n", inf, d128);

	d128 = DEC_INFINITY;
	inf = FUNCTION_CALL()(d128);
	printf("%d = isinf(%DDf)\n", inf, d128);

	d128 = -DEC_INFINITYDL;
	inf = FUNCTION_CALL()(d128);
	printf("%d = isinf(%DDf)\n", inf, d128);

	return 0;
}
