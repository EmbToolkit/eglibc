#include <stdio.h>
#include <stdint.h>
#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif
#include <math.h>

#ifndef FUNCTION
#define FUNCTION fdim
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

	ad32  = 10.0DF;
	bd32  = 9.0DF;
	cd32 = FUNCTION_CALL(d32)(ad32,bd32);
	printf("%Hf = fdimd32(%Hf,%Hf)\n", cd32, ad32, bd32);

	ad32  = 10.0DF;
	bd32  = 12.0DF;
	cd32 = FUNCTION_CALL(d32)(ad32,bd32);
	printf("%Hf = fdimd32(%Hf,%Hf)\n", cd32, ad32, bd32);

	ad32  = -10.0DF;
	bd32  = -12.0DF;
	cd32 = FUNCTION_CALL(d32)(ad32,bd32);
	printf("%Hf = fdimd32(%Hf,%Hf)\n", cd32, ad32, bd32);

	ad32  = -10.0DF;
	bd32  = -8.0DF;
	cd32 = FUNCTION_CALL(d32)(ad32,bd32);
	printf("%Hf = fdimd32(%Hf,%Hf)\n", cd32, ad32, bd32);

	ad32  = -0.012DF;
	bd32  = 0.010DF;
	cd32 = FUNCTION_CALL(d32)(ad32,bd32);
	printf("%Hf = fdimd32(%Hf,%Hf)\n", cd32, ad32, bd32);

	ad64  = 10.0DD;
	bd64  = 9.0DD;
	cd64 = FUNCTION_CALL(d64)(ad64,bd64);
	printf("%Df = fdimd64(%Df,%Df)\n", cd64, ad64, bd64);

	ad64  = 10.0DD;
	bd64 =  12.0DD;
	cd64 = FUNCTION_CALL(d64)(ad64,bd64);
	printf("%Df = fdimd64(%Df,%Df)\n", cd64, ad64, bd64);

	ad128 = 10.0DL;
	bd128 = 9.0DL;
	cd128 = FUNCTION_CALL(d128)(ad128,bd128);
	printf("%DDf = fdimd128(%DDf,%DDf)\n", cd128, ad128, bd128);

	ad128 = 10.0DL;
	bd128 = 12.0DL;
	cd128 = FUNCTION_CALL(d128)(ad128,bd128);
	printf("%DDf = fdimd128(%DDf,%DDf)\n", cd128, ad128, bd128);
}
