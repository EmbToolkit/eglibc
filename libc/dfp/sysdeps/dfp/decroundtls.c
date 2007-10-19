/* Decimal Float Rounding Mode accessor function definition and TLS variable.
   Copyright (C) 2006 IBM Corporation.

   Author(s): Ryan S. Arnold <rsa@us.ibm.com>

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

#include <tls.h>
#include <fenv.h>
#include <decroundtls.h>

__thread int __dec_round_mode attribute_tls_model_ie = FE_DEC_TONEAREST;

int *__decrm_location (void)
{
  return &__dec_round_mode;
}
libc_hidden_def (__decrm_location)
