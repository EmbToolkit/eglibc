# Makefile fragment for PowerPC with no FPU.

ifeq ($(subdir),soft-fp)
sysdep_routines += $(gcc-single-routines) $(gcc-double-routines) \
		   sim-full
endif

ifeq ($(subdir),math)
libm-support += fenv_const fe_nomask
CPPFLAGS += -I../soft-fp/
CFLAGS-e_powl.c += -fno-builtin-fabsl
CFLAGS-s_ccoshl.c += -fno-builtin-fabsl
CFLAGS-s_csinhl.c += -fno-builtin-fabsl
CFLAGS-s_clogl.c += -fno-builtin-fabsl
CFLAGS-s_clog10l.c += -fno-builtin-fabsl
CFLAGS-s_csinl.c += -fno-builtin-fabsl
CFLAGS-s_csqrtl.c += -fno-builtin-fabsl
endif
