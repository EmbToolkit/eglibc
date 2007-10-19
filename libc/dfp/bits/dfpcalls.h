/* Prototype declarations for math functions related only to decimal
   floating point support; helper file for <math.h>.

   Copyright (C) 2006 IBM Corporation.

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

/* Per comments in <bits/mathcalls.h> this file shouldn't be protected from
   multiple inclusion.  See <bits/mathcalls.h> for more information on
   declaring new prototypes.  */

#ifndef _MATH_H
# error "Never include <bits/dfpcalls.h> directly; include <math.h> instead."
#endif

#include <stdbool.h>

#ifdef __STDC_WANT_DEC_FP__
/* DFP supported functions only; new in ISO C WG14 N1176.  */
_Mdouble_BEGIN_NAMESPACE

/* Retain the value, but set the exponent of x to the exponent of y. */
__MATHCALL (quantize,, (_Mdouble_ __x, _Mdouble_ __y));

/* Is the representation exponents of the x and y parameters the same?  */
/* __MATHDECL_1 (_Bool,samequantum,, (_Mdouble_ __x, _Mdouble_ __y)); */
__MATHDECL_1 (_Bool,samequantum,, (_Mdouble_ __x, _Mdouble_ __y));

_Mdouble_END_NAMESPACE

#endif /* __STDC_WANT_DEC_FP__  */
