/* Decimal Floating Point convert 32-bit to unsigned int.
   POWER6 PowerPC64 version.
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
/* unsigned int __dpd_fixunssdsi (_Decimal32 x)  */
ENTRY (__dpd_fixunssdsi)
	dctdp	fp1,fp1	/* Convert x to _Decimal64.  */
	drintn	0,fp1,fp1,1	/* Preround to toward zero.  */
	dctfix	fp0,fp1 /* Convert x to integer.  */
	stfd	fp0,-8(r1)
	ori	r1,r1,0		/* Special group ending nop.  */
	oris	r4,0,0xffff /* 0x00000000ffff0000  */
	ori	r4,r4,0xffff /* 0x00000000ffffffff  */
	ld	r3,-8(r1)
/* The return is an unsigned int, but we have long long, so we need to force
   overflow if there are any significant bits in the high word or return
   zero if negative.  */
	cmpld	cr6,r3,r4
	blt	cr1,L(negative)
	blelr	cr6
L(posoverflow):
	mr	r3,r4	/* return max unsigned int.  */
	blr
L(negative):
	li	r3,0	/* return 0 for negative floats.  */
	blr
	END (__dpd_fixunssdsi)
