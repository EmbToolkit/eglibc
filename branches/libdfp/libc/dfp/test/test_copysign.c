#include <stdio.h>
#include <stdint.h>
#define __STDC_WANT_DEC_FP__ 1
#include <math.h>

#ifndef FUNCTION
#define FUNCTION copysign
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

	ad32  = -1.20DF;
	bd32  = 0.12DF;
	cd32 = FUNCTION_CALL()(ad32,bd32);
	printf("%Hf = copysign(%Hf,%Hf)\n", cd32, ad32, bd32);

	ad32  = -1.20DF;
	bd32  = -0.12DF;
	cd32 = FUNCTION_CALL()(ad32,bd32);
	printf("%Hf = copysign(%Hf,%Hf)\n", cd32, ad32, bd32);

	ad64  = -1.20DD;
	bd64  = 0.12DD;
	cd64 = FUNCTION_CALL()(ad64,bd64);
	printf("%Df = copysign(%Df,%Df)\n", cd64, ad64, bd64);

	ad64  = -1.20DD;
	bd64 = -0.12DD;
	cd64 = FUNCTION_CALL()(ad64,bd64);
	printf("%Df = copysign(%Df,%Df)\n", cd64, ad64, bd64);

	ad128 = -1.20DL;
	bd128 = -0.12DL;
	cd128 = FUNCTION_CALL()(ad128,bd128);
	printf("%DDf = copysign(%DDf,%DDf)\n", cd128, ad128, bd128);

	ad128 = -1.20DL;
	bd128 = -0.12DL;
	cd128 = FUNCTION_CALL()(ad128,bd128);
	printf("%DDf = copysign(%DDf,%DDf)\n", cd128, ad128, bd128);


}
