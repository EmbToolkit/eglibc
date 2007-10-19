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

/* This defines make it possible to use the same code for GNU C library and
   the GNU I/O library.	 */
#define PUT(f, s, n) _IO_sputn (f, s, n)
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

#define DECIMAL_PRINTF_BUF_SIZE 65 /* ((DECIMAL128_PMAX + 14) * 2) + 1  */
/* TODO: add wide character support */

int
__printf_dfp (FILE *fp,
	      const struct printf_info *info,
	      const void *const *args)
{
	char str[DECIMAL_PRINTF_BUF_SIZE];
	const char *str_ptr = str;

	int wide = info->wide;
	wchar_t *wbuffer = NULL;
	int buffer_malloced = 0;  /* PRINT macro uses this.  */
	/* Counter for number of written characters.	*/
	int done = 0;
	int len = 0;

	if (info->is_short) /* %H  */
	  {
	   __fmt_d32 (info, args, str, DECIMAL_PRINTF_BUF_SIZE);
	  }
	else if (info->is_long_double) /* %DD  */
	  {
	   __fmt_d128 (info, args, str, DECIMAL_PRINTF_BUF_SIZE);
	  }
	else /* %D  */
	  {
	   __fmt_d64 (info, args, str, DECIMAL_PRINTF_BUF_SIZE);
	  }
	len=strlen(str);
	PRINT(str_ptr, wbuffer, len);

	return 0;
}
libc_hidden_def (__printf_dfp)
