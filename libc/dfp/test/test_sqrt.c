/* /opt/biarch/dfp/bin/gcc -g test_sqrtd.c -o sqrtd -ldfp  */
#include <stdio.h>
#include <stdint.h>

#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif

#include <math.h>

int main() {
	_Decimal32 d32;
	_Decimal32 s32;
	_Decimal64 d64;
	_Decimal64 s64;
	_Decimal128 d128;
	_Decimal128 s128;

	d32 = 144.0DF;
	s32 = 0.0DF;

	d64 = 144.0DD;
	s64 = 0.0DD;
	d128 = 144.0DL;
	s128 = 0.0DL;

	s32 = sqrtd32(d32);

	s64 = sqrtd64(d64);

	s128 = sqrtd128(d128);

	printf("%Hf = sqrtd32(%Hf)\n", s32, d32);
	printf("%Df = sqrtd64(%Df)\n", s64, d64);
	printf("%DDf = sqrtd128(%DDf)\n", s128, d128);
}
