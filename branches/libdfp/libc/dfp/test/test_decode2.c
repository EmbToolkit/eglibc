/* /opt/biarch/dfp/bin/gcc -g test_signbit.c -o signbit -ldfp  */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifndef __STDC_WANT_DEC_FP
# define __STDC_WANT_DEC_FP__ 1
#endif
#include <math.h>
#include <float.h>
#include <fenv.h>

extern char * decoded32 (_Decimal32, char*);
extern char * decoded64 (_Decimal64, char*);
extern char * decoded128 (_Decimal128, char*);

int main() {
        _Decimal32 d32;
        _Decimal64 d64;
        _Decimal128 d128;
        char s32[32];
        char s64[64];
        char s128[128];
	double f64;

	d128 = 123.1215E4DL;
        printf("(_Decimal128)%DDfDL = [%s]\n", d128, decoded128(d128,s128));

	d128 = 123.12150E4DL;
        printf("(_Decimal128)%DDfDL = [%s]\n", d128, decoded128(d128,s128));

	d128 = 1231215.0DL;
        printf("(_Decimal128)%DDfDL = [%s]\n", d128, decoded128(d128,s128));

	f64 = 123.15315E7;
	printf("%.1lf\n", f64);
	printf("%.2lf\n", f64);

	f64 = 1231531.7;
	printf("%.1lf\n", f64);
	printf("%.2lf\n", f64);

	f64 = 0.12315315E-3;
	printf("%.1lf\n", f64);
	printf("%.2lf\n", f64);
	printf("%.8lf\n", f64);

	f64 = -0.0012315E-7;
	printf("%.2lf\n", f64);
	printf("%.8lf\n", f64);
	printf("%.9lf\n", f64);
	printf("%.10lf\n", f64);
	printf("%lf\n", f64);

}
