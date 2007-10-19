/* Handle
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

extern _Decimal64	__extenddfdd(double);

_Decimal64
__extendtfdd (long double a)
{
	_Decimal64 result = 0.0DD;
	_Decimal64 temp;
	union {
		long double ld;
		double d[2];
	}

	switch (fpclassify (a)) {
		case FP_ZERO:
			result = signbit(a) ? -0.0DD : 0.0DD;
			break;
		case FP_INFINITY: 
			result = a>0.0 ? DEC_INFINITY : -DEC_INFINITY;
			break;
		case FP_NAN:
			result = DEC_NAN;
			break;
		default:
			ldd.ld = a;
			temp = __extenddfdd (ldd.d[0]);
			result = temp;
			temp = __extenddfdd (ldd.d[1]);
			result = result + temp;
	}			
	return result;
}
