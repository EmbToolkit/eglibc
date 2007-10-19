/* /opt/biarch/dfp/bin/gcc -g test_fabsd.c -o fabsd -ldfp  */
#include <stdio.h>
#include <stdint.h>

#define __STDC_WANT_DEC_FP__ 1
#include <math.h>

int main() {
	_Decimal32 d32;
	_Decimal32 absd32;
	_Decimal64 d64;
	_Decimal64 absd64;
	_Decimal128 d128;
	_Decimal128 absd128;

	d32 = -19.54DF;
	absd32 = 0.0DF;
	d64 = -19.54DD;
	absd64 = 0.0DD;
	absd128 = 0.0DL;
	d128 = -19.54DL;

	absd32 = fabsd32(d32);

	absd64 = fabsd64(d64);

	absd128 = fabsd128(d128);

	printf("%Hf = fabsd32(%Hf)\n", absd32, d32);
	printf("%Df = fabsd64(%Df)\n", absd64, d64);
	printf("%DDf = fabsd128(%DDf)\n", absd128, d128);
}
