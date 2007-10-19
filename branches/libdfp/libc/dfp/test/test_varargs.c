/* /opt/biarch/dfp/bin/gcc -g test_fabsd.c -o fabsd -ldfp  */
#include <stdio.h>
/*#include <stdint.h>

#define __STDC_WANT_DEC_FP__ 1
#include <math.h> */

int main() {
	_Decimal128 d128;
	d128 = -1.0DL;
	printf("1 %DDf\n", d128);
	printf("1a %DDf,%DDf,%DDf\n", d128,d128,d128);
}
