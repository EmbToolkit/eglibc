/* ------------------------------------------------------------------ */
/* Decimal 64-bit format module header                                */
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

#if !defined(DECIMAL64)
  #define DECIMAL64
  #define DEC64NAME     "decimal64"                   /* Short name */
  #define DEC64FULLNAME "Decimal 64-bit Number"       /* Verbose name */
  #define DEC64AUTHOR   "Mike Cowlishaw"              /* Who to blame */


  /* parameters for decimal64s */
  #define DECIMAL64_Bytes  8            // length
  #define DECIMAL64_Pmax   16           // maximum precision (digits)
  #define DECIMAL64_Emax   384          // maximum adjusted exponent
  #define DECIMAL64_Emin  -383          // minimum adjusted exponent
  #define DECIMAL64_Bias   398          // bias for the exponent
  #define DECIMAL64_String 24           // maximum string length, +1
  #define DECIMAL64_EconL  8            // exponent continuation length
  // highest biased exponent (Elimit-1)
  #define DECIMAL64_Ehigh  (DECIMAL64_Emax+DECIMAL64_Bias-DECIMAL64_Pmax+1)

  // check enough digits, if pre-defined
  #if defined(DECNUMDIGITS)
    #if (DECNUMDIGITS<DECIMAL64_Pmax)
      #error decimal64.h needs pre-defined DECNUMDIGITS>=16 for safe use
    #endif
  #endif


  #ifndef DECNUMDIGITS
    #define DECNUMDIGITS DECIMAL64_Pmax // size if not already defined
  #endif
  #ifndef DECNUMBER
    #include "decNumber.h"              // context and number library
  #endif

  /* Decimal 64-bit type, accessible by bytes */
  typedef struct {
    uint8_t bytes[DECIMAL64_Bytes];     // decimal64: 1, 5, 8, 50 bits
    } decimal64;

  /* special values [top byte excluding sign bit; last two bits are
     don't-care for Infinity on input, last bit don't-care for NaN] */
  #if !defined(DECIMAL_NaN)
    #define DECIMAL_NaN     0x7c        // 0 11111 00 NaN
    #define DECIMAL_sNaN    0x7e        // 0 11111 10 sNaN
    #define DECIMAL_Inf     0x78        // 0 11110 00 Infinity
  #endif

  /* Macros for accessing decimal64 fields.  These assume the argument
     is a reference (pointer) to the decimal64 structure, and the
     decimal64 is in network byte order (big-endian) */
  // Get sign
  #define ___decimal64Sign(d)       ((unsigned)(d)->bytes[0]>>7)

  // Get combination field
  #define ___decimal64Comb(d)       (((d)->bytes[0] & 0x7c)>>2)

  // Get exponent continuation [does not remove bias]
  #define ___decimal64ExpCon(d)     ((((d)->bytes[0] & 0x03)<<6)         \
                               | ((unsigned)(d)->bytes[1]>>2))

  // Set sign [this assumes sign previously 0]
  #define ___decimal64SetSign(d, b) {                                    \
    (d)->bytes[0]|=((unsigned)(b)<<7);}

  // Set exponent continuation [does not apply bias]
  // This assumes range has been checked and exponent previously 0; type
  // of exponent must be unsigned
  #define ___decimal64SetExpCon(d, e) {                                  \
    (d)->bytes[0]|=(uint8_t)((e)>>6);                                 \
    (d)->bytes[1]|=(uint8_t)(((e)&0x3F)<<2);}

  /* ------------------------------------------------------------------ */
  /* Routines                                                           */
  /* ------------------------------------------------------------------ */
  // String conversions
#if defined NOT_IN_libc /* Don't build this into libc  */
  decimal64 * ___decimal64FromString(decimal64 *, const char *, decContext *);
#endif /* NOT_IN_libc  */
  char * ___decimal64ToString(const decimal64 *, char *);
  libc_hidden_proto (___decimal64ToString)
  char * ___decimal64ToEngString(const decimal64 *, char *);
  libc_hidden_proto (___decimal64ToEngString)

  // decNumber conversions
#if defined NOT_IN_libc /* Don't build this into libc  */
  decimal64 * ___decimal64FromNumber(decimal64 *, const decNumber *,
                                  decContext *);
#endif
  decNumber * ___decimal64ToNumber(const decimal64 *, decNumber *);
  libc_hidden_proto (___decimal64ToNumber)

#endif
