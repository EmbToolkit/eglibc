/* Test conversion from binary X to decimal X (note that many failures are
 * expected, and have to be reviewed on a case-by-case basis)
   Copyright (C) 2006 IBM Corporation.

   Author(s): Joe Kerian jkerian@us.ibm.com

   The Decimal Floating Point C Library is free software; you can
   redistribute it and/or modify it under the terms of the GNU Lesser
   General Public License version 2.1.

   The Decimal Floating Point C Library is distributed in the hope that
   it will be useful, but WITHOUT ANY WARRANTY; without even the implied
   warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
   the GNU Lesser General Public License version 2.1 for more details.

   You should have received a copy of the GNU Lesser General Public
   License version 2.1 along with the Decimal Floating Point C Library;
   if not, write to the Free Software Foundation, Inc., 59 Temple Place,
   Suite 330, Boston, MA 02111-1307 USA.

   Please see dfp/COPYING.txt for more information.  */

/* This mess of a test file created by Joseph Kerian 2006-12-13 */
/* -std=gnu99 */
//#define __STDC_WANT_DEC_FP__ 1
// At the moment... these tests can be compiled by moving or linking this file
// from the dfp/sysdeps/powerpc directory, and compiling it and all files in
// that directory with something like the following
// gcc -ldfp -std=gnu99 -D__STDC_WANT_DEC_FP__ *.c -o tests

//You can test individual areas by commenting in or out the following #defines
//Known errors:
// _Decimal64 -> double: due to truncation of D64 input... cases near DBL_MAX
//		seem to fail.
#define TEST_FROM_DECIMAL128
#define TEST_FROM_DECIMAL64
#define TEST_FROM_DECIMAL32
#define TEST_FROM_FLOAT
#define TEST_FROM_DOUBLE
#define TEST_FROM_LONG_DOUBLE

#define TEST_TO_DECIMAL128
#define TEST_TO_DECIMAL64
#define TEST_TO_DECIMAL32
#define TEST_TO_FLOAT
#define TEST_TO_DOUBLE
#define TEST_TO_LONG_DOUBLE


#include <stdio.h>
#include <errno.h>
#include <float.h>
#include <math.h>

#define PASTE(i,j)	PASTE2(i,j)
#define PASTE2(i,j)	i##j
#define STRINGIT(k)	STRINGIT2(k)
#define STRINGIT2(k)	#k

#define TEST(x)	\
do {\
	if(PASTE(x,SRC_SUFFIX) <= SRC_MAXSRC) {	\
		sample = PASTE(x,DST_SUFFIX);	\
		s = PASTE(x,SRC_SUFFIX);		\
		d = FUNCTION (s);		\
		printf (STRINGIT(DST_TYPE) "("STRINGIT(DST_PRINTF)")%s <- " \
			STRINGIT(SRC_TYPE)"("STRINGIT(SRC_PRINTF)") \n",d, \
			( PASTE(x,SRC_SUFFIX) > DST_MAXSRC )?"Overflow OK":" ",s); \
		if(d != sample) { \
			printf(STRINGIT(DST_TYPE)"("STRINGIT(DST_PRINTF)") Error: " \
				STRINGIT(DST_PRINTF)"("STRINGIT(DST_PRINTF)")\n",   \
				sample, d-sample, NEXT_AFTER(d, sample));	    \
			printf("---------\n");\
		}\
	} else		\
		printf ("Skipping: "#x" is too big for "STRINGIT(SRC_TYPE)"\n");	\
}while (0);
#define storage \

#define ALL_TESTS()		do  { \
	SRC_TYPE s;		\
	DST_TYPE d;		\
	DST_TYPE sample;	\
	\
	TEST(0.000000000000000000000000125);		\
	TEST(0.125);		\
	TEST(8388609.0);		\
	TEST(16777215.0);		\
	TEST(4503599627370496.0);			\
	TEST(4503599627370497.0);			\
	TEST(9223372036854775808.0);		\
	TEST(3.40282347e+38);		\
	TEST(3.40282348e+38);		\
	TEST(3.333333333333333333333333333333333333);		\
	TEST(-3.333333333333333333333333333333333333);		\
	TEST(256.0);		\
	TEST(9007199254740991.0);		\
	TEST(3.14159265358979323846264338327950288419716939937510);		\
	TEST(18446744073709551616.0);					\
	TEST(3.40282349e+38);						\
	TEST(1.7976931348623154e+308);					\
	TEST(1.7976931348623156e+308);					\
	TEST(1.7976931348623157e+308);	/* DBL_MAX */			\
	TEST(1.7976931348623158e+308);	/* LDBL_MAX */			\
	TEST(1.7976931348623159e+308);					\
}while (0)

