#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif
#include <math.h>
#include <stdint.h>
#include <fenv.h>
#include <stdio.h>

#define PRINT_ARRAY(size,array) \
for(i=0; i<size; i++)	\
	printf("%x ",array[i]);\
printf("\n");

int main() {
	int i;
	union {
		_Decimal32 dec;
		uint8_t	bytes[4];
	} d32;
	union {
		_Decimal64 dec;
		uint8_t	bytes[8];
	} d64;
	union {
		_Decimal128 dec;
		uint8_t	bytes[16];
	} d128;

	d32.dec = 0.0DF;
	d64.dec = 0.0DD;
	d128.dec= 0.0DL;
	PRINT_ARRAY(4,d32.bytes);
	PRINT_ARRAY(8,d64.bytes);
	PRINT_ARRAY(16,d128.bytes);
	d32.dec = 0.000000DF;
	d64.dec = 0.000000DD;
	d128.dec= 0.000000DL;
	PRINT_ARRAY(4,d32.bytes);
	PRINT_ARRAY(8,d64.bytes);
	PRINT_ARRAY(16,d128.bytes);
}

