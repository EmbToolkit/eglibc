#define __STDC_WANT_DEC_FP__ 1
#include <stdio.h>
#include <stdint.h>

#include "test_math.h"

 _Decimal32	exp2d32	(_Decimal32);
 _Decimal32	log2d32	(_Decimal32);
 _Decimal64	exp2d64	(_Decimal64);
 _Decimal64	log2d64	(_Decimal64);
 _Decimal128	exp2d128	(_Decimal128);
 _Decimal128	log2d128	(_Decimal128);
 _Decimal32	remquod32 (_Decimal32,_Decimal32,int*);
 _Decimal64	remquod64 (_Decimal64,_Decimal64,int*);
 _Decimal128	remquod128 (_Decimal128,_Decimal128,int*);
extern _Decimal32	fmad32 (_Decimal32,_Decimal32,_Decimal32);
extern _Decimal64	fmad64 (_Decimal64,_Decimal64,_Decimal64);
extern _Decimal128	fmad128 (_Decimal128,_Decimal128,_Decimal128);
//Functions that need testing in set2 (does not include hyperbolic
// or arctrig functions)
// _Decimal	exp2	(_Decimal)
// _Decimal	expm1	(_Decimal)
// _Decimal	log1p	(_Decimal)
// _Decimal	log2	(_Decimal)
// _Decimal	remquo	(_Decimal, _Decimal, *int)
// _Decimal	hypot	(_Decimal, _Decimal)
// _Decimal	fmod	(_Decimal, _Decimal)
// _Decimal	cbrt	(_Decimal)
// _Decimal	fma	(_Decimal, _Decimal, _Decimal)

