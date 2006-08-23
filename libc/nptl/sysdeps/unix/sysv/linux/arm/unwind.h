/* Exception handling and frame unwind runtime interface routines.
   Copyright (C) 2005 Free Software Foundation, Inc.

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

#ifndef _ARM_UNWIND_H
#define _ARM_UNWIND_H	1

#include <sysdeps/generic/unwind.h>

/* Call the SjLj versions of these functions.  */
#define _Unwind_ForcedUnwind _Unwind_SjLj_ForcedUnwind
#define _Unwind_Resume _Unwind_SjLj_Resume
#define __gcc_personality_v0 __gcc_personality_sj0

/* After processing a context during forced unwinding, we must discard
   the context from the SjLj unwind stack, or we will encounter it again
   after the next call to __pthread_unwind_next.  When we return
   _URC_INSTALL_CONTEXT this happens transparently, but not when we
   longjmp to a C handler.  */

struct _Unwind_Context
{
  struct SjLj_Function_Context *fc;
};

#define ARCH_UNWIND_CLEANUP(CONTEXT) _Unwind_SjLj_Unregister ((CONTEXT)->fc)

#endif	/* unwind.h */
