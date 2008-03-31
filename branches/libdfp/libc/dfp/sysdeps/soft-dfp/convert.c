/* Handle conversion from binary integers, floats and decimal types
   Copyright (C) 2007 IBM Corporation.

   Author(s): Pete Eberlein <eberlein@us.ibm.com>

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

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mapround.h"

#include "convert.h"

#if defined DECIMAL_TO_BINARY && SRC==32 && DEST==128
extern double __extendsddf (_Decimal32);
extern _Decimal32 __truncdfsd (double);
#elif defined DECIMAL_TO_BINARY && SRC==64 && DEST==128
extern double __truncdddf (_Decimal64);
extern _Decimal64 __extenddfdd (double);
#elif defined DECIMAL_TO_BINARY && SRC==128 && DEST==128
extern double __trunctddf(_Decimal128);
extern _Decimal128 __extenddftd(double);
#endif

#if defined BINARY_TO_DECIMAL && SRC==128 && DEST==32
extern _Decimal32	__truncdfsd(double);
#elif defined BINARY_TO_DECIMAL && SRC==128 && DEST==64
extern _Decimal64	__extenddfdd(double);
#elif defined BINARY_TO_DECIMAL && SRC==128 && DEST==128
extern _Decimal128	__extenddftd(double);
#endif

#define BUFMAX 128


DEST_TYPE 
FUNCTION_NAME (SRC_TYPE a)
{
#if defined DECIMAL_TO_DECIMAL
	DEST_TYPE result;
	decNumber d;
	decContext context;
	IEEE_SRC_TYPE e;
	IEEE_DEST_TYPE r;
	
	___decContextDefault(&context, CONTEXT_INIT);
	context.round = __dn_getround();
	
	PASTE(___host_to_ieee_,SRC) ((&a), &e);
	PASTE(___decimal,PASTE(SRC,ToNumber))(&e, &d);
	/* PASTE(___decimal,PASTE(SRC,ToNumber))(&a, &d); */
	/* PASTE(___decimal,PASTE(DEST,FromNumber))(&result, &d, &context);  */
	PASTE(___decimal,PASTE(DEST,FromNumber))(&r, &d, &context);
	PASTE(PASTE(___ieee_,DEST),_to_host) (&r, (&result));

	if (context.status != 0) {
	  int dec_flags = context.status & (DEC_IEEE_854_Inexact|DEC_IEEE_854_Invalid_operation);
	  DFP_HANDLE_EXCEPTIONS(DFP_IEEE_FLAGS(dec_flags));
	}

	return result;
#elif defined DECIMAL_TO_INTEGER
  /* decNumber's decimal* types have the same format as C's _Decimal*
     types, but they have different calling conventions.  */

  /* TODO: Decimal float to integer conversions should raise FE_INVALID
     if the result value does not fit into the result type.  */

  char buf[BUFMAX];
  char *pos;
  decNumber qval, n1, n2;
  decContext context;
  IEEE_SRC_TYPE e;

  /* Use a large context to avoid losing precision.  */
  ___decContextDefault (&context, DEC_INIT_DECIMAL128);
  /* Need non-default rounding mode here.  */
  context.round = DEC_ROUND_DOWN;

  PASTE(___host_to_ieee_,SRC) ((&a), &e);
  PASTE(___decimal,PASTE(SRC,ToNumber))(&e, &n1);
  /* PASTE(___decimal,PASTE(SRC,ToNumber))(&a, &n1); */

  /* Rescale if the exponent is less than zero.  */
  ___decNumberToIntegralValue (&n2, &n1, &context);
  /* Get a value to use for the quantize call.  */
  ___decNumberFromString (&qval, (char *) "1.0", &context);
  /* Force the exponent to zero.  */
  ___decNumberQuantize (&n1, &n2, &qval, &context);
  /* Get a string, which at this point will not include an exponent.  */
  ___decNumberToString (&n1, buf);
  /* Ignore the fractional part.  */
  pos = strchr (buf, '.');
  if (pos)
    *pos = 0;
  /* Use a C library function to convert to the integral type.  */
  return STR_TO_INT (buf, NULL, 10);
