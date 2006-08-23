/* Copyright (C) 2003, 2004 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Phil Blundell <pb@nexus.co.uk>, 2003.

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

#include <sysdep.h>
#include <tls.h>
#ifndef __ASSEMBLER__
# include <nptl/pthreadP.h>
#endif

#if !defined NOT_IN_libc || defined IS_IN_libpthread || defined IS_IN_librt

# undef PSEUDO_RET
# define PSEUDO_RET						        \
  ldrcc pc, [sp], $4;						        \
  ldr	lr, [sp], $4;							\
  b PLTJMP(SYSCALL_ERROR)

#   define PSEUDO_RET_MOV						\
  RETINSTR(cc, lr);							\
  b PLTJMP(SYSCALL_ERROR)

# undef PSEUDO
# define PSEUDO(name, syscall_name, args)				\
  .section ".text";							\
  .type __##syscall_name##_nocancel,%function;				\
  .globl __##syscall_name##_nocancel;					\
  __##syscall_name##_nocancel:						\
    DO_CALL (syscall_name, args);					\
    PSEUDO_RET_MOV;							\
  .size __##syscall_name##_nocancel,.-__##syscall_name##_nocancel;	\
  ENTRY (name);								\
    str lr, [sp, $-4]!;							\
    DOCARGS_##args;	/* save syscall args around CENABLE.  */	\
    SINGLE_THREAD_P;							\
    bne .Lpseudo_cancel;						\
    UNDOCARGS_##args;	/* restore syscall args.  */			\
    swi SYS_ify (syscall_name);	/* do the call.  */			\
    cmn r0, $4096;							\
    UNDOC2ARGS_##args;	/* fix register damage.  */			\
    PSEUDO_RET;								\
  .Lpseudo_cancel:							\
    CENABLE;								\
    mov ip, r0;		/* put mask in safe place.  */			\
    UNDOCARGS_##args;	/* restore syscall args.  */			\
    swi SYS_ify (syscall_name);	/* do the call.  */			\
    str r0, [sp, $-4]!; /* save syscall return value.  */		\
    mov r0, ip;		/* get mask back.  */				\
    CDISABLE;								\
    ldr r0, [sp], $4;	/* retrieve return value.  */			\
    UNDOC2ARGS_##args;	/* fix register damage.  */			\
    cmn r0, $4096;

# define DOCARGS_0
# define UNDOCARGS_0
# define UNDOC2ARGS_0

# define DOCARGS_1	str r0, [sp, #-4]!;
# define UNDOCARGS_1	ldr r0, [sp], #4;
# define UNDOC2ARGS_1

# define DOCARGS_2	str r1, [sp, #-4]!; str r0, [sp, #-4]!;
# define UNDOCARGS_2	ldr r0, [sp], #4; ldr r1, [sp], #4;
# define UNDOC2ARGS_2

# define DOCARGS_3	str r2, [sp, #-4]!; str r1, [sp, #-4]!; str r0, [sp, #-4]!;
# define UNDOCARGS_3	ldr r0, [sp], #4; ldr r1, [sp], #4; ldr r2, [sp], #4
# define UNDOC2ARGS_3

# define DOCARGS_4	stmfd sp!, {r0-r3}
# define UNDOCARGS_4	ldmfd sp!, {r0-r3}
# define UNDOC2ARGS_4

# define DOCARGS_5	stmfd sp!, {r0-r3}
# define UNDOCARGS_5	ldmfd sp, {r0-r3}; str r4, [sp, #-4]!; ldr r4, [sp, #24]
# define UNDOC2ARGS_5   ldr r4, [sp], #20

# ifdef IS_IN_libpthread
#  define CENABLE	bl PLTJMP(__pthread_enable_asynccancel)
#  define CDISABLE	bl PLTJMP(__pthread_disable_asynccancel)
# elif !defined NOT_IN_libc
#  define CENABLE	bl PLTJMP(__libc_enable_asynccancel)
#  define CDISABLE	bl PLTJMP(__libc_disable_asynccancel)
# elif defined IS_IN_librt
#  define CENABLE	bl PLTJMP(__librt_enable_asynccancel)
#  define CDISABLE	bl PLTJMP(__librt_disable_asynccancel)
# else
#  error Unsupported library
# endif

# ifndef __ASSEMBLER__
#  define SINGLE_THREAD_P						\
  __builtin_expect (THREAD_GETMEM (THREAD_SELF,				\
				   header.multiple_threads) == 0, 1)
# else
#  define PSEUDO_PROLOGUE
#  define SINGLE_THREAD_P						\
  mov	r0, #0xffff0fff;						\
  mov	lr, pc;								\
  sub	pc, r0, #31;							\
  ldr	ip, [r0, #MULTIPLE_THREADS_OFFSET];				\
  teq	ip, #0
#  define SINGLE_THREAD_P_PIC(x) SINGLE_THREAD_P
# endif

#elif !defined __ASSEMBLER__

# define SINGLE_THREAD_P (1)
# define NO_CANCELLATION 1

#endif
