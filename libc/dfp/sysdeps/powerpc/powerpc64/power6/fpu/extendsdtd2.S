/* Decimal Floating Point extend 32-bit to 128-bit.  P6 PowerPC64 version.
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
/* _Decimal128 __dpd_extendsdtd2 (_Decimal32 x)  */
ENTRY (__dpd_extendsdtd2)
	dctdp	fp1,fp1	/* Convert x to _Decimal64. */
	dctqpq	fp2,fp1	/* Convert x to _Decimal128. */
	blr
	END (__dpd_extendsdtd2)
