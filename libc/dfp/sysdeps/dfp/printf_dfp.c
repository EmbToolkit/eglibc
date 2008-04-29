/* Function definition to convert DFP values to strings

   Copyright (C) 2006 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   Contributed by IBM Corporation.
   Based on GLIBC stdio-common/printf_fp.c by Ulrich Drepper <drepper@gnu.ai.mit.edu>, 1995.
   Author(s): Ryan S. Arnold <rsa@us.ibm.com>

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#include "printf_dfp.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <libioP.h>

#include <fmt_dfp.h>

#include <fenv.h>

extern void __get_dpd_digits (int, const void *const *, char*, int*, int*, int*,
int*);


/* This defines make it possible to use the same code for GNU C library and
   the GNU I/O library.	 */
#define PUT(f, s, n) _IO_sputn (f, s, n)
#define PAD(f, c, n) (wide ? _IO_wpadn (f, c, n) : INTUSE(_IO_padn) (f, c, n))
/* We use this file GNU C library and GNU I/O library.	So make
   names equal.	 */
#undef putc
#define putc(c, f) (wide \
		    ? (int)_IO_putwc_unlocked (c, f) : _IO_putc_unlocked (c, f))
#define size_t     _IO_size_t
#define FILE	     _IO_FILE

/* Macros for doing the actual output.  */

#define outchar(ch)							      \
  do									      \
    {									      \
      register const int outc = (ch);					      \
      if (putc (outc, fp) == EOF)					      \
	{								      \
	  if (buffer_malloced)						      \
	    free (wbuffer);						      \
	  return -1;							      \
	}								      \
      ++done;								      \
    } while (0)

#define PRINT(ptr, wptr, len)						      \
  do									      \
    {									      \
      register size_t outlen = (len);					      \
      if (len > 20)							      \
	{								      \
	  if (PUT (fp, wide ? (const char *) wptr : ptr, outlen) != outlen)   \
	    {								      \
	      if (buffer_malloced)					      \
		free (wbuffer);						      \
	      return -1;						      \
	    }								      \
	  ptr += outlen;						      \
	  done += outlen;						      \
	}								      \
      else								      \
	{								      \
	  if (wide)							      \
	    while (outlen-- > 0)					      \
	      outchar (*wptr++);					      \
	  else								      \
	    while (outlen-- > 0)					      \
	      outchar (*ptr++);						      \
	}								      \
    } while (0)

#define PADN(ch, len)							      \
  do									      \
    {									      \
      if (PAD (fp, ch, len) != len)					      \
	{								      \
	  if (buffer_malloced)						      \
	    free (wbuffer);						      \
	  return -1;							      \
	}								      \
      done += len;							      \
    }									      \
  while (0)


#define DECIMAL_PRINTF_BUF_SIZE 65 /* ((DECIMAL128_PMAX + 14) * 2) + 1  */

/* fe_decround.c will initialize this function pointer to fe_decgetround */
int (*__printf_dfp_getround_callback)(void) = NULL;


