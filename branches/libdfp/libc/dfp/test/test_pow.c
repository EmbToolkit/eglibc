#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __STDC_WANT_DEC_FP__
#  define __STDC_WANT_DEC_FP__ 1
#endif
#include <fenv.h>
#include <math.h>

/* you can change this to 32,64,128 */
#define TEST_SIZE 32

#if TEST_SIZE == 128 

#define TYPE _Decimal128
#define SIZE(x) x##d128
#define DEC(x) x##DL
#define FMT "%DDf"

#elif TEST_SIZE == 64

#define TYPE _Decimal64
#define SIZE(x) x##d64
#define DEC(x) x##DD
#define FMT "%Df"

#elif TEST_SIZE == 32

#define TYPE _Decimal32
#define SIZE(x) x##d32
#define DEC(x) x##DF
#define FMT "%Hf"

#endif

#define PASTE(x,y) x##y
#define Stringify(x) Stringify2(x)
#define Stringify2(x) #x


int total_tests=0,
    total_fail=0,
    total_dec_fail=0,
    total_errno_fail=0;

void test(char *dec_str, TYPE dec_val, TYPE dec_expected, int dec_err,
	  char *str,	double val,	double expected, int err) {
  int fail, dec_fail, errno_fail;
  ++total_tests;
  fail = bcmp(&val, &expected, sizeof(double));
  dec_fail = bcmp(&dec_val, &dec_expected, sizeof(TYPE));
  errno_fail = dec_err!=err;

  total_fail += !!fail;
  total_dec_fail += !!dec_fail;
  total_errno_fail += !!errno_fail;

  printf("%s = %f  \t%s  errno=%d, \"%s\"\n",
    str,
    val,
    fail?"FAIL":"PASS",
    err, strerror(err));
  printf("%s = " FMT "  \t%s\n",
    dec_str,
    dec_val,
    dec_fail?"FAIL":"PASS");
  printf("  errno=%d \"%s\"  %s\n\n",
    dec_err,
    strerror(dec_err),
    errno_fail?"FAIL":"PASS");
  errno = 0;
}

#define TEST(op, op_dec, expected) { \
	TYPE DEC(result); \
	double result; \
	int err_dec, err; \
	errno = 0; \
	DEC(result) = op_dec; \
	err_dec = errno; \
	errno = 0; \
	result = op; \
	err = errno; \
	test(Stringify(op_dec), DEC(result), DEC(expected), err_dec, \
	     #op, result, expected, err); \
}

/* binary and unary testing macros */
#define TESTb(name, arg1, arg2, expected) TEST(name(arg1,arg2), SIZE(name)(DEC(arg1), DEC(arg2)), expected)
#define TESTu(name, arg, expected) TEST(name(arg), SIZE(name)(DEC(arg)), expected)