#elif defined INTEGER_TO_DECIMAL
  DEST_TYPE f;
  char buf[BUFMAX];
  decContext context;
  IEEE_DEST_TYPE e;

	___decContextDefault (&context, CONTEXT_INIT);
	context.round = DEC_ROUND_HALF_EVEN;

  /* Use a C library function to get a floating point string.  */
  sprintf (buf, INT_FMT ".0", CAST_FOR_FMT(a));
  /* Convert from the floating point string to a decimal* type.  */
  /* PASTE(___decimal,PASTE(DEST,FromString))(&f, buf, &context);  */
  PASTE(___decimal,PASTE(DEST,FromString))(&e, buf, &context);
  PASTE(PASTE(___ieee_,DEST),_to_host) (&e, (&f));

	if (context.status != 0) {
	  int dec_flags = context.status & 
	    (DEC_IEEE_854_Inexact|DEC_IEEE_854_Invalid_operation|DEC_IEEE_854_Overflow);
	  DFP_HANDLE_EXCEPTIONS(DFP_IEEE_FLAGS(dec_flags));
	}

  return f;
#else

	DEST_TYPE result = DEST_LITERAL(0.);

	switch (CLASSIFY (a)) {
		case FP_ZERO:
			result = SIGNBIT(a) ? DEST_LITERAL(-0.) : DEST_LITERAL(0.);
			break;
		case FP_INFINITE: 
			result = SIGNBIT(a) ? -DEST_INFINITY : DEST_INFINITY;
			break;
		case FP_NAN:
			result = DEST_NAN;
			break;
		default: {

#if defined DECIMAL_TO_BINARY && SRC==32 && DEST==128
// extendsdtf
	double df_part1, df_part2;
	_Decimal32 sd_part1, sd_part2;

	df_part1 = a;			/* TD -> DF  */
	sd_part1 = df_part1;		/* DF -> SD (not exact) */
	sd_part2 = a - sd_part1;	/* SD */
	df_part2 = sd_part2;		/* SD -> DF (trunc) */
	result = df_part1;
	result += df_part2;

#elif defined DECIMAL_TO_BINARY && SRC==64 && DEST==128
// extendddtf
	double df_part1, df_part2;
	_Decimal64 dd_part1, dd_part2;

	df_part1 = a;			/* TD -> DF  */
	dd_part1 = df_part1;		/* DF -> DD.  */
	dd_part2 = a - dd_part1;	/* DD.  */
	df_part2 = dd_part2;		/* DD -> DF.  */
	result = df_part1;
	result += df_part2;
	/* Clear inexact exception raised by DFP arithmetic.  */
	if (DFP_EXCEPTIONS_ENABLED
	    && DFP_TEST_EXCEPTIONS (FE_OVERFLOW|FE_UNDERFLOW) == 0)
	  DFP_CLEAR_EXCEPTIONS (FE_INEXACT);

#elif defined DECIMAL_TO_BINARY && SRC==128 && DEST==128
// trunctdtf
	double df_part1, df_part2;
	_Decimal128 td_part1, td_part2;

	df_part1 = a;			/* TD -> DF  */
	td_part1 = df_part1;		/* DF -> TD.  */
	td_part2 = a - td_part1;	/* TD.  */
	df_part2 = td_part2;		/* TD -> DF.  */
	result = df_part1;
	result += df_part2;
	/* Clear inexact exception raised by DFP arithmetic.  */
	if (DFP_EXCEPTIONS_ENABLED
	    && DFP_TEST_EXCEPTIONS (FE_OVERFLOW|FE_UNDERFLOW) == 0)
	  DFP_CLEAR_EXCEPTIONS (FE_INEXACT);

#elif defined BINARY_TO_DECIMAL && SRC==128 && (DEST==32 || DEST==64 || DEST==128)
// trunctfsd, trunctfdd, extendtftd
	DEST_TYPE temp;
	union {
		SRC_TYPE ld;
		double d[2];
	} ldd;

	ldd.ld = a;
	temp = ldd.d[0];
	result = temp;
	temp = ldd.d[1];
	result += temp;
	/* Clear inexact exception raised by DFP arithmetic.  */
	if (DFP_EXCEPTIONS_ENABLED
	    && DFP_TEST_EXCEPTIONS (FE_OVERFLOW|FE_UNDERFLOW) == 0)
	  DFP_CLEAR_EXCEPTIONS (FE_INEXACT);

#elif defined BINARY_TO_DECIMAL && SRC==64 && (DEST==32 || DEST==64 || DEST==128)
// truncdfsd, extenddfdd, extenddftd
/*	DEST_TYPE temp; */
	_Decimal128 temp; /* Needs to be big enough so that temp = mant doesn't round.  */
	double a_norm;
	long long mant;
	int exp, sexp;

	a_norm = FREXPDF (a, &exp);
	mant = a_norm * 9007199254740992.0;	/* 53 bits of mantissa.  */
	sexp = exp - 53;			/* Exponent adjusted for mantissa.  */
	temp = mant;				/* DI -> TD.  */
	if (sexp > 0)
		temp *= DECPOWOF2[sexp];
	else if (sexp < 0)
		temp /= DECPOWOF2[-sexp];
	result = (DEST_TYPE)temp; /* Cast to the resultant type.  */
	/* Clear inexact exception raised by DFP arithmetic.  */
	if (DFP_EXCEPTIONS_ENABLED
	    && DFP_TEST_EXCEPTIONS (FE_OVERFLOW|FE_UNDERFLOW) == 0)
	  DFP_CLEAR_EXCEPTIONS (FE_INEXACT);

#elif defined BINARY_TO_DECIMAL && SRC==32 && (DEST==32 || DEST==64 || DEST==128)
// extendsfsd, extendsfdd, extendsftd
#if DEST==32
	_Decimal64 temp;
#else
	_Decimal128 temp;
#endif
	float a_norm;
	long long mant;
	int exp, sexp;

	a_norm = FREXPSF (a, &exp);
	mant = a_norm * 16777216.0;	/* 24 bits of mantissa.  */
	sexp = exp - 24;		/* Exponent adjusted for mantissa.  */
	temp = mant;
	if (sexp > 0)
		temp *= DECPOWOF2[sexp];
	else if (sexp < 0)
		temp /= DECPOWOF2[-sexp];
	result = temp;
	/* Clear inexact exception raised by DFP arithmetic.  */
	if (DFP_EXCEPTIONS_ENABLED
	    && DFP_TEST_EXCEPTIONS (FE_OVERFLOW|FE_UNDERFLOW) == 0)
	  DFP_CLEAR_EXCEPTIONS (FE_INEXACT);

#elif defined DECIMAL_TO_BINARY && SRC==64 && DEST==64
// truncdddf
	long double temp;
	SRC_TYPE a_norm;
	long long mant;
	int	exp, sexp;

	a_norm = FREXPD64 (a, &exp);

	/* Avoid going beyond the bounds of the table, which would also
	   mean an overflow or underflow.  */
	if (exp > BINPOWOF10_LIMIT)		/* Obvious overflow.  */
	  {
	    if (DFP_EXCEPTIONS_ENABLED)
	      DFP_HANDLE_EXCEPTIONS (FE_OVERFLOW|FE_INEXACT);
	    return SIGNBIT(a) ? -INFINITY : INFINITY;
	  }
	else if (exp < -BINPOWOF10_LIMIT)	/* Obvious underflow.  */
	  {
	    if (DFP_EXCEPTIONS_ENABLED)
	      DFP_HANDLE_EXCEPTIONS (FE_UNDERFLOW|FE_INEXACT);
	    return SIGNBIT(a) ? -0.0 : 0.0;
	  }

	mant = a_norm * 1.E+16DD;	/* 16 digits of mantissa.  */
	sexp = exp - 16;		/* Exponent adjusted for mantissa.  */
	temp = mant;			/* mantissa as TF */
	if (sexp > 0)
	  result = temp * BINPOWOF10[sexp];
	else if (sexp < 0)
	  {
	    /* Avoid going beyond the bounds of the exponent table for
	       negative exponents.  */
	    if (sexp < -BINPOWOF10_LIMIT)
	      {
	        temp /= BINPOWOF10[BINPOWOF10_LIMIT];
	        sexp += BINPOWOF10_LIMIT;
	      }
	    result = temp / BINPOWOF10[-sexp];
	  }
	else
	  result = temp;
	/* Clear inexact exception raised by DFP arithmetic.  */
	if (DFP_EXCEPTIONS_ENABLED
	    && DFP_TEST_EXCEPTIONS (FE_OVERFLOW|FE_UNDERFLOW) == 0)
	  DFP_CLEAR_EXCEPTIONS (FE_INEXACT);

#elif defined DECIMAL_TO_BINARY && SRC==64 && DEST==32
// truncddsf
	double temp;
	_Decimal64 a_norm;
	long long mant;
	int exp, sexp;
	
	a_norm = FREXPD64 (a, &exp);
	
	/* Check for values that would overflow the exponent table, which
	   would be obvious overflow and underflow.  */
	if (exp > 39)		/* Obvious overflow.  */
	  {
	    if (DFP_EXCEPTIONS_ENABLED)
	      DFP_HANDLE_EXCEPTIONS (FE_OVERFLOW|FE_INEXACT);
	    return SIGNBIT(a) ? -INFINITY : INFINITY;
	  }
	else if (exp < -39)	/* Obvious underflow.  */
	  {
	    if (DFP_EXCEPTIONS_ENABLED)
	      DFP_HANDLE_EXCEPTIONS (FE_UNDERFLOW|FE_INEXACT);
	    return SIGNBIT(a) ? -0.0 : 0.0;
	  }

	mant = a_norm * 1.E+16DD;		/* 16 digits of mantissa.  */
	sexp = exp - 16;			/* Exponent adjusted for mantissa.  */
	temp = mant;
	if (sexp > 0)
	  temp *= BINPOWOF10[sexp];
	else if (sexp < 0)
	  temp /= BINPOWOF10[-sexp];
	result = temp;

#elif defined DECIMAL_TO_BINARY && SRC==128 && DEST==64
// trunctddf
	long double temp;	/* Need at least 16 decimal digits of accuracy.  */
	SRC_TYPE a_norm;
	long long mant;
	int	exp, sexp;

	a_norm = FREXPD128 (a, &exp);
	/* Avoid going beyond the bounds of the exponent table.  */
	if (exp > BINPOWOF10_LIMIT)		/* Obvious overflow.  */
	  {
	    if (DFP_EXCEPTIONS_ENABLED)
	      DFP_HANDLE_EXCEPTIONS (FE_OVERFLOW|FE_INEXACT);
	    return SIGNBIT(a) ? -INFINITY : INFINITY;
	  }
	else if (exp < -BINPOWOF10_LIMIT)		/* Obvious underflow.  */
	  {
	    if (DFP_EXCEPTIONS_ENABLED)
	      DFP_HANDLE_EXCEPTIONS (FE_UNDERFLOW|FE_INEXACT);
	    return SIGNBIT(a) ? -0.0 : 0.0;
	  }

	mant = a_norm * 1.E+17DL;		/* 17 digits of mantissa.  */
	sexp = exp - 17;			/* Exponent adjusted for mantissa.  */
	temp = mant;
	if (sexp > 0)
	  temp *= BINPOWOF10[sexp];
	else if (sexp < 0)
	  {
	    /* Avoid going beyond the bounds of the exponent table for
	       negative exponents.  */
	    if (sexp < -BINPOWOF10_LIMIT)
	      {
	        temp /= BINPOWOF10[BINPOWOF10_LIMIT];
	        sexp += BINPOWOF10_LIMIT;
	      }
	    temp /= BINPOWOF10[-sexp];
	  }
	result = temp;
	/* Clear inexact exception raised by DFP arithmetic.  */
	if (DFP_EXCEPTIONS_ENABLED
	    && DFP_TEST_EXCEPTIONS (FE_OVERFLOW|FE_UNDERFLOW) == 0)
	  DFP_CLEAR_EXCEPTIONS (FE_INEXACT);

#elif defined DECIMAL_TO_BINARY && SRC==128 && DEST==32
// trunctdsf
	double temp;
	SRC_TYPE a_norm;
	long long mant;
	int	exp, sexp;
	
	a_norm = FREXPD128 (a, &exp);
	/* Handle obvious overflow and underflow to avoid going beyond the
	   bounds of the exponent table.  */
	if (exp > 39)		/* Obvious overflow.  */
	  {
	    if (DFP_EXCEPTIONS_ENABLED)
	      DFP_HANDLE_EXCEPTIONS (FE_OVERFLOW|FE_INEXACT);
	    return SIGNBIT(a) ? -INFINITY : INFINITY;
	  }
	else if (exp < -39)	/* Obvious underflow. */
	  {
	    if (DFP_EXCEPTIONS_ENABLED)
	      DFP_HANDLE_EXCEPTIONS (FE_UNDERFLOW|FE_INEXACT);
	    return SIGNBIT(a) ? -0.0 : 0.0;
	  }

	mant = a_norm * 1E+15DL;		/* 15 digits of mantissa.  */
	sexp = exp - 15;			/* Exponent adjusted for mantissa.  */
	temp = mant;
	if (sexp > 0)
	  temp *= BINPOWOF10[sexp];
	else if (sexp < 0)
	  temp /= BINPOWOF10[-sexp];
        result = temp;

#elif defined DECIMAL_TO_BINARY && SRC==32 && (DEST==32 || DEST==64)
// truncsdsf, extendsddf
	double temp;
	SRC_TYPE a_norm;
	long long mant;
	int	exp, sexp;

	a_norm = FREXPD32 (a, &exp);
	mant = a_norm * 1E+7DF;		/* 7 digits of mantissa.  */
	sexp = exp - 7;			/* Exponent adjusted for mantissa.  */
	temp = mant;
	if (sexp > 0)
	  temp *= BINPOWOF10[sexp];
	else if (sexp < 0)
	  temp /= BINPOWOF10[-sexp];
	result = temp;

#endif
		break;
		}
	}
	return result;
#endif
}
