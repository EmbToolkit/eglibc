/* Function body to print DFP values in hex
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


/* The gmp headers need some configuration frobs.  */
/* #define HAVE_ALLOCA 1  */

#include "printf_dfp.h"
#include <unistd.h>

int
__printf_dfphex (FILE *fp,
		 const struct printf_info *info,
		 const void *const *args)
{
	write (1, "in __printf_dfphex\n", 19);
	return 0;
}
/* libc_hidden_def (__printf_dfphex) */
