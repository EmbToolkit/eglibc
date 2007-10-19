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


	TESTu(atan, -inf, result);
	TESTu(atan, -0.5, result);
	TESTu(atan, 0.0, 0.0);
	TESTu(atan, 1.0, result);
	TESTu(atan, 2.0, result);
	TESTu(atan, inf, result);
	TESTu(atan, nan, nan);

	TESTu(sinh, 0.0, 0.0);
	TESTu(sinh, 1.0, result);
	TESTu(sinh, -1.0, result);
	TESTu(sinh, inf, inf);
	TESTu(sinh, -inf, -inf);
	TESTu(sinh, nearinf, inf);
	TESTu(sinh, -nearinf, -inf);
	TESTu(sinh, nan, nan);

        TESTu(cosh, 0.0, 1.);
        TESTu(cosh, 1.0, result);
        TESTu(cosh, -1.0, result);
        TESTu(cosh, inf, inf);
        TESTu(cosh, -inf, inf);
        TESTu(cosh, nearinf, inf);
        TESTu(cosh, -nearinf, inf);
        TESTu(cosh, nan, nan);

	TESTu(exp, 0.0, 1.);
	TESTu(exp, nearinf, inf);
	TESTu(exp, -nearinf, 0.);
	TESTu(exp, inf, inf);
	TESTu(exp, -inf, 0.);
	TESTu(exp, nan, nan);
	TESTu(exp, 1.0, result);

	TESTu(log10, 0.0, -inf);
	TESTu(log10, -1.0, nan);
	TESTu(log10, inf, inf);  //decNumber hangs on this one
	TESTu(log10, -inf, nan);
	TESTu(log10, 10.0, 1.);

	TESTu(log, 0.0, -inf);
	TESTu(log, -1.0, nan);
	TESTu(log, inf, inf);
	TESTu(log, -inf, nan);
	{
	double e = exp(1.0);
	TYPE DEC(e) = SIZE(exp)(DEC(1.));
	TESTu(log, e, 1.);
	}

        TESTb(pow, nan, 0.0, 1.);
        TESTb(pow, nan, 1.0, nan);
        TESTb(pow, 0.0, 0.0, 1.);
        TESTb(pow, -0.0, -1.0, -inf);

        TESTb(pow, 0.0, -1.0, inf);
        TESTb(pow, -2.0, 1.1, nan);
        TESTb(pow, 2.0, nearinf, inf);
        TESTb(pow, 2.0, -nearinf, 0.);

        TESTu(sqrt, -inf, nan);
        TESTu(sqrt, -2.0, nan);
        TESTu(sqrt, 0.0, result);
        TESTu(sqrt, inf, inf);
        TESTu(sqrt, nan, nan);


	TESTu(acosh, -inf, nan);
	TESTu(acosh, -1.5, nan);
	TESTu(acosh, -1.0, nan);
	TESTu(acosh, -0.5, nan);
	TESTu(acosh, 0.0, nan);
	TESTu(acosh, 0.5, nan);
	TESTu(acosh, 1.0, result);
	TESTu(acosh, 1.5, result);
	TESTu(acosh, inf, inf);
	TESTu(acosh, nan, nan);

	TESTu(asinh, -inf, result);
	TESTu(asinh, -1.5, result);
	TESTu(asinh, -1.0, result);
	TESTu(asinh, -0.5, result);
	TESTu(asinh, 0.0, result);
	TESTu(asinh, 0.5, result);
	TESTu(asinh, 1.0, result);
	TESTu(asinh, 1.5, result);
	TESTu(asinh, inf, result);
	TESTu(asinh, nan, nan);

	TESTu(atanh, -inf, nan);
	TESTu(atanh, -1.5, nan);
	TESTu(atanh, -1.0, -inf);
	TESTu(atanh, -0.5, result);
	TESTu(atanh, 0.0, result);
	TESTu(atanh, 0.5, result);
	TESTu(atanh, 1.0, inf);
	TESTu(atanh, 1.5, nan);
	TESTu(atanh, inf, nan);
	TESTu(atanh, nan, nan);

	TESTb(atan2, 1.0, 1.0, result);
	TESTb(atan2, -1.0, 1.0, result);
	TESTb(atan2, -1.0, -1.0, result);
	TESTb(atan2, 1.0, -1.0, result);

  printf("%d tests, %d failed results, %d failed errno\n", total_tests,
	total_dec_fail, total_errno_fail);
} 
