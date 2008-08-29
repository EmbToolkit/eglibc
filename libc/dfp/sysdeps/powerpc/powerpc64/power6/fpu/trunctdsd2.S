/* Decimal Floating Point truncate 128-bit to 32-bit.
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
/* _Decimal32 __dpd_trunctdsd2 (_Decimal128 x)  */
ENTRY (__dpd_trunctdsd2)
	drdpq	fp0,fp2	/* Round result to _Decimal64. */
	drsp	fp1,fp0	/* Round result to _Decimal32. */
	blr
	END (__dpd_trunctdsd2)
