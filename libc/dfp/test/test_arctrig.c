#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif
#include <stdio.h>
#include <stdint.h>
#include <float.h>
#include "test_math.h"

//Functions that need testing:
//_Decimal	acos		(_Decimal)
//_Decimal	asin		(_Decimal)
//the various fe_set/get functions also need testing, but seperately

int main() {
//_Decimal	asin		(_Decimal)
	TEST_f_1_all(acos, DEC_NAN,  DEC_INFINITY);
	TEST_f_1_all(acos, DEC_NAN, -DEC_INFINITY);
	TEST_f_1_all(acos, DEC_NAN,  DEC_NAN);
	TEST_f_1_all(acos, DEC_NAN,  1.125);
	TEST_f_1_all(acos, DEC_NAN, -1.125);
//	TEST_f_f_all(acos, M_PI_2,   0.0);
//	TEST_f_f_all(acos, M_PI_2,  -0.0);
	TEST_f_f_all(acos, 0.0,      1.0);
//	TEST_f_f_all(acos, M_PI,    -1.0);
//	TEST_f_f_all(acos, M_PI/3.0, 0.5);
	TEST_f_f_all(acos, 0.722734247813415611178377352641333362, 0.75);
	TEST_f_f_all(acos, 1.57079632679489659923132169163975144, 2E-17);
	TEST_f_f_all(acos, 1.50825556499840522843072005474337068, 0.0625);

//_Decimal	asin		(_Decimal)
	TEST_f_1_all(asin, DEC_NAN,  DEC_INFINITY);
	TEST_f_1_all(asin, DEC_NAN, -DEC_INFINITY);
	TEST_f_1_all(asin, DEC_NAN,  DEC_NAN);
	TEST_f_1_all(asin, DEC_NAN,  1.125);
	TEST_f_1_all(asin, DEC_NAN, -1.125);
	TEST_f_f_all(asin, 0.0,      0.0);
	TEST_f_f_all(asin, -0.0,    -0.0);
//	TEST_f_f_all(asin, M_PI_6,   0.5);
//	TEST_f_f_all(asin, -M_PI_6, -0.5);
	TEST_f_f_all(asin, M_PI_2,   1.0);
//	TEST_f_f_all(asin, -M_PI_2, -1.0);
	TEST_f_f_all(asin, 0.848062078981481008052944338998418080, 0.75);

	if(isnan((_Decimal32)DEC_NAN))    printf("1 ");
	else                  printf("0 ");
	if(isnand32(DEC_NAN)) printf("1\n");
	else                  printf("0\n");
}
