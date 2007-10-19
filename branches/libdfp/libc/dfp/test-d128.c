/* Copyright (C) 2006,2007 IBM Corporation.
   Author(s): Ryan S. Arnold <rsa@us.ibm.com>

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

#define FUNC(function) function##d128
#define FLOAT _Decimal128
#define TEST_MSG "testing _Decimal128 (without inline functions)\n"

/* Always use the DL floating suffix.  The dfp library will handle proper
 * truncation and rounding.  */
/*#define MATHCONST(x) x##dl  NOT USED  */
#define _F(x) x##DL
#define _L(x) x##DL
#define _LC(x) x##dl /* Long Double constant suffix is the same  */
#define _C(x) x##dl  /* as the normal constant suffix for DFP  */
#define _N(x) x##_DL /* special long name terms for decimal float. e.g. minus_zero_DL  */

/* vim regex to search/replace instances of x.xL with _L(x.x):
 * :%s/\(-\=\d*\)\.\(\d\+[eE]\=-\=\d*\)L/_L(\1\.\2)/gc
 */

/* Define the rounding mode and rounding mode functions.  */
#define SETROUND(x) fe_dec_setround(x)
#define GETROUND(x) fe_dec_getround(x)

#define TONEAREST FE_DEC_TONEAREST
#define TOWARDZERO FE_DEC_TOWARDZERO
#define TONEARESTFROMZERO FE_DEC_TONEARESTFROMZERO
#define DOWNWARD FE_DEC_DOWNWARD
#define UPWARD FE_DEC_UPWARD

#define CHOOSE(Clongdouble,Cdouble,Cfloat,Cinlinelongdouble,Cinlinedouble,Cinlinefloat,C_Decimal128,C_Decimal64,C_Decimal32) C_Decimal128
#define PRINTF_EXPR "DDe"
/*#define PRINTF_XEXPR "Ha" We don't have hex printing yet. */
#define PRINTF_XEXPR "DDe"
#define PRINTF_NEXPR "DDf"
#define TEST_DECIMAL 1

#ifndef __NO_MATH_INLINES
# define __NO_MATH_INLINES
#endif

/* Various constants (we must supply them precalculated for accuracy).  */
# define M_PI_6dl		.52359877559829887307710723054658383DL
# define M_E2dl			7.389056098930650227230427460575008DL
# define M_E3dl			20.085536923187667740928529654581719DL
# define M_2_SQRT_PIdl		3.5449077018110320545963349666822903DL	/* 2 sqrt (M_PIdl)  */
# define M_SQRT_PIdl		1.7724538509055160272981674833411451DL	/* sqrt (M_PIdl)  */
# define M_LOG_SQRT_PIdl	0.57236494292470008707171367567652933DL	/* log(sqrt(M_PIdl))  */
# define M_LOG_2_SQRT_PIdl	1.265512123484645396488945797134706DL	/* log(2*sqrt(M_PIdl))  */
# define M_PI_34dl		(M_PIdl - M_PI_4dl)			/* 3*pi/4 */
# define M_PI_34_LOG10Edl		(M_PIdl - M_PI_4dl) * M_LOG10Edl
# define M_PI2_LOG10Edl		M_PI_2dl * M_LOG10Edl
# define M_PI4_LOG10Edl		M_PI_4dl * M_LOG10Edl
# define M_PI_LOG10Edl		M_PIdl * M_LOG10Edl
# define M_SQRT_2_2dl		0.70710678118654752440084436210484903DL /* sqrt (2) / 2 */

#include "libdfp-test.c"
