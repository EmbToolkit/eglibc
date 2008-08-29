/* Decimal Floating Point convert 64-bit to long.  P6 PowerPC64 version.
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
/* long __dpd_fixdddi (_Decimal64 x)       */
/* long long __dpd_fixdddi (_Decimal64 x)  */
ENTRY (__dpd_fixdddi)
	drintn	0,fp1,fp1,1	/* Preround to toward zero.  */
	dctfix	fp0,fp1		/* Convert x to integer.  */
	stfd	fp0,-8(r1)
	ori	r1,r1,0		/* Special group ending nop.  */
	ld	r3,-8(r1)
	blr
	END (__dpd_fixdddi)
