/* Decimal Floating Point convert 32-bit to int.  P6 PowerPC64 version.
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
/* int __dpd_fixsdsi (_Decimal32 x)  */
ENTRY (__dpd_fixsdsi)
	dctdp	fp1,fp1	/* Convert x to _Decimal64.  */
	drintn	0,fp1,fp1,1	/* Preround to toward zero.  */
	dctfix	fp0,fp1 /* Convert x to integer.  */
	stfd	fp0,-8(r1)
	ori	r1,r1,0		/* Special group ending nop.  */
	oris	r4,0,0x8000 /* 0x0000000080000000  */
	lis	r5,0x8000 /* 0xffffffff80000000  */
	ld	r3,-8(r1)
/* The return is an int, but we have long long, so we need to force overflow
   if there are any significant bits in the high word or overflow (incorrect
   sign) from the low word.  */

	cmpd	cr0,r3,r4
	cmpd	cr7,r3,r5
	cmpdi	cr6,r3,0
	blt	cr1,L(negative)
	bltlr	cr0
L(posoverflow):
	addi	r3,r4,-1	/* return max positive int.  */
	blr
L(negative):		/* If (result >= min negative int */
	bgelr	cr7	/* return result */
L(negoverflow):		/* else */
	mr	r3,r5	/* return min negative int.  */
	blr
	END (__dpd_fixsdsi)
