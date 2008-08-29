/* Decimal Floating Point convert 128-bit to unsigned int.
   POWER6 PowerPC32 version.
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
/* unsigned int __dpd_fixunstdsi (_Decimal128 x)   */
/* unsigned long __dpd_fixunstdsi (_Decimal128 x)  */
ENTRY (__dpd_fixunstdsi)
	stwu	r1,-16(r1)
	cfi_adjust_cfa_offset (16)
	drintnq	0,fp2,fp2,1	/* Preround to toward zero.  */
	dctfixq	fp0,fp2 /* Convert x to integer.  */
	stfd	fp0,8(r1)
	ori	r1,r1,0		/* Special group ending nop.  */
	lwz	r0,8(r1)
	lwz	r3,12(r1)
/* The return is an int, but we have long long, so we need to force overflow
   if there are any significant bits in the high word or overflow (incorrect
   sign) from the low word.  */
	cmpwi	cr0,r0,0
	cmpli	cr6,r3,0 /* Logical form to cmp unsigned.  */
	blt	cr0,L(negative)
	bne	cr0,L(posoverflow)
	bge	cr6,L(done)
L(posoverflow):
	li	r3,-1	/* return max unsigned int.  */
	b	L(done)
L(negative):
	lis	r3,0	/* return 0 for negative floats.  */
L(done):
	addi	r1,r1,16
	blr
	END (__dpd_fixunsddsi)

