/* /opt/biarch/dfp/bin/gcc -g test_signbit.c -o signbit -ldfp  */
#include <stdio.h>
#include <stdint.h>

#define __STDC_WANT_DEC_FP__ 1
#include <math.h>

int main() {
	_Decimal32 d32;
	_Decimal64 d64;
	_Decimal128 d128;
	int sign;

	d32 = -19.54DF;
	d64 = -19.54DD;
	d128 = -19.54DL;

	sign = signbit(d32);
	printf("%d = signbit(%Hf)\n", sign, d32);
	sign = signbit(d64);
	printf("%d = signbit(%Df)\n", sign, d64);
	sign = signbit(d128);
	printf("%d = signbit(%DDf)\n", sign, d128);

	d32 = 19.54DF;
	d64 = 19.54DD;
	d128 = 19.54DL;

	sign = signbit(d32);
	printf("%d = signbit(%Hf)\n", sign, d32);
	sign = signbit(d64);
	printf("%d = signbit(%Df)\n", sign, d64);
	sign = signbit(d128);
	printf("%d = signbit(%DDf)\n", sign, d128);

}
