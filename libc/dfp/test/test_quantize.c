#include <stdio.h>
#include <stdint.h>
#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif
#include <math.h>

#ifndef FUNCTION
#define FUNCTION quantize
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

	ad32  = 123.456DF;
	bd32  = 0.12DF;
	cd32 = FUNCTION_CALL(d32)(ad32,bd32);
	printf("%Hf = quantized32(%Hf,%Hf)\n", cd32, ad32, bd32);

	ad32  = -1.95DF;
	bd32  = -190.55DF;
	cd32 = FUNCTION_CALL(d32)(ad32,bd32);
	printf("%Hf = quantized32(%Hf,%Hf)\n", cd32, ad32, bd32);

	ad64  = 123.456DD;
	bd64  = 0.12DD;
	cd64 = FUNCTION_CALL(d64)(ad64,bd64);
	printf("%Df = quantized64(%Df,%Df)\n", cd64, ad64, bd64);

	ad64  = -1.95DD;
	bd64 = -190.55DD;
	cd64 = FUNCTION_CALL(d64)(ad64,bd64);
	printf("%Df = quantized64(%Df,%Df)\n", cd64, ad64, bd64);

	ad128 = 123.456DL;
	bd128 = 0.12DL;
	cd128 = FUNCTION_CALL(d128)(ad128,bd128);
	printf("%DDf = quantized128(%DDf,%DDf)\n", cd128, ad128, bd128);

	ad128 = -1.95DL;
	bd128 = -190.55DL;
	cd128 = FUNCTION_CALL(d128)(ad128,bd128);
	printf("%DDf = quantized128(%DDf,%DDf)\n", cd128, ad128, bd128);


}
