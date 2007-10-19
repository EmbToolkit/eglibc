/* Convert unsigned long to Decimal Floating Point 32-bit.
   POWER6 PowerPC64 version.
   Copyright (C) 2006 Free Software Foundation, Inc.
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

	.section	".toc","aw"
.LC1:	/* 9223372036854775808.0DD */
	.tc FD_6e45237c_836973f6[TC],0x6e45237c836973f6
	.section	".text"

	.machine	"power6"
/* __decimal32 __floatunsdisd (unsigned long x)  */
ENTRY (__floatunsdisd)
	cmpdi	cr0,r3,0
	std	r3,-8(r1)
	ori	r1,r1,0		/* Special group ending nop.  */
	lfd	fp0,-8(r1)
	blt	cr0,L(negative)
	dcffix	fp1,fp0 /* Convert x to decimal floatuns.  */
	drsp	fp1,fp1	/* Round result to __decimal32. */
	blr
/* we need to do more here. The function converts a unsigned long, but
   the dcffix instruction provides a signed conversion.  So we force
   the binary to be positive by clearing the sign bit before we convert
   to decimal.  Then we add 9223372036854775808.0DD to the result of the
   dcffix.  This gives the decimal equivalent to the full 64-bit value.  */
L(negative):
	fabs	fp0,fp0
	lfd	fp10,.LC1@toc(2)
	dcffix	fp1,fp0 /* Convert x to decimal float.  */
	dadd	fp1,fp1,fp10
	drsp	fp1,fp1	/* Round result to __decimal32. */
	blr
	END (__floatunsdisd)
