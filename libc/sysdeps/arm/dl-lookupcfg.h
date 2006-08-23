/* Configuration of lookup functions.
   Copyright (C) 2002 Free Software Foundation, Inc.
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

/* Some platforms need more information from the symbol lookup function
   than just the address.  But this is not generally the case.

   However, because of how _dl_sym and _dl_tls_symaddr are written, every
   platform needs it when we support TLS.  */

#include <tls.h>		/* Defines USE_TLS (or doesn't).  */

/* NOTE drow/2005-04-08: Always define this for ARM, because our TLS resolve
   support uses RESOLVE_MAP.  This is a CSL local change; in HEAD, this
   variable is gone, and RESOLVE_MAP is always used.  */

#define DL_LOOKUP_RETURNS_MAP
