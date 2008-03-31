/* Convert string representing a number to Decimal Float value, using given locale.
   Copyright (C) 1997,1998,2002,2004-2006 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   Contributed by IBM Corporation.
   Adapted primarily from stdlib/strtod_l.c by Ulrich Drepper <drepper@cygnus.com>
   Author(s): Joseph Kerian <jkerian@us.ibm.com>

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

/* 
 * TODO: SET_MANTISSA macro for preserving NaN info (or parse as mantissa)
 * TODO: Check that hexadecimal input is done properly... particularly hex
 * exponants
 */
#include <stdio.h>
#include <xlocale.h>
#include <ctype.h>
#include <errno.h>
#include "../locale/localeinfo.h"
#include <locale.h>
#include <string.h>

#include <math.h>
#include <float.h>

#ifndef FLOAT
# define FLOAT		_Decimal32
# define FLOAT_HUGE_VAL	HUGE_VAL_D32
# define FLOAT_SIZE	32
# define FLT		DEC32
# define FLOAT_ZERO	0.0DF
# define SET_MANTISSA(x,y)
#endif

/* We use this code for the extended locale handling where the
   function gets as an additional argument the locale which has to be
   used.  To access the values we have to redefine the _NL_CURRENT and
   _NL_CURRENT_WORD macros.  */
#undef _NL_CURRENT
#define _NL_CURRENT(category, item) \
  (current->values[_NL_ITEM_INDEX (item)].string)
#undef _NL_CURRENT_WORD
#define _NL_CURRENT_WORD(category, item) \
  ((uint32_t) current->values[_NL_ITEM_INDEX (item)].word)

#if defined _LIBC || defined HAVE_WCHAR_H
# include <wchar.h>
# include <dfpwchar.h> /* wcstod* internal interfaces */
#endif

#ifdef USE_WIDE_CHAR
extern unsigned long long int ____wcstoull_l_internal (const wchar_t *, wchar_t **,
						       int, int, __locale_t);
# include <wctype.h>
# define STRTO_PREFIX wcsto
# define STRING_TYPE wchar_t
# define CHAR_TYPE wint_t
# define L_(Ch) L##Ch
# define ISSPACE(Ch) __iswspace_l ((Ch), loc)
# define ISDIGIT(Ch) __iswdigit_l ((Ch), loc)
# define ISXDIGIT(Ch) __iswxdigit_l ((Ch), loc)
# define TOLOWER(Ch) __towlower_l ((Ch), loc)
# define TOLOWER_C(Ch) __towlower_l ((Ch), _nl_C_locobj_ptr)
# define STRNCASECMP(S1, S2, N) \
  __wcsncasecmp_l ((S1), (S2), (N), _nl_C_locobj_ptr)
# define STRTOULL(S, E, B) ____wcstoull_l_internal ((S), (E), (B), 0, loc)
#else
# include <dfpstdlib.h> /* strtod* internal interfaces.  */
# define STRTO_PREFIX strto
# define STRING_TYPE char
# define CHAR_TYPE char
# define L_(Ch) Ch
# define ISSPACE(Ch) __isspace_l ((Ch), loc)
# define ISDIGIT(Ch) __isdigit_l ((Ch), loc)
# define ISXDIGIT(Ch) __isxdigit_l ((Ch), loc)
# define TOLOWER(Ch) __tolower_l ((Ch), loc)
# define TOLOWER_C(Ch) __tolower_l ((Ch), _nl_C_locobj_ptr)
# define STRNCASECMP(S1, S2, N) \
  __strncasecmp_l ((S1), (S2), (N), _nl_C_locobj_ptr)
# define STRTOULL(S, E, B) ____strtoull_l_internal ((S), (E), (B), 0, loc)
#endif

/* Constants we need from float.h; select the set for the FLOAT precision.  */
#define MANT_DIG	PASTE(PASTE(__,FLT),_MANT_DIG__)
#define DIG		PASTE(PASTE(__,FLT),_DIG__)
//#define MAX_EXP		PASTE(FLT,_MAX_EXP)
//#define MIN_EXP		PASTE(FLT,_MIN_EXP)
#define MAX_10_EXP	PASTE(PASTE(__,FLT),_MAX_EXP__)
#define MIN_10_EXP	PASTE(PASTE(__,FLT),_MIN_EXP__)
#define FUNCTION_NAME	PASTE(PASTE(STRTO_PREFIX,d),FLOAT_SIZE)
#define __FUNCTION_NAME	PASTE(__,FUNCTION_NAME)
#define FUNCTION_INTERNAL	PASTE(__FUNCTION_NAME,_internal)
#define FUNCTION_L_INTERNAL	PASTE(__FUNCTION_NAME,_l_internal)

