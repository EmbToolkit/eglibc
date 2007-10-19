/* ------------------------------------------------------------------ */
/* Decimal 128-bit format module header                               */
/* ------------------------------------------------------------------ */
/* Copyright (C) 2006,2007 IBM Corporation.
   Contributed by IBM Corporation.

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

#if !defined(DECIMAL128)
  #define DECIMAL128
  #define DEC128NAME     "decimal128"                 /* Short name */
  #define DEC128FULLNAME "Decimal 128-bit Number"     /* Verbose name */
  #define DEC128AUTHOR   "Mike Cowlishaw"             /* Who to blame */

  /* parameters for decimal128s */
  #define DECIMAL128_Bytes  16          // length
  #define DECIMAL128_Pmax   34          // maximum precision (digits)
  #define DECIMAL128_Emax   6144        // maximum adjusted exponent
  #define DECIMAL128_Emin  -6143        // minimum adjusted exponent
  #define DECIMAL128_Bias   6176        // bias for the exponent
  #define DECIMAL128_String 43          // maximum string length, +1
  #define DECIMAL128_EconL  12          // exponent continuation length
  // highest biased exponent (Elimit-1)
  #define DECIMAL128_Ehigh  (DECIMAL128_Emax+DECIMAL128_Bias-DECIMAL128_Pmax+1)

  // check enough digits, if pre-defined
  #if defined(DECNUMDIGITS)
    #if (DECNUMDIGITS<DECIMAL128_Pmax)
      #error decimal128.h needs pre-defined DECNUMDIGITS>=34 for safe use
    #endif
  #endif

  #ifndef DECNUMDIGITS
    #define DECNUMDIGITS DECIMAL128_Pmax // size if not already defined
  #endif
  #ifndef DECNUMBER
    #include "decNumber.h"              // context and number library
  #endif

  /* Decimal 128-bit type, accessible by bytes */
  typedef struct {
    uint8_t bytes[DECIMAL128_Bytes];    // decimal128: 1, 5, 12, 110 bits
    } decimal128;

  /* special values [top byte excluding sign bit; last two bits are
     don't-care for Infinity on input, last bit don't-care for NaN] */
  #if !defined(DECIMAL_NaN)
    #define DECIMAL_NaN     0x7c        // 0 11111 00 NaN
    #define DECIMAL_sNaN    0x7e        // 0 11111 10 sNaN
    #define DECIMAL_Inf     0x78        // 0 11110 00 Infinity
  #endif

  /* Macros for accessing decimal128 fields.  These assume the argument
     is a reference (pointer) to the decimal128 structure, and the
     decimal128 is in network byte order (big-endian) */
  // Get sign
  #define ___decimal128Sign(d)       ((unsigned)(d)->bytes[0]>>7)

  // Get combination field
  #define ___decimal128Comb(d)       (((d)->bytes[0] & 0x7c)>>2)

  // Get exponent continuation [does not remove bias]
  #define ___decimal128ExpCon(d)     ((((d)->bytes[0] & 0x03)<<10)     \
                                | ((unsigned)(d)->bytes[1]<<2)        \
                                | ((unsigned)(d)->bytes[2]>>6))

  // Set sign [this assumes sign previously 0]
  #define ___decimal128SetSign(d, b) {                                 \
    (d)->bytes[0]|=((unsigned)(b)<<7);}

  // Set exponent continuation [does not apply bias]
  // This assumes range has been checked and exponent previously 0;
  // type of exponent must be unsigned
  #define ___decimal128SetExpCon(d, e) {                               \
    (d)->bytes[0]|=(uint8_t)((e)>>10);                                \
    (d)->bytes[1] =(uint8_t)(((e)&0x3fc)>>2);                         \
    (d)->bytes[2]|=(uint8_t)(((e)&0x03)<<6);}

  /* ------------------------------------------------------------------ */
  /* Routines                                                           */
  /* ------------------------------------------------------------------ */
  // String conversions
#if defined NOT_IN_libc /* Don't build this into libc  */
  decimal128 * ___decimal128FromString(decimal128 *, const char *, decContext *);
#endif
  char * ___decimal128ToString(const decimal128 *, char *);
  libc_hidden_proto (___decimal128ToString)
  char * ___decimal128ToEngString(const decimal128 *, char *);
  libc_hidden_proto (___decimal128ToEngString)

  // decNumber conversions
#if defined NOT_IN_libc /* Don't build this into libc  */
  decimal128 * ___decimal128FromNumber(decimal128 *, const decNumber *,
                                    decContext *);
#endif
  decNumber * ___decimal128ToNumber(const decimal128 *, decNumber *);
  libc_hidden_proto (___decimal128ToNumber)

#endif
