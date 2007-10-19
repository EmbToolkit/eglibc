#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif
#include <stdio.h>
#include <stdint.h>

#include "test_math.h"

//Functions that need testing in set1a
//_Decimal	nextafter	(_Decimal, _Decimal)
//_Decimal	nexttoward	(_Decimal, _Decimal128)
//_Decimal	scalbn		(_Decimal, int)
//_Decimal	scalbln		(_Decimal, long)
//_Decimal	logb		(_Decimal)
//_Decimal	ldexp		(_Decimal, int)
//int		ilogb		(_Decimal, _Decimal)
//_Bool		samequantum	(_Decimal, _Decimal)
//the various fe_set/get functions also need testing, but seperately

int main() {
//_Decimal	nextafter	(_Decimal, _Decimal)
	TEST_f(nextafterd32,-0.6999999DF,%Hf,-0.7DF,0.3DF);
	TEST_f(nextafterd32, 0.6999999DF,%Hf,0.7DF,0.3DF);
	TEST_f(nextafterd32, 6.999999DF,%Hf,7.0DF,3.0DF);
	TEST_f(nextafterd32, 69.99999DF,%Hf,70.0DF,3.0DF);
	/* Doing this with DEC_MIN actually pushes it toward DENORMAL, not
	 * -DEC_INFINITY.  */
	/* TEST_f_2_all(nextafter,-DEC_INFINITY,DEC_MIN,-DEC_INFINITY); */
	TEST_f_2_all(nextafter,-DEC_INFINITY,-DEC_MAX,-DEC_INFINITY);
	TEST_f_2_all(nextafter,DEC_INFINITY,DEC_MAX,DEC_INFINITY);

//_Decimal	nexttoward	(_Decimal, _Decimal128)
	TEST_f(nexttowardd32,-0.6999999DF,%Hf,-0.7DF,0.3DL);
	TEST_f(nexttowardd32,0.6999999DF,%Hf,0.7DF,0.3DL);
	TEST_f(nexttowardd32,6.999999DF,%Hf,7.0DF,3.0DL);
	TEST_f(nexttowardd32,69.99999DF,%Hf,70.0DF,3.0DL);
	/* Doing this with DEC_MIN actually pushes it toward DENORMAL, not
	 * -DEC_INFINITY.  */
	/* TEST_f_2_all(nexttoward,-DEC_INFINITY,DEC_MIN,-DEC_INFINITY);  */
	TEST_f_2_all(nexttoward,-DEC_INFINITY,-DEC_MAX,-DEC_INFINITY);
	TEST_f_2_all(nexttoward,DEC_INFINITY,DEC_MAX,DEC_INFINITY);

//_Decimal	scalbn		(_Decimal, int)
	TEST_f_f_i_all(scalbn,500.0,5.0,2);
	TEST_f_f_i_all(scalbn,100000.0,100.0,3);
	TEST_f_f_i_all(scalbn,0.003,3.0,-3);

//_Decimal	scalbln		(_Decimal, long)
	TEST_f_f_i_all(scalbln,500.0,5.0,2);
	TEST_f_f_i_all(scalbln,100000.0,100.0,3);
	TEST_f_f_i_all(scalbln,0.003,3.0,-3);

//_Decimal	logb		(_Decimal)
	TEST_f_f_all(logb, 3.0, 1024.0);
	TEST_f_f_all(logb, 4.0, 10024.0);
	TEST_f_f_all(logb,-3.0, 0.0023);
	TEST_f_f_all(logb, 5.0, 302234.0);

//int		ilogb		(_Decimal)
	TEST_i_f_all(ilogb, 3, 1024.0);
	TEST_i_f_all(ilogb, 4, 10024.0);
	TEST_i_f_all(ilogb,-3, 0.0023);
	TEST_i_f_all(ilogb, 5, 302234.0);

//_Decimal	ldexp		(_Decimal, int)
//
	TEST_f_f_i_all(ldexp, 0.0, 0.0, 4);
	TEST_f_f_i_all(ldexp, 80000.0, 0.8, 4);
	TEST_f_f_i_all(ldexp, -854375.0, -0.854375, 5);

//_Bool		samequantum	(_Decimal, _Decimal)
	TEST_i_2_all(samequantum, true, 0.3, 0.5);
	TEST_i_2_all(samequantum, false, 0.03, 0.5);
	TEST_i_2_all(samequantum, false, 0.3, 2.5);
	TEST_i_2_all(samequantum, false, 30000.2, 0.5);
	TEST_i_2_all(samequantum, false, DEC_NAN, 5.3);
	TEST_i_2_all(samequantum, false, 0.2, DEC_INFINITY);
	TEST_i_2_all(samequantum, true, DEC_NAN, DEC_NAN);
	TEST_i_2_all(samequantum, true, DEC_INFINITY, DEC_INFINITY);
}
