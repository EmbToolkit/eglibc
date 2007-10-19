#include <stdio.h>
#include <stdint.h>
#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif
#include <math.h>
#include <float.h>

#ifndef FUNCTION
#define FUNCTION isnormal
#endif

#define FUNCTION_CALL(type)	PASTE(FUNCTION,type)
#define PASTE(x,y)	PASTE1(x,y)
#define PASTE1(x,y)	x##y

union dec32 {
	_Decimal32 d;
	int i;
};

int main() {
	/*_Decimal32 d32; */
	union dec32 d32;
	_Decimal32 d33;
	_Decimal64 d64;
	_Decimal128 d128;
	int normal;

	d33 = -1.20DF;
	normal = FUNCTION_CALL()(d33);
	printf("%d = isnormal(%Hf)\n", normal, d33);

	d33 = __DEC32_DEN__;
	normal = FUNCTION_CALL()(d33);
	printf("%d = isnormal(%Hf)\n", normal, d33);

	d64  = -1.20DD;
	normal = FUNCTION_CALL()(d64);
	printf("%d = isnormal(%Df)\n", normal, d64);

	d64  = -1.20DD;
	normal = FUNCTION_CALL()(d64);
	printf("%d = isnormal(%Df)\n", normal, d64);

	d128 = __DEC128_DEN__;
	normal = FUNCTION_CALL()(d128);
	printf("%d = isnormal(%DDf)\n", normal, d128);

	d128 = -1.20DL;
	normal = FUNCTION_CALL()(d128);
	printf("%d = isnormal(%DDf)\n", normal, d128);

	d33 = 10.0E-96DF;
	normal = FUNCTION_CALL()(d33);
	printf("%d = isnormal(%Hf)\n", normal, d33);

	d33 = 1000.0E-98DF;
	normal = FUNCTION_CALL()(d33);
	printf("%d = isnormal(%Hf)\n", normal, d33);

	d33 = 1.0E-96DF;
	normal = FUNCTION_CALL()(d33);
	printf("%d = isnormal(%Hf)\n", normal, d33);
}