int
__printf_dfp (FILE *fp,
	      const struct printf_info *info,
	      const void *const *args)
{
	int wide = info->wide;
	wchar_t *wbuffer = NULL;
	int buffer_malloced = 0;  /* PRINT macro uses this.  */
	/* Counter for number of written characters.	*/
	int done = 0;
	int len = 0;

  /* Locale-dependent representation of decimal point.	*/
  const char *decimal;
  wchar_t decimalwc;
  char spec = tolower(info->spec);

  /* Locale-dependent thousands separator and grouping specification.  */
  const char *thousands_sep = NULL;
  wchar_t thousands_sepwc = 0;
  const char *grouping;

  
#ifdef OPTION_EGLIBC_LOCALE_CODE
  if (info->extra == 0)
    {
      decimal = _NL_CURRENT (LC_NUMERIC, DECIMAL_POINT);
      decimalwc = _NL_CURRENT_WORD (LC_NUMERIC, _NL_NUMERIC_DECIMAL_POINT_WC);
    }
  else
    {
      decimal = _NL_CURRENT (LC_MONETARY, MON_DECIMAL_POINT);
      if (*decimal == '\0')
	decimal = _NL_CURRENT (LC_NUMERIC, DECIMAL_POINT);
      decimalwc = _NL_CURRENT_WORD (LC_MONETARY,
				    _NL_MONETARY_DECIMAL_POINT_WC);
      if (decimalwc == L'\0')
	decimalwc = _NL_CURRENT_WORD (LC_NUMERIC,
				      _NL_NUMERIC_DECIMAL_POINT_WC);
    }
  /* The decimal point character must not be zero.  */
  assert (*decimal != '\0');
  assert (decimalwc != L'\0');
#else
  /* Hard-code values from 'C' locale.  */
  decimal = ".";
  decimalwc = L'.';
#endif


#ifdef OPTION_EGLIBC_LOCALE_CODE
  if (info->group)
    {
      if (info->extra == 0)
	grouping = _NL_CURRENT (LC_NUMERIC, GROUPING);
      else
	grouping = _NL_CURRENT (LC_MONETARY, MON_GROUPING);

      if (*grouping <= 0 || *grouping == CHAR_MAX)
	grouping = NULL;
      else
	{
	  /* Figure out the thousands separator character.  */
	  if (wide)
	    {
	      if (info->extra == 0)
		thousands_sepwc =
		  _NL_CURRENT_WORD (LC_NUMERIC, _NL_NUMERIC_THOUSANDS_SEP_WC);
	      else
		thousands_sepwc =
		  _NL_CURRENT_WORD (LC_MONETARY,
				    _NL_MONETARY_THOUSANDS_SEP_WC);
	    }
	  else
	    {
	      if (info->extra == 0)
		thousands_sep = _NL_CURRENT (LC_NUMERIC, THOUSANDS_SEP);
	      else
		thousands_sep = _NL_CURRENT (LC_MONETARY, MON_THOUSANDS_SEP);
	    }

	  if ((wide && thousands_sepwc == L'\0')
	      || (! wide && *thousands_sep == '\0'))
	    grouping = NULL;
	  else if (thousands_sepwc == L'\0')
	    /* If we are printing multibyte characters and there is a
	       multibyte representation for the thousands separator,
	       we must ensure the wide character thousands separator
	       is available, even if it is fake.  */
	    thousands_sepwc = 0xfffffffe;
	}
    }
  else
    grouping = NULL;
#else
  grouping = NULL;
#endif


{
    char digits[DECIMAL_PRINTF_BUF_SIZE];
    int exp, /* the exponent */
     is_neg, /* is negative */
     is_nan, /* is not a number */
     is_inf, /* is infinite */
     sig,    /* number of significant digits */
     width,  /* width of the field */
     decpt,  /* decimal point offset into digits[] */
     prec,   /* number of digits that follow the decimal point,
                or number of significant digits for %g */
     default_prec, /* default precision, if none given */
     n;      /* current digit offset into digits[] */
    digits[0] = '0'; /* need an extra digit for rounding up */
    
//    __get_dpd_digits (
//      (info->is_short) ?        32: /* %H */
//      (info->is_long_double) ? 128: /* %DD */
//                                64, /* %D */
//	args, digits+1, &exp, &is_neg, &is_nan, &is_inf);

    if (info->is_short)
      __get_digits_d32 (*((_Decimal32*)args[0]), digits+1, &exp, &is_neg,
			&is_nan, &is_inf);
    else if (info->is_long_double)
      __get_digits_d128 (*((_Decimal128*)args[0]), digits+1, &exp, &is_neg,
			 &is_nan, &is_inf);
    else
      __get_digits_d64 (*((_Decimal64*)args[0]), digits+1, &exp, &is_neg,
			&is_nan, &is_inf);

    width = info->width;
    prec = info->prec;
    
    if (is_nan || is_inf) {
      width -= 3;
      /*if (is_nan) is_neg = 0;*/
      if (is_neg || info->showsign || info->space) width--;
      
      if (!info->left && width > 0)
        PADN (' ', width);

      if (is_neg)
        outchar ('-');
      else if (info->showsign)
        outchar ('+');
      else if (info->space)
        outchar (' ');
      
      if (is_nan)
        if (isupper(info->spec))
	  { outchar ('N'); outchar ('A'); outchar ('N'); }
	else
	  { outchar ('n'); outchar ('a'); outchar ('n'); }
      else
        if (isupper(info->spec))
	  { outchar ('I'); outchar ('N'); outchar ('F'); }
	else
	  { outchar ('i'); outchar ('n'); outchar ('f'); }
	
      if (info->left && width > 0)
        PADN (' ', width);

      return 0;
    }
    
   
    n = 0;
    while (digits[n] == '0') n++;
    sig = strlen(digits+n);
    if (sig == 0) { sig = 1; n--; } /* coefficient is zero */
    len = n + sig;
    
    switch (spec)
      {
        case 'a': /* fall thru */
	case 'g': default_prec = sig; break;
	case 'f': default_prec = (exp < 0) ? -exp : 0; break;
        case 'e': default_prec = sig-1; break;
      }
    
    /* if no precision is specified, use that of the decimal type */
    if (prec < 0)
      prec = default_prec;
    else if (prec < default_prec)
    /* do rounding if precision is less than the decimal type */
      {
        int index, roundmode = 0, do_round = 0;
	char rounddigit = '4';
	
        index = n + prec + sig - default_prec;

        /* FIXME: we should check rounding mode for %a */
	if (__printf_dfp_getround_callback) {
	  roundmode = (*__printf_dfp_getround_callback)();
	
/*	outchar('[');
	outchar('r');
	outchar('o');
	outchar('u');
	outchar('n');
	outchar('d');
	outchar('m');
	outchar('o');
	outchar('d');
	outchar('e');
	outchar('=');
	outchar('0'+roundmode);
	outchar(']');*/
	
	switch (roundmode) {
	  case FE_DEC_TONEAREST: rounddigit = '4'; break;
	  case FE_DEC_TOWARDZERO: rounddigit = '9'; break;
	  case FE_DEC_UPWARD: rounddigit = is_neg ? '9' : '0'-1; break;
	  case FE_DEC_DOWNWARD: rounddigit = is_neg ? '0'-1 : '9'; break;
	  case FE_DEC_TONEARESTFROMZERO: rounddigit = '4'; break;
	  case 5: rounddigit = '4'; break; /* nearest, ties toward zero */
	  case 6: rounddigit = '0'-1; break; /* away from zero */
	  case 7: rounddigit = '4'; break; /* round for shorter precision */
	  default: rounddigit = '4'; break;
	}
	
	}
	
        if (index < len && digits[index] > rounddigit)
          do { 
	    int trailzero = index+1;
	    if (digits[index] == rounddigit+1)
	      {
	        while (trailzero < len)
	          {
	            if (digits[trailzero] != '0')
		      {
		        trailzero = 0;
		        break;
		      }
		    ++trailzero;
		  }
		if (roundmode == FE_DEC_TONEAREST && trailzero &&
		  (digits[index-1] & 1) == 0) break;
		if (roundmode == FE_DEC_UPWARD && !trailzero) break;
		if (roundmode == FE_DEC_DOWNWARD && !trailzero) break;
		if (roundmode == 5 && trailzero) break;
		if (roundmode == 6 && trailzero) break;
	      }
	  
            while (digits[--index] == '9') digits[index] = '0';
            digits[index]++;
            if (index < n) { n--; sig++; }
          } while (0);
      }
    
    /* calculate decimal point, adjust prec and exp if necessary */
    if (spec == 'f')
      {
	decpt = n + sig + exp;
      }
    else if (spec == 'a' && -(prec+5) <= exp && exp <= 0 && exp+sig <= prec)
      {
	spec = 'f';
	prec -= exp+sig;
	decpt = n + sig + exp;
      }
    else if (spec == 'g' && -4 < exp+sig && exp+sig <= prec)
      {
	spec = 'f';
	prec -= exp+sig;
	decpt = n + sig + exp;
      }
    else
      {
        if (spec != 'e') prec--;
	exp += sig-1;
	decpt = n + 1;
      }

    /* remove trailing zeroes for %g */
    if (tolower(info->spec) == 'g')
      {
        while (prec > 0 && decpt+prec > len) prec--;
	while (prec > 0 && digits[decpt+prec-1] == '0') prec--;
      }

    /* remove trailing zeroes for %a, but only if they are not significant */
    if (tolower(info->spec) == 'a')
      {
        while (prec > 0 && decpt+prec > len) prec--;
	while (prec > 0 && decpt+prec > n+sig && digits[decpt+prec-1] == '0') prec--;
      }
      

    /* digits to the left of the decimal pt. */
    if (n < decpt)
      { 
        width -= decpt - n;
	if (grouping) width -= (decpt-n)/3;
      }
    else width--;  /* zero */
  
    /* digits to the right of the decimal pt. */
    if (prec > 0) width -= 1 + prec;
    else if (info->alt) width -= 1;
  
    if (spec != 'f')
      {
        width -= 3;
	if (0!=(exp/10) || spec!='a') --width;
	if (0!=(exp/100)) --width;
	if (0!=(exp/1000)) --width;
      }
  
    if (is_neg || info->showsign || info->space) width--;

    if (!info->left && info->pad != '0' && width > 0)
      PADN (info->pad, width);

    if (is_neg)
      outchar ('-');
    else if (info->showsign)
      outchar ('+');
    else if (info->space)
      outchar (' ');

    if (!info->left && info->pad == '0' && width > 0)
      PADN ('0', width);

  /* print zero, decimal point and leading zeroes if needed */
  if (decpt <= n)
    {
      outchar ('0');
      n = decpt;
      if (n < 0)
        {
          outchar (wide ? decimalwc : *decimal);
          while (n < 0 && n < decpt + prec)
	    {
              outchar ('0');
              n++;
            }
        }
    }
  /* print digits */
  while (n < len && n < decpt + prec)
    {
      if (n == decpt) 
        outchar (wide ? decimalwc : *decimal);
      else if (grouping && n < decpt && (decpt-n)%3 == 0)
        outchar (wide ? thousands_sepwc : *thousands_sep);
      outchar (digits[n]);
      n++;
    }
  /* print trailing zeroes */
  while (n < decpt + prec)
    {
      if (n == decpt) 
        outchar (wide ? decimalwc : *decimal);
      else if (grouping && n < decpt && (decpt-n)%3 == 0)
        outchar (wide ? thousands_sepwc : *thousands_sep);
      outchar ('0');
      n++;
    }
  /* print decimal point, if needed */
  if (n == decpt && info->alt) outchar (wide ? decimalwc : *decimal);
  
  
  if (spec != 'f')
   {
     outchar (isupper(info->spec) ? 'E' : 'e');
     if (exp < 0) 
       { outchar ('-'); n = -exp; }
     else
       { outchar ('+'); n = exp; }
     if (n >= 1000) outchar ('0'+((n/1000)%10)); 
     if (n >= 100) outchar ('0'+((n/100)%10));
     if (n >= 10 || spec!='a') outchar ('0'+((n/10)%10));
     outchar ('0'+(n%10));
 
   }
  if (info->left && width > 0)
    PADN (info->pad, width);
}  

   return 0;
}
libc_hidden_def (__printf_dfp)
