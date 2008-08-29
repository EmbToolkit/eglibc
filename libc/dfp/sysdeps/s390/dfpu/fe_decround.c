/* Return current rounding direction.
   Copyright (C) 2000, 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Andreas Krebbel  <Andreas.Krebbel@de.ibm.com>

   Based on the binary floating point variants contributed
   by Denis Joseph Barrow (djbarrow@de.ibm.com).

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
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#include <fenv_libc.h>
#include <fpu_control.h>

int
__fe_dec_getround (void)
{
  fexcept_t cw;

  _FPU_GETCW (cw);

  return (cw & FPC_DFP_RM_MASK) >> 4;
}
strong_alias(__fe_dec_getround, fe_dec_getround)

int
__fe_dec_setround (int round)
{
  if ((round|FPC_DFP_RM_MASK) != FPC_DFP_RM_MASK
      || (round > FE_DEC_TONEARESTFROMZERO))
    {
      /* ROUND is not a valid rounding mode.  */
      return 1;
    }
  __asm__ volatile ("srnmt 0(%0)"
		 		     :
		 		     : "a" (round << 4));

  return 0;
}
strong_alias(__fe_dec_setround, fe_dec_setround)