int main() {
// _Decimal	exp2	(_Decimal)
	TEST_f_1_all (exp2, 1.0, 0.0);
	TEST_f_1_all (exp2, 1.0, -0.0);
	TEST_f_1_all (exp2, DEC_INFINITY, DEC_INFINITY);
	TEST_f_1_all (exp2, 0.0, -DEC_INFINITY);
	TEST_f_1_all (exp2, DEC_NAN, DEC_NAN);

	TEST_f_1_all (exp2, 1024.0, 10.0);
	TEST_f_1_all (exp2, 0.5, -1.0);
	TEST_f_1_all (exp2, DEC_INFINITY, 1.0E6);
	TEST_f_1_all (exp2, 0.0, -1.0E6);
	TEST_f_1_all (exp2, 1.68179283050742908606225095246642979, 0.75);

// _Decimal	expm1	(_Decimal)
	TEST_f_1_all (expm1, 0.0, 0.0);
	TEST_f_1_all (expm1, -0.0, -0.0);
	TEST_f_1_all (expm1, DEC_INFINITY, DEC_INFINITY);
	TEST_f_1_all (expm1, -1.0, -DEC_INFINITY);
	TEST_f_1_all (expm1, DEC_NAN, DEC_NAN);
//	TEST_f_1_all (expm1, M_Edl - 1.0DL, 1.0);
	TEST_f_1_all (expm1, 1.11700001661267466854536981983709561, 0.75);

// _Decimal	log1p	(_Decimal)
	TEST_f_1_all (log1p, 0.0, 0.0);
	TEST_f_1_all (log1p, -0.0, -0.0);
	TEST_f_1_all (log1p, -DEC_INFINITY, -1.0);
	TEST_f_1_all (log1p, DEC_NAN, -2.0);
	TEST_f_1_all (log1p, DEC_INFINITY, DEC_INFINITY);
	TEST_f_1_all (log1p, DEC_NAN, DEC_NAN);
//	TEST_f_1_all (log1p, 1, M_El - 1.0);
	TEST_f_1_all (log1p, -0.287682072451780927439219005993827432, -0.25);
	TEST_f_1_all (log1p, -2.07944154167983592825169636437452970, -0.875);

// _Decimal	log2	(_Decimal)
	TEST_f_1_all (log2, -DEC_INFINITY, 0.0);
	TEST_f_1_all (log2, -0.0, -DEC_INFINITY);
	TEST_f_1_all (log2, 0.0, 1.0);
	TEST_f_1_all (log2, DEC_NAN, -1.0);
	TEST_f_1_all (log2, DEC_INFINITY, DEC_INFINITY);
	TEST_f_1_all (log2, DEC_NAN, DEC_NAN);
//	TEST_f_1_all (log2, M_El, M_LOG2El);
	TEST_f_1_all (log2, 1.0, 2.0);
	TEST_f_1_all (log2, 4.0, 16.0);
	TEST_f_1_all (log2, 8.0, 256.0);
	TEST_f_1_all (log2, -0.415037499278843818546261056052183492, 0.75);
/*  Removed from the latest TR
// _Decimal	remquo	(_Decimal, _Decimal, *int)
// remquo needs it's own define to hanlde the odd int pointer
#define TEST_remquo_noquo(res,x,y)			\
	do { int quo;					\
		TEST_f(remquod32,res##DF,%Hf,x##DF,y##DF,&quo);	\
		TEST_f(remquod64,res##DD,%Df,x##DD,y##DD,&quo);	\
		TEST_f(remquod128,res##DL,%DDf,x##DL,y##DL,&quo);	\
	} while(0)

#define TEST_remquo(res,x,y,i)			\
	do { int quo;					\
		TEST_f(remquod32,res##DF,%Hf,x##DF,y##DF,&quo);	\
		if(i==quo) printf(" Success: quo value returned was: "#i"\n"); \
		else printf(" Failure: quo returned was %d,"\
				"was supposed to be "#i"\n", quo); \
		TEST_f(remquod64,res##DD,%Df,x##DD,y##DD,&quo);	\
		if(i==quo) printf(" Success: quo value returned was: "#i"\n"); \
		else printf(" Failure: quo returned was %d,"\
				"was supposed to be "#i"\n", quo); \
		TEST_f(remquod128,res##DL,%DDf,x##DL,y##DL,&quo);	\
		if(i==quo) printf(" Success: quo value returned was: "#i"\n"); \
		else printf(" Failure: quo returned was %d,"\
				"was supposed to be "#i"\n", quo); \
	} while(0)

	TEST_remquo_noquo (DEC_NAN, 1.0, 0.0);
	TEST_remquo_noquo (DEC_NAN, 1.0, -0.0);
	TEST_remquo_noquo (DEC_NAN, DEC_INFINITY, 1.0);
	TEST_remquo_noquo (DEC_NAN, -DEC_INFINITY, 1.0);
	TEST_remquo_noquo (DEC_NAN, DEC_NAN, DEC_NAN);
	TEST_remquo (-0.375, 1.625, 1.0, 2);
	TEST_remquo (0.375, -1.625, 1.0, -2);
	TEST_remquo (-0.375, 1.625, -1.0, -2);
	TEST_remquo (0.375, -1.625, -1.0, 2);
	TEST_remquo (1.0, 5.0, 2.0, 2);
	TEST_remquo (-1.0, 3.0, 2.0, 2);
*/
// _Decimal	hypot	(_Decimal, _Decimal)
	TEST_f_2_all (hypot, DEC_INFINITY, DEC_INFINITY, 1.0);
	TEST_f_2_all (hypot, -DEC_INFINITY, -DEC_INFINITY, 1.0);
	TEST_f_2_all (hypot, DEC_INFINITY, DEC_NAN, DEC_INFINITY);
	TEST_f_2_all (hypot, -DEC_INFINITY, -DEC_INFINITY, DEC_NAN);
	TEST_f_2_all (hypot, DEC_INFINITY, DEC_NAN, DEC_INFINITY);
	TEST_f_2_all (hypot, -DEC_INFINITY, DEC_NAN, -DEC_INFINITY);
	TEST_f_2_all (hypot, DEC_NAN, DEC_NAN, DEC_NAN);
	TEST_f_2_all (hypot, 12.419742348374220601176836866763271, 0.7, 12.4);
	TEST_f_2_all (hypot, 12.419742348374220601176836866763271, -0.7, 12.4);
	TEST_f_2_all (hypot, 12.419742348374220601176836866763271, 0.7, -12.4);
	TEST_f_2_all (hypot, 12.419742348374220601176836866763271, -0.7, -12.4);
	TEST_f_2_all (hypot, 12.419742348374220601176836866763271, 12.4, 0.7);
	TEST_f_2_all (hypot, 12.419742348374220601176836866763271, -12.4, 0.7);
	TEST_f_2_all (hypot, 12.419742348374220601176836866763271, 12.4, -0.7);
	TEST_f_2_all (hypot, 12.419742348374220601176836866763271, -12.4, -0.7);
	TEST_f_2_all (hypot, 0.75, 0.75, 0.0);  /*  hypot (x,0) == fabs (x)  */
	TEST_f_2_all (hypot, 0.75, -0.75, 0.0);
	TEST_f_2_all (hypot, 5.7e7, -5.7e7, 0.0);
	TEST_f_2_all (hypot, 1.45773797371132511771853821938639577, 0.75, 1.25);

// _Decimal	fmod	(_Decimal, _Decimal)
  /* fmod (+0, y) == +0 for y != 0.  */
	TEST_f_2_all (fmod, 0.0, 0.0, 3.0);
	/* fmod (-0, y) == -0 for y != 0.  */
	TEST_f_2_all (fmod, -0.0, -0.0, 3.0);
	/* fmod (+inf, y) == NaN plus invalid exception.  */
	TEST_f_2_all (fmod, DEC_NAN, DEC_INFINITY, 3.0);
	/* fmod (-inf, y) == NaN + invalid */
	TEST_f_2_all (fmod, DEC_NAN, -DEC_INFINITY, 3.0);
	/* fmod (x, +0) == NaN + invalid */
	TEST_f_2_all (fmod, DEC_NAN, 3.0, 0.0);
	/* fmod (x, -0) == NaN+invalid  */
	TEST_f_2_all (fmod, DEC_NAN, 3.0, -0.0);
	/* fmod (x, +inf) == x for x not infinite.  */
	TEST_f_2_all (fmod, 3.0, 3.0, DEC_INFINITY);
	/* fmod (x, -inf) == x for x not infinite.  */
	TEST_f_2_all (fmod, 3.0, 3.0, -DEC_INFINITY);
	TEST_f_2_all (fmod, DEC_NAN, DEC_NAN, DEC_NAN);
	/* Special test case */
	TEST_f_2_all (fmod, 1.0, 1e50, 3.0);

	TEST_f_2_all (fmod, 2.0, 6.5, 2.25);
	TEST_f_2_all (fmod, -2.0, -6.5, 2.25);
	TEST_f_2_all (fmod, 2.0, 6.5, -2.25);
	TEST_f_2_all (fmod, -2.0, -6.5, -2.25);

// _Decimal	cbrt	(_Decimal)
	TEST_f_1_all (cbrt, 0.0, 0.0);
	TEST_f_1_all (cbrt, -0.0, -0.0);
	TEST_f_1_all (cbrt, DEC_INFINITY, DEC_INFINITY);
	TEST_f_1_all (cbrt, -DEC_INFINITY, -DEC_INFINITY);
	TEST_f_1_all (cbrt, DEC_NAN, DEC_NAN);
	TEST_f_1_all (cbrt, -0.1, -0.001);
	TEST_f_1_all (cbrt, 2.0, 8.0);
	TEST_f_1_all (cbrt, -3.0, -27.0);
	TEST_f_1_all (cbrt, 0.997389022060725270579075195353955217, 0.9921875);
	TEST_f_1_all (cbrt, 0.908560296416069829445605878163630251, 0.75);

// _Decimal	fma	(_Decimal, _Decimal, _Decimal)

	TEST_f_3_all (fma, 5.0, 1.0, 2.0, 3.0);
	TEST_f_3_all (fma, DEC_NAN, DEC_NAN, 2.0, 3.0);
	TEST_f_3_all (fma, DEC_NAN, 1.0, DEC_NAN, 3.0);
	TEST_f_3_all (fma, DEC_NAN, 1.0, 2.0, DEC_NAN);
	TEST_f_3_all (fma, DEC_NAN, DEC_INFINITY, 0.0, DEC_NAN);
	TEST_f_3_all (fma, DEC_NAN, -DEC_INFINITY, 0.0, DEC_NAN);
	TEST_f_3_all (fma, DEC_NAN, 0.0, DEC_INFINITY, DEC_NAN);
	TEST_f_3_all (fma, DEC_NAN, 0.0, -DEC_INFINITY, DEC_NAN);
	TEST_f_3_all (fma, DEC_NAN, DEC_INFINITY, 0.0, 1.0);
	TEST_f_3_all (fma, DEC_NAN, -DEC_INFINITY, 0.0, 1.0);
	TEST_f_3_all (fma, DEC_NAN, 0.0, DEC_INFINITY, 1.0);
	TEST_f_3_all (fma, DEC_NAN, 0.0, -DEC_INFINITY, 1.0);

	TEST_f_3_all (fma, DEC_NAN, DEC_INFINITY, DEC_INFINITY,-DEC_INFINITY);
	TEST_f_3_all (fma, DEC_NAN,-DEC_INFINITY, DEC_INFINITY, DEC_INFINITY);
	TEST_f_3_all (fma, DEC_NAN, DEC_INFINITY,-DEC_INFINITY, DEC_INFINITY);
	TEST_f_3_all (fma, DEC_NAN,-DEC_INFINITY,-DEC_INFINITY,-DEC_INFINITY);
	TEST_f_3_all (fma, 1.0, 1.25, 0.75, 0.0625);

// _Decimal frexp	(_Decimal, int*);
	TEST_fI (frexpd32, %Hf, 0.128DF, 23, 128E20DF);
	TEST_fI (frexpd64, %Df, 0.128DD, 23, 128E20DD);
	TEST_fI (frexpd128, %DDf, 0.128DL, 23, 128E20DL);
	TEST_fI (frexpd32, %Hf, 0.128DF, 2, 12.8DF);
	TEST_fI (frexpd64, %Df, 0.128DD, 2, 12.8DD);
	TEST_fI (frexpd128, %DDf, 0.128DL, 2, 12.8DL);
	TEST_fI (frexpd32, %Hf, -0.2734DF, 2, -27.34DF);
	TEST_fI (frexpd64, %Df, -0.2734DD, 2, -27.34DD);
	TEST_fI (frexpd128, %DDf, -0.2734DL, 2, -27.34DL);
	TEST_fI (frexpd32, %Hf, -0.2734DF, 0, -0.2734DF);
	TEST_fI (frexpd64, %Df, -0.2734DD, 0, -0.2734DD);
	TEST_fI (frexpd128, %DDf, -0.2734DL, 0, -0.2734DL);
	TEST_fI (frexpd32, %Hf, -0.2734DF, -1, -0.02734DF);
	TEST_fI (frexpd64, %Df, -0.2734DD, -1, -0.02734DD);
	TEST_fI (frexpd128, %DDf, -0.2734DL, -1, -0.02734DL);
	TEST_fI (frexpd32, %Hf, 0.1DF, 0, 0.1000DF);
	TEST_fI (frexpd64, %Df, 0.1DD, 0, 0.1000DD);
	TEST_fI (frexpd128, %DDf, 0.1DL, 0, 0.1000DL);
	TEST_fI (frexpd32, %Hf, 0.1DF, -1, 0.010DF);
	TEST_fI (frexpd64, %Df, 0.1DD, -1, 0.0100DD);
	TEST_fI (frexpd128, %DDf, 0.1DL, -1, 0.01000DL);
	TEST_fI (frexpd32, %Hf, 0.256DF, 3, 256.0DF);
	TEST_fI (frexpd64, %Df, 0.256DD, 3, 256.0DD);
	TEST_fI (frexpd128, %DDf, 0.256DL, 3, 256.0DL);
}