/* Extra macros required to get FLT expanded before the pasting.  */
#define PASTE(a,b)	PASTE1(a,b)
#define PASTE1(a,b)	a##b


#define RETURN(val,end)							      \
    do { if (endptr != NULL) *endptr = (STRING_TYPE *) (end);		      \
	 return val; } while (0)

#define NDEBUG 1
#include <assert.h>

#include "stdlib/grouping.h"

/* This is of the form __strtod32_l_internal() */
FLOAT
FUNCTION_L_INTERNAL (const STRING_TYPE * nptr, STRING_TYPE ** endptr,
		int group, locale_t loc)
{
  FLOAT d32 = FLOAT_ZERO;

  int negative;			/* The sign of the number.  */
  int exponent;			/* Exponent of the number.  */

  /* Numbers starting `0X' or `0x' have to be processed with base 16.  */
  int base = 10;

  /* Number of bits currently in result value.  */
  int bits;

  /* Running pointer after the last character processed in the string.  */
  const STRING_TYPE *cp, *tp;
  /* Start of significant part of the number.  */
  const STRING_TYPE *startp, *start_of_digits;
  /* Points at the character following the integer and fractional digits.  */
  const STRING_TYPE *expp;
  /* Total number of digit and number of digits in integer part.  */
  int dig_no, int_no, lead_zero;
  /* Contains the last character read.  */
  CHAR_TYPE c;

/* We should get wint_t from <stddef.h>, but not all GCC versions define it
   there.  So define it ourselves if it remains undefined.  */
#ifndef _WINT_T
  typedef unsigned int wint_t;
#endif
  /* The radix character of the current locale.  */
#ifdef USE_WIDE_CHAR
  wchar_t decimal;
#else
  const char *decimal;
  size_t decimal_len;
#endif
  /* The thousands character of the current locale.  */
#ifdef USE_WIDE_CHAR
  wchar_t thousands = L'\0';
#else
  const char *thousands = NULL;
  /* Used in several places.  */
  int cnt;
#endif
  /* The numeric grouping specification of the current locale,
     in the format described in <locale.h>.  */
  const char *grouping;

  struct locale_data *current = loc->__locales[LC_NUMERIC];

  if (group)
    {
      grouping = _NL_CURRENT (LC_NUMERIC, GROUPING);
      if (*grouping <= 0 || *grouping == CHAR_MAX)
	grouping = NULL;
      else
	{
	  /* Figure out the thousands separator character.  */
#ifdef USE_WIDE_CHAR
	  thousands = _NL_CURRENT_WORD (LC_NUMERIC,
					_NL_NUMERIC_THOUSANDS_SEP_WC);
	  if (thousands == L'\0')
	    grouping = NULL;
#else
	  thousands = _NL_CURRENT (LC_NUMERIC, THOUSANDS_SEP);
	  if (*thousands == '\0')
	    {
	      thousands = NULL;
	      grouping = NULL;
	    }
#endif
	}
    }
  else
    grouping = NULL;

  /* Find the locale's decimal point character.  */
#ifdef USE_WIDE_CHAR
  decimal = _NL_CURRENT_WORD (LC_NUMERIC, _NL_NUMERIC_DECIMAL_POINT_WC);
  assert (decimal != L'\0');
# define decimal_len 1
#else
  decimal = _NL_CURRENT (LC_NUMERIC, DECIMAL_POINT);
  decimal_len = strlen (decimal);
  assert (decimal_len > 0);
#endif

  /* Prepare number representation.  */
  exponent = 0;
  negative = 0;
  bits = 0;

  /* Parse string to get maximal legal prefix.  We need the number of
     characters of the integer part, the fractional part and the exponent.  */
  cp = nptr - 1;
  /* Ignore leading white space.  */
  do
    c = *++cp;
  while (ISSPACE (c));

  /* Get sign of the result.  */
  if (c == L_('-'))
    {
      negative = 1;
      c = *++cp;
    }
  else if (c == L_('+'))
    c = *++cp;

  /* Return 0.0 if no legal string is found.
     No character is used even if a sign was found.  */
#ifdef USE_WIDE_CHAR
  if (c == (wint_t) decimal
      && (wint_t) cp[1] >= L'0' && (wint_t) cp[1] <= L'9')
    {
      /* We accept it.  This funny construct is here only to indent
	 the code directly.  */
    }
#else
  for (cnt = 0; decimal[cnt] != '\0'; ++cnt)
    if (cp[cnt] != decimal[cnt])
      break;
  if (decimal[cnt] == '\0' && cp[cnt] >= '0' && cp[cnt] <= '9')
    {
      /* We accept it.  This funny construct is here only to indent
	 the code directly.  */
    }
#endif
  else if (c < L_('0') || c > L_('9'))
    {
      /* Check for `INF' or `INFINITY'.  */
      if (TOLOWER_C (c) == L_('i') && STRNCASECMP (cp, L_("inf"), 3) == 0)
	{
	  /* Return +/- infinity.  */
	  if (endptr != NULL)
	    *endptr = (STRING_TYPE *)
		      (cp + (STRNCASECMP (cp + 3, L_("inity"), 5) == 0
			     ? 8 : 3));

	  return negative ? -FLOAT_HUGE_VAL : FLOAT_HUGE_VAL;
	}

      if (TOLOWER_C (c) == L_('n') && STRNCASECMP (cp, L_("nan"), 3) == 0)
	{
	  /* Return NaN.  */
	  FLOAT retval = DEC_NAN;

	  cp += 3;

	  /* Match `(n-char-sequence-digit)'.  */
	  if (*cp == L_('('))
	    {
	      startp = cp;
	      do
		++cp;
	      while ((*cp >= L_('0') && *cp <= L_('9'))
		     || (TOLOWER (*cp) >= L_('a') && TOLOWER (*cp) <= L_('z'))
		     || *cp == L_('_'));

	      if (*cp != L_(')'))
		/* The closing brace is missing.  Only match the NAN
		   part.  */
		cp = startp;
	      else
		{
		  /* This is a system-dependent way to specify the
		     bitmask used for the NaN.  We expect it to be
		     a number which is put in the mantissa of the
		     number.  */
		  STRING_TYPE *endp;
		  unsigned long long int mant;

		  mant = STRTOULL (startp + 1, &endp, 0);
		  if (endp == cp)
		    SET_MANTISSA (retval, mant);
		}
	    }

	  if (endptr != NULL)
	    *endptr = (STRING_TYPE *) cp;

	  return retval;
	}

      /* It is really a text we do not recognize.  */
      RETURN (0.0, nptr);
    }

  /* First look whether we are faced with a hexadecimal number.  */
  if (c == L_('0') && TOLOWER (cp[1]) == L_('x'))
    {
      /* Okay, it is a hexa-decimal number.  Remember this and skip
	 the characters.  BTW: hexadecimal numbers must not be
	 grouped.  */
      base = 16;
      cp += 2;
      c = *cp;
      grouping = NULL;
    }

  /* Record the start of the digits, in case we will check their grouping.  */
  start_of_digits = startp = cp;

  /* Ignore leading zeroes.  This helps us to avoid useless computations.  */
#ifdef USE_WIDE_CHAR
  while (c == L'0' || ((wint_t) thousands != L'\0' && c == (wint_t) thousands))
    c = *++cp;
#else
  if (thousands == NULL)
    while (c == '0')
      c = *++cp;
  else
    {
      /* We also have the multibyte thousands string.  */
      while (1)
	{
	  if (c != '0')
	    {
	      for (cnt = 0; thousands[cnt] != '\0'; ++cnt)
		if (c != thousands[cnt])
		  break;
	      if (thousands[cnt] != '\0')
		break;
	    }
	  c = *++cp;
	}
    }
#endif

  /* If no other digit but a '0' is found the result is 0.0.
     Return current read pointer.  */
  if ((c < L_('0') || c > L_('9'))
      && (base == 16 && (c < (CHAR_TYPE) TOLOWER (L_('a'))
			 || c > (CHAR_TYPE) TOLOWER (L_('f'))))
#ifdef USE_WIDE_CHAR
      && c != (wint_t) decimal
#else
      && ({ for (cnt = 0; decimal[cnt] != '\0'; ++cnt)
	      if (decimal[cnt] != cp[cnt])
		break;
	    decimal[cnt] != '\0'; })
#endif
      && (base == 16 && (cp == start_of_digits
			 || (CHAR_TYPE) TOLOWER (c) != L_('p')))
      && (base != 16 && (CHAR_TYPE) TOLOWER (c) != L_('e')))
    {
#ifdef USE_WIDE_CHAR
      tp = __correctly_grouped_prefixwc (start_of_digits, cp, thousands,
					 grouping);
#else
      tp = __correctly_grouped_prefixmb (start_of_digits, cp, thousands,
					 grouping);
#endif
      /* If TP is at the start of the digits, there was no correctly
	 grouped prefix of the string; so no number found.  */
      RETURN (negative ? -FLOAT_ZERO : FLOAT_ZERO,
              tp == start_of_digits ? (base == 16 ? cp - 1 : nptr) : tp);
    }

  /* Remember first significant digit and read following characters until the
     decimal point, exponent character or any non-FP number character.  */
  startp = cp;
  dig_no = 0;
  while (1)
    {
      if ((c >= L_('0') && c <= L_('9'))
	  || (base == 16 && (wint_t) TOLOWER (c) >= L_('a')
	      && (wint_t) TOLOWER (c) <= L_('f')))
	++dig_no;
      else
	{
#ifdef USE_WIDE_CHAR
	  if ((wint_t) thousands == L'\0' || c != (wint_t) thousands)
	    /* Not a digit or separator: end of the integer part.  */
	    break;
#else
	  if (thousands == NULL)
	    break;
	  else
	    {
	      for (cnt = 0; thousands[cnt] != '\0'; ++cnt)
		if (thousands[cnt] != cp[cnt])
		  break;
	      if (thousands[cnt] != '\0')
		break;
	    }
#endif
	}
      c = *++cp;
    }

  if (grouping && dig_no > 0)
    {
      /* Check the grouping of the digits.  */
#ifdef USE_WIDE_CHAR
      tp = __correctly_grouped_prefixwc (start_of_digits, cp, thousands,
					 grouping);
#else
      tp = __correctly_grouped_prefixmb (start_of_digits, cp, thousands,
					 grouping);
#endif
      if (cp != tp)
	{
	  /* Less than the entire string was correctly grouped.  */

	  if (tp == start_of_digits)
	    /* No valid group of numbers at all: no valid number.  */
	    RETURN (FLOAT_ZERO, nptr);

	  if (tp < startp)
	    /* The number is validly grouped, but consists
	       only of zeroes.  The whole value is zero.  */
	    RETURN (negative ? -FLOAT_ZERO : FLOAT_ZERO, tp);

	  /* Recompute DIG_NO so we won't read more digits than
	     are properly grouped.  */
	  cp = tp;
	  dig_no = 0;
	  for (tp = startp; tp < cp; ++tp)
	    if (*tp >= L_('0') && *tp <= L_('9'))
	      ++dig_no;

	  int_no = dig_no;
	  lead_zero = 0;

	  goto number_parsed;
	}
    }

  /* We have the number digits in the integer part.  Whether these are all or
     any is really a fractional digit will be decided later.  */
  int_no = dig_no;
  lead_zero = int_no == 0 ? -1 : 0;

  /* Read the fractional digits.  A special case are the 'american style'
     numbers like `16.' i.e. with decimal but without trailing digits.  */
  if (
#ifdef USE_WIDE_CHAR
      c == (wint_t) decimal
#else
      ({ for (cnt = 0; decimal[cnt] != '\0'; ++cnt)
	   if (decimal[cnt] != cp[cnt])
	     break;
	 decimal[cnt] == '\0'; })
#endif
      )
    {
      cp += decimal_len;
      c = *cp;
      while ((c >= L_('0') && c <= L_('9')) ||
	     (base == 16 && TOLOWER (c) >= L_('a') && TOLOWER (c) <= L_('f')))
	{
	  if (c != L_('0') && lead_zero == -1)
	    lead_zero = dig_no - int_no;
	  ++dig_no;
	  c = *++cp;
	}
    }

  /* Remember start of exponent (if any).  */
  expp = cp;

  /* Read exponent.  */
  if ((base == 16 && TOLOWER (c) == L_('p'))
      || (base != 16 && TOLOWER (c) == L_('e')))
    {
      int exp_negative = 0;

      c = *++cp;
      if (c == L_('-'))
	{
	  exp_negative = 1;
	  c = *++cp;
	}
      else if (c == L_('+'))
	c = *++cp;

      if (c >= L_('0') && c <= L_('9'))
	{
	  int exp_limit;

	  /* Get the exponent limit. */
#if 0
	  if (base == 16)
	    exp_limit = (exp_negative ?
			 -MIN_EXP + MANT_DIG + 4 * int_no :
			 MAX_EXP - 4 * int_no + lead_zero);
	  else
#endif
	    exp_limit = (exp_negative ?
			 -MIN_10_EXP + MANT_DIG + int_no :
			 MAX_10_EXP - int_no + lead_zero);

	  do
	    {
	      exponent *= 10;

	      if (exponent > exp_limit)
		/* The exponent is too large/small to represent a valid
		   number.  */
		{
		  FLOAT result;

		  /* We have to take care for special situation: a joker
		     might have written "0.0e100000" which is in fact
		     zero.  */
		  if (lead_zero == -1)
		    result = negative ? -FLOAT_ZERO : FLOAT_ZERO;
		  else
		    {
		      /* Overflow or underflow.  */
		      __set_errno (ERANGE);
		      result = (exp_negative ? FLOAT_ZERO :
				negative ? -FLOAT_HUGE_VAL : FLOAT_HUGE_VAL);
		    }

		  /* Accept all following digits as part of the exponent.  */
		  do
		    ++cp;
		  while (*cp >= L_('0') && *cp <= L_('9'));

		  RETURN (result, cp);
		  /* NOTREACHED */
		}

	      exponent += c - L_('0');
	      c = *++cp;
	    }
	  while (c >= L_('0') && c <= L_('9'));

	  if (exp_negative)
	    exponent = -exponent;
	}
      else
	cp = expp;
    }


      printf("lead_zero=%d dig_no=%d int_no=%d exponent=%d\n", 
              lead_zero, dig_no, int_no, exponent);

  /* We don't want to have to work with trailing zeroes after the radix.  */
  if (dig_no > int_no)
    {
      while (expp[-1] == L_('0'))
	{
	  --expp;
	  --exponent;
	  --dig_no;
	}
      assert (dig_no >= int_no);
    }

  if (dig_no == int_no && dig_no > 0 && exponent < 0)
    do
      {
	while (! (base == 16 ? ISXDIGIT (expp[-1]) : ISDIGIT (expp[-1])))
	  --expp;

	if (expp[-1] != L_('0'))
	  break;

	--expp;
	--dig_no;
	--int_no;
	++exponent;
      }
    while (dig_no > 0 && exponent < 0);

 number_parsed:

  /* The whole string is parsed.  Store the address of the next character.  */
  if (endptr)
    *endptr = (STRING_TYPE *) cp;

  if (dig_no == 0)
    {
      printf("lead_zero=%d dig_no=%d int_no=%d exponent=%d\n", 
              lead_zero, dig_no, int_no, exponent);


      if (exponent != 0)
        return negative ? -FLOAT_ZERO : FLOAT_ZERO;


      d32 += 1;
      while(exponent-- > 0)
	d32 *= 10;
      while(++exponent < 0)
	d32 /= 10;

      d32 -= d32;
      return negative ? -d32 : d32;
    }


  if (lead_zero)
    {
      /* Find the decimal point */
#ifdef USE_WIDE_CHAR
      while (*startp != decimal)
	++startp;
#else
      while (1)
	{
	  if (*startp == decimal[0])
	    {
	      for (cnt = 1; decimal[cnt] != '\0'; ++cnt)
		if (decimal[cnt] != startp[cnt])
		  break;
	      if (decimal[cnt] == '\0')
		break;
	    }
	  ++startp;
	}
#endif
      startp += lead_zero + decimal_len;
      exponent -= base == 16 ? 4 * lead_zero : lead_zero;
      dig_no -= lead_zero;
    }

  /* Now we have the number of digits in total and the integer digits as well
     as the exponent and its sign.  We can decide whether the read digits are
     really integer digits or belong to the fractional part; i.e. we normalize
     123e-2 to 1.23.  */
  {
    register int incr = (exponent < 0 ? MAX (-int_no, exponent)
			 : MIN (dig_no - int_no, exponent));
    int_no += incr;
    exponent -= incr;
  }

  if (int_no + exponent > MAX_10_EXP + 1)
    {
      __set_errno (ERANGE);
      return negative ? -FLOAT_HUGE_VAL : FLOAT_HUGE_VAL;
    }

  if (exponent < MIN_10_EXP - (MANT_DIG + 1))
    {
      __set_errno (ERANGE);
      return FLOAT_ZERO;
    }
  /* Read in the integer portion of the input string */
  if (int_no > 0)
    {
      /* Read the integer part as a d32.  */
      int digcnt = int_no;

      while (int_no > MAX_10_EXP + 1)
	{
	  digcnt--;
	  exponent++;
	}
      do
	{
	  /* There might be thousands separators or radix characters in
	    the string.  But these all can be ignored because we know the
	    format of the number is correct and we have an exact number
	    of characters to read.  */
#ifdef USE_WIDE_CHAR
	  if (*startp < L_('0') || *startp > L_('9'))
	    if (base==10 || (*startp < L_('a') || *startp > L_('h')))
	      ++startp;
#else
	  if (*startp < L_('0') || *startp > L_('9'))
	    if (base==10 || (*startp < L_('a') || *startp > L_('h')))
	      {
		int inner = 0;
		if (thousands != NULL && *startp == *thousands
		    && ({ for (inner = 1; thousands[inner] != '\0'; ++inner)
			if (thousands[inner] != startp[inner])
			  break;
			thousands[inner] == '\0'; }))
		  startp += inner;
		else
		  startp += decimal_len;
	      }
#endif
	  if(base == 10)
	    d32 = d32 * base + *startp - L_('0');
	  else
	    d32 = d32 * base + (*startp >= L_('0') && *startp <= L_('9') ?
			-L_('0') : 10-L_('a')) + *startp;
	  ++startp;
	}
      while (--digcnt > 0);

    }
  /* If we haven't filled our datatype, read in the fractional digits */
  if (int_no <= MANT_DIG && dig_no > int_no)
    {
      /* Read the decimal part as a FLOAT.  */
      int digcnt = dig_no - int_no;
      FLOAT frac = FLOAT_ZERO;

  /* There might be radix characters in
	    the string.  But these all can be ignored because we know the
	    format of the number is correct and we have an exact number
	    of characters to read.  */
#ifdef USE_WIDE_CHAR
      if (*startp < L_('0') || *startp > L_('9'))
	++startp;
#else
      if (*startp < '0' || *startp > '9')
	startp += decimal_len;
#endif

      do
	{
	  if(base == 10)
	    frac = frac/10 + *(startp+digcnt-1) - L_('0');
	  else
	    frac = frac/10 + (*(startp+digcnt-1) >= L_('0') && 
		*(startp+digcnt-1) <= L_('9') ? -L_('0') : 10-L_('a'))
		+ *(startp+digcnt-1);
	}
      while (--digcnt > 0);
      frac /= 10;

      d32 += frac;
    }

  while(exponent-- > 0)
    d32 *= 10;
  while(++exponent < 0)
    d32 /= 10;

  return negative? -d32:d32;
}

/* This is of the form __strtod32_internal() */
FLOAT
FUNCTION_INTERNAL (const STRING_TYPE *nptr, STRING_TYPE **endptr, int group)
{
  return FUNCTION_L_INTERNAL (nptr,endptr,group,_NL_CURRENT_LOCALE);
}

/*#if defined _LIBC
libc_hidden_def (FUNCTION_INTERNAL)
#endif*/

/* This is of the form strtod32() */
FLOAT
#ifdef weak_function
weak_function
#endif
FUNCTION_NAME (const STRING_TYPE *nptr, STRING_TYPE **endptr)
{
  return FUNCTION_L_INTERNAL(nptr, endptr, 0, _NL_CURRENT_LOCALE);
}

libc_hidden_def (FUNCTION_INTERNAL)