extern _Decimal32	__extendsfsd(float);
extern _Decimal64	__extendsfdd(float);
extern _Decimal128	__extendsftd(float);

extern _Decimal32	__truncdfsd(double);
extern _Decimal64	__extenddfdd(double);
extern _Decimal128	__extenddftd	(double);

extern _Decimal32	__truncxfsd(long double);
extern _Decimal64	__truncxfdd(long double);
extern _Decimal128	__extendxftd	(long double);

extern float		__extendsdsf(_Decimal32);
extern float		__truncddsf(_Decimal64);
extern float		__trunctdsf(_Decimal128);

extern double		__extendsddf(_Decimal32);
extern double		__truncdddf(_Decimal64);
extern double		__trunctddf(_Decimal128);

extern long double	__extendsdxf(_Decimal32);
extern long double	__extendddxf(_Decimal64);
extern long double	__trunctdxf(_Decimal128);

int main (int argc, char *argv[])
{
#ifdef TEST_FROM_DECIMAL128
/*  FIRST: Test from _Decimal128 */
#define SRC_TYPE	_Decimal128
#define SRC_PRINTF	%.36DDe
#define SRC_SUFFIX	DL
#define SRC_MAXSRC	9.999999999999999999999999999999999E+6144DL
//To float
#ifdef TEST_TO_FLOAT
#define FUNCTION	__trunctdsf
#define DST_TYPE	float
#define DST_PRINTF	%.20e
#define DST_MAXSRC	3.402823466385288598117041834845169e+38DL
#define DST_SUFFIX	
#define NEXT_AFTER	nextafterf
ALL_TESTS();
#endif
//To double
#ifdef TEST_TO_DOUBLE
#define FUNCTION	__trunctddf
#define DST_TYPE	double
#define DST_PRINTF	%.20e
#define DST_MAXSRC	1.797693134862315708145274237317044e+308DL
#define DST_SUFFIX	
#define NEXT_AFTER	nextafter
ALL_TESTS();
#endif
//To long double
#ifdef TEST_TO_LONG_DOUBLE
#define FUNCTION	__trunctdxf
#define DST_TYPE	long double
#define DST_PRINTF	%.20Le
#define DST_MAXSRC	1.797693134862315807937289714053012e+308DL
#define DST_SUFFIX	
#define NEXT_AFTER	nextafterl
ALL_TESTS();
#endif
#endif

/*  Second: Test from _Decimal64 */
#ifdef TEST_FROM_DECIMAL64
#define SRC_TYPE	_Decimal64
#define SRC_PRINTF	%.21Df
#define SRC_SUFFIX	DD
#define SRC_MAXSRC	9.9999999999999999E+384DD
//To float
#ifdef TEST_TO_FLOAT
#define FUNCTION	__truncddsf
#define DST_TYPE	float
#define DST_PRINTF	%.20e
#define DST_MAXSRC	3.4028234663852886e+38DD
#define DST_SUFFIX	
#define NEXT_AFTER	nextafterf
ALL_TESTS();
#endif
//To double
#ifdef TEST_TO_DOUBLE
#define FUNCTION	__truncdddf
#define DST_TYPE	double
#define DST_PRINTF	%.20e
#define DST_MAXSRC	1.7976931348623157e+308DD
#define DST_SUFFIX	
#define NEXT_AFTER	nextafter
ALL_TESTS();
#endif
//To long double
#ifdef TEST_TO_LONG_DOUBLE
#define FUNCTION	__extendddxf
#define DST_TYPE	long double
#define DST_PRINTF	%.20Le
#define DST_MAXSRC	1.7976931348623158e+308DD
#define DST_SUFFIX	
#define NEXT_AFTER	nextafterl
ALL_TESTS();
#endif
#endif
/*  Third: Test from _Decimal32 */
#ifdef TEST_FROM_DECIMAL32
#define SRC_TYPE	_Decimal32
#define SRC_PRINTF	%.21Hf
#define SRC_SUFFIX	DD
#define SRC_MAXSRC	9.9999999999999999E+384DF
//To float
#ifdef TEST_TO_FLOAT
#define FUNCTION	__extendsdsf
#define DST_TYPE	float
#define DST_PRINTF	%.20e
#define DST_MAXSRC	3.4028234663852886e+38DF
#define DST_SUFFIX	
#define NEXT_AFTER	nextafterf
ALL_TESTS();
#endif
//To double
#ifdef TEST_TO_DOUBLE
#define FUNCTION	__extendsddf
#define DST_TYPE	double
#define DST_PRINTF	%.20e
#define DST_MAXSRC	1.7976931348623157e+308DF
#define DST_SUFFIX	
#define NEXT_AFTER	nextafter
ALL_TESTS();
#endif
//To long double
#ifdef TEST_TO_LONG_DOUBLE
#define FUNCTION	__extendsdxf
#define DST_TYPE	long double
#define DST_PRINTF	%.20Le
#define DST_MAXSRC	1.7976931348623158e+308DF
#define DST_SUFFIX	
#define NEXT_AFTER	nextafterl
ALL_TESTS();
#endif
#endif

#ifdef TEST_FROM_LONG_DOUBLE
/*  FOURTH: Test from long double */
#define SRC_TYPE	long double
#define SRC_PRINTF	%.36Le
#define SRC_SUFFIX	
#define SRC_MAXSRC	LDBL_MAX
//To _Decimal32
#ifdef TEST_TO_DECIMAL32
#define FUNCTION	__truncxfsd
#define DST_TYPE	_Decimal32
#define DST_PRINTF	%.9Hf
#define DST_MAXSRC	9.999999e+96
#define DST_SUFFIX	
#define NEXT_AFTER	nextafterd32
ALL_TESTS();
#endif
//To _Decimal64
#ifdef TEST_TO_DECIMAL64
#define FUNCTION	__truncxfdd
#define DST_TYPE	_Decimal64
#define DST_PRINTF	%.17Df
#define DST_MAXSRC	9.999999999999999e+384
#define DST_SUFFIX	
#define NEXT_AFTER	nextafterd64
ALL_TESTS();
#endif
//To _Decimal128
#ifdef TEST_TO_DECIMAL128
#define FUNCTION	__extendxftd
#define DST_TYPE	_Decimal128
#define DST_PRINTF	%.34DDf
#define DST_MAXSRC	9.999999999999999999999999999999999e+6144
#define DST_SUFFIX	
#define NEXT_AFTER	nextafterd128
ALL_TESTS();
#endif
#endif

#ifdef TEST_FROM_DOUBLE
/*  FIFTH: Test from double */
#define SRC_TYPE	double
#define SRC_PRINTF	%.36e
#define SRC_SUFFIX	
#define SRC_MAXSRC	DBL_MAX
//To _Decimal32
#ifdef TEST_TO_DECIMAL32
#define FUNCTION	__truncdfsd
#define DST_TYPE	_Decimal32
#define DST_PRINTF	%.9Hf
#define DST_MAXSRC	9.999999e+96
#define DST_SUFFIX	
#define NEXT_AFTER	nextafterd32
ALL_TESTS();
#endif
//To _Decimal64
#ifdef TEST_TO_DECIMAL64
#define FUNCTION	__extenddfdd
#define DST_TYPE	_Decimal64
#define DST_PRINTF	%.17Df
#define DST_MAXSRC	9.999999999999999e+384
#define DST_SUFFIX	
#define NEXT_AFTER	nextafterd64
ALL_TESTS();
#endif
//To _Decimal128
#ifdef TEST_TO_DECIMAL128
#define FUNCTION	__extenddftd
#define DST_TYPE	_Decimal128
#define DST_PRINTF	%.34DDf
#define DST_MAXSRC	9.999999999999999999999999999999999e+6144
#define DST_SUFFIX	
#define NEXT_AFTER	nextafterd128
ALL_TESTS();
#endif
#endif

#ifdef TEST_FROM_FLOAT
/*  SIXTH: Test from float */
#define SRC_TYPE	float
#define SRC_PRINTF	%.36e
#define SRC_SUFFIX	
#define SRC_MAXSRC	FLT_MAX
//To _Decimal32
#ifdef TEST_TO_DECIMAL32
#define FUNCTION	__extendsfsd
#define DST_TYPE	_Decimal32
#define DST_PRINTF	%.9Hf
#define DST_MAXSRC	9.999999e+96
#define DST_SUFFIX	
#define NEXT_AFTER	nextafterd32
ALL_TESTS();
#endif
//To _Decimal64
#ifdef TEST_TO_DECIMAL64
#define FUNCTION	__extendsfdd
#define DST_TYPE	_Decimal64
#define DST_PRINTF	%.17Df
#define DST_MAXSRC	9.999999999999999e+384
#define DST_SUFFIX	
#define NEXT_AFTER	nextafterd64
ALL_TESTS();
#endif
//To _Decimal128
#ifdef TEST_TO_DECIMAL128
#define FUNCTION	__extendsftd
#define DST_TYPE	_Decimal128
#define DST_PRINTF	%.34DDf
#define DST_MAXSRC	9.999999999999999999999999999999999e+6144
#define DST_SUFFIX	
#define NEXT_AFTER	nextafterd128
ALL_TESTS();
#endif
#endif
//printf("\nFLT_MAX: %.32a\nDBL_MAX: %.32a\nLDBL_MAX:%.32La\n",FLT_MAX,DBL_MAX,LDBL_MAX);
    return 0;
}
