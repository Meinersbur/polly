# 1 "<built-in>"
# 1 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/semeai.c"
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * This is GNU GO, a Go program. Contact gnugo@gnu.org, or see       *
 * http://www.gnu.org/software/gnugo/ for more information.          *
 *                                                                   *
 * Copyright 1999, 2000, 2001, 2002 and 2003                         *
 * by the Free Software Foundation.                                  *
 *                                                                   *
 * This program is free software; you can redistribute it and/or     *
 * modify it under the terms of the GNU General Public License as    *
 * published by the Free Software Foundation - version 2             *
 *                                                                   *
 * This program is distributed in the hope that it will be useful,   *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of    *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     *
 * GNU General Public License in file COPYING for more details.      *
 *                                                                   *
 * You should have received a copy of the GNU General Public         *
 * License along with this program; if not, write to the Free        *
 * Software Foundation, Inc., 59 Temple Place - Suite 330,           *
 * Boston, MA 02111, USA.                                            *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if 0 /* expanded by -frewrite-includes */
#include "gnugo.h"
#endif /* expanded by -frewrite-includes */
# 23 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/semeai.c"
# 1 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/gnugo.h" 1
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * This is GNU GO, a Go program. Contact gnugo@gnu.org, or see       *
 * http://www.gnu.org/software/gnugo/ for more information.          *
 *                                                                   *
 * Copyright 1999, 2000, 2001, 2002 and 2003                         *
 * by the Free Software Foundation.                                  *
 *                                                                   *
 * This program is free software; you can redistribute it and/or     *
 * modify it under the terms of the GNU General Public License as    *
 * published by the Free Software Foundation - version 2             *
 *                                                                   *
 * This program is distributed in the hope that it will be useful,   *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of    *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     *
 * GNU General Public License in file COPYING for more details.      *
 *                                                                   *
 * You should have received a copy of the GNU General Public         *
 * License along with this program; if not, write to the Free        *
 * Software Foundation, Inc., 59 Temple Place - Suite 330,           *
 * Boston, MA 02111, USA.                                            *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* ---------------------------------------------------------------- *
 * gnugo.h
 *	This file contains the public interface to the GNU Go engine.
 * ---------------------------------------------------------------- */


#ifndef _GNUGO_H_
#define _GNUGO_H_


#if 0 /* expanded by -frewrite-includes */
#include <stdio.h>
#endif /* expanded by -frewrite-includes */
# 33 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/gnugo.h"
# 1 "/usr/include/stdio.h" 1 3 4
/* Define ISO C stdio on top of C++ iostreams.
   Copyright (C) 1991-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/*
 *	ISO C99 Standard: 7.19 Input/output	<stdio.h>
 */

#ifndef _STDIO_H

#if !defined __need_FILE && !defined __need___FILE
# define _STDIO_H	1
#if 0 /* expanded by -frewrite-includes */
# include <features.h>
#endif /* expanded by -frewrite-includes */
# 27 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef	_FEATURES_H
#define	_FEATURES_H	1

/* These are defined by the user (or the compiler)
   to specify the desired environment:

   __STRICT_ANSI__	ISO Standard C.
   _ISOC99_SOURCE	Extensions to ISO C89 from ISO C99.
   _ISOC11_SOURCE	Extensions to ISO C99 from ISO C11.
   _POSIX_SOURCE	IEEE Std 1003.1.
   _POSIX_C_SOURCE	If ==1, like _POSIX_SOURCE; if >=2 add IEEE Std 1003.2;
			if >=199309L, add IEEE Std 1003.1b-1993;
			if >=199506L, add IEEE Std 1003.1c-1995;
			if >=200112L, all of IEEE 1003.1-2004
			if >=200809L, all of IEEE 1003.1-2008
   _XOPEN_SOURCE	Includes POSIX and XPG things.  Set to 500 if
			Single Unix conformance is wanted, to 600 for the
			sixth revision, to 700 for the seventh revision.
   _XOPEN_SOURCE_EXTENDED XPG things and X/Open Unix extensions.
   _LARGEFILE_SOURCE	Some more functions for correct standard I/O.
   _LARGEFILE64_SOURCE	Additional functionality from LFS for large files.
   _FILE_OFFSET_BITS=N	Select default filesystem interface.
   _ATFILE_SOURCE	Additional *at interfaces.
   _GNU_SOURCE		All of the above, plus GNU extensions.
   _DEFAULT_SOURCE	The default set of features (taking precedence over
			__STRICT_ANSI__).
   _REENTRANT		Select additionally reentrant object.
   _THREAD_SAFE		Same as _REENTRANT, often used by other systems.
   _FORTIFY_SOURCE	If set to numeric value > 0 additional security
			measures are defined, according to level.

   The `-ansi' switch to the GNU C compiler, and standards conformance
   options such as `-std=c99', define __STRICT_ANSI__.  If none of
   these are defined, or if _DEFAULT_SOURCE is defined, the default is
   to have _POSIX_SOURCE set to one and _POSIX_C_SOURCE set to
   200809L, as well as enabling miscellaneous functions from BSD and
   SVID.  If more than one of these are defined, they accumulate.  For
   example __STRICT_ANSI__, _POSIX_SOURCE and _POSIX_C_SOURCE together
   give you ISO C, 1003.1, and 1003.2, but nothing else.

   These are defined by this file and are used by the
   header files to decide what to declare or define:

   __USE_ISOC11		Define ISO C11 things.
   __USE_ISOC99		Define ISO C99 things.
   __USE_ISOC95		Define ISO C90 AMD1 (C95) things.
   __USE_POSIX		Define IEEE Std 1003.1 things.
   __USE_POSIX2		Define IEEE Std 1003.2 things.
   __USE_POSIX199309	Define IEEE Std 1003.1, and .1b things.
   __USE_POSIX199506	Define IEEE Std 1003.1, .1b, .1c and .1i things.
   __USE_XOPEN		Define XPG things.
   __USE_XOPEN_EXTENDED	Define X/Open Unix things.
   __USE_UNIX98		Define Single Unix V2 things.
   __USE_XOPEN2K        Define XPG6 things.
   __USE_XOPEN2KXSI     Define XPG6 XSI things.
   __USE_XOPEN2K8       Define XPG7 things.
   __USE_XOPEN2K8XSI    Define XPG7 XSI things.
   __USE_LARGEFILE	Define correct standard I/O things.
   __USE_LARGEFILE64	Define LFS things with separate names.
   __USE_FILE_OFFSET64	Define 64bit interface as default.
   __USE_MISC		Define things from 4.3BSD or System V Unix.
   __USE_ATFILE		Define *at interfaces and AT_* constants for them.
   __USE_GNU		Define GNU extensions.
   __USE_REENTRANT	Define reentrant/thread-safe *_r functions.
   __USE_FORTIFY_LEVEL	Additional security measures used, according to level.

   The macros `__GNU_LIBRARY__', `__GLIBC__', and `__GLIBC_MINOR__' are
   defined by this file unconditionally.  `__GNU_LIBRARY__' is provided
   only for compatibility.  All new code should use the other symbols
   to test for features.

   All macros listed above as possibly being defined by this file are
   explicitly undefined if they are not explicitly defined.
   Feature-test macros that are not defined by the user or compiler
   but are implied by the other feature-test macros defined (or by the
   lack of any definitions) are defined by the file.  */


/* Undefine everything, so we get a clean slate.  */
#undef	__USE_ISOC11
#undef	__USE_ISOC99
#undef	__USE_ISOC95
#undef	__USE_ISOCXX11
#undef	__USE_POSIX
#undef	__USE_POSIX2
#undef	__USE_POSIX199309
#undef	__USE_POSIX199506
#undef	__USE_XOPEN
#undef	__USE_XOPEN_EXTENDED
#undef	__USE_UNIX98
#undef	__USE_XOPEN2K
#undef	__USE_XOPEN2KXSI
#undef	__USE_XOPEN2K8
#undef	__USE_XOPEN2K8XSI
#undef	__USE_LARGEFILE
#undef	__USE_LARGEFILE64
#undef	__USE_FILE_OFFSET64
#undef	__USE_MISC
#undef	__USE_ATFILE
#undef	__USE_GNU
#undef	__USE_REENTRANT
#undef	__USE_FORTIFY_LEVEL
#undef	__KERNEL_STRICT_NAMES

/* Suppress kernel-name space pollution unless user expressedly asks
   for it.  */
#ifndef _LOOSE_KERNEL_NAMES
# define __KERNEL_STRICT_NAMES
#endif
# 127 "/usr/include/features.h" 3 4

/* Convenience macros to test the versions of glibc and gcc.
   Use them like this:
   #if __GNUC_PREREQ (2,8)
   ... code requiring gcc 2.8 or later ...
   #endif
   Note - they won't work for gcc1 or glibc1, since the _MINOR macros
   were not defined then.  */
#if defined __GNUC__ && defined __GNUC_MINOR__
# define __GNUC_PREREQ(maj, min) \
	((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#else
# 139 "/usr/include/features.h" 3 4
# define __GNUC_PREREQ(maj, min) 0
#endif
# 141 "/usr/include/features.h" 3 4

/* _BSD_SOURCE and _SVID_SOURCE are deprecated aliases for
   _DEFAULT_SOURCE.  If _DEFAULT_SOURCE is present we do not
   issue a warning; the expectation is that the source is being
   transitioned to use the new macro.  */
#if (defined _BSD_SOURCE || defined _SVID_SOURCE) \
    && !defined _DEFAULT_SOURCE
/* Don't #warn about _BSD_SOURCE || _SVID_SOURCE, as it breaks -Werror
   and we don't have time to check/fix everything before vivid release
# warning "_BSD_SOURCE and _SVID_SOURCE are deprecated, use _DEFAULT_SOURCE"
*/
# undef  _DEFAULT_SOURCE
# define _DEFAULT_SOURCE	1
#endif
# 155 "/usr/include/features.h" 3 4

/* If _GNU_SOURCE was defined by the user, turn on all the other features.  */
#ifdef _GNU_SOURCE
# undef  _ISOC95_SOURCE
# define _ISOC95_SOURCE	1
# undef  _ISOC99_SOURCE
# define _ISOC99_SOURCE	1
# undef  _ISOC11_SOURCE
# define _ISOC11_SOURCE	1
# undef  _POSIX_SOURCE
# define _POSIX_SOURCE	1
# undef  _POSIX_C_SOURCE
# define _POSIX_C_SOURCE	200809L
# undef  _XOPEN_SOURCE
# define _XOPEN_SOURCE	700
# undef  _XOPEN_SOURCE_EXTENDED
# define _XOPEN_SOURCE_EXTENDED	1
# undef	 _LARGEFILE64_SOURCE
# define _LARGEFILE64_SOURCE	1
# undef  _DEFAULT_SOURCE
# define _DEFAULT_SOURCE	1
# undef  _ATFILE_SOURCE
# define _ATFILE_SOURCE	1
#endif
# 179 "/usr/include/features.h" 3 4

/* If nothing (other than _GNU_SOURCE and _DEFAULT_SOURCE) is defined,
   define _DEFAULT_SOURCE.  */
#if (defined _DEFAULT_SOURCE					\
     || (!defined __STRICT_ANSI__				\
	 && !defined _ISOC99_SOURCE				\
	 && !defined _POSIX_SOURCE && !defined _POSIX_C_SOURCE	\
	 && !defined _XOPEN_SOURCE))
# undef  _DEFAULT_SOURCE
# define _DEFAULT_SOURCE	1
#endif
# 190 "/usr/include/features.h" 3 4

/* This is to enable the ISO C11 extension.  */
#if (defined _ISOC11_SOURCE \
     || (defined __STDC_VERSION__ && __STDC_VERSION__ >= 201112L))
# define __USE_ISOC11	1
#endif
# 196 "/usr/include/features.h" 3 4

/* This is to enable the ISO C99 extension.  */
#if (defined _ISOC99_SOURCE || defined _ISOC11_SOURCE \
     || (defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L))
# define __USE_ISOC99	1
#endif
# 202 "/usr/include/features.h" 3 4

/* This is to enable the ISO C90 Amendment 1:1995 extension.  */
#if (defined _ISOC99_SOURCE || defined _ISOC11_SOURCE \
     || (defined __STDC_VERSION__ && __STDC_VERSION__ >= 199409L))
# define __USE_ISOC95	1
#endif
# 208 "/usr/include/features.h" 3 4

/* This is to enable compatibility for ISO C++11.

   So far g++ does not provide a macro.  Check the temporary macro for
   now, too.  */
#if ((defined __cplusplus && __cplusplus >= 201103L)			      \
     || defined __GXX_EXPERIMENTAL_CXX0X__)
# define __USE_ISOCXX11	1
#endif
# 217 "/usr/include/features.h" 3 4

/* If none of the ANSI/POSIX macros are defined, or if _DEFAULT_SOURCE
   is defined, use POSIX.1-2008 (or another version depending on
   _XOPEN_SOURCE).  */
#ifdef _DEFAULT_SOURCE
# if !defined _POSIX_SOURCE && !defined _POSIX_C_SOURCE
#  define __USE_POSIX_IMPLICITLY	1
# endif
# 225 "/usr/include/features.h" 3 4
# undef  _POSIX_SOURCE
# define _POSIX_SOURCE	1
# undef  _POSIX_C_SOURCE
# define _POSIX_C_SOURCE	200809L
#endif
# 230 "/usr/include/features.h" 3 4
#if ((!defined __STRICT_ANSI__					\
      || (defined _XOPEN_SOURCE && (_XOPEN_SOURCE - 0) >= 500))	\
     && !defined _POSIX_SOURCE && !defined _POSIX_C_SOURCE)
# define _POSIX_SOURCE	1
# if defined _XOPEN_SOURCE && (_XOPEN_SOURCE - 0) < 500
#  define _POSIX_C_SOURCE	2
# elif defined _XOPEN_SOURCE && (_XOPEN_SOURCE - 0) < 600
# 237 "/usr/include/features.h" 3 4
#  define _POSIX_C_SOURCE	199506L
# elif defined _XOPEN_SOURCE && (_XOPEN_SOURCE - 0) < 700
# 239 "/usr/include/features.h" 3 4
#  define _POSIX_C_SOURCE	200112L
# else
# 241 "/usr/include/features.h" 3 4
#  define _POSIX_C_SOURCE	200809L
# endif
# 243 "/usr/include/features.h" 3 4
# define __USE_POSIX_IMPLICITLY	1
#endif
# 245 "/usr/include/features.h" 3 4

#if (defined _POSIX_SOURCE					\
     || (defined _POSIX_C_SOURCE && _POSIX_C_SOURCE >= 1)	\
     || defined _XOPEN_SOURCE)
# define __USE_POSIX	1
#endif
# 251 "/usr/include/features.h" 3 4

#if defined _POSIX_C_SOURCE && _POSIX_C_SOURCE >= 2 || defined _XOPEN_SOURCE
# define __USE_POSIX2	1
#endif
# 255 "/usr/include/features.h" 3 4

#if defined _POSIX_C_SOURCE && (_POSIX_C_SOURCE - 0) >= 199309L
# define __USE_POSIX199309	1
#endif
# 259 "/usr/include/features.h" 3 4

#if defined _POSIX_C_SOURCE && (_POSIX_C_SOURCE - 0) >= 199506L
# define __USE_POSIX199506	1
#endif
# 263 "/usr/include/features.h" 3 4

#if defined _POSIX_C_SOURCE && (_POSIX_C_SOURCE - 0) >= 200112L
# define __USE_XOPEN2K		1
# undef __USE_ISOC95
# define __USE_ISOC95		1
# undef __USE_ISOC99
# define __USE_ISOC99		1
#endif
# 271 "/usr/include/features.h" 3 4

#if defined _POSIX_C_SOURCE && (_POSIX_C_SOURCE - 0) >= 200809L
# define __USE_XOPEN2K8		1
# undef  _ATFILE_SOURCE
# define _ATFILE_SOURCE	1
#endif
# 277 "/usr/include/features.h" 3 4

#ifdef	_XOPEN_SOURCE
# define __USE_XOPEN	1
# if (_XOPEN_SOURCE - 0) >= 500
#  define __USE_XOPEN_EXTENDED	1
#  define __USE_UNIX98	1
#  undef _LARGEFILE_SOURCE
#  define _LARGEFILE_SOURCE	1
#  if (_XOPEN_SOURCE - 0) >= 600
#   if (_XOPEN_SOURCE - 0) >= 700
#    define __USE_XOPEN2K8	1
#    define __USE_XOPEN2K8XSI	1
#   endif
# 290 "/usr/include/features.h" 3 4
#   define __USE_XOPEN2K	1
#   define __USE_XOPEN2KXSI	1
#   undef __USE_ISOC95
#   define __USE_ISOC95		1
#   undef __USE_ISOC99
#   define __USE_ISOC99		1
#  endif
# 297 "/usr/include/features.h" 3 4
# else
# 298 "/usr/include/features.h" 3 4
#  ifdef _XOPEN_SOURCE_EXTENDED
#   define __USE_XOPEN_EXTENDED	1
#  endif
# 301 "/usr/include/features.h" 3 4
# endif
# 302 "/usr/include/features.h" 3 4
#endif
# 303 "/usr/include/features.h" 3 4

#ifdef _LARGEFILE_SOURCE
# define __USE_LARGEFILE	1
#endif
# 307 "/usr/include/features.h" 3 4

#ifdef _LARGEFILE64_SOURCE
# define __USE_LARGEFILE64	1
#endif
# 311 "/usr/include/features.h" 3 4

#if defined _FILE_OFFSET_BITS && _FILE_OFFSET_BITS == 64
# define __USE_FILE_OFFSET64	1
#endif
# 315 "/usr/include/features.h" 3 4

#if defined _DEFAULT_SOURCE
# define __USE_MISC	1
#endif
# 319 "/usr/include/features.h" 3 4

#ifdef	_ATFILE_SOURCE
# define __USE_ATFILE	1
#endif
# 323 "/usr/include/features.h" 3 4

#ifdef	_GNU_SOURCE
# define __USE_GNU	1
#endif
# 327 "/usr/include/features.h" 3 4

#if defined _REENTRANT || defined _THREAD_SAFE
# define __USE_REENTRANT	1
#endif
# 331 "/usr/include/features.h" 3 4

#if defined _FORTIFY_SOURCE && _FORTIFY_SOURCE > 0 \
    && __GNUC_PREREQ (4, 1) && defined __OPTIMIZE__ && __OPTIMIZE__ > 0
# if _FORTIFY_SOURCE > 1
#  define __USE_FORTIFY_LEVEL 2
# else
# 337 "/usr/include/features.h" 3 4
#  define __USE_FORTIFY_LEVEL 1
# endif
# 339 "/usr/include/features.h" 3 4
#else
# 340 "/usr/include/features.h" 3 4
# define __USE_FORTIFY_LEVEL 0
#endif
# 342 "/usr/include/features.h" 3 4

/* Get definitions of __STDC_* predefined macros, if the compiler has
   not preincluded this header automatically.  */
#if 0 /* expanded by -frewrite-includes */
#include <stdc-predef.h>
#endif /* expanded by -frewrite-includes */
# 345 "/usr/include/features.h" 3 4
# 1 "/usr/include/stdc-predef.h" 1 3 4
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef	_STDC_PREDEF_H
#define	_STDC_PREDEF_H	1

/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */

/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */

#ifdef __GCC_IEC_559
# if __GCC_IEC_559 > 0
#  define __STDC_IEC_559__		1
# endif
# 40 "/usr/include/stdc-predef.h" 3 4
#else
# 41 "/usr/include/stdc-predef.h" 3 4
# define __STDC_IEC_559__		1
#endif
# 43 "/usr/include/stdc-predef.h" 3 4

#ifdef __GCC_IEC_559_COMPLEX
# if __GCC_IEC_559_COMPLEX > 0
#  define __STDC_IEC_559_COMPLEX__	1
# endif
# 48 "/usr/include/stdc-predef.h" 3 4
#else
# 49 "/usr/include/stdc-predef.h" 3 4
# define __STDC_IEC_559_COMPLEX__	1
#endif
# 51 "/usr/include/stdc-predef.h" 3 4

/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
   2015-05-15).  */
#define __STDC_ISO_10646__		201505L

/* We do not support C11 <threads.h>.  */
#define __STDC_NO_THREADS__		1

#endif
# 61 "/usr/include/stdc-predef.h" 3 4
# 346 "/usr/include/features.h" 2 3 4

/* This macro indicates that the installed library is the GNU C Library.
   For historic reasons the value now is 6 and this will stay from now
   on.  The use of this variable is deprecated.  Use __GLIBC__ and
   __GLIBC_MINOR__ now (see below) when you want to test for a specific
   GNU C library version and use the values in <gnu/lib-names.h> to get
   the sonames of the shared libraries.  */
#undef  __GNU_LIBRARY__
#define __GNU_LIBRARY__ 6

/* Major and minor version number of the GNU C library package.  Use
   these macros to test for features in specific releases.  */
#define	__GLIBC__	2
#define	__GLIBC_MINOR__	23

#define __GLIBC_PREREQ(maj, min) \
	((__GLIBC__ << 16) + __GLIBC_MINOR__ >= ((maj) << 16) + (min))

/* This is here only because every header file already includes this one.  */
#ifndef __ASSEMBLER__
# ifndef _SYS_CDEFS_H
#if 0 /* expanded by -frewrite-includes */
#  include <sys/cdefs.h>
#endif /* expanded by -frewrite-includes */
# 367 "/usr/include/features.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 1 3 4
/* Copyright (C) 1992-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef	_SYS_CDEFS_H
#define	_SYS_CDEFS_H	1

/* We are almost always included from features.h. */
#ifndef _FEATURES_H
#if 0 /* expanded by -frewrite-includes */
# include <features.h>
#endif /* expanded by -frewrite-includes */
# 23 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# 24 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
#endif
# 25 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

/* The GNU libc does not support any K&R compilers or the traditional mode
   of ISO C compilers anymore.  Check for some of the combinations not
   anymore supported.  */
#if defined __GNUC__ && !defined __STDC__
# error "You need a ISO C conforming compiler to use the glibc headers"
#endif
# 32 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

/* Some user header file might have defined this before.  */
#undef	__P
#undef	__PMT

#ifdef __GNUC__

/* All functions, except those with callbacks or those that
   synchronize memory, are leaf functions.  */
# if __GNUC_PREREQ (4, 6) && !defined _LIBC
#  define __LEAF , __leaf__
#  define __LEAF_ATTR __attribute__ ((__leaf__))
# else
# 45 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
#  define __LEAF
#  define __LEAF_ATTR
# endif
# 48 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

/* GCC can always grok prototypes.  For C++ programs we add throw()
   to help it optimize the function calls.  But this works only with
   gcc 2.8.x and egcs.  For gcc 3.2 and up we even mark C functions
   as non-throwing using a function attribute since programs can use
   the -fexceptions options for C code as well.  */
# if !defined __cplusplus && __GNUC_PREREQ (3, 3)
#  define __THROW	__attribute__ ((__nothrow__ __LEAF))
#  define __THROWNL	__attribute__ ((__nothrow__))
#  define __NTH(fct)	__attribute__ ((__nothrow__ __LEAF)) fct
# else
# 59 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
#  if defined __cplusplus && __GNUC_PREREQ (2,8)
#   define __THROW	throw ()
#   define __THROWNL	throw ()
#   define __NTH(fct)	__LEAF_ATTR fct throw ()
#  else
# 64 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
#   define __THROW
#   define __THROWNL
#   define __NTH(fct)	fct
#  endif
# 68 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# endif
# 69 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

#else	/* Not GCC.  */
# 71 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

# define __inline		/* No inline functions.  */

# define __THROW
# define __THROWNL
# define __NTH(fct)	fct

#endif	/* GCC.  */
# 79 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

/* These two macros are not used in glibc anymore.  They are kept here
   only because some other projects expect the macros to be defined.  */
#define __P(args)	args
#define __PMT(args)	args

/* For these things, GCC behaves the ANSI way normally,
   and the non-ANSI way under -traditional.  */

#define __CONCAT(x,y)	x ## y
#define __STRING(x)	#x

/* This is not a typedef so `const __ptr_t' does the right thing.  */
#define __ptr_t void *
#define __long_double_t  long double


/* C++ needs to know that types and declarations are C, not C++.  */
#ifdef	__cplusplus
# define __BEGIN_DECLS	extern "C" {
# define __END_DECLS	}
#else
# 101 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# define __BEGIN_DECLS
# define __END_DECLS
#endif
# 104 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4


/* The standard library needs the functions from the ISO C90 standard
   in the std namespace.  At the same time we want to be safe for
   future changes and we include the ISO C99 code in the non-standard
   namespace __c99.  The C++ wrapper header take case of adding the
   definitions to the global namespace.  */
#if defined __cplusplus && defined _GLIBCPP_USE_NAMESPACES
# define __BEGIN_NAMESPACE_STD	namespace std {
# define __END_NAMESPACE_STD	}
# define __USING_NAMESPACE_STD(name) using std::name;
# define __BEGIN_NAMESPACE_C99	namespace __c99 {
# define __END_NAMESPACE_C99	}
# define __USING_NAMESPACE_C99(name) using __c99::name;
#else
# 119 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
/* For compatibility we do not add the declarations into any
   namespace.  They will end up in the global namespace which is what
   old code expects.  */
# define __BEGIN_NAMESPACE_STD
# define __END_NAMESPACE_STD
# define __USING_NAMESPACE_STD(name)
# define __BEGIN_NAMESPACE_C99
# define __END_NAMESPACE_C99
# define __USING_NAMESPACE_C99(name)
#endif
# 129 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4


/* Fortify support.  */
#define __bos(ptr) __builtin_object_size (ptr, __USE_FORTIFY_LEVEL > 1)
#define __bos0(ptr) __builtin_object_size (ptr, 0)

#if __GNUC_PREREQ (4,3)
# define __warndecl(name, msg) \
  extern void name (void) __attribute__((__warning__ (msg)))
# define __warnattr(msg) __attribute__((__warning__ (msg)))
# define __errordecl(name, msg) \
  extern void name (void) __attribute__((__error__ (msg)))
#else
# 142 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# define __warndecl(name, msg) extern void name (void)
# define __warnattr(msg)
# define __errordecl(name, msg) extern void name (void)
#endif
# 146 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

/* Support for flexible arrays.  */
#if __GNUC_PREREQ (2,97)
/* GCC 2.97 supports C99 flexible array members.  */
# define __flexarr	[]
#else
# 152 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# ifdef __GNUC__
#  define __flexarr	[0]
# else
# 155 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
#  if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L
#   define __flexarr	[]
#  else
# 158 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
/* Some other non-C99 compiler.  Approximate with [1].  */
#   define __flexarr	[1]
#  endif
# 161 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# endif
# 162 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
#endif
# 163 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4


/* __asm__ ("xyz") is used throughout the headers to rename functions
   at the assembly language level.  This is wrapped by the __REDIRECT
   macro, in order to support compilers that can do this some other
   way.  When compilers don't support asm-names at all, we have to do
   preprocessor tricks instead (which don't have exactly the right
   semantics, but it's the best we can do).

   Example:
   int __REDIRECT(setpgrp, (__pid_t pid, __pid_t pgrp), setpgid); */

#if defined __GNUC__ && __GNUC__ >= 2

# define __REDIRECT(name, proto, alias) name proto __asm__ (__ASMNAME (#alias))
# ifdef __cplusplus
#  define __REDIRECT_NTH(name, proto, alias) \
     name proto __THROW __asm__ (__ASMNAME (#alias))
#  define __REDIRECT_NTHNL(name, proto, alias) \
     name proto __THROWNL __asm__ (__ASMNAME (#alias))
# else
# 184 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
#  define __REDIRECT_NTH(name, proto, alias) \
     name proto __asm__ (__ASMNAME (#alias)) __THROW
#  define __REDIRECT_NTHNL(name, proto, alias) \
     name proto __asm__ (__ASMNAME (#alias)) __THROWNL
# endif
# 189 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# define __ASMNAME(cname)  __ASMNAME2 (__USER_LABEL_PREFIX__, cname)
# define __ASMNAME2(prefix, cname) __STRING (prefix) cname

/*
#elif __SOME_OTHER_COMPILER__

# define __REDIRECT(name, proto, alias) name proto; \
	_Pragma("let " #name " = " #alias)
*/
#endif
# 199 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

/* GCC has various useful declarations that can be made with the
   `__attribute__' syntax.  All of the ways we use this do fine if
   they are omitted for compilers that don't understand it. */
#if !defined __GNUC__ || __GNUC__ < 2
# define __attribute__(xyz)	/* Ignore */
#endif
# 206 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

/* At some point during the gcc 2.96 development the `malloc' attribute
   for functions was introduced.  We don't want to use it unconditionally
   (although this would be possible) since it generates warnings.  */
#if __GNUC_PREREQ (2,96)
# define __attribute_malloc__ __attribute__ ((__malloc__))
#else
# 213 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# define __attribute_malloc__ /* Ignore */
#endif
# 215 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

/* Tell the compiler which arguments to an allocation function
   indicate the size of the allocation.  */
#if __GNUC_PREREQ (4, 3)
# define __attribute_alloc_size__(params) \
  __attribute__ ((__alloc_size__ params))
#else
# 222 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# define __attribute_alloc_size__(params) /* Ignore.  */
#endif
# 224 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

/* At some point during the gcc 2.96 development the `pure' attribute
   for functions was introduced.  We don't want to use it unconditionally
   (although this would be possible) since it generates warnings.  */
#if __GNUC_PREREQ (2,96)
# define __attribute_pure__ __attribute__ ((__pure__))
#else
# 231 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# define __attribute_pure__ /* Ignore */
#endif
# 233 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

/* This declaration tells the compiler that the value is constant.  */
#if __GNUC_PREREQ (2,5)
# define __attribute_const__ __attribute__ ((__const__))
#else
# 238 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# define __attribute_const__ /* Ignore */
#endif
# 240 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

/* At some point during the gcc 3.1 development the `used' attribute
   for functions was introduced.  We don't want to use it unconditionally
   (although this would be possible) since it generates warnings.  */
#if __GNUC_PREREQ (3,1)
# define __attribute_used__ __attribute__ ((__used__))
# define __attribute_noinline__ __attribute__ ((__noinline__))
#else
# 248 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# define __attribute_used__ __attribute__ ((__unused__))
# define __attribute_noinline__ /* Ignore */
#endif
# 251 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

/* gcc allows marking deprecated functions.  */
#if __GNUC_PREREQ (3,2)
# define __attribute_deprecated__ __attribute__ ((__deprecated__))
#else
# 256 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# define __attribute_deprecated__ /* Ignore */
#endif
# 258 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

/* At some point during the gcc 2.8 development the `format_arg' attribute
   for functions was introduced.  We don't want to use it unconditionally
   (although this would be possible) since it generates warnings.
   If several `format_arg' attributes are given for the same function, in
   gcc-3.0 and older, all but the last one are ignored.  In newer gccs,
   all designated arguments are considered.  */
#if __GNUC_PREREQ (2,8)
# define __attribute_format_arg__(x) __attribute__ ((__format_arg__ (x)))
#else
# 268 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# define __attribute_format_arg__(x) /* Ignore */
#endif
# 270 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

/* At some point during the gcc 2.97 development the `strfmon' format
   attribute for functions was introduced.  We don't want to use it
   unconditionally (although this would be possible) since it
   generates warnings.  */
#if __GNUC_PREREQ (2,97)
# define __attribute_format_strfmon__(a,b) \
  __attribute__ ((__format__ (__strfmon__, a, b)))
#else
# 279 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# define __attribute_format_strfmon__(a,b) /* Ignore */
#endif
# 281 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

/* The nonull function attribute allows to mark pointer parameters which
   must not be NULL.  */
#if __GNUC_PREREQ (3,3)
# define __nonnull(params) __attribute__ ((__nonnull__ params))
#else
# 287 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# define __nonnull(params)
#endif
# 289 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

/* If fortification mode, we warn about unused results of certain
   function calls which can lead to problems.  */
#if __GNUC_PREREQ (3,4)
# define __attribute_warn_unused_result__ \
   __attribute__ ((__warn_unused_result__))
# if __USE_FORTIFY_LEVEL > 0
#  define __wur __attribute_warn_unused_result__
# endif
# 298 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
#else
# 299 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# define __attribute_warn_unused_result__ /* empty */
#endif
# 301 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
#ifndef __wur
# define __wur /* Ignore */
#endif
# 304 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

/* Forces a function to be always inlined.  */
#if __GNUC_PREREQ (3,2)
# define __always_inline __inline __attribute__ ((__always_inline__))
#else
# 309 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# define __always_inline __inline
#endif
# 311 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

/* Associate error messages with the source location of the call site rather
   than with the source location inside the function.  */
#if __GNUC_PREREQ (4,3)
# define __attribute_artificial__ __attribute__ ((__artificial__))
#else
# 317 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# define __attribute_artificial__ /* Ignore */
#endif
# 319 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

/* GCC 4.3 and above with -std=c99 or -std=gnu99 implements ISO C99
   inline semantics, unless -fgnu89-inline is used.  Using __GNUC_STDC_INLINE__
   or __GNUC_GNU_INLINE is not a good enough check for gcc because gcc versions
   older than 4.3 may define these macros and still not guarantee GNU inlining
   semantics.

   clang++ identifies itself as gcc-4.2, but has support for GNU inlining
   semantics, that can be checked fot by using the __GNUC_STDC_INLINE_ and
   __GNUC_GNU_INLINE__ macro definitions.  */
#if (!defined __cplusplus || __GNUC_PREREQ (4,3) \
     || (defined __clang__ && (defined __GNUC_STDC_INLINE__ \
			       || defined __GNUC_GNU_INLINE__)))
# if defined __GNUC_STDC_INLINE__ || defined __cplusplus
#  define __extern_inline extern __inline __attribute__ ((__gnu_inline__))
#  define __extern_always_inline \
  extern __always_inline __attribute__ ((__gnu_inline__))
# else
# 337 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
#  define __extern_inline extern __inline
#  define __extern_always_inline extern __always_inline
# endif
# 340 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
#endif
# 341 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

#ifdef __extern_always_inline
# define __fortify_function __extern_always_inline __attribute_artificial__
#endif
# 345 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

/* GCC 4.3 and above allow passing all anonymous arguments of an
   __extern_always_inline function to some other vararg function.  */
#if __GNUC_PREREQ (4,3)
# define __va_arg_pack() __builtin_va_arg_pack ()
# define __va_arg_pack_len() __builtin_va_arg_pack_len ()
#endif
# 352 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

/* It is possible to compile containing GCC extensions even if GCC is
   run in pedantic mode if the uses are carefully marked using the
   `__extension__' keyword.  But this is not generally available before
   version 2.8.  */
#if !__GNUC_PREREQ (2,8)
# define __extension__		/* Ignore */
#endif
# 360 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

/* __restrict is known in EGCS 1.2 and above. */
#if !__GNUC_PREREQ (2,92)
# define __restrict	/* Ignore */
#endif
# 365 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

/* ISO C99 also allows to declare arrays as non-overlapping.  The syntax is
     array_name[restrict]
   GCC 3.1 supports this.  */
#if __GNUC_PREREQ (3,1) && !defined __GNUG__
# define __restrict_arr	__restrict
#else
# 372 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# ifdef __GNUC__
#  define __restrict_arr	/* Not supported in old GCC.  */
# else
# 375 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
#  if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L
#   define __restrict_arr	restrict
#  else
# 378 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
/* Some other non-C99 compiler.  */
#   define __restrict_arr	/* Not supported.  */
#  endif
# 381 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# endif
# 382 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
#endif
# 383 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

#if __GNUC__ >= 3
# define __glibc_unlikely(cond)	__builtin_expect ((cond), 0)
# define __glibc_likely(cond)	__builtin_expect ((cond), 1)
#else
# 388 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# define __glibc_unlikely(cond)	(cond)
# define __glibc_likely(cond)	(cond)
#endif
# 391 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

#if (!defined _Noreturn \
     && (defined __STDC_VERSION__ ? __STDC_VERSION__ : 0) < 201112 \
     &&  !__GNUC_PREREQ (4,7))
# if __GNUC_PREREQ (2,8)
#  define _Noreturn __attribute__ ((__noreturn__))
# else
# 398 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
#  define _Noreturn
# endif
# 400 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
#endif
# 401 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

#if (!defined _Static_assert && !defined __cplusplus \
     && (defined __STDC_VERSION__ ? __STDC_VERSION__ : 0) < 201112 \
     && (!__GNUC_PREREQ (4, 6) || defined __STRICT_ANSI__))
# define _Static_assert(expr, diagnostic) \
    extern int (*__Static_assert_function (void)) \
      [!!sizeof (struct { int __error_if_negative: (expr) ? 2 : -1; })]
#endif
# 409 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

#if 0 /* expanded by -frewrite-includes */
#include <bits/wordsize.h>
#endif /* expanded by -frewrite-includes */
# 410 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
/* Determine the wordsize from the preprocessor defines.  */

#if defined __x86_64__ && !defined __ILP32__
# define __WORDSIZE	64
#else
# 6 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 3 4
# define __WORDSIZE	32
#endif
# 8 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 3 4

#ifdef __x86_64__
# define __WORDSIZE_TIME64_COMPAT32	1
/* Both x86-64 and x32 use the 64-bit system call interface.  */
# define __SYSCALL_WORDSIZE		64
#endif
# 14 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 3 4
# 411 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 2 3 4

#if defined __LONG_DOUBLE_MATH_OPTIONAL && defined __NO_LONG_DOUBLE_MATH
# define __LDBL_COMPAT 1
# ifdef __REDIRECT
#  define __LDBL_REDIR1(name, proto, alias) __REDIRECT (name, proto, alias)
#  define __LDBL_REDIR(name, proto) \
  __LDBL_REDIR1 (name, proto, __nldbl_##name)
#  define __LDBL_REDIR1_NTH(name, proto, alias) __REDIRECT_NTH (name, proto, alias)
#  define __LDBL_REDIR_NTH(name, proto) \
  __LDBL_REDIR1_NTH (name, proto, __nldbl_##name)
#  define __LDBL_REDIR1_DECL(name, alias) \
  extern __typeof (name) name __asm (__ASMNAME (#alias));
#  define __LDBL_REDIR_DECL(name) \
  extern __typeof (name) name __asm (__ASMNAME ("__nldbl_" #name));
#  define __REDIRECT_LDBL(name, proto, alias) \
  __LDBL_REDIR1 (name, proto, __nldbl_##alias)
#  define __REDIRECT_NTH_LDBL(name, proto, alias) \
  __LDBL_REDIR1_NTH (name, proto, __nldbl_##alias)
# endif
# 430 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
#endif
# 431 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
#if !defined __LDBL_COMPAT || !defined __REDIRECT
# define __LDBL_REDIR1(name, proto, alias) name proto
# define __LDBL_REDIR(name, proto) name proto
# define __LDBL_REDIR1_NTH(name, proto, alias) name proto __THROW
# define __LDBL_REDIR_NTH(name, proto) name proto __THROW
# define __LDBL_REDIR_DECL(name)
# ifdef __REDIRECT
#  define __REDIRECT_LDBL(name, proto, alias) __REDIRECT (name, proto, alias)
#  define __REDIRECT_NTH_LDBL(name, proto, alias) \
  __REDIRECT_NTH (name, proto, alias)
# endif
# 442 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
#endif
# 443 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4

#endif	 /* sys/cdefs.h */
# 445 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# 368 "/usr/include/features.h" 2 3 4
# endif
# 369 "/usr/include/features.h" 3 4

/* If we don't have __REDIRECT, prototypes will be missing if
   __USE_FILE_OFFSET64 but not __USE_LARGEFILE[64]. */
# if defined __USE_FILE_OFFSET64 && !defined __REDIRECT
#  define __USE_LARGEFILE	1
#  define __USE_LARGEFILE64	1
# endif
# 376 "/usr/include/features.h" 3 4

#endif	/* !ASSEMBLER */
# 378 "/usr/include/features.h" 3 4

/* Decide whether we can define 'extern inline' functions in headers.  */
#if __GNUC_PREREQ (2, 7) && defined __OPTIMIZE__ \
    && !defined __OPTIMIZE_SIZE__ && !defined __NO_INLINE__ \
    && defined __extern_inline
# define __USE_EXTERN_INLINES	1
#endif
# 385 "/usr/include/features.h" 3 4


/* This is here only because every header file already includes this one.
   Get the definitions of all the appropriate `__stub_FUNCTION' symbols.
   <gnu/stubs.h> contains `#define __stub_FUNCTION' when FUNCTION is a stub
   that will always return failure (and set errno to ENOSYS).  */
#if 0 /* expanded by -frewrite-includes */
#include <gnu/stubs.h>
#endif /* expanded by -frewrite-includes */
# 391 "/usr/include/features.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 1 3 4
/* This file is automatically generated.
   This file selects the right generated file of `__stub_FUNCTION' macros
   based on the architecture being compiled for.  */


#if !defined __x86_64__
#if 0 /* expanded by -frewrite-includes */
# include <gnu/stubs-32.h>
#endif /* expanded by -frewrite-includes */
# 7 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 3 4
# 8 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 3 4
#endif
# 9 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 3 4
#if defined __x86_64__ && defined __LP64__
#if 0 /* expanded by -frewrite-includes */
# include <gnu/stubs-64.h>
#endif /* expanded by -frewrite-includes */
# 10 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/gnu/stubs-64.h" 1 3 4
/* This file is automatically generated.
   It defines a symbol `__stub_FUNCTION' for each function
   in the C library which is a stub, meaning it will fail
   every time called, usually setting errno to ENOSYS.  */

#ifdef _LIBC
# error Applications may not define the macro _LIBC
#endif
# 9 "/usr/include/x86_64-linux-gnu/gnu/stubs-64.h" 3 4

#define __stub___compat_bdflush
#define __stub_chflags
#define __stub_fattach
#define __stub_fchflags
#define __stub_fdetach
#define __stub_getmsg
#define __stub_gtty
#define __stub_lchmod
#define __stub_putmsg
#define __stub_revoke
#define __stub_setlogin
#define __stub_sigreturn
#define __stub_sstk
#define __stub_stty
# 11 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 2 3 4
#endif
# 12 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 3 4
#if defined __x86_64__ && defined __ILP32__
#if 0 /* expanded by -frewrite-includes */
# include <gnu/stubs-x32.h>
#endif /* expanded by -frewrite-includes */
# 13 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 3 4
# 14 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 3 4
#endif
# 15 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 3 4
# 392 "/usr/include/features.h" 2 3 4


#endif	/* features.h  */
# 395 "/usr/include/features.h" 3 4
# 28 "/usr/include/stdio.h" 2 3 4

__BEGIN_DECLS

# define __need_size_t
# define __need_NULL
#if 0 /* expanded by -frewrite-includes */
# include <stddef.h>
#endif /* expanded by -frewrite-includes */
# 33 "/usr/include/stdio.h" 3 4
# 1 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 1 3 4
/*===---- stddef.h - Basic type definitions --------------------------------===
 *
 * Copyright (c) 2008 Eli Friedman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *===-----------------------------------------------------------------------===
 */

#if !defined(__STDDEF_H) || defined(__need_ptrdiff_t) ||                       \
    defined(__need_size_t) || defined(__need_wchar_t) ||                       \
    defined(__need_NULL) || defined(__need_wint_t)

#if !defined(__need_ptrdiff_t) && !defined(__need_size_t) &&                   \
    !defined(__need_wchar_t) && !defined(__need_NULL) &&                       \
    !defined(__need_wint_t)
/* Always define miscellaneous pieces when modules are available. */
#if !__has_feature(modules)
#define __STDDEF_H
#endif
# 37 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#define __need_ptrdiff_t
#define __need_size_t
#define __need_wchar_t
#define __need_NULL
#define __need_STDDEF_H_misc
/* __need_wint_t is intentionally not defined here. */
#endif
# 44 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_ptrdiff_t)
#if !defined(_PTRDIFF_T) || __has_feature(modules)
/* Always define ptrdiff_t when modules are available. */
#if !__has_feature(modules)
#define _PTRDIFF_T
#endif
# 51 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif
# 53 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_ptrdiff_t
#endif /* defined(__need_ptrdiff_t) */
# 55 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_size_t)
#if !defined(_SIZE_T) || __has_feature(modules)
/* Always define size_t when modules are available. */
#if !__has_feature(modules)
#define _SIZE_T
#endif
# 62 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ size_t;
#endif
# 64 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_size_t
#endif /*defined(__need_size_t) */
# 66 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
/* ISO9899:2011 7.20 (C11 Annex K): Define rsize_t if __STDC_WANT_LIB_EXT1__ is
 * enabled. */
#if (defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ >= 1 && \
     !defined(_RSIZE_T)) || __has_feature(modules)
/* Always define rsize_t when modules are available. */
#if !__has_feature(modules)
#define _RSIZE_T
#endif
# 76 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ rsize_t;
#endif
# 78 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#endif /* defined(__need_STDDEF_H_misc) */
# 79 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_wchar_t)
#ifndef __cplusplus
/* Always define wchar_t when modules are available. */
#if !defined(_WCHAR_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WCHAR_T
#if defined(_MSC_EXTENSIONS)
#define _WCHAR_T_DEFINED
#endif
# 89 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 90 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WCHAR_TYPE__ wchar_t;
#endif
# 92 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 93 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wchar_t
#endif /* defined(__need_wchar_t) */
# 95 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_NULL)
#undef NULL
#ifdef __cplusplus
#  if !defined(__MINGW32__) && !defined(_MSC_VER)
#    define NULL __null
#  else
# 102 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#    define NULL 0
#  endif
# 104 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#else
# 105 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#  define NULL ((void*)0)
#endif
# 107 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#ifdef __cplusplus
#if defined(_MSC_EXTENSIONS) && defined(_NATIVE_NULLPTR_SUPPORTED)
namespace std { typedef decltype(nullptr) nullptr_t; }
using ::std::nullptr_t;
#endif
# 112 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 113 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_NULL
#endif /* defined(__need_NULL) */
# 115 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
#if __STDC_VERSION__ >= 201112L || __cplusplus >= 201103L
#if 0 /* expanded by -frewrite-includes */
#include "__stddef_max_align_t.h"
#endif /* expanded by -frewrite-includes */
# 118 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
# 119 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 120 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#define offsetof(t, d) __builtin_offsetof(t, d)
#undef __need_STDDEF_H_misc
#endif  /* defined(__need_STDDEF_H_misc) */
# 123 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

/* Some C libraries expect to see a wint_t here. Others (notably MinGW) will use
__WINT_TYPE__ directly; accommodate both by requiring __need_wint_t */
#if defined(__need_wint_t)
/* Always define wint_t when modules are available. */
#if !defined(_WINT_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WINT_T
#endif
# 132 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WINT_TYPE__ wint_t;
#endif
# 134 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wint_t
#endif /* __need_wint_t */
# 136 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#endif
# 138 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
# 34 "/usr/include/stdio.h" 2 3 4

#if 0 /* expanded by -frewrite-includes */
# include <bits/types.h>
#endif /* expanded by -frewrite-includes */
# 35 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types.h" 1 3 4
/* bits/types.h -- definitions of __*_t types underlying *_t types.
   Copyright (C) 2002-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/*
 * Never include this file directly; use <sys/types.h> instead.
 */

#ifndef	_BITS_TYPES_H
#define	_BITS_TYPES_H	1

#if 0 /* expanded by -frewrite-includes */
#include <features.h>
#endif /* expanded by -frewrite-includes */
# 26 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4
# 27 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4
#if 0 /* expanded by -frewrite-includes */
#include <bits/wordsize.h>
#endif /* expanded by -frewrite-includes */
# 27 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
/* Determine the wordsize from the preprocessor defines.  */

#if defined __x86_64__ && !defined __ILP32__
# define __WORDSIZE	64
#else
# 6 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 3 4
# define __WORDSIZE	32
#endif
# 8 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 3 4

#ifdef __x86_64__
# define __WORDSIZE_TIME64_COMPAT32	1
/* Both x86-64 and x32 use the 64-bit system call interface.  */
# define __SYSCALL_WORDSIZE		64
#endif
# 14 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 3 4
# 28 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4

/* Convenience types.  */
typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;

/* Fixed-size types, underlying types depend on word size and compiler.  */
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
#if __WORDSIZE == 64
typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;
#else
# 46 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4
__extension__ typedef signed long long int __int64_t;
__extension__ typedef unsigned long long int __uint64_t;
#endif
# 49 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4

/* quad_t is also 64 bits.  */
#if __WORDSIZE == 64
typedef long int __quad_t;
typedef unsigned long int __u_quad_t;
#else
# 55 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4
__extension__ typedef long long int __quad_t;
__extension__ typedef unsigned long long int __u_quad_t;
#endif
# 58 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4


/* The machine-dependent file <bits/typesizes.h> defines __*_T_TYPE
   macros for each of the OS types we define below.  The definitions
   of those macros must use the following macros for underlying types.
   We define __S<SIZE>_TYPE and __U<SIZE>_TYPE for the signed and unsigned
   variants of each of the following integer types on this machine.

	16		-- "natural" 16-bit type (always short)
	32		-- "natural" 32-bit type (always int)
	64		-- "natural" 64-bit type (long or long long)
	LONG32		-- 32-bit type, traditionally long
	QUAD		-- 64-bit type, always long long
	WORD		-- natural type of __WORDSIZE bits (int or long)
	LONGWORD	-- type of __WORDSIZE bits, traditionally long

   We distinguish WORD/LONGWORD, 32/LONG32, and 64/QUAD so that the
   conventional uses of `long' or `long long' type modifiers match the
   types we define, even when a less-adorned type would be the same size.
   This matters for (somewhat) portably writing printf/scanf formats for
   these types, where using the appropriate l or ll format modifiers can
   make the typedefs and the formats match up across all GNU platforms.  If
   we used `long' when it's 64 bits where `long long' is expected, then the
   compiler would warn about the formats not matching the argument types,
   and the programmer changing them to shut up the compiler would break the
   program's portability.

   Here we assume what is presently the case in all the GCC configurations
   we support: long long is always 64 bits, long is always word/address size,
   and int is always 32 bits.  */

#define	__S16_TYPE		short int
#define __U16_TYPE		unsigned short int
#define	__S32_TYPE		int
#define __U32_TYPE		unsigned int
#define __SLONGWORD_TYPE	long int
#define __ULONGWORD_TYPE	unsigned long int
#if __WORDSIZE == 32
# define __SQUAD_TYPE		__quad_t
# define __UQUAD_TYPE		__u_quad_t
# define __SWORD_TYPE		int
# define __UWORD_TYPE		unsigned int
# define __SLONG32_TYPE		long int
# define __ULONG32_TYPE		unsigned long int
# define __S64_TYPE		__quad_t
# define __U64_TYPE		__u_quad_t
/* We want __extension__ before typedef's that use nonstandard base types
   such as `long long' in C89 mode.  */
# define __STD_TYPE		__extension__ typedef
#elif __WORDSIZE == 64
# 108 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4
# define __SQUAD_TYPE		long int
# define __UQUAD_TYPE		unsigned long int
# define __SWORD_TYPE		long int
# define __UWORD_TYPE		unsigned long int
# define __SLONG32_TYPE		int
# define __ULONG32_TYPE		unsigned int
# define __S64_TYPE		long int
# define __U64_TYPE		unsigned long int
/* No need to mark the typedef with __extension__.   */
# define __STD_TYPE		typedef
#else
# 119 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4
# error
#endif
# 121 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4
#if 0 /* expanded by -frewrite-includes */
#include <bits/typesizes.h>	/* Defines __*_T_TYPE macros.  */
#endif /* expanded by -frewrite-includes */
# 121 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/typesizes.h" 1 3 4
/* bits/typesizes.h -- underlying types for *_t.  Linux/x86-64 version.
   Copyright (C) 2012-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _BITS_TYPES_H
# error "Never include <bits/typesizes.h> directly; use <sys/types.h> instead."
#endif
# 22 "/usr/include/x86_64-linux-gnu/bits/typesizes.h" 3 4

#ifndef	_BITS_TYPESIZES_H
#define	_BITS_TYPESIZES_H	1

/* See <bits/types.h> for the meaning of these macros.  This file exists so
   that <bits/types.h> need not vary across different GNU platforms.  */

/* X32 kernel interface is 64-bit.  */
#if defined __x86_64__ && defined __ILP32__
# define __SYSCALL_SLONG_TYPE	__SQUAD_TYPE
# define __SYSCALL_ULONG_TYPE	__UQUAD_TYPE
#else
# 34 "/usr/include/x86_64-linux-gnu/bits/typesizes.h" 3 4
# define __SYSCALL_SLONG_TYPE	__SLONGWORD_TYPE
# define __SYSCALL_ULONG_TYPE	__ULONGWORD_TYPE
#endif
# 37 "/usr/include/x86_64-linux-gnu/bits/typesizes.h" 3 4

#define __DEV_T_TYPE		__UQUAD_TYPE
#define __UID_T_TYPE		__U32_TYPE
#define __GID_T_TYPE		__U32_TYPE
#define __INO_T_TYPE		__SYSCALL_ULONG_TYPE
#define __INO64_T_TYPE		__UQUAD_TYPE
#define __MODE_T_TYPE		__U32_TYPE
#ifdef __x86_64__
# define __NLINK_T_TYPE		__SYSCALL_ULONG_TYPE
# define __FSWORD_T_TYPE	__SYSCALL_SLONG_TYPE
#else
# 48 "/usr/include/x86_64-linux-gnu/bits/typesizes.h" 3 4
# define __NLINK_T_TYPE		__UWORD_TYPE
# define __FSWORD_T_TYPE	__SWORD_TYPE
#endif
# 51 "/usr/include/x86_64-linux-gnu/bits/typesizes.h" 3 4
#define __OFF_T_TYPE		__SYSCALL_SLONG_TYPE
#define __OFF64_T_TYPE		__SQUAD_TYPE
#define __PID_T_TYPE		__S32_TYPE
#define __RLIM_T_TYPE		__SYSCALL_ULONG_TYPE
#define __RLIM64_T_TYPE		__UQUAD_TYPE
#define __BLKCNT_T_TYPE		__SYSCALL_SLONG_TYPE
#define __BLKCNT64_T_TYPE	__SQUAD_TYPE
#define __FSBLKCNT_T_TYPE	__SYSCALL_ULONG_TYPE
#define __FSBLKCNT64_T_TYPE	__UQUAD_TYPE
#define __FSFILCNT_T_TYPE	__SYSCALL_ULONG_TYPE
#define __FSFILCNT64_T_TYPE	__UQUAD_TYPE
#define __ID_T_TYPE		__U32_TYPE
#define __CLOCK_T_TYPE		__SYSCALL_SLONG_TYPE
#define __TIME_T_TYPE		__SYSCALL_SLONG_TYPE
#define __USECONDS_T_TYPE	__U32_TYPE
#define __SUSECONDS_T_TYPE	__SYSCALL_SLONG_TYPE
#define __DADDR_T_TYPE		__S32_TYPE
#define __KEY_T_TYPE		__S32_TYPE
#define __CLOCKID_T_TYPE	__S32_TYPE
#define __TIMER_T_TYPE		void *
#define __BLKSIZE_T_TYPE	__SYSCALL_SLONG_TYPE
#define __FSID_T_TYPE		struct { int __val[2]; }
#define __SSIZE_T_TYPE		__SWORD_TYPE
#define __CPU_MASK_TYPE 	__SYSCALL_ULONG_TYPE

#ifdef __x86_64__
/* Tell the libc code that off_t and off64_t are actually the same type
   for all ABI purposes, even if possibly expressed as different base types
   for C type-checking purposes.  */
# define __OFF_T_MATCHES_OFF64_T	1

/* Same for ino_t and ino64_t.  */
# define __INO_T_MATCHES_INO64_T	1
#endif
# 85 "/usr/include/x86_64-linux-gnu/bits/typesizes.h" 3 4

/* Number of descriptors that can fit in an `fd_set'.  */
#define __FD_SETSIZE		1024


#endif /* bits/typesizes.h */
# 91 "/usr/include/x86_64-linux-gnu/bits/typesizes.h" 3 4
# 122 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4


__STD_TYPE __DEV_T_TYPE __dev_t;	/* Type of device numbers.  */
__STD_TYPE __UID_T_TYPE __uid_t;	/* Type of user identifications.  */
__STD_TYPE __GID_T_TYPE __gid_t;	/* Type of group identifications.  */
__STD_TYPE __INO_T_TYPE __ino_t;	/* Type of file serial numbers.  */
__STD_TYPE __INO64_T_TYPE __ino64_t;	/* Type of file serial numbers (LFS).*/
__STD_TYPE __MODE_T_TYPE __mode_t;	/* Type of file attribute bitmasks.  */
__STD_TYPE __NLINK_T_TYPE __nlink_t;	/* Type of file link counts.  */
__STD_TYPE __OFF_T_TYPE __off_t;	/* Type of file sizes and offsets.  */
__STD_TYPE __OFF64_T_TYPE __off64_t;	/* Type of file sizes and offsets (LFS).  */
__STD_TYPE __PID_T_TYPE __pid_t;	/* Type of process identifications.  */
__STD_TYPE __FSID_T_TYPE __fsid_t;	/* Type of file system IDs.  */
__STD_TYPE __CLOCK_T_TYPE __clock_t;	/* Type of CPU usage counts.  */
__STD_TYPE __RLIM_T_TYPE __rlim_t;	/* Type for resource measurement.  */
__STD_TYPE __RLIM64_T_TYPE __rlim64_t;	/* Type for resource measurement (LFS).  */
__STD_TYPE __ID_T_TYPE __id_t;		/* General type for IDs.  */
__STD_TYPE __TIME_T_TYPE __time_t;	/* Seconds since the Epoch.  */
__STD_TYPE __USECONDS_T_TYPE __useconds_t; /* Count of microseconds.  */
__STD_TYPE __SUSECONDS_T_TYPE __suseconds_t; /* Signed count of microseconds.  */

__STD_TYPE __DADDR_T_TYPE __daddr_t;	/* The type of a disk address.  */
__STD_TYPE __KEY_T_TYPE __key_t;	/* Type of an IPC key.  */

/* Clock ID used in clock and timer functions.  */
__STD_TYPE __CLOCKID_T_TYPE __clockid_t;

/* Timer ID returned by `timer_create'.  */
__STD_TYPE __TIMER_T_TYPE __timer_t;

/* Type to represent block size.  */
__STD_TYPE __BLKSIZE_T_TYPE __blksize_t;

/* Types from the Large File Support interface.  */

/* Type to count number of disk blocks.  */
__STD_TYPE __BLKCNT_T_TYPE __blkcnt_t;
__STD_TYPE __BLKCNT64_T_TYPE __blkcnt64_t;

/* Type to count file system blocks.  */
__STD_TYPE __FSBLKCNT_T_TYPE __fsblkcnt_t;
__STD_TYPE __FSBLKCNT64_T_TYPE __fsblkcnt64_t;

/* Type to count file system nodes.  */
__STD_TYPE __FSFILCNT_T_TYPE __fsfilcnt_t;
__STD_TYPE __FSFILCNT64_T_TYPE __fsfilcnt64_t;

/* Type of miscellaneous file system fields.  */
__STD_TYPE __FSWORD_T_TYPE __fsword_t;

__STD_TYPE __SSIZE_T_TYPE __ssize_t; /* Type of a byte count, or error.  */

/* Signed long type used in system calls.  */
__STD_TYPE __SYSCALL_SLONG_TYPE __syscall_slong_t;
/* Unsigned long type used in system calls.  */
__STD_TYPE __SYSCALL_ULONG_TYPE __syscall_ulong_t;

/* These few don't really vary by system, they always correspond
   to one of the other defined types.  */
typedef __off64_t __loff_t;	/* Type of file sizes and offsets (LFS).  */
typedef __quad_t *__qaddr_t;
typedef char *__caddr_t;

/* Duplicates info from stdint.h but this is used in unistd.h.  */
__STD_TYPE __SWORD_TYPE __intptr_t;

/* Duplicate info from sys/socket.h.  */
__STD_TYPE __U32_TYPE __socklen_t;


#undef __STD_TYPE

#endif /* bits/types.h */
# 195 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4
# 36 "/usr/include/stdio.h" 2 3 4
# define __need_FILE
# define __need___FILE
#endif /* Don't need FILE.  */
# 39 "/usr/include/stdio.h" 3 4


#if !defined __FILE_defined && defined __need_FILE

/* Define outside of namespace so the C++ is happy.  */
struct _IO_FILE;

__BEGIN_NAMESPACE_STD
/* The opaque type of streams.  This is the definition used elsewhere.  */
typedef struct _IO_FILE FILE;
__END_NAMESPACE_STD
#if defined __USE_LARGEFILE64 || defined __USE_POSIX \
    || defined __USE_ISOC99 || defined __USE_XOPEN \
    || defined __USE_POSIX2
__USING_NAMESPACE_STD(FILE)
#endif
# 55 "/usr/include/stdio.h" 3 4

# define __FILE_defined	1
#endif /* FILE not defined.  */
# 58 "/usr/include/stdio.h" 3 4
#undef	__need_FILE


#if !defined ____FILE_defined && defined __need___FILE

/* The opaque type of streams.  This is the definition used elsewhere.  */
typedef struct _IO_FILE __FILE;

# define ____FILE_defined	1
#endif /* __FILE not defined.  */
# 68 "/usr/include/stdio.h" 3 4
#undef	__need___FILE


#ifdef	_STDIO_H
#define _STDIO_USES_IOSTREAM

#if 0 /* expanded by -frewrite-includes */
#include <libio.h>
#endif /* expanded by -frewrite-includes */
# 74 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/libio.h" 1 3 4
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Written by Per Bothner <bothner@cygnus.com>.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.

   As a special exception, if you link the code in this file with
   files compiled with a GNU compiler to produce an executable,
   that does not cause the resulting executable to be covered by
   the GNU Lesser General Public License.  This exception does not
   however invalidate any other reasons why the executable file
   might be covered by the GNU Lesser General Public License.
   This exception applies to code released by its copyright holders
   in files containing the exception.  */

#ifndef _IO_STDIO_H
#define _IO_STDIO_H

#if 0 /* expanded by -frewrite-includes */
#include <_G_config.h>
#endif /* expanded by -frewrite-includes */
# 31 "/usr/include/libio.h" 3 4
# 1 "/usr/include/_G_config.h" 1 3 4
/* This file is needed by libio to define various configuration parameters.
   These are always the same in the GNU C library.  */

#ifndef _G_config_h
#define _G_config_h 1

/* Define types for libio in terms of the standard internal type names.  */

#if 0 /* expanded by -frewrite-includes */
#include <bits/types.h>
#endif /* expanded by -frewrite-includes */
# 9 "/usr/include/_G_config.h" 3 4
# 10 "/usr/include/_G_config.h" 3 4
#define __need_size_t
#if defined _LIBC || defined _GLIBCPP_USE_WCHAR_T
# define __need_wchar_t
#endif
# 14 "/usr/include/_G_config.h" 3 4
#define __need_NULL
#if 0 /* expanded by -frewrite-includes */
#include <stddef.h>
#endif /* expanded by -frewrite-includes */
# 15 "/usr/include/_G_config.h" 3 4
# 1 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 1 3 4
/*===---- stddef.h - Basic type definitions --------------------------------===
 *
 * Copyright (c) 2008 Eli Friedman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *===-----------------------------------------------------------------------===
 */

#if !defined(__STDDEF_H) || defined(__need_ptrdiff_t) ||                       \
    defined(__need_size_t) || defined(__need_wchar_t) ||                       \
    defined(__need_NULL) || defined(__need_wint_t)

#if !defined(__need_ptrdiff_t) && !defined(__need_size_t) &&                   \
    !defined(__need_wchar_t) && !defined(__need_NULL) &&                       \
    !defined(__need_wint_t)
/* Always define miscellaneous pieces when modules are available. */
#if !__has_feature(modules)
#define __STDDEF_H
#endif
# 37 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#define __need_ptrdiff_t
#define __need_size_t
#define __need_wchar_t
#define __need_NULL
#define __need_STDDEF_H_misc
/* __need_wint_t is intentionally not defined here. */
#endif
# 44 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_ptrdiff_t)
#if !defined(_PTRDIFF_T) || __has_feature(modules)
/* Always define ptrdiff_t when modules are available. */
#if !__has_feature(modules)
#define _PTRDIFF_T
#endif
# 51 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif
# 53 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_ptrdiff_t
#endif /* defined(__need_ptrdiff_t) */
# 55 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_size_t)
#if !defined(_SIZE_T) || __has_feature(modules)
/* Always define size_t when modules are available. */
#if !__has_feature(modules)
#define _SIZE_T
#endif
# 62 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ size_t;
#endif
# 64 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_size_t
#endif /*defined(__need_size_t) */
# 66 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
/* ISO9899:2011 7.20 (C11 Annex K): Define rsize_t if __STDC_WANT_LIB_EXT1__ is
 * enabled. */
#if (defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ >= 1 && \
     !defined(_RSIZE_T)) || __has_feature(modules)
/* Always define rsize_t when modules are available. */
#if !__has_feature(modules)
#define _RSIZE_T
#endif
# 76 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ rsize_t;
#endif
# 78 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#endif /* defined(__need_STDDEF_H_misc) */
# 79 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_wchar_t)
#ifndef __cplusplus
/* Always define wchar_t when modules are available. */
#if !defined(_WCHAR_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WCHAR_T
#if defined(_MSC_EXTENSIONS)
#define _WCHAR_T_DEFINED
#endif
# 89 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 90 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WCHAR_TYPE__ wchar_t;
#endif
# 92 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 93 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wchar_t
#endif /* defined(__need_wchar_t) */
# 95 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_NULL)
#undef NULL
#ifdef __cplusplus
#  if !defined(__MINGW32__) && !defined(_MSC_VER)
#    define NULL __null
#  else
# 102 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#    define NULL 0
#  endif
# 104 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#else
# 105 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#  define NULL ((void*)0)
#endif
# 107 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#ifdef __cplusplus
#if defined(_MSC_EXTENSIONS) && defined(_NATIVE_NULLPTR_SUPPORTED)
namespace std { typedef decltype(nullptr) nullptr_t; }
using ::std::nullptr_t;
#endif
# 112 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 113 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_NULL
#endif /* defined(__need_NULL) */
# 115 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
#if __STDC_VERSION__ >= 201112L || __cplusplus >= 201103L
#if 0 /* expanded by -frewrite-includes */
#include "__stddef_max_align_t.h"
#endif /* expanded by -frewrite-includes */
# 118 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
# 119 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 120 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#define offsetof(t, d) __builtin_offsetof(t, d)
#undef __need_STDDEF_H_misc
#endif  /* defined(__need_STDDEF_H_misc) */
# 123 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

/* Some C libraries expect to see a wint_t here. Others (notably MinGW) will use
__WINT_TYPE__ directly; accommodate both by requiring __need_wint_t */
#if defined(__need_wint_t)
/* Always define wint_t when modules are available. */
#if !defined(_WINT_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WINT_T
#endif
# 132 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WINT_TYPE__ wint_t;
#endif
# 134 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wint_t
#endif /* __need_wint_t */
# 136 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#endif
# 138 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
# 16 "/usr/include/_G_config.h" 2 3 4
#define __need_mbstate_t
#if defined _LIBC || defined _GLIBCPP_USE_WCHAR_T
# define __need_wint_t
#endif
# 20 "/usr/include/_G_config.h" 3 4
#if 0 /* expanded by -frewrite-includes */
#include <wchar.h>
#endif /* expanded by -frewrite-includes */
# 20 "/usr/include/_G_config.h" 3 4
# 1 "/usr/include/wchar.h" 1 3 4
/* Copyright (C) 1995-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/*
 *      ISO C99 Standard: 7.24
 *	Extended multibyte and wide character utilities	<wchar.h>
 */

#ifndef _WCHAR_H

#if !defined __need_mbstate_t && !defined __need_wint_t
# define _WCHAR_H 1
#if 0 /* expanded by -frewrite-includes */
# include <features.h>
#endif /* expanded by -frewrite-includes */
# 27 "/usr/include/wchar.h" 3 4
# 28 "/usr/include/wchar.h" 3 4
#endif
# 29 "/usr/include/wchar.h" 3 4

#ifdef _WCHAR_H
/* Get FILE definition.  */
# define __need___FILE
# if defined __USE_UNIX98 || defined __USE_XOPEN2K
#  define __need_FILE
# endif
# 36 "/usr/include/wchar.h" 3 4
#if 0 /* expanded by -frewrite-includes */
# include <stdio.h>
#endif /* expanded by -frewrite-includes */
# 36 "/usr/include/wchar.h" 3 4
# 37 "/usr/include/wchar.h" 3 4
/* Get va_list definition.  */
# define __need___va_list
#if 0 /* expanded by -frewrite-includes */
# include <stdarg.h>
#endif /* expanded by -frewrite-includes */
# 39 "/usr/include/wchar.h" 3 4
# 40 "/usr/include/wchar.h" 3 4

#if 0 /* expanded by -frewrite-includes */
# include <bits/wchar.h>
#endif /* expanded by -frewrite-includes */
# 41 "/usr/include/wchar.h" 3 4
# 42 "/usr/include/wchar.h" 3 4

/* Get size_t, wchar_t, wint_t and NULL from <stddef.h>.  */
# define __need_size_t
# define __need_wchar_t
# define __need_NULL
#endif
# 48 "/usr/include/wchar.h" 3 4
#if defined _WCHAR_H || defined __need_wint_t || !defined __WINT_TYPE__
# undef __need_wint_t
# define __need_wint_t
#if 0 /* expanded by -frewrite-includes */
# include <stddef.h>
#endif /* expanded by -frewrite-includes */
# 51 "/usr/include/wchar.h" 3 4
# 52 "/usr/include/wchar.h" 3 4

/* We try to get wint_t from <stddef.h>, but not all GCC versions define it
   there.  So define it ourselves if it remains undefined.  */
# ifndef _WINT_T
/* Integral type unchanged by default argument promotions that can
   hold any value corresponding to members of the extended character
   set, as well as at least one value that does not correspond to any
   member of the extended character set.  */
#  define _WINT_T
typedef unsigned int wint_t;
# else
# 63 "/usr/include/wchar.h" 3 4
/* Work around problems with the <stddef.h> file which doesn't put
   wint_t in the std namespace.  */
#  if defined __cplusplus && defined _GLIBCPP_USE_NAMESPACES \
      && defined __WINT_TYPE__
__BEGIN_NAMESPACE_STD
typedef __WINT_TYPE__ wint_t;
__END_NAMESPACE_STD
#  endif
# 71 "/usr/include/wchar.h" 3 4
# endif
# 72 "/usr/include/wchar.h" 3 4

/* Tell the caller that we provide correct C++ prototypes.  */
# if defined __cplusplus && __GNUC_PREREQ (4, 4)
#  define __CORRECT_ISO_CPP_WCHAR_H_PROTO
# endif
# 77 "/usr/include/wchar.h" 3 4
#endif
# 78 "/usr/include/wchar.h" 3 4

#if (defined _WCHAR_H || defined __need_mbstate_t) && !defined ____mbstate_t_defined
# define ____mbstate_t_defined	1
/* Conversion state information.  */
typedef struct
{
  int __count;
  union
  {
# ifdef __WINT_TYPE__
    __WINT_TYPE__ __wch;
# else
# 90 "/usr/include/wchar.h" 3 4
    wint_t __wch;
# endif
# 92 "/usr/include/wchar.h" 3 4
    char __wchb[4];
  } __value;		/* Value so far.  */
} __mbstate_t;
#endif
# 96 "/usr/include/wchar.h" 3 4
#undef __need_mbstate_t


/* The rest of the file is only used if used if __need_mbstate_t is not
   defined.  */
#ifdef _WCHAR_H

# ifndef __mbstate_t_defined
__BEGIN_NAMESPACE_C99
/* Public type.  */
typedef __mbstate_t mbstate_t;
__END_NAMESPACE_C99
#  define __mbstate_t_defined 1
# endif
# 110 "/usr/include/wchar.h" 3 4

#ifdef __USE_GNU
__USING_NAMESPACE_C99(mbstate_t)
#endif
# 114 "/usr/include/wchar.h" 3 4

#ifndef WCHAR_MIN
/* These constants might also be defined in <inttypes.h>.  */
# define WCHAR_MIN __WCHAR_MIN
# define WCHAR_MAX __WCHAR_MAX
#endif
# 120 "/usr/include/wchar.h" 3 4

#ifndef WEOF
# define WEOF (0xffffffffu)
#endif
# 124 "/usr/include/wchar.h" 3 4

/* For XPG4 compliance we have to define the stuff from <wctype.h> here
   as well.  */
#if defined __USE_XOPEN && !defined __USE_UNIX98
#if 0 /* expanded by -frewrite-includes */
# include <wctype.h>
#endif /* expanded by -frewrite-includes */
# 128 "/usr/include/wchar.h" 3 4
# 129 "/usr/include/wchar.h" 3 4
#endif
# 130 "/usr/include/wchar.h" 3 4


__BEGIN_DECLS

__BEGIN_NAMESPACE_STD
/* This incomplete type is defined in <time.h> but needed here because
   of `wcsftime'.  */
struct tm;
__END_NAMESPACE_STD
/* XXX We have to clean this up at some point.  Since tm is in the std
   namespace but wcsftime is in __c99 the type wouldn't be found
   without inserting it in the global namespace.  */
__USING_NAMESPACE_STD(tm)


__BEGIN_NAMESPACE_STD
/* Copy SRC to DEST.  */
extern wchar_t *wcscpy (wchar_t *__restrict __dest,
			const wchar_t *__restrict __src)
     __THROW __nonnull ((1, 2));

/* Copy no more than N wide-characters of SRC to DEST.  */
extern wchar_t *wcsncpy (wchar_t *__restrict __dest,
			 const wchar_t *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Append SRC onto DEST.  */
extern wchar_t *wcscat (wchar_t *__restrict __dest,
			const wchar_t *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Append no more than N wide-characters of SRC onto DEST.  */
extern wchar_t *wcsncat (wchar_t *__restrict __dest,
			 const wchar_t *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Compare S1 and S2.  */
extern int wcscmp (const wchar_t *__s1, const wchar_t *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Compare N wide-characters of S1 and S2.  */
extern int wcsncmp (const wchar_t *__s1, const wchar_t *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));
__END_NAMESPACE_STD

#ifdef __USE_XOPEN2K8
/* Compare S1 and S2, ignoring case.  */
extern int wcscasecmp (const wchar_t *__s1, const wchar_t *__s2) __THROW;

/* Compare no more than N chars of S1 and S2, ignoring case.  */
extern int wcsncasecmp (const wchar_t *__s1, const wchar_t *__s2,
			size_t __n) __THROW;

/* Similar to the two functions above but take the information from
   the provided locale and not the global locale.  */
#if 0 /* expanded by -frewrite-includes */
# include <xlocale.h>
#endif /* expanded by -frewrite-includes */
# 183 "/usr/include/wchar.h" 3 4
# 184 "/usr/include/wchar.h" 3 4

extern int wcscasecmp_l (const wchar_t *__s1, const wchar_t *__s2,
			 __locale_t __loc) __THROW;

extern int wcsncasecmp_l (const wchar_t *__s1, const wchar_t *__s2,
			  size_t __n, __locale_t __loc) __THROW;
#endif
# 191 "/usr/include/wchar.h" 3 4

__BEGIN_NAMESPACE_STD
/* Compare S1 and S2, both interpreted as appropriate to the
   LC_COLLATE category of the current locale.  */
extern int wcscoll (const wchar_t *__s1, const wchar_t *__s2) __THROW;
/* Transform S2 into array pointed to by S1 such that if wcscmp is
   applied to two transformed strings the result is the as applying
   `wcscoll' to the original strings.  */
extern size_t wcsxfrm (wchar_t *__restrict __s1,
		       const wchar_t *__restrict __s2, size_t __n) __THROW;
__END_NAMESPACE_STD

#ifdef __USE_XOPEN2K8
/* Similar to the two functions above but take the information from
   the provided locale and not the global locale.  */

/* Compare S1 and S2, both interpreted as appropriate to the
   LC_COLLATE category of the given locale.  */
extern int wcscoll_l (const wchar_t *__s1, const wchar_t *__s2,
		      __locale_t __loc) __THROW;

/* Transform S2 into array pointed to by S1 such that if wcscmp is
   applied to two transformed strings the result is the as applying
   `wcscoll' to the original strings.  */
extern size_t wcsxfrm_l (wchar_t *__s1, const wchar_t *__s2,
			 size_t __n, __locale_t __loc) __THROW;

/* Duplicate S, returning an identical malloc'd string.  */
extern wchar_t *wcsdup (const wchar_t *__s) __THROW __attribute_malloc__;
#endif
# 221 "/usr/include/wchar.h" 3 4

__BEGIN_NAMESPACE_STD
/* Find the first occurrence of WC in WCS.  */
#ifdef __CORRECT_ISO_CPP_WCHAR_H_PROTO
extern "C++" wchar_t *wcschr (wchar_t *__wcs, wchar_t __wc)
     __THROW __asm ("wcschr") __attribute_pure__;
extern "C++" const wchar_t *wcschr (const wchar_t *__wcs, wchar_t __wc)
     __THROW __asm ("wcschr") __attribute_pure__;
#else
# 230 "/usr/include/wchar.h" 3 4
extern wchar_t *wcschr (const wchar_t *__wcs, wchar_t __wc)
     __THROW __attribute_pure__;
#endif
# 233 "/usr/include/wchar.h" 3 4
/* Find the last occurrence of WC in WCS.  */
#ifdef __CORRECT_ISO_CPP_WCHAR_H_PROTO
extern "C++" wchar_t *wcsrchr (wchar_t *__wcs, wchar_t __wc)
     __THROW __asm ("wcsrchr") __attribute_pure__;
extern "C++" const wchar_t *wcsrchr (const wchar_t *__wcs, wchar_t __wc)
     __THROW __asm ("wcsrchr") __attribute_pure__;
#else
# 240 "/usr/include/wchar.h" 3 4
extern wchar_t *wcsrchr (const wchar_t *__wcs, wchar_t __wc)
     __THROW __attribute_pure__;
#endif
# 243 "/usr/include/wchar.h" 3 4
__END_NAMESPACE_STD

#ifdef __USE_GNU
/* This function is similar to `wcschr'.  But it returns a pointer to
   the closing NUL wide character in case C is not found in S.  */
extern wchar_t *wcschrnul (const wchar_t *__s, wchar_t __wc)
     __THROW __attribute_pure__;
#endif
# 251 "/usr/include/wchar.h" 3 4

__BEGIN_NAMESPACE_STD
/* Return the length of the initial segmet of WCS which
   consists entirely of wide characters not in REJECT.  */
extern size_t wcscspn (const wchar_t *__wcs, const wchar_t *__reject)
     __THROW __attribute_pure__;
/* Return the length of the initial segmet of WCS which
   consists entirely of wide characters in  ACCEPT.  */
extern size_t wcsspn (const wchar_t *__wcs, const wchar_t *__accept)
     __THROW __attribute_pure__;
/* Find the first occurrence in WCS of any character in ACCEPT.  */
#ifdef __CORRECT_ISO_CPP_WCHAR_H_PROTO
extern "C++" wchar_t *wcspbrk (wchar_t *__wcs, const wchar_t *__accept)
     __THROW __asm ("wcspbrk") __attribute_pure__;
extern "C++" const wchar_t *wcspbrk (const wchar_t *__wcs,
				     const wchar_t *__accept)
     __THROW __asm ("wcspbrk") __attribute_pure__;
#else
# 269 "/usr/include/wchar.h" 3 4
extern wchar_t *wcspbrk (const wchar_t *__wcs, const wchar_t *__accept)
     __THROW __attribute_pure__;
#endif
# 272 "/usr/include/wchar.h" 3 4
/* Find the first occurrence of NEEDLE in HAYSTACK.  */
#ifdef __CORRECT_ISO_CPP_WCHAR_H_PROTO
extern "C++" wchar_t *wcsstr (wchar_t *__haystack, const wchar_t *__needle)
     __THROW __asm ("wcsstr") __attribute_pure__;
extern "C++" const wchar_t *wcsstr (const wchar_t *__haystack,
				    const wchar_t *__needle)
     __THROW __asm ("wcsstr") __attribute_pure__;
#else
# 280 "/usr/include/wchar.h" 3 4
extern wchar_t *wcsstr (const wchar_t *__haystack, const wchar_t *__needle)
     __THROW __attribute_pure__;
#endif
# 283 "/usr/include/wchar.h" 3 4

/* Divide WCS into tokens separated by characters in DELIM.  */
extern wchar_t *wcstok (wchar_t *__restrict __s,
			const wchar_t *__restrict __delim,
			wchar_t **__restrict __ptr) __THROW;

/* Return the number of wide characters in S.  */
extern size_t wcslen (const wchar_t *__s) __THROW __attribute_pure__;
__END_NAMESPACE_STD

#ifdef __USE_XOPEN
/* Another name for `wcsstr' from XPG4.  */
# ifdef __CORRECT_ISO_CPP_WCHAR_H_PROTO
extern "C++" wchar_t *wcswcs (wchar_t *__haystack, const wchar_t *__needle)
     __THROW __asm ("wcswcs") __attribute_pure__;
extern "C++" const wchar_t *wcswcs (const wchar_t *__haystack,
				    const wchar_t *__needle)
     __THROW __asm ("wcswcs") __attribute_pure__;
# else
# 302 "/usr/include/wchar.h" 3 4
extern wchar_t *wcswcs (const wchar_t *__haystack, const wchar_t *__needle)
     __THROW __attribute_pure__;
# endif
# 305 "/usr/include/wchar.h" 3 4
#endif
# 306 "/usr/include/wchar.h" 3 4

#ifdef __USE_XOPEN2K8
/* Return the number of wide characters in S, but at most MAXLEN.  */
extern size_t wcsnlen (const wchar_t *__s, size_t __maxlen)
     __THROW __attribute_pure__;
#endif
# 312 "/usr/include/wchar.h" 3 4


__BEGIN_NAMESPACE_STD
/* Search N wide characters of S for C.  */
#ifdef __CORRECT_ISO_CPP_WCHAR_H_PROTO
extern "C++" wchar_t *wmemchr (wchar_t *__s, wchar_t __c, size_t __n)
     __THROW __asm ("wmemchr") __attribute_pure__;
extern "C++" const wchar_t *wmemchr (const wchar_t *__s, wchar_t __c,
				     size_t __n)
     __THROW __asm ("wmemchr") __attribute_pure__;
#else
# 323 "/usr/include/wchar.h" 3 4
extern wchar_t *wmemchr (const wchar_t *__s, wchar_t __c, size_t __n)
     __THROW __attribute_pure__;
#endif
# 326 "/usr/include/wchar.h" 3 4

/* Compare N wide characters of S1 and S2.  */
extern int wmemcmp (const wchar_t *__s1, const wchar_t *__s2, size_t __n)
     __THROW __attribute_pure__;

/* Copy N wide characters of SRC to DEST.  */
extern wchar_t *wmemcpy (wchar_t *__restrict __s1,
			 const wchar_t *__restrict __s2, size_t __n) __THROW;

/* Copy N wide characters of SRC to DEST, guaranteeing
   correct behavior for overlapping strings.  */
extern wchar_t *wmemmove (wchar_t *__s1, const wchar_t *__s2, size_t __n)
     __THROW;

/* Set N wide characters of S to C.  */
extern wchar_t *wmemset (wchar_t *__s, wchar_t __c, size_t __n) __THROW;
__END_NAMESPACE_STD

#ifdef __USE_GNU
/* Copy N wide characters of SRC to DEST and return pointer to following
   wide character.  */
extern wchar_t *wmempcpy (wchar_t *__restrict __s1,
			  const wchar_t *__restrict __s2, size_t __n)
     __THROW;
#endif
# 351 "/usr/include/wchar.h" 3 4


__BEGIN_NAMESPACE_STD
/* Determine whether C constitutes a valid (one-byte) multibyte
   character.  */
extern wint_t btowc (int __c) __THROW;

/* Determine whether C corresponds to a member of the extended
   character set whose multibyte representation is a single byte.  */
extern int wctob (wint_t __c) __THROW;

/* Determine whether PS points to an object representing the initial
   state.  */
extern int mbsinit (const mbstate_t *__ps) __THROW __attribute_pure__;

/* Write wide character representation of multibyte character pointed
   to by S to PWC.  */
extern size_t mbrtowc (wchar_t *__restrict __pwc,
		       const char *__restrict __s, size_t __n,
		       mbstate_t *__restrict __p) __THROW;

/* Write multibyte representation of wide character WC to S.  */
extern size_t wcrtomb (char *__restrict __s, wchar_t __wc,
		       mbstate_t *__restrict __ps) __THROW;

/* Return number of bytes in multibyte character pointed to by S.  */
extern size_t __mbrlen (const char *__restrict __s, size_t __n,
			mbstate_t *__restrict __ps) __THROW;
extern size_t mbrlen (const char *__restrict __s, size_t __n,
		      mbstate_t *__restrict __ps) __THROW;
__END_NAMESPACE_STD

#ifdef __USE_EXTERN_INLINES
/* Define inline function as optimization.  */

/* We can use the BTOWC and WCTOB optimizations since we know that all
   locales must use ASCII encoding for the values in the ASCII range
   and because the wchar_t encoding is always ISO 10646.  */
extern wint_t __btowc_alias (int __c) __asm ("btowc");
__extern_inline wint_t
__NTH (btowc (int __c))
{ return (__builtin_constant_p (__c) && __c >= '\0' && __c <= '\x7f'
	  ? (wint_t) __c : __btowc_alias (__c)); }

extern int __wctob_alias (wint_t __c) __asm ("wctob");
__extern_inline int
__NTH (wctob (wint_t __wc))
{ return (__builtin_constant_p (__wc) && __wc >= L'\0' && __wc <= L'\x7f'
	  ? (int) __wc : __wctob_alias (__wc)); }

__extern_inline size_t
__NTH (mbrlen (const char *__restrict __s, size_t __n,
	       mbstate_t *__restrict __ps))
{ return (__ps != NULL
	  ? mbrtowc (NULL, __s, __n, __ps) : __mbrlen (__s, __n, NULL)); }
#endif
# 407 "/usr/include/wchar.h" 3 4

__BEGIN_NAMESPACE_STD
/* Write wide character representation of multibyte character string
   SRC to DST.  */
extern size_t mbsrtowcs (wchar_t *__restrict __dst,
			 const char **__restrict __src, size_t __len,
			 mbstate_t *__restrict __ps) __THROW;

/* Write multibyte character representation of wide character string
   SRC to DST.  */
extern size_t wcsrtombs (char *__restrict __dst,
			 const wchar_t **__restrict __src, size_t __len,
			 mbstate_t *__restrict __ps) __THROW;
__END_NAMESPACE_STD


#ifdef	__USE_XOPEN2K8
/* Write wide character representation of at most NMC bytes of the
   multibyte character string SRC to DST.  */
extern size_t mbsnrtowcs (wchar_t *__restrict __dst,
			  const char **__restrict __src, size_t __nmc,
			  size_t __len, mbstate_t *__restrict __ps) __THROW;

/* Write multibyte character representation of at most NWC characters
   from the wide character string SRC to DST.  */
extern size_t wcsnrtombs (char *__restrict __dst,
			  const wchar_t **__restrict __src,
			  size_t __nwc, size_t __len,
			  mbstate_t *__restrict __ps) __THROW;
#endif	/* use POSIX 2008 */
# 437 "/usr/include/wchar.h" 3 4


/* The following functions are extensions found in X/Open CAE.  */
#ifdef __USE_XOPEN
/* Determine number of column positions required for C.  */
extern int wcwidth (wchar_t __c) __THROW;

/* Determine number of column positions required for first N wide
   characters (or fewer if S ends before this) in S.  */
extern int wcswidth (const wchar_t *__s, size_t __n) __THROW;
#endif	/* Use X/Open.  */
# 448 "/usr/include/wchar.h" 3 4


__BEGIN_NAMESPACE_STD
/* Convert initial portion of the wide string NPTR to `double'
   representation.  */
extern double wcstod (const wchar_t *__restrict __nptr,
		      wchar_t **__restrict __endptr) __THROW;
__END_NAMESPACE_STD

#ifdef __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Likewise for `float' and `long double' sizes of floating-point numbers.  */
extern float wcstof (const wchar_t *__restrict __nptr,
		     wchar_t **__restrict __endptr) __THROW;
extern long double wcstold (const wchar_t *__restrict __nptr,
			    wchar_t **__restrict __endptr) __THROW;
__END_NAMESPACE_C99
#endif /* C99 */
# 466 "/usr/include/wchar.h" 3 4


__BEGIN_NAMESPACE_STD
/* Convert initial portion of wide string NPTR to `long int'
   representation.  */
extern long int wcstol (const wchar_t *__restrict __nptr,
			wchar_t **__restrict __endptr, int __base) __THROW;

/* Convert initial portion of wide string NPTR to `unsigned long int'
   representation.  */
extern unsigned long int wcstoul (const wchar_t *__restrict __nptr,
				  wchar_t **__restrict __endptr, int __base)
     __THROW;
__END_NAMESPACE_STD

#ifdef __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Convert initial portion of wide string NPTR to `long long int'
   representation.  */
__extension__
extern long long int wcstoll (const wchar_t *__restrict __nptr,
			      wchar_t **__restrict __endptr, int __base)
     __THROW;

/* Convert initial portion of wide string NPTR to `unsigned long long int'
   representation.  */
__extension__
extern unsigned long long int wcstoull (const wchar_t *__restrict __nptr,
					wchar_t **__restrict __endptr,
					int __base) __THROW;
__END_NAMESPACE_C99
#endif /* ISO C99.  */
# 498 "/usr/include/wchar.h" 3 4

#ifdef __USE_GNU
/* Convert initial portion of wide string NPTR to `long long int'
   representation.  */
__extension__
extern long long int wcstoq (const wchar_t *__restrict __nptr,
			     wchar_t **__restrict __endptr, int __base)
     __THROW;

/* Convert initial portion of wide string NPTR to `unsigned long long int'
   representation.  */
__extension__
extern unsigned long long int wcstouq (const wchar_t *__restrict __nptr,
				       wchar_t **__restrict __endptr,
				       int __base) __THROW;
#endif /* Use GNU.  */
# 514 "/usr/include/wchar.h" 3 4

#ifdef __USE_GNU
/* The concept of one static locale per category is not very well
   thought out.  Many applications will need to process its data using
   information from several different locales.  Another application is
   the implementation of the internationalization handling in the
   upcoming ISO C++ standard library.  To support this another set of
   the functions using locale data exist which have an additional
   argument.

   Attention: all these functions are *not* standardized in any form.
   This is a proof-of-concept implementation.  */

/* Structure for reentrant locale using functions.  This is an
   (almost) opaque type for the user level programs.  */
#if 0 /* expanded by -frewrite-includes */
# include <xlocale.h>
#endif /* expanded by -frewrite-includes */
# 529 "/usr/include/wchar.h" 3 4
# 530 "/usr/include/wchar.h" 3 4

/* Special versions of the functions above which take the locale to
   use as an additional parameter.  */
extern long int wcstol_l (const wchar_t *__restrict __nptr,
			  wchar_t **__restrict __endptr, int __base,
			  __locale_t __loc) __THROW;

extern unsigned long int wcstoul_l (const wchar_t *__restrict __nptr,
				    wchar_t **__restrict __endptr,
				    int __base, __locale_t __loc) __THROW;

__extension__
extern long long int wcstoll_l (const wchar_t *__restrict __nptr,
				wchar_t **__restrict __endptr,
				int __base, __locale_t __loc) __THROW;

__extension__
extern unsigned long long int wcstoull_l (const wchar_t *__restrict __nptr,
					  wchar_t **__restrict __endptr,
					  int __base, __locale_t __loc)
     __THROW;

extern double wcstod_l (const wchar_t *__restrict __nptr,
			wchar_t **__restrict __endptr, __locale_t __loc)
     __THROW;

extern float wcstof_l (const wchar_t *__restrict __nptr,
		       wchar_t **__restrict __endptr, __locale_t __loc)
     __THROW;

extern long double wcstold_l (const wchar_t *__restrict __nptr,
			      wchar_t **__restrict __endptr,
			      __locale_t __loc) __THROW;
#endif	/* use GNU */
# 564 "/usr/include/wchar.h" 3 4


#ifdef __USE_XOPEN2K8
/* Copy SRC to DEST, returning the address of the terminating L'\0' in
   DEST.  */
extern wchar_t *wcpcpy (wchar_t *__restrict __dest,
			const wchar_t *__restrict __src) __THROW;

/* Copy no more than N characters of SRC to DEST, returning the address of
   the last character written into DEST.  */
extern wchar_t *wcpncpy (wchar_t *__restrict __dest,
			 const wchar_t *__restrict __src, size_t __n)
     __THROW;


/* Wide character I/O functions.  */

/* Like OPEN_MEMSTREAM, but the stream is wide oriented and produces
   a wide character string.  */
extern __FILE *open_wmemstream (wchar_t **__bufloc, size_t *__sizeloc) __THROW;
#endif
# 585 "/usr/include/wchar.h" 3 4

#if defined __USE_ISOC95 || defined __USE_UNIX98
__BEGIN_NAMESPACE_STD

/* Select orientation for stream.  */
extern int fwide (__FILE *__fp, int __mode) __THROW;


/* Write formatted output to STREAM.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int fwprintf (__FILE *__restrict __stream,
		     const wchar_t *__restrict __format, ...)
     /* __attribute__ ((__format__ (__wprintf__, 2, 3))) */;
/* Write formatted output to stdout.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int wprintf (const wchar_t *__restrict __format, ...)
     /* __attribute__ ((__format__ (__wprintf__, 1, 2))) */;
/* Write formatted output of at most N characters to S.  */
extern int swprintf (wchar_t *__restrict __s, size_t __n,
		     const wchar_t *__restrict __format, ...)
     __THROW /* __attribute__ ((__format__ (__wprintf__, 3, 4))) */;

/* Write formatted output to S from argument list ARG.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int vfwprintf (__FILE *__restrict __s,
		      const wchar_t *__restrict __format,
		      __gnuc_va_list __arg)
     /* __attribute__ ((__format__ (__wprintf__, 2, 0))) */;
/* Write formatted output to stdout from argument list ARG.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int vwprintf (const wchar_t *__restrict __format,
		     __gnuc_va_list __arg)
     /* __attribute__ ((__format__ (__wprintf__, 1, 0))) */;
/* Write formatted output of at most N character to S from argument
   list ARG.  */
extern int vswprintf (wchar_t *__restrict __s, size_t __n,
		      const wchar_t *__restrict __format,
		      __gnuc_va_list __arg)
     __THROW /* __attribute__ ((__format__ (__wprintf__, 3, 0))) */;


/* Read formatted input from STREAM.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int fwscanf (__FILE *__restrict __stream,
		    const wchar_t *__restrict __format, ...)
     /* __attribute__ ((__format__ (__wscanf__, 2, 3))) */;
/* Read formatted input from stdin.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int wscanf (const wchar_t *__restrict __format, ...)
     /* __attribute__ ((__format__ (__wscanf__, 1, 2))) */;
/* Read formatted input from S.  */
extern int swscanf (const wchar_t *__restrict __s,
		    const wchar_t *__restrict __format, ...)
     __THROW /* __attribute__ ((__format__ (__wscanf__, 2, 3))) */;

# if defined __USE_ISOC99 && !defined __USE_GNU \
     && (!defined __LDBL_COMPAT || !defined __REDIRECT) \
     && (defined __STRICT_ANSI__ || defined __USE_XOPEN2K)
#  ifdef __REDIRECT
/* For strict ISO C99 or POSIX compliance disallow %as, %aS and %a[
   GNU extension which conflicts with valid %a followed by letter
   s, S or [.  */
extern int __REDIRECT (fwscanf, (__FILE *__restrict __stream,
				 const wchar_t *__restrict __format, ...),
		       __isoc99_fwscanf)
     /* __attribute__ ((__format__ (__wscanf__, 2, 3))) */;
extern int __REDIRECT (wscanf, (const wchar_t *__restrict __format, ...),
		       __isoc99_wscanf)
     /* __attribute__ ((__format__ (__wscanf__, 1, 2))) */;
extern int __REDIRECT_NTH (swscanf, (const wchar_t *__restrict __s,
				     const wchar_t *__restrict __format,
				     ...), __isoc99_swscanf)
     /* __attribute__ ((__format__ (__wscanf__, 2, 3))) */;
#  else
# 671 "/usr/include/wchar.h" 3 4
extern int __isoc99_fwscanf (__FILE *__restrict __stream,
			     const wchar_t *__restrict __format, ...);
extern int __isoc99_wscanf (const wchar_t *__restrict __format, ...);
extern int __isoc99_swscanf (const wchar_t *__restrict __s,
			     const wchar_t *__restrict __format, ...)
     __THROW;
#   define fwscanf __isoc99_fwscanf
#   define wscanf __isoc99_wscanf
#   define swscanf __isoc99_swscanf
#  endif
# 681 "/usr/include/wchar.h" 3 4
# endif
# 682 "/usr/include/wchar.h" 3 4

__END_NAMESPACE_STD
#endif /* Use ISO C95, C99 and Unix98. */
# 685 "/usr/include/wchar.h" 3 4

#ifdef __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Read formatted input from S into argument list ARG.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int vfwscanf (__FILE *__restrict __s,
		     const wchar_t *__restrict __format,
		     __gnuc_va_list __arg)
     /* __attribute__ ((__format__ (__wscanf__, 2, 0))) */;
/* Read formatted input from stdin into argument list ARG.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int vwscanf (const wchar_t *__restrict __format,
		    __gnuc_va_list __arg)
     /* __attribute__ ((__format__ (__wscanf__, 1, 0))) */;
/* Read formatted input from S into argument list ARG.  */
extern int vswscanf (const wchar_t *__restrict __s,
		     const wchar_t *__restrict __format,
		     __gnuc_va_list __arg)
     __THROW /* __attribute__ ((__format__ (__wscanf__, 2, 0))) */;

# if !defined __USE_GNU \
     && (!defined __LDBL_COMPAT || !defined __REDIRECT) \
     && (defined __STRICT_ANSI__ || defined __USE_XOPEN2K)
#  ifdef __REDIRECT
extern int __REDIRECT (vfwscanf, (__FILE *__restrict __s,
				  const wchar_t *__restrict __format,
				  __gnuc_va_list __arg), __isoc99_vfwscanf)
     /* __attribute__ ((__format__ (__wscanf__, 2, 0))) */;
extern int __REDIRECT (vwscanf, (const wchar_t *__restrict __format,
				 __gnuc_va_list __arg), __isoc99_vwscanf)
     /* __attribute__ ((__format__ (__wscanf__, 1, 0))) */;
extern int __REDIRECT_NTH (vswscanf, (const wchar_t *__restrict __s,
				      const wchar_t *__restrict __format,
				      __gnuc_va_list __arg), __isoc99_vswscanf)
     /* __attribute__ ((__format__ (__wscanf__, 2, 0))) */;
#  else
# 725 "/usr/include/wchar.h" 3 4
extern int __isoc99_vfwscanf (__FILE *__restrict __s,
			      const wchar_t *__restrict __format,
			      __gnuc_va_list __arg);
extern int __isoc99_vwscanf (const wchar_t *__restrict __format,
			     __gnuc_va_list __arg);
extern int __isoc99_vswscanf (const wchar_t *__restrict __s,
			      const wchar_t *__restrict __format,
			      __gnuc_va_list __arg) __THROW;
#   define vfwscanf __isoc99_vfwscanf
#   define vwscanf __isoc99_vwscanf
#   define vswscanf __isoc99_vswscanf
#  endif
# 737 "/usr/include/wchar.h" 3 4
# endif
# 738 "/usr/include/wchar.h" 3 4

__END_NAMESPACE_C99
#endif /* Use ISO C99. */
# 741 "/usr/include/wchar.h" 3 4


__BEGIN_NAMESPACE_STD
/* Read a character from STREAM.

   These functions are possible cancellation points and therefore not
   marked with __THROW.  */
extern wint_t fgetwc (__FILE *__stream);
extern wint_t getwc (__FILE *__stream);

/* Read a character from stdin.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern wint_t getwchar (void);


/* Write a character to STREAM.

   These functions are possible cancellation points and therefore not
   marked with __THROW.  */
extern wint_t fputwc (wchar_t __wc, __FILE *__stream);
extern wint_t putwc (wchar_t __wc, __FILE *__stream);

/* Write a character to stdout.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern wint_t putwchar (wchar_t __wc);


/* Get a newline-terminated wide character string of finite length
   from STREAM.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern wchar_t *fgetws (wchar_t *__restrict __ws, int __n,
			__FILE *__restrict __stream);

/* Write a string to STREAM.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int fputws (const wchar_t *__restrict __ws,
		   __FILE *__restrict __stream);


/* Push a character back onto the input buffer of STREAM.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern wint_t ungetwc (wint_t __wc, __FILE *__stream);
__END_NAMESPACE_STD


#ifdef __USE_GNU
/* These are defined to be equivalent to the `char' functions defined
   in POSIX.1:1996.

   These functions are not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation they are cancellation points and
   therefore not marked with __THROW.  */
extern wint_t getwc_unlocked (__FILE *__stream);
extern wint_t getwchar_unlocked (void);

/* This is the wide character version of a GNU extension.

   This function is not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation it is a cancellation point and
   therefore not marked with __THROW.  */
extern wint_t fgetwc_unlocked (__FILE *__stream);

/* Faster version when locking is not necessary.

   This function is not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation it is a cancellation point and
   therefore not marked with __THROW.  */
extern wint_t fputwc_unlocked (wchar_t __wc, __FILE *__stream);

/* These are defined to be equivalent to the `char' functions defined
   in POSIX.1:1996.

   These functions are not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation they are cancellation points and
   therefore not marked with __THROW.  */
extern wint_t putwc_unlocked (wchar_t __wc, __FILE *__stream);
extern wint_t putwchar_unlocked (wchar_t __wc);


/* This function does the same as `fgetws' but does not lock the stream.

   This function is not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation it is a cancellation point and
   therefore not marked with __THROW.  */
extern wchar_t *fgetws_unlocked (wchar_t *__restrict __ws, int __n,
				 __FILE *__restrict __stream);

/* This function does the same as `fputws' but does not lock the stream.

   This function is not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation it is a cancellation point and
   therefore not marked with __THROW.  */
extern int fputws_unlocked (const wchar_t *__restrict __ws,
			    __FILE *__restrict __stream);
#endif
# 852 "/usr/include/wchar.h" 3 4


__BEGIN_NAMESPACE_C99
/* Format TP into S according to FORMAT.
   Write no more than MAXSIZE wide characters and return the number
   of wide characters written, or 0 if it would exceed MAXSIZE.  */
extern size_t wcsftime (wchar_t *__restrict __s, size_t __maxsize,
			const wchar_t *__restrict __format,
			const struct tm *__restrict __tp) __THROW;
__END_NAMESPACE_C99

# ifdef __USE_GNU
#if 0 /* expanded by -frewrite-includes */
# include <xlocale.h>
#endif /* expanded by -frewrite-includes */
# 864 "/usr/include/wchar.h" 3 4
# 865 "/usr/include/wchar.h" 3 4

/* Similar to `wcsftime' but takes the information from
   the provided locale and not the global locale.  */
extern size_t wcsftime_l (wchar_t *__restrict __s, size_t __maxsize,
			  const wchar_t *__restrict __format,
			  const struct tm *__restrict __tp,
			  __locale_t __loc) __THROW;
# endif
# 873 "/usr/include/wchar.h" 3 4

/* The X/Open standard demands that most of the functions defined in
   the <wctype.h> header must also appear here.  This is probably
   because some X/Open members wrote their implementation before the
   ISO C standard was published and introduced the better solution.
   We have to provide these definitions for compliance reasons but we
   do this nonsense only if really necessary.  */
#if defined __USE_UNIX98 && !defined __USE_GNU
# define __need_iswxxx
#if 0 /* expanded by -frewrite-includes */
# include <wctype.h>
#endif /* expanded by -frewrite-includes */
# 882 "/usr/include/wchar.h" 3 4
# 883 "/usr/include/wchar.h" 3 4
#endif
# 884 "/usr/include/wchar.h" 3 4

/* Define some macros helping to catch buffer overflows.  */
#if __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
#if 0 /* expanded by -frewrite-includes */
# include <bits/wchar2.h>
#endif /* expanded by -frewrite-includes */
# 887 "/usr/include/wchar.h" 3 4
# 888 "/usr/include/wchar.h" 3 4
#endif
# 889 "/usr/include/wchar.h" 3 4

#ifdef __LDBL_COMPAT
#if 0 /* expanded by -frewrite-includes */
# include <bits/wchar-ldbl.h>
#endif /* expanded by -frewrite-includes */
# 891 "/usr/include/wchar.h" 3 4
# 892 "/usr/include/wchar.h" 3 4
#endif
# 893 "/usr/include/wchar.h" 3 4

__END_DECLS

#endif	/* _WCHAR_H defined */
# 897 "/usr/include/wchar.h" 3 4

#endif /* wchar.h  */
# 899 "/usr/include/wchar.h" 3 4

/* Undefine all __need_* constants in case we are included to get those
   constants but the whole file was already read.  */
#undef __need_mbstate_t
#undef __need_wint_t
# 21 "/usr/include/_G_config.h" 2 3 4
typedef struct
{
  __off_t __pos;
  __mbstate_t __state;
} _G_fpos_t;
typedef struct
{
  __off64_t __pos;
  __mbstate_t __state;
} _G_fpos64_t;
#if defined _LIBC || defined _GLIBCPP_USE_WCHAR_T
#if 0 /* expanded by -frewrite-includes */
# include <gconv.h>
#endif /* expanded by -frewrite-includes */
# 32 "/usr/include/_G_config.h" 3 4
# 33 "/usr/include/_G_config.h" 3 4
typedef union
{
  struct __gconv_info __cd;
  struct
  {
    struct __gconv_info __cd;
    struct __gconv_step_data __data;
  } __combined;
} _G_iconv_t;
#endif
# 43 "/usr/include/_G_config.h" 3 4


/* These library features are always available in the GNU C library.  */
#define _G_va_list __gnuc_va_list

#define _G_HAVE_MMAP 1
#define _G_HAVE_MREMAP 1

#define _G_IO_IO_FILE_VERSION 0x20001

/* This is defined by <bits/stat.h> if `st_blksize' exists.  */
#define _G_HAVE_ST_BLKSIZE defined (_STATBUF_ST_BLKSIZE)

#define _G_BUFSIZ 8192

#endif	/* _G_config.h */
# 59 "/usr/include/_G_config.h" 3 4
# 32 "/usr/include/libio.h" 2 3 4
/* ALL of these should be defined in _G_config.h */
#define _IO_fpos_t _G_fpos_t
#define _IO_fpos64_t _G_fpos64_t
#define _IO_size_t size_t
#define _IO_ssize_t __ssize_t
#define _IO_off_t __off_t
#define _IO_off64_t __off64_t
#define _IO_pid_t __pid_t
#define _IO_uid_t __uid_t
#define _IO_iconv_t _G_iconv_t
#define _IO_HAVE_ST_BLKSIZE _G_HAVE_ST_BLKSIZE
#define _IO_BUFSIZ _G_BUFSIZ
#define _IO_va_list _G_va_list
#define _IO_wint_t wint_t

/* This define avoids name pollution if we're using GNU stdarg.h */
#define __need___va_list
#if 0 /* expanded by -frewrite-includes */
#include <stdarg.h>
#endif /* expanded by -frewrite-includes */
# 49 "/usr/include/libio.h" 3 4
# 1 "/root/build/llvm/release/lib/clang/5.0.0/include/stdarg.h" 1 3 4
/*===---- stdarg.h - Variable argument handling ----------------------------===
 *
 * Copyright (c) 2008 Eli Friedman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *===-----------------------------------------------------------------------===
 */

#ifndef __STDARG_H
#define __STDARG_H

#ifndef _VA_LIST
typedef __builtin_va_list va_list;
#define _VA_LIST
#endif
# 33 "/root/build/llvm/release/lib/clang/5.0.0/include/stdarg.h" 3 4
#define va_start(ap, param) __builtin_va_start(ap, param)
#define va_end(ap)          __builtin_va_end(ap)
#define va_arg(ap, type)    __builtin_va_arg(ap, type)

/* GCC always defines __va_copy, but does not define va_copy unless in c99 mode
 * or -ansi is not specified, since it was not part of C90.
 */
#define __va_copy(d,s) __builtin_va_copy(d,s)

#if __STDC_VERSION__ >= 199901L || __cplusplus >= 201103L || !defined(__STRICT_ANSI__)
#define va_copy(dest, src)  __builtin_va_copy(dest, src)
#endif
# 45 "/root/build/llvm/release/lib/clang/5.0.0/include/stdarg.h" 3 4

#ifndef __GNUC_VA_LIST
#define __GNUC_VA_LIST 1
typedef __builtin_va_list __gnuc_va_list;
#endif
# 50 "/root/build/llvm/release/lib/clang/5.0.0/include/stdarg.h" 3 4

#endif /* __STDARG_H */
# 52 "/root/build/llvm/release/lib/clang/5.0.0/include/stdarg.h" 3 4
# 50 "/usr/include/libio.h" 2 3 4
#ifdef __GNUC_VA_LIST
# undef _IO_va_list
# define _IO_va_list __gnuc_va_list
#endif /* __GNUC_VA_LIST */
# 54 "/usr/include/libio.h" 3 4

#ifndef __P
#if 0 /* expanded by -frewrite-includes */
# include <sys/cdefs.h>
#endif /* expanded by -frewrite-includes */
# 56 "/usr/include/libio.h" 3 4
# 57 "/usr/include/libio.h" 3 4
#endif /*!__P*/
# 58 "/usr/include/libio.h" 3 4

#define _IO_UNIFIED_JUMPTABLES 1

#ifndef EOF
# define EOF (-1)
#endif
# 64 "/usr/include/libio.h" 3 4
#ifndef NULL
# if defined __GNUG__ && \
    (__GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 8))
#  define NULL (__null)
# else
# 69 "/usr/include/libio.h" 3 4
#  if !defined(__cplusplus)
#   define NULL ((void*)0)
#  else
# 72 "/usr/include/libio.h" 3 4
#   define NULL (0)
#  endif
# 74 "/usr/include/libio.h" 3 4
# endif
# 75 "/usr/include/libio.h" 3 4
#endif
# 76 "/usr/include/libio.h" 3 4

#define _IOS_INPUT	1
#define _IOS_OUTPUT	2
#define _IOS_ATEND	4
#define _IOS_APPEND	8
#define _IOS_TRUNC	16
#define _IOS_NOCREATE	32
#define _IOS_NOREPLACE	64
#define _IOS_BIN	128

/* Magic numbers and bits for the _flags field.
   The magic numbers use the high-order bits of _flags;
   the remaining bits are available for variable flags.
   Note: The magic numbers must all be negative if stdio
   emulation is desired. */

#define _IO_MAGIC 0xFBAD0000 /* Magic number */
#define _OLD_STDIO_MAGIC 0xFABC0000 /* Emulate old stdio. */
#define _IO_MAGIC_MASK 0xFFFF0000
#define _IO_USER_BUF 1 /* User owns buffer; don't delete it on close. */
#define _IO_UNBUFFERED 2
#define _IO_NO_READS 4 /* Reading not allowed */
#define _IO_NO_WRITES 8 /* Writing not allowd */
#define _IO_EOF_SEEN 0x10
#define _IO_ERR_SEEN 0x20
#define _IO_DELETE_DONT_CLOSE 0x40 /* Don't call close(_fileno) on cleanup. */
#define _IO_LINKED 0x80 /* Set if linked (using _chain) to streambuf::_list_all.*/
#define _IO_IN_BACKUP 0x100
#define _IO_LINE_BUF 0x200
#define _IO_TIED_PUT_GET 0x400 /* Set if put and get pointer logicly tied. */
#define _IO_CURRENTLY_PUTTING 0x800
#define _IO_IS_APPENDING 0x1000
#define _IO_IS_FILEBUF 0x2000
#define _IO_BAD_SEEN 0x4000
#define _IO_USER_LOCK 0x8000

#define _IO_FLAGS2_MMAP 1
#define _IO_FLAGS2_NOTCANCEL 2
#ifdef _LIBC
# define _IO_FLAGS2_FORTIFY 4
#endif
# 117 "/usr/include/libio.h" 3 4
#define _IO_FLAGS2_USER_WBUF 8
#ifdef _LIBC
# define _IO_FLAGS2_SCANF_STD 16
# define _IO_FLAGS2_NOCLOSE 32
# define _IO_FLAGS2_CLOEXEC 64
#endif
# 123 "/usr/include/libio.h" 3 4

/* These are "formatting flags" matching the iostream fmtflags enum values. */
#define _IO_SKIPWS 01
#define _IO_LEFT 02
#define _IO_RIGHT 04
#define _IO_INTERNAL 010
#define _IO_DEC 020
#define _IO_OCT 040
#define _IO_HEX 0100
#define _IO_SHOWBASE 0200
#define _IO_SHOWPOINT 0400
#define _IO_UPPERCASE 01000
#define _IO_SHOWPOS 02000
#define _IO_SCIENTIFIC 04000
#define _IO_FIXED 010000
#define _IO_UNITBUF 020000
#define _IO_STDIO 040000
#define _IO_DONT_CLOSE 0100000
#define _IO_BOOLALPHA 0200000


struct _IO_jump_t;  struct _IO_FILE;

/* Handle lock.  */
#ifdef _IO_MTSAFE_IO
/* _IO_lock_t defined in internal headers during the glibc build.  */
#else
# 150 "/usr/include/libio.h" 3 4
typedef void _IO_lock_t;
#endif
# 152 "/usr/include/libio.h" 3 4


/* A streammarker remembers a position in a buffer. */

struct _IO_marker {
  struct _IO_marker *_next;
  struct _IO_FILE *_sbuf;
  /* If _pos >= 0
 it points to _buf->Gbase()+_pos. FIXME comment */
  /* if _pos < 0, it points to _buf->eBptr()+_pos. FIXME comment */
  int _pos;
#if 0
    void set_streampos(streampos sp) { _spos = sp; }
    void set_offset(int offset) { _pos = offset; _spos = (streampos)(-2); }
  public:
    streammarker(streambuf *sb);
    ~streammarker();
    int saving() { return  _spos == -2; }
    int delta(streammarker&);
    int delta();
#endif
# 173 "/usr/include/libio.h" 3 4
};

/* This is the structure from the libstdc++ codecvt class.  */
enum __codecvt_result
{
  __codecvt_ok,
  __codecvt_partial,
  __codecvt_error,
  __codecvt_noconv
};

#if defined _LIBC || defined _GLIBCPP_USE_WCHAR_T
/* The order of the elements in the following struct must match the order
   of the virtual functions in the libstdc++ codecvt class.  */
struct _IO_codecvt
{
  void (*__codecvt_destr) (struct _IO_codecvt *);
  enum __codecvt_result (*__codecvt_do_out) (struct _IO_codecvt *,
					     __mbstate_t *,
					     const wchar_t *,
					     const wchar_t *,
					     const wchar_t **, char *,
					     char *, char **);
  enum __codecvt_result (*__codecvt_do_unshift) (struct _IO_codecvt *,
						 __mbstate_t *, char *,
						 char *, char **);
  enum __codecvt_result (*__codecvt_do_in) (struct _IO_codecvt *,
					    __mbstate_t *,
					    const char *, const char *,
					    const char **, wchar_t *,
					    wchar_t *, wchar_t **);
  int (*__codecvt_do_encoding) (struct _IO_codecvt *);
  int (*__codecvt_do_always_noconv) (struct _IO_codecvt *);
  int (*__codecvt_do_length) (struct _IO_codecvt *, __mbstate_t *,
			      const char *, const char *, _IO_size_t);
  int (*__codecvt_do_max_length) (struct _IO_codecvt *);

  _IO_iconv_t __cd_in;
  _IO_iconv_t __cd_out;
};

/* Extra data for wide character streams.  */
struct _IO_wide_data
{
  wchar_t *_IO_read_ptr;	/* Current read pointer */
  wchar_t *_IO_read_end;	/* End of get area. */
  wchar_t *_IO_read_base;	/* Start of putback+get area. */
  wchar_t *_IO_write_base;	/* Start of put area. */
  wchar_t *_IO_write_ptr;	/* Current put pointer. */
  wchar_t *_IO_write_end;	/* End of put area. */
  wchar_t *_IO_buf_base;	/* Start of reserve area. */
  wchar_t *_IO_buf_end;		/* End of reserve area. */
  /* The following fields are used to support backing up and undo. */
  wchar_t *_IO_save_base;	/* Pointer to start of non-current get area. */
  wchar_t *_IO_backup_base;	/* Pointer to first valid character of
				   backup area */
  wchar_t *_IO_save_end;	/* Pointer to end of non-current get area. */

  __mbstate_t _IO_state;
  __mbstate_t _IO_last_state;
  struct _IO_codecvt _codecvt;

  wchar_t _shortbuf[1];

  const struct _IO_jump_t *_wide_vtable;
};
#endif
# 240 "/usr/include/libio.h" 3 4

struct _IO_FILE {
  int _flags;		/* High-order word is _IO_MAGIC; rest is flags. */
#define _IO_file_flags _flags

  /* The following pointers correspond to the C++ streambuf protocol. */
  /* Note:  Tk uses the _IO_read_ptr and _IO_read_end fields directly. */
  char* _IO_read_ptr;	/* Current read pointer */
  char* _IO_read_end;	/* End of get area. */
  char* _IO_read_base;	/* Start of putback+get area. */
  char* _IO_write_base;	/* Start of put area. */
  char* _IO_write_ptr;	/* Current put pointer. */
  char* _IO_write_end;	/* End of put area. */
  char* _IO_buf_base;	/* Start of reserve area. */
  char* _IO_buf_end;	/* End of reserve area. */
  /* The following fields are used to support backing up and undo. */
  char *_IO_save_base; /* Pointer to start of non-current get area. */
  char *_IO_backup_base;  /* Pointer to first valid character of backup area */
  char *_IO_save_end; /* Pointer to end of non-current get area. */

  struct _IO_marker *_markers;

  struct _IO_FILE *_chain;

  int _fileno;
#if 0
  int _blksize;
#else
# 268 "/usr/include/libio.h" 3 4
  int _flags2;
#endif
# 270 "/usr/include/libio.h" 3 4
  _IO_off_t _old_offset; /* This used to be _offset but it's too small.  */

#define __HAVE_COLUMN /* temporary */
  /* 1+column number of pbase(); 0 is unknown. */
  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];

  /*  char* _save_gptr;  char* _save_egptr; */

  _IO_lock_t *_lock;
#ifdef _IO_USE_OLD_IO_FILE
};

struct _IO_FILE_complete
{
  struct _IO_FILE _file;
#endif
# 288 "/usr/include/libio.h" 3 4
#if defined _G_IO_IO_FILE_VERSION && _G_IO_IO_FILE_VERSION == 0x20001
  _IO_off64_t _offset;
# if defined _LIBC || defined _GLIBCPP_USE_WCHAR_T
  /* Wide character stream stuff.  */
  struct _IO_codecvt *_codecvt;
  struct _IO_wide_data *_wide_data;
  struct _IO_FILE *_freeres_list;
  void *_freeres_buf;
# else
# 297 "/usr/include/libio.h" 3 4
  void *__pad1;
  void *__pad2;
  void *__pad3;
  void *__pad4;
# endif
# 302 "/usr/include/libio.h" 3 4
  size_t __pad5;
  int _mode;
  /* Make sure we don't get into trouble again.  */
  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];
#endif
# 307 "/usr/include/libio.h" 3 4
};

#ifndef __cplusplus
typedef struct _IO_FILE _IO_FILE;
#endif
# 312 "/usr/include/libio.h" 3 4

struct _IO_FILE_plus;

extern struct _IO_FILE_plus _IO_2_1_stdin_;
extern struct _IO_FILE_plus _IO_2_1_stdout_;
extern struct _IO_FILE_plus _IO_2_1_stderr_;
#ifndef _LIBC
#define _IO_stdin ((_IO_FILE*)(&_IO_2_1_stdin_))
#define _IO_stdout ((_IO_FILE*)(&_IO_2_1_stdout_))
#define _IO_stderr ((_IO_FILE*)(&_IO_2_1_stderr_))
#else
# 323 "/usr/include/libio.h" 3 4
extern _IO_FILE *_IO_stdin attribute_hidden;
extern _IO_FILE *_IO_stdout attribute_hidden;
extern _IO_FILE *_IO_stderr attribute_hidden;
#endif
# 327 "/usr/include/libio.h" 3 4


/* Functions to do I/O and file management for a stream.  */

/* Read NBYTES bytes from COOKIE into a buffer pointed to by BUF.
   Return number of bytes read.  */
typedef __ssize_t __io_read_fn (void *__cookie, char *__buf, size_t __nbytes);

/* Write N bytes pointed to by BUF to COOKIE.  Write all N bytes
   unless there is an error.  Return number of bytes written.  If
   there is an error, return 0 and do not write anything.  If the file
   has been opened for append (__mode.__append set), then set the file
   pointer to the end of the file and then do the write; if not, just
   write at the current file pointer.  */
typedef __ssize_t __io_write_fn (void *__cookie, const char *__buf,
				 size_t __n);

/* Move COOKIE's file position to *POS bytes from the
   beginning of the file (if W is SEEK_SET),
   the current position (if W is SEEK_CUR),
   or the end of the file (if W is SEEK_END).
   Set *POS to the new file position.
   Returns zero if successful, nonzero if not.  */
typedef int __io_seek_fn (void *__cookie, _IO_off64_t *__pos, int __w);

/* Close COOKIE.  */
typedef int __io_close_fn (void *__cookie);


#ifdef _GNU_SOURCE
/* User-visible names for the above.  */
typedef __io_read_fn cookie_read_function_t;
typedef __io_write_fn cookie_write_function_t;
typedef __io_seek_fn cookie_seek_function_t;
typedef __io_close_fn cookie_close_function_t;

/* The structure with the cookie function pointers.  */
typedef struct
{
  __io_read_fn *read;		/* Read bytes.  */
  __io_write_fn *write;		/* Write bytes.  */
  __io_seek_fn *seek;		/* Seek/tell file position.  */
  __io_close_fn *close;		/* Close file.  */
} _IO_cookie_io_functions_t;
typedef _IO_cookie_io_functions_t cookie_io_functions_t;

struct _IO_cookie_file;

/* Initialize one of those.  */
extern void _IO_cookie_init (struct _IO_cookie_file *__cfile, int __read_write,
			     void *__cookie, _IO_cookie_io_functions_t __fns);
#endif
# 379 "/usr/include/libio.h" 3 4


#ifdef __cplusplus
extern "C" {
#endif
# 384 "/usr/include/libio.h" 3 4

extern int __underflow (_IO_FILE *);
extern int __uflow (_IO_FILE *);
extern int __overflow (_IO_FILE *, int);
#if defined _LIBC || defined _GLIBCPP_USE_WCHAR_T
extern _IO_wint_t __wunderflow (_IO_FILE *);
extern _IO_wint_t __wuflow (_IO_FILE *);
extern _IO_wint_t __woverflow (_IO_FILE *, _IO_wint_t);
#endif
# 393 "/usr/include/libio.h" 3 4

#if  __GNUC__ >= 3
# define _IO_BE(expr, res) __builtin_expect ((expr), res)
#else
# 397 "/usr/include/libio.h" 3 4
# define _IO_BE(expr, res) (expr)
#endif
# 399 "/usr/include/libio.h" 3 4

#define _IO_getc_unlocked(_fp) \
       (_IO_BE ((_fp)->_IO_read_ptr >= (_fp)->_IO_read_end, 0) \
	? __uflow (_fp) : *(unsigned char *) (_fp)->_IO_read_ptr++)
#define _IO_peekc_unlocked(_fp) \
       (_IO_BE ((_fp)->_IO_read_ptr >= (_fp)->_IO_read_end, 0) \
	  && __underflow (_fp) == EOF ? EOF \
	: *(unsigned char *) (_fp)->_IO_read_ptr)
#define _IO_putc_unlocked(_ch, _fp) \
   (_IO_BE ((_fp)->_IO_write_ptr >= (_fp)->_IO_write_end, 0) \
    ? __overflow (_fp, (unsigned char) (_ch)) \
    : (unsigned char) (*(_fp)->_IO_write_ptr++ = (_ch)))

#if defined _LIBC || defined _GLIBCPP_USE_WCHAR_T
# define _IO_getwc_unlocked(_fp) \
  (_IO_BE ((_fp)->_wide_data == NULL					\
	   || ((_fp)->_wide_data->_IO_read_ptr				\
	       >= (_fp)->_wide_data->_IO_read_end), 0)			\
   ? __wuflow (_fp) : (_IO_wint_t) *(_fp)->_wide_data->_IO_read_ptr++)
# define _IO_putwc_unlocked(_wch, _fp) \
  (_IO_BE ((_fp)->_wide_data == NULL					\
	   || ((_fp)->_wide_data->_IO_write_ptr				\
	       >= (_fp)->_wide_data->_IO_write_end), 0)			\
   ? __woverflow (_fp, _wch)						\
   : (_IO_wint_t) (*(_fp)->_wide_data->_IO_write_ptr++ = (_wch)))
#endif
# 425 "/usr/include/libio.h" 3 4

#define _IO_feof_unlocked(__fp) (((__fp)->_flags & _IO_EOF_SEEN) != 0)
#define _IO_ferror_unlocked(__fp) (((__fp)->_flags & _IO_ERR_SEEN) != 0)

extern int _IO_getc (_IO_FILE *__fp);
extern int _IO_putc (int __c, _IO_FILE *__fp);
extern int _IO_feof (_IO_FILE *__fp) __THROW;
extern int _IO_ferror (_IO_FILE *__fp) __THROW;

extern int _IO_peekc_locked (_IO_FILE *__fp);

/* This one is for Emacs. */
#define _IO_PENDING_OUTPUT_COUNT(_fp)	\
	((_fp)->_IO_write_ptr - (_fp)->_IO_write_base)

extern void _IO_flockfile (_IO_FILE *) __THROW;
extern void _IO_funlockfile (_IO_FILE *) __THROW;
extern int _IO_ftrylockfile (_IO_FILE *) __THROW;

#ifdef _IO_MTSAFE_IO
# define _IO_peekc(_fp) _IO_peekc_locked (_fp)
# define _IO_flockfile(_fp) \
  if (((_fp)->_flags & _IO_USER_LOCK) == 0) _IO_flockfile (_fp)
# define _IO_funlockfile(_fp) \
  if (((_fp)->_flags & _IO_USER_LOCK) == 0) _IO_funlockfile (_fp)
#else
# 451 "/usr/include/libio.h" 3 4
# define _IO_peekc(_fp) _IO_peekc_unlocked (_fp)
# define _IO_flockfile(_fp) /**/
# define _IO_funlockfile(_fp) /**/
# define _IO_ftrylockfile(_fp) /**/
# define _IO_cleanup_region_start(_fct, _fp) /**/
# define _IO_cleanup_region_end(_Doit) /**/
#endif /* !_IO_MTSAFE_IO */
# 458 "/usr/include/libio.h" 3 4

extern int _IO_vfscanf (_IO_FILE * __restrict, const char * __restrict,
			_IO_va_list, int *__restrict);
extern int _IO_vfprintf (_IO_FILE *__restrict, const char *__restrict,
			 _IO_va_list);
extern _IO_ssize_t _IO_padn (_IO_FILE *, int, _IO_ssize_t);
extern _IO_size_t _IO_sgetn (_IO_FILE *, void *, _IO_size_t);

extern _IO_off64_t _IO_seekoff (_IO_FILE *, _IO_off64_t, int, int);
extern _IO_off64_t _IO_seekpos (_IO_FILE *, _IO_off64_t, int);

extern void _IO_free_backup_area (_IO_FILE *) __THROW;

#if defined _LIBC || defined _GLIBCPP_USE_WCHAR_T
extern _IO_wint_t _IO_getwc (_IO_FILE *__fp);
extern _IO_wint_t _IO_putwc (wchar_t __wc, _IO_FILE *__fp);
extern int _IO_fwide (_IO_FILE *__fp, int __mode) __THROW;
# if __GNUC__ >= 2
/* While compiling glibc we have to handle compatibility with very old
   versions.  */
#  if defined _LIBC && defined SHARED
#if 0 /* expanded by -frewrite-includes */
#   include <shlib-compat.h>
#endif /* expanded by -frewrite-includes */
# 479 "/usr/include/libio.h" 3 4
# 480 "/usr/include/libio.h" 3 4
#   if SHLIB_COMPAT (libc, GLIBC_2_0, GLIBC_2_1)
#    define _IO_fwide_maybe_incompatible \
  (__builtin_expect (&_IO_stdin_used == NULL, 0))
extern const int _IO_stdin_used;
weak_extern (_IO_stdin_used);
#   endif
# 486 "/usr/include/libio.h" 3 4
#  endif
# 487 "/usr/include/libio.h" 3 4
#  ifndef _IO_fwide_maybe_incompatible
#   define _IO_fwide_maybe_incompatible (0)
#  endif
# 490 "/usr/include/libio.h" 3 4
/* A special optimized version of the function above.  It optimizes the
   case of initializing an unoriented byte stream.  */
#  define _IO_fwide(__fp, __mode) \
  ({ int __result = (__mode);						      \
     if (__result < 0 && ! _IO_fwide_maybe_incompatible)		      \
       {								      \
	 if ((__fp)->_mode == 0)					      \
	   /* We know that all we have to do is to set the flag.  */	      \
	   (__fp)->_mode = -1;						      \
	 __result = (__fp)->_mode;					      \
       }								      \
     else if (__builtin_constant_p (__mode) && (__mode) == 0)		      \
       __result = _IO_fwide_maybe_incompatible ? -1 : (__fp)->_mode;	      \
     else								      \
       __result = _IO_fwide (__fp, __result);				      \
     __result; })
# endif
# 507 "/usr/include/libio.h" 3 4

extern int _IO_vfwscanf (_IO_FILE * __restrict, const wchar_t * __restrict,
			 _IO_va_list, int *__restrict);
extern int _IO_vfwprintf (_IO_FILE *__restrict, const wchar_t *__restrict,
			  _IO_va_list);
extern _IO_ssize_t _IO_wpadn (_IO_FILE *, wint_t, _IO_ssize_t);
extern void _IO_free_wbackup_area (_IO_FILE *) __THROW;
#endif
# 515 "/usr/include/libio.h" 3 4

#ifdef __LDBL_COMPAT
#if 0 /* expanded by -frewrite-includes */
# include <bits/libio-ldbl.h>
#endif /* expanded by -frewrite-includes */
# 517 "/usr/include/libio.h" 3 4
# 518 "/usr/include/libio.h" 3 4
#endif
# 519 "/usr/include/libio.h" 3 4

#ifdef __cplusplus
}
#endif
# 523 "/usr/include/libio.h" 3 4

#endif /* _IO_STDIO_H */
# 525 "/usr/include/libio.h" 3 4
# 75 "/usr/include/stdio.h" 2 3 4

#if defined __USE_XOPEN || defined __USE_XOPEN2K8
# ifdef __GNUC__
#  ifndef _VA_LIST_DEFINED
typedef _G_va_list va_list;
#   define _VA_LIST_DEFINED
#  endif
# 82 "/usr/include/stdio.h" 3 4
# else
# 83 "/usr/include/stdio.h" 3 4
#if 0 /* expanded by -frewrite-includes */
#  include <stdarg.h>
#endif /* expanded by -frewrite-includes */
# 83 "/usr/include/stdio.h" 3 4
# 84 "/usr/include/stdio.h" 3 4
# endif
# 85 "/usr/include/stdio.h" 3 4
#endif
# 86 "/usr/include/stdio.h" 3 4

#ifdef __USE_XOPEN2K8
# ifndef __off_t_defined
# ifndef __USE_FILE_OFFSET64
typedef __off_t off_t;
# else
# 92 "/usr/include/stdio.h" 3 4
typedef __off64_t off_t;
# endif
# 94 "/usr/include/stdio.h" 3 4
# define __off_t_defined
# endif
# 96 "/usr/include/stdio.h" 3 4
# if defined __USE_LARGEFILE64 && !defined __off64_t_defined
typedef __off64_t off64_t;
# define __off64_t_defined
# endif
# 100 "/usr/include/stdio.h" 3 4

# ifndef __ssize_t_defined
typedef __ssize_t ssize_t;
# define __ssize_t_defined
# endif
# 105 "/usr/include/stdio.h" 3 4
#endif
# 106 "/usr/include/stdio.h" 3 4

/* The type of the second argument to `fgetpos' and `fsetpos'.  */
__BEGIN_NAMESPACE_STD
#ifndef __USE_FILE_OFFSET64
typedef _G_fpos_t fpos_t;
#else
# 112 "/usr/include/stdio.h" 3 4
typedef _G_fpos64_t fpos_t;
#endif
# 114 "/usr/include/stdio.h" 3 4
__END_NAMESPACE_STD
#ifdef __USE_LARGEFILE64
typedef _G_fpos64_t fpos64_t;
#endif
# 118 "/usr/include/stdio.h" 3 4

/* The possibilities for the third argument to `setvbuf'.  */
#define _IOFBF 0		/* Fully buffered.  */
#define _IOLBF 1		/* Line buffered.  */
#define _IONBF 2		/* No buffering.  */


/* Default buffer size.  */
#ifndef BUFSIZ
# define BUFSIZ _IO_BUFSIZ
#endif
# 129 "/usr/include/stdio.h" 3 4


/* End of file character.
   Some things throughout the library rely on this being -1.  */
#ifndef EOF
# define EOF (-1)
#endif
# 136 "/usr/include/stdio.h" 3 4


/* The possibilities for the third argument to `fseek'.
   These values should not be changed.  */
#define SEEK_SET	0	/* Seek from beginning of file.  */
#define SEEK_CUR	1	/* Seek from current position.  */
#define SEEK_END	2	/* Seek from end of file.  */
#ifdef __USE_GNU
# define SEEK_DATA	3	/* Seek to next data.  */
# define SEEK_HOLE	4	/* Seek to next hole.  */
#endif
# 147 "/usr/include/stdio.h" 3 4


#if defined __USE_MISC || defined __USE_XOPEN
/* Default path prefix for `tempnam' and `tmpnam'.  */
# define P_tmpdir	"/tmp"
#endif
# 153 "/usr/include/stdio.h" 3 4


/* Get the values:
   L_tmpnam	How long an array of chars must be to be passed to `tmpnam'.
   TMP_MAX	The minimum number of unique filenames generated by tmpnam
		(and tempnam when it uses tmpnam's name space),
		or tempnam (the two are separate).
   L_ctermid	How long an array to pass to `ctermid'.
   L_cuserid	How long an array to pass to `cuserid'.
   FOPEN_MAX	Minimum number of files that can be open at once.
   FILENAME_MAX	Maximum length of a filename.  */
#if 0 /* expanded by -frewrite-includes */
#include <bits/stdio_lim.h>
#endif /* expanded by -frewrite-includes */
# 164 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/stdio_lim.h" 1 3 4
/* Copyright (C) 1994-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#if !defined _STDIO_H && !defined __need_FOPEN_MAX && !defined __need_IOV_MAX
# error "Never include <bits/stdio_lim.h> directly; use <stdio.h> instead."
#endif
# 21 "/usr/include/x86_64-linux-gnu/bits/stdio_lim.h" 3 4

#ifdef _STDIO_H
# define L_tmpnam 20
# define TMP_MAX 238328
# define FILENAME_MAX 4096

# ifdef __USE_POSIX
#  define L_ctermid 9
#  if !defined __USE_XOPEN2K || defined __USE_GNU
#   define L_cuserid 9
#  endif
# 32 "/usr/include/x86_64-linux-gnu/bits/stdio_lim.h" 3 4
# endif
# 33 "/usr/include/x86_64-linux-gnu/bits/stdio_lim.h" 3 4
#endif
# 34 "/usr/include/x86_64-linux-gnu/bits/stdio_lim.h" 3 4

#if defined __need_FOPEN_MAX || defined _STDIO_H
# undef  FOPEN_MAX
# define FOPEN_MAX 16
#endif
# 39 "/usr/include/x86_64-linux-gnu/bits/stdio_lim.h" 3 4

#if defined __need_IOV_MAX && !defined IOV_MAX
# define IOV_MAX 1024
#endif
# 43 "/usr/include/x86_64-linux-gnu/bits/stdio_lim.h" 3 4
# 165 "/usr/include/stdio.h" 2 3 4


/* Standard streams.  */
extern struct _IO_FILE *stdin;		/* Standard input stream.  */
extern struct _IO_FILE *stdout;		/* Standard output stream.  */
extern struct _IO_FILE *stderr;		/* Standard error output stream.  */
/* C89/C99 say they're macros.  Make them happy.  */
#define stdin stdin
#define stdout stdout
#define stderr stderr

__BEGIN_NAMESPACE_STD
/* Remove file FILENAME.  */
extern int remove (const char *__filename) __THROW;
/* Rename file OLD to NEW.  */
extern int rename (const char *__old, const char *__new) __THROW;
__END_NAMESPACE_STD

#ifdef __USE_ATFILE
/* Rename file OLD relative to OLDFD to NEW relative to NEWFD.  */
extern int renameat (int __oldfd, const char *__old, int __newfd,
		     const char *__new) __THROW;
#endif
# 188 "/usr/include/stdio.h" 3 4

__BEGIN_NAMESPACE_STD
/* Create a temporary file and open it read/write.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
#ifndef __USE_FILE_OFFSET64
extern FILE *tmpfile (void) __wur;
#else
# 197 "/usr/include/stdio.h" 3 4
# ifdef __REDIRECT
extern FILE *__REDIRECT (tmpfile, (void), tmpfile64) __wur;
# else
# 200 "/usr/include/stdio.h" 3 4
#  define tmpfile tmpfile64
# endif
# 202 "/usr/include/stdio.h" 3 4
#endif
# 203 "/usr/include/stdio.h" 3 4

#ifdef __USE_LARGEFILE64
extern FILE *tmpfile64 (void) __wur;
#endif
# 207 "/usr/include/stdio.h" 3 4

/* Generate a temporary filename.  */
extern char *tmpnam (char *__s) __THROW __wur;
__END_NAMESPACE_STD

#ifdef __USE_MISC
/* This is the reentrant variant of `tmpnam'.  The only difference is
   that it does not allow S to be NULL.  */
extern char *tmpnam_r (char *__s) __THROW __wur;
#endif
# 217 "/usr/include/stdio.h" 3 4


#if defined __USE_MISC || defined __USE_XOPEN
/* Generate a unique temporary filename using up to five characters of PFX
   if it is not NULL.  The directory to put this file in is searched for
   as follows: First the environment variable "TMPDIR" is checked.
   If it contains the name of a writable directory, that directory is used.
   If not and if DIR is not NULL, that value is checked.  If that fails,
   P_tmpdir is tried and finally "/tmp".  The storage for the filename
   is allocated by `malloc'.  */
extern char *tempnam (const char *__dir, const char *__pfx)
     __THROW __attribute_malloc__ __wur;
#endif
# 230 "/usr/include/stdio.h" 3 4


__BEGIN_NAMESPACE_STD
/* Close STREAM.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int fclose (FILE *__stream);
/* Flush STREAM, or all streams if STREAM is NULL.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int fflush (FILE *__stream);
__END_NAMESPACE_STD

#ifdef __USE_MISC
/* Faster versions when locking is not required.

   This function is not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation it is a cancellation point and
   therefore not marked with __THROW.  */
extern int fflush_unlocked (FILE *__stream);
#endif
# 254 "/usr/include/stdio.h" 3 4

#ifdef __USE_GNU
/* Close all streams.

   This function is not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation it is a cancellation point and
   therefore not marked with __THROW.  */
extern int fcloseall (void);
#endif
# 264 "/usr/include/stdio.h" 3 4


__BEGIN_NAMESPACE_STD
#ifndef __USE_FILE_OFFSET64
/* Open a file and create a new stream for it.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern FILE *fopen (const char *__restrict __filename,
		    const char *__restrict __modes) __wur;
/* Open a file, replacing an existing stream with it.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern FILE *freopen (const char *__restrict __filename,
		      const char *__restrict __modes,
		      FILE *__restrict __stream) __wur;
#else
# 282 "/usr/include/stdio.h" 3 4
# ifdef __REDIRECT
extern FILE *__REDIRECT (fopen, (const char *__restrict __filename,
				 const char *__restrict __modes), fopen64)
  __wur;
extern FILE *__REDIRECT (freopen, (const char *__restrict __filename,
				   const char *__restrict __modes,
				   FILE *__restrict __stream), freopen64)
  __wur;
# else
# 291 "/usr/include/stdio.h" 3 4
#  define fopen fopen64
#  define freopen freopen64
# endif
# 294 "/usr/include/stdio.h" 3 4
#endif
# 295 "/usr/include/stdio.h" 3 4
__END_NAMESPACE_STD
#ifdef __USE_LARGEFILE64
extern FILE *fopen64 (const char *__restrict __filename,
		      const char *__restrict __modes) __wur;
extern FILE *freopen64 (const char *__restrict __filename,
			const char *__restrict __modes,
			FILE *__restrict __stream) __wur;
#endif
# 303 "/usr/include/stdio.h" 3 4

#ifdef	__USE_POSIX
/* Create a new stream that refers to an existing system file descriptor.  */
extern FILE *fdopen (int __fd, const char *__modes) __THROW __wur;
#endif
# 308 "/usr/include/stdio.h" 3 4

#ifdef	__USE_GNU
/* Create a new stream that refers to the given magic cookie,
   and uses the given functions for input and output.  */
extern FILE *fopencookie (void *__restrict __magic_cookie,
			  const char *__restrict __modes,
			  _IO_cookie_io_functions_t __io_funcs) __THROW __wur;
#endif
# 316 "/usr/include/stdio.h" 3 4

#ifdef __USE_XOPEN2K8
/* Create a new stream that refers to a memory buffer.  */
extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
  __THROW __wur;

/* Open a stream that writes into a malloc'd buffer that is expanded as
   necessary.  *BUFLOC and *SIZELOC are updated with the buffer's location
   and the number of characters written on fflush or fclose.  */
extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) __THROW __wur;
#endif
# 327 "/usr/include/stdio.h" 3 4


__BEGIN_NAMESPACE_STD
/* If BUF is NULL, make STREAM unbuffered.
   Else make it use buffer BUF, of size BUFSIZ.  */
extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) __THROW;
/* Make STREAM use buffering mode MODE.
   If BUF is not NULL, use N bytes of it for buffering;
   else allocate an internal buffer N bytes long.  */
extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
		    int __modes, size_t __n) __THROW;
__END_NAMESPACE_STD

#ifdef	__USE_MISC
/* If BUF is NULL, make STREAM unbuffered.
   Else make it use SIZE bytes of BUF for buffering.  */
extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
		       size_t __size) __THROW;

/* Make STREAM line-buffered.  */
extern void setlinebuf (FILE *__stream) __THROW;
#endif
# 349 "/usr/include/stdio.h" 3 4


__BEGIN_NAMESPACE_STD
/* Write formatted output to STREAM.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int fprintf (FILE *__restrict __stream,
		    const char *__restrict __format, ...);
/* Write formatted output to stdout.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int printf (const char *__restrict __format, ...);
/* Write formatted output to S.  */
extern int sprintf (char *__restrict __s,
		    const char *__restrict __format, ...) __THROWNL;

/* Write formatted output to S from argument list ARG.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int vfprintf (FILE *__restrict __s, const char *__restrict __format,
		     _G_va_list __arg);
/* Write formatted output to stdout from argument list ARG.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int vprintf (const char *__restrict __format, _G_va_list __arg);
/* Write formatted output to S from argument list ARG.  */
extern int vsprintf (char *__restrict __s, const char *__restrict __format,
		     _G_va_list __arg) __THROWNL;
__END_NAMESPACE_STD

#if defined __USE_ISOC99 || defined __USE_UNIX98
__BEGIN_NAMESPACE_C99
/* Maximum chars of output to write in MAXLEN.  */
extern int snprintf (char *__restrict __s, size_t __maxlen,
		     const char *__restrict __format, ...)
     __THROWNL __attribute__ ((__format__ (__printf__, 3, 4)));

extern int vsnprintf (char *__restrict __s, size_t __maxlen,
		      const char *__restrict __format, _G_va_list __arg)
     __THROWNL __attribute__ ((__format__ (__printf__, 3, 0)));
__END_NAMESPACE_C99
#endif
# 395 "/usr/include/stdio.h" 3 4

#ifdef __USE_GNU
/* Write formatted output to a string dynamically allocated with `malloc'.
   Store the address of the string in *PTR.  */
extern int vasprintf (char **__restrict __ptr, const char *__restrict __f,
		      _G_va_list __arg)
     __THROWNL __attribute__ ((__format__ (__printf__, 2, 0))) __wur;
extern int __asprintf (char **__restrict __ptr,
		       const char *__restrict __fmt, ...)
     __THROWNL __attribute__ ((__format__ (__printf__, 2, 3))) __wur;
extern int asprintf (char **__restrict __ptr,
		     const char *__restrict __fmt, ...)
     __THROWNL __attribute__ ((__format__ (__printf__, 2, 3))) __wur;
#endif
# 409 "/usr/include/stdio.h" 3 4

#ifdef __USE_XOPEN2K8
/* Write formatted output to a file descriptor.  */
extern int vdprintf (int __fd, const char *__restrict __fmt,
		     _G_va_list __arg)
     __attribute__ ((__format__ (__printf__, 2, 0)));
extern int dprintf (int __fd, const char *__restrict __fmt, ...)
     __attribute__ ((__format__ (__printf__, 2, 3)));
#endif
# 418 "/usr/include/stdio.h" 3 4


__BEGIN_NAMESPACE_STD
/* Read formatted input from STREAM.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int fscanf (FILE *__restrict __stream,
		   const char *__restrict __format, ...) __wur;
/* Read formatted input from stdin.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int scanf (const char *__restrict __format, ...) __wur;
/* Read formatted input from S.  */
extern int sscanf (const char *__restrict __s,
		   const char *__restrict __format, ...) __THROW;

#if defined __USE_ISOC99 && !defined __USE_GNU \
    && (!defined __LDBL_COMPAT || !defined __REDIRECT) \
    && (defined __STRICT_ANSI__ || defined __USE_XOPEN2K)
# ifdef __REDIRECT
/* For strict ISO C99 or POSIX compliance disallow %as, %aS and %a[
   GNU extension which conflicts with valid %a followed by letter
   s, S or [.  */
extern int __REDIRECT (fscanf, (FILE *__restrict __stream,
				const char *__restrict __format, ...),
		       __isoc99_fscanf) __wur;
extern int __REDIRECT (scanf, (const char *__restrict __format, ...),
		       __isoc99_scanf) __wur;
extern int __REDIRECT_NTH (sscanf, (const char *__restrict __s,
				    const char *__restrict __format, ...),
			   __isoc99_sscanf);
# else
# 452 "/usr/include/stdio.h" 3 4
extern int __isoc99_fscanf (FILE *__restrict __stream,
			    const char *__restrict __format, ...) __wur;
extern int __isoc99_scanf (const char *__restrict __format, ...) __wur;
extern int __isoc99_sscanf (const char *__restrict __s,
			    const char *__restrict __format, ...) __THROW;
#  define fscanf __isoc99_fscanf
#  define scanf __isoc99_scanf
#  define sscanf __isoc99_sscanf
# endif
# 461 "/usr/include/stdio.h" 3 4
#endif
# 462 "/usr/include/stdio.h" 3 4

__END_NAMESPACE_STD

#ifdef	__USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Read formatted input from S into argument list ARG.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int vfscanf (FILE *__restrict __s, const char *__restrict __format,
		    _G_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 2, 0))) __wur;

/* Read formatted input from stdin into argument list ARG.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int vscanf (const char *__restrict __format, _G_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 1, 0))) __wur;

/* Read formatted input from S into argument list ARG.  */
extern int vsscanf (const char *__restrict __s,
		    const char *__restrict __format, _G_va_list __arg)
     __THROW __attribute__ ((__format__ (__scanf__, 2, 0)));

# if !defined __USE_GNU \
     && (!defined __LDBL_COMPAT || !defined __REDIRECT) \
     && (defined __STRICT_ANSI__ || defined __USE_XOPEN2K)
#  ifdef __REDIRECT
/* For strict ISO C99 or POSIX compliance disallow %as, %aS and %a[
   GNU extension which conflicts with valid %a followed by letter
   s, S or [.  */
extern int __REDIRECT (vfscanf,
		       (FILE *__restrict __s,
			const char *__restrict __format, _G_va_list __arg),
		       __isoc99_vfscanf)
     __attribute__ ((__format__ (__scanf__, 2, 0))) __wur;
extern int __REDIRECT (vscanf, (const char *__restrict __format,
				_G_va_list __arg), __isoc99_vscanf)
     __attribute__ ((__format__ (__scanf__, 1, 0))) __wur;
extern int __REDIRECT_NTH (vsscanf,
			   (const char *__restrict __s,
			    const char *__restrict __format,
			    _G_va_list __arg), __isoc99_vsscanf)
     __attribute__ ((__format__ (__scanf__, 2, 0)));
#  else
# 508 "/usr/include/stdio.h" 3 4
extern int __isoc99_vfscanf (FILE *__restrict __s,
			     const char *__restrict __format,
			     _G_va_list __arg) __wur;
extern int __isoc99_vscanf (const char *__restrict __format,
			    _G_va_list __arg) __wur;
extern int __isoc99_vsscanf (const char *__restrict __s,
			     const char *__restrict __format,
			     _G_va_list __arg) __THROW;
#   define vfscanf __isoc99_vfscanf
#   define vscanf __isoc99_vscanf
#   define vsscanf __isoc99_vsscanf
#  endif
# 520 "/usr/include/stdio.h" 3 4
# endif
# 521 "/usr/include/stdio.h" 3 4

__END_NAMESPACE_C99
#endif /* Use ISO C9x.  */
# 524 "/usr/include/stdio.h" 3 4


__BEGIN_NAMESPACE_STD
/* Read a character from STREAM.

   These functions are possible cancellation points and therefore not
   marked with __THROW.  */
extern int fgetc (FILE *__stream);
extern int getc (FILE *__stream);

/* Read a character from stdin.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int getchar (void);
__END_NAMESPACE_STD

/* The C standard explicitly says this is a macro, so we always do the
   optimization for it.  */
#define getc(_fp) _IO_getc (_fp)

#ifdef __USE_POSIX
/* These are defined in POSIX.1:1996.

   These functions are possible cancellation points and therefore not
   marked with __THROW.  */
extern int getc_unlocked (FILE *__stream);
extern int getchar_unlocked (void);
#endif /* Use POSIX.  */
# 553 "/usr/include/stdio.h" 3 4

#ifdef __USE_MISC
/* Faster version when locking is not necessary.

   This function is not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation it is a cancellation point and
   therefore not marked with __THROW.  */
extern int fgetc_unlocked (FILE *__stream);
#endif /* Use MISC.  */
# 563 "/usr/include/stdio.h" 3 4


__BEGIN_NAMESPACE_STD
/* Write a character to STREAM.

   These functions are possible cancellation points and therefore not
   marked with __THROW.

   These functions is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int fputc (int __c, FILE *__stream);
extern int putc (int __c, FILE *__stream);

/* Write a character to stdout.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int putchar (int __c);
__END_NAMESPACE_STD

/* The C standard explicitly says this can be a macro,
   so we always do the optimization for it.  */
#define putc(_ch, _fp) _IO_putc (_ch, _fp)

#ifdef __USE_MISC
/* Faster version when locking is not necessary.

   This function is not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation it is a cancellation point and
   therefore not marked with __THROW.  */
extern int fputc_unlocked (int __c, FILE *__stream);
#endif /* Use MISC.  */
# 596 "/usr/include/stdio.h" 3 4

#ifdef __USE_POSIX
/* These are defined in POSIX.1:1996.

   These functions are possible cancellation points and therefore not
   marked with __THROW.  */
extern int putc_unlocked (int __c, FILE *__stream);
extern int putchar_unlocked (int __c);
#endif /* Use POSIX.  */
# 605 "/usr/include/stdio.h" 3 4


#if defined __USE_MISC \
    || (defined __USE_XOPEN && !defined __USE_XOPEN2K)
/* Get a word (int) from STREAM.  */
extern int getw (FILE *__stream);

/* Write a word (int) to STREAM.  */
extern int putw (int __w, FILE *__stream);
#endif
# 615 "/usr/include/stdio.h" 3 4


__BEGIN_NAMESPACE_STD
/* Get a newline-terminated string of finite length from STREAM.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
     __wur;

#if !defined __USE_ISOC11 \
    || (defined __cplusplus && __cplusplus <= 201103L)
/* Get a newline-terminated string from stdin, removing the newline.
   DO NOT USE THIS FUNCTION!!  There is no limit on how much it will read.

   The function has been officially removed in ISO C11.  This opportunity
   is used to also remove it from the GNU feature list.  It is now only
   available when explicitly using an old ISO C, Unix, or POSIX standard.
   GCC defines _GNU_SOURCE when building C++ code and the function is still
   in C++11, so it is also available for C++.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern char *gets (char *__s) __wur __attribute_deprecated__;
#endif
# 640 "/usr/include/stdio.h" 3 4
__END_NAMESPACE_STD

#ifdef __USE_GNU
/* This function does the same as `fgets' but does not lock the stream.

   This function is not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation it is a cancellation point and
   therefore not marked with __THROW.  */
extern char *fgets_unlocked (char *__restrict __s, int __n,
			     FILE *__restrict __stream) __wur;
#endif
# 652 "/usr/include/stdio.h" 3 4


#ifdef	__USE_XOPEN2K8
/* Read up to (and including) a DELIMITER from STREAM into *LINEPTR
   (and null-terminate it). *LINEPTR is a pointer returned from malloc (or
   NULL), pointing to *N characters of space.  It is realloc'd as
   necessary.  Returns the number of characters read (not including the
   null terminator), or -1 on error or EOF.

   These functions are not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation they are cancellation points and
   therefore not marked with __THROW.  */
extern _IO_ssize_t __getdelim (char **__restrict __lineptr,
			       size_t *__restrict __n, int __delimiter,
			       FILE *__restrict __stream) __wur;
extern _IO_ssize_t getdelim (char **__restrict __lineptr,
			     size_t *__restrict __n, int __delimiter,
			     FILE *__restrict __stream) __wur;

/* Like `getdelim', but reads up to a newline.

   This function is not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation it is a cancellation point and
   therefore not marked with __THROW.  */
extern _IO_ssize_t getline (char **__restrict __lineptr,
			    size_t *__restrict __n,
			    FILE *__restrict __stream) __wur;
#endif
# 682 "/usr/include/stdio.h" 3 4


__BEGIN_NAMESPACE_STD
/* Write a string to STREAM.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int fputs (const char *__restrict __s, FILE *__restrict __stream);

/* Write a string, followed by a newline, to stdout.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int puts (const char *__s);


/* Push a character back onto the input buffer of STREAM.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int ungetc (int __c, FILE *__stream);


/* Read chunks of generic data from STREAM.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern size_t fread (void *__restrict __ptr, size_t __size,
		     size_t __n, FILE *__restrict __stream) __wur;
/* Write chunks of generic data to STREAM.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern size_t fwrite (const void *__restrict __ptr, size_t __size,
		      size_t __n, FILE *__restrict __s);
__END_NAMESPACE_STD

#ifdef __USE_GNU
/* This function does the same as `fputs' but does not lock the stream.

   This function is not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation it is a cancellation point and
   therefore not marked with __THROW.  */
extern int fputs_unlocked (const char *__restrict __s,
			   FILE *__restrict __stream);
#endif
# 729 "/usr/include/stdio.h" 3 4

#ifdef __USE_MISC
/* Faster versions when locking is not necessary.

   These functions are not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation they are cancellation points and
   therefore not marked with __THROW.  */
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
			      size_t __n, FILE *__restrict __stream) __wur;
extern size_t fwrite_unlocked (const void *__restrict __ptr, size_t __size,
			       size_t __n, FILE *__restrict __stream);
#endif
# 742 "/usr/include/stdio.h" 3 4


__BEGIN_NAMESPACE_STD
/* Seek to a certain position on STREAM.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int fseek (FILE *__stream, long int __off, int __whence);
/* Return the current position of STREAM.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern long int ftell (FILE *__stream) __wur;
/* Rewind to the beginning of STREAM.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern void rewind (FILE *__stream);
__END_NAMESPACE_STD

/* The Single Unix Specification, Version 2, specifies an alternative,
   more adequate interface for the two functions above which deal with
   file offset.  `long int' is not the right type.  These definitions
   are originally defined in the Large File Support API.  */

#if defined __USE_LARGEFILE || defined __USE_XOPEN2K
# ifndef __USE_FILE_OFFSET64
/* Seek to a certain position on STREAM.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int fseeko (FILE *__stream, __off_t __off, int __whence);
/* Return the current position of STREAM.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern __off_t ftello (FILE *__stream) __wur;
# else
# 780 "/usr/include/stdio.h" 3 4
#  ifdef __REDIRECT
extern int __REDIRECT (fseeko,
		       (FILE *__stream, __off64_t __off, int __whence),
		       fseeko64);
extern __off64_t __REDIRECT (ftello, (FILE *__stream), ftello64);
#  else
# 786 "/usr/include/stdio.h" 3 4
#   define fseeko fseeko64
#   define ftello ftello64
#  endif
# 789 "/usr/include/stdio.h" 3 4
# endif
# 790 "/usr/include/stdio.h" 3 4
#endif
# 791 "/usr/include/stdio.h" 3 4

__BEGIN_NAMESPACE_STD
#ifndef __USE_FILE_OFFSET64
/* Get STREAM's position.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos);
/* Set STREAM's position.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int fsetpos (FILE *__stream, const fpos_t *__pos);
#else
# 805 "/usr/include/stdio.h" 3 4
# ifdef __REDIRECT
extern int __REDIRECT (fgetpos, (FILE *__restrict __stream,
				 fpos_t *__restrict __pos), fgetpos64);
extern int __REDIRECT (fsetpos,
		       (FILE *__stream, const fpos_t *__pos), fsetpos64);
# else
# 811 "/usr/include/stdio.h" 3 4
#  define fgetpos fgetpos64
#  define fsetpos fsetpos64
# endif
# 814 "/usr/include/stdio.h" 3 4
#endif
# 815 "/usr/include/stdio.h" 3 4
__END_NAMESPACE_STD

#ifdef __USE_LARGEFILE64
extern int fseeko64 (FILE *__stream, __off64_t __off, int __whence);
extern __off64_t ftello64 (FILE *__stream) __wur;
extern int fgetpos64 (FILE *__restrict __stream, fpos64_t *__restrict __pos);
extern int fsetpos64 (FILE *__stream, const fpos64_t *__pos);
#endif
# 823 "/usr/include/stdio.h" 3 4

__BEGIN_NAMESPACE_STD
/* Clear the error and EOF indicators for STREAM.  */
extern void clearerr (FILE *__stream) __THROW;
/* Return the EOF indicator for STREAM.  */
extern int feof (FILE *__stream) __THROW __wur;
/* Return the error indicator for STREAM.  */
extern int ferror (FILE *__stream) __THROW __wur;
__END_NAMESPACE_STD

#ifdef __USE_MISC
/* Faster versions when locking is not required.  */
extern void clearerr_unlocked (FILE *__stream) __THROW;
extern int feof_unlocked (FILE *__stream) __THROW __wur;
extern int ferror_unlocked (FILE *__stream) __THROW __wur;
#endif
# 839 "/usr/include/stdio.h" 3 4


__BEGIN_NAMESPACE_STD
/* Print a message describing the meaning of the value of errno.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern void perror (const char *__s);
__END_NAMESPACE_STD

/* Provide the declarations for `sys_errlist' and `sys_nerr' if they
   are available on this system.  Even if available, these variables
   should not be used directly.  The `strerror' function provides
   all the necessary functionality.  */
#if 0 /* expanded by -frewrite-includes */
#include <bits/sys_errlist.h>
#endif /* expanded by -frewrite-includes */
# 853 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/sys_errlist.h" 1 3 4
/* Declare sys_errlist and sys_nerr, or don't.  Compatibility (do) version.
   Copyright (C) 2002-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _STDIO_H
# error "Never include <bits/sys_errlist.h> directly; use <stdio.h> instead."
#endif
# 22 "/usr/include/x86_64-linux-gnu/bits/sys_errlist.h" 3 4

/* sys_errlist and sys_nerr are deprecated.  Use strerror instead.  */

#ifdef  __USE_MISC
extern int sys_nerr;
extern const char *const sys_errlist[];
#endif
# 29 "/usr/include/x86_64-linux-gnu/bits/sys_errlist.h" 3 4
#ifdef  __USE_GNU
extern int _sys_nerr;
extern const char *const _sys_errlist[];
#endif
# 33 "/usr/include/x86_64-linux-gnu/bits/sys_errlist.h" 3 4
# 854 "/usr/include/stdio.h" 2 3 4


#ifdef	__USE_POSIX
/* Return the system file descriptor for STREAM.  */
extern int fileno (FILE *__stream) __THROW __wur;
#endif /* Use POSIX.  */
# 860 "/usr/include/stdio.h" 3 4

#ifdef __USE_MISC
/* Faster version when locking is not required.  */
extern int fileno_unlocked (FILE *__stream) __THROW __wur;
#endif
# 865 "/usr/include/stdio.h" 3 4


#ifdef __USE_POSIX2
/* Create a new stream connected to a pipe running the given command.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern FILE *popen (const char *__command, const char *__modes) __wur;

/* Close a stream opened by popen and return the status of its child.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int pclose (FILE *__stream);
#endif
# 880 "/usr/include/stdio.h" 3 4


#ifdef	__USE_POSIX
/* Return the name of the controlling terminal.  */
extern char *ctermid (char *__s) __THROW;
#endif /* Use POSIX.  */
# 886 "/usr/include/stdio.h" 3 4


#ifdef __USE_XOPEN
/* Return the name of the current user.  */
extern char *cuserid (char *__s);
#endif /* Use X/Open, but not issue 6.  */
# 892 "/usr/include/stdio.h" 3 4


#ifdef	__USE_GNU
struct obstack;			/* See <obstack.h>.  */

/* Write formatted output to an obstack.  */
extern int obstack_printf (struct obstack *__restrict __obstack,
			   const char *__restrict __format, ...)
     __THROWNL __attribute__ ((__format__ (__printf__, 2, 3)));
extern int obstack_vprintf (struct obstack *__restrict __obstack,
			    const char *__restrict __format,
			    _G_va_list __args)
     __THROWNL __attribute__ ((__format__ (__printf__, 2, 0)));
#endif /* Use GNU.  */
# 906 "/usr/include/stdio.h" 3 4


#ifdef __USE_POSIX
/* These are defined in POSIX.1:1996.  */

/* Acquire ownership of STREAM.  */
extern void flockfile (FILE *__stream) __THROW;

/* Try to acquire ownership of STREAM but do not block if it is not
   possible.  */
extern int ftrylockfile (FILE *__stream) __THROW __wur;

/* Relinquish the ownership granted for STREAM.  */
extern void funlockfile (FILE *__stream) __THROW;
#endif /* POSIX */
# 921 "/usr/include/stdio.h" 3 4

#if defined __USE_XOPEN && !defined __USE_XOPEN2K && !defined __USE_GNU
/* The X/Open standard requires some functions and variables to be
   declared here which do not belong into this header.  But we have to
   follow.  In GNU mode we don't do this nonsense.  */
# define __need_getopt
#if 0 /* expanded by -frewrite-includes */
# include <getopt.h>
#endif /* expanded by -frewrite-includes */
# 927 "/usr/include/stdio.h" 3 4
# 928 "/usr/include/stdio.h" 3 4
#endif	/* X/Open, but not issue 6 and not for GNU.  */
# 929 "/usr/include/stdio.h" 3 4

/* If we are compiling with optimizing read this file.  It contains
   several optimizing inline functions and macros.  */
#ifdef __USE_EXTERN_INLINES
#if 0 /* expanded by -frewrite-includes */
# include <bits/stdio.h>
#endif /* expanded by -frewrite-includes */
# 933 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/stdio.h" 1 3 4
/* Optimizing macros and inline functions for stdio functions.
   Copyright (C) 1998-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _STDIO_H
# error "Never include <bits/stdio.h> directly; use <stdio.h> instead."
#endif
# 22 "/usr/include/x86_64-linux-gnu/bits/stdio.h" 3 4

#ifndef __extern_inline
# define __STDIO_INLINE inline
#else
# 26 "/usr/include/x86_64-linux-gnu/bits/stdio.h" 3 4
# define __STDIO_INLINE __extern_inline
#endif
# 28 "/usr/include/x86_64-linux-gnu/bits/stdio.h" 3 4


#ifdef __USE_EXTERN_INLINES
/* For -D_FORTIFY_SOURCE{,=2} bits/stdio2.h will define a different
   inline.  */
# if !(__USE_FORTIFY_LEVEL > 0 && defined __fortify_function)
/* Write formatted output to stdout from argument list ARG.  */
__STDIO_INLINE int
vprintf (const char *__restrict __fmt, _G_va_list __arg)
{
  return vfprintf (stdout, __fmt, __arg);
}
# endif
# 41 "/usr/include/x86_64-linux-gnu/bits/stdio.h" 3 4

/* Read a character from stdin.  */
__STDIO_INLINE int
getchar (void)
{
  return _IO_getc (stdin);
}


# ifdef __USE_MISC
/* Faster version when locking is not necessary.  */
__STDIO_INLINE int
fgetc_unlocked (FILE *__fp)
{
  return _IO_getc_unlocked (__fp);
}
# endif /* misc */
# 58 "/usr/include/x86_64-linux-gnu/bits/stdio.h" 3 4


# ifdef __USE_POSIX
/* This is defined in POSIX.1:1996.  */
__STDIO_INLINE int
getc_unlocked (FILE *__fp)
{
  return _IO_getc_unlocked (__fp);
}

/* This is defined in POSIX.1:1996.  */
__STDIO_INLINE int
getchar_unlocked (void)
{
  return _IO_getc_unlocked (stdin);
}
# endif	/* POSIX */
# 75 "/usr/include/x86_64-linux-gnu/bits/stdio.h" 3 4


/* Write a character to stdout.  */
__STDIO_INLINE int
putchar (int __c)
{
  return _IO_putc (__c, stdout);
}


# ifdef __USE_MISC
/* Faster version when locking is not necessary.  */
__STDIO_INLINE int
fputc_unlocked (int __c, FILE *__stream)
{
  return _IO_putc_unlocked (__c, __stream);
}
# endif /* misc */
# 93 "/usr/include/x86_64-linux-gnu/bits/stdio.h" 3 4


# ifdef __USE_POSIX
/* This is defined in POSIX.1:1996.  */
__STDIO_INLINE int
putc_unlocked (int __c, FILE *__stream)
{
  return _IO_putc_unlocked (__c, __stream);
}

/* This is defined in POSIX.1:1996.  */
__STDIO_INLINE int
putchar_unlocked (int __c)
{
  return _IO_putc_unlocked (__c, stdout);
}
# endif	/* POSIX */
# 110 "/usr/include/x86_64-linux-gnu/bits/stdio.h" 3 4


# ifdef	__USE_GNU
/* Like `getdelim', but reads up to a newline.  */
__STDIO_INLINE _IO_ssize_t
getline (char **__lineptr, size_t *__n, FILE *__stream)
{
  return __getdelim (__lineptr, __n, '\n', __stream);
}
# endif /* GNU */
# 120 "/usr/include/x86_64-linux-gnu/bits/stdio.h" 3 4


# ifdef __USE_MISC
/* Faster versions when locking is not required.  */
__STDIO_INLINE int
__NTH (feof_unlocked (FILE *__stream))
{
  return _IO_feof_unlocked (__stream);
}

/* Faster versions when locking is not required.  */
__STDIO_INLINE int
__NTH (ferror_unlocked (FILE *__stream))
{
  return _IO_ferror_unlocked (__stream);
}
# endif /* misc */
# 137 "/usr/include/x86_64-linux-gnu/bits/stdio.h" 3 4

#endif /* Use extern inlines.  */
# 139 "/usr/include/x86_64-linux-gnu/bits/stdio.h" 3 4


#if defined __USE_MISC && defined __GNUC__ && defined __OPTIMIZE__ \
    && !defined __cplusplus
/* Perform some simple optimizations.  */
# define fread_unlocked(ptr, size, n, stream) \
  (__extension__ ((__builtin_constant_p (size) && __builtin_constant_p (n)    \
		   && (size_t) (size) * (size_t) (n) <= 8		      \
		   && (size_t) (size) != 0)				      \
		  ? ({ char *__ptr = (char *) (ptr);			      \
		       FILE *__stream = (stream);			      \
		       size_t __cnt;					      \
		       for (__cnt = (size_t) (size) * (size_t) (n);	      \
			    __cnt > 0; --__cnt)				      \
			 {						      \
			   int __c = _IO_getc_unlocked (__stream);	      \
			   if (__c == EOF)				      \
			     break;					      \
			   *__ptr++ = __c;				      \
			 }						      \
		       ((size_t) (size) * (size_t) (n) - __cnt)		      \
			/ (size_t) (size); })				      \
		  : (((__builtin_constant_p (size) && (size_t) (size) == 0)   \
		      || (__builtin_constant_p (n) && (size_t) (n) == 0))     \
			/* Evaluate all parameters once.  */		      \
		     ? ((void) (ptr), (void) (stream), (void) (size),	      \
			(void) (n), (size_t) 0)				      \
		     : fread_unlocked (ptr, size, n, stream))))

# define fwrite_unlocked(ptr, size, n, stream) \
  (__extension__ ((__builtin_constant_p (size) && __builtin_constant_p (n)    \
		   && (size_t) (size) * (size_t) (n) <= 8		      \
		   && (size_t) (size) != 0)				      \
		  ? ({ const char *__ptr = (const char *) (ptr);	      \
		       FILE *__stream = (stream);			      \
		       size_t __cnt;					      \
		       for (__cnt = (size_t) (size) * (size_t) (n);	      \
			    __cnt > 0; --__cnt)				      \
			 if (_IO_putc_unlocked (*__ptr++, __stream) == EOF)   \
			   break;					      \
		       ((size_t) (size) * (size_t) (n) - __cnt)		      \
			/ (size_t) (size); })				      \
		  : (((__builtin_constant_p (size) && (size_t) (size) == 0)   \
		      || (__builtin_constant_p (n) && (size_t) (n) == 0))     \
			/* Evaluate all parameters once.  */		      \
		     ? ((void) (ptr), (void) (stream), (void) (size),	      \
			(void) (n), (size_t) 0)				      \
		     : fwrite_unlocked (ptr, size, n, stream))))
#endif
# 188 "/usr/include/x86_64-linux-gnu/bits/stdio.h" 3 4

/* Define helper macro.  */
#undef __STDIO_INLINE
# 934 "/usr/include/stdio.h" 2 3 4
#endif
# 935 "/usr/include/stdio.h" 3 4
#if __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
#if 0 /* expanded by -frewrite-includes */
# include <bits/stdio2.h>
#endif /* expanded by -frewrite-includes */
# 936 "/usr/include/stdio.h" 3 4
# 937 "/usr/include/stdio.h" 3 4
#endif
# 938 "/usr/include/stdio.h" 3 4
#ifdef __LDBL_COMPAT
#if 0 /* expanded by -frewrite-includes */
# include <bits/stdio-ldbl.h>
#endif /* expanded by -frewrite-includes */
# 939 "/usr/include/stdio.h" 3 4
# 940 "/usr/include/stdio.h" 3 4
#endif
# 941 "/usr/include/stdio.h" 3 4

__END_DECLS

#endif /* <stdio.h> included.  */
# 945 "/usr/include/stdio.h" 3 4

#endif /* !_STDIO_H */
# 947 "/usr/include/stdio.h" 3 4
# 34 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/gnugo.h" 2

#if 0 /* expanded by -frewrite-includes */
#include <config.h>
#endif /* expanded by -frewrite-includes */
# 35 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/gnugo.h"
# 1 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/include/config.h" 1
/* config.h.  Generated automatically by configure.  */
/* config.h.in.  Generated automatically from configure.in by autoheader.  */

/* Connection module. Default standard. */
#define ALTERNATE_CONNECTIONS 1

/* Ruleset. Default Japanese */
#define CHINESE_RULES 0

/* Default level (strength). Up to 10 supported */
#define DEFAULT_LEVEL 10

/* Semeai Variations. 250 default */
#define DEFAULT_SEMEAI_VARIATIONS 250

/* Connection module. Default experimental. */
#define EXPERIMENTAL_CONNECTIONS 1

/* GAIN/LOSS codes. Disabled by default. */
#define EXPERIMENTAL_OWL_EXT 0

/* Semeai module. Default standard. */
#define EXPERIMENTAL_SEMEAI 1

/* Define as 1 to use the grid optimisation, or 2 to run it in self-test mode
   */
#define GRID_OPT 1

/* Define if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

#if !defined(SPEC_CPU_WINDOWS)
/* Define if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1
#endif /* !SPEC_CPU_WINDOWS */
# 57 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/include/config.h"

/* Owl Node Limit */
#define OWL_NODE_LIMIT 1000

/* Owl Threats. 0 standard. */
#define OWL_THREATS 0

/* Name of package */
#define PACKAGE "gnugo"

/* The size of a `int', as computed by sizeof. */
#define SIZEOF_INT sizeof(int)

/* The size of a `long', as computed by sizeof. */
#define SIZEOF_LONG sizeof(long)

/* Define if you have the ANSI C header files. */
#define STDC_HEADERS 1

#if !defined(SPEC_CPU_WINDOWS)
/* Define if you can safely include both <sys/time.h> and <time.h>. */
#define TIME_WITH_SYS_TIME 1
#endif /* !SPEC_CPU_WINDOWS */
# 80 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/include/config.h"

/* Version number of package */
#define VERSION "3.3.14"
# 36 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/gnugo.h" 2

#if 0 /* expanded by -frewrite-includes */
#include "sgftree.h"
#endif /* expanded by -frewrite-includes */
# 37 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/gnugo.h"
# 1 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/sgf/sgftree.h" 1
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * This is GNU GO, a Go program. Contact gnugo@gnu.org, or see       *
 * http://www.gnu.org/software/gnugo/ for more information.          *
 *                                                                   *
 * Copyright 1999, 2000, 2001, 2002 and 2003                         *
 * by the Free Software Foundation.                                  *
 *                                                                   *
 * This program is free software; you can redistribute it and/or     *
 * modify it under the terms of the GNU General Public License as    *
 * published by the Free Software Foundation - version 2             *
 *                                                                   *
 * This program is distributed in the hope that it will be useful,   *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of    *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     *
 * GNU General Public License in file COPYING for more details.      *
 *                                                                   *
 * You should have received a copy of the GNU General Public         *
 * License along with this program; if not, write to the Free        *
 * Software Foundation, Inc., 59 Temple Place - Suite 330,           *
 * Boston, MA 02111, USA.                                            *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _SGFTREE_H
#define _SGFTREE_H 1

#if 0 /* expanded by -frewrite-includes */
#include <stdio.h>
#endif /* expanded by -frewrite-includes */
# 26 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/sgf/sgftree.h"
# 27 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/sgf/sgftree.h"

#if 0 /* expanded by -frewrite-includes */
#include "sgf_properties.h"
#endif /* expanded by -frewrite-includes */
# 28 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/sgf/sgftree.h"
# 1 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/sgf/sgf_properties.h" 1
/* # */
/* # This document was taken from the SGF Specfication. See: */
/* # http://www.red-bean.com/sgf/ */
/* # */
/* # [SGF FF[4] - Smart Game Format] */
/* # */
/* # FF[4] property index */
/* # */
/* # This is an alphabetical index to all properties defined in FF[4]. */
/* # New properties are marked with '*', changed properties are marked with '!'. */
/* # */
/* #ID   Description     property type    property value */
/* #---- --------------- ---------------  -------------------------------------- */
     /*  Add Black       setup            list of stone */
#define SGFAB   16961
     /*  Add Empty       setup            list of point */
#define SGFAE   17729
     /*  Annotation      game-info        simpletext */
#define SGFAN   20033
     /*  Application     root             composed simpletext ':' simpletext */
#define SGFAP   20545
     /*  Arrow           -                list of composed point ':' point */
#define SGFAR   21057
     /*  Who adds stones - (LOA)          simpletext */
#define SGFAS   21313
     /*  Add White       setup            list of stone */
#define SGFAW   22337
     /*  Black           move             move */
#define SGFB     8258
     /*  Black time left move             real */
#define SGFBL   19522
     /*  Bad move        move             double */
#define SGFBM   19778
     /*  Black rank      game-info        simpletext */
#define SGFBR   21058
     /*  Black team      game-info        simpletext */
#define SGFBT   21570
     /*  Comment         -                text */
#define SGFC     8259
     /*  Charset         root             simpletext */
#define SGFCA   16707
     /*  Copyright       game-info        simpletext */
#define SGFCP   20547
     /*  Circle          -                list of point */
#define SGFCR   21059
     /*  Dim points      - (inherit)      elist of point */
#define SGFDD   17476
     /*  Even position   -                double */
#define SGFDM   19780
     /*  Doubtful        move             none */
#define SGFDO   20292
     /*  Date            game-info        simpletext */
#define SGFDT   21572
     /*  Event           game-info        simpletext */
#define SGFEV   22085
     /*  Fileformat      root             number (range: 1-4) */
#define SGFFF   17990
     /*  Figure          -                none | composed number ":" simpletext */
#define SGFFG   18246
     /*  Good for Black  -                double */
#define SGFGB   16967
     /*  Game comment    game-info        text */
#define SGFGC   17223
     /*  Game            root             number (range: 1-5,7-16) */
#define SGFGM   19783
     /*  Game name       game-info        simpletext */
#define SGFGN   20039
     /*  Good for White  -                double */
#define SGFGW   22343
     /*  Handicap        game-info (Go)   number */
#define SGFHA   16712
     /*  Hotspot         -                double */
#define SGFHO   20296
     /*  Initial pos.    game-info (LOA)  simpletext */
#define SGFIP   20553
     /*  Interesting     move             none */
#define SGFIT   21577
     /*  Invert Y-axis   game-info (LOA)  simpletext */
#define SGFIY   22857
     /*  Komi            game-info (Go)   real */
#define SGFKM   19787
     /*  Ko              move             none */
#define SGFKO   20299
     /*  Label           -                list of composed point ':' simpletext */
#define SGFLB   16972
     /*  Line            -                list of composed point ':' point */
#define SGFLN   20044
     /*  Mark            -                list of point */
#define SGFMA   16717
     /*  set move number move             number */
#define SGFMN   20045
     /*  Nodename        -                simpletext */
#define SGFN     8270
     /*  OtStones Black  move             number */
#define SGFOB   16975
     /*  Opening         game-info        text */
#define SGFON   20047
     /*  Overtime        game-info        simpletext */
#define SGFOT   21583
     /*  OtStones White  move             number */
#define SGFOW   22351
     /*  Player Black    game-info        simpletext */
#define SGFPB   16976
     /*  Place           game-info        simpletext */
#define SGFPC   17232
     /*  Player to play  setup            color */
#define SGFPL   19536
     /*  Print move mode - (inherit)      number */
#define SGFPM   19792
     /*  Player White    game-info        simpletext */
#define SGFPW   22352
     /*  Result          game-info        simpletext */
#define SGFRE   17746
     /*  Round           game-info        simpletext */
#define SGFRO   20306
     /*  Rules           game-info        simpletext */
#define SGFRU   21842
     /*  Markup          - (LOA)          point */
#define SGFSE   17747
     /*  Selected        -                list of point */
#define SGFSL   19539
     /*  Source          game-info        simpletext */
#define SGFSO   20307
     /*  Square          -                list of point */
#define SGFSQ   20819
     /*  Style           root             number (range: 0-3) */
#define SGFST   21587
     /*  Setup type      game-info (LOA)  simpletext */
#define SGFSU   21843
     /*  Size            root             (number | composed number ':' number) */
#define SGFSZ   23123
     /*  Territory Black - (Go)           elist of point */
#define SGFTB   16980
     /*  Tesuji          move             double */
#define SGFTE   17748
     /*  Timelimit       game-info        real */
#define SGFTM   19796
     /*  Triangle        -                list of point */
#define SGFTR   21076
     /*  Territory White - (Go)           elist of point */
#define SGFTW   22356
     /*  Unclear pos     -                double */
#define SGFUC   17237
     /*  User            game-info        simpletext */
#define SGFUS   21333
     /*  Value           -                real */
#define SGFV     8278
     /*  View            - (inherit)      elist of point */
#define SGFVW   22358
     /*  White           move             move */
#define SGFW     8279
     /*  White time left move             real */
#define SGFWL   19543
     /*  White rank      game-info        simpletext */
#define SGFWR   21079
     /*  White team      game-info        simpletext */
#define SGFWT   21591
/* # */
/* # These are additions to the SGF spec- old commands and some others */
/* # */

/* # */
/* # outdated FF3 properties */
/* # */
#define SGFBS 21314
#define SGFWS 21335
#define SGFID 17481
#define SGFRG 18258
#define SGFSC 17235

/* # */
/* # some random ones used by CGoban */
/* # */
#define SGFSY 22867

/* # */
/* # nonstandard SGF property used by GNU Go to mark illegal moves */
/* # */
#define SGFIL 19529
# 29 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/sgf/sgftree.h" 2


#ifndef _GNUGO_H_
/*
 * NOTE: These MUST coincide with the definitions for the engine that we
 *       are using. In this case they are defined in engine/gnugo.h.
 *
 * The reason that we put them here within the #ifndef clause is because
 * we want to decouple the GNU Go engine from SGF library, but we don't 
 * want to redefine these symbols if we include this file into gnugo.h.
 */

#define EMPTY 0
#define WHITE 1
#define BLACK 2
#endif
# 45 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/sgf/sgftree.h"


void *xalloc(unsigned int);

/*
 * A property of an SGF node.  An SGF node is described by a linked
 * list of these.
 */

typedef struct SGFProperty_t {
  struct SGFProperty_t *next;
  short name;           /* FIXME: should be char with enumed flags */
  char  *value;         /* FIXME: different types */
} SGFProperty;

    
typedef struct SGFNode_t {
  SGFProperty      *props;
  struct SGFNode_t *parent;
  struct SGFNode_t *child;
  struct SGFNode_t *next;
} SGFNode;


/* low level functions */
SGFNode *sgfPrev(SGFNode *node);
SGFNode *sgfRoot(SGFNode *node);
SGFNode *sgfNewNode(void);
void sgfFreeNode(SGFNode *node);

int sgfGetIntProperty(SGFNode *node, const char *name, int *value);
int sgfGetFloatProperty(SGFNode *node, const char *name, float *value);
int sgfGetCharProperty(SGFNode *node, const char *name, char **value);
void sgfAddProperty(SGFNode *node, const char *name, const char *value);
void sgfAddPropertyInt(SGFNode *node, const char *name, long val);
void sgfAddPropertyFloat(SGFNode *node, const char *name, float val);
void sgfOverwriteProperty(SGFNode *node, const char *name, const char *text);
void sgfOverwritePropertyFloat(SGFNode *node, const char *name, float val);
void sgfOverwritePropertyInt(SGFNode *node, const char *name, int val);
void *xrealloc(void *pt, unsigned int size);
SGFProperty *sgfMkProperty(const char *name, const  char *value,
			   SGFNode *node, SGFProperty *last);
void sgfFreeProperty(SGFProperty *prop);

SGFNode *sgfAddStone(SGFNode *node, int color, int movex, int movey);
SGFNode *sgfAddPlay(SGFNode *node, int who, int movex, int movey);
SGFNode *sgfAddPlayLast(SGFNode *node, int who, int movex, int movey);

void sgfWriteResult(SGFNode *node, float score, int overwrite);
void sgf_write_header(SGFNode *root, int overwrite, int seed, float komi,
		      int level, int rules);

SGFNode *sgfLabel(SGFNode *node, const char *label, int i, int j);
SGFNode *sgfLabelInt(SGFNode *node, int num, int i, int j);
SGFNode *sgfCircle(SGFNode *node, int i, int j);
SGFNode *sgfSquare(SGFNode *node, int i, int j);
SGFNode *sgfTriangle(SGFNode *node, int i, int j);
SGFNode *sgfMark(SGFNode *node, int i, int j);
SGFNode *sgfAddComment(SGFNode *node, const char *comment);
SGFNode *sgfBoardText(SGFNode *node, int i, int j, const char *text);
SGFNode *sgfBoardChar(SGFNode *node, int i, int j, char c);
SGFNode *sgfBoardNumber(SGFNode *node, int i, int j, int number);
SGFNode *sgfStartVariant(SGFNode *node);
SGFNode *sgfStartVariantFirst(SGFNode *node);
SGFNode *sgfAddChild(SGFNode *node);

SGFNode *sgfCreateHeaderNode(int boardsize, float komi);

/* Read SGF tree from file. */
SGFNode *readsgffile(const char *filename);
/* Specific solution for fuseki */
SGFNode *readsgffilefuseki(const char *filename, int moves_per_game);

/* Write SGF tree to a file. */
int writesgf(SGFNode *root, const char *filename);


/* ---------------------------------------------------------------- */
/* ---                          SGFTree                         --- */
/* ---------------------------------------------------------------- */


typedef struct SGFTree_t {
  SGFNode *root;
  SGFNode *lastnode;
} SGFTree;


void sgftree_clear(SGFTree *tree);
int sgftree_readfile(SGFTree *tree, const char *infilename);

int sgftreeBack(SGFTree *tree);
int sgftreeForward(SGFTree *tree);

void sgftreeAddPlay(SGFTree *tree, int color, int movex, int movey);
void sgftreeAddPlayLast(SGFTree *tree, int color, int movex, int movey);
void sgftreeAddStone(SGFTree *tree, int color, int movex, int movey);
void sgftreeWriteResult(SGFTree *tree, float score, int overwrite);
SGFNode *sgftreeNodeCheck(SGFTree *tree);
	 
void sgftreeCircle(SGFTree *tree, int i, int j);
void sgftreeSquare(SGFTree *tree, int i, int j);
void sgftreeTriangle(SGFTree *tree, int i, int j);
void sgftreeMark(SGFTree *tree, int i, int j);
void sgftreeAddComment(SGFTree *tree, const char *comment);
void sgftreeBoardText(SGFTree *tree, int i, int j, const char *text);
void sgftreeBoardChar(SGFTree *tree, int i, int j, char c);
void sgftreeBoardNumber(SGFTree *tree, int i, int j, int number);
void sgftreeStartVariant(SGFTree *tree);
void sgftreeStartVariantFirst(SGFTree *tree);
void sgftreeCreateHeaderNode(SGFTree *tree, int boardsize, float komi);
void sgftreeSetLastNode(SGFTree *tree, SGFNode *lastnode);


/* ---------------------------------------------------------------- */
/* ---                         Utilities                        --- */
/* ---------------------------------------------------------------- */


int get_moveX(SGFProperty *property, int boardsize);
int get_moveY(SGFProperty *property, int boardsize);
int get_moveXY(SGFProperty *property, int *i, int *j, int boardsize);

int show_sgf_properties(SGFNode *node);
int show_sgf_tree(SGFNode *node);
int is_markup_node(SGFNode *node);
int is_move_node(SGFNode *node);
int is_pass_node(SGFNode *node, int boardsize);
int find_move(SGFNode *node);


#endif
# 177 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/sgf/sgftree.h"

# 38 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/gnugo.h" 2

/* interface.c */
/* Initialize the whole thing. Should be called once. */
void init_gnugo(void);

#define READING_CACHE_ENTRIES 400000


/* ================================================================ */
/*                some public macros used everywhere                */
/* ================================================================ */


/* Board size */

#define DEFAULT_BOARD_SIZE 19

/* Colors */
#define EMPTY        0
#define WHITE        1
#define BLACK        2
#define GRAY         3
#define GRAY_BORDER  3
#define WHITE_BORDER 4
#define BLACK_BORDER 5
#define ANCHOR_COLOR 6
#define ANCHOR_OTHER 7


#define OTHER_COLOR(color)  	(WHITE+BLACK-(color))
#define IS_STONE(arg)   	((arg) == WHITE || (arg) == BLACK)
#define BORDER_COLOR(color)	(color + WHITE_BORDER - WHITE)

/* Return codes for reading functions */

#define WIN  5
#define KO_A 4
#define GAIN 3
#define LOSS 2
#define KO_B 1
#define LOSE 0

/* Used by break_through(). Must be different from 0 and WIN. */
#define CUT  2

/* Group statuses */
#define DEAD        0
#define ALIVE       1
#define CRITICAL    2 
#define UNKNOWN     3
#define UNCHECKED   4
#define MAX_DRAGON_STATUS 4	/* used to size an array in matchpat.c */

/* Dragon safety values. DEAD, ALIVE, and CRITICAL are reused. */
#define INESSENTIAL     5
#define TACTICALLY_DEAD 6
#define ALIVE_IN_SEKI   7
#define STRONGLY_ALIVE  8
#define INVINCIBLE      9
#define INSUBSTANTIAL   10
#define CAN_THREATEN_ATTACK  11
#define CAN_THREATEN_DEFENSE 12

/* Surrounded */

#define SURROUNDED 1
#define WEAKLY_SURROUNDED 2

/* Final statuses for empty vertices. */
#define BLACK_TERRITORY 13
#define WHITE_TERRITORY 14
#define DAME            15

/* ================================================================ */
/*                        Board manipulation                        */
/* ================================================================ */


/* Board sizes */
#define MIN_BOARD          5	   /* Minimum supported board size.   */
#define MAX_BOARD         19       /* Maximum supported board size.   */
#define MAX_HANDICAP       9	   /* Maximum supported handicap.     */
#define MAX_MOVE_HISTORY 500       /* Max number of moves remembered. */

/* This type is used to store each intersection on the board.
 *
 * On a 486, char is best, since the time taken to push and pop
 * becomes significant otherwise. On other platforms, an int may
 * be better, e.g. if memcpy() is particularly fast, or if
 * character access is very slow.
 */

typedef unsigned char Intersection;


void gnugo_clear_board(int boardsize);
void gnugo_set_komi(float new_komi);
void gnugo_add_stone(int i, int j, int color);
void gnugo_remove_stone(int i, int j);
int  gnugo_is_pass(int i, int j);
void gnugo_play_move(int i, int j, int color);
int  gnugo_undo_move(int n);
int  gnugo_play_sgfnode(SGFNode *node, int to_move);
int  gnugo_play_sgftree(SGFNode *root, int *until, SGFNode **curnode);
int  gnugo_is_legal(int i, int j, int color);
int  gnugo_is_suicide(int i, int j, int color);

int  gnugo_placehand(int handicap);
int  gnugo_sethand(int handicap, SGFNode *root);
void gnugo_recordboard(SGFNode *node);

int  gnugo_genmove(int *i, int *j, int color);

int  gnugo_attack(int m, int n, int *i, int *j);
int  gnugo_find_defense(int m, int n, int *i, int *j);

void  gnugo_who_wins(int color, FILE *outfile);
float gnugo_estimate_score(float *upper, float *lower);
void  gnugo_examine_position(int color, int how_much);

float gnugo_get_komi(void);
void  gnugo_get_board(int b[MAX_BOARD][MAX_BOARD]);
int   gnugo_get_boardsize(void);
int   gnugo_get_move_number(void);

/* ================================================================ */
/*                           Game handling                          */
/* ================================================================ */


typedef struct {
  int       handicap;

  int       to_move;		/* whose move it currently is */
  SGFTree   game_record;	/* Game record in sgf format. */

  int       computer_player;	/* BLACK, WHITE, or EMPTY (used as BOTH) */
} Gameinfo;

void gameinfo_clear(Gameinfo *ginfo, int boardsize, float komi);
void gameinfo_print(Gameinfo *ginfo);
void gameinfo_load_sgfheader(Gameinfo *gameinfo, SGFNode *head);
void gameinfo_play_move(Gameinfo *ginfo, int i, int j, int color);
int  gameinfo_play_sgftree_rot(Gameinfo *gameinfo, SGFTree *tree,
			       const char *untilstr, int orientation);
int  gameinfo_play_sgftree(Gameinfo *gameinfo, SGFTree *tree,
			   const char *untilstr);


/* ================================================================ */
/*                           global variables                       */
/* ================================================================ */

/* Random seed */
extern int random_seed;

/* Miscellaneous debug options. */
extern int quiet;		/* Minimal output. */
extern int verbose;		/* Bore the opponent. */
extern int allpats;		/* generate all patterns, even small ones */
extern int printworms;		/* print full data on each string */
extern int printmoyo;		/* print moyo board each move */
extern int printdragons;	/* print full data on each dragon */
extern int printboard;		/* print board each move */
extern int showstatistics;	/* print statistics */
extern int profile_patterns;	/* print statistics of pattern usage */
extern char outfilename[128];  /* output file (-o option) */
extern int output_flags;       /* amount of output to outfile */

/* output flag bits */
#define OUTPUT_MARKDRAGONS         0x0001  /* mark dead and critical dragons */
#define OUTPUT_MOVEVALUES          0x0002  /* output values of all moves in list */

#define OUTPUT_DEFAULT             0 /* no debug output  by default */

/* debug flag bits */
/* NOTE : can specify -d0x... */
#define DEBUG_INFLUENCE             0x0001
#define DEBUG_EYES                  0x0002
#define DEBUG_OWL                   0x0004
#define DEBUG_ESCAPE                0x0008
#define DEBUG_MATCHER               0x0010
#define DEBUG_DRAGONS               0x0020
#define DEBUG_SEMEAI                0x0040
#define DEBUG_LOADSGF               0x0080
#define DEBUG_HELPER                0x0100
#define DEBUG_READING               0x0200
#define DEBUG_WORMS                 0x0400
#define DEBUG_MOVE_REASONS          0x0800
#define DEBUG_OWL_PERFORMANCE       0x1000
#define DEBUG_LIFE                  0x2000
#define DEBUG_FILLLIB               0x4000
#define DEBUG_READING_PERFORMANCE   0x8000
#define DEBUG_SCORING               0x010000
#define DEBUG_AFTERMATH             0x020000
#define DEBUG_ATARI_ATARI           0x040000
#define DEBUG_READING_CACHE         0x080000
#define DEBUG_TERRITORY             0x100000
#define DEBUG_OWL_PERSISTENT_CACHE  0x200000
#define DEBUG_TOP_MOVES             0x400000
#define DEBUG_MISCELLANEOUS         0x800000

/* hash flag bits 
 *
 * Regarding HASH_DEFAULT:
 * Hashing all functions saves time, but wastes table space, which is
 * bad when the reading is complicated. HASH_DEFAULT is a compromise. 
 */

#define HASH_FIND_DEFENSE 0x0001  /* NOTE : can specify -d0x... */
#define HASH_ATTACK       0x0020
#define HASH_OWL_ATTACK   0x0100
#define HASH_OWL_DEFEND   0x0200
#define HASH_SEMEAI       0x0400
#define HASH_CONNECT      0x0800
#define HASH_DISCONNECT   0x1000
#define HASH_NOTHING      0
#define HASH_ALL          0xffff
#define HASH_DEFAULT      (HASH_ATTACK | HASH_FIND_DEFENSE\
			   | HASH_OWL_ATTACK | HASH_OWL_DEFEND | HASH_SEMEAI\
                           | HASH_CONNECT | HASH_DISCONNECT)

extern int debug;		/* debug flags */
extern int hashflags;		/* hash flags */
extern int fusekidb;            /* use fuseki database */
extern int disable_fuseki;      /* do not generate fuseki moves */
extern int josekidb;            /* use joseki database */
extern int level;		/* controls depth of reading */
extern int semeai_variations;   /* max variations considered reading semeai */
extern int urgent;              /* urgent move on board */
extern int showtime;		/* print genmove time */
extern int showscore;		/* print score */
extern float score;
extern float lower_bound;
extern float upper_bound;
extern int chinese_rules;       /* use chinese (area) rules for counting */
extern int experimental_owl_ext;     /* use experimental owl (GAIN/LOSS) */
extern int experimental_semeai;      /* use experimental semeai module */
extern int experimental_connections; /* use experimental connection module */
extern int alternate_connections;    /* use alternate connection module */
extern int owl_threats;              /* compute owl threats */
extern int experimental_influence;   /* use experimental influence module */
extern int allow_suicide;            /* allow opponent to make suicide moves */
extern int capture_all_dead;         /* capture all dead opponent stones */
extern int play_out_aftermath; /* make everything unconditionally settled */
extern int play_mirror_go;           /* try to play mirror go if possible */
extern int mirror_stones_limit;      /* but stop at this number of stones */
extern int gtp_version;              /* version of Go Text Protocol */

/* Mandatory values of reading parameters. Normally -1, if set at 
 * these override the values derived from the level. */
extern int mandated_depth;
extern int mandated_backfill_depth;
extern int mandated_backfill2_depth;
extern int mandated_superstring_depth;
extern int mandated_fourlib_depth;
extern int mandated_ko_depth;
extern int mandated_branch_depth;
extern int mandated_aa_depth;
extern int mandated_owl_distrust_depth;
extern int mandated_owl_branch_depth;
extern int mandated_owl_reading_depth;
extern int mandated_owl_node_limit; 

/* Keep this as 2D until we change the entire API. */
extern float potential_moves[MAX_BOARD][MAX_BOARD];

/* ================================================================ */
/*                 tracing and debugging functions                  */
/* ================================================================ */

/* Colors. */
#define GG_COLOR_BLACK   0
#define GG_COLOR_RED     1
#define GG_COLOR_GREEN   2
#define GG_COLOR_YELLOW  3
#define GG_COLOR_BLUE    4
#define GG_COLOR_MAGENTA 5
#define GG_COLOR_CYAN    6
#define GG_COLOR_WHITE   7

/* showbord.c */
void start_draw_board(void);
void draw_color_char(int m, int n, int c, int color);
void draw_char(int m, int n, int c);
void end_draw_board(void);
void showboard(int xo);  /* ascii rep. of board to stderr */
void simple_showboard(FILE *outfile);  /* ascii rep. of board to outfile */

/* printutils.c */
int gprintf(const char *fmt, ...);
void mprintf(const char *fmt, ...);
void gfprintf(FILE *outfile, const char *fmt, ...);
const char *color_to_string(int color);
const char *location_to_string(int pos);
void        location_to_buffer(int pos, char *buf);
const char *status_to_string(int status);
const char *safety_to_string(int status);
const char *result_to_string(int result);
const char *routine_to_string(int routine);
int string_to_location(int boardsize, char *str, int *m, int *n);
double gg_gettimeofday(void);


/* influence.c */
void debug_influence_move(int i, int j);


#define TRACE  (!(verbose)) ? (void)0 : (void)gprintf

#define TRACE_INFLUENCE		!(debug & DEBUG_INFLUENCE) ? \
				 (void)0 : (void)gprintf 
#define TRACE_EYES		!(debug & DEBUG_EYES) ? \
				 (void)0 : (void)gprintf 
#define TRACE_OWL		!(debug & DEBUG_OWL) ? \
				 (void)0 : (void)gprintf 
#define TRACE_ESCAPE		!(debug & DEBUG_ESCAPE) ? \
				 (void)0 : (void)gprintf 
#define TRACE_MATCHER		!(debug & DEBUG_MATCHER) ? \
				 (void)0 : (void)gprintf 
#define TRACE_DRAGONS		!(debug & DEBUG_DRAGONS) ? \
				 (void)0 : (void)gprintf 
#define TRACE_SEMEAI		!(debug & DEBUG_SEMEAI) ? \
				 (void)0 : (void)gprintf 
#define TRACE_LOADSGF		!(debug & DEBUG_LOADSGF) ? \
				 (void)0 : (void)gprintf 
#define TRACE_HELPER		!(debug & DEBUG_HELPER) ? \
				 (void)0 : (void)gprintf 
#define TRACE_READING		!(debug & DEBUG_READING) ? \
				 (void)0 : (void)gprintf 
#define TRACE_WORMS		!(debug & DEBUG_WORMS) ? \
				 (void)0 : (void)gprintf 
#define TRACE_MOVE_REASONS	!(debug & DEBUG_MOVE_REASONS) ? \
				 (void)0 : (void)gprintf 
#define TRACE_OWL_PERFORMANCE	!(debug & DEBUG_OWL_PERFORMANCE) ? \
				 (void)0 : (void)gprintf 
#define TRACE_LIFE		!(debug & DEBUG_LIFE) ? \
				 (void)0 : (void)gprintf 
#define TRACE_FILLLIB		!(debug & DEBUG_FILLLIB) ? \
				 (void)0 : (void)gprintf 
#define TRACE_READING_PERFORMANCE !(debug & DEBUG_READING_PERFORMANCE) ? \
				 (void)0 : (void)gprintf 
#define TRACE_SCORING		!(debug & DEBUG_SCORING) ? \
				 (void)0 : (void)gprintf 
#define TRACE_AFTERMATH		!(debug & DEBUG_AFTERMATH) ? \
				 (void)0 : (void)gprintf 
#define TRACE_ATARI_ATARI	!(debug & DEBUG_ATARI_ATARI) ? \
				 (void)0 : (void)gprintf 
#define TRACE_READING_CACHE	!(debug & DEBUG_READING_CACHE) ? \
				 (void)0 : (void)gprintf 
#define TRACE_TERRITORY		!(debug & DEBUG_TERRITORY) ? \
				 (void)0 : (void)gprintf 
#define TRACE_OWL_PERSISTENT_CACHE !(debug & DEBUG_OWL_PERSISTENT_CACHE) ? \
				 (void)0 : (void)gprintf 
#define TRACE_TOP_MOVES		!(debug & DEBUG_TOP_MOVES) ? \
				 (void)0 : (void)gprintf 
#define TRACE_MISCELLANEOUS	!(debug & DEBUG_MISCELLANEOUS) ? \
				 (void)0 : (void)gprintf 


/* genmove.c */
#define EXAMINE_WORMS               1
#define EXAMINE_INITIAL_INFLUENCE   2
#define EXAMINE_DRAGONS_WITHOUT_OWL 3
#define EXAMINE_DRAGONS             4
#define EXAMINE_OWL_REASONS         5
#define EXAMINE_INITIAL_INFLUENCE2  6
#define FULL_EXAMINE_DRAGONS        7

#define EXAMINE_ALL                 99

void reset_engine(void);
void examine_position(int color, int how_much);
void silent_examine_position(int color, int how_much);


/* ================================================================ */
/*                         statistics functions                     */
/* ================================================================ */


/* These are mostly used for GTP examination. */
void reset_owl_node_counter(void);
int get_owl_node_counter(void);
void reset_reading_node_counter(void);
int get_reading_node_counter(void);
void reset_trymove_counter(void);
int get_trymove_counter(void);
void reset_connection_node_counter(void);
int get_connection_node_counter(void);


/* ================================================================ */
/*                         Low level functions                      */
/* ================================================================ */


/* board.c */
/* General board handling. */
void clear_board(void);
int test_gray_border(void);
void setup_board(Intersection new_board[MAX_BOARD][MAX_BOARD], int ko_pos,
		 int *last, float new_komi, int w_captured, int b_captured);


/* Putting stones on the board.. */
void add_stone(int pos, int color);
void remove_stone(int pos);
void play_move(int pos, int color);
int undo_move(int n);
int get_last_move(void);
int get_last_player(void);
int get_last_opponent_move(int color);
int is_pass(int pos);
int is_legal(int pos, int color);
int is_suicide(int pos, int color);
int is_illegal_ko_capture(int pos, int color);
int trymove(int pos, int color, const char *message, int str, 
	    int komaster, int kom_pos);
int semeai_trymove(int pos, int color, const char *message, 
		   int str1, int str2, int owl_phase, int value);
int tryko(int pos, int color, const char *message, 
	  int komaster, int kom_pos);
void popgo(void);

/* utils.c */
void change_dragon_status(int dr, int status);
void who_wins(int color, FILE *outfile);

/* high-level routine to generate the best move for the given color */
int genmove(int *i, int *j, int color);
int genmove_conservative(int *i, int *j, int color);

/* Play through the aftermath. */
float aftermath_compute_score(int color, float komi, SGFTree *tree);
int aftermath_final_status(int color, int pos);

/* Basic information gathering. */
/* worm.c */
void make_worms(void);
void compute_worm_influence(void);

/* dragon.c */
void make_dragons(int color, int stop_before_owl, int save_verbose);
void initialize_dragon_data(void);
void show_dragons(void);
int crude_status(int pos);
int dragon_status(int pos);
int same_dragon(int dr1, int dr2);

/* moyo functions */
void print_moyo(void);

/* sgffile.c */
void sgffile_add_debuginfo(SGFNode *node, int value);
void sgffile_output(SGFTree *tree);

void sgffile_printsgf(int color_to_play, const char *filename);
void sgffile_printboard(SGFTree *tree);
void sgffile_recordboard(SGFNode *node);

/* sgfdecide.c */
void decide_string(int pos);
void decide_connection(int apos, int bpos);
void decide_owl(int pos);
void decide_dragon_data(int pos);
void decide_semeai(int apos, int bpos);
void decide_tactical_semeai(int apos, int bpos);
void decide_position(int color);
void decide_eye(int pos);
void decide_combination(int color);
void decide_surrounded(int pos);

#endif  /* _GNUGO_H_ */
# 512 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/gnugo.h"


/*
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 2
 * End:
 */
# 24 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/semeai.c" 2

#if 0 /* expanded by -frewrite-includes */
#include <stdio.h>
#endif /* expanded by -frewrite-includes */
# 25 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/semeai.c"
# 26 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/semeai.c"
#if 0 /* expanded by -frewrite-includes */
#include <stdlib.h>
#endif /* expanded by -frewrite-includes */
# 26 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/semeai.c"
# 1 "/usr/include/stdlib.h" 1 3 4
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/*
 *	ISO C99 Standard: 7.20 General utilities	<stdlib.h>
 */

#ifndef	_STDLIB_H

#if 0 /* expanded by -frewrite-includes */
#include <features.h>
#endif /* expanded by -frewrite-includes */
# 24 "/usr/include/stdlib.h" 3 4
# 25 "/usr/include/stdlib.h" 3 4

/* Get size_t, wchar_t and NULL from <stddef.h>.  */
#define		__need_size_t
#ifndef __need_malloc_and_calloc
# define	__need_wchar_t
# define	__need_NULL
#endif
# 32 "/usr/include/stdlib.h" 3 4
#if 0 /* expanded by -frewrite-includes */
#include <stddef.h>
#endif /* expanded by -frewrite-includes */
# 32 "/usr/include/stdlib.h" 3 4
# 1 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 1 3 4
/*===---- stddef.h - Basic type definitions --------------------------------===
 *
 * Copyright (c) 2008 Eli Friedman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *===-----------------------------------------------------------------------===
 */

#if !defined(__STDDEF_H) || defined(__need_ptrdiff_t) ||                       \
    defined(__need_size_t) || defined(__need_wchar_t) ||                       \
    defined(__need_NULL) || defined(__need_wint_t)

#if !defined(__need_ptrdiff_t) && !defined(__need_size_t) &&                   \
    !defined(__need_wchar_t) && !defined(__need_NULL) &&                       \
    !defined(__need_wint_t)
/* Always define miscellaneous pieces when modules are available. */
#if !__has_feature(modules)
#define __STDDEF_H
#endif
# 37 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#define __need_ptrdiff_t
#define __need_size_t
#define __need_wchar_t
#define __need_NULL
#define __need_STDDEF_H_misc
/* __need_wint_t is intentionally not defined here. */
#endif
# 44 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_ptrdiff_t)
#if !defined(_PTRDIFF_T) || __has_feature(modules)
/* Always define ptrdiff_t when modules are available. */
#if !__has_feature(modules)
#define _PTRDIFF_T
#endif
# 51 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif
# 53 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_ptrdiff_t
#endif /* defined(__need_ptrdiff_t) */
# 55 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_size_t)
#if !defined(_SIZE_T) || __has_feature(modules)
/* Always define size_t when modules are available. */
#if !__has_feature(modules)
#define _SIZE_T
#endif
# 62 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ size_t;
#endif
# 64 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_size_t
#endif /*defined(__need_size_t) */
# 66 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
/* ISO9899:2011 7.20 (C11 Annex K): Define rsize_t if __STDC_WANT_LIB_EXT1__ is
 * enabled. */
#if (defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ >= 1 && \
     !defined(_RSIZE_T)) || __has_feature(modules)
/* Always define rsize_t when modules are available. */
#if !__has_feature(modules)
#define _RSIZE_T
#endif
# 76 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ rsize_t;
#endif
# 78 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#endif /* defined(__need_STDDEF_H_misc) */
# 79 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_wchar_t)
#ifndef __cplusplus
/* Always define wchar_t when modules are available. */
#if !defined(_WCHAR_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WCHAR_T
#if defined(_MSC_EXTENSIONS)
#define _WCHAR_T_DEFINED
#endif
# 89 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 90 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WCHAR_TYPE__ wchar_t;
#endif
# 92 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 93 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wchar_t
#endif /* defined(__need_wchar_t) */
# 95 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_NULL)
#undef NULL
#ifdef __cplusplus
#  if !defined(__MINGW32__) && !defined(_MSC_VER)
#    define NULL __null
#  else
# 102 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#    define NULL 0
#  endif
# 104 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#else
# 105 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#  define NULL ((void*)0)
#endif
# 107 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#ifdef __cplusplus
#if defined(_MSC_EXTENSIONS) && defined(_NATIVE_NULLPTR_SUPPORTED)
namespace std { typedef decltype(nullptr) nullptr_t; }
using ::std::nullptr_t;
#endif
# 112 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 113 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_NULL
#endif /* defined(__need_NULL) */
# 115 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
#if __STDC_VERSION__ >= 201112L || __cplusplus >= 201103L
#if 0 /* expanded by -frewrite-includes */
#include "__stddef_max_align_t.h"
#endif /* expanded by -frewrite-includes */
# 118 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
# 119 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 120 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#define offsetof(t, d) __builtin_offsetof(t, d)
#undef __need_STDDEF_H_misc
#endif  /* defined(__need_STDDEF_H_misc) */
# 123 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

/* Some C libraries expect to see a wint_t here. Others (notably MinGW) will use
__WINT_TYPE__ directly; accommodate both by requiring __need_wint_t */
#if defined(__need_wint_t)
/* Always define wint_t when modules are available. */
#if !defined(_WINT_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WINT_T
#endif
# 132 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WINT_TYPE__ wint_t;
#endif
# 134 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wint_t
#endif /* __need_wint_t */
# 136 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#endif
# 138 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
# 33 "/usr/include/stdlib.h" 2 3 4

__BEGIN_DECLS

#ifndef __need_malloc_and_calloc
#define	_STDLIB_H	1

#if (defined __USE_XOPEN || defined __USE_XOPEN2K8) && !defined _SYS_WAIT_H
/* XPG requires a few symbols from <sys/wait.h> being defined.  */
#if 0 /* expanded by -frewrite-includes */
# include <bits/waitflags.h>
#endif /* expanded by -frewrite-includes */
# 41 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/waitflags.h" 1 3 4
/* Definitions of flag bits for `waitpid' et al.
   Copyright (C) 1992-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#if !defined _SYS_WAIT_H && !defined _STDLIB_H
# error "Never include <bits/waitflags.h> directly; use <sys/wait.h> instead."
#endif
# 22 "/usr/include/x86_64-linux-gnu/bits/waitflags.h" 3 4


/* Bits in the third argument to `waitpid'.  */
#define	WNOHANG		1	/* Don't block waiting.  */
#define	WUNTRACED	2	/* Report status of stopped children.  */

/* Bits in the fourth argument to `waitid'.  */
#define WSTOPPED	2	/* Report stopped child (same as WUNTRACED). */
#define WEXITED		4	/* Report dead child.  */
#define WCONTINUED	8	/* Report continued child.  */
#define WNOWAIT		0x01000000 /* Don't reap, just poll status.  */

#define __WNOTHREAD     0x20000000 /* Don't wait on children of other threads
				      in this group */
#define __WALL		0x40000000 /* Wait for any child.  */
#define __WCLONE	0x80000000 /* Wait for cloned process.  */

/* The following values are used by the `waitid' function.  */
#if defined __USE_XOPEN || defined __USE_XOPEN2K8
# ifndef __ENUM_IDTYPE_T
# define __ENUM_IDTYPE_T 1

/* The Linux kernel defines these bare, rather than an enum,
   which causes a conflict if the include order is reversed. */
# undef P_ALL
# undef P_PID
# undef P_PGID

typedef enum
{
  P_ALL,		/* Wait for any child.  */
  P_PID,		/* Wait for specified process.  */
  P_PGID		/* Wait for members of process group.  */
} idtype_t;
# endif
# 57 "/usr/include/x86_64-linux-gnu/bits/waitflags.h" 3 4
#endif
# 58 "/usr/include/x86_64-linux-gnu/bits/waitflags.h" 3 4
# 42 "/usr/include/stdlib.h" 2 3 4
#if 0 /* expanded by -frewrite-includes */
# include <bits/waitstatus.h>
#endif /* expanded by -frewrite-includes */
# 42 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/waitstatus.h" 1 3 4
/* Definitions of status bits for `wait' et al.
   Copyright (C) 1992-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#if !defined _SYS_WAIT_H && !defined _STDLIB_H
# error "Never include <bits/waitstatus.h> directly; use <sys/wait.h> instead."
#endif
# 22 "/usr/include/x86_64-linux-gnu/bits/waitstatus.h" 3 4


/* Everything extant so far uses these same bits.  */


/* If WIFEXITED(STATUS), the low-order 8 bits of the status.  */
#define	__WEXITSTATUS(status)	(((status) & 0xff00) >> 8)

/* If WIFSIGNALED(STATUS), the terminating signal.  */
#define	__WTERMSIG(status)	((status) & 0x7f)

/* If WIFSTOPPED(STATUS), the signal that stopped the child.  */
#define	__WSTOPSIG(status)	__WEXITSTATUS(status)

/* Nonzero if STATUS indicates normal termination.  */
#define	__WIFEXITED(status)	(__WTERMSIG(status) == 0)

/* Nonzero if STATUS indicates termination by a signal.  */
#define __WIFSIGNALED(status) \
  (((signed char) (((status) & 0x7f) + 1) >> 1) > 0)

/* Nonzero if STATUS indicates the child is stopped.  */
#define	__WIFSTOPPED(status)	(((status) & 0xff) == 0x7f)

/* Nonzero if STATUS indicates the child continued after a stop.  We only
   define this if <bits/waitflags.h> provides the WCONTINUED flag bit.  */
#ifdef WCONTINUED
# define __WIFCONTINUED(status)	((status) == __W_CONTINUED)
#endif
# 51 "/usr/include/x86_64-linux-gnu/bits/waitstatus.h" 3 4

/* Nonzero if STATUS indicates the child dumped core.  */
#define	__WCOREDUMP(status)	((status) & __WCOREFLAG)

/* Macros for constructing status values.  */
#define	__W_EXITCODE(ret, sig)	((ret) << 8 | (sig))
#define	__W_STOPCODE(sig)	((sig) << 8 | 0x7f)
#define __W_CONTINUED		0xffff
#define	__WCOREFLAG		0x80


#ifdef	__USE_MISC

#if 0 /* expanded by -frewrite-includes */
# include <endian.h>
#endif /* expanded by -frewrite-includes */
# 64 "/usr/include/x86_64-linux-gnu/bits/waitstatus.h" 3 4
# 1 "/usr/include/endian.h" 1 3 4
/* Copyright (C) 1992-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef	_ENDIAN_H
#define	_ENDIAN_H	1

#if 0 /* expanded by -frewrite-includes */
#include <features.h>
#endif /* expanded by -frewrite-includes */
# 21 "/usr/include/endian.h" 3 4
# 22 "/usr/include/endian.h" 3 4

/* Definitions for byte order, according to significance of bytes,
   from low addresses to high addresses.  The value is what you get by
   putting '4' in the most significant byte, '3' in the second most
   significant byte, '2' in the second least significant byte, and '1'
   in the least significant byte, and then writing down one digit for
   each byte, starting with the byte at the lowest address at the left,
   and proceeding to the byte with the highest address at the right.  */

#define	__LITTLE_ENDIAN	1234
#define	__BIG_ENDIAN	4321
#define	__PDP_ENDIAN	3412

/* This file defines `__BYTE_ORDER' for the particular machine.  */
#if 0 /* expanded by -frewrite-includes */
#include <bits/endian.h>
#endif /* expanded by -frewrite-includes */
# 36 "/usr/include/endian.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/endian.h" 1 3 4
/* i386/x86_64 are little-endian.  */

#ifndef _ENDIAN_H
# error "Never use <bits/endian.h> directly; include <endian.h> instead."
#endif
# 6 "/usr/include/x86_64-linux-gnu/bits/endian.h" 3 4

#define __BYTE_ORDER __LITTLE_ENDIAN
# 37 "/usr/include/endian.h" 2 3 4

/* Some machines may need to use a different endianness for floating point
   values.  */
#ifndef __FLOAT_WORD_ORDER
# define __FLOAT_WORD_ORDER __BYTE_ORDER
#endif
# 43 "/usr/include/endian.h" 3 4

#ifdef	__USE_MISC
# define LITTLE_ENDIAN	__LITTLE_ENDIAN
# define BIG_ENDIAN	__BIG_ENDIAN
# define PDP_ENDIAN	__PDP_ENDIAN
# define BYTE_ORDER	__BYTE_ORDER
#endif
# 50 "/usr/include/endian.h" 3 4

#if __BYTE_ORDER == __LITTLE_ENDIAN
# define __LONG_LONG_PAIR(HI, LO) LO, HI
#elif __BYTE_ORDER == __BIG_ENDIAN
# 54 "/usr/include/endian.h" 3 4
# define __LONG_LONG_PAIR(HI, LO) HI, LO
#endif
# 56 "/usr/include/endian.h" 3 4


#if defined __USE_MISC && !defined __ASSEMBLER__
/* Conversion interfaces.  */
#if 0 /* expanded by -frewrite-includes */
# include <bits/byteswap.h>
#endif /* expanded by -frewrite-includes */
# 60 "/usr/include/endian.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 1 3 4
/* Macros to swap the order of bytes in integer values.
   Copyright (C) 1997-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#if !defined _BYTESWAP_H && !defined _NETINET_IN_H && !defined _ENDIAN_H
# error "Never use <bits/byteswap.h> directly; include <byteswap.h> instead."
#endif
# 22 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 3 4

#ifndef _BITS_BYTESWAP_H
#define _BITS_BYTESWAP_H 1

#if 0 /* expanded by -frewrite-includes */
#include <features.h>
#endif /* expanded by -frewrite-includes */
# 26 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 3 4
# 27 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 3 4
#if 0 /* expanded by -frewrite-includes */
#include <bits/types.h>
#endif /* expanded by -frewrite-includes */
# 27 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 3 4
# 28 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 3 4
#if 0 /* expanded by -frewrite-includes */
#include <bits/wordsize.h>
#endif /* expanded by -frewrite-includes */
# 28 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
/* Determine the wordsize from the preprocessor defines.  */

#if defined __x86_64__ && !defined __ILP32__
# define __WORDSIZE	64
#else
# 6 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 3 4
# define __WORDSIZE	32
#endif
# 8 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 3 4

#ifdef __x86_64__
# define __WORDSIZE_TIME64_COMPAT32	1
/* Both x86-64 and x32 use the 64-bit system call interface.  */
# define __SYSCALL_WORDSIZE		64
#endif
# 14 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 3 4
# 29 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 2 3 4

/* Swap bytes in 16 bit value.  */
#define __bswap_constant_16(x) \
     ((unsigned short int) ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8)))

/* Get __bswap_16.  */
#if 0 /* expanded by -frewrite-includes */
#include <bits/byteswap-16.h>
#endif /* expanded by -frewrite-includes */
# 35 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/byteswap-16.h" 1 3 4
/* Macros to swap the order of bytes in 16-bit integer values.
   Copyright (C) 2012-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _BITS_BYTESWAP_H
# error "Never use <bits/byteswap-16.h> directly; include <byteswap.h> instead."
#endif
# 22 "/usr/include/x86_64-linux-gnu/bits/byteswap-16.h" 3 4

#ifdef __GNUC__
# if __GNUC__ >= 2
#  define __bswap_16(x) \
     (__extension__							      \
      ({ unsigned short int __v, __x = (unsigned short int) (x);	      \
	 if (__builtin_constant_p (__x))				      \
	   __v = __bswap_constant_16 (__x);				      \
	 else								      \
	   __asm__ ("rorw $8, %w0"					      \
		    : "=r" (__v)					      \
		    : "0" (__x)						      \
		    : "cc");						      \
	 __v; }))
# else
# 37 "/usr/include/x86_64-linux-gnu/bits/byteswap-16.h" 3 4
/* This is better than nothing.  */
#  define __bswap_16(x) \
     (__extension__							      \
      ({ unsigned short int __x = (unsigned short int) (x);		      \
	 __bswap_constant_16 (__x); }))
# endif
# 43 "/usr/include/x86_64-linux-gnu/bits/byteswap-16.h" 3 4
#else
# 44 "/usr/include/x86_64-linux-gnu/bits/byteswap-16.h" 3 4
static __inline unsigned short int
__bswap_16 (unsigned short int __bsx)
{
  return __bswap_constant_16 (__bsx);
}
#endif
# 50 "/usr/include/x86_64-linux-gnu/bits/byteswap-16.h" 3 4
# 36 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 2 3 4

/* Swap bytes in 32 bit value.  */
#define __bswap_constant_32(x) \
     ((((x) & 0xff000000) >> 24) | (((x) & 0x00ff0000) >>  8) |		      \
      (((x) & 0x0000ff00) <<  8) | (((x) & 0x000000ff) << 24))

#ifdef __GNUC__
# if __GNUC_PREREQ (4, 3)
static __inline unsigned int
__bswap_32 (unsigned int __bsx)
{
  return __builtin_bswap32 (__bsx);
}
# elif __GNUC__ >= 2
# 50 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 3 4
#  if __WORDSIZE == 64 || (defined __i486__ || defined __pentium__	      \
			   || defined __pentiumpro__ || defined __pentium4__  \
			   || defined __k8__ || defined __athlon__	      \
			   || defined __k6__ || defined __nocona__	      \
			   || defined __core2__ || defined __geode__	      \
			   || defined __amdfam10__)
/* To swap the bytes in a word the i486 processors and up provide the
   `bswap' opcode.  On i386 we have to use three instructions.  */
#   define __bswap_32(x) \
      (__extension__							      \
       ({ unsigned int __v, __x = (x);					      \
	  if (__builtin_constant_p (__x))				      \
	    __v = __bswap_constant_32 (__x);				      \
	  else								      \
	    __asm__ ("bswap %0" : "=r" (__v) : "0" (__x));		      \
	  __v; }))
#  else
# 67 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 3 4
#   define __bswap_32(x)						      \
      (__extension__							      \
       ({ unsigned int __v, __x = (x);					      \
	  if (__builtin_constant_p (__x))				      \
	    __v = __bswap_constant_32 (__x);				      \
	  else								      \
	    __asm__ ("rorw $8, %w0;"					      \
		     "rorl $16, %0;"					      \
		     "rorw $8, %w0"					      \
		     : "=r" (__v)					      \
		     : "0" (__x)					      \
		     : "cc");						      \
	  __v; }))
#  endif
# 81 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 3 4
# else
# 82 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 3 4
#  define __bswap_32(x) \
     (__extension__							      \
      ({ unsigned int __x = (x); __bswap_constant_32 (__x); }))
# endif
# 86 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 3 4
#else
# 87 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 3 4
static __inline unsigned int
__bswap_32 (unsigned int __bsx)
{
  return __bswap_constant_32 (__bsx);
}
#endif
# 93 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 3 4


#if __GNUC_PREREQ (2, 0)
/* Swap bytes in 64 bit value.  */
# define __bswap_constant_64(x) \
     (__extension__ ((((x) & 0xff00000000000000ull) >> 56)		      \
		     | (((x) & 0x00ff000000000000ull) >> 40)		      \
		     | (((x) & 0x0000ff0000000000ull) >> 24)		      \
		     | (((x) & 0x000000ff00000000ull) >> 8)		      \
		     | (((x) & 0x00000000ff000000ull) << 8)		      \
		     | (((x) & 0x0000000000ff0000ull) << 24)		      \
		     | (((x) & 0x000000000000ff00ull) << 40)		      \
		     | (((x) & 0x00000000000000ffull) << 56)))

# if __GNUC_PREREQ (4, 3)
static __inline __uint64_t
__bswap_64 (__uint64_t __bsx)
{
  return __builtin_bswap64 (__bsx);
}
# elif __WORDSIZE == 64
# 114 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 3 4
#  define __bswap_64(x) \
     (__extension__							      \
      ({ __uint64_t __v, __x = (x);					      \
	 if (__builtin_constant_p (__x))				      \
	   __v = __bswap_constant_64 (__x);				      \
	 else								      \
	   __asm__ ("bswap %q0" : "=r" (__v) : "0" (__x));		      \
	 __v; }))
# else
# 123 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 3 4
#  define __bswap_64(x) \
     (__extension__                                                           \
      ({ union { __extension__ __uint64_t __ll;		                      \
		 unsigned int __l[2]; } __w, __r;                             \
	 if (__builtin_constant_p (x))                                        \
	   __r.__ll = __bswap_constant_64 (x);                                \
	 else                                                                 \
	   {                                                                  \
	     __w.__ll = (x);                                                  \
	     __r.__l[0] = __bswap_32 (__w.__l[1]);                            \
	     __r.__l[1] = __bswap_32 (__w.__l[0]);                            \
	   }                                                                  \
	 __r.__ll; }))
# endif
# 137 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 3 4
#else
# 138 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 3 4
# define __bswap_constant_64(x) \
     ((((x) & 0xff00000000000000ull) >> 56)				      \
      | (((x) & 0x00ff000000000000ull) >> 40)				      \
      | (((x) & 0x0000ff0000000000ull) >> 24)				      \
      | (((x) & 0x000000ff00000000ull) >> 8)				      \
      | (((x) & 0x00000000ff000000ull) << 8)				      \
      | (((x) & 0x0000000000ff0000ull) << 24)				      \
      | (((x) & 0x000000000000ff00ull) << 40)				      \
      | (((x) & 0x00000000000000ffull) << 56))

static __inline __uint64_t
__bswap_64 (__uint64_t __bsx)
{
  return __bswap_constant_64 (__bsx);
}
#endif
# 154 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 3 4

#endif /* _BITS_BYTESWAP_H */
# 156 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 3 4
# 61 "/usr/include/endian.h" 2 3 4

# if __BYTE_ORDER == __LITTLE_ENDIAN
#  define htobe16(x) __bswap_16 (x)
#  define htole16(x) (x)
#  define be16toh(x) __bswap_16 (x)
#  define le16toh(x) (x)

#  define htobe32(x) __bswap_32 (x)
#  define htole32(x) (x)
#  define be32toh(x) __bswap_32 (x)
#  define le32toh(x) (x)

#  define htobe64(x) __bswap_64 (x)
#  define htole64(x) (x)
#  define be64toh(x) __bswap_64 (x)
#  define le64toh(x) (x)

# else
# 79 "/usr/include/endian.h" 3 4
#  define htobe16(x) (x)
#  define htole16(x) __bswap_16 (x)
#  define be16toh(x) (x)
#  define le16toh(x) __bswap_16 (x)

#  define htobe32(x) (x)
#  define htole32(x) __bswap_32 (x)
#  define be32toh(x) (x)
#  define le32toh(x) __bswap_32 (x)

#  define htobe64(x) (x)
#  define htole64(x) __bswap_64 (x)
#  define be64toh(x) (x)
#  define le64toh(x) __bswap_64 (x)
# endif
# 94 "/usr/include/endian.h" 3 4
#endif
# 95 "/usr/include/endian.h" 3 4

#endif	/* endian.h */
# 97 "/usr/include/endian.h" 3 4
# 65 "/usr/include/x86_64-linux-gnu/bits/waitstatus.h" 2 3 4

union wait
  {
    int w_status;
    struct
      {
# if	__BYTE_ORDER == __LITTLE_ENDIAN
	unsigned int __w_termsig:7; /* Terminating signal.  */
	unsigned int __w_coredump:1; /* Set if dumped core.  */
	unsigned int __w_retcode:8; /* Return code if exited normally.  */
	unsigned int:16;
# endif				/* Little endian.  */
# 77 "/usr/include/x86_64-linux-gnu/bits/waitstatus.h" 3 4
# if	__BYTE_ORDER == __BIG_ENDIAN
	unsigned int:16;
	unsigned int __w_retcode:8;
	unsigned int __w_coredump:1;
	unsigned int __w_termsig:7;
# endif				/* Big endian.  */
# 83 "/usr/include/x86_64-linux-gnu/bits/waitstatus.h" 3 4
      } __wait_terminated;
    struct
      {
# if	__BYTE_ORDER == __LITTLE_ENDIAN
	unsigned int __w_stopval:8; /* W_STOPPED if stopped.  */
	unsigned int __w_stopsig:8; /* Stopping signal.  */
	unsigned int:16;
# endif				/* Little endian.  */
# 91 "/usr/include/x86_64-linux-gnu/bits/waitstatus.h" 3 4
# if	__BYTE_ORDER == __BIG_ENDIAN
	unsigned int:16;
	unsigned int __w_stopsig:8; /* Stopping signal.  */
	unsigned int __w_stopval:8; /* W_STOPPED if stopped.  */
# endif				/* Big endian.  */
# 96 "/usr/include/x86_64-linux-gnu/bits/waitstatus.h" 3 4
      } __wait_stopped;
  };

# define w_termsig	__wait_terminated.__w_termsig
# define w_coredump	__wait_terminated.__w_coredump
# define w_retcode	__wait_terminated.__w_retcode
# define w_stopsig	__wait_stopped.__w_stopsig
# define w_stopval	__wait_stopped.__w_stopval

#endif	/* Use misc.  */
# 106 "/usr/include/x86_64-linux-gnu/bits/waitstatus.h" 3 4
# 43 "/usr/include/stdlib.h" 2 3 4

# ifdef __USE_MISC

/* Lots of hair to allow traditional BSD use of `union wait'
   as well as POSIX.1 use of `int' for the status word.  */

#  if defined __GNUC__ && !defined __cplusplus
#   define __WAIT_INT(status) \
  (__extension__ (((union { __typeof(status) __in; int __i; }) \
		   { .__in = (status) }).__i))
#  else
# 54 "/usr/include/stdlib.h" 3 4
#   define __WAIT_INT(status)	(*(int *) &(status))
#  endif
# 56 "/usr/include/stdlib.h" 3 4

/* This is the type of the argument to `wait'.  The funky union
   causes redeclarations with either `int *' or `union wait *' to be
   allowed without complaint.  __WAIT_STATUS_DEFN is the type used in
   the actual function definitions.  */

#  if !defined __GNUC__ || __GNUC__ < 2 || defined __cplusplus
#   define __WAIT_STATUS	void *
#   define __WAIT_STATUS_DEFN	void *
#  else
# 66 "/usr/include/stdlib.h" 3 4
/* This works in GCC 2.6.1 and later.  */
typedef union
  {
    union wait *__uptr;
    int *__iptr;
  } __WAIT_STATUS __attribute__ ((__transparent_union__));
#   define __WAIT_STATUS_DEFN	int *
#  endif
# 74 "/usr/include/stdlib.h" 3 4

# else /* Don't use misc.  */
# 76 "/usr/include/stdlib.h" 3 4

#  define __WAIT_INT(status)	(status)
#  define __WAIT_STATUS		int *
#  define __WAIT_STATUS_DEFN	int *

# endif /* Use misc.  */
# 82 "/usr/include/stdlib.h" 3 4

/* Define the macros <sys/wait.h> also would define this way.  */
# define WEXITSTATUS(status)	__WEXITSTATUS (__WAIT_INT (status))
# define WTERMSIG(status)	__WTERMSIG (__WAIT_INT (status))
# define WSTOPSIG(status)	__WSTOPSIG (__WAIT_INT (status))
# define WIFEXITED(status)	__WIFEXITED (__WAIT_INT (status))
# define WIFSIGNALED(status)	__WIFSIGNALED (__WAIT_INT (status))
# define WIFSTOPPED(status)	__WIFSTOPPED (__WAIT_INT (status))
# ifdef __WIFCONTINUED
#  define WIFCONTINUED(status)	__WIFCONTINUED (__WAIT_INT (status))
# endif
# 93 "/usr/include/stdlib.h" 3 4
#endif	/* X/Open or XPG7 and <sys/wait.h> not included.  */
# 94 "/usr/include/stdlib.h" 3 4

__BEGIN_NAMESPACE_STD
/* Returned by `div'.  */
typedef struct
  {
    int quot;			/* Quotient.  */
    int rem;			/* Remainder.  */
  } div_t;

/* Returned by `ldiv'.  */
#ifndef __ldiv_t_defined
typedef struct
  {
    long int quot;		/* Quotient.  */
    long int rem;		/* Remainder.  */
  } ldiv_t;
# define __ldiv_t_defined	1
#endif
# 112 "/usr/include/stdlib.h" 3 4
__END_NAMESPACE_STD

#if defined __USE_ISOC99 && !defined __lldiv_t_defined
__BEGIN_NAMESPACE_C99
/* Returned by `lldiv'.  */
__extension__ typedef struct
  {
    long long int quot;		/* Quotient.  */
    long long int rem;		/* Remainder.  */
  } lldiv_t;
# define __lldiv_t_defined	1
__END_NAMESPACE_C99
#endif
# 125 "/usr/include/stdlib.h" 3 4


/* The largest number rand will return (same as INT_MAX).  */
#define	RAND_MAX	2147483647


/* We define these the same for all machines.
   Changes from this to the outside world should be done in `_exit'.  */
#define	EXIT_FAILURE	1	/* Failing exit status.  */
#define	EXIT_SUCCESS	0	/* Successful exit status.  */


/* Maximum length of a multibyte character in the current locale.  */
#define	MB_CUR_MAX	(__ctype_get_mb_cur_max ())
extern size_t __ctype_get_mb_cur_max (void) __THROW __wur;


__BEGIN_NAMESPACE_STD
/* Convert a string to a floating-point number.  */
extern double atof (const char *__nptr)
     __THROW __attribute_pure__ __nonnull ((1)) __wur;
/* Convert a string to an integer.  */
extern int atoi (const char *__nptr)
     __THROW __attribute_pure__ __nonnull ((1)) __wur;
/* Convert a string to a long integer.  */
extern long int atol (const char *__nptr)
     __THROW __attribute_pure__ __nonnull ((1)) __wur;
__END_NAMESPACE_STD

#ifdef __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Convert a string to a long long integer.  */
__extension__ extern long long int atoll (const char *__nptr)
     __THROW __attribute_pure__ __nonnull ((1)) __wur;
__END_NAMESPACE_C99
#endif
# 161 "/usr/include/stdlib.h" 3 4

__BEGIN_NAMESPACE_STD
/* Convert a string to a floating-point number.  */
extern double strtod (const char *__restrict __nptr,
		      char **__restrict __endptr)
     __THROW __nonnull ((1));
__END_NAMESPACE_STD

#ifdef	__USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Likewise for `float' and `long double' sizes of floating-point numbers.  */
extern float strtof (const char *__restrict __nptr,
		     char **__restrict __endptr) __THROW __nonnull ((1));

extern long double strtold (const char *__restrict __nptr,
			    char **__restrict __endptr)
     __THROW __nonnull ((1));
__END_NAMESPACE_C99
#endif
# 180 "/usr/include/stdlib.h" 3 4

__BEGIN_NAMESPACE_STD
/* Convert a string to a long integer.  */
extern long int strtol (const char *__restrict __nptr,
			char **__restrict __endptr, int __base)
     __THROW __nonnull ((1));
/* Convert a string to an unsigned long integer.  */
extern unsigned long int strtoul (const char *__restrict __nptr,
				  char **__restrict __endptr, int __base)
     __THROW __nonnull ((1));
__END_NAMESPACE_STD

#ifdef __USE_MISC
/* Convert a string to a quadword integer.  */
__extension__
extern long long int strtoq (const char *__restrict __nptr,
			     char **__restrict __endptr, int __base)
     __THROW __nonnull ((1));
/* Convert a string to an unsigned quadword integer.  */
__extension__
extern unsigned long long int strtouq (const char *__restrict __nptr,
				       char **__restrict __endptr, int __base)
     __THROW __nonnull ((1));
#endif /* Use misc.  */
# 204 "/usr/include/stdlib.h" 3 4

#ifdef __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Convert a string to a quadword integer.  */
__extension__
extern long long int strtoll (const char *__restrict __nptr,
			      char **__restrict __endptr, int __base)
     __THROW __nonnull ((1));
/* Convert a string to an unsigned quadword integer.  */
__extension__
extern unsigned long long int strtoull (const char *__restrict __nptr,
					char **__restrict __endptr, int __base)
     __THROW __nonnull ((1));
__END_NAMESPACE_C99
#endif /* ISO C99 or use MISC.  */
# 219 "/usr/include/stdlib.h" 3 4


#ifdef __USE_GNU
/* The concept of one static locale per category is not very well
   thought out.  Many applications will need to process its data using
   information from several different locales.  Another problem is
   the implementation of the internationalization handling in the
   ISO C++ standard library.  To support this another set of
   the functions using locale data exist which take an additional
   argument.

   Attention: even though several *_l interfaces are part of POSIX:2008,
   these are not.  */

/* Structure for reentrant locale using functions.  This is an
   (almost) opaque type for the user level programs.  */
#if 0 /* expanded by -frewrite-includes */
# include <xlocale.h>
#endif /* expanded by -frewrite-includes */
# 235 "/usr/include/stdlib.h" 3 4
# 236 "/usr/include/stdlib.h" 3 4

/* Special versions of the functions above which take the locale to
   use as an additional parameter.  */
extern long int strtol_l (const char *__restrict __nptr,
			  char **__restrict __endptr, int __base,
			  __locale_t __loc) __THROW __nonnull ((1, 4));

extern unsigned long int strtoul_l (const char *__restrict __nptr,
				    char **__restrict __endptr,
				    int __base, __locale_t __loc)
     __THROW __nonnull ((1, 4));

__extension__
extern long long int strtoll_l (const char *__restrict __nptr,
				char **__restrict __endptr, int __base,
				__locale_t __loc)
     __THROW __nonnull ((1, 4));

__extension__
extern unsigned long long int strtoull_l (const char *__restrict __nptr,
					  char **__restrict __endptr,
					  int __base, __locale_t __loc)
     __THROW __nonnull ((1, 4));

extern double strtod_l (const char *__restrict __nptr,
			char **__restrict __endptr, __locale_t __loc)
     __THROW __nonnull ((1, 3));

extern float strtof_l (const char *__restrict __nptr,
		       char **__restrict __endptr, __locale_t __loc)
     __THROW __nonnull ((1, 3));

extern long double strtold_l (const char *__restrict __nptr,
			      char **__restrict __endptr,
			      __locale_t __loc)
     __THROW __nonnull ((1, 3));
#endif /* GNU */
# 273 "/usr/include/stdlib.h" 3 4


#ifdef __USE_EXTERN_INLINES
__BEGIN_NAMESPACE_STD
__extern_inline int
__NTH (atoi (const char *__nptr))
{
  return (int) strtol (__nptr, (char **) NULL, 10);
}
__extern_inline long int
__NTH (atol (const char *__nptr))
{
  return strtol (__nptr, (char **) NULL, 10);
}
__END_NAMESPACE_STD

# ifdef __USE_ISOC99
__BEGIN_NAMESPACE_C99
__extension__ __extern_inline long long int
__NTH (atoll (const char *__nptr))
{
  return strtoll (__nptr, (char **) NULL, 10);
}
__END_NAMESPACE_C99
# endif
# 298 "/usr/include/stdlib.h" 3 4
#endif /* Optimizing and Inlining.  */
# 299 "/usr/include/stdlib.h" 3 4


#if defined __USE_MISC || defined __USE_XOPEN_EXTENDED
/* Convert N to base 64 using the digits "./0-9A-Za-z", least-significant
   digit first.  Returns a pointer to static storage overwritten by the
   next call.  */
extern char *l64a (long int __n) __THROW __wur;

/* Read a number from a string S in base 64 as above.  */
extern long int a64l (const char *__s)
     __THROW __attribute_pure__ __nonnull ((1)) __wur;

#endif	/* Use misc || extended X/Open.  */
# 312 "/usr/include/stdlib.h" 3 4

#if defined __USE_MISC || defined __USE_XOPEN_EXTENDED
#if 0 /* expanded by -frewrite-includes */
# include <sys/types.h>	/* we need int32_t... */
#endif /* expanded by -frewrite-includes */
# 314 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/sys/types.h" 1 3 4
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/*
 *	POSIX Standard: 2.6 Primitive System Data Types	<sys/types.h>
 */

#ifndef	_SYS_TYPES_H
#define	_SYS_TYPES_H	1

#if 0 /* expanded by -frewrite-includes */
#include <features.h>
#endif /* expanded by -frewrite-includes */
# 25 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
# 26 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4

__BEGIN_DECLS

#if 0 /* expanded by -frewrite-includes */
#include <bits/types.h>
#endif /* expanded by -frewrite-includes */
# 29 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
# 30 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4

#ifdef	__USE_MISC
# ifndef __u_char_defined
typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;
#  define __u_char_defined
# endif
# 42 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
#endif
# 43 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4

typedef __loff_t loff_t;

#ifndef __ino_t_defined
# ifndef __USE_FILE_OFFSET64
typedef __ino_t ino_t;
# else
# 50 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
typedef __ino64_t ino_t;
# endif
# 52 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
# define __ino_t_defined
#endif
# 54 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
#if defined __USE_LARGEFILE64 && !defined __ino64_t_defined
typedef __ino64_t ino64_t;
# define __ino64_t_defined
#endif
# 58 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4

#ifndef __dev_t_defined
typedef __dev_t dev_t;
# define __dev_t_defined
#endif
# 63 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4

#ifndef __gid_t_defined
typedef __gid_t gid_t;
# define __gid_t_defined
#endif
# 68 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4

#ifndef __mode_t_defined
typedef __mode_t mode_t;
# define __mode_t_defined
#endif
# 73 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4

#ifndef __nlink_t_defined
typedef __nlink_t nlink_t;
# define __nlink_t_defined
#endif
# 78 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4

#ifndef __uid_t_defined
typedef __uid_t uid_t;
# define __uid_t_defined
#endif
# 83 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4

#ifndef __off_t_defined
# ifndef __USE_FILE_OFFSET64
typedef __off_t off_t;
# else
# 88 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
typedef __off64_t off_t;
# endif
# 90 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
# define __off_t_defined
#endif
# 92 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
#if defined __USE_LARGEFILE64 && !defined __off64_t_defined
typedef __off64_t off64_t;
# define __off64_t_defined
#endif
# 96 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4

#ifndef __pid_t_defined
typedef __pid_t pid_t;
# define __pid_t_defined
#endif
# 101 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4

#if (defined __USE_XOPEN || defined __USE_XOPEN2K8) \
    && !defined __id_t_defined
typedef __id_t id_t;
# define __id_t_defined
#endif
# 107 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4

#ifndef __ssize_t_defined
typedef __ssize_t ssize_t;
# define __ssize_t_defined
#endif
# 112 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4

#ifdef	__USE_MISC
# ifndef __daddr_t_defined
typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;
#  define __daddr_t_defined
# endif
# 119 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
#endif
# 120 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4

#if (defined __USE_MISC || defined __USE_XOPEN) && !defined __key_t_defined
typedef __key_t key_t;
# define __key_t_defined
#endif
# 125 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4

#if defined __USE_XOPEN || defined __USE_XOPEN2K8
# define __need_clock_t
#endif
# 129 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
#define	__need_time_t
#define __need_timer_t
#define __need_clockid_t
#if 0 /* expanded by -frewrite-includes */
#include <time.h>
#endif /* expanded by -frewrite-includes */
# 132 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
# 1 "/usr/include/time.h" 1 3 4
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/*
 *	ISO C99 Standard: 7.23 Date and time	<time.h>
 */

#ifndef	_TIME_H

#if (! defined __need_time_t && !defined __need_clock_t && \
     ! defined __need_timespec)
# define _TIME_H	1
#if 0 /* expanded by -frewrite-includes */
# include <features.h>
#endif /* expanded by -frewrite-includes */
# 27 "/usr/include/time.h" 3 4
# 28 "/usr/include/time.h" 3 4

__BEGIN_DECLS

#endif
# 32 "/usr/include/time.h" 3 4

#ifdef	_TIME_H
/* Get size_t and NULL from <stddef.h>.  */
# define __need_size_t
# define __need_NULL
#if 0 /* expanded by -frewrite-includes */
# include <stddef.h>
#endif /* expanded by -frewrite-includes */
# 37 "/usr/include/time.h" 3 4
# 38 "/usr/include/time.h" 3 4

/* This defines CLOCKS_PER_SEC, which is the number of processor clock
   ticks per second.  */
#if 0 /* expanded by -frewrite-includes */
# include <bits/time.h>
#endif /* expanded by -frewrite-includes */
# 41 "/usr/include/time.h" 3 4
# 42 "/usr/include/time.h" 3 4

/* This is the obsolete POSIX.1-1988 name for the same constant.  */
# if !defined __STRICT_ANSI__ && !defined __USE_XOPEN2K
#  ifndef CLK_TCK
#   define CLK_TCK	CLOCKS_PER_SEC
#  endif
# 48 "/usr/include/time.h" 3 4
# endif
# 49 "/usr/include/time.h" 3 4

#endif /* <time.h> included.  */
# 51 "/usr/include/time.h" 3 4

#if !defined __clock_t_defined && (defined _TIME_H || defined __need_clock_t)
# define __clock_t_defined	1

#if 0 /* expanded by -frewrite-includes */
# include <bits/types.h>
#endif /* expanded by -frewrite-includes */
# 55 "/usr/include/time.h" 3 4
# 56 "/usr/include/time.h" 3 4

__BEGIN_NAMESPACE_STD
/* Returned by `clock'.  */
typedef __clock_t clock_t;
__END_NAMESPACE_STD
#if defined __USE_XOPEN || defined __USE_POSIX
__USING_NAMESPACE_STD(clock_t)
#endif
# 64 "/usr/include/time.h" 3 4

#endif /* clock_t not defined and <time.h> or need clock_t.  */
# 66 "/usr/include/time.h" 3 4
#undef	__need_clock_t

#if !defined __time_t_defined && (defined _TIME_H || defined __need_time_t)
# define __time_t_defined	1

#if 0 /* expanded by -frewrite-includes */
# include <bits/types.h>
#endif /* expanded by -frewrite-includes */
# 71 "/usr/include/time.h" 3 4
# 72 "/usr/include/time.h" 3 4

__BEGIN_NAMESPACE_STD
/* Returned by `time'.  */
typedef __time_t time_t;
__END_NAMESPACE_STD
#ifdef __USE_POSIX
__USING_NAMESPACE_STD(time_t)
#endif
# 80 "/usr/include/time.h" 3 4

#endif /* time_t not defined and <time.h> or need time_t.  */
# 82 "/usr/include/time.h" 3 4
#undef	__need_time_t

#if !defined __clockid_t_defined && \
   ((defined _TIME_H && defined __USE_POSIX199309) || defined __need_clockid_t)
# define __clockid_t_defined	1

#if 0 /* expanded by -frewrite-includes */
# include <bits/types.h>
#endif /* expanded by -frewrite-includes */
# 88 "/usr/include/time.h" 3 4
# 89 "/usr/include/time.h" 3 4

/* Clock ID used in clock and timer functions.  */
typedef __clockid_t clockid_t;

#endif /* clockid_t not defined and <time.h> or need clockid_t.  */
# 94 "/usr/include/time.h" 3 4
#undef	__clockid_time_t

#if !defined __timer_t_defined && \
    ((defined _TIME_H && defined __USE_POSIX199309) || defined __need_timer_t)
# define __timer_t_defined	1

#if 0 /* expanded by -frewrite-includes */
# include <bits/types.h>
#endif /* expanded by -frewrite-includes */
# 100 "/usr/include/time.h" 3 4
# 101 "/usr/include/time.h" 3 4

/* Timer ID returned by `timer_create'.  */
typedef __timer_t timer_t;

#endif /* timer_t not defined and <time.h> or need timer_t.  */
# 106 "/usr/include/time.h" 3 4
#undef	__need_timer_t


#if (!defined __timespec_defined					\
     && ((defined _TIME_H						\
	  && (defined __USE_POSIX199309					\
	      || defined __USE_ISOC11))					\
	 || defined __need_timespec))
# define __timespec_defined	1

#if 0 /* expanded by -frewrite-includes */
# include <bits/types.h>	/* This defines __time_t for us.  */
#endif /* expanded by -frewrite-includes */
# 116 "/usr/include/time.h" 3 4
# 117 "/usr/include/time.h" 3 4

/* POSIX.1b structure for a time value.  This is like a `struct timeval' but
   has nanoseconds instead of microseconds.  */
struct timespec
  {
    __time_t tv_sec;		/* Seconds.  */
    __syscall_slong_t tv_nsec;	/* Nanoseconds.  */
  };

#endif /* timespec not defined and <time.h> or need timespec.  */
# 127 "/usr/include/time.h" 3 4
#undef	__need_timespec


#ifdef	_TIME_H
__BEGIN_NAMESPACE_STD
/* Used by other time functions.  */
struct tm
{
  int tm_sec;			/* Seconds.	[0-60] (1 leap second) */
  int tm_min;			/* Minutes.	[0-59] */
  int tm_hour;			/* Hours.	[0-23] */
  int tm_mday;			/* Day.		[1-31] */
  int tm_mon;			/* Month.	[0-11] */
  int tm_year;			/* Year	- 1900.  */
  int tm_wday;			/* Day of week.	[0-6] */
  int tm_yday;			/* Days in year.[0-365]	*/
  int tm_isdst;			/* DST.		[-1/0/1]*/

# ifdef	__USE_MISC
  long int tm_gmtoff;		/* Seconds east of UTC.  */
  const char *tm_zone;		/* Timezone abbreviation.  */
# else
# 149 "/usr/include/time.h" 3 4
  long int __tm_gmtoff;		/* Seconds east of UTC.  */
  const char *__tm_zone;	/* Timezone abbreviation.  */
# endif
# 152 "/usr/include/time.h" 3 4
};
__END_NAMESPACE_STD
#if defined __USE_XOPEN || defined __USE_POSIX
__USING_NAMESPACE_STD(tm)
#endif
# 157 "/usr/include/time.h" 3 4


# ifdef __USE_POSIX199309
/* POSIX.1b structure for timer start values and intervals.  */
struct itimerspec
  {
    struct timespec it_interval;
    struct timespec it_value;
  };

/* We can use a simple forward declaration.  */
struct sigevent;

# endif	/* POSIX.1b */
# 171 "/usr/include/time.h" 3 4

# ifdef __USE_XOPEN2K
#  ifndef __pid_t_defined
typedef __pid_t pid_t;
#   define __pid_t_defined
#  endif
# 177 "/usr/include/time.h" 3 4
# endif
# 178 "/usr/include/time.h" 3 4


# ifdef __USE_ISOC11
/* Time base values for timespec_get.  */
# define TIME_UTC 1
# endif
# 184 "/usr/include/time.h" 3 4


__BEGIN_NAMESPACE_STD
/* Time used by the program so far (user time + system time).
   The result / CLOCKS_PER_SECOND is program time in seconds.  */
extern clock_t clock (void) __THROW;

/* Return the current time and put it in *TIMER if TIMER is not NULL.  */
extern time_t time (time_t *__timer) __THROW;

/* Return the difference between TIME1 and TIME0.  */
extern double difftime (time_t __time1, time_t __time0)
     __THROW __attribute__ ((__const__));

/* Return the `time_t' representation of TP and normalize TP.  */
extern time_t mktime (struct tm *__tp) __THROW;


/* Format TP into S according to FORMAT.
   Write no more than MAXSIZE characters and return the number
   of characters written, or 0 if it would exceed MAXSIZE.  */
extern size_t strftime (char *__restrict __s, size_t __maxsize,
			const char *__restrict __format,
			const struct tm *__restrict __tp) __THROW;
__END_NAMESPACE_STD

# ifdef __USE_XOPEN
/* Parse S according to FORMAT and store binary time information in TP.
   The return value is a pointer to the first unparsed character in S.  */
extern char *strptime (const char *__restrict __s,
		       const char *__restrict __fmt, struct tm *__tp)
     __THROW;
# endif
# 217 "/usr/include/time.h" 3 4

# ifdef __USE_XOPEN2K8
/* Similar to the two functions above but take the information from
   the provided locale and not the global locale.  */
#if 0 /* expanded by -frewrite-includes */
# include <xlocale.h>
#endif /* expanded by -frewrite-includes */
# 221 "/usr/include/time.h" 3 4
# 222 "/usr/include/time.h" 3 4

extern size_t strftime_l (char *__restrict __s, size_t __maxsize,
			  const char *__restrict __format,
			  const struct tm *__restrict __tp,
			  __locale_t __loc) __THROW;
# endif
# 228 "/usr/include/time.h" 3 4

# ifdef __USE_GNU
extern char *strptime_l (const char *__restrict __s,
			 const char *__restrict __fmt, struct tm *__tp,
			 __locale_t __loc) __THROW;
# endif
# 234 "/usr/include/time.h" 3 4


__BEGIN_NAMESPACE_STD
/* Return the `struct tm' representation of *TIMER
   in Universal Coordinated Time (aka Greenwich Mean Time).  */
extern struct tm *gmtime (const time_t *__timer) __THROW;

/* Return the `struct tm' representation
   of *TIMER in the local timezone.  */
extern struct tm *localtime (const time_t *__timer) __THROW;
__END_NAMESPACE_STD

# ifdef __USE_POSIX
/* Return the `struct tm' representation of *TIMER in UTC,
   using *TP to store the result.  */
extern struct tm *gmtime_r (const time_t *__restrict __timer,
			    struct tm *__restrict __tp) __THROW;

/* Return the `struct tm' representation of *TIMER in local time,
   using *TP to store the result.  */
extern struct tm *localtime_r (const time_t *__restrict __timer,
			       struct tm *__restrict __tp) __THROW;
# endif	/* POSIX */
# 257 "/usr/include/time.h" 3 4

__BEGIN_NAMESPACE_STD
/* Return a string of the form "Day Mon dd hh:mm:ss yyyy\n"
   that is the representation of TP in this format.  */
extern char *asctime (const struct tm *__tp) __THROW;

/* Equivalent to `asctime (localtime (timer))'.  */
extern char *ctime (const time_t *__timer) __THROW;
__END_NAMESPACE_STD

# ifdef __USE_POSIX
/* Reentrant versions of the above functions.  */

/* Return in BUF a string of the form "Day Mon dd hh:mm:ss yyyy\n"
   that is the representation of TP in this format.  */
extern char *asctime_r (const struct tm *__restrict __tp,
			char *__restrict __buf) __THROW;

/* Equivalent to `asctime_r (localtime_r (timer, *TMP*), buf)'.  */
extern char *ctime_r (const time_t *__restrict __timer,
		      char *__restrict __buf) __THROW;
# endif	/* POSIX */
# 279 "/usr/include/time.h" 3 4


/* Defined in localtime.c.  */
extern char *__tzname[2];	/* Current timezone names.  */
extern int __daylight;		/* If daylight-saving time is ever in use.  */
extern long int __timezone;	/* Seconds west of UTC.  */


# ifdef	__USE_POSIX
/* Same as above.  */
extern char *tzname[2];

/* Set time conversion information from the TZ environment variable.
   If TZ is not defined, a locale-dependent default is used.  */
extern void tzset (void) __THROW;
# endif
# 295 "/usr/include/time.h" 3 4

# if defined __USE_MISC || defined __USE_XOPEN
extern int daylight;
extern long int timezone;
# endif
# 300 "/usr/include/time.h" 3 4

# ifdef __USE_MISC
/* Set the system time to *WHEN.
   This call is restricted to the superuser.  */
extern int stime (const time_t *__when) __THROW;
# endif
# 306 "/usr/include/time.h" 3 4


/* Nonzero if YEAR is a leap year (every 4 years,
   except every 100th isn't, and every 400th is).  */
# define __isleap(year)	\
  ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0))


# ifdef __USE_MISC
/* Miscellaneous functions many Unices inherited from the public domain
   localtime package.  These are included only for compatibility.  */

/* Like `mktime', but for TP represents Universal Time, not local time.  */
extern time_t timegm (struct tm *__tp) __THROW;

/* Another name for `mktime'.  */
extern time_t timelocal (struct tm *__tp) __THROW;

/* Return the number of days in YEAR.  */
extern int dysize (int __year) __THROW  __attribute__ ((__const__));
# endif
# 327 "/usr/include/time.h" 3 4


# ifdef __USE_POSIX199309
/* Pause execution for a number of nanoseconds.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern int nanosleep (const struct timespec *__requested_time,
		      struct timespec *__remaining);


/* Get resolution of clock CLOCK_ID.  */
extern int clock_getres (clockid_t __clock_id, struct timespec *__res) __THROW;

/* Get current value of clock CLOCK_ID and store it in TP.  */
extern int clock_gettime (clockid_t __clock_id, struct timespec *__tp) __THROW;

/* Set clock CLOCK_ID to value TP.  */
extern int clock_settime (clockid_t __clock_id, const struct timespec *__tp)
     __THROW;

#  ifdef __USE_XOPEN2K
/* High-resolution sleep with the specified clock.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern int clock_nanosleep (clockid_t __clock_id, int __flags,
			    const struct timespec *__req,
			    struct timespec *__rem);

/* Return clock ID for CPU-time clock.  */
extern int clock_getcpuclockid (pid_t __pid, clockid_t *__clock_id) __THROW;
#  endif
# 360 "/usr/include/time.h" 3 4


/* Create new per-process timer using CLOCK_ID.  */
extern int timer_create (clockid_t __clock_id,
			 struct sigevent *__restrict __evp,
			 timer_t *__restrict __timerid) __THROW;

/* Delete timer TIMERID.  */
extern int timer_delete (timer_t __timerid) __THROW;

/* Set timer TIMERID to VALUE, returning old value in OVALUE.  */
extern int timer_settime (timer_t __timerid, int __flags,
			  const struct itimerspec *__restrict __value,
			  struct itimerspec *__restrict __ovalue) __THROW;

/* Get current value of timer TIMERID and store it in VALUE.  */
extern int timer_gettime (timer_t __timerid, struct itimerspec *__value)
     __THROW;

/* Get expiration overrun for timer TIMERID.  */
extern int timer_getoverrun (timer_t __timerid) __THROW;
# endif
# 382 "/usr/include/time.h" 3 4


# ifdef __USE_ISOC11
/* Set TS to calendar time based in time base BASE.  */
extern int timespec_get (struct timespec *__ts, int __base)
     __THROW __nonnull ((1));
# endif
# 389 "/usr/include/time.h" 3 4


# ifdef __USE_XOPEN_EXTENDED
/* Set to one of the following values to indicate an error.
     1  the DATEMSK environment variable is null or undefined,
     2  the template file cannot be opened for reading,
     3  failed to get file status information,
     4  the template file is not a regular file,
     5  an error is encountered while reading the template file,
     6  memory allication failed (not enough memory available),
     7  there is no line in the template that matches the input,
     8  invalid input specification Example: February 31 or a time is
	specified that can not be represented in a time_t (representing
	the time in seconds since 00:00:00 UTC, January 1, 1970) */
extern int getdate_err;

/* Parse the given string as a date specification and return a value
   representing the value.  The templates from the file identified by
   the environment variable DATEMSK are used.  In case of an error
   `getdate_err' is set.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern struct tm *getdate (const char *__string);
# endif
# 414 "/usr/include/time.h" 3 4

# ifdef __USE_GNU
/* Since `getdate' is not reentrant because of the use of `getdate_err'
   and the static buffer to return the result in, we provide a thread-safe
   variant.  The functionality is the same.  The result is returned in
   the buffer pointed to by RESBUFP and in case of an error the return
   value is != 0 with the same values as given above for `getdate_err'.

   This function is not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation it is a cancellation point and
   therefore not marked with __THROW.  */
extern int getdate_r (const char *__restrict __string,
		      struct tm *__restrict __resbufp);
# endif
# 429 "/usr/include/time.h" 3 4

__END_DECLS

#endif /* <time.h> included.  */
# 433 "/usr/include/time.h" 3 4

#endif /* <time.h> not already included.  */
# 435 "/usr/include/time.h" 3 4
# 133 "/usr/include/x86_64-linux-gnu/sys/types.h" 2 3 4

#ifdef __USE_XOPEN
# ifndef __useconds_t_defined
typedef __useconds_t useconds_t;
#  define __useconds_t_defined
# endif
# 139 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
# ifndef __suseconds_t_defined
typedef __suseconds_t suseconds_t;
#  define __suseconds_t_defined
# endif
# 143 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
#endif
# 144 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4

#define	__need_size_t
#if 0 /* expanded by -frewrite-includes */
#include <stddef.h>
#endif /* expanded by -frewrite-includes */
# 146 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
# 1 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 1 3 4
/*===---- stddef.h - Basic type definitions --------------------------------===
 *
 * Copyright (c) 2008 Eli Friedman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *===-----------------------------------------------------------------------===
 */

#if !defined(__STDDEF_H) || defined(__need_ptrdiff_t) ||                       \
    defined(__need_size_t) || defined(__need_wchar_t) ||                       \
    defined(__need_NULL) || defined(__need_wint_t)

#if !defined(__need_ptrdiff_t) && !defined(__need_size_t) &&                   \
    !defined(__need_wchar_t) && !defined(__need_NULL) &&                       \
    !defined(__need_wint_t)
/* Always define miscellaneous pieces when modules are available. */
#if !__has_feature(modules)
#define __STDDEF_H
#endif
# 37 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#define __need_ptrdiff_t
#define __need_size_t
#define __need_wchar_t
#define __need_NULL
#define __need_STDDEF_H_misc
/* __need_wint_t is intentionally not defined here. */
#endif
# 44 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_ptrdiff_t)
#if !defined(_PTRDIFF_T) || __has_feature(modules)
/* Always define ptrdiff_t when modules are available. */
#if !__has_feature(modules)
#define _PTRDIFF_T
#endif
# 51 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif
# 53 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_ptrdiff_t
#endif /* defined(__need_ptrdiff_t) */
# 55 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_size_t)
#if !defined(_SIZE_T) || __has_feature(modules)
/* Always define size_t when modules are available. */
#if !__has_feature(modules)
#define _SIZE_T
#endif
# 62 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ size_t;
#endif
# 64 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_size_t
#endif /*defined(__need_size_t) */
# 66 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
/* ISO9899:2011 7.20 (C11 Annex K): Define rsize_t if __STDC_WANT_LIB_EXT1__ is
 * enabled. */
#if (defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ >= 1 && \
     !defined(_RSIZE_T)) || __has_feature(modules)
/* Always define rsize_t when modules are available. */
#if !__has_feature(modules)
#define _RSIZE_T
#endif
# 76 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ rsize_t;
#endif
# 78 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#endif /* defined(__need_STDDEF_H_misc) */
# 79 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_wchar_t)
#ifndef __cplusplus
/* Always define wchar_t when modules are available. */
#if !defined(_WCHAR_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WCHAR_T
#if defined(_MSC_EXTENSIONS)
#define _WCHAR_T_DEFINED
#endif
# 89 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 90 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WCHAR_TYPE__ wchar_t;
#endif
# 92 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 93 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wchar_t
#endif /* defined(__need_wchar_t) */
# 95 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_NULL)
#undef NULL
#ifdef __cplusplus
#  if !defined(__MINGW32__) && !defined(_MSC_VER)
#    define NULL __null
#  else
# 102 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#    define NULL 0
#  endif
# 104 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#else
# 105 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#  define NULL ((void*)0)
#endif
# 107 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#ifdef __cplusplus
#if defined(_MSC_EXTENSIONS) && defined(_NATIVE_NULLPTR_SUPPORTED)
namespace std { typedef decltype(nullptr) nullptr_t; }
using ::std::nullptr_t;
#endif
# 112 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 113 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_NULL
#endif /* defined(__need_NULL) */
# 115 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
#if __STDC_VERSION__ >= 201112L || __cplusplus >= 201103L
#if 0 /* expanded by -frewrite-includes */
#include "__stddef_max_align_t.h"
#endif /* expanded by -frewrite-includes */
# 118 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
# 119 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 120 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#define offsetof(t, d) __builtin_offsetof(t, d)
#undef __need_STDDEF_H_misc
#endif  /* defined(__need_STDDEF_H_misc) */
# 123 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

/* Some C libraries expect to see a wint_t here. Others (notably MinGW) will use
__WINT_TYPE__ directly; accommodate both by requiring __need_wint_t */
#if defined(__need_wint_t)
/* Always define wint_t when modules are available. */
#if !defined(_WINT_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WINT_T
#endif
# 132 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WINT_TYPE__ wint_t;
#endif
# 134 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wint_t
#endif /* __need_wint_t */
# 136 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#endif
# 138 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
# 147 "/usr/include/x86_64-linux-gnu/sys/types.h" 2 3 4

#ifdef __USE_MISC
/* Old compatibility names for C types.  */
typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
#endif
# 154 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4

/* These size-specific names are used by some of the inet code.  */

#if !__GNUC_PREREQ (2, 7)

/* These types are defined by the ISO C99 header <inttypes.h>. */
# ifndef __int8_t_defined
#  define __int8_t_defined
typedef	char int8_t;
typedef	short int int16_t;
typedef	int int32_t;
#  if __WORDSIZE == 64
typedef long int int64_t;
#  else
# 168 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
__extension__ typedef long long int int64_t;
#  endif
# 170 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
# endif
# 171 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4

/* But these were defined by ISO C without the first `_'.  */
typedef	unsigned char u_int8_t;
typedef	unsigned short int u_int16_t;
typedef	unsigned int u_int32_t;
# if __WORDSIZE == 64
typedef unsigned long int u_int64_t;
# else
# 179 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
__extension__ typedef unsigned long long int u_int64_t;
# endif
# 181 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4

typedef int register_t;

#else
# 185 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4

/* For GCC 2.7 and later, we can use specific type-size attributes.  */
# define __intN_t(N, MODE) \
  typedef int int##N##_t __attribute__ ((__mode__ (MODE)))
# define __u_intN_t(N, MODE) \
  typedef unsigned int u_int##N##_t __attribute__ ((__mode__ (MODE)))

# ifndef __int8_t_defined
#  define __int8_t_defined
__intN_t (8, __QI__);
__intN_t (16, __HI__);
__intN_t (32, __SI__);
__intN_t (64, __DI__);
# endif
# 199 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4

__u_intN_t (8, __QI__);
__u_intN_t (16, __HI__);
__u_intN_t (32, __SI__);
__u_intN_t (64, __DI__);

typedef int register_t __attribute__ ((__mode__ (__word__)));


/* Some code from BIND tests this macro to see if the types above are
   defined.  */
#endif
# 211 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
#define __BIT_TYPES_DEFINED__	1


#ifdef	__USE_MISC
/* In BSD <sys/types.h> is expected to define BYTE_ORDER.  */
#if 0 /* expanded by -frewrite-includes */
# include <endian.h>
#endif /* expanded by -frewrite-includes */
# 216 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
# 217 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4

/* It also defines `fd_set' and the FD_* macros for `select'.  */
#if 0 /* expanded by -frewrite-includes */
# include <sys/select.h>
#endif /* expanded by -frewrite-includes */
# 219 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/sys/select.h" 1 3 4
/* `fd_set' type and related macros, and `select'/`pselect' declarations.
   Copyright (C) 1996-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/*	POSIX 1003.1g: 6.2 Select from File Descriptor Sets <sys/select.h>  */

#ifndef _SYS_SELECT_H
#define _SYS_SELECT_H	1

#if 0 /* expanded by -frewrite-includes */
#include <features.h>
#endif /* expanded by -frewrite-includes */
# 24 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4
# 25 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4

/* Get definition of needed basic types.  */
#if 0 /* expanded by -frewrite-includes */
#include <bits/types.h>
#endif /* expanded by -frewrite-includes */
# 27 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4
# 28 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4

/* Get __FD_* definitions.  */
#if 0 /* expanded by -frewrite-includes */
#include <bits/select.h>
#endif /* expanded by -frewrite-includes */
# 30 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/select.h" 1 3 4
/* Copyright (C) 1997-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _SYS_SELECT_H
# error "Never use <bits/select.h> directly; include <sys/select.h> instead."
#endif
# 21 "/usr/include/x86_64-linux-gnu/bits/select.h" 3 4

#if 0 /* expanded by -frewrite-includes */
#include <bits/wordsize.h>
#endif /* expanded by -frewrite-includes */
# 22 "/usr/include/x86_64-linux-gnu/bits/select.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
/* Determine the wordsize from the preprocessor defines.  */

#if defined __x86_64__ && !defined __ILP32__
# define __WORDSIZE	64
#else
# 6 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 3 4
# define __WORDSIZE	32
#endif
# 8 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 3 4

#ifdef __x86_64__
# define __WORDSIZE_TIME64_COMPAT32	1
/* Both x86-64 and x32 use the 64-bit system call interface.  */
# define __SYSCALL_WORDSIZE		64
#endif
# 14 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 3 4
# 23 "/usr/include/x86_64-linux-gnu/bits/select.h" 2 3 4


#if defined __GNUC__ && __GNUC__ >= 2

# if __WORDSIZE == 64
#  define __FD_ZERO_STOS "stosq"
# else
# 30 "/usr/include/x86_64-linux-gnu/bits/select.h" 3 4
#  define __FD_ZERO_STOS "stosl"
# endif
# 32 "/usr/include/x86_64-linux-gnu/bits/select.h" 3 4

# define __FD_ZERO(fdsp) \
  do {									      \
    int __d0, __d1;							      \
    __asm__ __volatile__ ("cld; rep; " __FD_ZERO_STOS			      \
			  : "=c" (__d0), "=D" (__d1)			      \
			  : "a" (0), "0" (sizeof (fd_set)		      \
					  / sizeof (__fd_mask)),	      \
			    "1" (&__FDS_BITS (fdsp)[0])			      \
			  : "memory");					      \
  } while (0)

#else	/* ! GNU CC */
# 45 "/usr/include/x86_64-linux-gnu/bits/select.h" 3 4

/* We don't use `memset' because this would require a prototype and
   the array isn't too big.  */
# define __FD_ZERO(set)  \
  do {									      \
    unsigned int __i;							      \
    fd_set *__arr = (set);						      \
    for (__i = 0; __i < sizeof (fd_set) / sizeof (__fd_mask); ++__i)	      \
      __FDS_BITS (__arr)[__i] = 0;					      \
  } while (0)

#endif	/* GNU CC */
# 57 "/usr/include/x86_64-linux-gnu/bits/select.h" 3 4

#define __FD_SET(d, set) \
  ((void) (__FDS_BITS (set)[__FD_ELT (d)] |= __FD_MASK (d)))
#define __FD_CLR(d, set) \
  ((void) (__FDS_BITS (set)[__FD_ELT (d)] &= ~__FD_MASK (d)))
#define __FD_ISSET(d, set) \
  ((__FDS_BITS (set)[__FD_ELT (d)] & __FD_MASK (d)) != 0)
# 31 "/usr/include/x86_64-linux-gnu/sys/select.h" 2 3 4

/* Get __sigset_t.  */
#if 0 /* expanded by -frewrite-includes */
#include <bits/sigset.h>
#endif /* expanded by -frewrite-includes */
# 33 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/sigset.h" 1 3 4
/* __sig_atomic_t, __sigset_t, and related definitions.  Linux version.
   Copyright (C) 1991-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef	_SIGSET_H_types
# define _SIGSET_H_types	1

typedef int __sig_atomic_t;

/* A `sigset_t' has a bit for each signal.  */

# define _SIGSET_NWORDS	(1024 / (8 * sizeof (unsigned long int)))
typedef struct
  {
    unsigned long int __val[_SIGSET_NWORDS];
  } __sigset_t;

#endif
# 33 "/usr/include/x86_64-linux-gnu/bits/sigset.h" 3 4


/* We only want to define these functions if <signal.h> was actually
   included; otherwise we were included just to define the types.  Since we
   are namespace-clean, it wouldn't hurt to define extra macros.  But
   trouble can be caused by functions being defined (e.g., any global
   register vars declared later will cause compilation errors).  */

#if !defined _SIGSET_H_fns && defined _SIGNAL_H
# define _SIGSET_H_fns 1

# ifndef _EXTERN_INLINE
#  define _EXTERN_INLINE __extern_inline
# endif
# 47 "/usr/include/x86_64-linux-gnu/bits/sigset.h" 3 4

/* Return a mask that includes the bit for SIG only.  */
# define __sigmask(sig) \
  (((unsigned long int) 1) << (((sig) - 1) % (8 * sizeof (unsigned long int))))

/* Return the word index for SIG.  */
# define __sigword(sig)	(((sig) - 1) / (8 * sizeof (unsigned long int)))

# if defined __GNUC__ && __GNUC__ >= 2
#  define __sigemptyset(set) \
  (__extension__ ({ int __cnt = _SIGSET_NWORDS;				      \
		    sigset_t *__set = (set);				      \
		    while (--__cnt >= 0) __set->__val[__cnt] = 0;	      \
		    0; }))
#  define __sigfillset(set) \
  (__extension__ ({ int __cnt = _SIGSET_NWORDS;				      \
		    sigset_t *__set = (set);				      \
		    while (--__cnt >= 0) __set->__val[__cnt] = ~0UL;	      \
		    0; }))

#  ifdef __USE_GNU
/* The POSIX does not specify for handling the whole signal set in one
   command.  This is often wanted and so we define three more functions
   here.  */
#   define __sigisemptyset(set) \
  (__extension__ ({ int __cnt = _SIGSET_NWORDS;				      \
		    const sigset_t *__set = (set);			      \
		    int __ret = __set->__val[--__cnt];			      \
		    while (!__ret && --__cnt >= 0)			      \
			__ret = __set->__val[__cnt];			      \
		    __ret == 0; }))
#   define __sigandset(dest, left, right) \
  (__extension__ ({ int __cnt = _SIGSET_NWORDS;				      \
		    sigset_t *__dest = (dest);				      \
		    const sigset_t *__left = (left);			      \
		    const sigset_t *__right = (right);			      \
		    while (--__cnt >= 0)				      \
		      __dest->__val[__cnt] = (__left->__val[__cnt]	      \
					      & __right->__val[__cnt]);	      \
		    0; }))
#   define __sigorset(dest, left, right) \
  (__extension__ ({ int __cnt = _SIGSET_NWORDS;				      \
		    sigset_t *__dest = (dest);				      \
		    const sigset_t *__left = (left);			      \
		    const sigset_t *__right = (right);			      \
		    while (--__cnt >= 0)				      \
		      __dest->__val[__cnt] = (__left->__val[__cnt]	      \
					      | __right->__val[__cnt]);	      \
		    0; }))
#  endif
# 97 "/usr/include/x86_64-linux-gnu/bits/sigset.h" 3 4
# endif
# 98 "/usr/include/x86_64-linux-gnu/bits/sigset.h" 3 4

/* These functions needn't check for a bogus signal number -- error
   checking is done in the non __ versions.  */

extern int __sigismember (const __sigset_t *, int);
extern int __sigaddset (__sigset_t *, int);
extern int __sigdelset (__sigset_t *, int);

# ifdef __USE_EXTERN_INLINES
#  define __SIGSETFN(NAME, BODY, CONST)					      \
  _EXTERN_INLINE int							      \
  NAME (CONST __sigset_t *__set, int __sig)				      \
  {									      \
    unsigned long int __mask = __sigmask (__sig);			      \
    unsigned long int __word = __sigword (__sig);			      \
    return BODY;							      \
  }

__SIGSETFN (__sigismember, (__set->__val[__word] & __mask) ? 1 : 0, const)
__SIGSETFN (__sigaddset, ((__set->__val[__word] |= __mask), 0), )
__SIGSETFN (__sigdelset, ((__set->__val[__word] &= ~__mask), 0), )

#  undef __SIGSETFN
# endif
# 122 "/usr/include/x86_64-linux-gnu/bits/sigset.h" 3 4


#endif /* ! _SIGSET_H_fns.  */
# 125 "/usr/include/x86_64-linux-gnu/bits/sigset.h" 3 4
# 34 "/usr/include/x86_64-linux-gnu/sys/select.h" 2 3 4

#ifndef __sigset_t_defined
# define __sigset_t_defined
typedef __sigset_t sigset_t;
#endif
# 39 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4

/* Get definition of timer specification structures.  */
#define __need_time_t
#define __need_timespec
#if 0 /* expanded by -frewrite-includes */
#include <time.h>
#endif /* expanded by -frewrite-includes */
# 43 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4
# 1 "/usr/include/time.h" 1 3 4
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/*
 *	ISO C99 Standard: 7.23 Date and time	<time.h>
 */

#ifndef	_TIME_H

#if (! defined __need_time_t && !defined __need_clock_t && \
     ! defined __need_timespec)
# define _TIME_H	1
#if 0 /* expanded by -frewrite-includes */
# include <features.h>
#endif /* expanded by -frewrite-includes */
# 27 "/usr/include/time.h" 3 4
# 28 "/usr/include/time.h" 3 4

__BEGIN_DECLS

#endif
# 32 "/usr/include/time.h" 3 4

#ifdef	_TIME_H
/* Get size_t and NULL from <stddef.h>.  */
# define __need_size_t
# define __need_NULL
#if 0 /* expanded by -frewrite-includes */
# include <stddef.h>
#endif /* expanded by -frewrite-includes */
# 37 "/usr/include/time.h" 3 4
# 38 "/usr/include/time.h" 3 4

/* This defines CLOCKS_PER_SEC, which is the number of processor clock
   ticks per second.  */
#if 0 /* expanded by -frewrite-includes */
# include <bits/time.h>
#endif /* expanded by -frewrite-includes */
# 41 "/usr/include/time.h" 3 4
# 42 "/usr/include/time.h" 3 4

/* This is the obsolete POSIX.1-1988 name for the same constant.  */
# if !defined __STRICT_ANSI__ && !defined __USE_XOPEN2K
#  ifndef CLK_TCK
#   define CLK_TCK	CLOCKS_PER_SEC
#  endif
# 48 "/usr/include/time.h" 3 4
# endif
# 49 "/usr/include/time.h" 3 4

#endif /* <time.h> included.  */
# 51 "/usr/include/time.h" 3 4

#if !defined __clock_t_defined && (defined _TIME_H || defined __need_clock_t)
# define __clock_t_defined	1

#if 0 /* expanded by -frewrite-includes */
# include <bits/types.h>
#endif /* expanded by -frewrite-includes */
# 55 "/usr/include/time.h" 3 4
# 56 "/usr/include/time.h" 3 4

__BEGIN_NAMESPACE_STD
/* Returned by `clock'.  */
typedef __clock_t clock_t;
__END_NAMESPACE_STD
#if defined __USE_XOPEN || defined __USE_POSIX
__USING_NAMESPACE_STD(clock_t)
#endif
# 64 "/usr/include/time.h" 3 4

#endif /* clock_t not defined and <time.h> or need clock_t.  */
# 66 "/usr/include/time.h" 3 4
#undef	__need_clock_t

#if !defined __time_t_defined && (defined _TIME_H || defined __need_time_t)
# define __time_t_defined	1

#if 0 /* expanded by -frewrite-includes */
# include <bits/types.h>
#endif /* expanded by -frewrite-includes */
# 71 "/usr/include/time.h" 3 4
# 72 "/usr/include/time.h" 3 4

__BEGIN_NAMESPACE_STD
/* Returned by `time'.  */
typedef __time_t time_t;
__END_NAMESPACE_STD
#ifdef __USE_POSIX
__USING_NAMESPACE_STD(time_t)
#endif
# 80 "/usr/include/time.h" 3 4

#endif /* time_t not defined and <time.h> or need time_t.  */
# 82 "/usr/include/time.h" 3 4
#undef	__need_time_t

#if !defined __clockid_t_defined && \
   ((defined _TIME_H && defined __USE_POSIX199309) || defined __need_clockid_t)
# define __clockid_t_defined	1

#if 0 /* expanded by -frewrite-includes */
# include <bits/types.h>
#endif /* expanded by -frewrite-includes */
# 88 "/usr/include/time.h" 3 4
# 89 "/usr/include/time.h" 3 4

/* Clock ID used in clock and timer functions.  */
typedef __clockid_t clockid_t;

#endif /* clockid_t not defined and <time.h> or need clockid_t.  */
# 94 "/usr/include/time.h" 3 4
#undef	__clockid_time_t

#if !defined __timer_t_defined && \
    ((defined _TIME_H && defined __USE_POSIX199309) || defined __need_timer_t)
# define __timer_t_defined	1

#if 0 /* expanded by -frewrite-includes */
# include <bits/types.h>
#endif /* expanded by -frewrite-includes */
# 100 "/usr/include/time.h" 3 4
# 101 "/usr/include/time.h" 3 4

/* Timer ID returned by `timer_create'.  */
typedef __timer_t timer_t;

#endif /* timer_t not defined and <time.h> or need timer_t.  */
# 106 "/usr/include/time.h" 3 4
#undef	__need_timer_t


#if (!defined __timespec_defined					\
     && ((defined _TIME_H						\
	  && (defined __USE_POSIX199309					\
	      || defined __USE_ISOC11))					\
	 || defined __need_timespec))
# define __timespec_defined	1

#if 0 /* expanded by -frewrite-includes */
# include <bits/types.h>	/* This defines __time_t for us.  */
#endif /* expanded by -frewrite-includes */
# 116 "/usr/include/time.h" 3 4
# 117 "/usr/include/time.h" 3 4

/* POSIX.1b structure for a time value.  This is like a `struct timeval' but
   has nanoseconds instead of microseconds.  */
struct timespec
  {
    __time_t tv_sec;		/* Seconds.  */
    __syscall_slong_t tv_nsec;	/* Nanoseconds.  */
  };

#endif /* timespec not defined and <time.h> or need timespec.  */
# 127 "/usr/include/time.h" 3 4
#undef	__need_timespec


#ifdef	_TIME_H
__BEGIN_NAMESPACE_STD
/* Used by other time functions.  */
struct tm
{
  int tm_sec;			/* Seconds.	[0-60] (1 leap second) */
  int tm_min;			/* Minutes.	[0-59] */
  int tm_hour;			/* Hours.	[0-23] */
  int tm_mday;			/* Day.		[1-31] */
  int tm_mon;			/* Month.	[0-11] */
  int tm_year;			/* Year	- 1900.  */
  int tm_wday;			/* Day of week.	[0-6] */
  int tm_yday;			/* Days in year.[0-365]	*/
  int tm_isdst;			/* DST.		[-1/0/1]*/

# ifdef	__USE_MISC
  long int tm_gmtoff;		/* Seconds east of UTC.  */
  const char *tm_zone;		/* Timezone abbreviation.  */
# else
# 149 "/usr/include/time.h" 3 4
  long int __tm_gmtoff;		/* Seconds east of UTC.  */
  const char *__tm_zone;	/* Timezone abbreviation.  */
# endif
# 152 "/usr/include/time.h" 3 4
};
__END_NAMESPACE_STD
#if defined __USE_XOPEN || defined __USE_POSIX
__USING_NAMESPACE_STD(tm)
#endif
# 157 "/usr/include/time.h" 3 4


# ifdef __USE_POSIX199309
/* POSIX.1b structure for timer start values and intervals.  */
struct itimerspec
  {
    struct timespec it_interval;
    struct timespec it_value;
  };

/* We can use a simple forward declaration.  */
struct sigevent;

# endif	/* POSIX.1b */
# 171 "/usr/include/time.h" 3 4

# ifdef __USE_XOPEN2K
#  ifndef __pid_t_defined
typedef __pid_t pid_t;
#   define __pid_t_defined
#  endif
# 177 "/usr/include/time.h" 3 4
# endif
# 178 "/usr/include/time.h" 3 4


# ifdef __USE_ISOC11
/* Time base values for timespec_get.  */
# define TIME_UTC 1
# endif
# 184 "/usr/include/time.h" 3 4


__BEGIN_NAMESPACE_STD
/* Time used by the program so far (user time + system time).
   The result / CLOCKS_PER_SECOND is program time in seconds.  */
extern clock_t clock (void) __THROW;

/* Return the current time and put it in *TIMER if TIMER is not NULL.  */
extern time_t time (time_t *__timer) __THROW;

/* Return the difference between TIME1 and TIME0.  */
extern double difftime (time_t __time1, time_t __time0)
     __THROW __attribute__ ((__const__));

/* Return the `time_t' representation of TP and normalize TP.  */
extern time_t mktime (struct tm *__tp) __THROW;


/* Format TP into S according to FORMAT.
   Write no more than MAXSIZE characters and return the number
   of characters written, or 0 if it would exceed MAXSIZE.  */
extern size_t strftime (char *__restrict __s, size_t __maxsize,
			const char *__restrict __format,
			const struct tm *__restrict __tp) __THROW;
__END_NAMESPACE_STD

# ifdef __USE_XOPEN
/* Parse S according to FORMAT and store binary time information in TP.
   The return value is a pointer to the first unparsed character in S.  */
extern char *strptime (const char *__restrict __s,
		       const char *__restrict __fmt, struct tm *__tp)
     __THROW;
# endif
# 217 "/usr/include/time.h" 3 4

# ifdef __USE_XOPEN2K8
/* Similar to the two functions above but take the information from
   the provided locale and not the global locale.  */
#if 0 /* expanded by -frewrite-includes */
# include <xlocale.h>
#endif /* expanded by -frewrite-includes */
# 221 "/usr/include/time.h" 3 4
# 222 "/usr/include/time.h" 3 4

extern size_t strftime_l (char *__restrict __s, size_t __maxsize,
			  const char *__restrict __format,
			  const struct tm *__restrict __tp,
			  __locale_t __loc) __THROW;
# endif
# 228 "/usr/include/time.h" 3 4

# ifdef __USE_GNU
extern char *strptime_l (const char *__restrict __s,
			 const char *__restrict __fmt, struct tm *__tp,
			 __locale_t __loc) __THROW;
# endif
# 234 "/usr/include/time.h" 3 4


__BEGIN_NAMESPACE_STD
/* Return the `struct tm' representation of *TIMER
   in Universal Coordinated Time (aka Greenwich Mean Time).  */
extern struct tm *gmtime (const time_t *__timer) __THROW;

/* Return the `struct tm' representation
   of *TIMER in the local timezone.  */
extern struct tm *localtime (const time_t *__timer) __THROW;
__END_NAMESPACE_STD

# ifdef __USE_POSIX
/* Return the `struct tm' representation of *TIMER in UTC,
   using *TP to store the result.  */
extern struct tm *gmtime_r (const time_t *__restrict __timer,
			    struct tm *__restrict __tp) __THROW;

/* Return the `struct tm' representation of *TIMER in local time,
   using *TP to store the result.  */
extern struct tm *localtime_r (const time_t *__restrict __timer,
			       struct tm *__restrict __tp) __THROW;
# endif	/* POSIX */
# 257 "/usr/include/time.h" 3 4

__BEGIN_NAMESPACE_STD
/* Return a string of the form "Day Mon dd hh:mm:ss yyyy\n"
   that is the representation of TP in this format.  */
extern char *asctime (const struct tm *__tp) __THROW;

/* Equivalent to `asctime (localtime (timer))'.  */
extern char *ctime (const time_t *__timer) __THROW;
__END_NAMESPACE_STD

# ifdef __USE_POSIX
/* Reentrant versions of the above functions.  */

/* Return in BUF a string of the form "Day Mon dd hh:mm:ss yyyy\n"
   that is the representation of TP in this format.  */
extern char *asctime_r (const struct tm *__restrict __tp,
			char *__restrict __buf) __THROW;

/* Equivalent to `asctime_r (localtime_r (timer, *TMP*), buf)'.  */
extern char *ctime_r (const time_t *__restrict __timer,
		      char *__restrict __buf) __THROW;
# endif	/* POSIX */
# 279 "/usr/include/time.h" 3 4


/* Defined in localtime.c.  */
extern char *__tzname[2];	/* Current timezone names.  */
extern int __daylight;		/* If daylight-saving time is ever in use.  */
extern long int __timezone;	/* Seconds west of UTC.  */


# ifdef	__USE_POSIX
/* Same as above.  */
extern char *tzname[2];

/* Set time conversion information from the TZ environment variable.
   If TZ is not defined, a locale-dependent default is used.  */
extern void tzset (void) __THROW;
# endif
# 295 "/usr/include/time.h" 3 4

# if defined __USE_MISC || defined __USE_XOPEN
extern int daylight;
extern long int timezone;
# endif
# 300 "/usr/include/time.h" 3 4

# ifdef __USE_MISC
/* Set the system time to *WHEN.
   This call is restricted to the superuser.  */
extern int stime (const time_t *__when) __THROW;
# endif
# 306 "/usr/include/time.h" 3 4


/* Nonzero if YEAR is a leap year (every 4 years,
   except every 100th isn't, and every 400th is).  */
# define __isleap(year)	\
  ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0))


# ifdef __USE_MISC
/* Miscellaneous functions many Unices inherited from the public domain
   localtime package.  These are included only for compatibility.  */

/* Like `mktime', but for TP represents Universal Time, not local time.  */
extern time_t timegm (struct tm *__tp) __THROW;

/* Another name for `mktime'.  */
extern time_t timelocal (struct tm *__tp) __THROW;

/* Return the number of days in YEAR.  */
extern int dysize (int __year) __THROW  __attribute__ ((__const__));
# endif
# 327 "/usr/include/time.h" 3 4


# ifdef __USE_POSIX199309
/* Pause execution for a number of nanoseconds.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern int nanosleep (const struct timespec *__requested_time,
		      struct timespec *__remaining);


/* Get resolution of clock CLOCK_ID.  */
extern int clock_getres (clockid_t __clock_id, struct timespec *__res) __THROW;

/* Get current value of clock CLOCK_ID and store it in TP.  */
extern int clock_gettime (clockid_t __clock_id, struct timespec *__tp) __THROW;

/* Set clock CLOCK_ID to value TP.  */
extern int clock_settime (clockid_t __clock_id, const struct timespec *__tp)
     __THROW;

#  ifdef __USE_XOPEN2K
/* High-resolution sleep with the specified clock.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern int clock_nanosleep (clockid_t __clock_id, int __flags,
			    const struct timespec *__req,
			    struct timespec *__rem);

/* Return clock ID for CPU-time clock.  */
extern int clock_getcpuclockid (pid_t __pid, clockid_t *__clock_id) __THROW;
#  endif
# 360 "/usr/include/time.h" 3 4


/* Create new per-process timer using CLOCK_ID.  */
extern int timer_create (clockid_t __clock_id,
			 struct sigevent *__restrict __evp,
			 timer_t *__restrict __timerid) __THROW;

/* Delete timer TIMERID.  */
extern int timer_delete (timer_t __timerid) __THROW;

/* Set timer TIMERID to VALUE, returning old value in OVALUE.  */
extern int timer_settime (timer_t __timerid, int __flags,
			  const struct itimerspec *__restrict __value,
			  struct itimerspec *__restrict __ovalue) __THROW;

/* Get current value of timer TIMERID and store it in VALUE.  */
extern int timer_gettime (timer_t __timerid, struct itimerspec *__value)
     __THROW;

/* Get expiration overrun for timer TIMERID.  */
extern int timer_getoverrun (timer_t __timerid) __THROW;
# endif
# 382 "/usr/include/time.h" 3 4


# ifdef __USE_ISOC11
/* Set TS to calendar time based in time base BASE.  */
extern int timespec_get (struct timespec *__ts, int __base)
     __THROW __nonnull ((1));
# endif
# 389 "/usr/include/time.h" 3 4


# ifdef __USE_XOPEN_EXTENDED
/* Set to one of the following values to indicate an error.
     1  the DATEMSK environment variable is null or undefined,
     2  the template file cannot be opened for reading,
     3  failed to get file status information,
     4  the template file is not a regular file,
     5  an error is encountered while reading the template file,
     6  memory allication failed (not enough memory available),
     7  there is no line in the template that matches the input,
     8  invalid input specification Example: February 31 or a time is
	specified that can not be represented in a time_t (representing
	the time in seconds since 00:00:00 UTC, January 1, 1970) */
extern int getdate_err;

/* Parse the given string as a date specification and return a value
   representing the value.  The templates from the file identified by
   the environment variable DATEMSK are used.  In case of an error
   `getdate_err' is set.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern struct tm *getdate (const char *__string);
# endif
# 414 "/usr/include/time.h" 3 4

# ifdef __USE_GNU
/* Since `getdate' is not reentrant because of the use of `getdate_err'
   and the static buffer to return the result in, we provide a thread-safe
   variant.  The functionality is the same.  The result is returned in
   the buffer pointed to by RESBUFP and in case of an error the return
   value is != 0 with the same values as given above for `getdate_err'.

   This function is not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation it is a cancellation point and
   therefore not marked with __THROW.  */
extern int getdate_r (const char *__restrict __string,
		      struct tm *__restrict __resbufp);
# endif
# 429 "/usr/include/time.h" 3 4

__END_DECLS

#endif /* <time.h> included.  */
# 433 "/usr/include/time.h" 3 4

#endif /* <time.h> not already included.  */
# 435 "/usr/include/time.h" 3 4
# 44 "/usr/include/x86_64-linux-gnu/sys/select.h" 2 3 4
#define __need_timeval
#if 0 /* expanded by -frewrite-includes */
#include <bits/time.h>
#endif /* expanded by -frewrite-includes */
# 45 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/time.h" 1 3 4
/* System-dependent timing definitions.  Linux version.
   Copyright (C) 1996-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/*
 * Never include this file directly; use <time.h> instead.
 */

#if defined __need_timeval || defined __USE_GNU
# ifndef _STRUCT_TIMEVAL
#  define _STRUCT_TIMEVAL	1
#if 0 /* expanded by -frewrite-includes */
#  include <bits/types.h>
#endif /* expanded by -frewrite-includes */
# 26 "/usr/include/x86_64-linux-gnu/bits/time.h" 3 4
# 27 "/usr/include/x86_64-linux-gnu/bits/time.h" 3 4

/* A time value that is accurate to the nearest
   microsecond but also has a range of years.  */
struct timeval
  {
    __time_t tv_sec;		/* Seconds.  */
    __suseconds_t tv_usec;	/* Microseconds.  */
  };
# endif	/* struct timeval */
# 36 "/usr/include/x86_64-linux-gnu/bits/time.h" 3 4
#endif
# 37 "/usr/include/x86_64-linux-gnu/bits/time.h" 3 4

#ifndef __need_timeval
# ifndef _BITS_TIME_H
#  define _BITS_TIME_H	1

/* ISO/IEC 9899:1999 7.23.1: Components of time
   The macro `CLOCKS_PER_SEC' is an expression with type `clock_t' that is
   the number per second of the value returned by the `clock' function.  */
/* CAE XSH, Issue 4, Version 2: <time.h>
   The value of CLOCKS_PER_SEC is required to be 1 million on all
   XSI-conformant systems. */
#  define CLOCKS_PER_SEC  ((clock_t) 1000000)

#  if (!defined __STRICT_ANSI__ || defined __USE_POSIX) \
   && !defined __USE_XOPEN2K
/* Even though CLOCKS_PER_SEC has such a strange value CLK_TCK
   presents the real value for clock ticks per second for the system.  */
#if 0 /* expanded by -frewrite-includes */
#   include <bits/types.h>
#endif /* expanded by -frewrite-includes */
# 54 "/usr/include/x86_64-linux-gnu/bits/time.h" 3 4
# 55 "/usr/include/x86_64-linux-gnu/bits/time.h" 3 4
extern long int __sysconf (int);
#   define CLK_TCK ((__clock_t) __sysconf (2))	/* 2 is _SC_CLK_TCK */
#  endif
# 58 "/usr/include/x86_64-linux-gnu/bits/time.h" 3 4

#  ifdef __USE_POSIX199309
/* Identifier for system-wide realtime clock.  */
#   define CLOCK_REALTIME		0
/* Monotonic system-wide clock.  */
#   define CLOCK_MONOTONIC		1
/* High-resolution timer from the CPU.  */
#   define CLOCK_PROCESS_CPUTIME_ID	2
/* Thread-specific CPU-time clock.  */
#   define CLOCK_THREAD_CPUTIME_ID	3
/* Monotonic system-wide clock, not adjusted for frequency scaling.  */
#   define CLOCK_MONOTONIC_RAW		4
/* Identifier for system-wide realtime clock, updated only on ticks.  */
#   define CLOCK_REALTIME_COARSE	5
/* Monotonic system-wide clock, updated only on ticks.  */
#   define CLOCK_MONOTONIC_COARSE	6
/* Monotonic system-wide clock that includes time spent in suspension.  */
#   define CLOCK_BOOTTIME		7
/* Like CLOCK_REALTIME but also wakes suspended system.  */
#   define CLOCK_REALTIME_ALARM		8
/* Like CLOCK_BOOTTIME but also wakes suspended system.  */
#   define CLOCK_BOOTTIME_ALARM		9
/* Like CLOCK_REALTIME but in International Atomic Time.  */
#   define CLOCK_TAI			11

/* Flag to indicate time is absolute.  */
#   define TIMER_ABSTIME		1
#  endif
# 86 "/usr/include/x86_64-linux-gnu/bits/time.h" 3 4

#  ifdef __USE_GNU
#if 0 /* expanded by -frewrite-includes */
#   include <bits/timex.h>
#endif /* expanded by -frewrite-includes */
# 88 "/usr/include/x86_64-linux-gnu/bits/time.h" 3 4
# 89 "/usr/include/x86_64-linux-gnu/bits/time.h" 3 4

__BEGIN_DECLS

/* Tune a POSIX clock.  */
extern int clock_adjtime (__clockid_t __clock_id, struct timex *__utx) __THROW;

__END_DECLS
#  endif /* use GNU */
# 97 "/usr/include/x86_64-linux-gnu/bits/time.h" 3 4

# endif	/* bits/time.h */
# 99 "/usr/include/x86_64-linux-gnu/bits/time.h" 3 4
#endif
# 100 "/usr/include/x86_64-linux-gnu/bits/time.h" 3 4

#undef __need_timeval
# 46 "/usr/include/x86_64-linux-gnu/sys/select.h" 2 3 4

#ifndef __suseconds_t_defined
typedef __suseconds_t suseconds_t;
# define __suseconds_t_defined
#endif
# 51 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4


/* The fd_set member is required to be an array of longs.  */
typedef long int __fd_mask;

/* Some versions of <linux/posix_types.h> define this macros.  */
#undef	__NFDBITS
/* It's easier to assume 8-bit bytes than to get CHAR_BIT.  */
#define __NFDBITS	(8 * (int) sizeof (__fd_mask))
#define	__FD_ELT(d)	((d) / __NFDBITS)
#define	__FD_MASK(d)	((__fd_mask) (1UL << ((d) % __NFDBITS)))

/* fd_set for select and pselect.  */
typedef struct
  {
    /* XPG4.2 requires this member name.  Otherwise avoid the name
       from the global namespace.  */
#ifdef __USE_XOPEN
    __fd_mask fds_bits[__FD_SETSIZE / __NFDBITS];
# define __FDS_BITS(set) ((set)->fds_bits)
#else
# 72 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4
    __fd_mask __fds_bits[__FD_SETSIZE / __NFDBITS];
# define __FDS_BITS(set) ((set)->__fds_bits)
#endif
# 75 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4
  } fd_set;

/* Maximum number of file descriptors in `fd_set'.  */
#define	FD_SETSIZE		__FD_SETSIZE

#ifdef __USE_MISC
/* Sometimes the fd_set member is assumed to have this type.  */
typedef __fd_mask fd_mask;

/* Number of bits per word of `fd_set' (some code assumes this is 32).  */
# define NFDBITS		__NFDBITS
#endif
# 87 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4


/* Access macros for `fd_set'.  */
#define	FD_SET(fd, fdsetp)	__FD_SET (fd, fdsetp)
#define	FD_CLR(fd, fdsetp)	__FD_CLR (fd, fdsetp)
#define	FD_ISSET(fd, fdsetp)	__FD_ISSET (fd, fdsetp)
#define	FD_ZERO(fdsetp)		__FD_ZERO (fdsetp)


__BEGIN_DECLS

/* Check the first NFDS descriptors each in READFDS (if not NULL) for read
   readiness, in WRITEFDS (if not NULL) for write readiness, and in EXCEPTFDS
   (if not NULL) for exceptional conditions.  If TIMEOUT is not NULL, time out
   after waiting the interval specified therein.  Returns the number of ready
   descriptors, or -1 for errors.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern int select (int __nfds, fd_set *__restrict __readfds,
		   fd_set *__restrict __writefds,
		   fd_set *__restrict __exceptfds,
		   struct timeval *__restrict __timeout);

#ifdef __USE_XOPEN2K
/* Same as above only that the TIMEOUT value is given with higher
   resolution and a sigmask which is been set temporarily.  This version
   should be used.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern int pselect (int __nfds, fd_set *__restrict __readfds,
		    fd_set *__restrict __writefds,
		    fd_set *__restrict __exceptfds,
		    const struct timespec *__restrict __timeout,
		    const __sigset_t *__restrict __sigmask);
#endif
# 124 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4


/* Define some inlines helping to catch common problems.  */
#if __USE_FORTIFY_LEVEL > 0 && defined __GNUC__
#if 0 /* expanded by -frewrite-includes */
# include <bits/select2.h>
#endif /* expanded by -frewrite-includes */
# 128 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4
# 129 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4
#endif
# 130 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4

__END_DECLS

#endif /* sys/select.h */
# 134 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4
# 220 "/usr/include/x86_64-linux-gnu/sys/types.h" 2 3 4

/* BSD defines these symbols, so we follow.  */
#if 0 /* expanded by -frewrite-includes */
# include <sys/sysmacros.h>
#endif /* expanded by -frewrite-includes */
# 222 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/sys/sysmacros.h" 1 3 4
/* Definitions of macros to access `dev_t' values.
   Copyright (C) 1996-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _SYS_SYSMACROS_H
#define _SYS_SYSMACROS_H	1

#if 0 /* expanded by -frewrite-includes */
#include <features.h>
#endif /* expanded by -frewrite-includes */
# 22 "/usr/include/x86_64-linux-gnu/sys/sysmacros.h" 3 4
# 23 "/usr/include/x86_64-linux-gnu/sys/sysmacros.h" 3 4

__BEGIN_DECLS

__extension__
extern unsigned int gnu_dev_major (unsigned long long int __dev)
     __THROW __attribute_const__;
__extension__
extern unsigned int gnu_dev_minor (unsigned long long int __dev)
     __THROW __attribute_const__;
__extension__
extern unsigned long long int gnu_dev_makedev (unsigned int __major,
					       unsigned int __minor)
     __THROW __attribute_const__;

#ifdef __USE_EXTERN_INLINES
__extension__ __extern_inline __attribute_const__ unsigned int
__NTH (gnu_dev_major (unsigned long long int __dev))
{
  return ((__dev >> 8) & 0xfff) | ((unsigned int) (__dev >> 32) & ~0xfff);
}

__extension__ __extern_inline __attribute_const__ unsigned int
__NTH (gnu_dev_minor (unsigned long long int __dev))
{
  return (__dev & 0xff) | ((unsigned int) (__dev >> 12) & ~0xff);
}

__extension__ __extern_inline __attribute_const__ unsigned long long int
__NTH (gnu_dev_makedev (unsigned int __major, unsigned int __minor))
{
  return ((__minor & 0xff) | ((__major & 0xfff) << 8)
	  | (((unsigned long long int) (__minor & ~0xff)) << 12)
	  | (((unsigned long long int) (__major & ~0xfff)) << 32));
}
#endif
# 58 "/usr/include/x86_64-linux-gnu/sys/sysmacros.h" 3 4
__END_DECLS

/* Access the functions with their traditional names.  */
#define major(dev) gnu_dev_major (dev)
#define minor(dev) gnu_dev_minor (dev)
#define makedev(maj, min) gnu_dev_makedev (maj, min)

#endif /* sys/sysmacros.h */
# 66 "/usr/include/x86_64-linux-gnu/sys/sysmacros.h" 3 4
# 223 "/usr/include/x86_64-linux-gnu/sys/types.h" 2 3 4
#endif /* Use misc.  */
# 224 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4


#if (defined __USE_UNIX98 || defined __USE_XOPEN2K8) \
    && !defined __blksize_t_defined
typedef __blksize_t blksize_t;
# define __blksize_t_defined
#endif
# 231 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4

/* Types from the Large File Support interface.  */
#ifndef __USE_FILE_OFFSET64
# ifndef __blkcnt_t_defined
typedef __blkcnt_t blkcnt_t;	 /* Type to count number of disk blocks.  */
#  define __blkcnt_t_defined
# endif
# 238 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
# ifndef __fsblkcnt_t_defined
typedef __fsblkcnt_t fsblkcnt_t; /* Type to count file system blocks.  */
#  define __fsblkcnt_t_defined
# endif
# 242 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
# ifndef __fsfilcnt_t_defined
typedef __fsfilcnt_t fsfilcnt_t; /* Type to count file system inodes.  */
#  define __fsfilcnt_t_defined
# endif
# 246 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
#else
# 247 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
# ifndef __blkcnt_t_defined
typedef __blkcnt64_t blkcnt_t;	   /* Type to count number of disk blocks.  */
#  define __blkcnt_t_defined
# endif
# 251 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
# ifndef __fsblkcnt_t_defined
typedef __fsblkcnt64_t fsblkcnt_t; /* Type to count file system blocks.  */
#  define __fsblkcnt_t_defined
# endif
# 255 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
# ifndef __fsfilcnt_t_defined
typedef __fsfilcnt64_t fsfilcnt_t; /* Type to count file system inodes.  */
#  define __fsfilcnt_t_defined
# endif
# 259 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
#endif
# 260 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4

#ifdef __USE_LARGEFILE64
typedef __blkcnt64_t blkcnt64_t;     /* Type to count number of disk blocks. */
typedef __fsblkcnt64_t fsblkcnt64_t; /* Type to count file system blocks.  */
typedef __fsfilcnt64_t fsfilcnt64_t; /* Type to count file system inodes.  */
#endif
# 266 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4


/* Now add the thread types.  */
#if defined __USE_POSIX199506 || defined __USE_UNIX98
#if 0 /* expanded by -frewrite-includes */
# include <bits/pthreadtypes.h>
#endif /* expanded by -frewrite-includes */
# 270 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 1 3 4
/* Copyright (C) 2002-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _BITS_PTHREADTYPES_H
#define _BITS_PTHREADTYPES_H	1

#if 0 /* expanded by -frewrite-includes */
#include <bits/wordsize.h>
#endif /* expanded by -frewrite-includes */
# 21 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
/* Determine the wordsize from the preprocessor defines.  */

#if defined __x86_64__ && !defined __ILP32__
# define __WORDSIZE	64
#else
# 6 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 3 4
# define __WORDSIZE	32
#endif
# 8 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 3 4

#ifdef __x86_64__
# define __WORDSIZE_TIME64_COMPAT32	1
/* Both x86-64 and x32 use the 64-bit system call interface.  */
# define __SYSCALL_WORDSIZE		64
#endif
# 14 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 3 4
# 22 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 2 3 4

#ifdef __x86_64__
# if __WORDSIZE == 64
#  define __SIZEOF_PTHREAD_ATTR_T 56
#  define __SIZEOF_PTHREAD_MUTEX_T 40
#  define __SIZEOF_PTHREAD_MUTEXATTR_T 4
#  define __SIZEOF_PTHREAD_COND_T 48
#  define __SIZEOF_PTHREAD_CONDATTR_T 4
#  define __SIZEOF_PTHREAD_RWLOCK_T 56
#  define __SIZEOF_PTHREAD_RWLOCKATTR_T 8
#  define __SIZEOF_PTHREAD_BARRIER_T 32
#  define __SIZEOF_PTHREAD_BARRIERATTR_T 4
# else
# 35 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 3 4
#  define __SIZEOF_PTHREAD_ATTR_T 32
#  define __SIZEOF_PTHREAD_MUTEX_T 32
#  define __SIZEOF_PTHREAD_MUTEXATTR_T 4
#  define __SIZEOF_PTHREAD_COND_T 48
#  define __SIZEOF_PTHREAD_CONDATTR_T 4
#  define __SIZEOF_PTHREAD_RWLOCK_T 44
#  define __SIZEOF_PTHREAD_RWLOCKATTR_T 8
#  define __SIZEOF_PTHREAD_BARRIER_T 20
#  define __SIZEOF_PTHREAD_BARRIERATTR_T 4
# endif
# 45 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 3 4
#else
# 46 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 3 4
# define __SIZEOF_PTHREAD_ATTR_T 36
# define __SIZEOF_PTHREAD_MUTEX_T 24
# define __SIZEOF_PTHREAD_MUTEXATTR_T 4
# define __SIZEOF_PTHREAD_COND_T 48
# define __SIZEOF_PTHREAD_CONDATTR_T 4
# define __SIZEOF_PTHREAD_RWLOCK_T 32
# define __SIZEOF_PTHREAD_RWLOCKATTR_T 8
# define __SIZEOF_PTHREAD_BARRIER_T 20
# define __SIZEOF_PTHREAD_BARRIERATTR_T 4
#endif
# 56 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 3 4


/* Thread identifiers.  The structure of the attribute type is not
   exposed on purpose.  */
typedef unsigned long int pthread_t;


union pthread_attr_t
{
  char __size[__SIZEOF_PTHREAD_ATTR_T];
  long int __align;
};
#ifndef __have_pthread_attr_t
typedef union pthread_attr_t pthread_attr_t;
# define __have_pthread_attr_t	1
#endif
# 72 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 3 4


#ifdef __x86_64__
typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;
#else
# 81 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 3 4
typedef struct __pthread_internal_slist
{
  struct __pthread_internal_slist *__next;
} __pthread_slist_t;
#endif
# 86 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 3 4


/* Data structures for mutex handling.  The structure of the attribute
   type is not exposed on purpose.  */
typedef union
{
  struct __pthread_mutex_s
  {
    int __lock;
    unsigned int __count;
    int __owner;
#ifdef __x86_64__
    unsigned int __nusers;
#endif
# 100 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 3 4
    /* KIND must stay at this position in the structure to maintain
       binary compatibility.  */
    int __kind;
#ifdef __x86_64__
    short __spins;
    short __elision;
    __pthread_list_t __list;
# define __PTHREAD_MUTEX_HAVE_PREV	1
/* Mutex __spins initializer used by PTHREAD_MUTEX_INITIALIZER.  */
# define __PTHREAD_SPINS             0, 0
#else
# 111 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 3 4
    unsigned int __nusers;
    __extension__ union
    {
      struct
      {
	short __espins;
	short __elision;
# define __spins __elision_data.__espins
# define __elision __elision_data.__elision
# define __PTHREAD_SPINS         { 0, 0 }
      } __elision_data;
      __pthread_slist_t __list;
    };
#endif
# 125 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 3 4
  } __data;
  char __size[__SIZEOF_PTHREAD_MUTEX_T];
  long int __align;
} pthread_mutex_t;

typedef union
{
  char __size[__SIZEOF_PTHREAD_MUTEXATTR_T];
  int __align;
} pthread_mutexattr_t;


/* Data structure for conditional variable handling.  The structure of
   the attribute type is not exposed on purpose.  */
typedef union
{
  struct
  {
    int __lock;
    unsigned int __futex;
    __extension__ unsigned long long int __total_seq;
    __extension__ unsigned long long int __wakeup_seq;
    __extension__ unsigned long long int __woken_seq;
    void *__mutex;
    unsigned int __nwaiters;
    unsigned int __broadcast_seq;
  } __data;
  char __size[__SIZEOF_PTHREAD_COND_T];
  __extension__ long long int __align;
} pthread_cond_t;

typedef union
{
  char __size[__SIZEOF_PTHREAD_CONDATTR_T];
  int __align;
} pthread_condattr_t;


/* Keys for thread-specific data */
typedef unsigned int pthread_key_t;


/* Once-only execution */
typedef int pthread_once_t;


#if defined __USE_UNIX98 || defined __USE_XOPEN2K
/* Data structure for read-write lock variable handling.  The
   structure of the attribute type is not exposed on purpose.  */
typedef union
{
# ifdef __x86_64__
  struct
  {
    int __lock;
    unsigned int __nr_readers;
    unsigned int __readers_wakeup;
    unsigned int __writer_wakeup;
    unsigned int __nr_readers_queued;
    unsigned int __nr_writers_queued;
    int __writer;
    int __shared;
    signed char __rwelision;
#  ifdef  __ILP32__
    unsigned char __pad1[3];
#    define __PTHREAD_RWLOCK_ELISION_EXTRA 0, { 0, 0, 0 }
#  else
# 192 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 3 4
    unsigned char __pad1[7];
#    define __PTHREAD_RWLOCK_ELISION_EXTRA 0, { 0, 0, 0, 0, 0, 0, 0 }
#  endif
# 195 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 3 4
    unsigned long int __pad2;
    /* FLAGS must stay at this position in the structure to maintain
       binary compatibility.  */
    unsigned int __flags;
# define __PTHREAD_RWLOCK_INT_FLAGS_SHARED	1
  } __data;
# else
# 202 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 3 4
  struct
  {
    int __lock;
    unsigned int __nr_readers;
    unsigned int __readers_wakeup;
    unsigned int __writer_wakeup;
    unsigned int __nr_readers_queued;
    unsigned int __nr_writers_queued;
    /* FLAGS must stay at this position in the structure to maintain
       binary compatibility.  */
    unsigned char __flags;
    unsigned char __shared;
    signed char __rwelision;
# define __PTHREAD_RWLOCK_ELISION_EXTRA 0
    unsigned char __pad2;
    int __writer;
  } __data;
# endif
# 220 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 3 4
  char __size[__SIZEOF_PTHREAD_RWLOCK_T];
  long int __align;
} pthread_rwlock_t;

typedef union
{
  char __size[__SIZEOF_PTHREAD_RWLOCKATTR_T];
  long int __align;
} pthread_rwlockattr_t;
#endif
# 230 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 3 4


#ifdef __USE_XOPEN2K
/* POSIX spinlock data type.  */
typedef volatile int pthread_spinlock_t;


/* POSIX barriers data type.  The structure of the type is
   deliberately not exposed.  */
typedef union
{
  char __size[__SIZEOF_PTHREAD_BARRIER_T];
  long int __align;
} pthread_barrier_t;

typedef union
{
  char __size[__SIZEOF_PTHREAD_BARRIERATTR_T];
  int __align;
} pthread_barrierattr_t;
#endif
# 251 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 3 4


#ifndef __x86_64__
/* Extra attributes for the cleanup functions.  */
# define __cleanup_fct_attribute __attribute__ ((__regparm__ (1)))
#endif
# 257 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 3 4

#endif	/* bits/pthreadtypes.h */
# 259 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 3 4
# 271 "/usr/include/x86_64-linux-gnu/sys/types.h" 2 3 4
#endif
# 272 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4

__END_DECLS

#endif /* sys/types.h */
# 276 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
# 315 "/usr/include/stdlib.h" 2 3 4

/* These are the functions that actually do things.  The `random', `srandom',
   `initstate' and `setstate' functions are those from BSD Unices.
   The `rand' and `srand' functions are required by the ANSI standard.
   We provide both interfaces to the same random number generator.  */
/* Return a random long integer between 0 and RAND_MAX inclusive.  */
extern long int random (void) __THROW;

/* Seed the random number generator with the given number.  */
extern void srandom (unsigned int __seed) __THROW;

/* Initialize the random number generator to use state buffer STATEBUF,
   of length STATELEN, and seed it with SEED.  Optimal lengths are 8, 16,
   32, 64, 128 and 256, the bigger the better; values less than 8 will
   cause an error and values greater than 256 will be rounded down.  */
extern char *initstate (unsigned int __seed, char *__statebuf,
			size_t __statelen) __THROW __nonnull ((2));

/* Switch the random number generator to state buffer STATEBUF,
   which should have been previously initialized by `initstate'.  */
extern char *setstate (char *__statebuf) __THROW __nonnull ((1));


# ifdef __USE_MISC
/* Reentrant versions of the `random' family of functions.
   These functions all use the following data structure to contain
   state, rather than global state variables.  */

struct random_data
  {
    int32_t *fptr;		/* Front pointer.  */
    int32_t *rptr;		/* Rear pointer.  */
    int32_t *state;		/* Array of state values.  */
    int rand_type;		/* Type of random number generator.  */
    int rand_deg;		/* Degree of random number generator.  */
    int rand_sep;		/* Distance between front and rear.  */
    int32_t *end_ptr;		/* Pointer behind state table.  */
  };

extern int random_r (struct random_data *__restrict __buf,
		     int32_t *__restrict __result) __THROW __nonnull ((1, 2));

extern int srandom_r (unsigned int __seed, struct random_data *__buf)
     __THROW __nonnull ((2));

extern int initstate_r (unsigned int __seed, char *__restrict __statebuf,
			size_t __statelen,
			struct random_data *__restrict __buf)
     __THROW __nonnull ((2, 4));

extern int setstate_r (char *__restrict __statebuf,
		       struct random_data *__restrict __buf)
     __THROW __nonnull ((1, 2));
# endif	/* Use misc.  */
# 369 "/usr/include/stdlib.h" 3 4
#endif	/* Use extended X/Open || misc. */
# 370 "/usr/include/stdlib.h" 3 4


__BEGIN_NAMESPACE_STD
/* Return a random integer between 0 and RAND_MAX inclusive.  */
extern int rand (void) __THROW;
/* Seed the random number generator with the given number.  */
extern void srand (unsigned int __seed) __THROW;
__END_NAMESPACE_STD

#ifdef __USE_POSIX
/* Reentrant interface according to POSIX.1.  */
extern int rand_r (unsigned int *__seed) __THROW;
#endif
# 383 "/usr/include/stdlib.h" 3 4


#if defined __USE_MISC || defined __USE_XOPEN
/* System V style 48-bit random number generator functions.  */

/* Return non-negative, double-precision floating-point value in [0.0,1.0).  */
extern double drand48 (void) __THROW;
extern double erand48 (unsigned short int __xsubi[3]) __THROW __nonnull ((1));

/* Return non-negative, long integer in [0,2^31).  */
extern long int lrand48 (void) __THROW;
extern long int nrand48 (unsigned short int __xsubi[3])
     __THROW __nonnull ((1));

/* Return signed, long integers in [-2^31,2^31).  */
extern long int mrand48 (void) __THROW;
extern long int jrand48 (unsigned short int __xsubi[3])
     __THROW __nonnull ((1));

/* Seed random number generator.  */
extern void srand48 (long int __seedval) __THROW;
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
     __THROW __nonnull ((1));
extern void lcong48 (unsigned short int __param[7]) __THROW __nonnull ((1));

# ifdef __USE_MISC
/* Data structure for communication with thread safe versions.  This
   type is to be regarded as opaque.  It's only exported because users
   have to allocate objects of this type.  */
struct drand48_data
  {
    unsigned short int __x[3];	/* Current state.  */
    unsigned short int __old_x[3]; /* Old state.  */
    unsigned short int __c;	/* Additive const. in congruential formula.  */
    unsigned short int __init;	/* Flag for initializing.  */
    __extension__ unsigned long long int __a;	/* Factor in congruential
						   formula.  */
  };

/* Return non-negative, double-precision floating-point value in [0.0,1.0).  */
extern int drand48_r (struct drand48_data *__restrict __buffer,
		      double *__restrict __result) __THROW __nonnull ((1, 2));
extern int erand48_r (unsigned short int __xsubi[3],
		      struct drand48_data *__restrict __buffer,
		      double *__restrict __result) __THROW __nonnull ((1, 2));

/* Return non-negative, long integer in [0,2^31).  */
extern int lrand48_r (struct drand48_data *__restrict __buffer,
		      long int *__restrict __result)
     __THROW __nonnull ((1, 2));
extern int nrand48_r (unsigned short int __xsubi[3],
		      struct drand48_data *__restrict __buffer,
		      long int *__restrict __result)
     __THROW __nonnull ((1, 2));

/* Return signed, long integers in [-2^31,2^31).  */
extern int mrand48_r (struct drand48_data *__restrict __buffer,
		      long int *__restrict __result)
     __THROW __nonnull ((1, 2));
extern int jrand48_r (unsigned short int __xsubi[3],
		      struct drand48_data *__restrict __buffer,
		      long int *__restrict __result)
     __THROW __nonnull ((1, 2));

/* Seed random number generator.  */
extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
     __THROW __nonnull ((2));

extern int seed48_r (unsigned short int __seed16v[3],
		     struct drand48_data *__buffer) __THROW __nonnull ((1, 2));

extern int lcong48_r (unsigned short int __param[7],
		      struct drand48_data *__buffer)
     __THROW __nonnull ((1, 2));
# endif	/* Use misc.  */
# 458 "/usr/include/stdlib.h" 3 4
#endif	/* Use misc or X/Open.  */
# 459 "/usr/include/stdlib.h" 3 4

#endif /* don't just need malloc and calloc */
# 461 "/usr/include/stdlib.h" 3 4

#ifndef __malloc_and_calloc_defined
# define __malloc_and_calloc_defined
__BEGIN_NAMESPACE_STD
/* Allocate SIZE bytes of memory.  */
extern void *malloc (size_t __size) __THROW __attribute_malloc__ __wur;
/* Allocate NMEMB elements of SIZE bytes each, all initialized to 0.  */
extern void *calloc (size_t __nmemb, size_t __size)
     __THROW __attribute_malloc__ __wur;
__END_NAMESPACE_STD
#endif
# 472 "/usr/include/stdlib.h" 3 4

#ifndef __need_malloc_and_calloc
__BEGIN_NAMESPACE_STD
/* Re-allocate the previously allocated block
   in PTR, making the new block SIZE bytes long.  */
/* __attribute_malloc__ is not used, because if realloc returns
   the same pointer that was passed to it, aliasing needs to be allowed
   between objects pointed by the old and new pointers.  */
extern void *realloc (void *__ptr, size_t __size)
     __THROW __attribute_warn_unused_result__;
/* Free a block allocated by `malloc', `realloc' or `calloc'.  */
extern void free (void *__ptr) __THROW;
__END_NAMESPACE_STD

#ifdef	__USE_MISC
/* Free a block.  An alias for `free'.	(Sun Unices).  */
extern void cfree (void *__ptr) __THROW;
#endif /* Use misc.  */
# 490 "/usr/include/stdlib.h" 3 4

#ifdef __USE_MISC
#if 0 /* expanded by -frewrite-includes */
# include <alloca.h>
#endif /* expanded by -frewrite-includes */
# 492 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/alloca.h" 1 3 4
/* Copyright (C) 1992-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef	_ALLOCA_H
#define	_ALLOCA_H	1

#if 0 /* expanded by -frewrite-includes */
#include <features.h>
#endif /* expanded by -frewrite-includes */
# 21 "/usr/include/alloca.h" 3 4
# 22 "/usr/include/alloca.h" 3 4

#define	__need_size_t
#if 0 /* expanded by -frewrite-includes */
#include <stddef.h>
#endif /* expanded by -frewrite-includes */
# 24 "/usr/include/alloca.h" 3 4
# 1 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 1 3 4
/*===---- stddef.h - Basic type definitions --------------------------------===
 *
 * Copyright (c) 2008 Eli Friedman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *===-----------------------------------------------------------------------===
 */

#if !defined(__STDDEF_H) || defined(__need_ptrdiff_t) ||                       \
    defined(__need_size_t) || defined(__need_wchar_t) ||                       \
    defined(__need_NULL) || defined(__need_wint_t)

#if !defined(__need_ptrdiff_t) && !defined(__need_size_t) &&                   \
    !defined(__need_wchar_t) && !defined(__need_NULL) &&                       \
    !defined(__need_wint_t)
/* Always define miscellaneous pieces when modules are available. */
#if !__has_feature(modules)
#define __STDDEF_H
#endif
# 37 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#define __need_ptrdiff_t
#define __need_size_t
#define __need_wchar_t
#define __need_NULL
#define __need_STDDEF_H_misc
/* __need_wint_t is intentionally not defined here. */
#endif
# 44 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_ptrdiff_t)
#if !defined(_PTRDIFF_T) || __has_feature(modules)
/* Always define ptrdiff_t when modules are available. */
#if !__has_feature(modules)
#define _PTRDIFF_T
#endif
# 51 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif
# 53 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_ptrdiff_t
#endif /* defined(__need_ptrdiff_t) */
# 55 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_size_t)
#if !defined(_SIZE_T) || __has_feature(modules)
/* Always define size_t when modules are available. */
#if !__has_feature(modules)
#define _SIZE_T
#endif
# 62 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ size_t;
#endif
# 64 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_size_t
#endif /*defined(__need_size_t) */
# 66 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
/* ISO9899:2011 7.20 (C11 Annex K): Define rsize_t if __STDC_WANT_LIB_EXT1__ is
 * enabled. */
#if (defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ >= 1 && \
     !defined(_RSIZE_T)) || __has_feature(modules)
/* Always define rsize_t when modules are available. */
#if !__has_feature(modules)
#define _RSIZE_T
#endif
# 76 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ rsize_t;
#endif
# 78 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#endif /* defined(__need_STDDEF_H_misc) */
# 79 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_wchar_t)
#ifndef __cplusplus
/* Always define wchar_t when modules are available. */
#if !defined(_WCHAR_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WCHAR_T
#if defined(_MSC_EXTENSIONS)
#define _WCHAR_T_DEFINED
#endif
# 89 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 90 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WCHAR_TYPE__ wchar_t;
#endif
# 92 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 93 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wchar_t
#endif /* defined(__need_wchar_t) */
# 95 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_NULL)
#undef NULL
#ifdef __cplusplus
#  if !defined(__MINGW32__) && !defined(_MSC_VER)
#    define NULL __null
#  else
# 102 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#    define NULL 0
#  endif
# 104 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#else
# 105 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#  define NULL ((void*)0)
#endif
# 107 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#ifdef __cplusplus
#if defined(_MSC_EXTENSIONS) && defined(_NATIVE_NULLPTR_SUPPORTED)
namespace std { typedef decltype(nullptr) nullptr_t; }
using ::std::nullptr_t;
#endif
# 112 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 113 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_NULL
#endif /* defined(__need_NULL) */
# 115 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
#if __STDC_VERSION__ >= 201112L || __cplusplus >= 201103L
#if 0 /* expanded by -frewrite-includes */
#include "__stddef_max_align_t.h"
#endif /* expanded by -frewrite-includes */
# 118 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
# 119 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 120 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#define offsetof(t, d) __builtin_offsetof(t, d)
#undef __need_STDDEF_H_misc
#endif  /* defined(__need_STDDEF_H_misc) */
# 123 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

/* Some C libraries expect to see a wint_t here. Others (notably MinGW) will use
__WINT_TYPE__ directly; accommodate both by requiring __need_wint_t */
#if defined(__need_wint_t)
/* Always define wint_t when modules are available. */
#if !defined(_WINT_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WINT_T
#endif
# 132 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WINT_TYPE__ wint_t;
#endif
# 134 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wint_t
#endif /* __need_wint_t */
# 136 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4

#endif
# 138 "/root/build/llvm/release/lib/clang/5.0.0/include/stddef.h" 3 4
# 25 "/usr/include/alloca.h" 2 3 4

__BEGIN_DECLS

/* Remove any previous definitions.  */
#undef	alloca

/* Allocate a block that will be freed when the calling function exits.  */
extern void *alloca (size_t __size) __THROW;

#ifdef	__GNUC__
# define alloca(size)	__builtin_alloca (size)
#endif /* GCC.  */
# 37 "/usr/include/alloca.h" 3 4

__END_DECLS

#endif /* alloca.h */
# 41 "/usr/include/alloca.h" 3 4
# 493 "/usr/include/stdlib.h" 2 3 4
#endif /* Use misc.  */
# 494 "/usr/include/stdlib.h" 3 4

#if (defined __USE_XOPEN_EXTENDED && !defined __USE_XOPEN2K) \
    || defined __USE_MISC
/* Allocate SIZE bytes on a page boundary.  The storage cannot be freed.  */
extern void *valloc (size_t __size) __THROW __attribute_malloc__ __wur;
#endif
# 500 "/usr/include/stdlib.h" 3 4

#ifdef __USE_XOPEN2K
/* Allocate memory of SIZE bytes with an alignment of ALIGNMENT.  */
extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
     __THROW __nonnull ((1)) __wur;
#endif
# 506 "/usr/include/stdlib.h" 3 4

#ifdef __USE_ISOC11
/* ISO C variant of aligned allocation.  */
extern void *aligned_alloc (size_t __alignment, size_t __size)
     __THROW __attribute_malloc__ __attribute_alloc_size__ ((2)) __wur;
#endif
# 512 "/usr/include/stdlib.h" 3 4

__BEGIN_NAMESPACE_STD
/* Abort execution and generate a core-dump.  */
extern void abort (void) __THROW __attribute__ ((__noreturn__));


/* Register a function to be called when `exit' is called.  */
extern int atexit (void (*__func) (void)) __THROW __nonnull ((1));

#if defined __USE_ISOC11 || defined __USE_ISOCXX11
/* Register a function to be called when `quick_exit' is called.  */
# ifdef __cplusplus
extern "C++" int at_quick_exit (void (*__func) (void))
     __THROW __asm ("at_quick_exit") __nonnull ((1));
# else
# 527 "/usr/include/stdlib.h" 3 4
extern int at_quick_exit (void (*__func) (void)) __THROW __nonnull ((1));
# endif
# 529 "/usr/include/stdlib.h" 3 4
#endif
# 530 "/usr/include/stdlib.h" 3 4
__END_NAMESPACE_STD

#ifdef	__USE_MISC
/* Register a function to be called with the status
   given to `exit' and the given argument.  */
extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
     __THROW __nonnull ((1));
#endif
# 538 "/usr/include/stdlib.h" 3 4

__BEGIN_NAMESPACE_STD
/* Call all functions registered with `atexit' and `on_exit',
   in the reverse of the order in which they were registered,
   perform stdio cleanup, and terminate program execution with STATUS.  */
extern void exit (int __status) __THROW __attribute__ ((__noreturn__));

#if defined __USE_ISOC11 || defined __USE_ISOCXX11
/* Call all functions registered with `at_quick_exit' in the reverse
   of the order in which they were registered and terminate program
   execution with STATUS.  */
extern void quick_exit (int __status) __THROW __attribute__ ((__noreturn__));
#endif
# 551 "/usr/include/stdlib.h" 3 4
__END_NAMESPACE_STD

#ifdef __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Terminate the program with STATUS without calling any of the
   functions registered with `atexit' or `on_exit'.  */
extern void _Exit (int __status) __THROW __attribute__ ((__noreturn__));
__END_NAMESPACE_C99
#endif
# 560 "/usr/include/stdlib.h" 3 4


__BEGIN_NAMESPACE_STD
/* Return the value of envariable NAME, or NULL if it doesn't exist.  */
extern char *getenv (const char *__name) __THROW __nonnull ((1)) __wur;
__END_NAMESPACE_STD

#ifdef __USE_GNU
/* This function is similar to the above but returns NULL if the
   programs is running with SUID or SGID enabled.  */
extern char *secure_getenv (const char *__name)
     __THROW __nonnull ((1)) __wur;
#endif
# 573 "/usr/include/stdlib.h" 3 4

#if defined __USE_MISC || defined __USE_XOPEN
/* The SVID says this is in <stdio.h>, but this seems a better place.	*/
/* Put STRING, which is of the form "NAME=VALUE", in the environment.
   If there is no `=', remove NAME from the environment.  */
extern int putenv (char *__string) __THROW __nonnull ((1));
#endif
# 580 "/usr/include/stdlib.h" 3 4

#ifdef __USE_XOPEN2K
/* Set NAME to VALUE in the environment.
   If REPLACE is nonzero, overwrite an existing value.  */
extern int setenv (const char *__name, const char *__value, int __replace)
     __THROW __nonnull ((2));

/* Remove the variable NAME from the environment.  */
extern int unsetenv (const char *__name) __THROW __nonnull ((1));
#endif
# 590 "/usr/include/stdlib.h" 3 4

#ifdef	__USE_MISC
/* The `clearenv' was planned to be added to POSIX.1 but probably
   never made it.  Nevertheless the POSIX.9 standard (POSIX bindings
   for Fortran 77) requires this function.  */
extern int clearenv (void) __THROW;
#endif
# 597 "/usr/include/stdlib.h" 3 4


#if defined __USE_MISC \
    || (defined __USE_XOPEN_EXTENDED && !defined __USE_XOPEN2K8)
/* Generate a unique temporary file name from TEMPLATE.
   The last six characters of TEMPLATE must be "XXXXXX";
   they are replaced with a string that makes the file name unique.
   Always returns TEMPLATE, it's either a temporary file name or a null
   string if it cannot get a unique file name.  */
extern char *mktemp (char *__template) __THROW __nonnull ((1));
#endif
# 608 "/usr/include/stdlib.h" 3 4

#if defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8
/* Generate a unique temporary file name from TEMPLATE.
   The last six characters of TEMPLATE must be "XXXXXX";
   they are replaced with a string that makes the filename unique.
   Returns a file descriptor open on the file for reading and writing,
   or -1 if it cannot create a uniquely-named file.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
# ifndef __USE_FILE_OFFSET64
extern int mkstemp (char *__template) __nonnull ((1)) __wur;
# else
# 621 "/usr/include/stdlib.h" 3 4
#  ifdef __REDIRECT
extern int __REDIRECT (mkstemp, (char *__template), mkstemp64)
     __nonnull ((1)) __wur;
#  else
# 625 "/usr/include/stdlib.h" 3 4
#   define mkstemp mkstemp64
#  endif
# 627 "/usr/include/stdlib.h" 3 4
# endif
# 628 "/usr/include/stdlib.h" 3 4
# ifdef __USE_LARGEFILE64
extern int mkstemp64 (char *__template) __nonnull ((1)) __wur;
# endif
# 631 "/usr/include/stdlib.h" 3 4
#endif
# 632 "/usr/include/stdlib.h" 3 4

#ifdef __USE_MISC
/* Similar to mkstemp, but the template can have a suffix after the
   XXXXXX.  The length of the suffix is specified in the second
   parameter.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
# ifndef __USE_FILE_OFFSET64
extern int mkstemps (char *__template, int __suffixlen) __nonnull ((1)) __wur;
# else
# 643 "/usr/include/stdlib.h" 3 4
#  ifdef __REDIRECT
extern int __REDIRECT (mkstemps, (char *__template, int __suffixlen),
		       mkstemps64) __nonnull ((1)) __wur;
#  else
# 647 "/usr/include/stdlib.h" 3 4
#   define mkstemps mkstemps64
#  endif
# 649 "/usr/include/stdlib.h" 3 4
# endif
# 650 "/usr/include/stdlib.h" 3 4
# ifdef __USE_LARGEFILE64
extern int mkstemps64 (char *__template, int __suffixlen)
     __nonnull ((1)) __wur;
# endif
# 654 "/usr/include/stdlib.h" 3 4
#endif
# 655 "/usr/include/stdlib.h" 3 4

#ifdef __USE_XOPEN2K8
/* Create a unique temporary directory from TEMPLATE.
   The last six characters of TEMPLATE must be "XXXXXX";
   they are replaced with a string that makes the directory name unique.
   Returns TEMPLATE, or a null pointer if it cannot get a unique name.
   The directory is created mode 700.  */
extern char *mkdtemp (char *__template) __THROW __nonnull ((1)) __wur;
#endif
# 664 "/usr/include/stdlib.h" 3 4

#ifdef __USE_GNU
/* Generate a unique temporary file name from TEMPLATE similar to
   mkstemp.  But allow the caller to pass additional flags which are
   used in the open call to create the file..

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
# ifndef __USE_FILE_OFFSET64
extern int mkostemp (char *__template, int __flags) __nonnull ((1)) __wur;
# else
# 675 "/usr/include/stdlib.h" 3 4
#  ifdef __REDIRECT
extern int __REDIRECT (mkostemp, (char *__template, int __flags), mkostemp64)
     __nonnull ((1)) __wur;
#  else
# 679 "/usr/include/stdlib.h" 3 4
#   define mkostemp mkostemp64
#  endif
# 681 "/usr/include/stdlib.h" 3 4
# endif
# 682 "/usr/include/stdlib.h" 3 4
# ifdef __USE_LARGEFILE64
extern int mkostemp64 (char *__template, int __flags) __nonnull ((1)) __wur;
# endif
# 685 "/usr/include/stdlib.h" 3 4

/* Similar to mkostemp, but the template can have a suffix after the
   XXXXXX.  The length of the suffix is specified in the second
   parameter.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
# ifndef __USE_FILE_OFFSET64
extern int mkostemps (char *__template, int __suffixlen, int __flags)
     __nonnull ((1)) __wur;
# else
# 696 "/usr/include/stdlib.h" 3 4
#  ifdef __REDIRECT
extern int __REDIRECT (mkostemps, (char *__template, int __suffixlen,
				   int __flags), mkostemps64)
     __nonnull ((1)) __wur;
#  else
# 701 "/usr/include/stdlib.h" 3 4
#   define mkostemps mkostemps64
#  endif
# 703 "/usr/include/stdlib.h" 3 4
# endif
# 704 "/usr/include/stdlib.h" 3 4
# ifdef __USE_LARGEFILE64
extern int mkostemps64 (char *__template, int __suffixlen, int __flags)
     __nonnull ((1)) __wur;
# endif
# 708 "/usr/include/stdlib.h" 3 4
#endif
# 709 "/usr/include/stdlib.h" 3 4


__BEGIN_NAMESPACE_STD
/* Execute the given line as a shell command.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern int system (const char *__command) __wur;
__END_NAMESPACE_STD


#ifdef	__USE_GNU
/* Return a malloc'd string containing the canonical absolute name of the
   existing named file.  */
extern char *canonicalize_file_name (const char *__name)
     __THROW __nonnull ((1)) __wur;
#endif
# 726 "/usr/include/stdlib.h" 3 4

#if defined __USE_MISC || defined __USE_XOPEN_EXTENDED
/* Return the canonical absolute name of file NAME.  If RESOLVED is
   null, the result is malloc'd; otherwise, if the canonical name is
   PATH_MAX chars or more, returns null with `errno' set to
   ENAMETOOLONG; if the name fits in fewer than PATH_MAX chars,
   returns the name in RESOLVED.  */
extern char *realpath (const char *__restrict __name,
		       char *__restrict __resolved) __THROW __wur;
#endif
# 736 "/usr/include/stdlib.h" 3 4


/* Shorthand for type of comparison functions.  */
#ifndef __COMPAR_FN_T
# define __COMPAR_FN_T
typedef int (*__compar_fn_t) (const void *, const void *);

# ifdef	__USE_GNU
typedef __compar_fn_t comparison_fn_t;
# endif
# 746 "/usr/include/stdlib.h" 3 4
#endif
# 747 "/usr/include/stdlib.h" 3 4
#ifdef __USE_GNU
typedef int (*__compar_d_fn_t) (const void *, const void *, void *);
#endif
# 750 "/usr/include/stdlib.h" 3 4

__BEGIN_NAMESPACE_STD
/* Do a binary search for KEY in BASE, which consists of NMEMB elements
   of SIZE bytes each, using COMPAR to perform the comparisons.  */
extern void *bsearch (const void *__key, const void *__base,
		      size_t __nmemb, size_t __size, __compar_fn_t __compar)
     __nonnull ((1, 2, 5)) __wur;

#ifdef __USE_EXTERN_INLINES
#if 0 /* expanded by -frewrite-includes */
# include <bits/stdlib-bsearch.h>
#endif /* expanded by -frewrite-includes */
# 759 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/stdlib-bsearch.h" 1 3 4
/* Perform binary search - inline version.
   Copyright (C) 1991-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

__extern_inline void *
bsearch (const void *__key, const void *__base, size_t __nmemb, size_t __size,
	 __compar_fn_t __compar)
{
  size_t __l, __u, __idx;
  const void *__p;
  int __comparison;

  __l = 0;
  __u = __nmemb;
  while (__l < __u)
    {
      __idx = (__l + __u) / 2;
      __p = (void *) (((const char *) __base) + (__idx * __size));
      __comparison = (*__compar) (__key, __p);
      if (__comparison < 0)
	__u = __idx;
      else if (__comparison > 0)
	__l = __idx + 1;
      else
	return (void *) __p;
    }

  return NULL;
}
# 760 "/usr/include/stdlib.h" 2 3 4
#endif
# 761 "/usr/include/stdlib.h" 3 4

/* Sort NMEMB elements of BASE, of SIZE bytes each,
   using COMPAR to perform the comparisons.  */
extern void qsort (void *__base, size_t __nmemb, size_t __size,
		   __compar_fn_t __compar) __nonnull ((1, 4));
#ifdef __USE_GNU
extern void qsort_r (void *__base, size_t __nmemb, size_t __size,
		     __compar_d_fn_t __compar, void *__arg)
  __nonnull ((1, 4));
#endif
# 771 "/usr/include/stdlib.h" 3 4


/* Return the absolute value of X.  */
extern int abs (int __x) __THROW __attribute__ ((__const__)) __wur;
extern long int labs (long int __x) __THROW __attribute__ ((__const__)) __wur;
__END_NAMESPACE_STD

#ifdef __USE_ISOC99
__extension__ extern long long int llabs (long long int __x)
     __THROW __attribute__ ((__const__)) __wur;
#endif
# 782 "/usr/include/stdlib.h" 3 4


__BEGIN_NAMESPACE_STD
/* Return the `div_t', `ldiv_t' or `lldiv_t' representation
   of the value of NUMER over DENOM. */
/* GCC may have built-ins for these someday.  */
extern div_t div (int __numer, int __denom)
     __THROW __attribute__ ((__const__)) __wur;
extern ldiv_t ldiv (long int __numer, long int __denom)
     __THROW __attribute__ ((__const__)) __wur;
__END_NAMESPACE_STD

#ifdef __USE_ISOC99
__BEGIN_NAMESPACE_C99
__extension__ extern lldiv_t lldiv (long long int __numer,
				    long long int __denom)
     __THROW __attribute__ ((__const__)) __wur;
__END_NAMESPACE_C99
#endif
# 801 "/usr/include/stdlib.h" 3 4


#if (defined __USE_XOPEN_EXTENDED && !defined __USE_XOPEN2K8) \
    || defined __USE_MISC
/* Convert floating point numbers to strings.  The returned values are
   valid only until another call to the same function.  */

/* Convert VALUE to a string with NDIGIT digits and return a pointer to
   this.  Set *DECPT with the position of the decimal character and *SIGN
   with the sign of the number.  */
extern char *ecvt (double __value, int __ndigit, int *__restrict __decpt,
		   int *__restrict __sign) __THROW __nonnull ((3, 4)) __wur;

/* Convert VALUE to a string rounded to NDIGIT decimal digits.  Set *DECPT
   with the position of the decimal character and *SIGN with the sign of
   the number.  */
extern char *fcvt (double __value, int __ndigit, int *__restrict __decpt,
		   int *__restrict __sign) __THROW __nonnull ((3, 4)) __wur;

/* If possible convert VALUE to a string with NDIGIT significant digits.
   Otherwise use exponential representation.  The resulting string will
   be written to BUF.  */
extern char *gcvt (double __value, int __ndigit, char *__buf)
     __THROW __nonnull ((3)) __wur;
#endif
# 826 "/usr/include/stdlib.h" 3 4

#ifdef __USE_MISC
/* Long double versions of above functions.  */
extern char *qecvt (long double __value, int __ndigit,
		    int *__restrict __decpt, int *__restrict __sign)
     __THROW __nonnull ((3, 4)) __wur;
extern char *qfcvt (long double __value, int __ndigit,
		    int *__restrict __decpt, int *__restrict __sign)
     __THROW __nonnull ((3, 4)) __wur;
extern char *qgcvt (long double __value, int __ndigit, char *__buf)
     __THROW __nonnull ((3)) __wur;


/* Reentrant version of the functions above which provide their own
   buffers.  */
extern int ecvt_r (double __value, int __ndigit, int *__restrict __decpt,
		   int *__restrict __sign, char *__restrict __buf,
		   size_t __len) __THROW __nonnull ((3, 4, 5));
extern int fcvt_r (double __value, int __ndigit, int *__restrict __decpt,
		   int *__restrict __sign, char *__restrict __buf,
		   size_t __len) __THROW __nonnull ((3, 4, 5));

extern int qecvt_r (long double __value, int __ndigit,
		    int *__restrict __decpt, int *__restrict __sign,
		    char *__restrict __buf, size_t __len)
     __THROW __nonnull ((3, 4, 5));
extern int qfcvt_r (long double __value, int __ndigit,
		    int *__restrict __decpt, int *__restrict __sign,
		    char *__restrict __buf, size_t __len)
     __THROW __nonnull ((3, 4, 5));
#endif	/* misc */
# 857 "/usr/include/stdlib.h" 3 4


__BEGIN_NAMESPACE_STD
/* Return the length of the multibyte character
   in S, which is no longer than N.  */
extern int mblen (const char *__s, size_t __n) __THROW;
/* Return the length of the given multibyte character,
   putting its `wchar_t' representation in *PWC.  */
extern int mbtowc (wchar_t *__restrict __pwc,
		   const char *__restrict __s, size_t __n) __THROW;
/* Put the multibyte character represented
   by WCHAR in S, returning its length.  */
extern int wctomb (char *__s, wchar_t __wchar) __THROW;


/* Convert a multibyte string to a wide char string.  */
extern size_t mbstowcs (wchar_t *__restrict  __pwcs,
			const char *__restrict __s, size_t __n) __THROW;
/* Convert a wide char string to multibyte string.  */
extern size_t wcstombs (char *__restrict __s,
			const wchar_t *__restrict __pwcs, size_t __n)
     __THROW;
__END_NAMESPACE_STD


#ifdef __USE_MISC
/* Determine whether the string value of RESPONSE matches the affirmation
   or negative response expression as specified by the LC_MESSAGES category
   in the program's current locale.  Returns 1 if affirmative, 0 if
   negative, and -1 if not matching.  */
extern int rpmatch (const char *__response) __THROW __nonnull ((1)) __wur;
#endif
# 889 "/usr/include/stdlib.h" 3 4


#if defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8
/* Parse comma separated suboption from *OPTIONP and match against
   strings in TOKENS.  If found return index and set *VALUEP to
   optional value introduced by an equal sign.  If the suboption is
   not part of TOKENS return in *VALUEP beginning of unknown
   suboption.  On exit *OPTIONP is set to the beginning of the next
   token or at the terminating NUL character.  */
extern int getsubopt (char **__restrict __optionp,
		      char *const *__restrict __tokens,
		      char **__restrict __valuep)
     __THROW __nonnull ((1, 2, 3)) __wur;
#endif
# 903 "/usr/include/stdlib.h" 3 4


#ifdef __USE_XOPEN
/* Setup DES tables according KEY.  */
extern void setkey (const char *__key) __THROW __nonnull ((1));
#endif
# 909 "/usr/include/stdlib.h" 3 4


/* X/Open pseudo terminal handling.  */

#ifdef __USE_XOPEN2KXSI
/* Return a master pseudo-terminal handle.  */
extern int posix_openpt (int __oflag) __wur;
#endif
# 917 "/usr/include/stdlib.h" 3 4

#ifdef __USE_XOPEN
/* The next four functions all take a master pseudo-tty fd and
   perform an operation on the associated slave:  */

/* Chown the slave to the calling user.  */
extern int grantpt (int __fd) __THROW;

/* Release an internal lock so the slave can be opened.
   Call after grantpt().  */
extern int unlockpt (int __fd) __THROW;

/* Return the pathname of the pseudo terminal slave associated with
   the master FD is open on, or NULL on errors.
   The returned storage is good until the next call to this function.  */
extern char *ptsname (int __fd) __THROW __wur;
#endif
# 934 "/usr/include/stdlib.h" 3 4

#ifdef __USE_GNU
/* Store at most BUFLEN characters of the pathname of the slave pseudo
   terminal associated with the master FD is open on in BUF.
   Return 0 on success, otherwise an error number.  */
extern int ptsname_r (int __fd, char *__buf, size_t __buflen)
     __THROW __nonnull ((2));

/* Open a master pseudo terminal and return its file descriptor.  */
extern int getpt (void);
#endif
# 945 "/usr/include/stdlib.h" 3 4

#ifdef __USE_MISC
/* Put the 1 minute, 5 minute and 15 minute load averages into the first
   NELEM elements of LOADAVG.  Return the number written (never more than
   three, but may be less than NELEM), or -1 if an error occurred.  */
extern int getloadavg (double __loadavg[], int __nelem)
     __THROW __nonnull ((1));
#endif
# 953 "/usr/include/stdlib.h" 3 4

#if 0 /* expanded by -frewrite-includes */
#include <bits/stdlib-float.h>
#endif /* expanded by -frewrite-includes */
# 954 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/stdlib-float.h" 1 3 4
/* Floating-point inline functions for stdlib.h.
   Copyright (C) 2012-2016 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _STDLIB_H
# error "Never use <bits/stdlib-float.h> directly; include <stdlib.h> instead."
#endif
# 22 "/usr/include/x86_64-linux-gnu/bits/stdlib-float.h" 3 4

#ifdef __USE_EXTERN_INLINES
__BEGIN_NAMESPACE_STD
__extern_inline double
__NTH (atof (const char *__nptr))
{
  return strtod (__nptr, (char **) NULL);
}
__END_NAMESPACE_STD
#endif /* Optimizing and Inlining.  */
# 32 "/usr/include/x86_64-linux-gnu/bits/stdlib-float.h" 3 4
# 955 "/usr/include/stdlib.h" 2 3 4

/* Define some macros helping to catch buffer overflows.  */
#if __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
#if 0 /* expanded by -frewrite-includes */
# include <bits/stdlib.h>
#endif /* expanded by -frewrite-includes */
# 958 "/usr/include/stdlib.h" 3 4
# 959 "/usr/include/stdlib.h" 3 4
#endif
# 960 "/usr/include/stdlib.h" 3 4
#ifdef __LDBL_COMPAT
#if 0 /* expanded by -frewrite-includes */
# include <bits/stdlib-ldbl.h>
#endif /* expanded by -frewrite-includes */
# 961 "/usr/include/stdlib.h" 3 4
# 962 "/usr/include/stdlib.h" 3 4
#endif
# 963 "/usr/include/stdlib.h" 3 4

#endif /* don't just need malloc and calloc */
# 965 "/usr/include/stdlib.h" 3 4
#undef __need_malloc_and_calloc

__END_DECLS

#endif /* stdlib.h  */
# 970 "/usr/include/stdlib.h" 3 4
# 27 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/semeai.c" 2

#if 0 /* expanded by -frewrite-includes */
#include "liberty.h"
#endif /* expanded by -frewrite-includes */
# 28 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/semeai.c"
# 1 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/liberty.h" 1
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * This is GNU GO, a Go program. Contact gnugo@gnu.org, or see       *
 * http://www.gnu.org/software/gnugo/ for more information.          *
 *                                                                   *
 * Copyright 1999, 2000, 2001, 2002 and 2003                         *
 * by the Free Software Foundation.                                  *
 *                                                                   *
 * This program is free software; you can redistribute it and/or     *
 * modify it under the terms of the GNU General Public License as    *
 * published by the Free Software Foundation - version 2             *
 *                                                                   *
 * This program is distributed in the hope that it will be useful,   *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of    *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     *
 * GNU General Public License in file COPYING for more details.      *
 *                                                                   *
 * You should have received a copy of the GNU General Public         *
 * License along with this program; if not, write to the Free        *
 * Software Foundation, Inc., 59 Temple Place - Suite 330,           *
 * Boston, MA 02111, USA.                                            *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _LIBERTY_H_
#define _LIBERTY_H_

#if 0 /* expanded by -frewrite-includes */
#include "gnugo.h"
#endif /* expanded by -frewrite-includes */
# 26 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/liberty.h"
# 27 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/liberty.h"

/* local versions of absolute value, min and max */

#define gg_abs(x) ((x) < 0 ? -(x) : (x))
#define gg_min(a, b) ((a)<(b) ? (a) : (b))
#define gg_max(a, b) ((a)<(b) ? (b) : (a))

/* Avoid compiler warnings with unused parameters */
#define UNUSED(x)  (void)x


/* ================================================================ */
/*                           public variables                       */
/* ================================================================ */


/* A few variables below are of types defined in hash.h. */
#if 0 /* expanded by -frewrite-includes */
#include "hash.h"
#endif /* expanded by -frewrite-includes */
# 44 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/liberty.h"
# 1 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/hash.h" 1
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * This is GNU GO, a Go program. Contact gnugo@gnu.org, or see       *
 * http://www.gnu.org/software/gnugo/ for more information.          *
 *                                                                   *
 * Copyright 1999, 2000, 2001, 2002 and 2003                         *
 * by the Free Software Foundation.                                  *
 *                                                                   *
 * This program is free software; you can redistribute it and/or     *
 * modify it under the terms of the GNU General Public License as    *
 * published by the Free Software Foundation - version 2             *
 *                                                                   *
 * This program is distributed in the hope that it will be useful,   *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of    *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     *
 * GNU General Public License in file COPYING for more details.      *
 *                                                                   *
 * You should have received a copy of the GNU General Public         *
 * License along with this program; if not, write to the Free        *
 * Software Foundation, Inc., 59 Temple Place - Suite 330,           *
 * Boston, MA 02111, USA.                                            *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if 0 /* expanded by -frewrite-includes */
#include <stdio.h>
#endif /* expanded by -frewrite-includes */
# 23 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/hash.h"
# 24 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/hash.h"
#if 0 /* expanded by -frewrite-includes */
#include "gnugo.h"
#endif /* expanded by -frewrite-includes */
# 24 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/hash.h"
# 25 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/hash.h"

/*
 * This file, together with engine/hash.c implements hashing of go positions
 * using a method known as Zobrist hashing.  See the Texinfo documentation
 * (Reading/Hashing) for more information.  
 */


#ifndef _HASH_H_
#define _HASH_H_

/* Hash values and the compact board representation should use the
 * longest integer type that the platform can handle efficiently.
 * Typically this would be a 32 bit integer on a 32 bit platform and a
 * 64 bit integer on a 64 bit platform.
 *
 * Our preliminary assumption is that unsigned long has this
 * characteristic. Should it turn out to be false for some platform
 * we'll add conditional code to choose some other type.
 *
 * At the few places in the code where the actual size of these types
 * matter, the code should use sizeof(type) to test for this. Notice
 * that ISO C guarantees a long to be at least 32 bits.
 *
 * On (future) platforms with word length 128 bits or more, it might
 * be a waste to use more than 64 bit hashvalues, since the decreased
 * risk for hash collisions probably isn't worth the increased storage
 * cost.
 */
typedef unsigned long Hashvalue;
typedef unsigned long Compacttype;

/* How many bits should be used at least for hashing? Set this to 32 for
 * some memory save and speedup, at the cost of occasional irreproducable
 * mistakes (and possibly assertion failures). 
 * With 64 bits, there should be less than one such mistake in 10^9 games.
 * Set this to 96 if this is not safe enough for you.
 */
#define MIN_HASHBITS 		64		

#define NUM_HASHVALUES 		(MIN_HASHBITS / ( 8 * SIZEOF_LONG))



/*
 * This struct is maintained by the machinery that updates the board
 * to provide incremental hashing. Examples: trymove(), play_move(), ...
 */

typedef struct {
  Hashvalue     hashval[NUM_HASHVALUES];
} Hash_data;


void hash_init(void);

void hashdata_recalc(Hash_data *hd, Intersection *board, int ko_pos);
int hashdata_compare(Hash_data *hd1, Hash_data *hd2);
void hashdata_invert_ko(Hash_data *hd, int pos);
void hashdata_invert_stone(Hash_data *hd, int pos, int color);
void hashdata_set_tomove(Hash_data *hd, int to_move);

int hashdata_diff_dump(Hash_data *key1, Hash_data *key2);

#endif
# 90 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/hash.h"


/*
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 2
 * End:
 */
# 45 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/liberty.h" 2

/* Other modules get read-only access to this variable. */
extern Hash_data    hashdata;



/* ================================================================ */


#define FALSE_EYE          1
#define HALF_EYE           2
#define INHIBIT_CONNECTION 4


/* A string with n stones can have at most 2(n+1) liberties. From this
 * follows that an upper bound on the number of liberties of a string
 * on a board of size N^2 is 2/3 (N^2+1).
 */
#define MAXLIBS   (2*(MAX_BOARD*MAX_BOARD + 1)/3)
/* This is a smaller, practical number of liberties that we care to keep track of. */
#define MAX_LIBERTIES 20


/* This is an upper bound of the number of strings that can exist on
 * the board simultaneously.  
 * FIXME: This is not sufficiently large;  above stackp==0, the incremental 
 *   board code doesn't necessarily re-use all indices.  This is a problem
 *   only in very pathological cases, and is extremely unlikely to occur in
 *   practice.
 */
#define MAX_STRINGS (2 * MAX_BOARD * MAX_BOARD / 3)

/* Per gf: Unconditional_life() can get very close to filling the 
 * entire board under certain circumstances. This was discussed in 
 * the list around August 21, 2001, in a thread with the subject 
 * "gnugo bug logs".
 */
#define MAXSTACK  MAX_BOARD * MAX_BOARD
#define MAXCHAIN  160

/* 1D board macros.
 * Note that POS(-1, -1) == 0
 * DELTA() is defined so that POS(i+di, j+dj) = POS(i, j) + DELTA(di, dj).
 */
#define BOARDSIZE     ((MAX_BOARD + 2) * (MAX_BOARD + 1) + 1)
#define BOARDMIN      (MAX_BOARD + 2)
#define BOARDMAX      (MAX_BOARD + 1) * (MAX_BOARD + 1)
#define POS(i, j)     ((MAX_BOARD + 2) + (i) * (MAX_BOARD + 1) + (j))
#define DELTA(di, dj) ((di) * (MAX_BOARD + 1) + (dj))
#define I(pos)        ((pos) / (MAX_BOARD + 1) - 1)
#define J(pos)        ((pos) % (MAX_BOARD + 1) - 1)
#define PASS_MOVE     0
#define NO_MOVE       PASS_MOVE
#define NS            (MAX_BOARD + 1)
#define WE            1
#define SOUTH(pos)    ((pos) + NS)
#define WEST(pos)     ((pos) - 1)
#define NORTH(pos)    ((pos) - NS)
#define EAST(pos)     ((pos) + 1)
#define SW(pos)       ((pos) + NS - 1)
#define NW(pos)       ((pos) - NS - 1)
#define NE(pos)       ((pos) - NS + 1)
#define SE(pos)       ((pos) + NS + 1)
#define SS(pos)       ((pos) + 2 * NS)
#define WW(pos)       ((pos) - 2)
#define NN(pos)       ((pos) - 2 * NS)
#define EE(pos)       ((pos) + 2)

#define BOARD(i, j)   board[POS(i, j)]

#define REVERSE_RESULT(result)		(WIN - result)

/* Transformation stuff. */
#define MAX_OFFSET			(2*MAX_BOARD - 1) * (2*MAX_BOARD - 1)
#define OFFSET(dx, dy)\
  ((dy + MAX_BOARD - 1) * (2*MAX_BOARD - 1) + (dx + MAX_BOARD - 1))
#define OFFSET_DELTA(dx, dy)		(OFFSET(dx, dy) - OFFSET(0, 0))
#define CENTER_OFFSET(offset)		(offset - OFFSET(0, 0))
#define TRANSFORM(offset, trans)	(transformation[offset][trans])
#define AFFINE_TRANSFORM(offset, trans, delta)\
  (transformation[offset][trans] + delta)
#define TRANSFORM2(x, y, tx, ty, trans)\
  do {\
    *tx = transformation2[trans][0][0] * (x) + transformation2[trans][0][1] * (y);\
    *ty = transformation2[trans][1][0] * (x) + transformation2[trans][1][1] * (y);\
  } while (0)


/* This struct holds the internal board state.
 */
struct board_state {
  int board_size;

  Intersection board[BOARDSIZE];
  int board_ko_pos;
  int black_captured;
  int white_captured;

  Intersection initial_board[BOARDSIZE];
  int initial_board_ko_pos;
  int initial_white_captured;
  int initial_black_captured;
  int move_history_color[MAX_MOVE_HISTORY];
  int move_history_pos[MAX_MOVE_HISTORY];
  int move_history_pointer;

  float komi;
  int move_number;
};


/* board utility functions */
int find_origin(int str);
int chainlinks(int str, int adj[MAXCHAIN]);
int chainlinks2(int str, int adj[MAXCHAIN], int lib);
int chainlinks3(int str, int adj[MAXCHAIN], int lib);
int extended_chainlinks(int str, int adj[MAXCHAIN], int both_colors);


/* This is increased by one anytime a move is (permanently) played or
 * the board is cleared.
 */
extern int position_number;


/* Detect vertex on edge. */
int is_edge_vertex(int pos);


/* Count and/or find liberties at (pos). */
int countlib(int str);
int findlib(int str, int maxlib, int *libs);
int fastlib(int pos, int color, int ignore_capture);
int approxlib(int pos, int color, int maxlib, int *libs);
int accuratelib(int pos, int color, int maxlib, int *libs);
int count_common_libs(int str1, int str2);
int find_common_libs(int str1, int str2, int maxlib, int *libs);
int have_common_lib(int str1, int str2, int *lib);


void start_timer(int n);
double time_report(int n, const char *occupation, int move, double mintime);

void update_random_seed(void);


/* Check for self atari. */
int is_self_atari(int pos, int color);

/* Count the number of stones in a string. */
int countstones(int str);
int findstones(int str, int maxstones, int *stones);

/* Exported from incremental_board.c so that reading.c can use it. */
void incremental_order_moves(int move, int color, int string,
			     int *number_edges, int *number_same_string,
			     int *number_own, int *number_opponent,
			     int *captured_stones, int *threatened_stones,
			     int *saved_stones, int *number_open);


void transformation_init(void);

  
void dump_stack(void);
void report_worm(int m, int n);
void ascii_report_worm(char *string);
void report_dragon(FILE *outfile, int pos);
void ascii_report_dragon(char *string);
struct dragon_data2 * dragon2_func(int pos);

/* prototypes for reorientation functions */

void rotate2(int i, int j, int *ri, int *rj, int rot);
void inv_rotate2(int i, int j, int *ri, int *rj, int rot);
int rotate1(int pos, int rot);
int inv_rotate1(int pos, int rot);

/* Is this point inside the board? */
#if 0
#define ON_BOARD2(i, j) ((i)>=0 && (j)>=0 && (i)<board_size && (j)<board_size)
#else
# 227 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/liberty.h"
/*
 * For the case when expr can only be slightly negative,
 *    if (expr < 0 || expr > something)
 * is equivalent to
 *    if ((unsigned) expr > something)
 *
 * (I think gcc knows this trick, but it does no harm to
 *  encode it explicitly since it saves typing !)
 */
#define ON_BOARD2(i, j) ((unsigned) (i) < (unsigned) board_size &&\
		         (unsigned) (j) < (unsigned) board_size)
#endif
# 239 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/liberty.h"

#define ASSERT_ON_BOARD2(i, j) ASSERT2(ON_BOARD2((i), (j)), (i), (j))

#define ON_BOARD1(pos) (((unsigned) (pos) < BOARDSIZE) && board[pos] != GRAY)
#define ON_BOARD(pos) (board[pos] != GRAY)
#define ASSERT_ON_BOARD1(pos) ASSERT1(ON_BOARD1(pos), (pos))

/* Coordinates for the eight directions, ordered
 * south, west, north, east, southwest, northwest, northeast, southeast.
 * Defined in utils.c.
 */
extern int deltai[8]; /* = { 1,  0, -1,  0,  1, -1, -1, 1}; */
extern int deltaj[8]; /* = { 0, -1,  0,  1, -1, -1,  1, 1}; */
extern int delta[8];  /* = { NS, -1, -NS, 1, NS-1, -NS-1, -NS+1, NS+1}; */

void store_board(struct board_state *state);
void restore_board(struct board_state *state);

/* Forward struct declarations. */
struct pattern;
struct pattern_db;
struct fullboard_pattern;
struct corner_pattern;
struct corner_db;
struct half_eye_data;
struct movelist;
struct tree_node_list;
struct match_node;

/*
 * Try to match a pattern in the database to the board. Callback for
 * each match
 */
typedef void (*matchpat_callback_fn_ptr)(int anchor, int color,
                                         struct pattern *, int rotation,
                                         void *data);
typedef void (*fullboard_matchpat_callback_fn_ptr)(int move,
                                                   struct fullboard_pattern *,
                                                   int rotation);
typedef void (*corner_matchpat_callback_fn_ptr)(int move, int color,
						struct corner_pattern *pattern,
						int rotation);
void matchpat(matchpat_callback_fn_ptr callback, int color,
	      struct pattern_db *pdb, void *callback_data,
	      char goal[BOARDMAX]);
void matchpat_goal_anchor(matchpat_callback_fn_ptr callback, int color,
	      struct pattern_db *pdb, void *callback_data,
	      char goal[BOARDMAX], int anchor_in_goal);
void fullboard_matchpat(fullboard_matchpat_callback_fn_ptr callback,
			int color, struct fullboard_pattern *pattern);
void corner_matchpat(corner_matchpat_callback_fn_ptr callback, int color,
		     struct corner_db *database);
void dfa_match_init(void);
void tree_match_init(void);
void tree_initialize_pointers(struct tree_node_list *tnl,
                              struct match_node *matches,
                              int tnl_size,
                              int matches_size);

void reading_cache_init(void);
void reading_cache_clear(void);

/* reading.c */
int attack(int str, int *move);
int find_defense(int str, int *move);
int attack_and_defend(int str,
		      int *attack_code, int *attack_point,
		      int *defend_code, int *defense_point);
int attack_either(int astr, int bstr);
int defend_both(int astr, int bstr);
int break_through(int apos, int bpos, int cpos);
int attack_threats(int pos, int max_points, int moves[], int codes[]);

int simple_ladder(int str, int *move);
#define MOVE_ORDERING_PARAMETERS 67
void tune_move_ordering(int params[MOVE_ORDERING_PARAMETERS]);
void draw_reading_shadow(void);

/* persistent.c */
void purge_persistent_reading_cache(void);
void clear_persistent_reading_cache(void);
int search_persistent_reading_cache(int routine, int str, int *result,
				    int *move);
void store_persistent_reading_cache(int routine, int str, int result,
				    int move, int nodes);
void delete_persistent_reading_cache_entry(int routine, int str);
void reading_hotspots(float values[BOARDMAX]);
void purge_persistent_owl_cache(void);
void clear_persistent_owl_cache(void);
int search_persistent_owl_cache(int routine, int apos, int bpos, int cpos,
				int *result, int *move, int *move2,
				int *certain);
void store_persistent_owl_cache(int routine, int apos, int bpos, int cpos,
				int result, int move, int move2, int certain,
				int tactical_nodes, char goal[BOARDMAX],
				int goal_color);
void owl_hotspots(float values[BOARDMAX]);

/* readconnect.c */
int string_connect(int str1, int str2, int *move);
int disconnect(int str1, int str2, int *move);
int non_transitivity(int str1, int str2, int str3, int *move);

/* board.c */
int liberty_of_string(int pos, int str);
int second_order_liberty_of_string(int pos, int str);
int neighbor_of_string(int pos, int str);
int has_neighbor(int pos, int color);
int same_string(int str1, int str2);
int adjacent_strings(int str1, int str2);
int is_ko(int pos, int color, int *ko_pos);
int is_ko_point(int pos);
int komaster_trymove(int pos, int color,
		     const char *message, int str,
		     int komaster, int kom_pos,
		     int *new_komaster, int *new_kom_pos,
		     int *is_conditional_ko, int consider_conditional_ko);
int does_capture_something(int pos, int color);
void mark_string(int str, char mx[BOARDMAX], char mark);
int move_in_stack(int pos, int cutoff);
void get_move_from_stack(int k, int *move, int *color);
int stones_on_board(int color);

int obvious_false_eye(int pos, int color);
int owl_topological_eye(int pos, int color);
int vital_chain(int pos);
int confirm_safety(int move, int color, int *defense_point,
		   char safe_stones[BOARDMAX]);
float blunder_size(int move, int color, int *defense_point,
		   char safe_stones[BOARDMAX]);
void set_depth_values(int level);
void modify_depth_values(int n);
void increase_depth_values(void);
void decrease_depth_values(void);
void set_temporary_depth_values(int d, int b, int f, int k, 
				int br, int b2, int ss);
void restore_depth_values(void);

int safe_move(int move, int color);

void join_dragons(int d1, int d2);
int dragon_escape(char goal[BOARDMAX], int color, char escape_value[BOARDMAX]);
void compute_refined_dragon_weaknesses(void);
struct eyevalue;
float crude_dragon_weakness(int safety, struct eyevalue *genus, int has_lunch,
			    float moyo_value, float escape_route);
int is_same_dragon(int d1, int d2);
int are_neighbor_dragons(int d1, int d2);
int first_worm_in_dragon(int w);
int next_worm_in_dragon(int w);
int lively_dragon_exists(int color);
void compute_dragon_influence(void);
void set_strength_data(int color, char safe_stones[BOARDMAX],
		       float strength[BOARDMAX]);

void get_lively_stones(int color, char safe_stones[BOARDMAX]);
int is_same_worm(int w1, int w2);
int is_worm_origin(int w, int pos);
void propagate_worm(int pos);
void transform2(int i, int j, int *ti, int *tj, int trans);
void find_cuts(void);
void find_connections(void);
void modify_eye_spaces(void);

/* movelist.c */
int movelist_move_known(int move, int max_points, int points[], int codes[]);
void movelist_change_point(int move, int code, int max_points, 
			   int points[], int codes[]);

/* safety.c */
int compute_surroundings(int pos, int apos, int showboard,
			 int *surround_size);
int is_surrounded(int pos);
int does_surround(int move, int dragon);
void reset_surround_data(void);
int surround_map(int dr, int pos);

/* functions to add (or remove) move reasons */
void clear_move_reasons(void);
void add_lunch(int eater, int food);
void remove_lunch(int eater, int food);
void add_attack_move(int pos, int ww, int code);
void add_defense_move(int pos, int ww, int code);
void add_attack_threat_move(int pos, int ww, int code);
void remove_attack_threat_move(int pos, int ww);
void add_defense_threat_move(int pos, int ww, int code);
void add_connection_move(int pos, int dr1, int dr2);
void add_cut_move(int pos, int dr1, int dr2);
void add_antisuji_move(int pos);
void add_semeai_move(int pos, int dr);
void add_semeai_threat(int pos, int dr);

void add_owl_attack_move(int pos, int dr, int code);
void add_owl_defense_move(int pos, int dr, int code);
void add_owl_attack_threat_move(int pos, int dr, int code);
void add_owl_defense_threat_move(int pos, int dr, int code);
void add_owl_prevent_threat_move(int pos, int dr);
void add_owl_uncertain_defense_move(int pos, int dr);
void add_owl_uncertain_attack_move(int pos, int dr);

void add_my_atari_atari_move(int pos, int size);
void add_your_atari_atari_move(int pos, int size);
void add_vital_eye_move(int pos, int eyespace, int color);
void add_invasion_move(int pos);
void add_expand_territory_move(int pos);
void add_expand_moyo_move(int pos);
void add_strategical_attack_move(int pos, int dr);
void add_strategical_defense_move(int pos, int dr);
void add_worthwhile_threat_move(int pos);
void add_replacement_move(int from, int to);
int  set_minimum_move_value(int pos, float value);
void set_maximum_move_value(int pos, float value);
void set_minimum_territorial_value(int pos, float value);
void set_maximum_territorial_value(int pos, float value);
void add_shape_value(int pos, float value);
void add_followup_value(int pos, float value);
void add_reverse_followup_value(int pos, float value);
void record_top_move(int move, float val);
void remove_top_move(int move);
void scale_randomness(int pos, float scaling);

/* Parameters to add_either_move and add_all_move */
#define ATTACK_STRING  1
#define DEFEND_STRING  2
void add_either_move(int pos, int reason1, int target1,
		     int reason2, int target2);
void add_all_move(int pos, int reason1, int target1,
		  int reason2, int target2);

void add_gain_move(int pos, int target1, int target2);
void add_loss_move(int pos, int target1, int target2);


int get_attack_threats(int pos, int max_strings, int strings[]);
int get_defense_threats(int pos, int max_strings, int strings[]);
void get_saved_worms(int pos, char saved[BOARDMAX]);
void get_saved_dragons(int pos, char saved[BOARDMAX]);
void mark_safe_stones(int color, int move_pos,
		      const char saved_dragons[BOARDMAX],
		      const char saved_worms[BOARDMAX],
		      char safe_stones[BOARDMAX]);


int owl_lively(int pos);
int owl_escape_value(int pos);
int owl_goal_dragon(int pos);
int owl_eyespace(int pos);
int owl_big_eyespace(int pos);
int owl_proper_eye(int pos);
int owl_eye_size(int pos);
int owl_strong_dragon(int pos);
void owl_reasons(int color);

void unconditional_life(int unconditional_territory[BOARDMAX], int color);
void find_superstring(int str, int *num_stones, int *stones);
void find_superstring_conservative(int str, int *num_stones, int *stones);
void find_superstring_liberties(int str, int *liberties, int *libs,
                                int liberty_cap);
void find_proper_superstring_liberties(int str, int *liberties, int *libs, 
                                       int liberty_cap);
void find_superstring_stones_and_liberties(int str, int *num_stones,
					   int *stones, int *liberties,
					   int *libs, int liberty_cap);
void superstring_chainlinks(int str, int *num_adj, int adj[MAXCHAIN],
                            int liberty_cap);
void proper_superstring_chainlinks(int str, int *num_adj, 
                                   int adj[MAXCHAIN], int liberty_cap);

int place_fixed_handicap(int handicap); /* place stones on board only */
int place_free_handicap(int handicap); /* place stones on board only */
int free_handicap_remaining_stones(void);
int free_handicap_total_stones(void);


/* Various different strategies for finding a move */
void fuseki(int color);
void semeai(int color);
void new_semeai(int color);
void shapes(int color);
void endgame_shapes(int color);

void combinations(int color);
int atari_atari(int color, int *attack_move, char defense_moves[BOARDMAX],
		int save_verbose);
int atari_atari_confirm_safety(int color, int tpos, int *move, int minsize,
			       const char saved_dragons[BOARDMAX],
			       const char saved_worms[BOARDMAX]);

int atari_atari_blunder_size(int color, int tpos, int *move,
			     const char safe_stones[BOARDMAX]);

int review_move_reasons(int *move, float *val, int color,
			float pure_threat_value, float lower_bound,
			int allowed_moves[BOARDMAX]);
int fill_liberty(int *move, int color);
int aftermath_genmove(int *aftermath_move, int color,
		      int under_control[BOARDMAX],
		      int do_capture_dead_stones);

int owl_attack(int target, int *attack_point, int *certain, int *kworm);
int owl_defend(int target, int *defense_point, int *certain, int *kworm);
int owl_threaten_attack(int target, int *attack1, int *attack2);
int owl_threaten_defense(int target, int *defend1, int *defend2);
int owl_does_defend(int move, int target, int *kworm);
int owl_confirm_safety(int move, int target, int *defense_point, int *kworm);
int owl_does_attack(int move, int target, int *kworm);
int owl_connection_defends(int move, int target1, int target2);
int owl_substantial(int str);
void owl_analyze_semeai(int apos, int bpos, 
			int *resulta, int *resultb, int *move,
			int owl);

int genmove_restricted(int *i, int *j, int color, int allowed_moves[BOARDMAX]);

void change_attack(int str, int move, int acode);
void change_defense(int str, int move, int dcode);
void change_attack_threat(int str, int move, int acode);
void change_defense_threat(int str, int move, int dcode);
int attack_move_known(int move, int str);
int defense_move_known(int move, int str);
int attack_threat_move_known(int move, int str);
int defense_threat_move_known(int move, int str);
void worm_reasons(int color);

int does_attack(int move, int str);
int does_defend(int move, int str);
int double_atari(int move, int color, float *value,
		 char safe_stones[BOARDMAX]);
int play_attack_defend_n(int color, int do_attack, int num_moves, ...);
int play_attack_defend2_n(int color, int do_attack, int num_moves, ...);
int play_break_through_n(int color, int num_moves, ...);
int play_connect_n(int color, int do_connect, int num_moves, ...);
int cut_possible(int pos, int color);
int defend_against(int move, int color, int apos);
int somewhere(int color, int check_alive, int num_moves, ...);
int visible_along_edge(int color, int apos, int bpos);

/* Printmoyo values, specified by -m flag. */
#define PRINTMOYO_TERRITORY         0x01
#define PRINTMOYO_MOYO              0x02
#define PRINTMOYO_AREA              0x04
/* The following have been borrowed by the influence functions below. */
#define PRINTMOYO_INITIAL_INFLUENCE 0x08
#define PRINTMOYO_PRINT_INFLUENCE   0x10
#define PRINTMOYO_NUMERIC_INFLUENCE 0x20
#define PRINTMOYO_PERMEABILITY      0x40
#define PRINTMOYO_STRENGTH          0x80
#define PRINTMOYO_ATTENUATION       0x100
#define PRINTMOYO_VALUE_TERRITORY   0x200

/* These values are used to communicate whether stones are safe or
 * have been saved, when computing influence.
 */
#define INFLUENCE_SAFE_STONE	1
#define INFLUENCE_SAVED_STONE	2

/* These values are used to communicate the status of stones when analyzing
 * a move for potentially being a blunder.
 */
/* 	dead		0 */
#define SAFE_STONE 	1
#define OWL_SAVED_STONE	2

/* This format is used when exporting the moyo segmentation. */
#define MAX_MOYOS MAX_BOARD*MAX_BOARD

struct moyo_data
{
  int number; /* Number of moyos. */
  int segmentation[BOARDMAX]; /* Numbers the moyos. */
  int size[MAX_MOYOS];
  int owner[MAX_MOYOS];
  float territorial_value[MAX_MOYOS];
};

/* We use a forward declaration of influence_data so that the rest
 * of the engine can reference influence data. It can only be accessed
 * in influence.c, however!
 */
struct influence_data;
extern struct influence_data initial_black_influence;
extern struct influence_data initial_white_influence;
extern struct influence_data move_influence;
extern struct influence_data followup_influence;

#define INITIAL_INFLUENCE(color) ((color) == WHITE ? \
				    &initial_white_influence \
				  : &initial_black_influence)
#define OPPOSITE_INFLUENCE(color) (INITIAL_INFLUENCE(OTHER_COLOR(color)))

#define DEFAULT_STRENGTH 100.0

/* Influence functions. */
void compute_influence(int color, const char safe_stones[BOARDMAX],
		       const float strength[BOARDMAX],
		       struct influence_data *q,
		       int move, const char *trace_message);
void compute_followup_influence(const struct influence_data *base,
			        struct influence_data *q, 
		                int move, const char *trace_message);
void compute_escape_influence(int color, const char safe_stones[BOARDMAX],
			      const float strength[BOARDMAX],
                              char escape_value[BOARDMAX]);

float influence_delta_territory(const struct influence_data *base,
	                        const struct influence_data *q, int color,
				int move);
int retrieve_delta_territory_cache(int pos, int color, float *move_value,
			           float *followup_value);
void store_delta_territory_cache(int pos, int color, float move_value,
				 float followup_value);

int whose_territory(const struct influence_data *q, int pos);
int whose_moyo(const struct influence_data *q, int pos);
int whose_area(const struct influence_data *q, int pos);
float influence_territory(const struct influence_data *q, int pos, int color);
void influence_get_moyo_segmentation(const struct influence_data *q,
	       			     struct moyo_data *moyo);
void influence_get_moyo_data(const struct influence_data *q,
			     int moyo_color[BOARDMAX],
			     float territory_value[BOARDMAX]);
void resegment_initial_influence(void);
void influence_mark_non_territory(int pos, int color);

float estimate_score(float *upper, float *lower);

/* Eye space functions. */
int is_eye_space(int pos);
int is_proper_eye_space(int pos);
int is_marginal_eye_space(int pos);
int max_eye_value(int pos);
void test_eyeshape(int eyesize, int *eye_vertices);


/* debugging support */
void goaldump(char goal[BOARDMAX]);
void move_considered(int move, float value);


/* SGF routines for debugging purposes in sgffile.c */
void sgffile_begindump(struct SGFTree_t *tree);
void sgffile_enddump(const char *filename);



/* ================================================================ */
/*                         global variables                         */
/* ================================================================ */

/* The board and the other parameters deciding the current position. */
extern int          board_size;             /* board size (usually 19) */
extern Intersection board[BOARDSIZE];       /* go board */
extern int          board_ko_pos;
extern int          black_captured;   /* num. of black stones captured */
extern int          white_captured;

extern Intersection initial_board[BOARDSIZE];
extern int          initial_board_ko_pos;
extern int          initial_white_captured;
extern int          initial_black_captured;
extern int          move_history_color[MAX_MOVE_HISTORY];
extern int          move_history_pos[MAX_MOVE_HISTORY];
extern int          move_history_pointer;

extern float        komi;
extern int          movenum;      /* movenumber - used for debug output */
		    
extern Intersection shadow[BOARDMAX];      /* reading tree shadow */

		    
extern int          disable_threat_computation;
extern int          disable_endgame_patterns;
extern int          doing_scoring;

/* Transformation arrays */
extern int	    transformation[MAX_OFFSET][8];
extern const int    transformation2[8][2][2];

/* Reading parameters */
extern int depth;               /* deep reading cutoff */
extern int backfill_depth;      /* deep reading cutoff */
extern int backfill2_depth;     /* deep reading cutoff */
extern int superstring_depth;   /* deep reading cutoff */
extern int branch_depth;        /* deep reading cutoff */
extern int fourlib_depth;       /* deep reading cutoff */
extern int ko_depth;            /* deep ko reading cutoff */
extern int aa_depth;            /* deep global reading cutoff */
extern int owl_distrust_depth;  /* below this owl trusts the optics code */
extern int owl_branch_depth;    /* below this owl tries only one variation */
extern int owl_reading_depth;   /* owl does not read below this depth */
extern int owl_node_limit;      /* maximum number of nodes considered */
extern int level;               /* controls the strength of play */
extern int semeai_variations;   /* max variations considered reading semeai */
extern float best_move_values[10];
extern int best_moves[10];

extern int chinese_rules;
extern int experimental_owl_ext;     /* use experimental owl (GAIN/LOSS) */
extern int experimental_semeai;      /* use experimental semeai module */
extern int experimental_connections; /* use experimental connection module */
extern int alternate_connections;    /* use alternate connection module */
extern int owl_threats;              /* compute owl threats */
extern int experimental_influence;   /* use experimental influence module */

extern int thrashing_dragon; /* Dead opponent's dragon trying to live */

/* Experimental reading */
extern char *rgoal;
extern int goallib;

extern int stackp;                /* stack pointer */
extern int count_variations;      /* count (decidestring) */
extern SGFTree *sgf_dumptree;

/* Arrays pointing out the closest worms from each vertex.  The first
 * one is the closest worms of either color, the last two ones ignore
 * worms of the other color.  Beyond a certain distance from any worm
 * no close worm is listed at all.  Only the closest worm is listed
 * and if more than one are equally close they are all listed. The
 * number of equally close worms is given in the number_*_worms
 * arrays. If more than MAX_CLOSE_WORMS are equally close, none is
 * listed.
 *
 * See compute_effective_worm_sizes() in worm.c for details.
 */
#define MAX_CLOSE_WORMS 4
extern int close_worms[BOARDMAX][MAX_CLOSE_WORMS];
extern int number_close_worms[BOARDMAX];
extern int close_black_worms[BOARDMAX][MAX_CLOSE_WORMS];
extern int number_close_black_worms[BOARDMAX];
extern int close_white_worms[BOARDMAX][MAX_CLOSE_WORMS];
extern int number_close_white_worms[BOARDMAX];

extern int false_eye_territory[BOARDMAX];

struct stats_data {
  int nodes;                     /* Number of visited nodes while reading */
  int position_entered;          /* Number of Positions entered. */
  int position_hits;             /* Number of hits of Positions. */
  int read_result_entered;       /* Number of Read_results entered. */
  int read_result_hits;          /* Number of hits of Read_results. */
  int hash_collisions;           /* Number of hash collisions. */
};

extern struct stats_data stats;


struct eyevalue {
#if 0
  char maxeye;       /* number of eyes if defender plays first               */
  char mineye;       /* number of eyes if attacker plays first               */
#else
# 791 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/liberty.h"
  unsigned char a; /* number of eyes if attacker plays first twice */
  unsigned char b; /* number of eyes if attacker plays first */
  unsigned char c; /* number of eyes if defender plays first */
  unsigned char d; /* number of eyes if defender plays first twice */
#endif
# 796 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/liberty.h"
};


struct half_eye_data {
  float value;          /* Topological eye value. */
  char type;            /* HALF_EYE or FALSE_EYE; */
  int num_attacks;      /* number of attacking points */
  int attack_point[4];  /* the moves to attack a topological halfeye */
  int num_defends;      /* number of defending points */
  int defense_point[4]; /* the moves to defend a topological halfeye */
};

/* array of half-eye data */
extern struct half_eye_data half_eye[BOARDMAX];

/*
 * data concerning a worm. A copy is kept at each vertex of the worm.
 */

#define MAX_TACTICAL_POINTS 10

struct worm_data {
  int color;         /* its color */
  int size;          /* its cardinality */
  float effective_size; /* stones and surrounding spaces */
  int origin;        /* the origin of the string. Two vertices are in */
                     /* the same worm iff they have same origin. */
  int liberties;     /* number of liberties */
  int liberties2;    /* number of second order liberties */
  int liberties3;    /* third order liberties (empty vertices at distance 3) */
  int liberties4;    /* fourth order liberties */
  int lunch;         /* if lunch != 0 then lunch points to a boundary */
                     /* worm which can be captured easily. */
  int cutstone;      /* 1=potential cutting stone; 2=cutting stone */
  int cutstone2;     /* Number of potential cuts involving the worm. */
  int genus;         /* number of connected components of the complement, less one */
  int inessential;   /* 1=inessential worm */
  int invincible;    /* 1=strongly unconditionally non-capturable */
  int unconditional_status; /* ALIVE, DEAD, WHITE_BORDER, BLACK_BORDER, UNKNOWN */

  /* The following arrays keeps track of up to MAX_TACTICAL_POINTS
   * different attack, defense, attack threat, and defense threat
   * points with corresponding result codes. (0 = loss, 1 = bad ko, 2
   * = good ko, 3 = win). The arrays are guaranteed to be sorted with
   * respect to the codes so that the first element contains the best
   * result.
   */
  int attack_points[MAX_TACTICAL_POINTS];
  int attack_codes[MAX_TACTICAL_POINTS];
  int defense_points[MAX_TACTICAL_POINTS];
  int defense_codes[MAX_TACTICAL_POINTS];
  int attack_threat_points[MAX_TACTICAL_POINTS];
  int attack_threat_codes[MAX_TACTICAL_POINTS]; 
  int defense_threat_points[MAX_TACTICAL_POINTS];
  int defense_threat_codes[MAX_TACTICAL_POINTS];
};

extern struct worm_data worm[BOARDMAX];

/* Surround cache (see surround.c) */

#define MAX_SURROUND 10

struct surround_data {
  int dragon_number;           /* number of the (surrounded) beast */
  char surround_map[BOARDMAX]; /* surround map                     */
};

extern struct surround_data surroundings[MAX_SURROUND];
extern int surround_pointer;

/*
 * data concerning a dragon. A copy is kept at each stone of the string.
 */

struct dragon_data {
  int color;    /* its color                                                 */
  int id;       /* the index into the dragon2 array                          */
  int origin;   /* the origin of the dragon. Two vertices are in the same    */
                /* dragon iff they have same origin.                         */
  int size;     /* size of the dragon                                        */
  float effective_size; /* stones and surrounding spaces                     */
  int crude_status;   /* (ALIVE, DEAD, UNKNOWN, CRITICAL)                    */
  int owl_threat_status;   /* CAN_THREATEN_ATTACK or CAN_THREATEN_DEFENSE    */
  int owl_status;          /* (ALIVE, DEAD, UNKNOWN, CRITICAL, UNCHECKED)    */
  int owl_attack_point;    /* vital point for attack                         */
  int owl_attack_code;     /* ko result code                                 */
#if 0
  int owl_attack_points[MAX_TACTICAL_POINTS];
  int owl_attack_codes[MAX_TACTICAL_POINTS];
#endif
# 887 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/liberty.h"
  int owl_attack_certain;  /* 0 if owl reading node limit is reached         */
  int owl_second_attack_point;/* if attacker gets both attack points, wins   */
  int owl_defense_point;   /* vital point for defense                        */
  int owl_defense_code;    /* ko result code                                 */
  int owl_defense_certain; /* 0 if owl reading node limit is reached         */
  int owl_second_defense_point;/* if defender gets both attack points, wins  */
  int status;              /* best trusted status                            */
  int owl_attack_kworm;    /* only valid when owl_attack_code is GAIN        */
  int owl_defense_kworm;   /* only valid when owl_defense_code is LOSS       */
};

extern struct dragon_data dragon[BOARDMAX];

/* Supplementary data concerning a dragon. Only one copy is stored per
 * dragon in the dragon2 array.
 */

#define MAX_NEIGHBOR_DRAGONS 10

struct dragon_data2 {
  int origin;                         /* the origin of the dragon            */
  int adjacent[MAX_NEIGHBOR_DRAGONS]; /* adjacent dragons                    */
  int neighbors;                      /* number of adjacent dragons          */
  int hostile_neighbors;              /* neighbors of opposite color         */
  int moyo_size;		      /* size of surrounding influence moyo, */
  float moyo_territorial_value;       /* ...and its territorial value */
  int safety;                         /* a more detailed status estimate     */
  float weakness; /* A new (3.3.x) continuos estimate of the dragon's safety */
  float weakness_pre_owl;     /* Dragon safety based on pre-owl computations */
  int escape_route; /* a measurement of likelihood of escape                 */
  struct eyevalue genus;    /* the number of eyes (approximately)            */
  int heye;     /* coordinates of a half eye                                 */
  int lunch;    /* if lunch != 0 then lunch points to a boundary worm which  */
                /* can be captured easily.                                   */
  int semeai;          /* true if a dragon is part of a semeai               */
  int semeai_margin_of_safety; /* if small, the semeai is close              */
  int surround_status;         /* Is it surrounded?                          */
  int surround_size;           /* Size of the surrounding area               */
};

/* dragon2 is dynamically allocated */
extern int number_of_dragons;
extern struct dragon_data2 *dragon2;

/* Macros for accessing the dragon2 data with board coordinates and
 * the dragon data with a dragon id.
 */
#if 1 /* Trust DRAGON2 accesses */
#define DRAGON2(pos) dragon2[dragon[pos].id]
#else
# 937 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/liberty.h"
struct dragon_data2 * dragon2_func(int pos);
#define DRAGON2(pos) (*dragon2_func(pos))
#endif
# 940 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/liberty.h"

#define DRAGON(d) dragon[dragon2[d].origin]

struct aftermath_data {
  int white_captured;
  int black_captured;
  int white_prisoners;
  int black_prisoners;
  int white_territory;
  int black_territory;
  int white_area;
  int black_area;
  int white_control[BOARDMAX];
  int black_control[BOARDMAX];
  int final_status[BOARDMAX];
};

struct eye_data {
  int color;/* BLACK, WHITE, BLACK_BORDERED, WHITE_BORDERED or GRAY_BORDERED */
  int esize;         /* size of the eyespace                                 */
  int msize;         /* number of marginal vertices                          */
  int origin;        /* The origin                                           */
  struct eyevalue value; /* Number of eyes.                                  */
  int attack_point;  /* vital point for attack                               */
  int defense_point; /* vital point for defense                              */

  /* The above fields are constant on the whole eyespace. */
  /* ---------------------------------------------------------------- */
  /* The below fields are not. */

  char marginal;             /* This vertex is marginal                    */
  char type;                 /* Various characteristics of the eyespace    */
  char neighbors;            /* number of neighbors in eyespace            */
  char marginal_neighbors;   /* number of marginal neighbors               */
  char cut;                  /* Opponent can cut at vertex.                */
};

extern struct eye_data white_eye[BOARDMAX];
extern struct eye_data black_eye[BOARDMAX];

/* The following declarations have to be postponed until after the
 * definition of struct eye_data or struct half_eye_data.
 */

void compute_eyes(int pos, struct eyevalue *value,
                  int *attack_point, int *defense_point,
                  struct eye_data eye[BOARDMAX],
                  struct half_eye_data heye[BOARDMAX],
                  int add_moves, int color);
void compute_eyes_pessimistic(int pos, struct eyevalue *value,
                              int *pessimistic_min,
                              int *attack_point, int *defense_point,
                              struct eye_data eye[BOARDMAX],
                              struct half_eye_data heye[BOARDMAX]);
void propagate_eye(int pos, struct eye_data eye[BOARDMAX]);
int find_eye_dragons(int origin, struct eye_data eye[BOARDMAX], int eye_color,
		     int dragons[], int max_dragons);
float topological_eye(int pos, int color,
		      struct eye_data my_eye[BOARDMAX],
		      struct half_eye_data heye[BOARDMAX]);
void add_false_eye(int pos, struct eye_data eye[BOARDMAX], 
		   struct half_eye_data heye[BOARDMAX]);
void make_domains(struct eye_data b_eye[BOARDMAX],
                  struct eye_data w_eye[BOARDMAX],
		  int owl_call);
void find_half_and_false_eyes(int color, struct eye_data eye[BOARDMAX],
			      struct half_eye_data heye[BOARDMAX],
			      char find_mask[BOARDMAX]);

void set_eyevalue(struct eyevalue *e, int a, int b, int c, int d);
int min_eye_threat(struct eyevalue *e);
int min_eyes(struct eyevalue *e);
int max_eyes(struct eyevalue *e);
int max_eye_threat(struct eyevalue *e);
void add_eyevalues(struct eyevalue *e1, struct eyevalue *e2,
		   struct eyevalue *sum);
int eye_move_urgency(struct eyevalue *e);
char *eyevalue_to_string(struct eyevalue *e);

int is_halfeye(struct half_eye_data heye[BOARDMAX], int pos);
int is_false_eye(struct half_eye_data heye[BOARDMAX], int pos);

/* Our own abort() which prints board state on the way out.
 * (i, j) is a "relevant" board position for info. */
void abortgo(const char *file, int line, const char *msg, int i, int j);

#if GG_TURN_OFF_ASSERTS
#define ASSERT2(x, i, j)
#define ASSERT1(x, pos)
#else
# 1030 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/liberty.h"
/* avoid dangling else */
/* FIXME: Should probably re-write these using do {...} while (0) idiom. */
#define ASSERT2(x, i, j) if (x) ; else abortgo(__FILE__, __LINE__, #x, i, j)
#define ASSERT1(x, pos) if (x) ; else abortgo(__FILE__, __LINE__, #x, I(pos), J(pos))
#endif
# 1035 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/liberty.h"

#define gg_assert(x) ASSERT2(x, -1, -1);

#endif  /* _LIBERTY_H_ */
# 1039 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/liberty.h"


/*
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 2
 * End:
 */
# 29 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/semeai.c" 2

#define INFINITY 1000

static void analyze_semeai(int my_dragon, int your_dragon);
static void add_appropriate_semeai_moves(int move, 
					 int my_dragon, int your_dragon, 
					 int my_status, int your_status,
					 int margin_of_safety);
static void update_status(int dr, int new_status, int new_safety);


/* semeai() searches for pairs of dragons of opposite color which
 * have safety DEAD. If such a pair is found, analyze_semeai is
 * called to determine which dragon will prevail in a semeai, and
 * whether a move now will make a difference in the outcome. The
 * dragon statuses are revised, and if a move now will make a
 * difference in the outcome, an owl reason is generated.
 */

void
semeai(int color)
{
  int d1, d2;
  int k;
  int apos = NO_MOVE;
  int bpos = NO_MOVE;
  int other = OTHER_COLOR(color);

  TRACE("Semeai Player is THINKING for %s!\n", 
	color_to_string(color));

  for (d1 = 0; d1 < number_of_dragons; d1++) {
    if (DRAGON(d1).color != color
	|| (DRAGON(d1).status != DEAD
	    && DRAGON(d1).status != CRITICAL))
      continue;

    for (k = 0; k < dragon2[d1].neighbors; k++) {
      d2 = dragon2[d1].adjacent[k];
      if (DRAGON(d2).color != other
	  || (DRAGON(d2).status != DEAD
	      && DRAGON(d2).status != CRITICAL))
	continue;

      /* Dragons d1 (our) and d2 (opponent) are adjacent and both DEAD
       * or CRITICAL.
       */
      apos = DRAGON(d1).origin;
      bpos = DRAGON(d2).origin;

      /* Ignore inessential worms or dragons */
      if (worm[apos].inessential 
	  || DRAGON2(apos).safety == INESSENTIAL
	  || worm[bpos].inessential 
	  || DRAGON2(bpos).safety == INESSENTIAL)
	continue;

      analyze_semeai(apos, bpos);      
    }
  }
}


/* Experimental alternative to semeai() using owl reading */

void
new_semeai(int color)
{
  int d1, d2;
  int k;
  int apos = NO_MOVE;
  int bpos = NO_MOVE;
  int other = OTHER_COLOR(color);
  int best_result_a[MAX_NEIGHBOR_DRAGONS];
  int best_result_b[MAX_NEIGHBOR_DRAGONS];
  int worst_result_a[MAX_NEIGHBOR_DRAGONS];
  int worst_result_b[MAX_NEIGHBOR_DRAGONS];
  int a_best_status = UNKNOWN;  /* status if a plays first */
  int b_worst_status = UNKNOWN; /* status if a plays first */
  int a_worst_status = UNKNOWN; /* status if b plays first */
  int b_best_status = UNKNOWN;  /* status if b plays first */

  int move[MAX_NEIGHBOR_DRAGONS];
  int a_status = UNKNOWN;
  int b_status = UNKNOWN;
  int pass;

  TRACE("Experimental Semeai Module is THINKING for %s!\n", 
	color_to_string(color));
  
  for (d1 = 0; d1 < number_of_dragons; d1++) {
    int semeai_found = 0;
    if (DRAGON(d1).color != color
	|| (DRAGON(d1).status != DEAD
	    && DRAGON(d1).status != CRITICAL))
      continue;
    
    /* First pass : collect data
     * Second pass: update statuses
     */
    
    for (k = 0; k < dragon2[d1].neighbors; k++) {
      best_result_a[k] = DEAD;
      worst_result_b[k] = ALIVE;
      move[k] = NO_MOVE;
    }

    for (pass = 0; pass < 2; pass ++) {
      for (k = 0; k < dragon2[d1].neighbors; k++) {
	d2 = dragon2[d1].adjacent[k];
	if (DRAGON(d2).color != other
	    || (DRAGON(d2).status != DEAD
		&& DRAGON(d2).status != CRITICAL))
	  continue;
	
	/* Dragons d1 (our) and d2 (opponent) are adjacent and both DEAD
	 * or CRITICAL.
	 */
	apos = DRAGON(d1).origin;
	bpos = DRAGON(d2).origin;
	
	/* The following is something we want to do but
	 * better wait until we have the semeai stuff working
	 * with ko. See nicklas2 test 1401.
	 */
#if 0
	if (DRAGON(d1).status == CRITICAL
	    && DRAGON(d2).status == DEAD) {
	  update_status(bpos, CRITICAL, CRITICAL);
	  add_owl_attack_move(dragon[apos].owl_attack_point,
			      bpos, WIN);
	  continue;
	}
#endif
# 163 "/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/semeai.c"

	/* Ignore inessential worms or dragons */
	if (worm[apos].inessential 
	    || DRAGON2(apos).safety == INESSENTIAL
	    || worm[bpos].inessential 
	    || DRAGON2(bpos).safety == INESSENTIAL)
	  continue;
	
	/* A dragon consisting of a single worm which is tactically dead or
	 * critical and having just one neighbor should be ignored.
	 */
	if (dragon[apos].size == worm[apos].size
	    && worm[apos].attack_codes[0] == WIN
	    && DRAGON2(apos).hostile_neighbors == 1)
	  continue;
	if (dragon[bpos].size == worm[bpos].size
	    && worm[bpos].attack_codes[0] == WIN
	    && DRAGON2(bpos).hostile_neighbors == 1)
	  continue;

	/* If one dragon consist of a single stone, don't treat it
	 * as a semeai. (But see nicklas1:1405 for an example where
	 * this rule is bad.
	 */

	if (dragon[apos].size == 1 || dragon[bpos].size == 1)
	  continue;

	semeai_found = 1;
	a_best_status = UNKNOWN;
	b_best_status = UNKNOWN;
	a_worst_status = UNKNOWN;
	b_worst_status = UNKNOWN;

	if (pass == 0) {
	  TRACE_SEMEAI("Considering semeai between %1m and %1m\n",
		apos, bpos);
	  owl_analyze_semeai(apos, bpos,
			     best_result_a+k, worst_result_b+k, move+k, 1);
	  TRACE_SEMEAI("Result1: %s %s %1m, ",
	        safety_to_string(best_result_a[k]),
	        safety_to_string(worst_result_b[k]), move[k]);
	  if (a_best_status == DEAD
	      || a_best_status == UNKNOWN
	      || (a_best_status == ALIVE_IN_SEKI 
		  && best_result_a[k] == ALIVE)) {
	    a_best_status = best_result_a[k];
	    b_worst_status = worst_result_b[k];
	  }
	  owl_analyze_semeai(bpos, apos, 
			     best_result_b+k, worst_result_a+k, NULL, 1);
	  TRACE_SEMEAI("Result2 %s %s.\n",
	        safety_to_string(best_result_b[k]),
	        safety_to_string(worst_result_a[k]));
	  if (b_best_status == DEAD
	      || b_best_status == UNKNOWN
	      || (b_best_status == ALIVE_IN_SEKI
		  && best_result_b[k] == ALIVE)) {
	    b_best_status = best_result_b[k];
	    a_worst_status = worst_result_a[k];
	  }
	}
	else { /* pass == 1 */
	  if (a_status == CRITICAL
	      && best_result_a[k] != DEAD)
	    add_owl_defense_move(move[k], apos, WIN);
	  if (b_status == CRITICAL
	      && worst_result_b[k] == DEAD)
	    add_owl_attack_move(move[k], bpos, WIN);
	}
      } /* loop over neighbor dragons */
      if (pass == 0 && semeai_found) {
	int a_status;
	int b_status;

	if (a_best_status != DEAD && a_worst_status == DEAD)
	  a_status = CRITICAL;
	else
	  a_status = a_worst_status;
	
	if (b_best_status != DEAD && b_worst_status == DEAD)
	  b_status = CRITICAL;
	else
	  b_status = b_worst_status;
	
	a_status = a_status;
	b_status = b_status;
	if (a_status == ALIVE_IN_SEKI)
	  a_status = ALIVE;
	if (b_status == ALIVE_IN_SEKI)
	  b_status = ALIVE;
	
	update_status(apos, a_status, a_status);
	update_status(bpos, b_status, b_status);
      }
    }
  }
}

/* liberty_of_dragon(pos, origin) returns true if the vertex at (pos) is a
 * liberty of the dragon with origin at (origin).
 */

static int 
liberty_of_dragon(int pos, int origin)
{
  if (pos == NO_MOVE)
    return 0;

  if (board[pos] != EMPTY)
    return 0;

  if ((ON_BOARD(SOUTH(pos))    && dragon[SOUTH(pos)].origin == origin)
      || (ON_BOARD(WEST(pos))  && dragon[WEST(pos)].origin == origin)
      || (ON_BOARD(NORTH(pos)) && dragon[NORTH(pos)].origin == origin)
      || (ON_BOARD(EAST(pos))  && dragon[EAST(pos)].origin == origin))
    return 1;

  return 0;
}

/* Change the status and safety of a dragon */

static void
update_status(int dr, int new_status, int new_safety)
{
  int pos;

  if (dragon[dr].status != new_status
      && (dragon[dr].status != CRITICAL || new_status != DEAD))  {
    TRACE_SEMEAI("Changing status of %1m from %s to %s.\n", dr,
	  status_to_string(dragon[dr].status),
	  status_to_string(new_status));
    for (pos = BOARDMIN; pos < BOARDMAX; pos++)
      if (IS_STONE(board[pos]) && is_same_dragon(dr, pos))
	dragon[pos].status = new_status;
  }

  if (DRAGON2(dr).safety != new_safety
      && (DRAGON2(dr).safety != CRITICAL || new_safety != DEAD)) {
    TRACE_SEMEAI("Changing safety of %1m from %s to %s.\n", dr,
	  safety_to_string(DRAGON2(dr).safety), safety_to_string(new_safety));
    DRAGON2(dr).safety = new_safety;
  }
}



/* analyzes a pair of adjacent dragons which are 
 * DEAD or CRITICAL.
 */
static void
analyze_semeai(int my_dragon, int your_dragon)
{
  /* We start liberty counts at 1 since we will be subtracting
   * the number of worms. */
  int mylibs = 1, yourlibs = 1, commonlibs = 0; 
  int yourlib = NO_MOVE;
  int commonlib = NO_MOVE;
  int color = board[my_dragon];
  int my_status = UNKNOWN;
  int your_status = UNKNOWN;
  int margin_of_safety = 0;
  int owl_code_sufficient = 0;
  int pos;
  
  TRACE_SEMEAI("semeai_analyzer: %1m (me) vs %1m (them)\n",
	my_dragon, your_dragon);

  /* If both dragons are owl-critical, and the defense point for my
   * dragon owl_does_attack your dragon, add another owl attack move
   * reason.
   */
  if (dragon[my_dragon].owl_status == CRITICAL
      && dragon[your_dragon].owl_status == CRITICAL) {
    if (dragon[your_dragon].owl_attack_point
	== dragon[my_dragon].owl_defense_point)
      return;
    if (dragon[my_dragon].owl_defense_point != NO_MOVE) {
      int acode = owl_does_attack(dragon[my_dragon].owl_defense_point,
				  your_dragon, NULL);
      if (acode != 0) {
	add_owl_attack_move(dragon[my_dragon].owl_defense_point, your_dragon,
			    acode);
	TRACE_SEMEAI("added owl attack of %1m at %1m with code %d\n",
	      your_dragon, dragon[my_dragon].owl_defense_point, acode);
	owl_code_sufficient = 1;
      }
    }
  }

  /* If both dragons are owl-critical, or your dragon is owl-critical
   * and my dragon is owl-dead, and the attack point for your dragon
   * owl_does_defend my dragon, add another owl defense move reason
   * and possibly change the owl status of my dragon to critical.
   */
  if ((dragon[my_dragon].owl_status == CRITICAL
       || dragon[my_dragon].owl_status == DEAD)
      && dragon[your_dragon].owl_status == CRITICAL) {
    if (dragon[your_dragon].owl_attack_point
	== dragon[my_dragon].owl_defense_point)
      return;
    if (dragon[your_dragon].owl_attack_point != NO_MOVE) {
      int dcode = owl_does_defend(dragon[your_dragon].owl_attack_point,
				  my_dragon, NULL);
      if (dcode != 0) {
	add_owl_defense_move(dragon[your_dragon].owl_attack_point, my_dragon,
			     dcode);
	TRACE_SEMEAI("added owl defense of %1m at %1m with code %d\n",
	      my_dragon, dragon[your_dragon].owl_attack_point, dcode);
	if (dragon[my_dragon].owl_status == DEAD) {
	  int pos;

	  for (pos = BOARDMIN; pos < BOARDMAX; pos++) {
	    if (!ON_BOARD(pos))
	      continue;
	    if (board[pos] == board[my_dragon]
		&& is_same_dragon(pos, my_dragon)) {
	      dragon[pos].owl_status = CRITICAL;
	      dragon[pos].status = CRITICAL;
	    }
	  }
	  TRACE_SEMEAI(
		"changed owl_status and status of %1m to CRITICAL\n",
		my_dragon);
	}
	owl_code_sufficient = 1;
      }
    }
  }

  /* If the owl code was able to resolve the semeai, exit. */
  if (owl_code_sufficient) {
    TRACE_SEMEAI("...owl code sufficient to resolve semeai, exiting\n");
    return;
  }


  /* The semeai module is prone to errors since semeai cannot
   * really be handled by static analysis. It is really only needed
   * when the dragons have many liberties since tight situations
   * can be handled by the tactical reading code. Thus we exclude
   * dragon pairs where either has a tactically DEAD or CRITICAL
   * string which is adjacent to the other dragon which is owl
   * substantial.
   */
  for (pos = BOARDMIN; pos < BOARDMAX; pos++) {
    if (!ON_BOARD(pos))
      continue;

    if (worm[pos].origin == pos
	&& worm[pos].attack_codes[0] == WIN) {
      if (dragon[pos].origin == my_dragon
	  || dragon[pos].origin == your_dragon) {
	int adj;
	int adjs[MAXCHAIN];
	int r;
	
	adj = chainlinks(pos, adjs);
	for (r = 0; r < adj; r++) {
	  int cpos = adjs[r];
	  if (dragon[cpos].origin == my_dragon
	      || dragon[cpos].origin == your_dragon) {
	    if (owl_substantial(pos)) {
	      TRACE_SEMEAI(
		    "...tactical situation detected, exiting\n");
	      return;
	    }
	  }
	}
      }
    }
  }
  
  
  /* Mark the dragons as involved in semeai */
  for (pos = BOARDMIN; pos < BOARDMAX; pos++) {
    if (ON_BOARD(pos)
	&& (is_same_dragon(pos, my_dragon)
	    || is_same_dragon(pos, your_dragon)))
      DRAGON2(pos).semeai = 1;
  }
  
  /* First we try to determine the number of liberties of each
   * dragon, and the number of common liberties. We subtract
   * 1 minus the number of worms of the dragon from the liberty
   * count, since if a dragon has several worms, a move may
   * have to be invested in connecting them. At the same time
   * we try to find a liberty of the opponent's dragon, and a
   * common liberty, for future reference.
   */
  for (pos = BOARDMIN; pos < BOARDMAX; pos++) {
    if (!ON_BOARD(pos))
      continue;
    if (IS_STONE(board[pos])
	&& worm[pos].origin == pos) {
      if (is_same_dragon(pos, my_dragon))
	mylibs--;
      if (is_same_dragon(pos, your_dragon))
	yourlibs--;
    }
    else if (board[pos] == EMPTY) {
      if (liberty_of_dragon(pos, your_dragon)) {
	yourlibs ++;
	if (liberty_of_dragon(pos, my_dragon)) {
	  commonlibs++;
	  mylibs++;
	  commonlib = pos;
	}
	else
	  yourlib = pos;
      }
      else if (liberty_of_dragon(pos, my_dragon))
	mylibs++;
    }
  }

  /* We add 1 to the
   * number of liberties of an owl critical dragon if the point
   * of attack is not a liberty of the dragon, since a move
   * may have to be invested in attacking it.
   */

  if (dragon[my_dragon].owl_status == CRITICAL
      && dragon[my_dragon].owl_attack_point != NO_MOVE
      && !liberty_of_string(dragon[my_dragon].owl_attack_point, my_dragon))
    mylibs++;
  
  if (dragon[your_dragon].owl_status == CRITICAL
      && dragon[your_dragon].owl_attack_point != NO_MOVE
      && !liberty_of_string(dragon[your_dragon].owl_attack_point, your_dragon))
    yourlibs++;
  
  /* Now we compute the statuses which result from a
   * naive comparison of the number of liberties. There
   * is some uncertainty in these calculations, so we
   * must exercise caution in applying the results.
   *
   * RULES FOR PLAYING SEMEAI. Let M be the number of liberties
   * of my group, excluding common liberties; let Y be the
   * number of liberties of your group, excluding common
   * liberties; and let C be the number of common liberties.
   * 
   *             If both groups have zero eyes:
   * 
   * (1)  If C=0 and M=Y, whoever moves first wins. CRITICAL.
   * (2)  If C=0 and M>Y, I win.
   * (3)  If C=0 and M<Y, you win.
   * (4)  If C>0 and M >= Y+C then your group is dead and mine is alive.
   * (5)  If C>0 and M = Y+C-1 then the situation is CRITICAL. 
   * (5a) If M=0, then Y=0 and C=1. Whoever moves first kills.
   * (5b) If M>0, then I can kill or you can make seki.
   * (6)  If M < Y+C-1 and Y < M+C-1 then the situation is seki.
   * (7)  If C>0 and Y=M+C-1 the situation is CRITICAL. 
   * (7a) If Y=0, then M=0 and C=1 as in (5). 
   * (7b) If Y>0, you can kill or I can make seki.
   * (8)  If C>0 and Y > M+C then your group is alive and mine is dead.
   *
   *              If both groups have one eye:
   *
   * In this case M > 0 and Y > 0.
   * 
   * (1) If M>C+Y then I win.
   * (2) If Y>C+M then you win.
   * (3) If C=0 and M=Y then whoever moves first kills. CRITICAL.
   * (4) If C>0 and M=C+Y then I can kill, you can make seki. CRITICAL.
   * (5) If C>0 and M<C+Y, Y<C+M, then the situation is seki. 
   * (6) If C>0 and Y=C+M, then you can kill, I can make seki. CRITICAL.
   *
   *            If I have an eye and you dont:
   * 
   * In this case, M > 0. This situation (me ari me nashi) can
   * never be seki. The common liberties must be filled by you,
   * making it difficult to win.
   * 
   * (1) If M+C>Y then I win.
   * (2) If M+C=Y then whoever moves first wins. CRITICAL.
   * (3) If M+C<Y then you win.
   *
   *            If you have an eye and I don't
   * 
   * In this case, Y > 0. 
   * 
   * (1) If Y+C>M you win.
   * (2) If Y+C=M whoever moves first wins. CRITICAL.
   * (3) If Y+C<M I win.  */

  if (min_eyes(&DRAGON2(my_dragon).genus) == 0
      && min_eyes(&DRAGON2(your_dragon).genus) == 0) {
    if (commonlibs == 0) {
      if (mylibs > yourlibs) {
	my_status = ALIVE;
	your_status = DEAD;
	margin_of_safety = mylibs - yourlibs;
      }
      else if (mylibs < yourlibs) {
	my_status = DEAD;
	your_status = ALIVE;
	margin_of_safety = yourlibs - mylibs;
      }
      else {
	my_status = CRITICAL;
	your_status = CRITICAL;
	margin_of_safety = 0;
      }
    }
    else if (mylibs == yourlibs + commonlibs - 1) {
      if (mylibs == 0) {
	my_status = CRITICAL;
	your_status = CRITICAL;
	margin_of_safety = 0;
      }
      else {
	/* I can kill, you can make seki */
	my_status = ALIVE;
	your_status = CRITICAL;
	margin_of_safety = 0;
      }
    }
    else if (mylibs < yourlibs + commonlibs - 1
	     && yourlibs < mylibs+commonlibs - 1) {
      /* Seki */
      my_status = ALIVE;
      your_status = ALIVE;
      margin_of_safety = INFINITY; 
    }
    else if (commonlibs > 0
	     && yourlibs == mylibs + commonlibs - 1) {
      if (yourlibs == 0) {
	my_status = CRITICAL;
	your_status = CRITICAL;
	margin_of_safety = 0;
      }
      else {
	/* you can kill, I can make seki */
	my_status = CRITICAL;
	your_status = ALIVE;
	margin_of_safety = 0;
      }
    }
    else if (commonlibs > 0
	     && yourlibs > mylibs + commonlibs) {
      my_status = DEAD;
      your_status = ALIVE;
      margin_of_safety = yourlibs - mylibs - commonlibs;
    }
  }
  if (min_eyes(&DRAGON2(my_dragon).genus) > 0
      && min_eyes(&DRAGON2(your_dragon).genus) > 0) {
    if (mylibs > yourlibs + commonlibs) {
      my_status = ALIVE;
      your_status = DEAD;
      margin_of_safety = mylibs - yourlibs - commonlibs;
    }
    else if (yourlibs > mylibs + commonlibs) {
      my_status = DEAD;
      your_status = ALIVE;
      margin_of_safety = yourlibs - mylibs - commonlibs;
    }
    else if (commonlibs == 0
	     && mylibs == yourlibs) {
      my_status = CRITICAL;
      your_status = CRITICAL;
      margin_of_safety = 0;
    }
    else if (commonlibs > 0
	     && mylibs == commonlibs + yourlibs) {
      my_status = ALIVE;
      your_status = CRITICAL;
      margin_of_safety = 0;
    }
    else if (commonlibs > 0
	     && mylibs < commonlibs + yourlibs
	     && yourlibs < commonlibs + mylibs) {
      /* seki */
      my_status = ALIVE;
      your_status = ALIVE;
      margin_of_safety = INFINITY;
    }
    else if (commonlibs > 0
	     && yourlibs == commonlibs + mylibs) {
      my_status = CRITICAL;
      your_status = ALIVE;
      margin_of_safety = 0;
    }
  }
  if (min_eyes(&DRAGON2(my_dragon).genus) > 0
      && min_eyes(&DRAGON2(your_dragon).genus) == 0) {
    if (mylibs > commonlibs + yourlibs) {
      my_status = ALIVE;
      your_status = DEAD;
      margin_of_safety = mylibs - commonlibs - yourlibs;
    }
    else if (mylibs + commonlibs == yourlibs) {
      my_status = CRITICAL;
      your_status = CRITICAL;
    }
    else if (mylibs + commonlibs < yourlibs) {
      my_status = DEAD;
      your_status = ALIVE;
      margin_of_safety = mylibs + commonlibs - yourlibs;
    }
  }
  if (min_eyes(&DRAGON2(my_dragon).genus) == 0
      && min_eyes(&DRAGON2(your_dragon).genus) > 0) {
    if (yourlibs + commonlibs > mylibs) {
      my_status = DEAD;
      your_status = ALIVE;
      margin_of_safety = yourlibs + commonlibs - mylibs;
    }
    else if (yourlibs + commonlibs == mylibs) {
      my_status = CRITICAL;
      your_status = CRITICAL;
      margin_of_safety = 0;
    }
    else if (yourlibs + commonlibs > mylibs) {
      my_status = DEAD;
      your_status = ALIVE;
      margin_of_safety = yourlibs - mylibs - commonlibs;
    }
  }
  
  /* Update matcher statuses */

  /* We do not want to change the matcher status of the friendly
   * dragon if the owl status is critical. If my_status==DEAD by
   * the preceeding heuristics but the owl code finds a way to
   * live, then we should by all means take it. On the other hand
   * if my_status==ALIVE we are alive by semeai, but as a matter
   * of "safety first" if the owl code finds a way to live we may
   * want to take it. So the matcher status is not changed.
   */
  
  if (dragon[my_dragon].owl_status != CRITICAL) {
    if (my_status == ALIVE)
      update_status(my_dragon, ALIVE, ALIVE_IN_SEKI);
    else if (my_status == CRITICAL)
      update_status(my_dragon, CRITICAL, CRITICAL);
    else if (my_status == DEAD)
      update_status(my_dragon, DEAD, DEAD);
  }

  if (your_status == ALIVE)
    update_status(your_dragon, ALIVE, ALIVE_IN_SEKI);
  else if (your_status == CRITICAL)
    update_status(your_dragon, CRITICAL, CRITICAL);
  else if (your_status == DEAD)
    update_status(your_dragon, DEAD, DEAD);
  
  /* Find the recommended semeai moves. In order of priority,
   * (1) We defend our dragon;
   * (2) We attack your dragon;
   * (3) If common liberties > 1, make an eye;
   * (4) If common liberties > 1, kill an eye;
   * (5) Fill a liberty of yours;
   * (6) Fill a common liberty.  */

  if (my_status == CRITICAL || your_status == CRITICAL) {
    int found_one = 0;
    if (dragon[my_dragon].owl_status == CRITICAL
	&& dragon[my_dragon].owl_defense_point != NO_MOVE)
      add_appropriate_semeai_moves(dragon[my_dragon].owl_defense_point,
				   my_dragon, your_dragon,
				   my_status, your_status, margin_of_safety);
    else if (dragon[your_dragon].owl_status == CRITICAL
	     && dragon[your_dragon].owl_attack_point != NO_MOVE)
      add_appropriate_semeai_moves(dragon[your_dragon].owl_attack_point,
				   my_dragon, your_dragon,
				   my_status, your_status, margin_of_safety);
    else if (commonlibs > 1) {
      if (eye_move_urgency(&DRAGON2(my_dragon).genus) > 0)
	add_appropriate_semeai_moves(DRAGON2(my_dragon).heye,
				     my_dragon, your_dragon,
				     my_status, your_status, margin_of_safety);
      if (eye_move_urgency(&DRAGON2(your_dragon).genus))
	add_appropriate_semeai_moves(DRAGON2(your_dragon).heye,
				     my_dragon, your_dragon,
				     my_status, your_status, margin_of_safety);
    }
    else {
      for (pos = BOARDMIN; pos < BOARDMAX; pos++) {
	if (!ON_BOARD(pos))
	  continue;

	if (liberty_of_dragon(pos, your_dragon) 
	    && !liberty_of_dragon(pos, my_dragon)
	    && safe_move(pos, color)) {
	  /* add move reasons for EVERY outside liberty where we can
	   * play safely. A move to win a semeai might not be a
	   * safe move if it is inside the opponent's eyespace. 
	   * However we hope that the reading code can analyze the
	   * semeai in cases where every safe liberty has been filled.
	   */
	  add_appropriate_semeai_moves(pos, my_dragon, your_dragon,
				       my_status, your_status,
				       margin_of_safety);
	  found_one = 1;
	}
      }
      if (!found_one) {
	/* No outside liberties --- look for common liberties.
	 * Filling a common liberty is usually bad but if our 
	 * heuristics are accurate, we should only reach this point 
	 * if we definitely have enough liberties to win. As a
	 * sanity check, we require filling a common liberty to
	 * be a safe move.
	 */
	for (pos = BOARDMIN; pos < BOARDMAX; pos++) {
	  if (ON_BOARD(pos)
	      && liberty_of_dragon(pos, your_dragon)
	      && safe_move(pos, color))
	    add_appropriate_semeai_moves(pos, my_dragon, your_dragon,
					 my_status, your_status,
					 margin_of_safety);
	}
      }
    }
  }
}

/* Add those move reasons which are appropriate. */

static void
add_appropriate_semeai_moves(int move, int my_dragon, int your_dragon, 
			     int my_status, int your_status, 
			     int margin_of_safety)
{
  if (my_status == CRITICAL)
    add_semeai_move(move, my_dragon);
  else if (margin_of_safety == 1)
    add_semeai_threat(move, my_dragon);
  if (your_status == CRITICAL)
    add_semeai_move(move, your_dragon);
  else if (margin_of_safety == 1)
    add_semeai_threat(move, your_dragon);
}


/*
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 2
 * End:
 */
