/* Wide character string-to-decimal conversion function prototypes

   Copyright (C) 2006 IBM Corporation.

   Author(s): Joseph Kerian <jkerian@us.ibm.com>

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

#ifndef	_DFPWCHAR_H
#define	_DFPWCHAR_H	1

extern _Decimal32 __wcstod32_internal (const wchar_t * __restrict nptr, wchar_t ** __restrict endptr, int group);
extern _Decimal64 __wcstod64_internal (const wchar_t * __restrict nptr, wchar_t ** __restrict endptr, int group);
extern _Decimal128 __wcstod128_internal (const wchar_t * __restrict nptr, wchar_t ** __restrict endptr, int group);

libc_hidden_proto (__wcstod32_internal)
libc_hidden_proto (__wcstod64_internal)
libc_hidden_proto (__wcstod128_internal)

#endif /* _DFPWCHAR_H  */

