#include <stdio.h>
#include <stdint.h>
#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif
#include <math.h>

#include "test_math.h"

/* These don't have prototypes because they aren't available to users.  */
extern int islessd32 (_Decimal32 x, _Decimal32 y);
extern int islessd64 (_Decimal64 x, _Decimal64 y);
extern int islessd128 (_Decimal128 x, _Decimal128 y);

extern int islessequald32 (_Decimal32 x, _Decimal32 y);
extern int islessequald64 (_Decimal64 x, _Decimal64 y);
extern int islessequald128 (_Decimal128 x, _Decimal128 y);

extern int isgreaterd32 (_Decimal32 x, _Decimal32 y);
extern int isgreaterd64 (_Decimal64 x, _Decimal64 y);
extern int isgreaterd128 (_Decimal128 x, _Decimal128 y);

extern int isgreaterequald32 (_Decimal32 x, _Decimal32 y);
extern int isgreaterequald64 (_Decimal64 x, _Decimal64 y);
extern int isgreaterequald128 (_Decimal128 x, _Decimal128 y);

extern int islessgreaterd32 (_Decimal32 x, _Decimal32 y);
extern int islessgreaterd64 (_Decimal64 x, _Decimal64 y);
extern int islessgreaterd128 (_Decimal128 x, _Decimal128 y);

