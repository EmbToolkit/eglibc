#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif
#include <stdio.h>
#include <stdint.h>

#include "fenv.h"
#include "test_math.h"

int main() {
	_Decimal128 d128,e128;

	fe_dec_setround(FE_DEC_TOWARDZERO);
	fesetround(FE_TOWARDZERO);
	//TEST_f_1_all (cbrt, 0.997389022060725270579075195353955217, 0.9921875);
	TEST_f_1_all (cbrt, 0.908560296416069829445605878163630251, 0.75);
	//if(0.9085602964160698294456058781636302DL != 0.908560296416069829445605878163630251DL)
	//	printf("fail d128\n");

	d128 = cbrtd128(0.75DL);
	e128 = 0.908560296416069829445605878163630251DL;
	printf("%DDf = cbrt(0.75DL)\n", d128);
	printf("%DDf = 0.908560296416069829445605878163630251DL\n", e128);
}

