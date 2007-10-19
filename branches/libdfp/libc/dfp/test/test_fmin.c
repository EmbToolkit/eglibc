#include <stdio.h>
#include <stdint.h>
#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif
#include <math.h>

#ifndef FUNCTION
#define FUNCTION fmin
#endif

#define FUNCTION_CALL(type)	PASTE(FUNCTION,type)
#define PASTE(x,y)	PASTE1(x,y)
#define PASTE1(x,y)	x##y

int main() {
	_Decimal32 ad32;
	_Decimal32 bd32;
	_Decimal32 cd32;

	_Decimal64 ad64;
	_Decimal64 bd64;
	_Decimal64 cd64;

	_Decimal128 ad128;
	_Decimal128 bd128;
	_Decimal128 cd128;
	
	ad32  = -19.54DF;
	bd32  = -19.55DF;
	cd32 = FUNCTION_CALL(d32)(ad32,bd32);
	printf("%Hf = fmind32(%Hf,%Hf)\n", cd32, ad32, bd32);

	ad32  = 19.54DF;
	bd32  = 19.55DF;
	cd32 = FUNCTION_CALL(d32)(ad32,bd32);
	printf("%Hf = fmind32(%Hf,%Hf)\n", cd32, ad32, bd32);

	ad64  = -19.54DD;
	bd64 = -19.55DD;
	cd64 = FUNCTION_CALL(d64)(ad64,bd64);
	printf("%Df = fmind64(%Df,%Df)\n", cd64, ad64, bd64);

	ad64  = 19.54DD;
	bd64  = 19.55DD;
	cd64 = FUNCTION_CALL(d64)(ad64,bd64);
	printf("%Df = fmind64(%Df,%Df)\n", cd64, ad64, bd64);

	ad128 = -19.54DL;
	bd128 = -19.55DL;
	cd128 = FUNCTION_CALL(d128)(ad128,bd128);
	printf("%DDf = fmind128(%DDf,%DDf)\n", cd128, ad128, bd128);

	ad128 = 19.54DL;
	bd128 = 19.55DL;
	cd128 = FUNCTION_CALL(d128)(ad128,bd128);
	printf("%DDf = fmind128(%DDf,%DDf)\n", cd128, ad128, bd128);
}
