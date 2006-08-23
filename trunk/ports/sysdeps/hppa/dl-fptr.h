/* Function descriptors.  HPPA version.
   Copyright (C) 2003 Free Software Foundation, Inc.
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

#ifndef dl_hppa_fptr_h
#define dl_hppa_fptr_h 1

#include <sysdeps/generic/dl-fptr.h>

/* There are currently 20 dynamic symbols in ld.so.
   ELF_MACHINE_BOOT_FPTR_TABLE_LEN needs to be at least that big.  */
#define ELF_MACHINE_BOOT_FPTR_TABLE_LEN	200

#define ELF_MACHINE_LOAD_ADDRESS(var, symbol)		\
  asm ("	addil LT%%" #symbol ", %%r19\n"		\
       "	ldw RT%%" #symbol "(%%sr0,%%r1), %0\n"	\
      : "=&r" (var));


#endif /* !dl_hppa_fptr_h */