int main() {

	TYPE DEC(nan) = DEC_NAN;
	TYPE DEC(inf) = DEC_INFINITY;
	double nan = NAN;
	double inf = INFINITY;
	double nearinf = 1.5e308;
	TYPE DEC(nearinf) = DEC(1.0e8);

	TESTb(pow, -inf, -inf, 0.);
        TESTb(pow, -inf, -1.0, -0.);
        TESTb(pow, -inf, -1.5, 0.);
        TESTb(pow, -inf, -2.0, 0.);
        TESTb(pow, -inf, -0.0, 1.0);
        TESTb(pow, -inf, 0.0, 1.0);
        TESTb(pow, -inf, 2.0, inf);
        TESTb(pow, -inf, 1.5, inf);
        TESTb(pow, -inf, 1.0, -inf);
        TESTb(pow, -inf, inf, inf);
        TESTb(pow, -inf, nan, nan);

	TESTb(pow, -5.0, -inf, 0.);
        TESTb(pow, -5.0, -1.0, -0.2);
        TESTb(pow, -5.0, -1.5, nan);
        TESTb(pow, -5.0, -2.0, 0.04);
        TESTb(pow, -5.0, -0.0, 1.0);
        TESTb(pow, -5.0, 0.0, 1.0);
        TESTb(pow, -5.0, 2.0, 25.0);
        TESTb(pow, -5.0, 1.5, nan);
        TESTb(pow, -5.0, 1.0, -5.0);
        TESTb(pow, -5.0, inf, inf);
        TESTb(pow, -5.0, nan, nan);

	TESTb(pow, -2.0, -inf, 0.);
        TESTb(pow, -2.0, -1.0, -0.5);
        TESTb(pow, -2.0, -1.5, nan);
        TESTb(pow, -2.0, -2.0, 0.25);
        TESTb(pow, -2.0, -0.0, 1.0);
        TESTb(pow, -2.0, 0.0, 1.0);
        TESTb(pow, -2.0, 2.0, 4.0);
        TESTb(pow, -2.0, 1.0, -2.0);
        TESTb(pow, -2.0, 1.5, nan);
        TESTb(pow, -2.0, inf, inf);
        TESTb(pow, -2.0, nan, nan);

	TESTb(pow, -1.0, -inf, 1.0);
        TESTb(pow, -1.0, -1.0, -1.0);
        TESTb(pow, -1.0, -1.5, nan);
        TESTb(pow, -1.0, -2.0, 1.0);
        TESTb(pow, -1.0, -0.0, 1.0);
        TESTb(pow, -1.0, 0.0, 1.0);
        TESTb(pow, -1.0, 2.0, 1.0);
        TESTb(pow, -1.0, 1.0, -1.0);
        TESTb(pow, -1.0, 1.5, nan);
        TESTb(pow, -1.0, inf, 1.0);
        TESTb(pow, -1.0, nan, nan);

	TESTb(pow, -0.5, -inf, inf);
        TESTb(pow, -0.5, -1.0, -2.);
        TESTb(pow, -0.5, -1.5, nan);
        TESTb(pow, -0.5, -2.0, 4.0);
        TESTb(pow, -0.5, -0.0, 1.0);
        TESTb(pow, -0.5, 0.0, 1.0);
        TESTb(pow, -0.5, 2.0, 0.25);
        TESTb(pow, -0.5, 1.5, nan);
        TESTb(pow, -0.5, 1.0, -0.5);
        TESTb(pow, -0.5, inf, 0.);
        TESTb(pow, -0.5, nan, nan);

        TESTb(pow, -0.0, -inf, inf);
        TESTb(pow, -0.0, -1.0, -inf);
        TESTb(pow, -0.0, -1.5, inf);
        TESTb(pow, -0.0, -2.0, inf);
        TESTb(pow, -0.0, -0.0, 1.0);
        TESTb(pow, -0.0, 0.0, 1.0);
        TESTb(pow, -0.0, 2.0, 0.);
        TESTb(pow, -0.0, 1.0, -0.);
        TESTb(pow, -0.0, 1.5, 0.);
        TESTb(pow, -0.0, inf, 0.);
        TESTb(pow, -0.0, nan, nan);

	TESTb(pow, 0.0, -inf, inf);
        TESTb(pow, 0.0, -1.0, inf);
        TESTb(pow, 0.0, -1.5, inf);
        TESTb(pow, 0.0, -2.0, inf);
        TESTb(pow, 0.0, -0.0, 1.0);
        TESTb(pow, 0.0, 0.0, 1.0);
        TESTb(pow, 0.0, 2.0, 0.);
        TESTb(pow, 0.0, 1.5, 0.);
        TESTb(pow, 0.0, 1.0, 0.);
        TESTb(pow, 0.0, inf, 0.);
        TESTb(pow, 0.0, nan, nan);

	TESTb(pow, 0.5, -inf, inf);
        TESTb(pow, 0.5, -1.0, 2.);
        TESTb(pow, 0.5, -1.5, 2.828424);
        TESTb(pow, 0.5, -2.0, 4.);
        TESTb(pow, 0.5, -0.0, 1.0);
        TESTb(pow, 0.5, 0.0, 1.0);
        TESTb(pow, 0.5, 2.0, .25);
        TESTb(pow, 0.5, 1.5, 0.3535536);
        TESTb(pow, 0.5, 1.0, 0.5);
        TESTb(pow, 0.5, inf, 0.);
        TESTb(pow, 0.5, nan, nan);

	TESTb(pow, 1.0, -inf, 1.0);
        TESTb(pow, 1.0, -1.0, 1.0);
        TESTb(pow, 1.0, -1.5, 1.0);
        TESTb(pow, 1.0, -2.0, 1.0);
        TESTb(pow, 1.0, -0.0, 1.0);
        TESTb(pow, 1.0, 0.0, 1.0);
        TESTb(pow, 1.0, 2.0, 1.0);
        TESTb(pow, 1.0, 1.5, 1.0);
        TESTb(pow, 1.0, 1.0, 1.0);
        TESTb(pow, 1.0, inf, 1.0);
        TESTb(pow, 1.0, nan, 1.0);

	TESTb(pow, 2.0, -inf, 0.);
        TESTb(pow, 2.0, -1.0, 0.5);
        TESTb(pow, 2.0, -1.5, 0.3535536);
        TESTb(pow, 2.0, -2.0, 0.25);
        TESTb(pow, 2.0, -0.0, 1.0);
        TESTb(pow, 2.0, 0.0, 1.0);
        TESTb(pow, 2.0, 2.0, 4.0);
        TESTb(pow, 2.0, 1.5, 2.828424);
        TESTb(pow, 2.0, 1.0, 2.0);
        TESTb(pow, 2.0, inf, inf);
        TESTb(pow, 2.0, nan, nan);

	TESTb(pow, 5.0, -inf, 0.);
        TESTb(pow, 5.0, -1.0, .2);
        TESTb(pow, 5.0, -1.5, .08944272);
        TESTb(pow, 5.0, -2.0, 0.04);
        TESTb(pow, 5.0, -0.0, 1.0);
        TESTb(pow, 5.0, 0.0, 1.0);
        TESTb(pow, 5.0, 2.0, 25.0);
        TESTb(pow, 5.0, 1.5, 11.18035);
        TESTb(pow, 5.0, 1.0, 5.0);
        TESTb(pow, 5.0, inf, inf);
        TESTb(pow, 5.0, nan, nan);

//	TESTb(pow, inf, -inf, 0.);
        TESTb(pow, inf, -1.0, 0.);
//        TESTb(pow, inf, -1.5, 0.);
        TESTb(pow, inf, -2.0, 0.);
        TESTb(pow, inf, -0.0, 1.0);
        TESTb(pow, inf, 0.0, 1.0);
        TESTb(pow, inf, 2.0, inf);
//        TESTb(pow, inf, 1.5, inf);
        TESTb(pow, inf, 1.0, inf);
//        TESTb(pow, inf, inf, inf);
//        TESTb(pow, inf, nan, nan);

//	TESTb(pow, nan, -inf, nan);
        TESTb(pow, nan, -1.0, nan);
        TESTb(pow, nan, -2.0, nan);
        TESTb(pow, nan, -0.0, 1.0);
        TESTb(pow, nan, 0.0, 1.0);
        TESTb(pow, nan, 2.0, nan);
        TESTb(pow, nan, 1.0, nan);
//        TESTb(pow, nan, inf, nan);
//        TESTb(pow, nan, nan, nan);

  printf("%d tests, %d failed results, %d failed errno\n", total_tests,
	total_dec_fail, total_errno_fail);
}
