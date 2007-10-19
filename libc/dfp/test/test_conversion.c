#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif
#include <stdio.h>
#include <stdint.h>

#include "test_math.h"

extern char * decoded32 (_Decimal32, char*);
extern char * decoded64 (_Decimal64, char*);
extern char * decoded128 (_Decimal128, char*);

static float f = 2.f;
int main() {

        _Decimal32 d32;
	_Decimal64 d64;
	float f32;
	long double ld128;
	_Complex long double cld;
	double f64 = 0.0625;
	char s32[32];
	char s64[64];
	char s128[128];
	_Decimal128 c128;
	_Decimal64 c64;
	_Decimal32 c32;


	cld = 2.0l *  __extension__ 1i + 0.0625l;

	f64 = cld;
	c32 = f64;
	printf("[%s]d32 = f64[%lf] = (double)cld\n", decoded32(c32,s32),f64);

	printf("%Hf\n", c32);
	printf("%s\n", decoded32(c32,s32));

	f32 = cld;
	d32 = f32;
	printf("[%s]d32 = f32[%f] = (float)cld\n", decoded32(d32,s32),f32);

	c128 = cld;
	c32 = c128;
	printf("[%s]d32 = d128[%DDf] = (_Decimal128)cld\n", decoded32(c32,s32), c128);

	c64 = cld;
	c32 = c64;
	printf("[%s]d32 = d64[%Df] = (_Decimal64)cld\n", decoded32(c32,s32), c64);

	d32 = cld;
	printf("[%s]d32 = (_Decimal32)cld\n", decoded32(d32,s32));
	ld128 = cld;
	d32 = ld128;
	printf("[%s]d32 = f128[%llf] = (long double)cld\n", decoded32(d32,s32),ld128);

	d32 = f64;
	printf("[%s]d32 = f64[%lf]\n", decoded32(d32,s32),f64);

	d64 = cld;
	printf("[%s]d64 = f128[%llf] = (long double)cld\n", decoded64(d64,s64), ld128);

//	DISP_HEXD32(d32,0.0625DF);
//	DISP_HEXD64(d64,0.0625DD);
//	DISP_HEXD128(d128,0.0625DL);

//	DISP_HEXD32(d32,(_Decimal32)cld);
//	DISP_HEXD64(d64,(_Decimal64)cld);
        return -1;
}
