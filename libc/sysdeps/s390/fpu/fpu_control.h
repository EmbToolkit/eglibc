/* FPU control word definitions.  Stub version.
   Copyright (C) 2000 Free Software Foundation, Inc.
   Contributed by Denis Joseph Barrow (djbarrow@de.ibm.com) and
   Martin Schwidefsky (schwidefsky@de.ibm.com).
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
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#ifndef _FPU_CONTROL_H
# define _FPU_CONTROL_H

# include <features.h>

/* rounding control */
#define _FPU_RC_NEAREST 0x00   /* RECOMMENDED */
#define _FPU_RC_DOWN    0x03
#define _FPU_RC_UP      0x02
#define _FPU_RC_ZERO    0x01

/* masking of interrupts */
#define _FPU_MASK_ZM  0x40 /* zero divide */
#define _FPU_MASK_OM  0x20 /* overflow */
#define _FPU_MASK_UM  0x10 /* underflow */
#define _FPU_MASK_XM  0x08 /* inexact */
#define _FPU_MASK_IM  0x80 /* invalid operation */

/* These bits are reserved are not changed.  */
# define _FPU_RESERVED 0x070700FC

/* The fdlibm code requires no interrupts for exceptions.  Don't
   change the rounding mode, it would break long double I/O!  */
#define _FPU_DEFAULT  0x00000000 /* Default value.  */

/* Type of the control word.  */
typedef unsigned int fpu_control_t;

/* Macros for accessing the hardware control word.  */
#define _FPU_GETCW(cw)  __asm__ volatile ("efpc %0,0" : "=d" (cw))
#define _FPU_SETCW(cw)  __asm__ volatile ("sfpc  %0,0" : : "d" (cw))

/* Default control word set at startup.  */
extern fpu_control_t __fpu_control;

#endif /* _FPU_CONTROL_H */
