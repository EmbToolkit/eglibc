/* Number of digits functions.

   Copyright (C) 2006, 2007, 2008 IBM Corporation.
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


#ifndef _NUMDIGITS_H
#define _NUMDIGITS_H 1

#include "dpd-private.h"
#include <string.h>

static inline int
getexp (DEC_TYPE x)
{
  int exp;
  struct ieee754r_c_field c_f;

#if _DECIMAL_SIZE == 32
  union ieee754r_Decimal32 d;
  d.sd = x;
  c_f =  c_decoder[d.ieee.c];
  exp = c_f.lm_exp << DECIMAL32_BEC_bits;
  exp += d.ieee.bec;
  exp -= DECIMAL32_Bias;

#elif _DECIMAL_SIZE == 64
  union ieee754r_Decimal64 d;
  d.dd = x;
  c_f =  c_decoder[d.ieee.c];
  exp = c_f.lm_exp << DECIMAL64_BEC_bits;
  exp += d.ieee.bec;
  exp -= DECIMAL64_Bias;

#elif _DECIMAL_SIZE == 128
  union ieee754r_Decimal128 d;
  d.td = x;
  c_f =  c_decoder[d.ieee.c];
  exp = c_f.lm_exp << DECIMAL128_BEC_bits;
  exp += d.ieee.bec;
  exp -= DECIMAL128_Bias;

#endif

  return exp;
}


static inline void
setexp (DEC_TYPE *x, int exp)
{

#if _DECIMAL_SIZE == 32
  union ieee754r_Decimal32 d;
  d.sd = *x;
  exp += DECIMAL32_Bias;
  d.ieee.bec = exp;
  d.ieee.c = lm2lmd_to_c[c_decoder[d.ieee.c].lmd][exp >> DECIMAL32_BEC_bits];
  *x = d.sd;

#elif _DECIMAL_SIZE == 64
  union ieee754r_Decimal64 d;
  d.dd = *x;
  exp += DECIMAL64_Bias;
  d.ieee.bec = exp;
  d.ieee.c = lm2lmd_to_c[c_decoder[d.ieee.c].lmd][exp >> DECIMAL64_BEC_bits];
  *x = d.dd;

#elif _DECIMAL_SIZE == 128
  union ieee754r_Decimal128 d;
  d.td = *x;
  exp += DECIMAL128_Bias;
  d.ieee.bec = exp;
  d.ieee.c = lm2lmd_to_c[c_decoder[d.ieee.c].lmd][exp >> DECIMAL128_BEC_bits];
  *x = d.td;

#endif

}



static inline int
numdigits (DEC_TYPE x)
{
  int firstdigit = 0 ;
#if _DECIMAL_SIZE == 32
  char digits[8];
  __get_digits_d32(x, digits, NULL, NULL, NULL, NULL);
#elif _DECIMAL_SIZE == 64
  char digits[17];
  __get_digits_d64(x, digits, NULL, NULL, NULL, NULL);
#elif _DECIMAL_SIZE == 128
  char digits[35];
  __get_digits_d128(x, digits, NULL, NULL, NULL, NULL);
#endif
  while (digits[firstdigit] == '0') firstdigit++;

  return strlen(digits + firstdigit);
}


#endif /* _NUMDIGITS_H */
