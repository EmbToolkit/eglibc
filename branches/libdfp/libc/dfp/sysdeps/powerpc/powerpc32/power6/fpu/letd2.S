/* Decimal Floating Point 128-bit compare >=.  P6 PowerPC32 version.
   Copyright (C) 2006,2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

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
   Software Foundation, Inc., 51 Franklin St - Fifth Floor, Boston,
   MA 02110-1301 USA  */

#include <sysdep.h>
#include <math_ldbl_opt.h>

	.machine	"power6"
/* int __dpd_letd2 (_Decimal128 x, _Decimal128 y)  */
ENTRY (__dpd_letd2)
	dcmpuq	cr0,fp2,fp4 	/* if ((x < y) && !unordered(x,y)) */
	li	r3, -1		/*   return -1  */
	bltlr	cr0		/* else	if ((x == y) && !unordered(x,y)) */
	li	r3, 0		/*   return 0  */
	beqlr	cr0		/* else	 */
	li	r3, 1		/*   return 1  */
	blr
	END (__dpd_letd2)