int main() {

	//isgreater
	TEST_POLY_i_2_all(isgreater,0, -1.20,    1.0);
	TEST_i_2_all(isgreater,0, -1.20,    1.0);

	TEST_POLY_i_2_all(isgreater,1, 1.20,    -1.0);
	TEST_i_2_all(isgreater,1, 1.20,    -1.0);

	TEST_POLY_i_2_all(isgreater,1, 1.20,     1.0);
	TEST_i_2_all(isgreater,1, 1.20,     1.0);

	TEST_POLY_i_2_all(isgreater,1, 0.0020,   0.0019);
	TEST_i_2_all(isgreater,1, 0.0020,   0.0019);

	TEST_POLY_i_2_all(isgreater,0, 0.0020,   0.0020);
	TEST_i_2_all(isgreater,0, 0.0020,   0.0020);

	TEST_POLY_i_2_all(isgreater,0, DEC_NAN,  1.0019);
	TEST_i_2_all(isgreater,0, DEC_NAN,  1.0019);

	TEST_POLY_i_2_all(isgreater,0, DEC_NAN,  3.0019);
	TEST_i_2_all(isgreater,0, DEC_NAN,  3.0019);

	TEST_POLY_i_2_all(isgreater,0, 1.0019,   DEC_NAN);
	TEST_i_2_all(isgreater,0, 1.0019,   DEC_NAN);

	TEST_POLY_i_2_all(isgreater,1, DEC_INFINITY, DEC_MAX);
	TEST_i_2_all(isgreater,1, DEC_INFINITY, DEC_MAX);

	TEST_POLY_i_2_all(isgreater,0, DEC_INFINITY, DEC_INFINITY);
	TEST_i_2_all(isgreater,0, DEC_INFINITY, DEC_INFINITY);
	//isgreaterequal
	TEST_POLY_i_2_all(isgreaterequal,0, -1.20,    1.0);
	TEST_i_2_all(isgreaterequal,0, -1.20,    1.0);

	TEST_POLY_i_2_all(isgreaterequal,1, 1.20,    -1.0);
	TEST_i_2_all(isgreaterequal,1, 1.20,    -1.0);

	TEST_POLY_i_2_all(isgreaterequal,1, 1.20,     1.0);
	TEST_i_2_all(isgreaterequal,1, 1.20,     1.0);

	TEST_POLY_i_2_all(isgreaterequal,1, 0.0020,   0.0019);
	TEST_i_2_all(isgreaterequal,1, 0.0020,   0.0019);

	TEST_POLY_i_2_all(isgreaterequal,1, 0.0020,   0.0020);
	TEST_i_2_all(isgreaterequal,1, 0.0020,   0.0020);

	TEST_POLY_i_2_all(isgreaterequal,0, DEC_NAN,  1.0019);
	TEST_i_2_all(isgreaterequal,0, DEC_NAN,  1.0019);

	TEST_POLY_i_2_all(isgreaterequal,0, DEC_NAN,  3.0019);
	TEST_i_2_all(isgreaterequal,0, DEC_NAN,  3.0019);

	TEST_POLY_i_2_all(isgreaterequal,0, 1.0019,   DEC_NAN);
	TEST_i_2_all(isgreaterequal,0, 1.0019,   DEC_NAN);

	TEST_POLY_i_2_all(isgreaterequal,1, DEC_INFINITY, DEC_MAX);
	TEST_i_2_all(isgreaterequal,1, DEC_INFINITY, DEC_MAX);

	TEST_POLY_i_2_all(isgreaterequal,1, DEC_INFINITY, DEC_INFINITY);
	TEST_i_2_all(isgreaterequal,1, DEC_INFINITY, DEC_INFINITY);
	//isless
	TEST_POLY_i_2_all(isless,1, -1.20,    1.0);
	TEST_i_2_all(isless,1, -1.20,    1.0);

	TEST_POLY_i_2_all(isless,0, 1.20,    -1.0);
	TEST_i_2_all(isless,0, 1.20,    -1.0);

	TEST_POLY_i_2_all(isless,0, 1.20,     1.0);
	TEST_i_2_all(isless,0, 1.20,     1.0);

	TEST_POLY_i_2_all(isless,0, 0.0020,   0.0019);
	TEST_i_2_all(isless,0, 0.0020,   0.0019);

	TEST_POLY_i_2_all(isless,0, 0.0020,   0.0020);
	TEST_i_2_all(isless,0, 0.0020,   0.0020);

	TEST_POLY_i_2_all(isless,0, DEC_NAN,  1.0019);
	TEST_i_2_all(isless,0, DEC_NAN,  1.0019);

	TEST_POLY_i_2_all(isless,0, DEC_NAN,  3.0019);
	TEST_i_2_all(isless,0, DEC_NAN,  3.0019);
	
	TEST_POLY_i_2_all(isless,0, 1.0019,   DEC_NAN);
	TEST_i_2_all(isless,0, 1.0019,   DEC_NAN);

	TEST_POLY_i_2_all(isless,0, DEC_INFINITY, DEC_MAX);
	TEST_i_2_all(isless,0, DEC_INFINITY, DEC_MAX);

	TEST_POLY_i_2_all(isless,0, DEC_INFINITY, DEC_INFINITY);
	TEST_i_2_all(isless,0, DEC_INFINITY, DEC_INFINITY);
	//islessequal
	TEST_POLY_i_2_all(islessequal,1, -1.20,    1.0);
	TEST_i_2_all(islessequal,1, -1.20,    1.0);

	TEST_POLY_i_2_all(islessequal,0, 1.20,    -1.0);
	TEST_i_2_all(islessequal,0, 1.20,    -1.0);

	TEST_POLY_i_2_all(islessequal,0, 1.20,     1.0);
	TEST_i_2_all(islessequal,0, 1.20,     1.0);

	TEST_POLY_i_2_all(islessequal,0, 0.0020,   0.0019);
	TEST_i_2_all(islessequal,0, 0.0020,   0.0019);

	TEST_POLY_i_2_all(islessequal,1, 0.0020,   0.0020);
	TEST_i_2_all(islessequal,1, 0.0020,   0.0020);

	TEST_POLY_i_2_all(islessequal,0, DEC_NAN,  1.0019);
	TEST_i_2_all(islessequal,0, DEC_NAN,  1.0019);

	TEST_POLY_i_2_all(islessequal,0, DEC_NAN,  3.0019);
	TEST_i_2_all(islessequal,0, DEC_NAN,  3.0019);

	TEST_POLY_i_2_all(islessequal,0, 1.0019,   DEC_NAN);
	TEST_i_2_all(islessequal,0, 1.0019,   DEC_NAN);

	TEST_POLY_i_2_all(islessequal,0, DEC_INFINITY, DEC_MAX);
	TEST_i_2_all(islessequal,0, DEC_INFINITY, DEC_MAX);

	TEST_POLY_i_2_all(islessequal,1, DEC_INFINITY, DEC_INFINITY);
	TEST_i_2_all(islessequal,1, DEC_INFINITY, DEC_INFINITY);
	//isgreater
/*	TEST_POLY_i_2_all(isgreater,0, -1.20,    1.0);
	TEST_i_2_all(isgreater,0, -1.20,    1.0);

	TEST_POLY_i_2_all(isgreater,1, 1.20,    -1.0);
	TEST_i_2_all(isgreater,1, 1.20,    -1.0);

	TEST_POLY_i_2_all(isgreater,1, 1.20,     1.0);
	TEST_i_2_all(isgreater,1, 1.20,     1.0);

	TEST_POLY_i_2_all(isgreater,1, 0.0020,   0.0019);
	TEST_i_2_all(isgreater,1, 0.0020,   0.0019);

	TEST_POLY_i_2_all(isgreater,0, 0.0020,   0.0020);
	TEST_i_2_all(isgreater,0, 0.0020,   0.0020);

	TEST_POLY_i_2_all(isgreater,0, DEC_NAN,  1.0019);
	TEST_i_2_all(isgreater,0, DEC_NAN,  1.0019);

	TEST_POLY_i_2_all(isgreater,0, DEC_NAN,  3.0019);
	TEST_i_2_all(isgreater,0, DEC_NAN,  3.0019);

	TEST_POLY_i_2_all(isgreater,0, 1.0019,   DEC_NAN);
	TEST_i_2_all(isgreater,0, 1.0019,   DEC_NAN);

	TEST_POLY_i_2_all(isgreater,1, DEC_INFINITY, DEC_MAX);
	TEST_i_2_all(isgreater,1, DEC_INFINITY, DEC_MAX);

	TEST_POLY_i_2_all(isgreater,0, DEC_INFINITY, DEC_INFINITY);
	TEST_i_2_all(isgreater,0, DEC_INFINITY, DEC_INFINITY); */
	//islessgreater
	TEST_POLY_i_2_all(islessgreater,1, -1.20,    1.0);
	TEST_i_2_all(islessgreater,1, -1.20,    1.0);

	TEST_POLY_i_2_all(islessgreater,1, 1.20,    -1.0);
	TEST_i_2_all(islessgreater,1, 1.20,    -1.0);

	TEST_POLY_i_2_all(islessgreater,1, 1.20,     1.0);
	TEST_i_2_all(islessgreater,1, 1.20,     1.0);

	TEST_POLY_i_2_all(islessgreater,1, 0.0020,   0.0019);
	TEST_i_2_all(islessgreater,1, 0.0020,   0.0019);

	TEST_POLY_i_2_all(islessgreater,0, 0.0020,   0.0020);
	TEST_i_2_all(islessgreater,0, 0.0020,   0.0020);

	TEST_POLY_i_2_all(islessgreater,0, DEC_NAN,  1.0019);
	TEST_i_2_all(islessgreater,0, DEC_NAN,  1.0019);
	
	TEST_POLY_i_2_all(islessgreater,0, DEC_NAN,  3.0019);
	TEST_i_2_all(islessgreater,0, DEC_NAN,  3.0019);

	TEST_POLY_i_2_all(islessgreater,0, 1.0019,   DEC_NAN);
	TEST_i_2_all(islessgreater,0, 1.0019,   DEC_NAN);

	TEST_POLY_i_2_all(islessgreater,1, DEC_INFINITY, DEC_MAX);
	TEST_i_2_all(islessgreater,1, DEC_INFINITY, DEC_MAX);

	TEST_POLY_i_2_all(islessgreater,0, DEC_INFINITY, DEC_INFINITY);
	TEST_i_2_all(islessgreater,0, DEC_INFINITY, DEC_INFINITY);
}
