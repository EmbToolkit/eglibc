#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif
#include <stdio.h>
#include <stdint.h>

#include "test_math.h"

_Decimal32	tgammad32	(_Decimal32);
_Decimal64	tgammad64	(_Decimal64);
_Decimal128	tgammad128	(_Decimal128);
//Functions that need testing in set2 (does not include hyperbolic
// or arctrig functions)
//_Decimal	erf		(_Decimal)
//_Decimal	erfc		(_Decimal)
//_Decimal	lgamma		(_Decimal)
//_Decimal	tgamma		(_Decimal)
//_Decimal	remainder	(_Decimal, _Decimal)

int main() {
//_Decimal	erf		(_Decimal)
	TEST_f_1_all(erf, 0.0, 0.0);
	TEST_f_1_all(erf, -0.0, -0.0);
	TEST_f_1_all(erf, 1.0, DEC_INFINITY);
	TEST_f_1_all(erf, -1.0, -DEC_INFINITY);
	TEST_f_1_all(erf, DEC_NAN, DEC_NAN);
	TEST_f_1_all(erf, 0.140316204801333817393029446521623398, 0.125);
	TEST_f_1_all(erf, 0.711155633653515131598937834591410777, 0.75);
	TEST_f_1_all(erf, 0.922900128256458230136523481197281140, 1.25);
	TEST_f_1_all(erf, 0.995322265018952734162069256367252929, 2.0);
	TEST_f_1_all(erf, 0.999999994576599200434933994687765914, 4.125);
	TEST_f_1_all(erf, 1.0, 27.0);

//_Decimal	erfc		(_Decimal)
	TEST_f_1_all (erfc, 0.0, DEC_INFINITY);
	TEST_f_1_all (erfc, 2.0, -DEC_INFINITY);
	TEST_f_1_all (erfc, 1.0, 0.0);
	TEST_f_1_all (erfc, 1.0, -0.0);
	TEST_f_1_all (erfc, DEC_NAN, DEC_NAN);
	TEST_f_1_all (erfc, 0.859683795198666182606970553478376602, 0.125);
	TEST_f_1_all (erfc, 0.288844366346484868401062165408589223, 0.75);
	TEST_f_1_all (erfc, 0.0770998717435417698634765188027188596, 1.25);
	TEST_f_1_all (erfc, 0.00467773498104726583793074363274707139, 2.0);
	TEST_f_1_all (erfc, 0.542340079956506600531223408575531062e-8, 4.125);
//	TEST_f (erfcd128, 0.523704892378925568501606768284954709e-318DL, %Hf, 27.0DL);

//_Decimal	lgamma		(_Decimal)
	TEST_f_1_all (lgamma, DEC_INFINITY, DEC_INFINITY);
	TEST_f_1_all (lgamma, DEC_INFINITY, 0.0);
	TEST_f_1_all (lgamma, DEC_NAN, DEC_NAN);
       /* lgamma (x) == +inf plus divide by zero exception for integer x <=
	* 0. */
	TEST_f_1_all (lgamma, DEC_INFINITY, -3.0 );
	TEST_f_1_all (lgamma, DEC_INFINITY, -DEC_INFINITY);
/* Reminder: arguments are backwards on the below commented section
	TEST_f_f1 (lgamma, 1, 0, 1);
	TEST_f_f1 (lgamma, 3, M_LN2l, 1);
	TEST_f_f1 (lgamma, 0.5, M_LOG_SQRT_PIl, 1);
	TEST_f_f1 (lgamma, -0.5, M_LOG_2_SQRT_PIl, -1);
	TEST_f_f1 (lgamma, 0.7L, 0.260867246531666514385732417016759578L,1);
	TEST_f_f1 (lgamma, 1.2L,
		-0.853740900033158497197028392998854470e-1L, 1);
*/

//_Decimal	tgamma		(_Decimal)
TEST_f_1_all (tgamma, DEC_INFINITY, DEC_INFINITY);
TEST_f_1_all (tgamma, DEC_INFINITY, 0.0);
TEST_f_1_all (tgamma, -DEC_INFINITY, -0.0);
/* tgamma (x) == NaN plus invalid exception for integer x <= 0.  */
TEST_f_1_all (tgamma, DEC_NAN, -2.0);
TEST_f_1_all (tgamma, -DEC_INFINITY, -DEC_INFINITY);
TEST_f_1_all (tgamma, DEC_NAN, DEC_NAN);

//TEST_f_1_all (tgamma, 0.5, M_SQRT_PIl);
//TEST_f_1_all (tgamma, -0.5, -M_2_SQRT_PIl);
TEST_f_1_all (tgamma, 1.0, 1.0);
TEST_f_1_all (tgamma, 6.0, 4.0);
TEST_f_1_all (tgamma, 1.29805533264755778568117117915281162, 0.7);
TEST_f_1_all (tgamma, 0.918168742399760610640951655185830401, 1.2);

//_Decimal	remainder	(_Decimal, _Decimal)
TEST_f_2_all (remainder, DEC_NAN, 1.0, 0.0);
TEST_f_2_all (remainder, DEC_NAN, 1.0, -0.0);
TEST_f_2_all (remainder, DEC_NAN, DEC_INFINITY, 1.0);
TEST_f_2_all (remainder, DEC_NAN, -DEC_INFINITY, 1.0);
TEST_f_2_all (remainder, DEC_NAN, DEC_NAN, DEC_NAN);
TEST_f_2_all (remainder, -0.375, 1.625, 1.0);
TEST_f_2_all (remainder, 0.375, -1.625, 1.0);
TEST_f_2_all (remainder, -0.375, 1.625, -1.0);
TEST_f_2_all (remainder, 0.375, -1.625, -1.0);
TEST_f_2_all (remainder, 1.0, 5.0, 2.0);
TEST_f_2_all (remainder, -1.0, 3.0, 2.0);

}
