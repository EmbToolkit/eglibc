/* Decimal Floating Point convert 64-bit to unsigned long.  P6 PPC32 version.
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


	.section	.rodata.cst8,"aM",@progbits,8
	.align	3
.LC1:	/* 9223372036854775808.0DD */
	.long	0x6e45237c
	.long	0x836973f6
.LC2:	/* 18446744073709551616.0DD */
	.long	0x264a4cdd
	.long	0x2077c2dd
	.section	".text"

	.machine	"power6"
/* unsigned long __fixunsdddi (__decimal64 x)  */
ENTRY (__fixunsdddi)
	stwu	r1,-16(r1)
	cfi_adjust_cfa_offset (16)
#ifdef SHARED
	mflr	r11
	cfi_register(lr,r11)
# ifdef HAVE_ASM_PPC_REL16
	bcl	20,31,1f
1:	mflr	r9
	addis	r9,r9,.LC1-1b@ha
	addi	r9,r9,.LC1-1b@l
# else
	bl	_GLOBAL_OFFSET_TABLE_@local-4
	mflr	r10
	lwz	r9,.LC1@got(10)
# endif
	mtlr	r11
	cfi_same_value (lr)
	lfd	fp10,0(r9)
	lfd	fp11,.LC2-.LC1(r9)
#else
	lis	r9,.LC1@ha
	lis	r10,.LC2@ha
	lfd	fp10,.LC1@l(r9)
	lfd	fp11,.LC2@l(r10)
#endif
	drintn.	0,fp1,fp1,1	/* Preround to toward zero.  */
	dcmpu	cr0,fp1,fp10	/* check if > 2**63-1 */
	blt	cr1,L(negative)
	blt	cr0,L(poslong)
/* The return is an unsigned long, but "DFP convert to fixed" takes
   signed long, so we need to pre-adjust (-18446744073709551616.0DD)
   to get the final (signed) conversion result to be the correct	
   unsigned result.  */
	dsub	fp1,fp1,fp11
	dcmpu	cr0,fp1,fp10	/* if x still > 2**63-1 */
	li	r3,-1		/* return max_unsigned_long */
	blt	cr0,L(done)	/* else */
L(poslong):
	dctfix	fp0,fp1 /* Convert x to integer.  */
	stfd	fp0,8(r1)
	ori	r1,r1,0		/* Special group ending nop.  */
	lwz	r3,8(r1)
	lwz	r4,12(r1)
	addi	r1,r1,16
	blr
L(negative):
	li	r3,0	/* return 0 for negative floats.  */
L(done):
	mr	r4,r3
	addi	r1,r1,16
	blr
	END (__fixunsdddi)

