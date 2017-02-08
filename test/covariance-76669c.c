# 1 "<built-in>"
# 1 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/covariance.c"
/**
 * covariance.c: This file is part of the PolyBench/C 3.2 test suite.
 *
 *
 * Contact: Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://polybench.sourceforge.net
 */
#if 0 /* expanded by -frewrite-includes */
#include <stdio.h>
#endif /* expanded by -frewrite-includes */
# 8 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/covariance.c"
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
# 1 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 1 3 4
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
# 37 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#define __need_ptrdiff_t
#define __need_size_t
#define __need_wchar_t
#define __need_NULL
#define __need_STDDEF_H_misc
/* __need_wint_t is intentionally not defined here. */
#endif
# 44 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_ptrdiff_t)
#if !defined(_PTRDIFF_T) || __has_feature(modules)
/* Always define ptrdiff_t when modules are available. */
#if !__has_feature(modules)
#define _PTRDIFF_T
#endif
# 51 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif
# 53 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_ptrdiff_t
#endif /* defined(__need_ptrdiff_t) */
# 55 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_size_t)
#if !defined(_SIZE_T) || __has_feature(modules)
/* Always define size_t when modules are available. */
#if !__has_feature(modules)
#define _SIZE_T
#endif
# 62 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ size_t;
#endif
# 64 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_size_t
#endif /*defined(__need_size_t) */
# 66 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
/* ISO9899:2011 7.20 (C11 Annex K): Define rsize_t if __STDC_WANT_LIB_EXT1__ is
 * enabled. */
#if (defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ >= 1 && \
     !defined(_RSIZE_T)) || __has_feature(modules)
/* Always define rsize_t when modules are available. */
#if !__has_feature(modules)
#define _RSIZE_T
#endif
# 76 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ rsize_t;
#endif
# 78 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif /* defined(__need_STDDEF_H_misc) */
# 79 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_wchar_t)
#ifndef __cplusplus
/* Always define wchar_t when modules are available. */
#if !defined(_WCHAR_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WCHAR_T
#if defined(_MSC_EXTENSIONS)
#define _WCHAR_T_DEFINED
#endif
# 89 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 90 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WCHAR_TYPE__ wchar_t;
#endif
# 92 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 93 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wchar_t
#endif /* defined(__need_wchar_t) */
# 95 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_NULL)
#undef NULL
#ifdef __cplusplus
#  if !defined(__MINGW32__) && !defined(_MSC_VER)
#    define NULL __null
#  else
# 102 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#    define NULL 0
#  endif
# 104 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#else
# 105 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#  define NULL ((void*)0)
#endif
# 107 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#ifdef __cplusplus
#if defined(_MSC_EXTENSIONS) && defined(_NATIVE_NULLPTR_SUPPORTED)
namespace std { typedef decltype(nullptr) nullptr_t; }
using ::std::nullptr_t;
#endif
# 112 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 113 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_NULL
#endif /* defined(__need_NULL) */
# 115 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
#if __STDC_VERSION__ >= 201112L || __cplusplus >= 201103L
#if 0 /* expanded by -frewrite-includes */
#include "__stddef_max_align_t.h"
#endif /* expanded by -frewrite-includes */
# 118 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
# 119 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 120 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#define offsetof(t, d) __builtin_offsetof(t, d)
#undef __need_STDDEF_H_misc
#endif  /* defined(__need_STDDEF_H_misc) */
# 123 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

/* Some C libraries expect to see a wint_t here. Others (notably MinGW) will use
__WINT_TYPE__ directly; accommodate both by requiring __need_wint_t */
#if defined(__need_wint_t)
/* Always define wint_t when modules are available. */
#if !defined(_WINT_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WINT_T
#endif
# 132 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WINT_TYPE__ wint_t;
#endif
# 134 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wint_t
#endif /* __need_wint_t */
# 136 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#endif
# 138 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
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
# 1 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 1 3 4
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
# 37 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#define __need_ptrdiff_t
#define __need_size_t
#define __need_wchar_t
#define __need_NULL
#define __need_STDDEF_H_misc
/* __need_wint_t is intentionally not defined here. */
#endif
# 44 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_ptrdiff_t)
#if !defined(_PTRDIFF_T) || __has_feature(modules)
/* Always define ptrdiff_t when modules are available. */
#if !__has_feature(modules)
#define _PTRDIFF_T
#endif
# 51 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif
# 53 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_ptrdiff_t
#endif /* defined(__need_ptrdiff_t) */
# 55 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_size_t)
#if !defined(_SIZE_T) || __has_feature(modules)
/* Always define size_t when modules are available. */
#if !__has_feature(modules)
#define _SIZE_T
#endif
# 62 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ size_t;
#endif
# 64 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_size_t
#endif /*defined(__need_size_t) */
# 66 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
/* ISO9899:2011 7.20 (C11 Annex K): Define rsize_t if __STDC_WANT_LIB_EXT1__ is
 * enabled. */
#if (defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ >= 1 && \
     !defined(_RSIZE_T)) || __has_feature(modules)
/* Always define rsize_t when modules are available. */
#if !__has_feature(modules)
#define _RSIZE_T
#endif
# 76 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ rsize_t;
#endif
# 78 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif /* defined(__need_STDDEF_H_misc) */
# 79 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_wchar_t)
#ifndef __cplusplus
/* Always define wchar_t when modules are available. */
#if !defined(_WCHAR_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WCHAR_T
#if defined(_MSC_EXTENSIONS)
#define _WCHAR_T_DEFINED
#endif
# 89 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 90 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WCHAR_TYPE__ wchar_t;
#endif
# 92 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 93 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wchar_t
#endif /* defined(__need_wchar_t) */
# 95 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_NULL)
#undef NULL
#ifdef __cplusplus
#  if !defined(__MINGW32__) && !defined(_MSC_VER)
#    define NULL __null
#  else
# 102 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#    define NULL 0
#  endif
# 104 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#else
# 105 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#  define NULL ((void*)0)
#endif
# 107 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#ifdef __cplusplus
#if defined(_MSC_EXTENSIONS) && defined(_NATIVE_NULLPTR_SUPPORTED)
namespace std { typedef decltype(nullptr) nullptr_t; }
using ::std::nullptr_t;
#endif
# 112 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 113 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_NULL
#endif /* defined(__need_NULL) */
# 115 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
#if __STDC_VERSION__ >= 201112L || __cplusplus >= 201103L
#if 0 /* expanded by -frewrite-includes */
#include "__stddef_max_align_t.h"
#endif /* expanded by -frewrite-includes */
# 118 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
# 119 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 120 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#define offsetof(t, d) __builtin_offsetof(t, d)
#undef __need_STDDEF_H_misc
#endif  /* defined(__need_STDDEF_H_misc) */
# 123 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

/* Some C libraries expect to see a wint_t here. Others (notably MinGW) will use
__WINT_TYPE__ directly; accommodate both by requiring __need_wint_t */
#if defined(__need_wint_t)
/* Always define wint_t when modules are available. */
#if !defined(_WINT_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WINT_T
#endif
# 132 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WINT_TYPE__ wint_t;
#endif
# 134 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wint_t
#endif /* __need_wint_t */
# 136 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#endif
# 138 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
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
# 1 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stdarg.h" 1 3 4
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
# 33 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stdarg.h" 3 4
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
# 45 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stdarg.h" 3 4

#ifndef __GNUC_VA_LIST
#define __GNUC_VA_LIST 1
typedef __builtin_va_list __gnuc_va_list;
#endif
# 50 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stdarg.h" 3 4

#endif /* __STDARG_H */
# 52 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stdarg.h" 3 4
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
# 9 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/covariance.c" 2
#if 0 /* expanded by -frewrite-includes */
#include <unistd.h>
#endif /* expanded by -frewrite-includes */
# 9 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/covariance.c"
# 1 "/usr/include/unistd.h" 1 3 4
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
 *	POSIX Standard: 2.10 Symbolic Constants		<unistd.h>
 */

#ifndef	_UNISTD_H
#define	_UNISTD_H	1

#if 0 /* expanded by -frewrite-includes */
#include <features.h>
#endif /* expanded by -frewrite-includes */
# 25 "/usr/include/unistd.h" 3 4
# 26 "/usr/include/unistd.h" 3 4

__BEGIN_DECLS

/* These may be used to determine what facilities are present at compile time.
   Their values can be obtained at run time from `sysconf'.  */

#ifdef __USE_XOPEN2K8
/* POSIX Standard approved as ISO/IEC 9945-1 as of September 2008.  */
# define _POSIX_VERSION	200809L
#elif defined __USE_XOPEN2K
# 36 "/usr/include/unistd.h" 3 4
/* POSIX Standard approved as ISO/IEC 9945-1 as of December 2001.  */
# define _POSIX_VERSION	200112L
#elif defined __USE_POSIX199506
# 39 "/usr/include/unistd.h" 3 4
/* POSIX Standard approved as ISO/IEC 9945-1 as of June 1995.  */
# define _POSIX_VERSION	199506L
#elif defined __USE_POSIX199309
# 42 "/usr/include/unistd.h" 3 4
/* POSIX Standard approved as ISO/IEC 9945-1 as of September 1993.  */
# define _POSIX_VERSION	199309L
#else
# 45 "/usr/include/unistd.h" 3 4
/* POSIX Standard approved as ISO/IEC 9945-1 as of September 1990.  */
# define _POSIX_VERSION	199009L
#endif
# 48 "/usr/include/unistd.h" 3 4

/* These are not #ifdef __USE_POSIX2 because they are
   in the theoretically application-owned namespace.  */

#ifdef __USE_XOPEN2K8
# define __POSIX2_THIS_VERSION	200809L
/* The utilities on GNU systems also correspond to this version.  */
#elif defined __USE_XOPEN2K
# 56 "/usr/include/unistd.h" 3 4
/* The utilities on GNU systems also correspond to this version.  */
# define __POSIX2_THIS_VERSION	200112L
#elif defined __USE_POSIX199506
# 59 "/usr/include/unistd.h" 3 4
/* The utilities on GNU systems also correspond to this version.  */
# define __POSIX2_THIS_VERSION	199506L
#else
# 62 "/usr/include/unistd.h" 3 4
/* The utilities on GNU systems also correspond to this version.  */
# define __POSIX2_THIS_VERSION	199209L
#endif
# 65 "/usr/include/unistd.h" 3 4

/* The utilities on GNU systems also correspond to this version.  */
#define _POSIX2_VERSION	__POSIX2_THIS_VERSION

/* This symbol was required until the 2001 edition of POSIX.  */
#define	_POSIX2_C_VERSION	__POSIX2_THIS_VERSION

/* If defined, the implementation supports the
   C Language Bindings Option.  */
#define	_POSIX2_C_BIND	__POSIX2_THIS_VERSION

/* If defined, the implementation supports the
   C Language Development Utilities Option.  */
#define	_POSIX2_C_DEV	__POSIX2_THIS_VERSION

/* If defined, the implementation supports the
   Software Development Utilities Option.  */
#define	_POSIX2_SW_DEV	__POSIX2_THIS_VERSION

/* If defined, the implementation supports the
   creation of locales with the localedef utility.  */
#define _POSIX2_LOCALEDEF       __POSIX2_THIS_VERSION

/* X/Open version number to which the library conforms.  It is selectable.  */
#ifdef __USE_XOPEN2K8
# define _XOPEN_VERSION	700
#elif defined __USE_XOPEN2K
# 92 "/usr/include/unistd.h" 3 4
# define _XOPEN_VERSION	600
#elif defined __USE_UNIX98
# 94 "/usr/include/unistd.h" 3 4
# define _XOPEN_VERSION	500
#else
# 96 "/usr/include/unistd.h" 3 4
# define _XOPEN_VERSION	4
#endif
# 98 "/usr/include/unistd.h" 3 4

/* Commands and utilities from XPG4 are available.  */
#define _XOPEN_XCU_VERSION	4

/* We are compatible with the old published standards as well.  */
#define _XOPEN_XPG2	1
#define _XOPEN_XPG3	1
#define _XOPEN_XPG4	1

/* The X/Open Unix extensions are available.  */
#define _XOPEN_UNIX	1

/* Encryption is present.  */
#define	_XOPEN_CRYPT	1

/* The enhanced internationalization capabilities according to XPG4.2
   are present.  */
#define	_XOPEN_ENH_I18N	1

/* The legacy interfaces are also available.  */
#define _XOPEN_LEGACY	1


/* Get values of POSIX options:

   If these symbols are defined, the corresponding features are
   always available.  If not, they may be available sometimes.
   The current values can be obtained with `sysconf'.

   _POSIX_JOB_CONTROL		Job control is supported.
   _POSIX_SAVED_IDS		Processes have a saved set-user-ID
				and a saved set-group-ID.
   _POSIX_REALTIME_SIGNALS	Real-time, queued signals are supported.
   _POSIX_PRIORITY_SCHEDULING	Priority scheduling is supported.
   _POSIX_TIMERS		POSIX.4 clocks and timers are supported.
   _POSIX_ASYNCHRONOUS_IO	Asynchronous I/O is supported.
   _POSIX_PRIORITIZED_IO	Prioritized asynchronous I/O is supported.
   _POSIX_SYNCHRONIZED_IO	Synchronizing file data is supported.
   _POSIX_FSYNC			The fsync function is present.
   _POSIX_MAPPED_FILES		Mapping of files to memory is supported.
   _POSIX_MEMLOCK		Locking of all memory is supported.
   _POSIX_MEMLOCK_RANGE		Locking of ranges of memory is supported.
   _POSIX_MEMORY_PROTECTION	Setting of memory protections is supported.
   _POSIX_MESSAGE_PASSING	POSIX.4 message queues are supported.
   _POSIX_SEMAPHORES		POSIX.4 counting semaphores are supported.
   _POSIX_SHARED_MEMORY_OBJECTS	POSIX.4 shared memory objects are supported.
   _POSIX_THREADS		POSIX.1c pthreads are supported.
   _POSIX_THREAD_ATTR_STACKADDR	Thread stack address attribute option supported.
   _POSIX_THREAD_ATTR_STACKSIZE	Thread stack size attribute option supported.
   _POSIX_THREAD_SAFE_FUNCTIONS	Thread-safe functions are supported.
   _POSIX_THREAD_PRIORITY_SCHEDULING
				POSIX.1c thread execution scheduling supported.
   _POSIX_THREAD_PRIO_INHERIT	Thread priority inheritance option supported.
   _POSIX_THREAD_PRIO_PROTECT	Thread priority protection option supported.
   _POSIX_THREAD_PROCESS_SHARED	Process-shared synchronization supported.
   _POSIX_PII			Protocol-independent interfaces are supported.
   _POSIX_PII_XTI		XTI protocol-indep. interfaces are supported.
   _POSIX_PII_SOCKET		Socket protocol-indep. interfaces are supported.
   _POSIX_PII_INTERNET		Internet family of protocols supported.
   _POSIX_PII_INTERNET_STREAM	Connection-mode Internet protocol supported.
   _POSIX_PII_INTERNET_DGRAM	Connectionless Internet protocol supported.
   _POSIX_PII_OSI		ISO/OSI family of protocols supported.
   _POSIX_PII_OSI_COTS		Connection-mode ISO/OSI service supported.
   _POSIX_PII_OSI_CLTS		Connectionless ISO/OSI service supported.
   _POSIX_POLL			Implementation supports `poll' function.
   _POSIX_SELECT		Implementation supports `select' and `pselect'.

   _XOPEN_REALTIME		X/Open realtime support is available.
   _XOPEN_REALTIME_THREADS	X/Open realtime thread support is available.
   _XOPEN_SHM			Shared memory interface according to XPG4.2.

   _XBS5_ILP32_OFF32		Implementation provides environment with 32-bit
				int, long, pointer, and off_t types.
   _XBS5_ILP32_OFFBIG		Implementation provides environment with 32-bit
				int, long, and pointer and off_t with at least
				64 bits.
   _XBS5_LP64_OFF64		Implementation provides environment with 32-bit
				int, and 64-bit long, pointer, and off_t types.
   _XBS5_LPBIG_OFFBIG		Implementation provides environment with at
				least 32 bits int and long, pointer, and off_t
				with at least 64 bits.

   If any of these symbols is defined as -1, the corresponding option is not
   true for any file.  If any is defined as other than -1, the corresponding
   option is true for all files.  If a symbol is not defined at all, the value
   for a specific file can be obtained from `pathconf' and `fpathconf'.

   _POSIX_CHOWN_RESTRICTED	Only the super user can use `chown' to change
				the owner of a file.  `chown' can only be used
				to change the group ID of a file to a group of
				which the calling process is a member.
   _POSIX_NO_TRUNC		Pathname components longer than
				NAME_MAX generate an error.
   _POSIX_VDISABLE		If defined, if the value of an element of the
				`c_cc' member of `struct termios' is
				_POSIX_VDISABLE, no character will have the
				effect associated with that element.
   _POSIX_SYNC_IO		Synchronous I/O may be performed.
   _POSIX_ASYNC_IO		Asynchronous I/O may be performed.
   _POSIX_PRIO_IO		Prioritized Asynchronous I/O may be performed.

   Support for the Large File Support interface is not generally available.
   If it is available the following constants are defined to one.
   _LFS64_LARGEFILE		Low-level I/O supports large files.
   _LFS64_STDIO			Standard I/O supports large files.
   */

#if 0 /* expanded by -frewrite-includes */
#include <bits/posix_opt.h>
#endif /* expanded by -frewrite-includes */
# 205 "/usr/include/unistd.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/posix_opt.h" 1 3 4
/* Define POSIX options for Linux.
   Copyright (C) 1996-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If
   not, see <http://www.gnu.org/licenses/>.  */

#ifndef	_BITS_POSIX_OPT_H
#define	_BITS_POSIX_OPT_H	1

/* Job control is supported.  */
#define	_POSIX_JOB_CONTROL	1

/* Processes have a saved set-user-ID and a saved set-group-ID.  */
#define	_POSIX_SAVED_IDS	1

/* Priority scheduling is supported.  */
#define	_POSIX_PRIORITY_SCHEDULING	200809L

/* Synchronizing file data is supported.  */
#define	_POSIX_SYNCHRONIZED_IO	200809L

/* The fsync function is present.  */
#define	_POSIX_FSYNC	200809L

/* Mapping of files to memory is supported.  */
#define	_POSIX_MAPPED_FILES	200809L

/* Locking of all memory is supported.  */
#define	_POSIX_MEMLOCK	200809L

/* Locking of ranges of memory is supported.  */
#define	_POSIX_MEMLOCK_RANGE	200809L

/* Setting of memory protections is supported.  */
#define	_POSIX_MEMORY_PROTECTION	200809L

/* Some filesystems allow all users to change file ownership.  */
#define	_POSIX_CHOWN_RESTRICTED	0

/* `c_cc' member of 'struct termios' structure can be disabled by
   using the value _POSIX_VDISABLE.  */
#define	_POSIX_VDISABLE	'\0'

/* Filenames are not silently truncated.  */
#define	_POSIX_NO_TRUNC	1

/* X/Open realtime support is available.  */
#define _XOPEN_REALTIME	1

/* X/Open thread realtime support is available.  */
#define _XOPEN_REALTIME_THREADS	1

/* XPG4.2 shared memory is supported.  */
#define	_XOPEN_SHM	1

/* Tell we have POSIX threads.  */
#define _POSIX_THREADS	200809L

/* We have the reentrant functions described in POSIX.  */
#define _POSIX_REENTRANT_FUNCTIONS      1
#define _POSIX_THREAD_SAFE_FUNCTIONS	200809L

/* We provide priority scheduling for threads.  */
#define _POSIX_THREAD_PRIORITY_SCHEDULING	200809L

/* We support user-defined stack sizes.  */
#define _POSIX_THREAD_ATTR_STACKSIZE	200809L

/* We support user-defined stacks.  */
#define _POSIX_THREAD_ATTR_STACKADDR	200809L

/* We support priority inheritence.  */
#define _POSIX_THREAD_PRIO_INHERIT	200809L

/* We support priority protection, though only for non-robust
   mutexes.  */
#define _POSIX_THREAD_PRIO_PROTECT	200809L

#ifdef __USE_XOPEN2K8
/* We support priority inheritence for robust mutexes.  */
# define _POSIX_THREAD_ROBUST_PRIO_INHERIT	200809L

/* We do not support priority protection for robust mutexes.  */
# define _POSIX_THREAD_ROBUST_PRIO_PROTECT	-1
#endif
# 98 "/usr/include/x86_64-linux-gnu/bits/posix_opt.h" 3 4

/* We support POSIX.1b semaphores.  */
#define _POSIX_SEMAPHORES	200809L

/* Real-time signals are supported.  */
#define _POSIX_REALTIME_SIGNALS	200809L

/* We support asynchronous I/O.  */
#define _POSIX_ASYNCHRONOUS_IO	200809L
#define _POSIX_ASYNC_IO		1
/* Alternative name for Unix98.  */
#define _LFS_ASYNCHRONOUS_IO	1
/* Support for prioritization is also available.  */
#define _POSIX_PRIORITIZED_IO	200809L

/* The LFS support in asynchronous I/O is also available.  */
#define _LFS64_ASYNCHRONOUS_IO	1

/* The rest of the LFS is also available.  */
#define _LFS_LARGEFILE		1
#define _LFS64_LARGEFILE	1
#define _LFS64_STDIO		1

/* POSIX shared memory objects are implemented.  */
#define _POSIX_SHARED_MEMORY_OBJECTS	200809L

/* CPU-time clocks support needs to be checked at runtime.  */
#define _POSIX_CPUTIME	0

/* Clock support in threads must be also checked at runtime.  */
#define _POSIX_THREAD_CPUTIME	0

/* GNU libc provides regular expression handling.  */
#define _POSIX_REGEXP	1

/* Reader/Writer locks are available.  */
#define _POSIX_READER_WRITER_LOCKS	200809L

/* We have a POSIX shell.  */
#define _POSIX_SHELL	1

/* We support the Timeouts option.  */
#define _POSIX_TIMEOUTS	200809L

/* We support spinlocks.  */
#define _POSIX_SPIN_LOCKS	200809L

/* The `spawn' function family is supported.  */
#define _POSIX_SPAWN	200809L

/* We have POSIX timers.  */
#define _POSIX_TIMERS	200809L

/* The barrier functions are available.  */
#define _POSIX_BARRIERS	200809L

/* POSIX message queues are available.  */
#define	_POSIX_MESSAGE_PASSING	200809L

/* Thread process-shared synchronization is supported.  */
#define _POSIX_THREAD_PROCESS_SHARED	200809L

/* The monotonic clock might be available.  */
#define _POSIX_MONOTONIC_CLOCK	0

/* The clock selection interfaces are available.  */
#define _POSIX_CLOCK_SELECTION	200809L

/* Advisory information interfaces are available.  */
#define _POSIX_ADVISORY_INFO	200809L

/* IPv6 support is available.  */
#define _POSIX_IPV6	200809L

/* Raw socket support is available.  */
#define _POSIX_RAW_SOCKETS	200809L

/* We have at least one terminal.  */
#define _POSIX2_CHAR_TERM	200809L

/* Neither process nor thread sporadic server interfaces is available.  */
#define _POSIX_SPORADIC_SERVER	-1
#define _POSIX_THREAD_SPORADIC_SERVER	-1

/* trace.h is not available.  */
#define _POSIX_TRACE	-1
#define _POSIX_TRACE_EVENT_FILTER	-1
#define _POSIX_TRACE_INHERIT	-1
#define _POSIX_TRACE_LOG	-1

/* Typed memory objects are not available.  */
#define _POSIX_TYPED_MEMORY_OBJECTS	-1

#endif /* bits/posix_opt.h */
# 192 "/usr/include/x86_64-linux-gnu/bits/posix_opt.h" 3 4
# 206 "/usr/include/unistd.h" 2 3 4

/* Get the environment definitions from Unix98.  */
#if defined __USE_UNIX98 || defined __USE_XOPEN2K
#if 0 /* expanded by -frewrite-includes */
# include <bits/environments.h>
#endif /* expanded by -frewrite-includes */
# 209 "/usr/include/unistd.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/environments.h" 1 3 4
/* Copyright (C) 1999-2016 Free Software Foundation, Inc.
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

#ifndef _UNISTD_H
# error "Never include this file directly.  Use <unistd.h> instead"
#endif
# 21 "/usr/include/x86_64-linux-gnu/bits/environments.h" 3 4

#if 0 /* expanded by -frewrite-includes */
#include <bits/wordsize.h>
#endif /* expanded by -frewrite-includes */
# 22 "/usr/include/x86_64-linux-gnu/bits/environments.h" 3 4
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
# 23 "/usr/include/x86_64-linux-gnu/bits/environments.h" 2 3 4

/* This header should define the following symbols under the described
   situations.  A value `1' means that the model is always supported,
   `-1' means it is never supported.  Undefined means it cannot be
   statically decided.

   _POSIX_V7_ILP32_OFF32   32bit int, long, pointers, and off_t type
   _POSIX_V7_ILP32_OFFBIG  32bit int, long, and pointers and larger off_t type

   _POSIX_V7_LP64_OFF32	   64bit long and pointers and 32bit off_t type
   _POSIX_V7_LPBIG_OFFBIG  64bit long and pointers and large off_t type

   The macros _POSIX_V6_ILP32_OFF32, _POSIX_V6_ILP32_OFFBIG,
   _POSIX_V6_LP64_OFF32, _POSIX_V6_LPBIG_OFFBIG, _XBS5_ILP32_OFF32,
   _XBS5_ILP32_OFFBIG, _XBS5_LP64_OFF32, and _XBS5_LPBIG_OFFBIG were
   used in previous versions of the Unix standard and are available
   only for compatibility.
*/

#if __WORDSIZE == 64

/* Environments with 32-bit wide pointers are optionally provided.
   Therefore following macros aren't defined:
   # undef _POSIX_V7_ILP32_OFF32
   # undef _POSIX_V7_ILP32_OFFBIG
   # undef _POSIX_V6_ILP32_OFF32
   # undef _POSIX_V6_ILP32_OFFBIG
   # undef _XBS5_ILP32_OFF32
   # undef _XBS5_ILP32_OFFBIG
   and users need to check at runtime.  */

/* We also have no use (for now) for an environment with bigger pointers
   and offsets.  */
# define _POSIX_V7_LPBIG_OFFBIG	-1
# define _POSIX_V6_LPBIG_OFFBIG	-1
# define _XBS5_LPBIG_OFFBIG	-1

/* By default we have 64-bit wide `long int', pointers and `off_t'.  */
# define _POSIX_V7_LP64_OFF64	1
# define _POSIX_V6_LP64_OFF64	1
# define _XBS5_LP64_OFF64	1

#else /* __WORDSIZE == 32 */
# 66 "/usr/include/x86_64-linux-gnu/bits/environments.h" 3 4

/* We have 32-bit wide `int', `long int' and pointers and all platforms
   support LFS.  -mx32 has 64-bit wide `off_t'.  */
# define _POSIX_V7_ILP32_OFFBIG	1
# define _POSIX_V6_ILP32_OFFBIG 1
# define _XBS5_ILP32_OFFBIG	1

# ifndef __x86_64__
/* -m32 has 32-bit wide `off_t'.  */
#  define _POSIX_V7_ILP32_OFF32	1
#  define _POSIX_V6_ILP32_OFF32	1
#  define _XBS5_ILP32_OFF32	1
# endif
# 79 "/usr/include/x86_64-linux-gnu/bits/environments.h" 3 4

/* We optionally provide an environment with the above size but an 64-bit
   side `off_t'.  Therefore we don't define _POSIX_V7_ILP32_OFFBIG.  */

/* Environments with 64-bit wide pointers can be provided,
   so these macros aren't defined:
   # undef _POSIX_V7_LP64_OFF64
   # undef _POSIX_V7_LPBIG_OFFBIG
   # undef _POSIX_V6_LP64_OFF64
   # undef _POSIX_V6_LPBIG_OFFBIG
   # undef _XBS5_LP64_OFF64
   # undef _XBS5_LPBIG_OFFBIG
   and sysconf tests for it at runtime.  */

#endif /* __WORDSIZE == 32 */
# 94 "/usr/include/x86_64-linux-gnu/bits/environments.h" 3 4

#define __ILP32_OFF32_CFLAGS	"-m32"
#define __ILP32_OFF32_LDFLAGS	"-m32"
#if defined __x86_64__ && defined __ILP32__
# define __ILP32_OFFBIG_CFLAGS	"-mx32"
# define __ILP32_OFFBIG_LDFLAGS	"-mx32"
#else
# 101 "/usr/include/x86_64-linux-gnu/bits/environments.h" 3 4
# define __ILP32_OFFBIG_CFLAGS	"-m32 -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64"
# define __ILP32_OFFBIG_LDFLAGS	"-m32"
#endif
# 104 "/usr/include/x86_64-linux-gnu/bits/environments.h" 3 4
#define __LP64_OFF64_CFLAGS	"-m64"
#define __LP64_OFF64_LDFLAGS	"-m64"
# 210 "/usr/include/unistd.h" 2 3 4
#endif
# 211 "/usr/include/unistd.h" 3 4

/* Standard file descriptors.  */
#define	STDIN_FILENO	0	/* Standard input.  */
#define	STDOUT_FILENO	1	/* Standard output.  */
#define	STDERR_FILENO	2	/* Standard error output.  */


/* All functions that are not declared anywhere else.  */

#if 0 /* expanded by -frewrite-includes */
#include <bits/types.h>
#endif /* expanded by -frewrite-includes */
# 220 "/usr/include/unistd.h" 3 4
# 221 "/usr/include/unistd.h" 3 4

#ifndef	__ssize_t_defined
typedef __ssize_t ssize_t;
# define __ssize_t_defined
#endif
# 226 "/usr/include/unistd.h" 3 4

#define	__need_size_t
#define __need_NULL
#if 0 /* expanded by -frewrite-includes */
#include <stddef.h>
#endif /* expanded by -frewrite-includes */
# 229 "/usr/include/unistd.h" 3 4
# 1 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 1 3 4
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
# 37 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#define __need_ptrdiff_t
#define __need_size_t
#define __need_wchar_t
#define __need_NULL
#define __need_STDDEF_H_misc
/* __need_wint_t is intentionally not defined here. */
#endif
# 44 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_ptrdiff_t)
#if !defined(_PTRDIFF_T) || __has_feature(modules)
/* Always define ptrdiff_t when modules are available. */
#if !__has_feature(modules)
#define _PTRDIFF_T
#endif
# 51 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif
# 53 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_ptrdiff_t
#endif /* defined(__need_ptrdiff_t) */
# 55 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_size_t)
#if !defined(_SIZE_T) || __has_feature(modules)
/* Always define size_t when modules are available. */
#if !__has_feature(modules)
#define _SIZE_T
#endif
# 62 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ size_t;
#endif
# 64 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_size_t
#endif /*defined(__need_size_t) */
# 66 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
/* ISO9899:2011 7.20 (C11 Annex K): Define rsize_t if __STDC_WANT_LIB_EXT1__ is
 * enabled. */
#if (defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ >= 1 && \
     !defined(_RSIZE_T)) || __has_feature(modules)
/* Always define rsize_t when modules are available. */
#if !__has_feature(modules)
#define _RSIZE_T
#endif
# 76 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ rsize_t;
#endif
# 78 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif /* defined(__need_STDDEF_H_misc) */
# 79 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_wchar_t)
#ifndef __cplusplus
/* Always define wchar_t when modules are available. */
#if !defined(_WCHAR_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WCHAR_T
#if defined(_MSC_EXTENSIONS)
#define _WCHAR_T_DEFINED
#endif
# 89 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 90 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WCHAR_TYPE__ wchar_t;
#endif
# 92 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 93 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wchar_t
#endif /* defined(__need_wchar_t) */
# 95 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_NULL)
#undef NULL
#ifdef __cplusplus
#  if !defined(__MINGW32__) && !defined(_MSC_VER)
#    define NULL __null
#  else
# 102 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#    define NULL 0
#  endif
# 104 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#else
# 105 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#  define NULL ((void*)0)
#endif
# 107 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#ifdef __cplusplus
#if defined(_MSC_EXTENSIONS) && defined(_NATIVE_NULLPTR_SUPPORTED)
namespace std { typedef decltype(nullptr) nullptr_t; }
using ::std::nullptr_t;
#endif
# 112 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 113 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_NULL
#endif /* defined(__need_NULL) */
# 115 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
#if __STDC_VERSION__ >= 201112L || __cplusplus >= 201103L
#if 0 /* expanded by -frewrite-includes */
#include "__stddef_max_align_t.h"
#endif /* expanded by -frewrite-includes */
# 118 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
# 119 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 120 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#define offsetof(t, d) __builtin_offsetof(t, d)
#undef __need_STDDEF_H_misc
#endif  /* defined(__need_STDDEF_H_misc) */
# 123 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

/* Some C libraries expect to see a wint_t here. Others (notably MinGW) will use
__WINT_TYPE__ directly; accommodate both by requiring __need_wint_t */
#if defined(__need_wint_t)
/* Always define wint_t when modules are available. */
#if !defined(_WINT_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WINT_T
#endif
# 132 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WINT_TYPE__ wint_t;
#endif
# 134 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wint_t
#endif /* __need_wint_t */
# 136 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#endif
# 138 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
# 230 "/usr/include/unistd.h" 2 3 4

#if defined __USE_XOPEN || defined __USE_XOPEN2K
/* The Single Unix specification says that some more types are
   available here.  */
# ifndef __gid_t_defined
typedef __gid_t gid_t;
#  define __gid_t_defined
# endif
# 238 "/usr/include/unistd.h" 3 4

# ifndef __uid_t_defined
typedef __uid_t uid_t;
#  define __uid_t_defined
# endif
# 243 "/usr/include/unistd.h" 3 4

# ifndef __off_t_defined
#  ifndef __USE_FILE_OFFSET64
typedef __off_t off_t;
#  else
# 248 "/usr/include/unistd.h" 3 4
typedef __off64_t off_t;
#  endif
# 250 "/usr/include/unistd.h" 3 4
#  define __off_t_defined
# endif
# 252 "/usr/include/unistd.h" 3 4
# if defined __USE_LARGEFILE64 && !defined __off64_t_defined
typedef __off64_t off64_t;
#  define __off64_t_defined
# endif
# 256 "/usr/include/unistd.h" 3 4

# ifndef __useconds_t_defined
typedef __useconds_t useconds_t;
#  define __useconds_t_defined
# endif
# 261 "/usr/include/unistd.h" 3 4

# ifndef __pid_t_defined
typedef __pid_t pid_t;
#  define __pid_t_defined
# endif
# 266 "/usr/include/unistd.h" 3 4
#endif	/* X/Open */
# 267 "/usr/include/unistd.h" 3 4

#if defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K
# ifndef __intptr_t_defined
typedef __intptr_t intptr_t;
#  define __intptr_t_defined
# endif
# 273 "/usr/include/unistd.h" 3 4
#endif
# 274 "/usr/include/unistd.h" 3 4

#if defined __USE_MISC || defined __USE_XOPEN
# ifndef __socklen_t_defined
typedef __socklen_t socklen_t;
#  define __socklen_t_defined
# endif
# 280 "/usr/include/unistd.h" 3 4
#endif
# 281 "/usr/include/unistd.h" 3 4

/* Values for the second argument to access.
   These may be OR'd together.  */
#define	R_OK	4		/* Test for read permission.  */
#define	W_OK	2		/* Test for write permission.  */
#define	X_OK	1		/* Test for execute permission.  */
#define	F_OK	0		/* Test for existence.  */

/* Test for access to NAME using the real UID and real GID.  */
extern int access (const char *__name, int __type) __THROW __nonnull ((1));

#ifdef __USE_GNU
/* Test for access to NAME using the effective UID and GID
   (as normal file operations use).  */
extern int euidaccess (const char *__name, int __type)
     __THROW __nonnull ((1));

/* An alias for `euidaccess', used by some other systems.  */
extern int eaccess (const char *__name, int __type)
     __THROW __nonnull ((1));
#endif
# 302 "/usr/include/unistd.h" 3 4

#ifdef __USE_ATFILE
/* Test for access to FILE relative to the directory FD is open on.
   If AT_EACCESS is set in FLAG, then use effective IDs like `eaccess',
   otherwise use real IDs like `access'.  */
extern int faccessat (int __fd, const char *__file, int __type, int __flag)
     __THROW __nonnull ((2)) __wur;
#endif /* Use GNU.  */
# 310 "/usr/include/unistd.h" 3 4


/* Values for the WHENCE argument to lseek.  */
#ifndef	_STDIO_H		/* <stdio.h> has the same definitions.  */
# define SEEK_SET	0	/* Seek from beginning of file.  */
# define SEEK_CUR	1	/* Seek from current position.  */
# define SEEK_END	2	/* Seek from end of file.  */
# ifdef __USE_GNU
#  define SEEK_DATA	3	/* Seek to next data.  */
#  define SEEK_HOLE	4	/* Seek to next hole.  */
# endif
# 321 "/usr/include/unistd.h" 3 4
#endif
# 322 "/usr/include/unistd.h" 3 4

#if defined __USE_MISC && !defined L_SET
/* Old BSD names for the same constants; just for compatibility.  */
# define L_SET		SEEK_SET
# define L_INCR		SEEK_CUR
# define L_XTND		SEEK_END
#endif
# 329 "/usr/include/unistd.h" 3 4


/* Move FD's file position to OFFSET bytes from the
   beginning of the file (if WHENCE is SEEK_SET),
   the current position (if WHENCE is SEEK_CUR),
   or the end of the file (if WHENCE is SEEK_END).
   Return the new file position.  */
#ifndef __USE_FILE_OFFSET64
extern __off_t lseek (int __fd, __off_t __offset, int __whence) __THROW;
#else
# 339 "/usr/include/unistd.h" 3 4
# ifdef __REDIRECT_NTH
extern __off64_t __REDIRECT_NTH (lseek,
				 (int __fd, __off64_t __offset, int __whence),
				 lseek64);
# else
# 344 "/usr/include/unistd.h" 3 4
#  define lseek lseek64
# endif
# 346 "/usr/include/unistd.h" 3 4
#endif
# 347 "/usr/include/unistd.h" 3 4
#ifdef __USE_LARGEFILE64
extern __off64_t lseek64 (int __fd, __off64_t __offset, int __whence)
     __THROW;
#endif
# 351 "/usr/include/unistd.h" 3 4

/* Close the file descriptor FD.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern int close (int __fd);

/* Read NBYTES into BUF from FD.  Return the
   number read, -1 for errors or 0 for EOF.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern ssize_t read (int __fd, void *__buf, size_t __nbytes) __wur;

/* Write N bytes of BUF to FD.  Return the number written, or -1.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern ssize_t write (int __fd, const void *__buf, size_t __n) __wur;

#if defined __USE_UNIX98 || defined __USE_XOPEN2K8
# ifndef __USE_FILE_OFFSET64
/* Read NBYTES into BUF from FD at the given position OFFSET without
   changing the file pointer.  Return the number read, -1 for errors
   or 0 for EOF.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern ssize_t pread (int __fd, void *__buf, size_t __nbytes,
		      __off_t __offset) __wur;

/* Write N bytes of BUF to FD at the given position OFFSET without
   changing the file pointer.  Return the number written, or -1.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern ssize_t pwrite (int __fd, const void *__buf, size_t __n,
		       __off_t __offset) __wur;
# else
# 390 "/usr/include/unistd.h" 3 4
#  ifdef __REDIRECT
extern ssize_t __REDIRECT (pread, (int __fd, void *__buf, size_t __nbytes,
				   __off64_t __offset),
			   pread64) __wur;
extern ssize_t __REDIRECT (pwrite, (int __fd, const void *__buf,
				    size_t __nbytes, __off64_t __offset),
			   pwrite64) __wur;
#  else
# 398 "/usr/include/unistd.h" 3 4
#   define pread pread64
#   define pwrite pwrite64
#  endif
# 401 "/usr/include/unistd.h" 3 4
# endif
# 402 "/usr/include/unistd.h" 3 4

# ifdef __USE_LARGEFILE64
/* Read NBYTES into BUF from FD at the given position OFFSET without
   changing the file pointer.  Return the number read, -1 for errors
   or 0 for EOF.  */
extern ssize_t pread64 (int __fd, void *__buf, size_t __nbytes,
			__off64_t __offset) __wur;
/* Write N bytes of BUF to FD at the given position OFFSET without
   changing the file pointer.  Return the number written, or -1.  */
extern ssize_t pwrite64 (int __fd, const void *__buf, size_t __n,
			 __off64_t __offset) __wur;
# endif
# 414 "/usr/include/unistd.h" 3 4
#endif
# 415 "/usr/include/unistd.h" 3 4

/* Create a one-way communication channel (pipe).
   If successful, two file descriptors are stored in PIPEDES;
   bytes written on PIPEDES[1] can be read from PIPEDES[0].
   Returns 0 if successful, -1 if not.  */
extern int pipe (int __pipedes[2]) __THROW __wur;

#ifdef __USE_GNU
/* Same as pipe but apply flags passed in FLAGS to the new file
   descriptors.  */
extern int pipe2 (int __pipedes[2], int __flags) __THROW __wur;
#endif
# 427 "/usr/include/unistd.h" 3 4

/* Schedule an alarm.  In SECONDS seconds, the process will get a SIGALRM.
   If SECONDS is zero, any currently scheduled alarm will be cancelled.
   The function returns the number of seconds remaining until the last
   alarm scheduled would have signaled, or zero if there wasn't one.
   There is no return value to indicate an error, but you can set `errno'
   to 0 and check its value after calling `alarm', and this might tell you.
   The signal may come late due to processor scheduling.  */
extern unsigned int alarm (unsigned int __seconds) __THROW;

/* Make the process sleep for SECONDS seconds, or until a signal arrives
   and is not ignored.  The function returns the number of seconds less
   than SECONDS which it actually slept (thus zero if it slept the full time).
   If a signal handler does a `longjmp' or modifies the handling of the
   SIGALRM signal while inside `sleep' call, the handling of the SIGALRM
   signal afterwards is undefined.  There is no return value to indicate
   error, but if `sleep' returns SECONDS, it probably didn't work.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern unsigned int sleep (unsigned int __seconds);

#if (defined __USE_XOPEN_EXTENDED && !defined __USE_XOPEN2K8) \
    || defined __USE_MISC
/* Set an alarm to go off (generating a SIGALRM signal) in VALUE
   microseconds.  If INTERVAL is nonzero, when the alarm goes off, the
   timer is reset to go off every INTERVAL microseconds thereafter.
   Returns the number of microseconds remaining before the alarm.  */
extern __useconds_t ualarm (__useconds_t __value, __useconds_t __interval)
     __THROW;

/* Sleep USECONDS microseconds, or until a signal arrives that is not blocked
   or ignored.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern int usleep (__useconds_t __useconds);
#endif
# 465 "/usr/include/unistd.h" 3 4


/* Suspend the process until a signal arrives.
   This always returns -1 and sets `errno' to EINTR.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern int pause (void);


/* Change the owner and group of FILE.  */
extern int chown (const char *__file, __uid_t __owner, __gid_t __group)
     __THROW __nonnull ((1)) __wur;

#if defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8
/* Change the owner and group of the file that FD is open on.  */
extern int fchown (int __fd, __uid_t __owner, __gid_t __group) __THROW __wur;


/* Change owner and group of FILE, if it is a symbolic
   link the ownership of the symbolic link is changed.  */
extern int lchown (const char *__file, __uid_t __owner, __gid_t __group)
     __THROW __nonnull ((1)) __wur;

#endif /* Use X/Open Unix.  */
# 490 "/usr/include/unistd.h" 3 4

#ifdef __USE_ATFILE
/* Change the owner and group of FILE relative to the directory FD is open
   on.  */
extern int fchownat (int __fd, const char *__file, __uid_t __owner,
		     __gid_t __group, int __flag)
     __THROW __nonnull ((2)) __wur;
#endif /* Use GNU.  */
# 498 "/usr/include/unistd.h" 3 4

/* Change the process's working directory to PATH.  */
extern int chdir (const char *__path) __THROW __nonnull ((1)) __wur;

#if defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8
/* Change the process's working directory to the one FD is open on.  */
extern int fchdir (int __fd) __THROW __wur;
#endif
# 506 "/usr/include/unistd.h" 3 4

/* Get the pathname of the current working directory,
   and put it in SIZE bytes of BUF.  Returns NULL if the
   directory couldn't be determined or SIZE was too small.
   If successful, returns BUF.  In GNU, if BUF is NULL,
   an array is allocated with `malloc'; the array is SIZE
   bytes long, unless SIZE == 0, in which case it is as
   big as necessary.  */
extern char *getcwd (char *__buf, size_t __size) __THROW __wur;

#ifdef	__USE_GNU
/* Return a malloc'd string containing the current directory name.
   If the environment variable `PWD' is set, and its value is correct,
   that value is used.  */
extern char *get_current_dir_name (void) __THROW;
#endif
# 522 "/usr/include/unistd.h" 3 4

#if (defined __USE_XOPEN_EXTENDED && !defined __USE_XOPEN2K8) \
    || defined __USE_MISC
/* Put the absolute pathname of the current working directory in BUF.
   If successful, return BUF.  If not, put an error message in
   BUF and return NULL.  BUF should be at least PATH_MAX bytes long.  */
extern char *getwd (char *__buf)
     __THROW __nonnull ((1)) __attribute_deprecated__ __wur;
#endif
# 531 "/usr/include/unistd.h" 3 4


/* Duplicate FD, returning a new file descriptor on the same file.  */
extern int dup (int __fd) __THROW __wur;

/* Duplicate FD to FD2, closing FD2 and making it open on the same file.  */
extern int dup2 (int __fd, int __fd2) __THROW;

#ifdef __USE_GNU
/* Duplicate FD to FD2, closing FD2 and making it open on the same
   file while setting flags according to FLAGS.  */
extern int dup3 (int __fd, int __fd2, int __flags) __THROW;
#endif
# 544 "/usr/include/unistd.h" 3 4

/* NULL-terminated array of "NAME=VALUE" environment variables.  */
extern char **__environ;
#ifdef __USE_GNU
extern char **environ;
#endif
# 550 "/usr/include/unistd.h" 3 4


/* Replace the current process, executing PATH with arguments ARGV and
   environment ENVP.  ARGV and ENVP are terminated by NULL pointers.  */
extern int execve (const char *__path, char *const __argv[],
		   char *const __envp[]) __THROW __nonnull ((1, 2));

#ifdef __USE_XOPEN2K8
/* Execute the file FD refers to, overlaying the running program image.
   ARGV and ENVP are passed to the new program, as for `execve'.  */
extern int fexecve (int __fd, char *const __argv[], char *const __envp[])
     __THROW __nonnull ((2));
#endif
# 563 "/usr/include/unistd.h" 3 4


/* Execute PATH with arguments ARGV and environment from `environ'.  */
extern int execv (const char *__path, char *const __argv[])
     __THROW __nonnull ((1, 2));

/* Execute PATH with all arguments after PATH until a NULL pointer,
   and the argument after that for environment.  */
extern int execle (const char *__path, const char *__arg, ...)
     __THROW __nonnull ((1, 2));

/* Execute PATH with all arguments after PATH until
   a NULL pointer and environment from `environ'.  */
extern int execl (const char *__path, const char *__arg, ...)
     __THROW __nonnull ((1, 2));

/* Execute FILE, searching in the `PATH' environment variable if it contains
   no slashes, with arguments ARGV and environment from `environ'.  */
extern int execvp (const char *__file, char *const __argv[])
     __THROW __nonnull ((1, 2));

/* Execute FILE, searching in the `PATH' environment variable if
   it contains no slashes, with all arguments after FILE until a
   NULL pointer and environment from `environ'.  */
extern int execlp (const char *__file, const char *__arg, ...)
     __THROW __nonnull ((1, 2));

#ifdef __USE_GNU
/* Execute FILE, searching in the `PATH' environment variable if it contains
   no slashes, with arguments ARGV and environment from `environ'.  */
extern int execvpe (const char *__file, char *const __argv[],
		    char *const __envp[])
     __THROW __nonnull ((1, 2));
#endif
# 597 "/usr/include/unistd.h" 3 4


#if defined __USE_MISC || defined __USE_XOPEN
/* Add INC to priority of the current process.  */
extern int nice (int __inc) __THROW __wur;
#endif
# 603 "/usr/include/unistd.h" 3 4


/* Terminate program execution with the low-order 8 bits of STATUS.  */
extern void _exit (int __status) __attribute__ ((__noreturn__));


/* Get the `_PC_*' symbols for the NAME argument to `pathconf' and `fpathconf';
   the `_SC_*' symbols for the NAME argument to `sysconf';
   and the `_CS_*' symbols for the NAME argument to `confstr'.  */
#if 0 /* expanded by -frewrite-includes */
#include <bits/confname.h>
#endif /* expanded by -frewrite-includes */
# 612 "/usr/include/unistd.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/confname.h" 1 3 4
/* `sysconf', `pathconf', and `confstr' NAME values.  Generic version.
   Copyright (C) 1993-2016 Free Software Foundation, Inc.
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

#ifndef _UNISTD_H
# error "Never use <bits/confname.h> directly; include <unistd.h> instead."
#endif
# 22 "/usr/include/x86_64-linux-gnu/bits/confname.h" 3 4

/* Values for the NAME argument to `pathconf' and `fpathconf'.  */
enum
  {
    _PC_LINK_MAX,
#define	_PC_LINK_MAX			_PC_LINK_MAX
    _PC_MAX_CANON,
#define	_PC_MAX_CANON			_PC_MAX_CANON
    _PC_MAX_INPUT,
#define	_PC_MAX_INPUT			_PC_MAX_INPUT
    _PC_NAME_MAX,
#define	_PC_NAME_MAX			_PC_NAME_MAX
    _PC_PATH_MAX,
#define	_PC_PATH_MAX			_PC_PATH_MAX
    _PC_PIPE_BUF,
#define	_PC_PIPE_BUF			_PC_PIPE_BUF
    _PC_CHOWN_RESTRICTED,
#define	_PC_CHOWN_RESTRICTED		_PC_CHOWN_RESTRICTED
    _PC_NO_TRUNC,
#define	_PC_NO_TRUNC			_PC_NO_TRUNC
    _PC_VDISABLE,
#define _PC_VDISABLE			_PC_VDISABLE
    _PC_SYNC_IO,
#define	_PC_SYNC_IO			_PC_SYNC_IO
    _PC_ASYNC_IO,
#define	_PC_ASYNC_IO			_PC_ASYNC_IO
    _PC_PRIO_IO,
#define	_PC_PRIO_IO			_PC_PRIO_IO
    _PC_SOCK_MAXBUF,
#define	_PC_SOCK_MAXBUF			_PC_SOCK_MAXBUF
    _PC_FILESIZEBITS,
#define _PC_FILESIZEBITS		_PC_FILESIZEBITS
    _PC_REC_INCR_XFER_SIZE,
#define _PC_REC_INCR_XFER_SIZE		_PC_REC_INCR_XFER_SIZE
    _PC_REC_MAX_XFER_SIZE,
#define _PC_REC_MAX_XFER_SIZE		_PC_REC_MAX_XFER_SIZE
    _PC_REC_MIN_XFER_SIZE,
#define _PC_REC_MIN_XFER_SIZE		_PC_REC_MIN_XFER_SIZE
    _PC_REC_XFER_ALIGN,
#define _PC_REC_XFER_ALIGN		_PC_REC_XFER_ALIGN
    _PC_ALLOC_SIZE_MIN,
#define _PC_ALLOC_SIZE_MIN		_PC_ALLOC_SIZE_MIN
    _PC_SYMLINK_MAX,
#define _PC_SYMLINK_MAX			_PC_SYMLINK_MAX
    _PC_2_SYMLINKS
#define _PC_2_SYMLINKS			_PC_2_SYMLINKS
  };

/* Values for the argument to `sysconf'.  */
enum
  {
    _SC_ARG_MAX,
#define	_SC_ARG_MAX			_SC_ARG_MAX
    _SC_CHILD_MAX,
#define	_SC_CHILD_MAX			_SC_CHILD_MAX
    _SC_CLK_TCK,
#define	_SC_CLK_TCK			_SC_CLK_TCK
    _SC_NGROUPS_MAX,
#define	_SC_NGROUPS_MAX			_SC_NGROUPS_MAX
    _SC_OPEN_MAX,
#define	_SC_OPEN_MAX			_SC_OPEN_MAX
    _SC_STREAM_MAX,
#define	_SC_STREAM_MAX			_SC_STREAM_MAX
    _SC_TZNAME_MAX,
#define	_SC_TZNAME_MAX			_SC_TZNAME_MAX
    _SC_JOB_CONTROL,
#define	_SC_JOB_CONTROL			_SC_JOB_CONTROL
    _SC_SAVED_IDS,
#define	_SC_SAVED_IDS			_SC_SAVED_IDS
    _SC_REALTIME_SIGNALS,
#define	_SC_REALTIME_SIGNALS		_SC_REALTIME_SIGNALS
    _SC_PRIORITY_SCHEDULING,
#define	_SC_PRIORITY_SCHEDULING		_SC_PRIORITY_SCHEDULING
    _SC_TIMERS,
#define	_SC_TIMERS			_SC_TIMERS
    _SC_ASYNCHRONOUS_IO,
#define	_SC_ASYNCHRONOUS_IO		_SC_ASYNCHRONOUS_IO
    _SC_PRIORITIZED_IO,
#define	_SC_PRIORITIZED_IO		_SC_PRIORITIZED_IO
    _SC_SYNCHRONIZED_IO,
#define	_SC_SYNCHRONIZED_IO		_SC_SYNCHRONIZED_IO
    _SC_FSYNC,
#define	_SC_FSYNC			_SC_FSYNC
    _SC_MAPPED_FILES,
#define	_SC_MAPPED_FILES		_SC_MAPPED_FILES
    _SC_MEMLOCK,
#define	_SC_MEMLOCK			_SC_MEMLOCK
    _SC_MEMLOCK_RANGE,
#define	_SC_MEMLOCK_RANGE		_SC_MEMLOCK_RANGE
    _SC_MEMORY_PROTECTION,
#define	_SC_MEMORY_PROTECTION		_SC_MEMORY_PROTECTION
    _SC_MESSAGE_PASSING,
#define	_SC_MESSAGE_PASSING		_SC_MESSAGE_PASSING
    _SC_SEMAPHORES,
#define	_SC_SEMAPHORES			_SC_SEMAPHORES
    _SC_SHARED_MEMORY_OBJECTS,
#define	_SC_SHARED_MEMORY_OBJECTS	_SC_SHARED_MEMORY_OBJECTS
    _SC_AIO_LISTIO_MAX,
#define	_SC_AIO_LISTIO_MAX		_SC_AIO_LISTIO_MAX
    _SC_AIO_MAX,
#define	_SC_AIO_MAX			_SC_AIO_MAX
    _SC_AIO_PRIO_DELTA_MAX,
#define	_SC_AIO_PRIO_DELTA_MAX		_SC_AIO_PRIO_DELTA_MAX
    _SC_DELAYTIMER_MAX,
#define	_SC_DELAYTIMER_MAX		_SC_DELAYTIMER_MAX
    _SC_MQ_OPEN_MAX,
#define	_SC_MQ_OPEN_MAX			_SC_MQ_OPEN_MAX
    _SC_MQ_PRIO_MAX,
#define	_SC_MQ_PRIO_MAX			_SC_MQ_PRIO_MAX
    _SC_VERSION,
#define	_SC_VERSION			_SC_VERSION
    _SC_PAGESIZE,
#define	_SC_PAGESIZE			_SC_PAGESIZE
#define	_SC_PAGE_SIZE			_SC_PAGESIZE
    _SC_RTSIG_MAX,
#define	_SC_RTSIG_MAX			_SC_RTSIG_MAX
    _SC_SEM_NSEMS_MAX,
#define	_SC_SEM_NSEMS_MAX		_SC_SEM_NSEMS_MAX
    _SC_SEM_VALUE_MAX,
#define	_SC_SEM_VALUE_MAX		_SC_SEM_VALUE_MAX
    _SC_SIGQUEUE_MAX,
#define	_SC_SIGQUEUE_MAX		_SC_SIGQUEUE_MAX
    _SC_TIMER_MAX,
#define	_SC_TIMER_MAX			_SC_TIMER_MAX

    /* Values for the argument to `sysconf'
       corresponding to _POSIX2_* symbols.  */
    _SC_BC_BASE_MAX,
#define	_SC_BC_BASE_MAX			_SC_BC_BASE_MAX
    _SC_BC_DIM_MAX,
#define	_SC_BC_DIM_MAX			_SC_BC_DIM_MAX
    _SC_BC_SCALE_MAX,
#define	_SC_BC_SCALE_MAX		_SC_BC_SCALE_MAX
    _SC_BC_STRING_MAX,
#define	_SC_BC_STRING_MAX		_SC_BC_STRING_MAX
    _SC_COLL_WEIGHTS_MAX,
#define	_SC_COLL_WEIGHTS_MAX		_SC_COLL_WEIGHTS_MAX
    _SC_EQUIV_CLASS_MAX,
#define	_SC_EQUIV_CLASS_MAX		_SC_EQUIV_CLASS_MAX
    _SC_EXPR_NEST_MAX,
#define	_SC_EXPR_NEST_MAX		_SC_EXPR_NEST_MAX
    _SC_LINE_MAX,
#define	_SC_LINE_MAX			_SC_LINE_MAX
    _SC_RE_DUP_MAX,
#define	_SC_RE_DUP_MAX			_SC_RE_DUP_MAX
    _SC_CHARCLASS_NAME_MAX,
#define	_SC_CHARCLASS_NAME_MAX		_SC_CHARCLASS_NAME_MAX

    _SC_2_VERSION,
#define	_SC_2_VERSION			_SC_2_VERSION
    _SC_2_C_BIND,
#define	_SC_2_C_BIND			_SC_2_C_BIND
    _SC_2_C_DEV,
#define	_SC_2_C_DEV			_SC_2_C_DEV
    _SC_2_FORT_DEV,
#define	_SC_2_FORT_DEV			_SC_2_FORT_DEV
    _SC_2_FORT_RUN,
#define	_SC_2_FORT_RUN			_SC_2_FORT_RUN
    _SC_2_SW_DEV,
#define	_SC_2_SW_DEV			_SC_2_SW_DEV
    _SC_2_LOCALEDEF,
#define	_SC_2_LOCALEDEF			_SC_2_LOCALEDEF

    _SC_PII,
#define	_SC_PII				_SC_PII
    _SC_PII_XTI,
#define	_SC_PII_XTI			_SC_PII_XTI
    _SC_PII_SOCKET,
#define	_SC_PII_SOCKET			_SC_PII_SOCKET
    _SC_PII_INTERNET,
#define	_SC_PII_INTERNET		_SC_PII_INTERNET
    _SC_PII_OSI,
#define	_SC_PII_OSI			_SC_PII_OSI
    _SC_POLL,
#define	_SC_POLL			_SC_POLL
    _SC_SELECT,
#define	_SC_SELECT			_SC_SELECT
    _SC_UIO_MAXIOV,
#define	_SC_UIO_MAXIOV			_SC_UIO_MAXIOV
    _SC_IOV_MAX = _SC_UIO_MAXIOV,
#define _SC_IOV_MAX			_SC_IOV_MAX
    _SC_PII_INTERNET_STREAM,
#define	_SC_PII_INTERNET_STREAM		_SC_PII_INTERNET_STREAM
    _SC_PII_INTERNET_DGRAM,
#define	_SC_PII_INTERNET_DGRAM		_SC_PII_INTERNET_DGRAM
    _SC_PII_OSI_COTS,
#define	_SC_PII_OSI_COTS		_SC_PII_OSI_COTS
    _SC_PII_OSI_CLTS,
#define	_SC_PII_OSI_CLTS		_SC_PII_OSI_CLTS
    _SC_PII_OSI_M,
#define	_SC_PII_OSI_M			_SC_PII_OSI_M
    _SC_T_IOV_MAX,
#define	_SC_T_IOV_MAX			_SC_T_IOV_MAX

    /* Values according to POSIX 1003.1c (POSIX threads).  */
    _SC_THREADS,
#define	_SC_THREADS			_SC_THREADS
    _SC_THREAD_SAFE_FUNCTIONS,
#define _SC_THREAD_SAFE_FUNCTIONS	_SC_THREAD_SAFE_FUNCTIONS
    _SC_GETGR_R_SIZE_MAX,
#define	_SC_GETGR_R_SIZE_MAX		_SC_GETGR_R_SIZE_MAX
    _SC_GETPW_R_SIZE_MAX,
#define	_SC_GETPW_R_SIZE_MAX		_SC_GETPW_R_SIZE_MAX
    _SC_LOGIN_NAME_MAX,
#define	_SC_LOGIN_NAME_MAX		_SC_LOGIN_NAME_MAX
    _SC_TTY_NAME_MAX,
#define	_SC_TTY_NAME_MAX		_SC_TTY_NAME_MAX
    _SC_THREAD_DESTRUCTOR_ITERATIONS,
#define	_SC_THREAD_DESTRUCTOR_ITERATIONS _SC_THREAD_DESTRUCTOR_ITERATIONS
    _SC_THREAD_KEYS_MAX,
#define	_SC_THREAD_KEYS_MAX		_SC_THREAD_KEYS_MAX
    _SC_THREAD_STACK_MIN,
#define	_SC_THREAD_STACK_MIN		_SC_THREAD_STACK_MIN
    _SC_THREAD_THREADS_MAX,
#define	_SC_THREAD_THREADS_MAX		_SC_THREAD_THREADS_MAX
    _SC_THREAD_ATTR_STACKADDR,
#define	_SC_THREAD_ATTR_STACKADDR	_SC_THREAD_ATTR_STACKADDR
    _SC_THREAD_ATTR_STACKSIZE,
#define	_SC_THREAD_ATTR_STACKSIZE	_SC_THREAD_ATTR_STACKSIZE
    _SC_THREAD_PRIORITY_SCHEDULING,
#define	_SC_THREAD_PRIORITY_SCHEDULING	_SC_THREAD_PRIORITY_SCHEDULING
    _SC_THREAD_PRIO_INHERIT,
#define	_SC_THREAD_PRIO_INHERIT		_SC_THREAD_PRIO_INHERIT
    _SC_THREAD_PRIO_PROTECT,
#define	_SC_THREAD_PRIO_PROTECT		_SC_THREAD_PRIO_PROTECT
    _SC_THREAD_PROCESS_SHARED,
#define	_SC_THREAD_PROCESS_SHARED	_SC_THREAD_PROCESS_SHARED

    _SC_NPROCESSORS_CONF,
#define _SC_NPROCESSORS_CONF		_SC_NPROCESSORS_CONF
    _SC_NPROCESSORS_ONLN,
#define _SC_NPROCESSORS_ONLN		_SC_NPROCESSORS_ONLN
    _SC_PHYS_PAGES,
#define _SC_PHYS_PAGES			_SC_PHYS_PAGES
    _SC_AVPHYS_PAGES,
#define _SC_AVPHYS_PAGES		_SC_AVPHYS_PAGES
    _SC_ATEXIT_MAX,
#define _SC_ATEXIT_MAX			_SC_ATEXIT_MAX
    _SC_PASS_MAX,
#define _SC_PASS_MAX			_SC_PASS_MAX

    _SC_XOPEN_VERSION,
#define _SC_XOPEN_VERSION		_SC_XOPEN_VERSION
    _SC_XOPEN_XCU_VERSION,
#define _SC_XOPEN_XCU_VERSION		_SC_XOPEN_XCU_VERSION
    _SC_XOPEN_UNIX,
#define _SC_XOPEN_UNIX			_SC_XOPEN_UNIX
    _SC_XOPEN_CRYPT,
#define _SC_XOPEN_CRYPT			_SC_XOPEN_CRYPT
    _SC_XOPEN_ENH_I18N,
#define _SC_XOPEN_ENH_I18N		_SC_XOPEN_ENH_I18N
    _SC_XOPEN_SHM,
#define _SC_XOPEN_SHM			_SC_XOPEN_SHM

    _SC_2_CHAR_TERM,
#define _SC_2_CHAR_TERM			_SC_2_CHAR_TERM
    _SC_2_C_VERSION,
#define _SC_2_C_VERSION			_SC_2_C_VERSION
    _SC_2_UPE,
#define _SC_2_UPE			_SC_2_UPE

    _SC_XOPEN_XPG2,
#define _SC_XOPEN_XPG2			_SC_XOPEN_XPG2
    _SC_XOPEN_XPG3,
#define _SC_XOPEN_XPG3			_SC_XOPEN_XPG3
    _SC_XOPEN_XPG4,
#define _SC_XOPEN_XPG4			_SC_XOPEN_XPG4

    _SC_CHAR_BIT,
#define	_SC_CHAR_BIT			_SC_CHAR_BIT
    _SC_CHAR_MAX,
#define	_SC_CHAR_MAX			_SC_CHAR_MAX
    _SC_CHAR_MIN,
#define	_SC_CHAR_MIN			_SC_CHAR_MIN
    _SC_INT_MAX,
#define	_SC_INT_MAX			_SC_INT_MAX
    _SC_INT_MIN,
#define	_SC_INT_MIN			_SC_INT_MIN
    _SC_LONG_BIT,
#define	_SC_LONG_BIT			_SC_LONG_BIT
    _SC_WORD_BIT,
#define	_SC_WORD_BIT			_SC_WORD_BIT
    _SC_MB_LEN_MAX,
#define	_SC_MB_LEN_MAX			_SC_MB_LEN_MAX
    _SC_NZERO,
#define	_SC_NZERO			_SC_NZERO
    _SC_SSIZE_MAX,
#define	_SC_SSIZE_MAX			_SC_SSIZE_MAX
    _SC_SCHAR_MAX,
#define	_SC_SCHAR_MAX			_SC_SCHAR_MAX
    _SC_SCHAR_MIN,
#define	_SC_SCHAR_MIN			_SC_SCHAR_MIN
    _SC_SHRT_MAX,
#define	_SC_SHRT_MAX			_SC_SHRT_MAX
    _SC_SHRT_MIN,
#define	_SC_SHRT_MIN			_SC_SHRT_MIN
    _SC_UCHAR_MAX,
#define	_SC_UCHAR_MAX			_SC_UCHAR_MAX
    _SC_UINT_MAX,
#define	_SC_UINT_MAX			_SC_UINT_MAX
    _SC_ULONG_MAX,
#define	_SC_ULONG_MAX			_SC_ULONG_MAX
    _SC_USHRT_MAX,
#define	_SC_USHRT_MAX			_SC_USHRT_MAX

    _SC_NL_ARGMAX,
#define	_SC_NL_ARGMAX			_SC_NL_ARGMAX
    _SC_NL_LANGMAX,
#define	_SC_NL_LANGMAX			_SC_NL_LANGMAX
    _SC_NL_MSGMAX,
#define	_SC_NL_MSGMAX			_SC_NL_MSGMAX
    _SC_NL_NMAX,
#define	_SC_NL_NMAX			_SC_NL_NMAX
    _SC_NL_SETMAX,
#define	_SC_NL_SETMAX			_SC_NL_SETMAX
    _SC_NL_TEXTMAX,
#define	_SC_NL_TEXTMAX			_SC_NL_TEXTMAX

    _SC_XBS5_ILP32_OFF32,
#define _SC_XBS5_ILP32_OFF32		_SC_XBS5_ILP32_OFF32
    _SC_XBS5_ILP32_OFFBIG,
#define _SC_XBS5_ILP32_OFFBIG		_SC_XBS5_ILP32_OFFBIG
    _SC_XBS5_LP64_OFF64,
#define _SC_XBS5_LP64_OFF64		_SC_XBS5_LP64_OFF64
    _SC_XBS5_LPBIG_OFFBIG,
#define _SC_XBS5_LPBIG_OFFBIG		_SC_XBS5_LPBIG_OFFBIG

    _SC_XOPEN_LEGACY,
#define _SC_XOPEN_LEGACY		_SC_XOPEN_LEGACY
    _SC_XOPEN_REALTIME,
#define _SC_XOPEN_REALTIME		_SC_XOPEN_REALTIME
    _SC_XOPEN_REALTIME_THREADS,
#define _SC_XOPEN_REALTIME_THREADS	_SC_XOPEN_REALTIME_THREADS

    _SC_ADVISORY_INFO,
#define _SC_ADVISORY_INFO		_SC_ADVISORY_INFO
    _SC_BARRIERS,
#define _SC_BARRIERS			_SC_BARRIERS
    _SC_BASE,
#define _SC_BASE			_SC_BASE
    _SC_C_LANG_SUPPORT,
#define _SC_C_LANG_SUPPORT		_SC_C_LANG_SUPPORT
    _SC_C_LANG_SUPPORT_R,
#define _SC_C_LANG_SUPPORT_R		_SC_C_LANG_SUPPORT_R
    _SC_CLOCK_SELECTION,
#define _SC_CLOCK_SELECTION		_SC_CLOCK_SELECTION
    _SC_CPUTIME,
#define _SC_CPUTIME			_SC_CPUTIME
    _SC_THREAD_CPUTIME,
#define _SC_THREAD_CPUTIME		_SC_THREAD_CPUTIME
    _SC_DEVICE_IO,
#define _SC_DEVICE_IO			_SC_DEVICE_IO
    _SC_DEVICE_SPECIFIC,
#define _SC_DEVICE_SPECIFIC		_SC_DEVICE_SPECIFIC
    _SC_DEVICE_SPECIFIC_R,
#define _SC_DEVICE_SPECIFIC_R		_SC_DEVICE_SPECIFIC_R
    _SC_FD_MGMT,
#define _SC_FD_MGMT			_SC_FD_MGMT
    _SC_FIFO,
#define _SC_FIFO			_SC_FIFO
    _SC_PIPE,
#define _SC_PIPE			_SC_PIPE
    _SC_FILE_ATTRIBUTES,
#define _SC_FILE_ATTRIBUTES		_SC_FILE_ATTRIBUTES
    _SC_FILE_LOCKING,
#define _SC_FILE_LOCKING		_SC_FILE_LOCKING
    _SC_FILE_SYSTEM,
#define _SC_FILE_SYSTEM			_SC_FILE_SYSTEM
    _SC_MONOTONIC_CLOCK,
#define _SC_MONOTONIC_CLOCK		_SC_MONOTONIC_CLOCK
    _SC_MULTI_PROCESS,
#define _SC_MULTI_PROCESS		_SC_MULTI_PROCESS
    _SC_SINGLE_PROCESS,
#define _SC_SINGLE_PROCESS		_SC_SINGLE_PROCESS
    _SC_NETWORKING,
#define _SC_NETWORKING			_SC_NETWORKING
    _SC_READER_WRITER_LOCKS,
#define _SC_READER_WRITER_LOCKS		_SC_READER_WRITER_LOCKS
    _SC_SPIN_LOCKS,
#define _SC_SPIN_LOCKS			_SC_SPIN_LOCKS
    _SC_REGEXP,
#define _SC_REGEXP			_SC_REGEXP
    _SC_REGEX_VERSION,
#define _SC_REGEX_VERSION		_SC_REGEX_VERSION
    _SC_SHELL,
#define _SC_SHELL			_SC_SHELL
    _SC_SIGNALS,
#define _SC_SIGNALS			_SC_SIGNALS
    _SC_SPAWN,
#define _SC_SPAWN			_SC_SPAWN
    _SC_SPORADIC_SERVER,
#define _SC_SPORADIC_SERVER		_SC_SPORADIC_SERVER
    _SC_THREAD_SPORADIC_SERVER,
#define _SC_THREAD_SPORADIC_SERVER	_SC_THREAD_SPORADIC_SERVER
    _SC_SYSTEM_DATABASE,
#define _SC_SYSTEM_DATABASE		_SC_SYSTEM_DATABASE
    _SC_SYSTEM_DATABASE_R,
#define _SC_SYSTEM_DATABASE_R		_SC_SYSTEM_DATABASE_R
    _SC_TIMEOUTS,
#define _SC_TIMEOUTS			_SC_TIMEOUTS
    _SC_TYPED_MEMORY_OBJECTS,
#define _SC_TYPED_MEMORY_OBJECTS	_SC_TYPED_MEMORY_OBJECTS
    _SC_USER_GROUPS,
#define _SC_USER_GROUPS			_SC_USER_GROUPS
    _SC_USER_GROUPS_R,
#define _SC_USER_GROUPS_R		_SC_USER_GROUPS_R
    _SC_2_PBS,
#define _SC_2_PBS			_SC_2_PBS
    _SC_2_PBS_ACCOUNTING,
#define _SC_2_PBS_ACCOUNTING		_SC_2_PBS_ACCOUNTING
    _SC_2_PBS_LOCATE,
#define _SC_2_PBS_LOCATE		_SC_2_PBS_LOCATE
    _SC_2_PBS_MESSAGE,
#define _SC_2_PBS_MESSAGE		_SC_2_PBS_MESSAGE
    _SC_2_PBS_TRACK,
#define _SC_2_PBS_TRACK			_SC_2_PBS_TRACK
    _SC_SYMLOOP_MAX,
#define _SC_SYMLOOP_MAX			_SC_SYMLOOP_MAX
    _SC_STREAMS,
#define _SC_STREAMS			_SC_STREAMS
    _SC_2_PBS_CHECKPOINT,
#define _SC_2_PBS_CHECKPOINT		_SC_2_PBS_CHECKPOINT

    _SC_V6_ILP32_OFF32,
#define _SC_V6_ILP32_OFF32		_SC_V6_ILP32_OFF32
    _SC_V6_ILP32_OFFBIG,
#define _SC_V6_ILP32_OFFBIG		_SC_V6_ILP32_OFFBIG
    _SC_V6_LP64_OFF64,
#define _SC_V6_LP64_OFF64		_SC_V6_LP64_OFF64
    _SC_V6_LPBIG_OFFBIG,
#define _SC_V6_LPBIG_OFFBIG		_SC_V6_LPBIG_OFFBIG

    _SC_HOST_NAME_MAX,
#define _SC_HOST_NAME_MAX		_SC_HOST_NAME_MAX
    _SC_TRACE,
#define _SC_TRACE			_SC_TRACE
    _SC_TRACE_EVENT_FILTER,
#define _SC_TRACE_EVENT_FILTER		_SC_TRACE_EVENT_FILTER
    _SC_TRACE_INHERIT,
#define _SC_TRACE_INHERIT		_SC_TRACE_INHERIT
    _SC_TRACE_LOG,
#define _SC_TRACE_LOG			_SC_TRACE_LOG

    _SC_LEVEL1_ICACHE_SIZE,
#define _SC_LEVEL1_ICACHE_SIZE		_SC_LEVEL1_ICACHE_SIZE
    _SC_LEVEL1_ICACHE_ASSOC,
#define _SC_LEVEL1_ICACHE_ASSOC		_SC_LEVEL1_ICACHE_ASSOC
    _SC_LEVEL1_ICACHE_LINESIZE,
#define _SC_LEVEL1_ICACHE_LINESIZE	_SC_LEVEL1_ICACHE_LINESIZE
    _SC_LEVEL1_DCACHE_SIZE,
#define _SC_LEVEL1_DCACHE_SIZE		_SC_LEVEL1_DCACHE_SIZE
    _SC_LEVEL1_DCACHE_ASSOC,
#define _SC_LEVEL1_DCACHE_ASSOC		_SC_LEVEL1_DCACHE_ASSOC
    _SC_LEVEL1_DCACHE_LINESIZE,
#define _SC_LEVEL1_DCACHE_LINESIZE	_SC_LEVEL1_DCACHE_LINESIZE
    _SC_LEVEL2_CACHE_SIZE,
#define _SC_LEVEL2_CACHE_SIZE		_SC_LEVEL2_CACHE_SIZE
    _SC_LEVEL2_CACHE_ASSOC,
#define _SC_LEVEL2_CACHE_ASSOC		_SC_LEVEL2_CACHE_ASSOC
    _SC_LEVEL2_CACHE_LINESIZE,
#define _SC_LEVEL2_CACHE_LINESIZE	_SC_LEVEL2_CACHE_LINESIZE
    _SC_LEVEL3_CACHE_SIZE,
#define _SC_LEVEL3_CACHE_SIZE		_SC_LEVEL3_CACHE_SIZE
    _SC_LEVEL3_CACHE_ASSOC,
#define _SC_LEVEL3_CACHE_ASSOC		_SC_LEVEL3_CACHE_ASSOC
    _SC_LEVEL3_CACHE_LINESIZE,
#define _SC_LEVEL3_CACHE_LINESIZE	_SC_LEVEL3_CACHE_LINESIZE
    _SC_LEVEL4_CACHE_SIZE,
#define _SC_LEVEL4_CACHE_SIZE		_SC_LEVEL4_CACHE_SIZE
    _SC_LEVEL4_CACHE_ASSOC,
#define _SC_LEVEL4_CACHE_ASSOC		_SC_LEVEL4_CACHE_ASSOC
    _SC_LEVEL4_CACHE_LINESIZE,
#define _SC_LEVEL4_CACHE_LINESIZE	_SC_LEVEL4_CACHE_LINESIZE
    /* Leave room here, maybe we need a few more cache levels some day.  */

    _SC_IPV6 = _SC_LEVEL1_ICACHE_SIZE + 50,
#define _SC_IPV6			_SC_IPV6
    _SC_RAW_SOCKETS,
#define _SC_RAW_SOCKETS			_SC_RAW_SOCKETS

    _SC_V7_ILP32_OFF32,
#define _SC_V7_ILP32_OFF32		_SC_V7_ILP32_OFF32
    _SC_V7_ILP32_OFFBIG,
#define _SC_V7_ILP32_OFFBIG		_SC_V7_ILP32_OFFBIG
    _SC_V7_LP64_OFF64,
#define _SC_V7_LP64_OFF64		_SC_V7_LP64_OFF64
    _SC_V7_LPBIG_OFFBIG,
#define _SC_V7_LPBIG_OFFBIG		_SC_V7_LPBIG_OFFBIG

    _SC_SS_REPL_MAX,
#define _SC_SS_REPL_MAX			_SC_SS_REPL_MAX

    _SC_TRACE_EVENT_NAME_MAX,
#define _SC_TRACE_EVENT_NAME_MAX	_SC_TRACE_EVENT_NAME_MAX
    _SC_TRACE_NAME_MAX,
#define _SC_TRACE_NAME_MAX		_SC_TRACE_NAME_MAX
    _SC_TRACE_SYS_MAX,
#define _SC_TRACE_SYS_MAX		_SC_TRACE_SYS_MAX
    _SC_TRACE_USER_EVENT_MAX,
#define _SC_TRACE_USER_EVENT_MAX	_SC_TRACE_USER_EVENT_MAX

    _SC_XOPEN_STREAMS,
#define _SC_XOPEN_STREAMS		_SC_XOPEN_STREAMS

    _SC_THREAD_ROBUST_PRIO_INHERIT,
#define _SC_THREAD_ROBUST_PRIO_INHERIT	_SC_THREAD_ROBUST_PRIO_INHERIT
    _SC_THREAD_ROBUST_PRIO_PROTECT
#define _SC_THREAD_ROBUST_PRIO_PROTECT	_SC_THREAD_ROBUST_PRIO_PROTECT
  };

/* Values for the NAME argument to `confstr'.  */
enum
  {
    _CS_PATH,			/* The default search path.  */
#define _CS_PATH		_CS_PATH

    _CS_V6_WIDTH_RESTRICTED_ENVS,
#define _CS_V6_WIDTH_RESTRICTED_ENVS	_CS_V6_WIDTH_RESTRICTED_ENVS
#define _CS_POSIX_V6_WIDTH_RESTRICTED_ENVS	_CS_V6_WIDTH_RESTRICTED_ENVS

    _CS_GNU_LIBC_VERSION,
#define _CS_GNU_LIBC_VERSION	_CS_GNU_LIBC_VERSION
    _CS_GNU_LIBPTHREAD_VERSION,
#define _CS_GNU_LIBPTHREAD_VERSION	_CS_GNU_LIBPTHREAD_VERSION

    _CS_V5_WIDTH_RESTRICTED_ENVS,
#define _CS_V5_WIDTH_RESTRICTED_ENVS	_CS_V5_WIDTH_RESTRICTED_ENVS
#define _CS_POSIX_V5_WIDTH_RESTRICTED_ENVS	_CS_V5_WIDTH_RESTRICTED_ENVS

    _CS_V7_WIDTH_RESTRICTED_ENVS,
#define _CS_V7_WIDTH_RESTRICTED_ENVS	_CS_V7_WIDTH_RESTRICTED_ENVS
#define _CS_POSIX_V7_WIDTH_RESTRICTED_ENVS	_CS_V7_WIDTH_RESTRICTED_ENVS

    _CS_LFS_CFLAGS = 1000,
#define _CS_LFS_CFLAGS	_CS_LFS_CFLAGS
    _CS_LFS_LDFLAGS,
#define _CS_LFS_LDFLAGS	_CS_LFS_LDFLAGS
    _CS_LFS_LIBS,
#define _CS_LFS_LIBS		_CS_LFS_LIBS
    _CS_LFS_LINTFLAGS,
#define _CS_LFS_LINTFLAGS	_CS_LFS_LINTFLAGS
    _CS_LFS64_CFLAGS,
#define _CS_LFS64_CFLAGS	_CS_LFS64_CFLAGS
    _CS_LFS64_LDFLAGS,
#define _CS_LFS64_LDFLAGS	_CS_LFS64_LDFLAGS
    _CS_LFS64_LIBS,
#define _CS_LFS64_LIBS	_CS_LFS64_LIBS
    _CS_LFS64_LINTFLAGS,
#define _CS_LFS64_LINTFLAGS	_CS_LFS64_LINTFLAGS

    _CS_XBS5_ILP32_OFF32_CFLAGS = 1100,
#define _CS_XBS5_ILP32_OFF32_CFLAGS _CS_XBS5_ILP32_OFF32_CFLAGS
    _CS_XBS5_ILP32_OFF32_LDFLAGS,
#define _CS_XBS5_ILP32_OFF32_LDFLAGS _CS_XBS5_ILP32_OFF32_LDFLAGS
    _CS_XBS5_ILP32_OFF32_LIBS,
#define _CS_XBS5_ILP32_OFF32_LIBS _CS_XBS5_ILP32_OFF32_LIBS
    _CS_XBS5_ILP32_OFF32_LINTFLAGS,
#define _CS_XBS5_ILP32_OFF32_LINTFLAGS _CS_XBS5_ILP32_OFF32_LINTFLAGS
    _CS_XBS5_ILP32_OFFBIG_CFLAGS,
#define _CS_XBS5_ILP32_OFFBIG_CFLAGS _CS_XBS5_ILP32_OFFBIG_CFLAGS
    _CS_XBS5_ILP32_OFFBIG_LDFLAGS,
#define _CS_XBS5_ILP32_OFFBIG_LDFLAGS _CS_XBS5_ILP32_OFFBIG_LDFLAGS
    _CS_XBS5_ILP32_OFFBIG_LIBS,
#define _CS_XBS5_ILP32_OFFBIG_LIBS _CS_XBS5_ILP32_OFFBIG_LIBS
    _CS_XBS5_ILP32_OFFBIG_LINTFLAGS,
#define _CS_XBS5_ILP32_OFFBIG_LINTFLAGS _CS_XBS5_ILP32_OFFBIG_LINTFLAGS
    _CS_XBS5_LP64_OFF64_CFLAGS,
#define _CS_XBS5_LP64_OFF64_CFLAGS _CS_XBS5_LP64_OFF64_CFLAGS
    _CS_XBS5_LP64_OFF64_LDFLAGS,
#define _CS_XBS5_LP64_OFF64_LDFLAGS _CS_XBS5_LP64_OFF64_LDFLAGS
    _CS_XBS5_LP64_OFF64_LIBS,
#define _CS_XBS5_LP64_OFF64_LIBS _CS_XBS5_LP64_OFF64_LIBS
    _CS_XBS5_LP64_OFF64_LINTFLAGS,
#define _CS_XBS5_LP64_OFF64_LINTFLAGS _CS_XBS5_LP64_OFF64_LINTFLAGS
    _CS_XBS5_LPBIG_OFFBIG_CFLAGS,
#define _CS_XBS5_LPBIG_OFFBIG_CFLAGS _CS_XBS5_LPBIG_OFFBIG_CFLAGS
    _CS_XBS5_LPBIG_OFFBIG_LDFLAGS,
#define _CS_XBS5_LPBIG_OFFBIG_LDFLAGS _CS_XBS5_LPBIG_OFFBIG_LDFLAGS
    _CS_XBS5_LPBIG_OFFBIG_LIBS,
#define _CS_XBS5_LPBIG_OFFBIG_LIBS _CS_XBS5_LPBIG_OFFBIG_LIBS
    _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS,
#define _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS

    _CS_POSIX_V6_ILP32_OFF32_CFLAGS,
#define _CS_POSIX_V6_ILP32_OFF32_CFLAGS _CS_POSIX_V6_ILP32_OFF32_CFLAGS
    _CS_POSIX_V6_ILP32_OFF32_LDFLAGS,
#define _CS_POSIX_V6_ILP32_OFF32_LDFLAGS _CS_POSIX_V6_ILP32_OFF32_LDFLAGS
    _CS_POSIX_V6_ILP32_OFF32_LIBS,
#define _CS_POSIX_V6_ILP32_OFF32_LIBS _CS_POSIX_V6_ILP32_OFF32_LIBS
    _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS,
#define _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS
    _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS,
#define _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS
    _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS,
#define _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS
    _CS_POSIX_V6_ILP32_OFFBIG_LIBS,
#define _CS_POSIX_V6_ILP32_OFFBIG_LIBS _CS_POSIX_V6_ILP32_OFFBIG_LIBS
    _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS,
#define _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS
    _CS_POSIX_V6_LP64_OFF64_CFLAGS,
#define _CS_POSIX_V6_LP64_OFF64_CFLAGS _CS_POSIX_V6_LP64_OFF64_CFLAGS
    _CS_POSIX_V6_LP64_OFF64_LDFLAGS,
#define _CS_POSIX_V6_LP64_OFF64_LDFLAGS _CS_POSIX_V6_LP64_OFF64_LDFLAGS
    _CS_POSIX_V6_LP64_OFF64_LIBS,
#define _CS_POSIX_V6_LP64_OFF64_LIBS _CS_POSIX_V6_LP64_OFF64_LIBS
    _CS_POSIX_V6_LP64_OFF64_LINTFLAGS,
#define _CS_POSIX_V6_LP64_OFF64_LINTFLAGS _CS_POSIX_V6_LP64_OFF64_LINTFLAGS
    _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS,
#define _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS
    _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS,
#define _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS
    _CS_POSIX_V6_LPBIG_OFFBIG_LIBS,
#define _CS_POSIX_V6_LPBIG_OFFBIG_LIBS _CS_POSIX_V6_LPBIG_OFFBIG_LIBS
    _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS,
#define _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS

    _CS_POSIX_V7_ILP32_OFF32_CFLAGS,
#define _CS_POSIX_V7_ILP32_OFF32_CFLAGS _CS_POSIX_V7_ILP32_OFF32_CFLAGS
    _CS_POSIX_V7_ILP32_OFF32_LDFLAGS,
#define _CS_POSIX_V7_ILP32_OFF32_LDFLAGS _CS_POSIX_V7_ILP32_OFF32_LDFLAGS
    _CS_POSIX_V7_ILP32_OFF32_LIBS,
#define _CS_POSIX_V7_ILP32_OFF32_LIBS _CS_POSIX_V7_ILP32_OFF32_LIBS
    _CS_POSIX_V7_ILP32_OFF32_LINTFLAGS,
#define _CS_POSIX_V7_ILP32_OFF32_LINTFLAGS _CS_POSIX_V7_ILP32_OFF32_LINTFLAGS
    _CS_POSIX_V7_ILP32_OFFBIG_CFLAGS,
#define _CS_POSIX_V7_ILP32_OFFBIG_CFLAGS _CS_POSIX_V7_ILP32_OFFBIG_CFLAGS
    _CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS,
#define _CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS _CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS
    _CS_POSIX_V7_ILP32_OFFBIG_LIBS,
#define _CS_POSIX_V7_ILP32_OFFBIG_LIBS _CS_POSIX_V7_ILP32_OFFBIG_LIBS
    _CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS,
#define _CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS _CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS
    _CS_POSIX_V7_LP64_OFF64_CFLAGS,
#define _CS_POSIX_V7_LP64_OFF64_CFLAGS _CS_POSIX_V7_LP64_OFF64_CFLAGS
    _CS_POSIX_V7_LP64_OFF64_LDFLAGS,
#define _CS_POSIX_V7_LP64_OFF64_LDFLAGS _CS_POSIX_V7_LP64_OFF64_LDFLAGS
    _CS_POSIX_V7_LP64_OFF64_LIBS,
#define _CS_POSIX_V7_LP64_OFF64_LIBS _CS_POSIX_V7_LP64_OFF64_LIBS
    _CS_POSIX_V7_LP64_OFF64_LINTFLAGS,
#define _CS_POSIX_V7_LP64_OFF64_LINTFLAGS _CS_POSIX_V7_LP64_OFF64_LINTFLAGS
    _CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS,
#define _CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS _CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS
    _CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS,
#define _CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS _CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS
    _CS_POSIX_V7_LPBIG_OFFBIG_LIBS,
#define _CS_POSIX_V7_LPBIG_OFFBIG_LIBS _CS_POSIX_V7_LPBIG_OFFBIG_LIBS
    _CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS,
#define _CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS _CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS

    _CS_V6_ENV,
#define _CS_V6_ENV			_CS_V6_ENV
    _CS_V7_ENV
#define _CS_V7_ENV			_CS_V7_ENV
  };
# 613 "/usr/include/unistd.h" 2 3 4

/* Get file-specific configuration information about PATH.  */
extern long int pathconf (const char *__path, int __name)
     __THROW __nonnull ((1));

/* Get file-specific configuration about descriptor FD.  */
extern long int fpathconf (int __fd, int __name) __THROW;

/* Get the value of the system variable NAME.  */
extern long int sysconf (int __name) __THROW;

#ifdef	__USE_POSIX2
/* Get the value of the string-valued system variable NAME.  */
extern size_t confstr (int __name, char *__buf, size_t __len) __THROW;
#endif
# 628 "/usr/include/unistd.h" 3 4


/* Get the process ID of the calling process.  */
extern __pid_t getpid (void) __THROW;

/* Get the process ID of the calling process's parent.  */
extern __pid_t getppid (void) __THROW;

/* Get the process group ID of the calling process.  */
extern __pid_t getpgrp (void) __THROW;

/* Get the process group ID of process PID.  */
extern __pid_t __getpgid (__pid_t __pid) __THROW;
#if defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8
extern __pid_t getpgid (__pid_t __pid) __THROW;
#endif
# 644 "/usr/include/unistd.h" 3 4


/* Set the process group ID of the process matching PID to PGID.
   If PID is zero, the current process's process group ID is set.
   If PGID is zero, the process ID of the process is used.  */
extern int setpgid (__pid_t __pid, __pid_t __pgid) __THROW;

#if defined __USE_MISC || defined __USE_XOPEN_EXTENDED
/* Both System V and BSD have `setpgrp' functions, but with different
   calling conventions.  The BSD function is the same as POSIX.1 `setpgid'
   (above).  The System V function takes no arguments and puts the calling
   process in its on group like `setpgid (0, 0)'.

   New programs should always use `setpgid' instead.

   GNU provides the POSIX.1 function.  */

/* Set the process group ID of the calling process to its own PID.
   This is exactly the same as `setpgid (0, 0)'.  */
extern int setpgrp (void) __THROW;

#endif	/* Use misc or X/Open.  */
# 666 "/usr/include/unistd.h" 3 4

/* Create a new session with the calling process as its leader.
   The process group IDs of the session and the calling process
   are set to the process ID of the calling process, which is returned.  */
extern __pid_t setsid (void) __THROW;

#if defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8
/* Return the session ID of the given process.  */
extern __pid_t getsid (__pid_t __pid) __THROW;
#endif
# 676 "/usr/include/unistd.h" 3 4

/* Get the real user ID of the calling process.  */
extern __uid_t getuid (void) __THROW;

/* Get the effective user ID of the calling process.  */
extern __uid_t geteuid (void) __THROW;

/* Get the real group ID of the calling process.  */
extern __gid_t getgid (void) __THROW;

/* Get the effective group ID of the calling process.  */
extern __gid_t getegid (void) __THROW;

/* If SIZE is zero, return the number of supplementary groups
   the calling process is in.  Otherwise, fill in the group IDs
   of its supplementary groups in LIST and return the number written.  */
extern int getgroups (int __size, __gid_t __list[]) __THROW __wur;

#ifdef	__USE_GNU
/* Return nonzero iff the calling process is in group GID.  */
extern int group_member (__gid_t __gid) __THROW;
#endif
# 698 "/usr/include/unistd.h" 3 4

/* Set the user ID of the calling process to UID.
   If the calling process is the super-user, set the real
   and effective user IDs, and the saved set-user-ID to UID;
   if not, the effective user ID is set to UID.  */
extern int setuid (__uid_t __uid) __THROW __wur;

#if defined __USE_MISC || defined __USE_XOPEN_EXTENDED
/* Set the real user ID of the calling process to RUID,
   and the effective user ID of the calling process to EUID.  */
extern int setreuid (__uid_t __ruid, __uid_t __euid) __THROW __wur;
#endif
# 710 "/usr/include/unistd.h" 3 4

#ifdef __USE_XOPEN2K
/* Set the effective user ID of the calling process to UID.  */
extern int seteuid (__uid_t __uid) __THROW __wur;
#endif /* Use POSIX.1-2001.  */
# 715 "/usr/include/unistd.h" 3 4

/* Set the group ID of the calling process to GID.
   If the calling process is the super-user, set the real
   and effective group IDs, and the saved set-group-ID to GID;
   if not, the effective group ID is set to GID.  */
extern int setgid (__gid_t __gid) __THROW __wur;

#if defined __USE_MISC || defined __USE_XOPEN_EXTENDED
/* Set the real group ID of the calling process to RGID,
   and the effective group ID of the calling process to EGID.  */
extern int setregid (__gid_t __rgid, __gid_t __egid) __THROW __wur;
#endif
# 727 "/usr/include/unistd.h" 3 4

#ifdef __USE_XOPEN2K
/* Set the effective group ID of the calling process to GID.  */
extern int setegid (__gid_t __gid) __THROW __wur;
#endif /* Use POSIX.1-2001.  */
# 732 "/usr/include/unistd.h" 3 4

#ifdef __USE_GNU
/* Fetch the real user ID, effective user ID, and saved-set user ID,
   of the calling process.  */
extern int getresuid (__uid_t *__ruid, __uid_t *__euid, __uid_t *__suid)
     __THROW;

/* Fetch the real group ID, effective group ID, and saved-set group ID,
   of the calling process.  */
extern int getresgid (__gid_t *__rgid, __gid_t *__egid, __gid_t *__sgid)
     __THROW;

/* Set the real user ID, effective user ID, and saved-set user ID,
   of the calling process to RUID, EUID, and SUID, respectively.  */
extern int setresuid (__uid_t __ruid, __uid_t __euid, __uid_t __suid)
     __THROW __wur;

/* Set the real group ID, effective group ID, and saved-set group ID,
   of the calling process to RGID, EGID, and SGID, respectively.  */
extern int setresgid (__gid_t __rgid, __gid_t __egid, __gid_t __sgid)
     __THROW __wur;
#endif
# 754 "/usr/include/unistd.h" 3 4


/* Clone the calling process, creating an exact copy.
   Return -1 for errors, 0 to the new process,
   and the process ID of the new process to the old process.  */
extern __pid_t fork (void) __THROWNL;

#if (defined __USE_XOPEN_EXTENDED && !defined __USE_XOPEN2K8) \
    || defined __USE_MISC
/* Clone the calling process, but without copying the whole address space.
   The calling process is suspended until the new process exits or is
   replaced by a call to `execve'.  Return -1 for errors, 0 to the new process,
   and the process ID of the new process to the old process.  */
extern __pid_t vfork (void) __THROW;
#endif /* Use misc or XPG < 7. */
# 769 "/usr/include/unistd.h" 3 4


/* Return the pathname of the terminal FD is open on, or NULL on errors.
   The returned storage is good only until the next call to this function.  */
extern char *ttyname (int __fd) __THROW;

/* Store at most BUFLEN characters of the pathname of the terminal FD is
   open on in BUF.  Return 0 on success, otherwise an error number.  */
extern int ttyname_r (int __fd, char *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __wur;

/* Return 1 if FD is a valid descriptor associated
   with a terminal, zero if not.  */
extern int isatty (int __fd) __THROW;

#if defined __USE_MISC \
    || (defined __USE_XOPEN_EXTENDED && !defined __USE_UNIX98)
/* Return the index into the active-logins file (utmp) for
   the controlling terminal.  */
extern int ttyslot (void) __THROW;
#endif
# 790 "/usr/include/unistd.h" 3 4


/* Make a link to FROM named TO.  */
extern int link (const char *__from, const char *__to)
     __THROW __nonnull ((1, 2)) __wur;

#ifdef __USE_ATFILE
/* Like link but relative paths in TO and FROM are interpreted relative
   to FROMFD and TOFD respectively.  */
extern int linkat (int __fromfd, const char *__from, int __tofd,
		   const char *__to, int __flags)
     __THROW __nonnull ((2, 4)) __wur;
#endif
# 803 "/usr/include/unistd.h" 3 4

#if defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K
/* Make a symbolic link to FROM named TO.  */
extern int symlink (const char *__from, const char *__to)
     __THROW __nonnull ((1, 2)) __wur;

/* Read the contents of the symbolic link PATH into no more than
   LEN bytes of BUF.  The contents are not null-terminated.
   Returns the number of characters read, or -1 for errors.  */
extern ssize_t readlink (const char *__restrict __path,
			 char *__restrict __buf, size_t __len)
     __THROW __nonnull ((1, 2)) __wur;
#endif /* Use POSIX.1-2001.  */
# 816 "/usr/include/unistd.h" 3 4

#ifdef __USE_ATFILE
/* Like symlink but a relative path in TO is interpreted relative to TOFD.  */
extern int symlinkat (const char *__from, int __tofd,
		      const char *__to) __THROW __nonnull ((1, 3)) __wur;

/* Like readlink but a relative PATH is interpreted relative to FD.  */
extern ssize_t readlinkat (int __fd, const char *__restrict __path,
			   char *__restrict __buf, size_t __len)
     __THROW __nonnull ((2, 3)) __wur;
#endif
# 827 "/usr/include/unistd.h" 3 4

/* Remove the link NAME.  */
extern int unlink (const char *__name) __THROW __nonnull ((1));

#ifdef __USE_ATFILE
/* Remove the link NAME relative to FD.  */
extern int unlinkat (int __fd, const char *__name, int __flag)
     __THROW __nonnull ((2));
#endif
# 836 "/usr/include/unistd.h" 3 4

/* Remove the directory PATH.  */
extern int rmdir (const char *__path) __THROW __nonnull ((1));


/* Return the foreground process group ID of FD.  */
extern __pid_t tcgetpgrp (int __fd) __THROW;

/* Set the foreground process group ID of FD set PGRP_ID.  */
extern int tcsetpgrp (int __fd, __pid_t __pgrp_id) __THROW;


/* Return the login name of the user.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern char *getlogin (void);
#if defined __USE_REENTRANT || defined __USE_POSIX199506
/* Return at most NAME_LEN characters of the login name of the user in NAME.
   If it cannot be determined or some other error occurred, return the error
   code.  Otherwise return 0.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern int getlogin_r (char *__name, size_t __name_len) __nonnull ((1));
#endif
# 862 "/usr/include/unistd.h" 3 4

#ifdef	__USE_MISC
/* Set the login name returned by `getlogin'.  */
extern int setlogin (const char *__name) __THROW __nonnull ((1));
#endif
# 867 "/usr/include/unistd.h" 3 4


#ifdef	__USE_POSIX2
/* Get definitions and prototypes for functions to process the
   arguments in ARGV (ARGC of them, minus the program name) for
   options given in OPTS.  */
# define __need_getopt
#if 0 /* expanded by -frewrite-includes */
# include <getopt.h>
#endif /* expanded by -frewrite-includes */
# 874 "/usr/include/unistd.h" 3 4
# 1 "/usr/include/getopt.h" 1 3 4
/* Declarations for getopt.
   Copyright (C) 1989-2016 Free Software Foundation, Inc.
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

#ifndef _GETOPT_H

#ifndef __need_getopt
# define _GETOPT_H 1
#endif
# 24 "/usr/include/getopt.h" 3 4

/* If __GNU_LIBRARY__ is not already defined, either we are being used
   standalone, or this is the first header included in the source file.
   If we are being used with glibc, we need to include <features.h>, but
   that does not exist if we are standalone.  So: if __GNU_LIBRARY__ is
   not defined, include <ctype.h>, which will pull in <features.h> for us
   if it's from glibc.  (Why ctype.h?  It's guaranteed to exist and it
   doesn't flood the namespace with stuff the way some other headers do.)  */
#if !defined __GNU_LIBRARY__
#if 0 /* expanded by -frewrite-includes */
# include <ctype.h>
#endif /* expanded by -frewrite-includes */
# 33 "/usr/include/getopt.h" 3 4
# 34 "/usr/include/getopt.h" 3 4
#endif
# 35 "/usr/include/getopt.h" 3 4

#ifndef __THROW
# ifndef __GNUC_PREREQ
#  define __GNUC_PREREQ(maj, min) (0)
# endif
# 40 "/usr/include/getopt.h" 3 4
# if defined __cplusplus && __GNUC_PREREQ (2,8)
#  define __THROW	throw ()
# else
# 43 "/usr/include/getopt.h" 3 4
#  define __THROW
# endif
# 45 "/usr/include/getopt.h" 3 4
#endif
# 46 "/usr/include/getopt.h" 3 4

#ifdef	__cplusplus
extern "C" {
#endif
# 50 "/usr/include/getopt.h" 3 4

/* For communication from `getopt' to the caller.
   When `getopt' finds an option that takes an argument,
   the argument value is returned here.
   Also, when `ordering' is RETURN_IN_ORDER,
   each non-option ARGV-element is returned here.  */

extern char *optarg;

/* Index in ARGV of the next element to be scanned.
   This is used for communication to and from the caller
   and for communication between successive calls to `getopt'.

   On entry to `getopt', zero means this is the first call; initialize.

   When `getopt' returns -1, this is the index of the first of the
   non-option elements that the caller should itself scan.

   Otherwise, `optind' communicates from one call to the next
   how much of ARGV has been scanned so far.  */

extern int optind;

/* Callers store zero here to inhibit the error message `getopt' prints
   for unrecognized options.  */

extern int opterr;

/* Set to an option character which was unrecognized.  */

extern int optopt;

#ifndef __need_getopt
/* Describe the long-named options requested by the application.
   The LONG_OPTIONS argument to getopt_long or getopt_long_only is a vector
   of `struct option' terminated by an element containing a name which is
   zero.

   The field `has_arg' is:
   no_argument		(or 0) if the option does not take an argument,
   required_argument	(or 1) if the option requires an argument,
   optional_argument 	(or 2) if the option takes an optional argument.

   If the field `flag' is not NULL, it points to a variable that is set
   to the value given in the field `val' when the option is found, but
   left unchanged if the option is not found.

   To have a long-named option do something other than set an `int' to
   a compiled-in constant, such as set a value from `optarg', set the
   option's `flag' field to zero and its `val' field to a nonzero
   value (the equivalent single-letter option character, if there is
   one).  For long options that have a zero `flag' field, `getopt'
   returns the contents of the `val' field.  */

struct option
{
  const char *name;
  /* has_arg can't be an enum because some compilers complain about
     type mismatches in all the code that assumes it is an int.  */
  int has_arg;
  int *flag;
  int val;
};

/* Names for the values of the `has_arg' field of `struct option'.  */

# define no_argument		0
# define required_argument	1
# define optional_argument	2
#endif	/* need getopt */
# 120 "/usr/include/getopt.h" 3 4


/* Get definitions and prototypes for functions to process the
   arguments in ARGV (ARGC of them, minus the program name) for
   options given in OPTS.

   Return the option character from OPTS just read.  Return -1 when
   there are no more options.  For unrecognized options, or options
   missing arguments, `optopt' is set to the option letter, and '?' is
   returned.

   The OPTS string is a list of characters which are recognized option
   letters, optionally followed by colons, specifying that that letter
   takes an argument, to be placed in `optarg'.

   If a letter in OPTS is followed by two colons, its argument is
   optional.  This behavior is specific to the GNU `getopt'.

   The argument `--' causes premature termination of argument
   scanning, explicitly telling `getopt' that there are no more
   options.

   If OPTS begins with `--', then non-option arguments are treated as
   arguments to the option '\0'.  This behavior is specific to the GNU
   `getopt'.  */

#ifdef __GNU_LIBRARY__
/* Many other libraries have conflicting prototypes for getopt, with
   differences in the consts, in stdlib.h.  To avoid compilation
   errors, only prototype getopt for the GNU C library.  */
extern int getopt (int ___argc, char *const *___argv, const char *__shortopts)
       __THROW;

# if defined __need_getopt && defined __USE_POSIX2 \
  && !defined __USE_POSIX_IMPLICITLY && !defined __USE_GNU
/* The GNU getopt has more functionality than the standard version.  The
   additional functionality can be disable at runtime.  This redirection
   helps to also do this at runtime.  */
#  ifdef __REDIRECT
  extern int __REDIRECT_NTH (getopt, (int ___argc, char *const *___argv,
				      const char *__shortopts),
			     __posix_getopt);
#  else
# 163 "/usr/include/getopt.h" 3 4
extern int __posix_getopt (int ___argc, char *const *___argv,
			   const char *__shortopts) __THROW;
#   define getopt __posix_getopt
#  endif
# 167 "/usr/include/getopt.h" 3 4
# endif
# 168 "/usr/include/getopt.h" 3 4
#else /* not __GNU_LIBRARY__ */
# 169 "/usr/include/getopt.h" 3 4
extern int getopt ();
#endif /* __GNU_LIBRARY__ */
# 171 "/usr/include/getopt.h" 3 4

#ifndef __need_getopt
extern int getopt_long (int ___argc, char *const *___argv,
			const char *__shortopts,
		        const struct option *__longopts, int *__longind)
       __THROW;
extern int getopt_long_only (int ___argc, char *const *___argv,
			     const char *__shortopts,
		             const struct option *__longopts, int *__longind)
       __THROW;

#endif
# 183 "/usr/include/getopt.h" 3 4

#ifdef	__cplusplus
}
#endif
# 187 "/usr/include/getopt.h" 3 4

/* Make sure we later can get all the definitions and declarations.  */
#undef __need_getopt

#endif /* getopt.h */
# 192 "/usr/include/getopt.h" 3 4
# 875 "/usr/include/unistd.h" 2 3 4
#endif
# 876 "/usr/include/unistd.h" 3 4


#if defined __USE_UNIX98 || defined __USE_XOPEN2K
/* Put the name of the current host in no more than LEN bytes of NAME.
   The result is null-terminated if LEN is large enough for the full
   name and the terminator.  */
extern int gethostname (char *__name, size_t __len) __THROW __nonnull ((1));
#endif
# 884 "/usr/include/unistd.h" 3 4


#if defined __USE_MISC
/* Set the name of the current host to NAME, which is LEN bytes long.
   This call is restricted to the super-user.  */
extern int sethostname (const char *__name, size_t __len)
     __THROW __nonnull ((1)) __wur;

/* Set the current machine's Internet number to ID.
   This call is restricted to the super-user.  */
extern int sethostid (long int __id) __THROW __wur;


/* Get and set the NIS (aka YP) domain name, if any.
   Called just like `gethostname' and `sethostname'.
   The NIS domain name is usually the empty string when not using NIS.  */
extern int getdomainname (char *__name, size_t __len)
     __THROW __nonnull ((1)) __wur;
extern int setdomainname (const char *__name, size_t __len)
     __THROW __nonnull ((1)) __wur;


/* Revoke access permissions to all processes currently communicating
   with the control terminal, and then send a SIGHUP signal to the process
   group of the control terminal.  */
extern int vhangup (void) __THROW;

/* Revoke the access of all descriptors currently open on FILE.  */
extern int revoke (const char *__file) __THROW __nonnull ((1)) __wur;


/* Enable statistical profiling, writing samples of the PC into at most
   SIZE bytes of SAMPLE_BUFFER; every processor clock tick while profiling
   is enabled, the system examines the user PC and increments
   SAMPLE_BUFFER[((PC - OFFSET) / 2) * SCALE / 65536].  If SCALE is zero,
   disable profiling.  Returns zero on success, -1 on error.  */
extern int profil (unsigned short int *__sample_buffer, size_t __size,
		   size_t __offset, unsigned int __scale)
     __THROW __nonnull ((1));


/* Turn accounting on if NAME is an existing file.  The system will then write
   a record for each process as it terminates, to this file.  If NAME is NULL,
   turn accounting off.  This call is restricted to the super-user.  */
extern int acct (const char *__name) __THROW;


/* Successive calls return the shells listed in `/etc/shells'.  */
extern char *getusershell (void) __THROW;
extern void endusershell (void) __THROW; /* Discard cached info.  */
extern void setusershell (void) __THROW; /* Rewind and re-read the file.  */


/* Put the program in the background, and dissociate from the controlling
   terminal.  If NOCHDIR is zero, do `chdir ("/")'.  If NOCLOSE is zero,
   redirects stdin, stdout, and stderr to /dev/null.  */
extern int daemon (int __nochdir, int __noclose) __THROW __wur;
#endif /* Use misc.  */
# 942 "/usr/include/unistd.h" 3 4


#if defined __USE_MISC || (defined __USE_XOPEN && !defined __USE_XOPEN2K)
/* Make PATH be the root directory (the starting point for absolute paths).
   This call is restricted to the super-user.  */
extern int chroot (const char *__path) __THROW __nonnull ((1)) __wur;

/* Prompt with PROMPT and read a string from the terminal without echoing.
   Uses /dev/tty if possible; otherwise stderr and stdin.  */
extern char *getpass (const char *__prompt) __nonnull ((1));
#endif /* Use misc || X/Open.  */
# 953 "/usr/include/unistd.h" 3 4


/* Make all changes done to FD actually appear on disk.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern int fsync (int __fd);


#ifdef __USE_GNU
/* Make all changes done to all files on the file system associated
   with FD actually appear on disk.  */
extern int syncfs (int __fd) __THROW;
#endif
# 967 "/usr/include/unistd.h" 3 4


#if defined __USE_MISC || defined __USE_XOPEN_EXTENDED

/* Return identifier for the current host.  */
extern long int gethostid (void);

/* Make all changes done to all files actually appear on disk.  */
extern void sync (void) __THROW;


# if defined __USE_MISC || !defined __USE_XOPEN2K
/* Return the number of bytes in a page.  This is the system's page size,
   which is not necessarily the same as the hardware page size.  */
extern int getpagesize (void)  __THROW __attribute__ ((__const__));


/* Return the maximum number of file descriptors
   the current process could possibly have.  */
extern int getdtablesize (void) __THROW;
# endif
# 988 "/usr/include/unistd.h" 3 4

#endif /* Use misc || X/Open Unix.  */
# 990 "/usr/include/unistd.h" 3 4


#if defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8

/* Truncate FILE to LENGTH bytes.  */
# ifndef __USE_FILE_OFFSET64
extern int truncate (const char *__file, __off_t __length)
     __THROW __nonnull ((1)) __wur;
# else
# 999 "/usr/include/unistd.h" 3 4
#  ifdef __REDIRECT_NTH
extern int __REDIRECT_NTH (truncate,
			   (const char *__file, __off64_t __length),
			   truncate64) __nonnull ((1)) __wur;
#  else
# 1004 "/usr/include/unistd.h" 3 4
#   define truncate truncate64
#  endif
# 1006 "/usr/include/unistd.h" 3 4
# endif
# 1007 "/usr/include/unistd.h" 3 4
# ifdef __USE_LARGEFILE64
extern int truncate64 (const char *__file, __off64_t __length)
     __THROW __nonnull ((1)) __wur;
# endif
# 1011 "/usr/include/unistd.h" 3 4

#endif /* Use X/Open Unix || POSIX 2008.  */
# 1013 "/usr/include/unistd.h" 3 4

#if defined __USE_POSIX199309 \
    || defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K

/* Truncate the file FD is open on to LENGTH bytes.  */
# ifndef __USE_FILE_OFFSET64
extern int ftruncate (int __fd, __off_t __length) __THROW __wur;
# else
# 1021 "/usr/include/unistd.h" 3 4
#  ifdef __REDIRECT_NTH
extern int __REDIRECT_NTH (ftruncate, (int __fd, __off64_t __length),
			   ftruncate64) __wur;
#  else
# 1025 "/usr/include/unistd.h" 3 4
#   define ftruncate ftruncate64
#  endif
# 1027 "/usr/include/unistd.h" 3 4
# endif
# 1028 "/usr/include/unistd.h" 3 4
# ifdef __USE_LARGEFILE64
extern int ftruncate64 (int __fd, __off64_t __length) __THROW __wur;
# endif
# 1031 "/usr/include/unistd.h" 3 4

#endif /* Use POSIX.1b || X/Open Unix || XPG6.  */
# 1033 "/usr/include/unistd.h" 3 4


#if (defined __USE_XOPEN_EXTENDED && !defined __USE_XOPEN2K) \
    || defined __USE_MISC

/* Set the end of accessible data space (aka "the break") to ADDR.
   Returns zero on success and -1 for errors (with errno set).  */
extern int brk (void *__addr) __THROW __wur;

/* Increase or decrease the end of accessible data space by DELTA bytes.
   If successful, returns the address the previous end of data space
   (i.e. the beginning of the new space, if DELTA > 0);
   returns (void *) -1 for errors (with errno set).  */
extern void *sbrk (intptr_t __delta) __THROW;
#endif
# 1048 "/usr/include/unistd.h" 3 4


#ifdef __USE_MISC
/* Invoke `system call' number SYSNO, passing it the remaining arguments.
   This is completely system-dependent, and not often useful.

   In Unix, `syscall' sets `errno' for all errors and most calls return -1
   for errors; in many systems you cannot pass arguments or get return
   values for all system calls (`pipe', `fork', and `getppid' typically
   among them).

   In Mach, all system calls take normal arguments and always return an
   error code (zero for success).  */
extern long int syscall (long int __sysno, ...) __THROW;

#endif	/* Use misc.  */
# 1064 "/usr/include/unistd.h" 3 4


#if (defined __USE_MISC || defined __USE_XOPEN_EXTENDED) && !defined F_LOCK
/* NOTE: These declarations also appear in <fcntl.h>; be sure to keep both
   files consistent.  Some systems have them there and some here, and some
   software depends on the macros being defined without including both.  */

/* `lockf' is a simpler interface to the locking facilities of `fcntl'.
   LEN is always relative to the current file position.
   The CMD argument is one of the following.

   This function is a cancellation point and therefore not marked with
   __THROW.  */

# define F_ULOCK 0	/* Unlock a previously locked region.  */
# define F_LOCK  1	/* Lock a region for exclusive use.  */
# define F_TLOCK 2	/* Test and lock a region for exclusive use.  */
# define F_TEST  3	/* Test a region for other processes locks.  */

# ifndef __USE_FILE_OFFSET64
extern int lockf (int __fd, int __cmd, __off_t __len) __wur;
# else
# 1086 "/usr/include/unistd.h" 3 4
#  ifdef __REDIRECT
extern int __REDIRECT (lockf, (int __fd, int __cmd, __off64_t __len),
		       lockf64) __wur;
#  else
# 1090 "/usr/include/unistd.h" 3 4
#   define lockf lockf64
#  endif
# 1092 "/usr/include/unistd.h" 3 4
# endif
# 1093 "/usr/include/unistd.h" 3 4
# ifdef __USE_LARGEFILE64
extern int lockf64 (int __fd, int __cmd, __off64_t __len) __wur;
# endif
# 1096 "/usr/include/unistd.h" 3 4
#endif /* Use misc and F_LOCK not already defined.  */
# 1097 "/usr/include/unistd.h" 3 4


#ifdef __USE_GNU

/* Evaluate EXPRESSION, and repeat as long as it returns -1 with `errno'
   set to EINTR.  */

# define TEMP_FAILURE_RETRY(expression) \
  (__extension__							      \
    ({ long int __result;						      \
       do __result = (long int) (expression);				      \
       while (__result == -1L && errno == EINTR);			      \
       __result; }))
#endif
# 1111 "/usr/include/unistd.h" 3 4

#if defined __USE_POSIX199309 || defined __USE_UNIX98
/* Synchronize at least the data part of a file with the underlying
   media.  */
extern int fdatasync (int __fildes);
#endif /* Use POSIX199309 */
# 1117 "/usr/include/unistd.h" 3 4


/* XPG4.2 specifies that prototypes for the encryption functions must
   be defined here.  */
#ifdef	__USE_XOPEN
/* Encrypt at most 8 characters from KEY using salt to perturb DES.  */
extern char *crypt (const char *__key, const char *__salt)
     __THROW __nonnull ((1, 2));

/* Encrypt data in BLOCK in place if EDFLAG is zero; otherwise decrypt
   block in place.  */
extern void encrypt (char *__glibc_block, int __edflag)
     __THROW __nonnull ((1));


/* Swab pairs bytes in the first N bytes of the area pointed to by
   FROM and copy the result to TO.  The value of TO must not be in the
   range [FROM - N + 1, FROM - 1].  If N is odd the first byte in FROM
   is without partner.  */
extern void swab (const void *__restrict __from, void *__restrict __to,
		  ssize_t __n) __THROW __nonnull ((1, 2));
#endif
# 1139 "/usr/include/unistd.h" 3 4


/* The Single Unix specification demands this prototype to be here.
   It is also found in <stdio.h>.  */
#if defined __USE_XOPEN && !defined __USE_XOPEN2K
/* Return the name of the controlling terminal.  */
extern char *ctermid (char *__s) __THROW;
#endif
# 1147 "/usr/include/unistd.h" 3 4


/* Define some macros helping to catch buffer overflows.  */
#if __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
#if 0 /* expanded by -frewrite-includes */
# include <bits/unistd.h>
#endif /* expanded by -frewrite-includes */
# 1151 "/usr/include/unistd.h" 3 4
# 1152 "/usr/include/unistd.h" 3 4
#endif
# 1153 "/usr/include/unistd.h" 3 4

__END_DECLS

#endif /* unistd.h  */
# 1157 "/usr/include/unistd.h" 3 4
# 10 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/covariance.c" 2
#if 0 /* expanded by -frewrite-includes */
#include <string.h>
#endif /* expanded by -frewrite-includes */
# 10 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/covariance.c"
# 1 "/usr/include/string.h" 1 3 4
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
 *	ISO C99 Standard: 7.21 String handling	<string.h>
 */

#ifndef	_STRING_H
#define	_STRING_H	1

#if 0 /* expanded by -frewrite-includes */
#include <features.h>
#endif /* expanded by -frewrite-includes */
# 25 "/usr/include/string.h" 3 4
# 26 "/usr/include/string.h" 3 4

__BEGIN_DECLS

/* Get size_t and NULL from <stddef.h>.  */
#define	__need_size_t
#define	__need_NULL
#if 0 /* expanded by -frewrite-includes */
#include <stddef.h>
#endif /* expanded by -frewrite-includes */
# 32 "/usr/include/string.h" 3 4
# 1 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 1 3 4
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
# 37 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#define __need_ptrdiff_t
#define __need_size_t
#define __need_wchar_t
#define __need_NULL
#define __need_STDDEF_H_misc
/* __need_wint_t is intentionally not defined here. */
#endif
# 44 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_ptrdiff_t)
#if !defined(_PTRDIFF_T) || __has_feature(modules)
/* Always define ptrdiff_t when modules are available. */
#if !__has_feature(modules)
#define _PTRDIFF_T
#endif
# 51 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif
# 53 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_ptrdiff_t
#endif /* defined(__need_ptrdiff_t) */
# 55 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_size_t)
#if !defined(_SIZE_T) || __has_feature(modules)
/* Always define size_t when modules are available. */
#if !__has_feature(modules)
#define _SIZE_T
#endif
# 62 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ size_t;
#endif
# 64 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_size_t
#endif /*defined(__need_size_t) */
# 66 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
/* ISO9899:2011 7.20 (C11 Annex K): Define rsize_t if __STDC_WANT_LIB_EXT1__ is
 * enabled. */
#if (defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ >= 1 && \
     !defined(_RSIZE_T)) || __has_feature(modules)
/* Always define rsize_t when modules are available. */
#if !__has_feature(modules)
#define _RSIZE_T
#endif
# 76 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ rsize_t;
#endif
# 78 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif /* defined(__need_STDDEF_H_misc) */
# 79 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_wchar_t)
#ifndef __cplusplus
/* Always define wchar_t when modules are available. */
#if !defined(_WCHAR_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WCHAR_T
#if defined(_MSC_EXTENSIONS)
#define _WCHAR_T_DEFINED
#endif
# 89 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 90 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WCHAR_TYPE__ wchar_t;
#endif
# 92 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 93 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wchar_t
#endif /* defined(__need_wchar_t) */
# 95 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_NULL)
#undef NULL
#ifdef __cplusplus
#  if !defined(__MINGW32__) && !defined(_MSC_VER)
#    define NULL __null
#  else
# 102 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#    define NULL 0
#  endif
# 104 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#else
# 105 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#  define NULL ((void*)0)
#endif
# 107 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#ifdef __cplusplus
#if defined(_MSC_EXTENSIONS) && defined(_NATIVE_NULLPTR_SUPPORTED)
namespace std { typedef decltype(nullptr) nullptr_t; }
using ::std::nullptr_t;
#endif
# 112 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 113 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_NULL
#endif /* defined(__need_NULL) */
# 115 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
#if __STDC_VERSION__ >= 201112L || __cplusplus >= 201103L
#if 0 /* expanded by -frewrite-includes */
#include "__stddef_max_align_t.h"
#endif /* expanded by -frewrite-includes */
# 118 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
# 119 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 120 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#define offsetof(t, d) __builtin_offsetof(t, d)
#undef __need_STDDEF_H_misc
#endif  /* defined(__need_STDDEF_H_misc) */
# 123 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

/* Some C libraries expect to see a wint_t here. Others (notably MinGW) will use
__WINT_TYPE__ directly; accommodate both by requiring __need_wint_t */
#if defined(__need_wint_t)
/* Always define wint_t when modules are available. */
#if !defined(_WINT_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WINT_T
#endif
# 132 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WINT_TYPE__ wint_t;
#endif
# 134 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wint_t
#endif /* __need_wint_t */
# 136 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#endif
# 138 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
# 33 "/usr/include/string.h" 2 3 4

/* Tell the caller that we provide correct C++ prototypes.  */
#if defined __cplusplus && __GNUC_PREREQ (4, 4)
# define __CORRECT_ISO_CPP_STRING_H_PROTO
#endif
# 38 "/usr/include/string.h" 3 4


__BEGIN_NAMESPACE_STD
/* Copy N bytes of SRC to DEST.  */
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
		     size_t __n) __THROW __nonnull ((1, 2));
/* Copy N bytes of SRC to DEST, guaranteeing
   correct behavior for overlapping strings.  */
extern void *memmove (void *__dest, const void *__src, size_t __n)
     __THROW __nonnull ((1, 2));
__END_NAMESPACE_STD

/* Copy no more than N bytes of SRC to DEST, stopping when C is found.
   Return the position in DEST one byte past where C was copied,
   or NULL if C was not found in the first N bytes of SRC.  */
#if defined __USE_MISC || defined __USE_XOPEN
extern void *memccpy (void *__restrict __dest, const void *__restrict __src,
		      int __c, size_t __n)
     __THROW __nonnull ((1, 2));
#endif /* Misc || X/Open.  */
# 58 "/usr/include/string.h" 3 4


__BEGIN_NAMESPACE_STD
/* Set N bytes of S to C.  */
extern void *memset (void *__s, int __c, size_t __n) __THROW __nonnull ((1));

/* Compare N bytes of S1 and S2.  */
extern int memcmp (const void *__s1, const void *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Search N bytes of S for C.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
extern "C++"
{
extern void *memchr (void *__s, int __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));
extern const void *memchr (const void *__s, int __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline void *
memchr (void *__s, int __c, size_t __n) __THROW
{
  return __builtin_memchr (__s, __c, __n);
}

__extern_always_inline const void *
memchr (const void *__s, int __c, size_t __n) __THROW
{
  return __builtin_memchr (__s, __c, __n);
}
# endif
# 90 "/usr/include/string.h" 3 4
}
#else
# 92 "/usr/include/string.h" 3 4
extern void *memchr (const void *__s, int __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1));
#endif
# 95 "/usr/include/string.h" 3 4
__END_NAMESPACE_STD

#ifdef __USE_GNU
/* Search in S for C.  This is similar to `memchr' but there is no
   length limit.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
extern "C++" void *rawmemchr (void *__s, int __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
extern "C++" const void *rawmemchr (const void *__s, int __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
# else
# 106 "/usr/include/string.h" 3 4
extern void *rawmemchr (const void *__s, int __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
# 109 "/usr/include/string.h" 3 4

/* Search N bytes of S for the final occurrence of C.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
extern "C++" void *memrchr (void *__s, int __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1));
extern "C++" const void *memrchr (const void *__s, int __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1));
# else
# 117 "/usr/include/string.h" 3 4
extern void *memrchr (const void *__s, int __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1));
# endif
# 120 "/usr/include/string.h" 3 4
#endif
# 121 "/usr/include/string.h" 3 4


__BEGIN_NAMESPACE_STD
/* Copy SRC to DEST.  */
extern char *strcpy (char *__restrict __dest, const char *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Copy no more than N characters of SRC to DEST.  */
extern char *strncpy (char *__restrict __dest,
		      const char *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Append SRC onto DEST.  */
extern char *strcat (char *__restrict __dest, const char *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Append no more than N characters from SRC onto DEST.  */
extern char *strncat (char *__restrict __dest, const char *__restrict __src,
		      size_t __n) __THROW __nonnull ((1, 2));

/* Compare S1 and S2.  */
extern int strcmp (const char *__s1, const char *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Compare N characters of S1 and S2.  */
extern int strncmp (const char *__s1, const char *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare the collated forms of S1 and S2.  */
extern int strcoll (const char *__s1, const char *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Put a transformation of SRC into no more than N bytes of DEST.  */
extern size_t strxfrm (char *__restrict __dest,
		       const char *__restrict __src, size_t __n)
     __THROW __nonnull ((2));
__END_NAMESPACE_STD

#ifdef __USE_XOPEN2K8
/* The following functions are equivalent to the both above but they
   take the locale they use for the collation as an extra argument.
   This is not standardsized but something like will come.  */
#if 0 /* expanded by -frewrite-includes */
# include <xlocale.h>
#endif /* expanded by -frewrite-includes */
# 159 "/usr/include/string.h" 3 4
# 1 "/usr/include/xlocale.h" 1 3 4
/* Definition of locale datatype.
   Copyright (C) 1997-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1997.

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

#ifndef _XLOCALE_H
#define _XLOCALE_H	1

/* Structure for reentrant locale using functions.  This is an
   (almost) opaque type for the user level programs.  The file and
   this data structure is not standardized.  Don't rely on it.  It can
   go away without warning.  */
typedef struct __locale_struct
{
  /* Note: LC_ALL is not a valid index into this array.  */
  struct __locale_data *__locales[13]; /* 13 = __LC_LAST. */

  /* To increase the speed of this solution we add some special members.  */
  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;

  /* Note: LC_ALL is not a valid index into this array.  */
  const char *__names[13];
} *__locale_t;

/* POSIX 2008 makes locale_t official.  */
typedef __locale_t locale_t;

#endif /* xlocale.h */
# 45 "/usr/include/xlocale.h" 3 4
# 160 "/usr/include/string.h" 2 3 4

/* Compare the collated forms of S1 and S2 using rules from L.  */
extern int strcoll_l (const char *__s1, const char *__s2, __locale_t __l)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));
/* Put a transformation of SRC into no more than N bytes of DEST.  */
extern size_t strxfrm_l (char *__dest, const char *__src, size_t __n,
			 __locale_t __l) __THROW __nonnull ((2, 4));
#endif
# 168 "/usr/include/string.h" 3 4

#if defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8
/* Duplicate S, returning an identical malloc'd string.  */
extern char *strdup (const char *__s)
     __THROW __attribute_malloc__ __nonnull ((1));
#endif
# 174 "/usr/include/string.h" 3 4

/* Return a malloc'd copy of at most N bytes of STRING.  The
   resultant string is terminated even if no null terminator
   appears before STRING[N].  */
#if defined __USE_XOPEN2K8
extern char *strndup (const char *__string, size_t __n)
     __THROW __attribute_malloc__ __nonnull ((1));
#endif
# 182 "/usr/include/string.h" 3 4

#if defined __USE_GNU && defined __GNUC__
/* Duplicate S, returning an identical alloca'd string.  */
# define strdupa(s)							      \
  (__extension__							      \
    ({									      \
      const char *__old = (s);						      \
      size_t __len = strlen (__old) + 1;				      \
      char *__new = (char *) __builtin_alloca (__len);			      \
      (char *) memcpy (__new, __old, __len);				      \
    }))

/* Return an alloca'd copy of at most N bytes of string.  */
# define strndupa(s, n)							      \
  (__extension__							      \
    ({									      \
      const char *__old = (s);						      \
      size_t __len = strnlen (__old, (n));				      \
      char *__new = (char *) __builtin_alloca (__len + 1);		      \
      __new[__len] = '\0';						      \
      (char *) memcpy (__new, __old, __len);				      \
    }))
#endif
# 205 "/usr/include/string.h" 3 4

__BEGIN_NAMESPACE_STD
/* Find the first occurrence of C in S.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
extern "C++"
{
extern char *strchr (char *__s, int __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));
extern const char *strchr (const char *__s, int __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline char *
strchr (char *__s, int __c) __THROW
{
  return __builtin_strchr (__s, __c);
}

__extern_always_inline const char *
strchr (const char *__s, int __c) __THROW
{
  return __builtin_strchr (__s, __c);
}
# endif
# 229 "/usr/include/string.h" 3 4
}
#else
# 231 "/usr/include/string.h" 3 4
extern char *strchr (const char *__s, int __c)
     __THROW __attribute_pure__ __nonnull ((1));
#endif
# 234 "/usr/include/string.h" 3 4
/* Find the last occurrence of C in S.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
extern "C++"
{
extern char *strrchr (char *__s, int __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));
extern const char *strrchr (const char *__s, int __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline char *
strrchr (char *__s, int __c) __THROW
{
  return __builtin_strrchr (__s, __c);
}

__extern_always_inline const char *
strrchr (const char *__s, int __c) __THROW
{
  return __builtin_strrchr (__s, __c);
}
# endif
# 256 "/usr/include/string.h" 3 4
}
#else
# 258 "/usr/include/string.h" 3 4
extern char *strrchr (const char *__s, int __c)
     __THROW __attribute_pure__ __nonnull ((1));
#endif
# 261 "/usr/include/string.h" 3 4
__END_NAMESPACE_STD

#ifdef __USE_GNU
/* This function is similar to `strchr'.  But it returns a pointer to
   the closing NUL byte in case C is not found in S.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
extern "C++" char *strchrnul (char *__s, int __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
extern "C++" const char *strchrnul (const char *__s, int __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
# else
# 272 "/usr/include/string.h" 3 4
extern char *strchrnul (const char *__s, int __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
# 275 "/usr/include/string.h" 3 4
#endif
# 276 "/usr/include/string.h" 3 4

__BEGIN_NAMESPACE_STD
/* Return the length of the initial segment of S which
   consists entirely of characters not in REJECT.  */
extern size_t strcspn (const char *__s, const char *__reject)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Return the length of the initial segment of S which
   consists entirely of characters in ACCEPT.  */
extern size_t strspn (const char *__s, const char *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Find the first occurrence in S of any character in ACCEPT.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
extern "C++"
{
extern char *strpbrk (char *__s, const char *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));
extern const char *strpbrk (const char *__s, const char *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline char *
strpbrk (char *__s, const char *__accept) __THROW
{
  return __builtin_strpbrk (__s, __accept);
}

__extern_always_inline const char *
strpbrk (const char *__s, const char *__accept) __THROW
{
  return __builtin_strpbrk (__s, __accept);
}
# endif
# 308 "/usr/include/string.h" 3 4
}
#else
# 310 "/usr/include/string.h" 3 4
extern char *strpbrk (const char *__s, const char *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
#endif
# 313 "/usr/include/string.h" 3 4
/* Find the first occurrence of NEEDLE in HAYSTACK.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
extern "C++"
{
extern char *strstr (char *__haystack, const char *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));
extern const char *strstr (const char *__haystack, const char *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline char *
strstr (char *__haystack, const char *__needle) __THROW
{
  return __builtin_strstr (__haystack, __needle);
}

__extern_always_inline const char *
strstr (const char *__haystack, const char *__needle) __THROW
{
  return __builtin_strstr (__haystack, __needle);
}
# endif
# 335 "/usr/include/string.h" 3 4
}
#else
# 337 "/usr/include/string.h" 3 4
extern char *strstr (const char *__haystack, const char *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
#endif
# 340 "/usr/include/string.h" 3 4


/* Divide S into tokens separated by characters in DELIM.  */
extern char *strtok (char *__restrict __s, const char *__restrict __delim)
     __THROW __nonnull ((2));
__END_NAMESPACE_STD

/* Divide S into tokens separated by characters in DELIM.  Information
   passed between calls are stored in SAVE_PTR.  */
extern char *__strtok_r (char *__restrict __s,
			 const char *__restrict __delim,
			 char **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#ifdef __USE_POSIX
extern char *strtok_r (char *__restrict __s, const char *__restrict __delim,
		       char **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#endif
# 358 "/usr/include/string.h" 3 4

#ifdef __USE_GNU
/* Similar to `strstr' but this function ignores the case of both strings.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
extern "C++" char *strcasestr (char *__haystack, const char *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
extern "C++" const char *strcasestr (const char *__haystack,
				     const char *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
# else
# 368 "/usr/include/string.h" 3 4
extern char *strcasestr (const char *__haystack, const char *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# endif
# 371 "/usr/include/string.h" 3 4
#endif
# 372 "/usr/include/string.h" 3 4

#ifdef __USE_GNU
/* Find the first occurrence of NEEDLE in HAYSTACK.
   NEEDLE is NEEDLELEN bytes long;
   HAYSTACK is HAYSTACKLEN bytes long.  */
extern void *memmem (const void *__haystack, size_t __haystacklen,
		     const void *__needle, size_t __needlelen)
     __THROW __attribute_pure__ __nonnull ((1, 3));

/* Copy N bytes of SRC to DEST, return pointer to bytes after the
   last written byte.  */
extern void *__mempcpy (void *__restrict __dest,
			const void *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
extern void *mempcpy (void *__restrict __dest,
		      const void *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#endif
# 390 "/usr/include/string.h" 3 4


__BEGIN_NAMESPACE_STD
/* Return the length of S.  */
extern size_t strlen (const char *__s)
     __THROW __attribute_pure__ __nonnull ((1));
__END_NAMESPACE_STD

#ifdef	__USE_XOPEN2K8
/* Find the length of STRING, but scan at most MAXLEN characters.
   If no '\0' terminator is found in that many characters, return MAXLEN.  */
extern size_t strnlen (const char *__string, size_t __maxlen)
     __THROW __attribute_pure__ __nonnull ((1));
#endif
# 404 "/usr/include/string.h" 3 4


__BEGIN_NAMESPACE_STD
/* Return a string describing the meaning of the `errno' code in ERRNUM.  */
extern char *strerror (int __errnum) __THROW;
__END_NAMESPACE_STD
#ifdef __USE_XOPEN2K
/* Reentrant version of `strerror'.
   There are 2 flavors of `strerror_r', GNU which returns the string
   and may or may not use the supplied temporary buffer and POSIX one
   which fills the string into the buffer.
   To use the POSIX version, -D_XOPEN_SOURCE=600 or -D_POSIX_C_SOURCE=200112L
   without -D_GNU_SOURCE is needed, otherwise the GNU version is
   preferred.  */
# if defined __USE_XOPEN2K && !defined __USE_GNU
/* Fill BUF with a string describing the meaning of the `errno' code in
   ERRNUM.  */
#  ifdef __REDIRECT_NTH
extern int __REDIRECT_NTH (strerror_r,
			   (int __errnum, char *__buf, size_t __buflen),
			   __xpg_strerror_r) __nonnull ((2));
#  else
# 426 "/usr/include/string.h" 3 4
extern int __xpg_strerror_r (int __errnum, char *__buf, size_t __buflen)
     __THROW __nonnull ((2));
#   define strerror_r __xpg_strerror_r
#  endif
# 430 "/usr/include/string.h" 3 4
# else
# 431 "/usr/include/string.h" 3 4
/* If a temporary buffer is required, at most BUFLEN bytes of BUF will be
   used.  */
extern char *strerror_r (int __errnum, char *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __wur;
# endif
# 436 "/usr/include/string.h" 3 4
#endif
# 437 "/usr/include/string.h" 3 4

#ifdef __USE_XOPEN2K8
/* Translate error number to string according to the locale L.  */
extern char *strerror_l (int __errnum, __locale_t __l) __THROW;
#endif
# 442 "/usr/include/string.h" 3 4


/* We define this function always since `bzero' is sometimes needed when
   the namespace rules does not allow this.  */
extern void __bzero (void *__s, size_t __n) __THROW __nonnull ((1));

#ifdef __USE_MISC
/* Copy N bytes of SRC to DEST (like memmove, but args reversed).  */
extern void bcopy (const void *__src, void *__dest, size_t __n)
     __THROW __nonnull ((1, 2));

/* Set N bytes of S to 0.  */
extern void bzero (void *__s, size_t __n) __THROW __nonnull ((1));

/* Compare N bytes of S1 and S2 (same as memcmp).  */
extern int bcmp (const void *__s1, const void *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Find the first occurrence of C in S (same as strchr).  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
extern "C++"
{
extern char *index (char *__s, int __c)
     __THROW __asm ("index") __attribute_pure__ __nonnull ((1));
extern const char *index (const char *__s, int __c)
     __THROW __asm ("index") __attribute_pure__ __nonnull ((1));

#  if defined __OPTIMIZE__ && !defined __CORRECT_ISO_CPP_STRINGS_H_PROTO
__extern_always_inline char *
index (char *__s, int __c) __THROW
{
  return __builtin_index (__s, __c);
}

__extern_always_inline const char *
index (const char *__s, int __c) __THROW
{
  return __builtin_index (__s, __c);
}
#  endif
# 482 "/usr/include/string.h" 3 4
}
# else
# 484 "/usr/include/string.h" 3 4
extern char *index (const char *__s, int __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
# 487 "/usr/include/string.h" 3 4

/* Find the last occurrence of C in S (same as strrchr).  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
extern "C++"
{
extern char *rindex (char *__s, int __c)
     __THROW __asm ("rindex") __attribute_pure__ __nonnull ((1));
extern const char *rindex (const char *__s, int __c)
     __THROW __asm ("rindex") __attribute_pure__ __nonnull ((1));

#  if defined __OPTIMIZE__ && !defined __CORRECT_ISO_CPP_STRINGS_H_PROTO
__extern_always_inline char *
rindex (char *__s, int __c) __THROW
{
  return __builtin_rindex (__s, __c);
}

__extern_always_inline const char *
rindex (const char *__s, int __c) __THROW
{
  return __builtin_rindex (__s, __c);
}
#endif
# 510 "/usr/include/string.h" 3 4
}
# else
# 512 "/usr/include/string.h" 3 4
extern char *rindex (const char *__s, int __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
# 515 "/usr/include/string.h" 3 4

/* Return the position of the first bit set in I, or 0 if none are set.
   The least-significant bit is position 1, the most-significant 32.  */
extern int ffs (int __i) __THROW __attribute__ ((__const__));

/* The following two functions are non-standard but necessary for non-32 bit
   platforms.  */
# ifdef	__USE_GNU
extern int ffsl (long int __l) __THROW __attribute__ ((__const__));
__extension__ extern int ffsll (long long int __ll)
     __THROW __attribute__ ((__const__));
# endif
# 527 "/usr/include/string.h" 3 4

/* Compare S1 and S2, ignoring case.  */
extern int strcasecmp (const char *__s1, const char *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare no more than N chars of S1 and S2, ignoring case.  */
extern int strncasecmp (const char *__s1, const char *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));
#endif /* Use misc.  */
# 536 "/usr/include/string.h" 3 4

#ifdef	__USE_GNU
/* Again versions of a few functions which use the given locale instead
   of the global one.  */
extern int strcasecmp_l (const char *__s1, const char *__s2,
			 __locale_t __loc)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));

extern int strncasecmp_l (const char *__s1, const char *__s2,
			  size_t __n, __locale_t __loc)
     __THROW __attribute_pure__ __nonnull ((1, 2, 4));
#endif
# 548 "/usr/include/string.h" 3 4

#ifdef	__USE_MISC
/* Return the next DELIM-delimited token from *STRINGP,
   terminating it with a '\0', and update *STRINGP to point past it.  */
extern char *strsep (char **__restrict __stringp,
		     const char *__restrict __delim)
     __THROW __nonnull ((1, 2));
#endif
# 556 "/usr/include/string.h" 3 4

#ifdef	__USE_XOPEN2K8
/* Return a string describing the meaning of the signal number in SIG.  */
extern char *strsignal (int __sig) __THROW;

/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
extern char *__stpcpy (char *__restrict __dest, const char *__restrict __src)
     __THROW __nonnull ((1, 2));
extern char *stpcpy (char *__restrict __dest, const char *__restrict __src)
     __THROW __nonnull ((1, 2));

/* Copy no more than N characters of SRC to DEST, returning the address of
   the last character written into DEST.  */
extern char *__stpncpy (char *__restrict __dest,
			const char *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
extern char *stpncpy (char *__restrict __dest,
		      const char *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#endif
# 576 "/usr/include/string.h" 3 4

#ifdef	__USE_GNU
/* Compare S1 and S2 as strings holding name & indices/version numbers.  */
extern int strverscmp (const char *__s1, const char *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Sautee STRING briskly.  */
extern char *strfry (char *__string) __THROW __nonnull ((1));

/* Frobnicate N bytes of S.  */
extern void *memfrob (void *__s, size_t __n) __THROW __nonnull ((1));

# ifndef basename
/* Return the file name within directory of FILENAME.  We don't
   declare the function if the `basename' macro is available (defined
   in <libgen.h>) which makes the XPG version of this function
   available.  */
#  ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
extern "C++" char *basename (char *__filename)
     __THROW __asm ("basename") __nonnull ((1));
extern "C++" const char *basename (const char *__filename)
     __THROW __asm ("basename") __nonnull ((1));
#  else
# 599 "/usr/include/string.h" 3 4
extern char *basename (const char *__filename) __THROW __nonnull ((1));
#  endif
# 601 "/usr/include/string.h" 3 4
# endif
# 602 "/usr/include/string.h" 3 4
#endif
# 603 "/usr/include/string.h" 3 4


#if defined __GNUC__ && __GNUC__ >= 2
# if defined __OPTIMIZE__ && !defined __OPTIMIZE_SIZE__ \
     && !defined __NO_INLINE__ && !defined __cplusplus
/* When using GNU CC we provide some optimized versions of selected
   functions from this header.  There are two kinds of optimizations:

   - machine-dependent optimizations, most probably using inline
     assembler code; these might be quite expensive since the code
     size can increase significantly.
     These optimizations are not used unless the symbol
	__USE_STRING_INLINES
     is defined before including this header.

   - machine-independent optimizations which do not increase the
     code size significantly and which optimize mainly situations
     where one or more arguments are compile-time constants.
     These optimizations are used always when the compiler is
     taught to optimize.

   One can inhibit all optimizations by defining __NO_STRING_INLINES.  */

/* Get the machine-dependent optimizations (if any).  */
#if 0 /* expanded by -frewrite-includes */
#  include <bits/string.h>
#endif /* expanded by -frewrite-includes */
# 627 "/usr/include/string.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/string.h" 1 3 4
/* Optimized, inlined string functions.  i486/x86-64 version.
   Copyright (C) 2001-2016 Free Software Foundation, Inc.
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

#ifndef _STRING_H
# error "Never use <bits/string.h> directly; include <string.h> instead."
#endif
# 22 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4

/* Use the unaligned string inline ABI.  */
#define _STRING_INLINE_unaligned 1

/* Don't inline mempcpy into memcpy as x86 has an optimized mempcpy.  */
#define _HAVE_STRING_ARCH_mempcpy 1

/* Enable inline functions only for i486 or better when compiling for
   ia32.  */
#if !defined __x86_64__ && (defined __i486__ || defined __pentium__	      \
			    || defined __pentiumpro__ || defined __pentium4__ \
			    || defined __nocona__ || defined __atom__ 	      \
			    || defined __core2__ || defined __corei7__	      \
			    || defined __sandybridge__ || defined __haswell__ \
			    || defined __bonnell__ || defined __silvermont__  \
			    || defined __k6__ || defined __geode__	      \
			    || defined __k8__ || defined __athlon__	      \
			    || defined __amdfam10__ || defined __bdver1__     \
			    || defined __bdver2__ || defined __bdver3__	      \
			    || defined __bdver4__ || defined __btver1__	      \
			    || defined __btver2__)

/* We only provide optimizations if the user selects them and if
   GNU CC is used.  */
# if !defined __NO_STRING_INLINES && defined __USE_STRING_INLINES \
    && defined __GNUC__ && __GNUC__ >= 2

# ifndef __STRING_INLINE
#  ifndef __extern_inline
#   define __STRING_INLINE inline
#  else
# 53 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
#   define __STRING_INLINE __extern_inline
#  endif
# 55 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
# endif
# 56 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4

/* The macros are used in some of the optimized implementations below.  */
# define __STRING_SMALL_GET16(src, idx) \
  ((((const unsigned char *) (src))[idx + 1] << 8)			      \
   | ((const unsigned char *) (src))[idx])
# define __STRING_SMALL_GET32(src, idx) \
  (((((const unsigned char *) (src))[idx + 3] << 8			      \
     | ((const unsigned char *) (src))[idx + 2]) << 8			      \
    | ((const unsigned char *) (src))[idx + 1]) << 8			      \
   | ((const unsigned char *) (src))[idx])


/* Copy N bytes of SRC to DEST.  */
# define _HAVE_STRING_ARCH_memcpy 1
# define memcpy(dest, src, n) \
  (__extension__ (__builtin_constant_p (n)				      \
		  ? __memcpy_c ((dest), (src), (n))			      \
		  : __memcpy_g ((dest), (src), (n))))
# define __memcpy_c(dest, src, n) \
  ((n) == 0								      \
   ? (dest)								      \
   : (((n) % 4 == 0)							      \
      ? __memcpy_by4 (dest, src, n)					      \
      : (((n) % 2 == 0)							      \
	 ? __memcpy_by2 (dest, src, n)					      \
	 : __memcpy_g (dest, src, n))))

__STRING_INLINE void *__memcpy_by4 (void *__dest, const void *__src,
				    size_t __n);

__STRING_INLINE void *
__memcpy_by4 (void *__dest, const void *__src, size_t __n)
{
  register unsigned long int __d0, __d1;
  register void *__tmp = __dest;
  __asm__ __volatile__
    ("1:\n\t"
     "movl	(%2),%0\n\t"
     "leal	4(%2),%2\n\t"
     "movl	%0,(%1)\n\t"
     "leal	4(%1),%1\n\t"
     "decl	%3\n\t"
     "jnz	1b"
     : "=&r" (__d0), "=&r" (__tmp), "=&r" (__src), "=&r" (__d1)
     : "1" (__tmp), "2" (__src), "3" (__n / 4)
     : "memory", "cc");
  return __dest;
}

__STRING_INLINE void *__memcpy_by2 (void *__dest, const void *__src,
				    size_t __n);

__STRING_INLINE void *
__memcpy_by2 (void *__dest, const void *__src, size_t __n)
{
  register unsigned long int __d0, __d1;
  register void *__tmp = __dest;
  __asm__ __volatile__
    ("shrl	$1,%3\n\t"
     "jz	2f\n"                 /* only a word */
     "1:\n\t"
     "movl	(%2),%0\n\t"
     "leal	4(%2),%2\n\t"
     "movl	%0,(%1)\n\t"
     "leal	4(%1),%1\n\t"
     "decl	%3\n\t"
     "jnz	1b\n"
     "2:\n\t"
     "movw	(%2),%w0\n\t"
     "movw	%w0,(%1)"
     : "=&q" (__d0), "=&r" (__tmp), "=&r" (__src), "=&r" (__d1)
     : "1" (__tmp), "2" (__src), "3" (__n / 2)
     : "memory", "cc");
  return __dest;
}

__STRING_INLINE void *__memcpy_g (void *__dest, const void *__src, size_t __n);

__STRING_INLINE void *
__memcpy_g (void *__dest, const void *__src, size_t __n)
{
  register unsigned long int __d0, __d1, __d2;
  register void *__tmp = __dest;
  __asm__ __volatile__
    ("cld\n\t"
     "shrl	$1,%%ecx\n\t"
     "jnc	1f\n\t"
     "movsb\n"
     "1:\n\t"
     "shrl	$1,%%ecx\n\t"
     "jnc	2f\n\t"
     "movsw\n"
     "2:\n\t"
     "rep; movsl"
     : "=&c" (__d0), "=&D" (__d1), "=&S" (__d2),
       "=m" ( *(struct { __extension__ char __x[__n]; } *)__dest)
     : "0" (__n), "1" (__tmp), "2" (__src),
       "m" ( *(struct { __extension__ char __x[__n]; } *)__src)
     : "cc");
  return __dest;
}

# define _HAVE_STRING_ARCH_memmove 1
# ifndef _FORCE_INLINES
/* Copy N bytes of SRC to DEST, guaranteeing
   correct behavior for overlapping strings.  */
#  define memmove(dest, src, n) __memmove_g (dest, src, n)

__STRING_INLINE void *__memmove_g (void *, const void *, size_t)
     __asm__ ("memmove");

__STRING_INLINE void *
__memmove_g (void *__dest, const void *__src, size_t __n)
{
  register unsigned long int __d0, __d1, __d2;
  register void *__tmp = __dest;
  if (__dest < __src)
    __asm__ __volatile__
      ("cld\n\t"
       "rep; movsb"
       : "=&c" (__d0), "=&S" (__d1), "=&D" (__d2),
	 "=m" ( *(struct { __extension__ char __x[__n]; } *)__dest)
       : "0" (__n), "1" (__src), "2" (__tmp),
	 "m" ( *(struct { __extension__ char __x[__n]; } *)__src));
  else
    __asm__ __volatile__
      ("decl %1\n\t"
       "decl %2\n\t"
       "std\n\t"
       "rep; movsb\n\t"
       "cld"
       : "=&c" (__d0), "=&S" (__d1), "=&D" (__d2),
	 "=m" ( *(struct { __extension__ char __x[__n]; } *)__dest)
       : "0" (__n), "1" (__n + (const char *) __src),
	 "2" (__n + (char *) __tmp),
	 "m" ( *(struct { __extension__ char __x[__n]; } *)__src));
  return __dest;
}
# endif
# 195 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4

/* Compare N bytes of S1 and S2.  */
# define _HAVE_STRING_ARCH_memcmp 1
# ifndef _FORCE_INLINES
#  ifndef __PIC__
/* gcc has problems to spill registers when using PIC.  */
__STRING_INLINE int
memcmp (const void *__s1, const void *__s2, size_t __n)
{
  register unsigned long int __d0, __d1, __d2;
  register int __res;
  __asm__ __volatile__
    ("cld\n\t"
     "testl %3,%3\n\t"
     "repe; cmpsb\n\t"
     "je	1f\n\t"
     "sbbl	%0,%0\n\t"
     "orl	$1,%0\n"
     "1:"
     : "=&a" (__res), "=&S" (__d0), "=&D" (__d1), "=&c" (__d2)
     : "0" (0), "1" (__s1), "2" (__s2), "3" (__n),
       "m" ( *(struct { __extension__ char __x[__n]; } *)__s1),
       "m" ( *(struct { __extension__ char __x[__n]; } *)__s2)
     : "cc");
  return __res;
}
#  endif
# 222 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
# endif
# 223 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4

/* Set N bytes of S to C.  */
# define _HAVE_STRING_ARCH_memset 1
# define _USE_STRING_ARCH_memset 1
# define memset(s, c, n) \
  (__extension__ (__builtin_constant_p (n) && (n) <= 16			      \
		  ? ((n) == 1						      \
		     ? __memset_c1 ((s), (c))				      \
		     : __memset_gc ((s), (c), (n)))			      \
		  : (__builtin_constant_p (c)				      \
		     ? (__builtin_constant_p (n)			      \
			? __memset_ccn ((s), (c), (n))			      \
			: memset ((s), (c), (n)))			      \
		     : (__builtin_constant_p (n)			      \
			? __memset_gcn ((s), (c), (n))			      \
			: memset ((s), (c), (n))))))

# define __memset_c1(s, c) ({ void *__s = (s);				      \
			      *((unsigned char *) __s) = (unsigned char) (c); \
			      __s; })

# define __memset_gc(s, c, n) \
  ({ void *__s = (s);							      \
     union {								      \
       unsigned int __ui;						      \
       unsigned short int __usi;					      \
       unsigned char __uc;						      \
     } *__u = __s;							      \
     unsigned int __c = ((unsigned int) ((unsigned char) (c))) * 0x01010101;  \
									      \
     /* We apply a trick here.  `gcc' would implement the following	      \
	assignments using immediate operands.  But this uses to much	      \
	memory (7, instead of 4 bytes).  So we force the value in a	      \
	registers.  */							      \
     if ((n) == 3 || (n) >= 5)						      \
       __asm__ __volatile__ ("" : "=r" (__c) : "0" (__c));		      \
									      \
     /* This `switch' statement will be removed at compile-time.  */	      \
     switch (n)								      \
       {								      \
       case 15:								      \
	 __u->__ui = __c;						      \
	 __u = __extension__ ((void *) __u + 4);			      \
       case 11:								      \
	 __u->__ui = __c;						      \
	 __u = __extension__ ((void *) __u + 4);			      \
       case 7:								      \
	 __u->__ui = __c;						      \
	 __u = __extension__ ((void *) __u + 4);			      \
       case 3:								      \
	 __u->__usi = (unsigned short int) __c;				      \
	 __u = __extension__ ((void *) __u + 2);			      \
	 __u->__uc = (unsigned char) __c;				      \
	 break;								      \
									      \
       case 14:								      \
	 __u->__ui = __c;						      \
	 __u = __extension__ ((void *) __u + 4);			      \
       case 10:								      \
	 __u->__ui = __c;						      \
	 __u = __extension__ ((void *) __u + 4);			      \
       case 6:								      \
	 __u->__ui = __c;						      \
	 __u = __extension__ ((void *) __u + 4);			      \
       case 2:								      \
	 __u->__usi = (unsigned short int) __c;				      \
	 break;								      \
									      \
       case 13:								      \
	 __u->__ui = __c;						      \
	 __u = __extension__ ((void *) __u + 4);			      \
       case 9:								      \
	 __u->__ui = __c;						      \
	 __u = __extension__ ((void *) __u + 4);			      \
       case 5:								      \
	 __u->__ui = __c;						      \
	 __u = __extension__ ((void *) __u + 4);			      \
       case 1:								      \
	 __u->__uc = (unsigned char) __c;				      \
	 break;								      \
									      \
       case 16:								      \
	 __u->__ui = __c;						      \
	 __u = __extension__ ((void *) __u + 4);			      \
       case 12:								      \
	 __u->__ui = __c;						      \
	 __u = __extension__ ((void *) __u + 4);			      \
       case 8:								      \
	 __u->__ui = __c;						      \
	 __u = __extension__ ((void *) __u + 4);			      \
       case 4:								      \
	 __u->__ui = __c;						      \
       case 0:								      \
	 break;								      \
       }								      \
									      \
     __s; })

# define __memset_ccn(s, c, n) \
  (((n) % 4 == 0)							      \
   ? __memset_ccn_by4 (s, ((unsigned int) ((unsigned char) (c))) * 0x01010101,\
		       n)						      \
   : (((n) % 2 == 0)							      \
      ? __memset_ccn_by2 (s,						      \
			  ((unsigned int) ((unsigned char) (c))) * 0x01010101,\
			   n)						      \
      : memset (s, c, n)))

__STRING_INLINE void *__memset_ccn_by4 (void *__s, unsigned int __c,
					size_t __n);

__STRING_INLINE void *
__memset_ccn_by4 (void *__s, unsigned int __c, size_t __n)
{
  register void *__tmp = __s;
  register unsigned long int __d0;
# ifdef __i686__
  __asm__ __volatile__
    ("cld\n\t"
     "rep; stosl"
     : "=&a" (__c), "=&D" (__tmp), "=&c" (__d0),
       "=m" ( *(struct { __extension__ char __x[__n]; } *)__s)
     : "0" ((unsigned int) __c), "1" (__tmp), "2" (__n / 4)
     : "cc");
# else
# 348 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
  __asm__ __volatile__
    ("1:\n\t"
     "movl	%0,(%1)\n\t"
     "addl	$4,%1\n\t"
     "decl	%2\n\t"
     "jnz	1b\n"
     : "=&r" (__c), "=&r" (__tmp), "=&r" (__d0),
       "=m" ( *(struct { __extension__ char __x[__n]; } *)__s)
     : "0" ((unsigned int) __c), "1" (__tmp), "2" (__n / 4)
     : "cc");
# endif
# 359 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
  return __s;
}

__STRING_INLINE void *__memset_ccn_by2 (void *__s, unsigned int __c,
					size_t __n);

__STRING_INLINE void *
__memset_ccn_by2 (void *__s, unsigned int __c, size_t __n)
{
  register unsigned long int __d0, __d1;
  register void *__tmp = __s;
# ifdef __i686__
  __asm__ __volatile__
    ("cld\n\t"
     "rep; stosl\n"
     "stosw"
     : "=&a" (__d0), "=&D" (__tmp), "=&c" (__d1),
       "=m" ( *(struct { __extension__ char __x[__n]; } *)__s)
     : "0" ((unsigned int) __c), "1" (__tmp), "2" (__n / 4)
     : "cc");
# else
# 380 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
  __asm__ __volatile__
    ("1:\tmovl	%0,(%1)\n\t"
     "leal	4(%1),%1\n\t"
     "decl	%2\n\t"
     "jnz	1b\n"
     "movw	%w0,(%1)"
     : "=&q" (__d0), "=&r" (__tmp), "=&r" (__d1),
       "=m" ( *(struct { __extension__ char __x[__n]; } *)__s)
     : "0" ((unsigned int) __c), "1" (__tmp), "2" (__n / 4)
     : "cc");
#endif
# 391 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
  return __s;
}

# define __memset_gcn(s, c, n) \
  (((n) % 4 == 0)							      \
   ? __memset_gcn_by4 (s, c, n)						      \
   : (((n) % 2 == 0)							      \
      ? __memset_gcn_by2 (s, c, n)					      \
      : memset (s, c, n)))

__STRING_INLINE void *__memset_gcn_by4 (void *__s, int __c, size_t __n);

__STRING_INLINE void *
__memset_gcn_by4 (void *__s, int __c, size_t __n)
{
  register void *__tmp = __s;
  register unsigned long int __d0;
  __asm__ __volatile__
    ("movb	%b0,%h0\n"
     "pushw	%w0\n\t"
     "shll	$16,%0\n\t"
     "popw	%w0\n"
     "1:\n\t"
     "movl	%0,(%1)\n\t"
     "addl	$4,%1\n\t"
     "decl	%2\n\t"
     "jnz	1b\n"
     : "=&q" (__c), "=&r" (__tmp), "=&r" (__d0),
       "=m" ( *(struct { __extension__ char __x[__n]; } *)__s)
     : "0" ((unsigned int) __c), "1" (__tmp), "2" (__n / 4)
     : "cc");
  return __s;
}

__STRING_INLINE void *__memset_gcn_by2 (void *__s, int __c, size_t __n);

__STRING_INLINE void *
__memset_gcn_by2 (void *__s, int __c, size_t __n)
{
  register unsigned long int __d0, __d1;
  register void *__tmp = __s;
  __asm__ __volatile__
    ("movb	%b0,%h0\n\t"
     "pushw	%w0\n\t"
     "shll	$16,%0\n\t"
     "popw	%w0\n"
     "1:\n\t"
     "movl	%0,(%1)\n\t"
     "leal	4(%1),%1\n\t"
     "decl	%2\n\t"
     "jnz	1b\n"
     "movw	%w0,(%1)"
     : "=&q" (__d0), "=&r" (__tmp), "=&r" (__d1),
       "=m" ( *(struct { __extension__ char __x[__n]; } *)__s)
     : "0" ((unsigned int) __c), "1" (__tmp), "2" (__n / 4)
     : "cc");
  return __s;
}


/* Search N bytes of S for C.  */
# define _HAVE_STRING_ARCH_memchr 1
# ifndef _FORCE_INLINES
__STRING_INLINE void *
memchr (const void *__s, int __c, size_t __n)
{
  register unsigned long int __d0;
#  ifdef __i686__
  register unsigned long int __d1;
#  endif
# 461 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
  register unsigned char *__res;
  if (__n == 0)
    return NULL;
#  ifdef __i686__
  __asm__ __volatile__
    ("cld\n\t"
     "repne; scasb\n\t"
     "cmovne %2,%0"
     : "=D" (__res), "=&c" (__d0), "=&r" (__d1)
     : "a" (__c), "0" (__s), "1" (__n), "2" (1),
       "m" ( *(struct { __extension__ char __x[__n]; } *)__s)
     : "cc");
#  else
# 474 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
  __asm__ __volatile__
    ("cld\n\t"
     "repne; scasb\n\t"
     "je	1f\n\t"
     "movl	$1,%0\n"
     "1:"
     : "=D" (__res), "=&c" (__d0)
     : "a" (__c), "0" (__s), "1" (__n),
       "m" ( *(struct { __extension__ char __x[__n]; } *)__s)
     : "cc");
#  endif
# 485 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
  return __res - 1;
}
# endif
# 488 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4

# define _HAVE_STRING_ARCH_memrchr 1
# ifndef _FORCE_INLINES
__STRING_INLINE void *__memrchr (const void *__s, int __c, size_t __n);

__STRING_INLINE void *
__memrchr (const void *__s, int __c, size_t __n)
{
  register unsigned long int __d0;
#  ifdef __i686__
  register unsigned long int __d1;
#  endif
# 500 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
  register void *__res;
  if (__n == 0)
    return NULL;
#  ifdef __i686__
  __asm__ __volatile__
    ("std\n\t"
     "repne; scasb\n\t"
     "cmovne %2,%0\n\t"
     "cld\n\t"
     "incl %0"
     : "=D" (__res), "=&c" (__d0), "=&r" (__d1)
     : "a" (__c), "0" (__s + __n - 1), "1" (__n), "2" (-1),
       "m" ( *(struct { __extension__ char __x[__n]; } *)__s)
     : "cc");
#  else
# 515 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
  __asm__ __volatile__
    ("std\n\t"
     "repne; scasb\n\t"
     "je 1f\n\t"
     "orl $-1,%0\n"
     "1:\tcld\n\t"
     "incl %0"
     : "=D" (__res), "=&c" (__d0)
     : "a" (__c), "0" (__s + __n - 1), "1" (__n),
       "m" ( *(struct { __extension__ char __x[__n]; } *)__s)
     : "cc");
#  endif
# 527 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
  return __res;
}
#  ifdef __USE_GNU
#   define memrchr(s, c, n) __memrchr ((s), (c), (n))
#  endif
# 532 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
# endif
# 533 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4

/* Return pointer to C in S.  */
# define _HAVE_STRING_ARCH_rawmemchr 1
__STRING_INLINE void *__rawmemchr (const void *__s, int __c);

# ifndef _FORCE_INLINES
__STRING_INLINE void *
__rawmemchr (const void *__s, int __c)
{
  register unsigned long int __d0;
  register unsigned char *__res;
  __asm__ __volatile__
    ("cld\n\t"
     "repne; scasb\n\t"
     : "=D" (__res), "=&c" (__d0)
     : "a" (__c), "0" (__s), "1" (0xffffffff),
       "m" ( *(struct { char __x[0xfffffff]; } *)__s)
     : "cc");
  return __res - 1;
}
#  ifdef __USE_GNU
__STRING_INLINE void *
rawmemchr (const void *__s, int __c)
{
  return __rawmemchr (__s, __c);
}
#  endif /* use GNU */
# 560 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
# endif
# 561 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4


/* Return the length of S.  */
# define _HAVE_STRING_ARCH_strlen 1
# define strlen(str) \
  (__extension__ (__builtin_constant_p (str)				      \
		  ? __builtin_strlen (str)				      \
		  : __strlen_g (str)))
__STRING_INLINE size_t __strlen_g (const char *__str);

__STRING_INLINE size_t
__strlen_g (const char *__str)
{
  register char __dummy;
  register const char *__tmp = __str;
  __asm__ __volatile__
    ("1:\n\t"
     "movb	(%0),%b1\n\t"
     "leal	1(%0),%0\n\t"
     "testb	%b1,%b1\n\t"
     "jne	1b"
     : "=r" (__tmp), "=&q" (__dummy)
     : "0" (__str),
       "m" ( *(struct { char __x[0xfffffff]; } *)__str)
     : "cc" );
  return __tmp - __str - 1;
}


/* Copy SRC to DEST.  */
# define _HAVE_STRING_ARCH_strcpy 1
# define strcpy(dest, src) \
  (__extension__ (__builtin_constant_p (src)				      \
		  ? (sizeof ((src)[0]) == 1 && strlen (src) + 1 <= 8	      \
		     ? __strcpy_a_small ((dest), (src), strlen (src) + 1)     \
		     : (char *) memcpy ((char *) (dest),		      \
					(const char *) (src),		      \
					strlen (src) + 1))		      \
		  : __strcpy_g ((dest), (src))))

# define __strcpy_a_small(dest, src, srclen) \
  (__extension__ ({ char *__dest = (dest);				      \
		    union {						      \
		      unsigned int __ui;				      \
		      unsigned short int __usi;				      \
		      unsigned char __uc;				      \
		      char __c;						      \
		    } *__u = (void *) __dest;				      \
		    switch (srclen)					      \
		      {							      \
		      case 1:						      \
			__u->__uc = '\0';				      \
			break;						      \
		      case 2:						      \
			__u->__usi = __STRING_SMALL_GET16 (src, 0);	      \
			break;						      \
		      case 3:						      \
			__u->__usi = __STRING_SMALL_GET16 (src, 0);	      \
			__u = __extension__ ((void *) __u + 2);		      \
			__u->__uc = '\0';				      \
			break;						      \
		      case 4:						      \
			__u->__ui = __STRING_SMALL_GET32 (src, 0);	      \
			break;						      \
		      case 5:						      \
			__u->__ui = __STRING_SMALL_GET32 (src, 0);	      \
			__u = __extension__ ((void *) __u + 4);		      \
			__u->__uc = '\0';				      \
			break;						      \
		      case 6:						      \
			__u->__ui = __STRING_SMALL_GET32 (src, 0);	      \
			__u = __extension__ ((void *) __u + 4);		      \
			__u->__usi = __STRING_SMALL_GET16 (src, 4);	      \
			break;						      \
		      case 7:						      \
			__u->__ui = __STRING_SMALL_GET32 (src, 0);	      \
			__u = __extension__ ((void *) __u + 4);		      \
			__u->__usi = __STRING_SMALL_GET16 (src, 4);	      \
			__u = __extension__ ((void *) __u + 2);		      \
			__u->__uc = '\0';				      \
			break;						      \
		      case 8:						      \
			__u->__ui = __STRING_SMALL_GET32 (src, 0);	      \
			__u = __extension__ ((void *) __u + 4);		      \
			__u->__ui = __STRING_SMALL_GET32 (src, 4);	      \
			break;						      \
		      }							      \
		    (char *) __dest; }))

__STRING_INLINE char *__strcpy_g (char *__dest, const char *__src);

__STRING_INLINE char *
__strcpy_g (char *__dest, const char *__src)
{
  register char *__tmp = __dest;
  register char __dummy;
  __asm__ __volatile__
    (
     "1:\n\t"
     "movb	(%0),%b2\n\t"
     "leal	1(%0),%0\n\t"
     "movb	%b2,(%1)\n\t"
     "leal	1(%1),%1\n\t"
     "testb	%b2,%b2\n\t"
     "jne	1b"
     : "=&r" (__src), "=&r" (__tmp), "=&q" (__dummy),
       "=m" ( *(struct { char __x[0xfffffff]; } *)__dest)
     : "0" (__src), "1" (__tmp),
       "m" ( *(struct { char __x[0xfffffff]; } *)__src)
     : "cc");
  return __dest;
}


# ifdef __USE_GNU
#  define _HAVE_STRING_ARCH_stpcpy 1
/* Copy SRC to DEST.  */
#  define __stpcpy(dest, src) \
  (__extension__ (__builtin_constant_p (src)				      \
		  ? (strlen (src) + 1 <= 8				      \
		     ? __stpcpy_a_small ((dest), (src), strlen (src) + 1)     \
		     : __stpcpy_c ((dest), (src), strlen (src) + 1))	      \
		  : __stpcpy_g ((dest), (src))))
#  define __stpcpy_c(dest, src, srclen) \
  ((srclen) % 4 == 0							      \
   ? __mempcpy_by4 (dest, src, srclen) - 1				      \
   : ((srclen) % 2 == 0							      \
      ? __mempcpy_by2 (dest, src, srclen) - 1				      \
      : __mempcpy_byn (dest, src, srclen) - 1))

/* In glibc itself we use this symbol for namespace reasons.  */
#  define stpcpy(dest, src) __stpcpy ((dest), (src))

#  define __stpcpy_a_small(dest, src, srclen) \
  (__extension__ ({ union {						      \
		      unsigned int __ui;				      \
		      unsigned short int __usi;				      \
		      unsigned char __uc;				      \
		      char __c;						      \
		    } *__u = (void *) (dest);				      \
		    switch (srclen)					      \
		      {							      \
		      case 1:						      \
			__u->__uc = '\0';				      \
			break;						      \
		      case 2:						      \
			__u->__usi = __STRING_SMALL_GET16 (src, 0);	      \
			__u = __extension__ ((void *) __u + 1);		      \
			break;						      \
		      case 3:						      \
			__u->__usi = __STRING_SMALL_GET16 (src, 0);	      \
			__u = __extension__ ((void *) __u + 2);		      \
			__u->__uc = '\0';				      \
			break;						      \
		      case 4:						      \
			__u->__ui = __STRING_SMALL_GET32 (src, 0);	      \
			__u = __extension__ ((void *) __u + 3);		      \
			break;						      \
		      case 5:						      \
			__u->__ui = __STRING_SMALL_GET32 (src, 0);	      \
			__u = __extension__ ((void *) __u + 4);		      \
			__u->__uc = '\0';				      \
			break;						      \
		      case 6:						      \
			__u->__ui = __STRING_SMALL_GET32 (src, 0);	      \
			__u = __extension__ ((void *) __u + 4);		      \
			__u->__usi = __STRING_SMALL_GET16 (src, 4);	      \
			__u = __extension__ ((void *) __u + 1);		      \
			break;						      \
		      case 7:						      \
			__u->__ui = __STRING_SMALL_GET32 (src, 0);	      \
			__u = __extension__ ((void *) __u + 4);		      \
			__u->__usi = __STRING_SMALL_GET16 (src, 4);	      \
			__u = __extension__ ((void *) __u + 2);		      \
			__u->__uc = '\0';				      \
			break;						      \
		      case 8:						      \
			__u->__ui = __STRING_SMALL_GET32 (src, 0);	      \
			__u = __extension__ ((void *) __u + 4);		      \
			__u->__ui = __STRING_SMALL_GET32 (src, 4);	      \
			__u = __extension__ ((void *) __u + 3);		      \
			break;						      \
		      }							      \
		    (char *) __u; }))

__STRING_INLINE char *__mempcpy_by4 (char *__dest, const char *__src,
				     size_t __srclen);

__STRING_INLINE char *
__mempcpy_by4 (char *__dest, const char *__src, size_t __srclen)
{
  register char *__tmp = __dest;
  register unsigned long int __d0, __d1;
  __asm__ __volatile__
    ("1:\n\t"
     "movl	(%2),%0\n\t"
     "leal	4(%2),%2\n\t"
     "movl	%0,(%1)\n\t"
     "leal	4(%1),%1\n\t"
     "decl	%3\n\t"
     "jnz	1b"
     : "=&r" (__d0), "=r" (__tmp), "=&r" (__src), "=&r" (__d1)
     : "1" (__tmp), "2" (__src), "3" (__srclen / 4)
     : "memory", "cc");
  return __tmp;
}

__STRING_INLINE char *__mempcpy_by2 (char *__dest, const char *__src,
				     size_t __srclen);

__STRING_INLINE char *
__mempcpy_by2 (char *__dest, const char *__src, size_t __srclen)
{
  register char *__tmp = __dest;
  register unsigned long int __d0, __d1;
  __asm__ __volatile__
    ("shrl	$1,%3\n\t"
     "jz	2f\n"                 /* only a word */
     "1:\n\t"
     "movl	(%2),%0\n\t"
     "leal	4(%2),%2\n\t"
     "movl	%0,(%1)\n\t"
     "leal	4(%1),%1\n\t"
     "decl	%3\n\t"
     "jnz	1b\n"
     "2:\n\t"
     "movw	(%2),%w0\n\t"
     "movw	%w0,(%1)"
     : "=&q" (__d0), "=r" (__tmp), "=&r" (__src), "=&r" (__d1),
       "=m" ( *(struct { __extension__ char __x[__srclen]; } *)__dest)
     : "1" (__tmp), "2" (__src), "3" (__srclen / 2),
       "m" ( *(struct { __extension__ char __x[__srclen]; } *)__src)
     : "cc");
  return __tmp + 2;
}

__STRING_INLINE char *__mempcpy_byn (char *__dest, const char *__src,
				     size_t __srclen);

__STRING_INLINE char *
__mempcpy_byn (char *__dest, const char *__src, size_t __srclen)
{
  register unsigned long __d0, __d1;
  register char *__tmp = __dest;
  __asm__ __volatile__
    ("cld\n\t"
     "shrl	$1,%%ecx\n\t"
     "jnc	1f\n\t"
     "movsb\n"
     "1:\n\t"
     "shrl	$1,%%ecx\n\t"
     "jnc	2f\n\t"
     "movsw\n"
     "2:\n\t"
     "rep; movsl"
     : "=D" (__tmp), "=&c" (__d0), "=&S" (__d1),
       "=m" ( *(struct { __extension__ char __x[__srclen]; } *)__dest)
     : "0" (__tmp), "1" (__srclen), "2" (__src),
       "m" ( *(struct { __extension__ char __x[__srclen]; } *)__src)
     : "cc");
  return __tmp;
}

__STRING_INLINE char *__stpcpy_g (char *__dest, const char *__src);

__STRING_INLINE char *
__stpcpy_g (char *__dest, const char *__src)
{
  register char *__tmp = __dest;
  register char __dummy;
  __asm__ __volatile__
    (
     "1:\n\t"
     "movb	(%0),%b2\n\t"
     "leal	1(%0),%0\n\t"
     "movb	%b2,(%1)\n\t"
     "leal	1(%1),%1\n\t"
     "testb	%b2,%b2\n\t"
     "jne	1b"
     : "=&r" (__src), "=r" (__tmp), "=&q" (__dummy),
       "=m" ( *(struct { char __x[0xfffffff]; } *)__dest)
     : "0" (__src), "1" (__tmp),
       "m" ( *(struct { char __x[0xfffffff]; } *)__src)
     : "cc");
  return __tmp - 1;
}
# endif
# 848 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4


/* Copy no more than N characters of SRC to DEST.  */
# define _HAVE_STRING_ARCH_strncpy 1
# define strncpy(dest, src, n) \
  (__extension__ (__builtin_constant_p (src)				      \
		  ? ((strlen (src) + 1 >= ((size_t) (n))		      \
		      ? (char *) memcpy ((char *) (dest),		      \
					 (const char *) (src), n)	      \
		      : __strncpy_cg ((dest), (src), strlen (src) + 1, n)))   \
		  : __strncpy_gg ((dest), (src), n)))
# define __strncpy_cg(dest, src, srclen, n) \
  (((srclen) % 4 == 0)							      \
   ? __strncpy_by4 (dest, src, srclen, n)				      \
   : (((srclen) % 2 == 0)						      \
      ? __strncpy_by2 (dest, src, srclen, n)				      \
      : __strncpy_byn (dest, src, srclen, n)))

__STRING_INLINE char *__strncpy_by4 (char *__dest, const char __src[],
				     size_t __srclen, size_t __n);

__STRING_INLINE char *
__strncpy_by4 (char *__dest, const char __src[], size_t __srclen, size_t __n)
{
  register char *__tmp = __dest;
  register int __dummy1, __dummy2;
  __asm__ __volatile__
    ("1:\n\t"
     "movl	(%2),%0\n\t"
     "leal	4(%2),%2\n\t"
     "movl	%0,(%1)\n\t"
     "leal	4(%1),%1\n\t"
     "decl	%3\n\t"
     "jnz	1b"
     : "=&r" (__dummy1), "=r" (__tmp), "=&r" (__src), "=&r" (__dummy2),
       "=m" ( *(struct { __extension__ char __x[__srclen]; } *)__dest)
     : "1" (__tmp), "2" (__src), "3" (__srclen / 4),
       "m" ( *(struct { __extension__ char __x[__srclen]; } *)__src)
     : "cc");
  (void) memset (__tmp, '\0', __n - __srclen);
  return __dest;
}

__STRING_INLINE char *__strncpy_by2 (char *__dest, const char __src[],
				     size_t __srclen, size_t __n);

__STRING_INLINE char *
__strncpy_by2 (char *__dest, const char __src[], size_t __srclen, size_t __n)
{
  register char *__tmp = __dest;
  register int __dummy1, __dummy2;
  __asm__ __volatile__
    ("shrl	$1,%3\n\t"
     "jz	2f\n"                 /* only a word */
     "1:\n\t"
     "movl	(%2),%0\n\t"
     "leal	4(%2),%2\n\t"
     "movl	%0,(%1)\n\t"
     "leal	4(%1),%1\n\t"
     "decl	%3\n\t"
     "jnz	1b\n"
     "2:\n\t"
     "movw	(%2),%w0\n\t"
     "movw	%w0,(%1)\n\t"
     : "=&q" (__dummy1), "=r" (__tmp), "=&r" (__src), "=&r" (__dummy2),
       "=m" ( *(struct { __extension__ char __x[__srclen]; } *)__dest)
     : "1" (__tmp), "2" (__src), "3" (__srclen / 2),
       "m" ( *(struct { __extension__ char __x[__srclen]; } *)__src)
     : "cc");
  (void) memset (__tmp + 2, '\0', __n - __srclen);
  return __dest;
}

__STRING_INLINE char *__strncpy_byn (char *__dest, const char __src[],
				     size_t __srclen, size_t __n);

__STRING_INLINE char *
__strncpy_byn (char *__dest, const char __src[], size_t __srclen, size_t __n)
{
  register unsigned long int __d0, __d1;
  register char *__tmp = __dest;
  __asm__ __volatile__
    ("cld\n\t"
     "shrl	$1,%1\n\t"
     "jnc	1f\n\t"
     "movsb\n"
     "1:\n\t"
     "shrl	$1,%1\n\t"
     "jnc	2f\n\t"
     "movsw\n"
     "2:\n\t"
     "rep; movsl"
     : "=D" (__tmp), "=&c" (__d0), "=&S" (__d1),
       "=m" ( *(struct { __extension__ char __x[__srclen]; } *)__dest)
     : "1" (__srclen), "0" (__tmp),"2" (__src),
       "m" ( *(struct { __extension__ char __x[__srclen]; } *)__src)
     : "cc");
  (void) memset (__tmp, '\0', __n - __srclen);
  return __dest;
}

__STRING_INLINE char *__strncpy_gg (char *__dest, const char *__src,
				    size_t __n);

__STRING_INLINE char *
__strncpy_gg (char *__dest, const char *__src, size_t __n)
{
  register char *__tmp = __dest;
  register char __dummy;
  if (__n > 0)
    __asm__ __volatile__
      ("1:\n\t"
       "movb	(%0),%2\n\t"
       "incl	%0\n\t"
       "movb	%2,(%1)\n\t"
       "incl	%1\n\t"
       "decl	%3\n\t"
       "je	3f\n\t"
       "testb	%2,%2\n\t"
       "jne	1b\n\t"
       "2:\n\t"
       "movb	%2,(%1)\n\t"
       "incl	%1\n\t"
       "decl	%3\n\t"
       "jne	2b\n\t"
       "3:"
       : "=&r" (__src), "=&r" (__tmp), "=&q" (__dummy), "=&r" (__n)
       : "0" (__src), "1" (__tmp), "3" (__n)
       : "memory", "cc");

  return __dest;
}


/* Append SRC onto DEST.  */
# define _HAVE_STRING_ARCH_strcat 1
# define strcat(dest, src) \
  (__extension__ (__builtin_constant_p (src)				      \
		  ? __strcat_c ((dest), (src), strlen (src) + 1)	      \
		  : __strcat_g ((dest), (src))))

__STRING_INLINE char *__strcat_c (char *__dest, const char __src[],
				  size_t __srclen);

__STRING_INLINE char *
__strcat_c (char *__dest, const char __src[], size_t __srclen)
{
# ifdef __i686__
  register unsigned long int __d0;
  register char *__tmp;
  __asm__ __volatile__
    ("repne; scasb"
     : "=D" (__tmp), "=&c" (__d0),
       "=m" ( *(struct { char __x[0xfffffff]; } *)__dest)
     : "0" (__dest), "1" (0xffffffff), "a" (0),
       "m" ( *(struct { __extension__ char __x[__srclen]; } *)__src)
     : "cc");
  --__tmp;
# else
# 1007 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
  register char *__tmp = __dest;
  __asm__ __volatile__
    ("decl	%0\n\t"
     "1:\n\t"
     "incl	%0\n\t"
     "cmpb	$0,(%0)\n\t"
     "jne	1b\n"
     : "=r" (__tmp),
       "=m" ( *(struct { char __x[0xfffffff]; } *)__dest)
     : "0" (__tmp),
       "m" ( *(struct { __extension__ char __x[__srclen]; } *)__src)
     : "cc");
# endif
# 1020 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
  (void) memcpy (__tmp, __src, __srclen);
  return __dest;
}

__STRING_INLINE char *__strcat_g (char *__dest, const char *__src);

__STRING_INLINE char *
__strcat_g (char *__dest, const char *__src)
{
  register char *__tmp = __dest;
  register char __dummy;
  __asm__ __volatile__
    ("decl	%1\n\t"
     "1:\n\t"
     "incl	%1\n\t"
     "cmpb	$0,(%1)\n\t"
     "jne	1b\n"
     "2:\n\t"
     "movb	(%2),%b0\n\t"
     "incl	%2\n\t"
     "movb	%b0,(%1)\n\t"
     "incl	%1\n\t"
     "testb	%b0,%b0\n\t"
     "jne	2b\n"
     : "=&q" (__dummy), "=&r" (__tmp), "=&r" (__src),
       "=m" ( *(struct { char __x[0xfffffff]; } *)__dest)
     : "1"  (__tmp), "2"  (__src),
       "m" ( *(struct { char __x[0xfffffff]; } *)__src)
     : "memory", "cc");
  return __dest;
}


/* Append no more than N characters from SRC onto DEST.  */
# define _HAVE_STRING_ARCH_strncat 1
# define strncat(dest, src, n) \
  (__extension__ ({ char *__dest = (dest);				      \
		    __builtin_constant_p (src) && __builtin_constant_p (n)    \
		    ? (strlen (src) < ((size_t) (n))			      \
		       ? strcat (__dest, (src))				      \
		       : (*(char *)__mempcpy (strchr (__dest, '\0'),	      \
					       (const char *) (src),	      \
					      (n)) = 0, __dest))	      \
		    : __strncat_g (__dest, (src), (n)); }))

__STRING_INLINE char *__strncat_g (char *__dest, const char __src[],
				   size_t __n);

__STRING_INLINE char *
__strncat_g (char *__dest, const char __src[], size_t __n)
{
  register char *__tmp = __dest;
  register char __dummy;
# ifdef __i686__
  __asm__ __volatile__
    ("repne; scasb\n"
     "movl %4, %3\n\t"
     "decl %1\n\t"
     "1:\n\t"
     "subl	$1,%3\n\t"
     "jc	2f\n\t"
     "movb	(%2),%b0\n\t"
     "movsb\n\t"
     "testb	%b0,%b0\n\t"
     "jne	1b\n\t"
     "decl	%1\n"
     "2:\n\t"
     "movb	$0,(%1)"
     : "=&a" (__dummy), "=&D" (__tmp), "=&S" (__src), "=&c" (__n)
     :  "g" (__n), "0" (0), "1" (__tmp), "2" (__src), "3" (0xffffffff)
     : "memory", "cc");
# else
# 1092 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
  --__tmp;
  __asm__ __volatile__
    ("1:\n\t"
     "cmpb	$0,1(%1)\n\t"
     "leal	1(%1),%1\n\t"
     "jne	1b\n"
     "2:\n\t"
     "subl	$1,%3\n\t"
     "jc	3f\n\t"
     "movb	(%2),%b0\n\t"
     "leal	1(%2),%2\n\t"
     "movb	%b0,(%1)\n\t"
     "leal	1(%1),%1\n\t"
     "testb	%b0,%b0\n\t"
     "jne	2b\n\t"
     "decl	%1\n"
     "3:\n\t"
     "movb	$0,(%1)"
     : "=&q" (__dummy), "=&r" (__tmp), "=&r" (__src), "=&r" (__n)
     : "1" (__tmp), "2" (__src), "3" (__n)
     : "memory", "cc");
#endif
# 1114 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
  return __dest;
}


/* Compare S1 and S2.  */
# define _HAVE_STRING_ARCH_strcmp 1
# define strcmp(s1, s2) \
  (__extension__ (__builtin_constant_p (s1) && __builtin_constant_p (s2)      \
		  && (sizeof ((s1)[0]) != 1 || strlen (s1) >= 4)	      \
		  && (sizeof ((s2)[0]) != 1 || strlen (s2) >= 4)	      \
		  ? memcmp ((const char *) (s1), (const char *) (s2),	      \
			    (strlen (s1) < strlen (s2)			      \
			     ? strlen (s1) : strlen (s2)) + 1)		      \
		  : (__builtin_constant_p (s1) && sizeof ((s1)[0]) == 1	      \
		     && sizeof ((s2)[0]) == 1 && strlen (s1) < 4	      \
		     ? (__builtin_constant_p (s2) && sizeof ((s2)[0]) == 1    \
			? __strcmp_cc ((const unsigned char *) (s1),	      \
				       (const unsigned char *) (s2),	      \
				       strlen (s1))			      \
			: __strcmp_cg ((const unsigned char *) (s1),	      \
				       (const unsigned char *) (s2),	      \
				       strlen (s1)))			      \
		     : (__builtin_constant_p (s2) && sizeof ((s1)[0]) == 1    \
			&& sizeof ((s2)[0]) == 1 && strlen (s2) < 4	      \
			? (__builtin_constant_p (s1)			      \
			   ? __strcmp_cc ((const unsigned char *) (s1),	      \
					  (const unsigned char *) (s2),	      \
					  strlen (s2))			      \
			   : __strcmp_gc ((const unsigned char *) (s1),	      \
					  (const unsigned char *) (s2),	      \
					  strlen (s2)))			      \
			: __strcmp_gg ((s1), (s2))))))

# define __strcmp_cc(s1, s2, l) \
  (__extension__ ({ register int __result = (s1)[0] - (s2)[0];		      \
		    if (l > 0 && __result == 0)				      \
		      {							      \
			__result = (s1)[1] - (s2)[1];			      \
			if (l > 1 && __result == 0)			      \
			  {						      \
			    __result = (s1)[2] - (s2)[2];		      \
			    if (l > 2 && __result == 0)			      \
			      __result = (s1)[3] - (s2)[3];		      \
			  }						      \
		      }							      \
		    __result; }))

# define __strcmp_cg(s1, s2, l1) \
  (__extension__ ({ const unsigned char *__s2 = (s2);			      \
		    register int __result = (s1)[0] - __s2[0];		      \
		    if (l1 > 0 && __result == 0)			      \
		      {							      \
			__result = (s1)[1] - __s2[1];			      \
			if (l1 > 1 && __result == 0)			      \
			  {						      \
			    __result = (s1)[2] - __s2[2];		      \
			    if (l1 > 2 && __result == 0)		      \
			      __result = (s1)[3] - __s2[3];		      \
			  }						      \
		      }							      \
		    __result; }))

# define __strcmp_gc(s1, s2, l2) \
  (__extension__ ({ const unsigned char *__s1 = (s1);			      \
		    register int __result = __s1[0] - (s2)[0];		      \
		    if (l2 > 0 && __result == 0)			      \
		      {							      \
			__result = __s1[1] - (s2)[1];			      \
			if (l2 > 1 && __result == 0)			      \
			  {						      \
			    __result = __s1[2] - (s2)[2];		      \
			    if (l2 > 2 && __result == 0)		      \
			      __result = __s1[3] - (s2)[3];		      \
			  }						      \
		      }							      \
		    __result; }))

__STRING_INLINE int __strcmp_gg (const char *__s1, const char *__s2);

__STRING_INLINE int
__strcmp_gg (const char *__s1, const char *__s2)
{
  register int __res;
  __asm__ __volatile__
    ("1:\n\t"
     "movb	(%1),%b0\n\t"
     "leal	1(%1),%1\n\t"
     "cmpb	%b0,(%2)\n\t"
     "jne	2f\n\t"
     "leal	1(%2),%2\n\t"
     "testb	%b0,%b0\n\t"
     "jne	1b\n\t"
     "xorl	%0,%0\n\t"
     "jmp	3f\n"
     "2:\n\t"
     "movl	$1,%0\n\t"
     "jb	3f\n\t"
     "negl	%0\n"
     "3:"
     : "=q" (__res), "=&r" (__s1), "=&r" (__s2)
     : "1" (__s1), "2" (__s2),
       "m" ( *(struct { char __x[0xfffffff]; } *)__s1),
       "m" ( *(struct { char __x[0xfffffff]; } *)__s2)
     : "cc");
  return __res;
}


/* Compare N characters of S1 and S2.  */
# define _HAVE_STRING_ARCH_strncmp 1
# define strncmp(s1, s2, n) \
  (__extension__ (__builtin_constant_p (s1) && strlen (s1) < ((size_t) (n))   \
		  ? strcmp ((s1), (s2))					      \
		  : (__builtin_constant_p (s2) && strlen (s2) < ((size_t) (n))\
		     ? strcmp ((s1), (s2))				      \
		     : __strncmp_g ((s1), (s2), (n)))))

__STRING_INLINE int __strncmp_g (const char *__s1, const char *__s2,
				 size_t __n);

__STRING_INLINE int
__strncmp_g (const char *__s1, const char *__s2, size_t __n)
{
  register int __res;
  __asm__ __volatile__
    ("1:\n\t"
     "subl	$1,%3\n\t"
     "jc	2f\n\t"
     "movb	(%1),%b0\n\t"
     "incl	%1\n\t"
     "cmpb	%b0,(%2)\n\t"
     "jne	3f\n\t"
     "incl	%2\n\t"
     "testb	%b0,%b0\n\t"
     "jne	1b\n"
     "2:\n\t"
     "xorl	%0,%0\n\t"
     "jmp	4f\n"
     "3:\n\t"
     "movl	$1,%0\n\t"
     "jb	4f\n\t"
     "negl	%0\n"
     "4:"
     : "=q" (__res), "=&r" (__s1), "=&r" (__s2), "=&r" (__n)
     : "1"  (__s1), "2"  (__s2),  "3" (__n),
       "m" ( *(struct { __extension__ char __x[__n]; } *)__s1),
       "m" ( *(struct { __extension__ char __x[__n]; } *)__s2)
     : "cc");
  return __res;
}


/* Find the first occurrence of C in S.  */
# define _HAVE_STRING_ARCH_strchr 1
# define _USE_STRING_ARCH_strchr 1
# define strchr(s, c) \
  (__extension__ (__builtin_constant_p (c)				      \
		  ? ((c) == '\0'					      \
		     ? (char *) __rawmemchr ((s), (c))			      \
		     : __strchr_c ((s), ((c) & 0xff) << 8))		      \
		  : __strchr_g ((s), (c))))

__STRING_INLINE char *__strchr_c (const char *__s, int __c);

__STRING_INLINE char *
__strchr_c (const char *__s, int __c)
{
  register unsigned long int __d0;
  register char *__res;
  __asm__ __volatile__
    ("1:\n\t"
     "movb	(%0),%%al\n\t"
     "cmpb	%%ah,%%al\n\t"
     "je	2f\n\t"
     "leal	1(%0),%0\n\t"
     "testb	%%al,%%al\n\t"
     "jne	1b\n\t"
     "xorl	%0,%0\n"
     "2:"
     : "=r" (__res), "=&a" (__d0)
     : "0" (__s), "1" (__c),
       "m" ( *(struct { char __x[0xfffffff]; } *)__s)
     : "cc");
  return __res;
}

__STRING_INLINE char *__strchr_g (const char *__s, int __c);

__STRING_INLINE char *
__strchr_g (const char *__s, int __c)
{
  register unsigned long int __d0;
  register char *__res;
  __asm__ __volatile__
    ("movb	%%al,%%ah\n"
     "1:\n\t"
     "movb	(%0),%%al\n\t"
     "cmpb	%%ah,%%al\n\t"
     "je	2f\n\t"
     "leal	1(%0),%0\n\t"
     "testb	%%al,%%al\n\t"
     "jne	1b\n\t"
     "xorl	%0,%0\n"
     "2:"
     : "=r" (__res), "=&a" (__d0)
     : "0" (__s), "1" (__c),
       "m" ( *(struct { char __x[0xfffffff]; } *)__s)
     : "cc");
  return __res;
}


/* Find the first occurrence of C in S or the final NUL byte.  */
# define _HAVE_STRING_ARCH_strchrnul 1
# define __strchrnul(s, c) \
  (__extension__ (__builtin_constant_p (c)				      \
		  ? ((c) == '\0'					      \
		     ? (char *) __rawmemchr ((s), c)			      \
		     : __strchrnul_c ((s), ((c) & 0xff) << 8))		      \
		  : __strchrnul_g ((s), c)))

__STRING_INLINE char *__strchrnul_c (const char *__s, int __c);

__STRING_INLINE char *
__strchrnul_c (const char *__s, int __c)
{
  register unsigned long int __d0;
  register char *__res;
  __asm__ __volatile__
    ("1:\n\t"
     "movb	(%0),%%al\n\t"
     "cmpb	%%ah,%%al\n\t"
     "je	2f\n\t"
     "leal	1(%0),%0\n\t"
     "testb	%%al,%%al\n\t"
     "jne	1b\n\t"
     "decl	%0\n"
     "2:"
     : "=r" (__res), "=&a" (__d0)
     : "0" (__s), "1" (__c),
       "m" ( *(struct { char __x[0xfffffff]; } *)__s)
     : "cc");
  return __res;
}

__STRING_INLINE char *__strchrnul_g (const char *__s, int __c);

__STRING_INLINE char *
__strchrnul_g (const char *__s, int __c)
{
  register unsigned long int __d0;
  register char *__res;
  __asm__ __volatile__
    ("movb	%%al,%%ah\n"
     "1:\n\t"
     "movb	(%0),%%al\n\t"
     "cmpb	%%ah,%%al\n\t"
     "je	2f\n\t"
     "leal	1(%0),%0\n\t"
     "testb	%%al,%%al\n\t"
     "jne	1b\n\t"
     "decl	%0\n"
     "2:"
     : "=r" (__res), "=&a" (__d0)
     : "0" (__s), "1" (__c),
       "m" ( *(struct { char __x[0xfffffff]; } *)__s)
     : "cc");
  return __res;
}
# ifdef __USE_GNU
#  define strchrnul(s, c) __strchrnul ((s), (c))
# endif
# 1386 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4


# if defined __USE_MISC || defined __USE_XOPEN_EXTENDED
/* Find the first occurrence of C in S.  This is the BSD name.  */
#  define _HAVE_STRING_ARCH_index 1
#  define index(s, c) \
  (__extension__ (__builtin_constant_p (c)				      \
		  ? __strchr_c ((s), ((c) & 0xff) << 8)			      \
		  : __strchr_g ((s), (c))))
# endif
# 1396 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4


/* Find the last occurrence of C in S.  */
# define _HAVE_STRING_ARCH_strrchr 1
# define strrchr(s, c) \
  (__extension__ (__builtin_constant_p (c)				      \
		  ? __strrchr_c ((s), ((c) & 0xff) << 8)		      \
		  : __strrchr_g ((s), (c))))

# ifdef __i686__
__STRING_INLINE char *__strrchr_c (const char *__s, int __c);

__STRING_INLINE char *
__strrchr_c (const char *__s, int __c)
{
  register unsigned long int __d0, __d1;
  register char *__res;
  __asm__ __volatile__
    ("cld\n"
     "1:\n\t"
     "lodsb\n\t"
     "cmpb	%h2,%b2\n\t"
     "cmove	%1,%0\n\t"
     "testb	%b2,%b2\n\t"
     "jne 1b"
     : "=d" (__res), "=&S" (__d0), "=&a" (__d1)
     : "0" (1), "1" (__s), "2" (__c),
       "m" ( *(struct { char __x[0xfffffff]; } *)__s)
     : "cc");
  return __res - 1;
}

__STRING_INLINE char *__strrchr_g (const char *__s, int __c);

__STRING_INLINE char *
__strrchr_g (const char *__s, int __c)
{
  register unsigned long int __d0, __d1;
  register char *__res;
  __asm__ __volatile__
    ("movb	%b2,%h2\n"
     "cld\n\t"
     "1:\n\t"
     "lodsb\n\t"
     "cmpb	%h2,%b2\n\t"
     "cmove	%1,%0\n\t"
     "testb	%b2,%b2\n\t"
     "jne 1b"
     : "=d" (__res), "=&S" (__d0), "=&a" (__d1)
     : "0" (1), "1" (__s), "2" (__c),
       "m" ( *(struct { char __x[0xfffffff]; } *)__s)
     : "cc");
  return __res - 1;
}
# else
# 1451 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
__STRING_INLINE char *__strrchr_c (const char *__s, int __c);

__STRING_INLINE char *
__strrchr_c (const char *__s, int __c)
{
  register unsigned long int __d0, __d1;
  register char *__res;
  __asm__ __volatile__
    ("cld\n"
     "1:\n\t"
     "lodsb\n\t"
     "cmpb	%%ah,%%al\n\t"
     "jne	2f\n\t"
     "leal	-1(%%esi),%0\n"
     "2:\n\t"
     "testb	%%al,%%al\n\t"
     "jne 1b"
     : "=d" (__res), "=&S" (__d0), "=&a" (__d1)
     : "0" (0), "1" (__s), "2" (__c),
       "m" ( *(struct { char __x[0xfffffff]; } *)__s)
     : "cc");
  return __res;
}

__STRING_INLINE char *__strrchr_g (const char *__s, int __c);

__STRING_INLINE char *
__strrchr_g (const char *__s, int __c)
{
  register unsigned long int __d0, __d1;
  register char *__res;
  __asm__ __volatile__
    ("movb	%%al,%%ah\n"
     "cld\n\t"
     "1:\n\t"
     "lodsb\n\t"
     "cmpb	%%ah,%%al\n\t"
     "jne	2f\n\t"
     "leal	-1(%%esi),%0\n"
     "2:\n\t"
     "testb	%%al,%%al\n\t"
     "jne 1b"
     : "=r" (__res), "=&S" (__d0), "=&a" (__d1)
     : "0" (0), "1" (__s), "2" (__c),
       "m" ( *(struct { char __x[0xfffffff]; } *)__s)
     : "cc");
  return __res;
}
# endif
# 1500 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4


# if defined __USE_MISC || defined __USE_XOPEN_EXTENDED
/* Find the last occurrence of C in S.  This is the BSD name.  */
#  define _HAVE_STRING_ARCH_rindex 1
#  define rindex(s, c) \
  (__extension__ (__builtin_constant_p (c)				      \
		  ? __strrchr_c ((s), ((c) & 0xff) << 8)		      \
		  : __strrchr_g ((s), (c))))
# endif
# 1510 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4


/* Return the length of the initial segment of S which
   consists entirely of characters not in REJECT.  */
# define _HAVE_STRING_ARCH_strcspn 1
# define strcspn(s, reject) \
  (__extension__ (__builtin_constant_p (reject) && sizeof ((reject)[0]) == 1  \
		  ? ((reject)[0] == '\0'				      \
		     ? strlen (s)					      \
		     : ((reject)[1] == '\0'				      \
			? __strcspn_c1 ((s), (((reject)[0] << 8) & 0xff00))   \
			: __strcspn_cg ((s), (reject), strlen (reject))))     \
		  : __strcspn_g ((s), (reject))))

__STRING_INLINE size_t __strcspn_c1 (const char *__s, int __reject);

# ifndef _FORCE_INLINES
__STRING_INLINE size_t
__strcspn_c1 (const char *__s, int __reject)
{
  register unsigned long int __d0;
  register char *__res;
  __asm__ __volatile__
    ("1:\n\t"
     "movb	(%0),%%al\n\t"
     "leal	1(%0),%0\n\t"
     "cmpb	%%ah,%%al\n\t"
     "je	2f\n\t"
     "testb	%%al,%%al\n\t"
     "jne	1b\n"
     "2:"
     : "=r" (__res), "=&a" (__d0)
     : "0" (__s), "1" (__reject),
       "m" ( *(struct { char __x[0xfffffff]; } *)__s)
     : "cc");
  return (__res - 1) - __s;
}
# endif
# 1548 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4

__STRING_INLINE size_t __strcspn_cg (const char *__s, const char __reject[],
				     size_t __reject_len);

__STRING_INLINE size_t
__strcspn_cg (const char *__s, const char __reject[], size_t __reject_len)
{
  register unsigned long int __d0, __d1, __d2;
  register const char *__res;
  __asm__ __volatile__
    ("cld\n"
     "1:\n\t"
     "lodsb\n\t"
     "testb	%%al,%%al\n\t"
     "je	2f\n\t"
     "movl	%5,%%edi\n\t"
     "movl	%6,%%ecx\n\t"
     "repne; scasb\n\t"
     "jne	1b\n"
     "2:"
     : "=S" (__res), "=&a" (__d0), "=&c" (__d1), "=&D" (__d2)
     : "0" (__s), "d" (__reject), "g" (__reject_len)
     : "memory", "cc");
  return (__res - 1) - __s;
}

__STRING_INLINE size_t __strcspn_g (const char *__s, const char *__reject);
# ifdef __PIC__

__STRING_INLINE size_t
__strcspn_g (const char *__s, const char *__reject)
{
  register unsigned long int __d0, __d1, __d2;
  register const char *__res;
  __asm__ __volatile__
    ("pushl	%%ebx\n\t"
     "movl	%4,%%edi\n\t"
     "cld\n\t"
     "repne; scasb\n\t"
     "notl	%%ecx\n\t"
     "leal	-1(%%ecx),%%ebx\n"
     "1:\n\t"
     "lodsb\n\t"
     "testb	%%al,%%al\n\t"
     "je	2f\n\t"
     "movl	%4,%%edi\n\t"
     "movl	%%ebx,%%ecx\n\t"
     "repne; scasb\n\t"
     "jne	1b\n"
     "2:\n\t"
     "popl	%%ebx"
     : "=S" (__res), "=&a" (__d0), "=&c" (__d1), "=&D" (__d2)
     : "r" (__reject), "0" (__s), "1" (0), "2" (0xffffffff)
     : "memory", "cc");
  return (__res - 1) - __s;
}
# else
# 1605 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
__STRING_INLINE size_t
__strcspn_g (const char *__s, const char *__reject)
{
  register unsigned long int __d0, __d1, __d2, __d3;
  register const char *__res;
  __asm__ __volatile__
    ("cld\n\t"
     "repne; scasb\n\t"
     "notl	%%ecx\n\t"
     "leal	-1(%%ecx),%%edx\n"
     "1:\n\t"
     "lodsb\n\t"
     "testb	%%al,%%al\n\t"
     "je	2f\n\t"
     "movl	%%ebx,%%edi\n\t"
     "movl	%%edx,%%ecx\n\t"
     "repne; scasb\n\t"
     "jne	1b\n"
     "2:"
     : "=S" (__res), "=&a" (__d0), "=&c" (__d1), "=&D" (__d2), "=&d" (__d3)
     : "0" (__s), "1" (0), "2" (0xffffffff), "3" (__reject), "b" (__reject)
     /* Clobber memory, otherwise GCC cannot handle this.  */
     : "memory", "cc");
  return (__res - 1) - __s;
}
# endif
# 1631 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4


/* Return the length of the initial segment of S which
   consists entirely of characters in ACCEPT.  */
# define _HAVE_STRING_ARCH_strspn 1
# define strspn(s, accept) \
  (__extension__ (__builtin_constant_p (accept) && sizeof ((accept)[0]) == 1  \
		  ? ((accept)[0] == '\0'				      \
		     ? ((void) (s), 0)					      \
		     : ((accept)[1] == '\0'				      \
			? __strspn_c1 ((s), (((accept)[0] << 8 ) & 0xff00))   \
			: __strspn_cg ((s), (accept), strlen (accept))))      \
		  : __strspn_g ((s), (accept))))

# ifndef _FORCE_INLINES
__STRING_INLINE size_t __strspn_c1 (const char *__s, int __accept);

__STRING_INLINE size_t
__strspn_c1 (const char *__s, int __accept)
{
  register unsigned long int __d0;
  register char *__res;
  /* Please note that __accept never can be '\0'.  */
  __asm__ __volatile__
    ("1:\n\t"
     "movb	(%0),%b1\n\t"
     "leal	1(%0),%0\n\t"
     "cmpb	%h1,%b1\n\t"
     "je	1b"
     : "=r" (__res), "=&q" (__d0)
     : "0" (__s), "1" (__accept),
       "m" ( *(struct { char __x[0xfffffff]; } *)__s)
     : "cc");
  return (__res - 1) - __s;
}
# endif
# 1667 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4

__STRING_INLINE size_t __strspn_cg (const char *__s, const char __accept[],
				    size_t __accept_len);

__STRING_INLINE size_t
__strspn_cg (const char *__s, const char __accept[], size_t __accept_len)
{
  register unsigned long int __d0, __d1, __d2;
  register const char *__res;
  __asm__ __volatile__
    ("cld\n"
     "1:\n\t"
     "lodsb\n\t"
     "testb	%%al,%%al\n\t"
     "je	2f\n\t"
     "movl	%5,%%edi\n\t"
     "movl	%6,%%ecx\n\t"
     "repne; scasb\n\t"
     "je	1b\n"
     "2:"
     : "=S" (__res), "=&a" (__d0), "=&c" (__d1), "=&D" (__d2)
     : "0" (__s), "g" (__accept), "g" (__accept_len),
       /* Since we do not know how large the memory we access it, use a
	  really large amount.  */
       "m" ( *(struct { char __x[0xfffffff]; } *)__s),
       "m" ( *(struct { __extension__ char __x[__accept_len]; } *)__accept)
     : "cc");
  return (__res - 1) - __s;
}

__STRING_INLINE size_t __strspn_g (const char *__s, const char *__accept);
# ifdef __PIC__

__STRING_INLINE size_t
__strspn_g (const char *__s, const char *__accept)
{
  register unsigned long int __d0, __d1, __d2;
  register const char *__res;
  __asm__ __volatile__
    ("pushl	%%ebx\n\t"
     "cld\n\t"
     "repne; scasb\n\t"
     "notl	%%ecx\n\t"
     "leal	-1(%%ecx),%%ebx\n"
     "1:\n\t"
     "lodsb\n\t"
     "testb	%%al,%%al\n\t"
     "je	2f\n\t"
     "movl	%%edx,%%edi\n\t"
     "movl	%%ebx,%%ecx\n\t"
     "repne; scasb\n\t"
     "je	1b\n"
     "2:\n\t"
     "popl	%%ebx"
     : "=S" (__res), "=&a" (__d0), "=&c" (__d1), "=&D" (__d2)
     : "d" (__accept), "0" (__s), "1" (0), "2" (0xffffffff), "3" (__accept)
     : "memory", "cc");
  return (__res - 1) - __s;
}
# else
# 1727 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
__STRING_INLINE size_t
__strspn_g (const char *__s, const char *__accept)
{
  register unsigned long int __d0, __d1, __d2, __d3;
  register const char *__res;
  __asm__ __volatile__
    ("cld\n\t"
     "repne; scasb\n\t"
     "notl	%%ecx\n\t"
     "leal	-1(%%ecx),%%edx\n"
     "1:\n\t"
     "lodsb\n\t"
     "testb	%%al,%%al\n\t"
     "je	2f\n\t"
     "movl	%%ebx,%%edi\n\t"
     "movl	%%edx,%%ecx\n\t"
     "repne; scasb\n\t"
     "je	1b\n"
     "2:"
     : "=S" (__res), "=&a" (__d0), "=&c" (__d1), "=&D" (__d2), "=&d" (__d3)
     : "0" (__s), "1" (0), "2" (0xffffffff), "3" (__accept), "b" (__accept)
     : "memory", "cc");
  return (__res - 1) - __s;
}
# endif
# 1752 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4


/* Find the first occurrence in S of any character in ACCEPT.  */
# define _HAVE_STRING_ARCH_strpbrk 1
# define strpbrk(s, accept) \
  (__extension__ (__builtin_constant_p (accept) && sizeof ((accept)[0]) == 1  \
		  ? ((accept)[0] == '\0'				      \
		     ? ((void) (s), (char *) 0)				      \
		     : ((accept)[1] == '\0'				      \
			? strchr ((s), (accept)[0])			      \
			: __strpbrk_cg ((s), (accept), strlen (accept))))     \
		  : __strpbrk_g ((s), (accept))))

__STRING_INLINE char *__strpbrk_cg (const char *__s, const char __accept[],
				    size_t __accept_len);

__STRING_INLINE char *
__strpbrk_cg (const char *__s, const char __accept[], size_t __accept_len)
{
  register unsigned long int __d0, __d1, __d2;
  register char *__res;
  __asm__ __volatile__
    ("cld\n"
     "1:\n\t"
     "lodsb\n\t"
     "testb	%%al,%%al\n\t"
     "je	2f\n\t"
     "movl	%5,%%edi\n\t"
     "movl	%6,%%ecx\n\t"
     "repne; scasb\n\t"
     "jne	1b\n\t"
     "decl	%0\n\t"
     "jmp	3f\n"
     "2:\n\t"
     "xorl	%0,%0\n"
     "3:"
     : "=S" (__res), "=&a" (__d0), "=&c" (__d1), "=&D" (__d2)
     : "0" (__s), "d" (__accept), "g" (__accept_len)
     : "memory", "cc");
  return __res;
}

__STRING_INLINE char *__strpbrk_g (const char *__s, const char *__accept);
# ifdef __PIC__

__STRING_INLINE char *
__strpbrk_g (const char *__s, const char *__accept)
{
  register unsigned long int __d0, __d1, __d2;
  register char *__res;
  __asm__ __volatile__
    ("pushl	%%ebx\n\t"
     "movl	%%edx,%%edi\n\t"
     "cld\n\t"
     "repne; scasb\n\t"
     "notl	%%ecx\n\t"
     "leal	-1(%%ecx),%%ebx\n"
     "1:\n\t"
     "lodsb\n\t"
     "testb	%%al,%%al\n\t"
     "je	2f\n\t"
     "movl	%%edx,%%edi\n\t"
     "movl	%%ebx,%%ecx\n\t"
     "repne; scasb\n\t"
     "jne	1b\n\t"
     "decl	%0\n\t"
     "jmp	3f\n"
     "2:\n\t"
     "xorl	%0,%0\n"
     "3:\n\t"
     "popl	%%ebx"
     : "=S" (__res), "=&a" (__d0), "=&c" (__d1), "=&D" (__d2)
     : "d" (__accept), "0" (__s), "1" (0), "2" (0xffffffff)
     : "memory", "cc");
  return __res;
}
# else
# 1829 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
__STRING_INLINE char *
__strpbrk_g (const char *__s, const char *__accept)
{
  register unsigned long int __d0, __d1, __d2, __d3;
  register char *__res;
  __asm__ __volatile__
    ("movl	%%ebx,%%edi\n\t"
     "cld\n\t"
     "repne; scasb\n\t"
     "notl	%%ecx\n\t"
     "leal	-1(%%ecx),%%edx\n"
     "1:\n\t"
     "lodsb\n\t"
     "testb	%%al,%%al\n\t"
     "je	2f\n\t"
     "movl	%%ebx,%%edi\n\t"
     "movl	%%edx,%%ecx\n\t"
     "repne; scasb\n\t"
     "jne	1b\n\t"
     "decl	%0\n\t"
     "jmp	3f\n"
     "2:\n\t"
     "xorl	%0,%0\n"
     "3:"
     : "=S" (__res), "=&a" (__d0), "=&c" (__d1), "=&d" (__d2), "=&D" (__d3)
     : "0" (__s), "1" (0), "2" (0xffffffff), "b" (__accept)
     : "memory", "cc");
  return __res;
}
# endif
# 1859 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4


/* Find the first occurrence of NEEDLE in HAYSTACK.  */
# define _HAVE_STRING_ARCH_strstr 1
# define strstr(haystack, needle) \
  (__extension__ (__builtin_constant_p (needle) && sizeof ((needle)[0]) == 1  \
		  ? ((needle)[0] == '\0'				      \
		     ? (haystack)					      \
		     : ((needle)[1] == '\0'				      \
			? strchr ((haystack), (needle)[0])		      \
			: __strstr_cg ((haystack), (needle),		      \
				       strlen (needle))))		      \
		  : __strstr_g ((haystack), (needle))))

/* Please note that this function need not handle NEEDLEs with a
   length shorter than two.  */
__STRING_INLINE char *__strstr_cg (const char *__haystack,
				   const char __needle[],
				   size_t __needle_len);

__STRING_INLINE char *
__strstr_cg (const char *__haystack, const char __needle[],
	     size_t __needle_len)
{
  register unsigned long int __d0, __d1, __d2;
  register char *__res;
  __asm__ __volatile__
    ("cld\n" \
     "1:\n\t"
     "movl	%6,%%edi\n\t"
     "movl	%5,%%eax\n\t"
     "movl	%4,%%ecx\n\t"
     "repe; cmpsb\n\t"
     "je	2f\n\t"
     "cmpb	$0,-1(%%esi)\n\t"
     "leal	1(%%eax),%5\n\t"
     "jne	1b\n\t"
     "xorl	%%eax,%%eax\n"
     "2:"
     : "=&a" (__res), "=&S" (__d0), "=&D" (__d1), "=&c" (__d2)
     : "g" (__needle_len), "1" (__haystack), "d" (__needle)
     : "memory", "cc");
  return __res;
}

__STRING_INLINE char *__strstr_g (const char *__haystack,
				  const char *__needle);
# ifdef __PIC__

__STRING_INLINE char *
__strstr_g (const char *__haystack, const char *__needle)
{
  register unsigned long int __d0, __d1, __d2;
  register char *__res;
  __asm__ __volatile__
    ("cld\n\t"
     "repne; scasb\n\t"
     "notl	%%ecx\n\t"
     "pushl	%%ebx\n\t"
     "decl	%%ecx\n\t"	/* NOTE! This also sets Z if searchstring='' */
     "movl	%%ecx,%%ebx\n"
     "1:\n\t"
     "movl	%%edx,%%edi\n\t"
     "movl	%%esi,%%eax\n\t"
     "movl	%%ebx,%%ecx\n\t"
     "repe; cmpsb\n\t"
     "je	2f\n\t"		/* also works for empty string, see above */
     "cmpb	$0,-1(%%esi)\n\t"
     "leal	1(%%eax),%%esi\n\t"
     "jne	1b\n\t"
     "xorl	%%eax,%%eax\n"
     "2:\n\t"
     "popl	%%ebx"
     : "=&a" (__res), "=&c" (__d0), "=&S" (__d1), "=&D" (__d2)
     : "0" (0), "1" (0xffffffff), "2" (__haystack), "3" (__needle),
       "d" (__needle)
     : "memory", "cc");
  return __res;
}
# else
# 1939 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
__STRING_INLINE char *
__strstr_g (const char *__haystack, const char *__needle)
{
  register unsigned long int __d0, __d1, __d2, __d3;
  register char *__res;
  __asm__ __volatile__
    ("cld\n\t"
     "repne; scasb\n\t"
     "notl	%%ecx\n\t"
     "decl	%%ecx\n\t"	/* NOTE! This also sets Z if searchstring='' */
     "movl	%%ecx,%%edx\n"
     "1:\n\t"
     "movl	%%ebx,%%edi\n\t"
     "movl	%%esi,%%eax\n\t"
     "movl	%%edx,%%ecx\n\t"
     "repe; cmpsb\n\t"
     "je	2f\n\t"		/* also works for empty string, see above */
     "cmpb	$0,-1(%%esi)\n\t"
     "leal	1(%%eax),%%esi\n\t"
     "jne	1b\n\t"
     "xorl	%%eax,%%eax\n"
     "2:"
     : "=&a" (__res), "=&c" (__d0), "=&S" (__d1), "=&D" (__d2), "=&d" (__d3)
     : "0" (0), "1" (0xffffffff), "2" (__haystack), "3" (__needle),
       "b" (__needle)
     : "memory", "cc");
  return __res;
}
# endif
# 1968 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4


/* Bit find functions.  We define only the i686 version since for the other
   processors gcc generates good code.  */
# if defined __USE_MISC || defined __USE_XOPEN_EXTENDED
#  ifdef __i686__
#   define _HAVE_STRING_ARCH_ffs 1
#   define ffs(word) (__builtin_constant_p (word)			      \
		      ? __builtin_ffs (word)				      \
		      : ({ int __cnt, __tmp;				      \
			   __asm__ __volatile__				      \
			     ("bsfl %2,%0\n\t"				      \
			      "cmovel %1,%0"				      \
			      : "=&r" (__cnt), "=r" (__tmp)		      \
			      : "rm" (word), "1" (-1));			      \
			   __cnt + 1; }))

#   ifndef ffsl
#    define ffsl(word) ffs(word)
#   endif
# 1988 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
#  endif /* i686 */
# 1989 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
# endif	/* Misc || X/Open */
# 1990 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4

# ifndef _FORCE_INLINES
#  undef __STRING_INLINE
# endif
# 1994 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4

# endif	/* use string inlines && GNU CC */
# 1996 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4

#endif
# 1998 "/usr/include/x86_64-linux-gnu/bits/string.h" 3 4
# 628 "/usr/include/string.h" 2 3 4

/* These are generic optimizations which do not add too much inline code.  */
#if 0 /* expanded by -frewrite-includes */
#  include <bits/string2.h>
#endif /* expanded by -frewrite-includes */
# 630 "/usr/include/string.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/string2.h" 1 3 4
/* Machine-independant string function optimizations.
   Copyright (C) 1997-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1997.

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

#ifndef _STRING_H
# error "Never use <bits/string2.h> directly; include <string.h> instead."
#endif
# 23 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4

#ifndef __NO_STRING_INLINES

/* Unlike the definitions in the header <bits/string.h> the
   definitions contained here are not optimized down to assembler
   level.  Those optimizations are not always a good idea since this
   means the code size increases a lot.  Instead the definitions here
   optimize some functions in a way which do not dramatically
   increase the code size and which do not use assembler.  The main
   trick is to use GCC's `__builtin_constant_p' function.

   Every function XXX which has a defined version in
   <bits/string.h> must be accompanied by a symbol _HAVE_STRING_ARCH_XXX
   to make sure we don't get redefinitions.

   We must use here macros instead of inline functions since the
   trick won't work with the latter.  */

#ifndef __STRING_INLINE
# ifdef __cplusplus
#  define __STRING_INLINE inline
# else
# 45 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#  define __STRING_INLINE __extern_inline
# endif
# 47 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#endif
# 48 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4

#if _STRING_INLINE_unaligned
/* If we can do unaligned memory accesses we must know the endianess.  */
#if 0 /* expanded by -frewrite-includes */
# include <endian.h>
#endif /* expanded by -frewrite-includes */
# 51 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
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
# 52 "/usr/include/x86_64-linux-gnu/bits/string2.h" 2 3 4
#if 0 /* expanded by -frewrite-includes */
# include <bits/types.h>
#endif /* expanded by -frewrite-includes */
# 52 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
# 53 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4

# if __BYTE_ORDER == __LITTLE_ENDIAN
#  define __STRING2_SMALL_GET16(src, idx) \
     (((const unsigned char *) (const char *) (src))[idx + 1] << 8	      \
      | ((const unsigned char *) (const char *) (src))[idx])
#  define __STRING2_SMALL_GET32(src, idx) \
     (((((const unsigned char *) (const char *) (src))[idx + 3] << 8	      \
	| ((const unsigned char *) (const char *) (src))[idx + 2]) << 8	      \
       | ((const unsigned char *) (const char *) (src))[idx + 1]) << 8	      \
      | ((const unsigned char *) (const char *) (src))[idx])
# else
# 64 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#  define __STRING2_SMALL_GET16(src, idx) \
     (((const unsigned char *) (const char *) (src))[idx] << 8		      \
      | ((const unsigned char *) (const char *) (src))[idx + 1])
#  define __STRING2_SMALL_GET32(src, idx) \
     (((((const unsigned char *) (const char *) (src))[idx] << 8	      \
	| ((const unsigned char *) (const char *) (src))[idx + 1]) << 8	      \
       | ((const unsigned char *) (const char *) (src))[idx + 2]) << 8	      \
      | ((const unsigned char *) (const char *) (src))[idx + 3])
# endif
# 73 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#else
# 74 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
/* These are a few types we need for the optimizations if we cannot
   use unaligned memory accesses.  */
# define __STRING2_COPY_TYPE(N) \
  typedef struct { unsigned char __arr[N]; }				      \
    __attribute__ ((__packed__)) __STRING2_COPY_ARR##N
__STRING2_COPY_TYPE (2);
__STRING2_COPY_TYPE (3);
__STRING2_COPY_TYPE (4);
__STRING2_COPY_TYPE (5);
__STRING2_COPY_TYPE (6);
__STRING2_COPY_TYPE (7);
__STRING2_COPY_TYPE (8);
# undef __STRING2_COPY_TYPE
#endif
# 88 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4

/* Dereferencing a pointer arg to run sizeof on it fails for the void
   pointer case, so we use this instead.
   Note that __x is evaluated twice. */
#define __string2_1bptr_p(__x) \
  ((size_t)(const void *)((__x) + 1) - (size_t)(const void *)(__x) == 1)

/* Set N bytes of S to C.  */
#if !defined _HAVE_STRING_ARCH_memset
# if !__GNUC_PREREQ (3, 0)
#  if _STRING_INLINE_unaligned
#   define memset(s, c, n) \
  (__extension__ (__builtin_constant_p (n) && (n) <= 16			      \
		  ? ((n) == 1						      \
		     ? __memset_1 (s, c)				      \
		     : __memset_gc (s, c, n))				      \
		  : (__builtin_constant_p (c) && (c) == '\0'		      \
		     ? ({ void *__s = (s); __bzero (__s, n); __s; })	      \
		     : memset (s, c, n))))

#   define __memset_1(s, c) ({ void *__s = (s);				      \
			    *((__uint8_t *) __s) = (__uint8_t) c; __s; })

#   define __memset_gc(s, c, n) \
  ({ void *__s = (s);							      \
     union {								      \
       unsigned int __ui;						      \
       unsigned short int __usi;					      \
       unsigned char __uc;						      \
     } *__u = __s;							      \
     __uint8_t __c = (__uint8_t) (c);					      \
									      \
     /* This `switch' statement will be removed at compile-time.  */	      \
     switch ((unsigned int) (n))					      \
       {								      \
       case 15:								      \
	 __u->__ui = __c * 0x01010101;					      \
	 __u = __extension__ ((void *) __u + 4);			      \
       case 11:								      \
	 __u->__ui = __c * 0x01010101;					      \
	 __u = __extension__ ((void *) __u + 4);			      \
       case 7:								      \
	 __u->__ui = __c * 0x01010101;					      \
	 __u = __extension__ ((void *) __u + 4);			      \
       case 3:								      \
	 __u->__usi = (unsigned short int) __c * 0x0101;		      \
	 __u = __extension__ ((void *) __u + 2);			      \
	 __u->__uc = (unsigned char) __c;				      \
	 break;								      \
									      \
       case 14:								      \
	 __u->__ui = __c * 0x01010101;					      \
	 __u = __extension__ ((void *) __u + 4);			      \
       case 10:								      \
	 __u->__ui = __c * 0x01010101;					      \
	 __u = __extension__ ((void *) __u + 4);			      \
       case 6:								      \
	 __u->__ui = __c * 0x01010101;					      \
	 __u = __extension__ ((void *) __u + 4);			      \
       case 2:								      \
	 __u->__usi = (unsigned short int) __c * 0x0101;		      \
	 break;								      \
									      \
       case 13:								      \
	 __u->__ui = __c * 0x01010101;					      \
	 __u = __extension__ ((void *) __u + 4);			      \
       case 9:								      \
	 __u->__ui = __c * 0x01010101;					      \
	 __u = __extension__ ((void *) __u + 4);			      \
       case 5:								      \
	 __u->__ui = __c * 0x01010101;					      \
	 __u = __extension__ ((void *) __u + 4);			      \
       case 1:								      \
	 __u->__uc = (unsigned char) __c;				      \
	 break;								      \
									      \
       case 16:								      \
	 __u->__ui = __c * 0x01010101;					      \
	 __u = __extension__ ((void *) __u + 4);			      \
       case 12:								      \
	 __u->__ui = __c * 0x01010101;					      \
	 __u = __extension__ ((void *) __u + 4);			      \
       case 8:								      \
	 __u->__ui = __c * 0x01010101;					      \
	 __u = __extension__ ((void *) __u + 4);			      \
       case 4:								      \
	 __u->__ui = __c * 0x01010101;					      \
       case 0:								      \
	 break;								      \
       }								      \
									      \
     __s; })
#  else
# 181 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#   define memset(s, c, n) \
  (__extension__ (__builtin_constant_p (c) && (c) == '\0'		      \
		  ? ({ void *__s = (s); __bzero (__s, n); __s; })	      \
		  : memset (s, c, n)))
#  endif
# 186 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
# endif
# 187 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4

/* GCC < 3.0 optimizes memset(s, 0, n) but not bzero(s, n).
   The optimization is broken before EGCS 1.1.
   GCC 3.0+ has __builtin_bzero as well, but at least till GCC 3.4
   if it decides to call the library function, it calls memset
   and not bzero.  */
# if __GNUC_PREREQ (2, 91)
#  define __bzero(s, n) __builtin_memset (s, '\0', n)
# endif
# 196 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4

#endif
# 198 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4


/* Copy N bytes from SRC to DEST, returning pointer to byte following the
   last copied.  */
#ifdef __USE_GNU
# if !defined _HAVE_STRING_ARCH_mempcpy || defined _FORCE_INLINES
#  ifndef _HAVE_STRING_ARCH_mempcpy
#   if __GNUC_PREREQ (3, 4)
#    define __mempcpy(dest, src, n) __builtin_mempcpy (dest, src, n)
#   elif __GNUC_PREREQ (3, 0)
# 208 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#    define __mempcpy(dest, src, n) \
  (__extension__ (__builtin_constant_p (src) && __builtin_constant_p (n)      \
		  && __string2_1bptr_p (src) && n <= 8			      \
		  ? __builtin_memcpy (dest, src, n) + (n)		      \
		  : __mempcpy (dest, src, n)))
#   else
# 214 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#    define __mempcpy(dest, src, n) \
  (__extension__ (__builtin_constant_p (src) && __builtin_constant_p (n)      \
		  && __string2_1bptr_p (src) && n <= 8			      \
		  ? __mempcpy_small (dest, __mempcpy_args (src), n)	      \
		  : __mempcpy (dest, src, n)))
#   endif
# 220 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
/* In glibc we use this function frequently but for namespace reasons
   we have to use the name `__mempcpy'.  */
#   define mempcpy(dest, src, n) __mempcpy (dest, src, n)
#  endif
# 224 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4

#  if !__GNUC_PREREQ (3, 0) || defined _FORCE_INLINES
#   if _STRING_INLINE_unaligned
#    ifndef _FORCE_INLINES
#     define __mempcpy_args(src) \
     ((const char *) (src))[0], ((const char *) (src))[2],		      \
     ((const char *) (src))[4], ((const char *) (src))[6],		      \
     __extension__ __STRING2_SMALL_GET16 (src, 0),			      \
     __extension__ __STRING2_SMALL_GET16 (src, 4),			      \
     __extension__ __STRING2_SMALL_GET32 (src, 0),			      \
     __extension__ __STRING2_SMALL_GET32 (src, 4)
#    endif
# 236 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
__STRING_INLINE void *__mempcpy_small (void *, char, char, char, char,
				       __uint16_t, __uint16_t, __uint32_t,
				       __uint32_t, size_t);
__STRING_INLINE void *
__mempcpy_small (void *__dest1,
		 char __src0_1, char __src2_1, char __src4_1, char __src6_1,
		 __uint16_t __src0_2, __uint16_t __src4_2,
		 __uint32_t __src0_4, __uint32_t __src4_4,
		 size_t __srclen)
{
  union {
    __uint32_t __ui;
    __uint16_t __usi;
    unsigned char __uc;
    unsigned char __c;
  } *__u = __dest1;
  switch ((unsigned int) __srclen)
    {
    case 1:
      __u->__c = __src0_1;
      __u = __extension__ ((void *) __u + 1);
      break;
    case 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((void *) __u + 2);
      break;
    case 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((void *) __u + 2);
      __u->__c = __src2_1;
      __u = __extension__ ((void *) __u + 1);
      break;
    case 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      break;
    case 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__c = __src4_1;
      __u = __extension__ ((void *) __u + 1);
      break;
    case 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((void *) __u + 2);
      break;
    case 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((void *) __u + 2);
      __u->__c = __src6_1;
      __u = __extension__ ((void *) __u + 1);
      break;
    case 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((void *) __u + 4);
      break;
    }
  return (void *) __u;
}
#   else
# 302 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#    ifndef _FORCE_INLINES
#     define __mempcpy_args(src) \
     ((const char *) (src))[0],						      \
     __extension__ ((__STRING2_COPY_ARR2)				      \
      { { ((const char *) (src))[0], ((const char *) (src))[1] } }),	      \
     __extension__ ((__STRING2_COPY_ARR3)				      \
      { { ((const char *) (src))[0], ((const char *) (src))[1],		      \
	  ((const char *) (src))[2] } }),				      \
     __extension__ ((__STRING2_COPY_ARR4)				      \
      { { ((const char *) (src))[0], ((const char *) (src))[1],		      \
	  ((const char *) (src))[2], ((const char *) (src))[3] } }),	      \
     __extension__ ((__STRING2_COPY_ARR5)				      \
      { { ((const char *) (src))[0], ((const char *) (src))[1],		      \
	  ((const char *) (src))[2], ((const char *) (src))[3],		      \
	  ((const char *) (src))[4] } }),				      \
     __extension__ ((__STRING2_COPY_ARR6)				      \
      { { ((const char *) (src))[0], ((const char *) (src))[1],		      \
	  ((const char *) (src))[2], ((const char *) (src))[3],		      \
	  ((const char *) (src))[4], ((const char *) (src))[5] } }),	      \
     __extension__ ((__STRING2_COPY_ARR7)				      \
      { { ((const char *) (src))[0], ((const char *) (src))[1],		      \
	  ((const char *) (src))[2], ((const char *) (src))[3],		      \
	  ((const char *) (src))[4], ((const char *) (src))[5],		      \
	  ((const char *) (src))[6] } }),				      \
     __extension__ ((__STRING2_COPY_ARR8)				      \
      { { ((const char *) (src))[0], ((const char *) (src))[1],		      \
	  ((const char *) (src))[2], ((const char *) (src))[3],		      \
	  ((const char *) (src))[4], ((const char *) (src))[5],		      \
	  ((const char *) (src))[6], ((const char *) (src))[7] } })
#    endif
# 332 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
__STRING_INLINE void *__mempcpy_small (void *, char, __STRING2_COPY_ARR2,
				       __STRING2_COPY_ARR3,
				       __STRING2_COPY_ARR4,
				       __STRING2_COPY_ARR5,
				       __STRING2_COPY_ARR6,
				       __STRING2_COPY_ARR7,
				       __STRING2_COPY_ARR8, size_t);
__STRING_INLINE void *
__mempcpy_small (void *__dest, char __src1,
		 __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		 __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		 __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		 __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  union {
    char __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = __dest;
  switch ((unsigned int) __srclen)
    {
    case 1:
      __u->__c = __src1;
      break;
    case 2:
      __extension__ __u->__sca2 = __src2;
      break;
    case 3:
      __extension__ __u->__sca3 = __src3;
      break;
    case 4:
      __extension__ __u->__sca4 = __src4;
      break;
    case 5:
      __extension__ __u->__sca5 = __src5;
      break;
    case 6:
      __extension__ __u->__sca6 = __src6;
      break;
    case 7:
      __extension__ __u->__sca7 = __src7;
      break;
    case 8:
      __extension__ __u->__sca8 = __src8;
      break;
    }
  return __extension__ ((void *) __u + __srclen);
}
#   endif
# 386 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#  endif
# 387 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
# endif
# 388 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#endif
# 389 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4


/* Return pointer to C in S.  */
#ifndef _HAVE_STRING_ARCH_strchr
extern void *__rawmemchr (const void *__s, int __c);
# if __GNUC_PREREQ (3, 2)
#  define strchr(s, c) \
  (__extension__ (__builtin_constant_p (c) && !__builtin_constant_p (s)	      \
		  && (c) == '\0'					      \
		  ? (char *) __rawmemchr (s, c)				      \
		  : __builtin_strchr (s, c)))
# else
# 401 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#  define strchr(s, c) \
  (__extension__ (__builtin_constant_p (c) && (c) == '\0'		      \
		  ? (char *) __rawmemchr (s, c)				      \
		  : strchr (s, c)))
# endif
# 406 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#endif
# 407 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4


/* Copy SRC to DEST.  */
#if (!defined _HAVE_STRING_ARCH_strcpy && !__GNUC_PREREQ (3, 0)) \
    || defined _FORCE_INLINES
# if !defined _HAVE_STRING_ARCH_strcpy && !__GNUC_PREREQ (3, 0)
#  define strcpy(dest, src) \
  (__extension__ (__builtin_constant_p (src)				      \
		  ? (__string2_1bptr_p (src) && strlen (src) + 1 <= 8	      \
		     ? __strcpy_small (dest, __strcpy_args (src),	      \
				       strlen (src) + 1)		      \
		     : (char *) memcpy (dest, src, strlen (src) + 1))	      \
		  : strcpy (dest, src)))
# endif
# 421 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4

# if _STRING_INLINE_unaligned
#  ifndef _FORCE_INLINES
#   define __strcpy_args(src) \
     __extension__ __STRING2_SMALL_GET16 (src, 0),			      \
     __extension__ __STRING2_SMALL_GET16 (src, 4),			      \
     __extension__ __STRING2_SMALL_GET32 (src, 0),			      \
     __extension__ __STRING2_SMALL_GET32 (src, 4)
#  endif
# 430 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
__STRING_INLINE char *__strcpy_small (char *, __uint16_t, __uint16_t,
				      __uint32_t, __uint32_t, size_t);
__STRING_INLINE char *
__strcpy_small (char *__dest,
		__uint16_t __src0_2, __uint16_t __src4_2,
		__uint32_t __src0_4, __uint32_t __src4_4,
		size_t __srclen)
{
  union {
    __uint32_t __ui;
    __uint16_t __usi;
    unsigned char __uc;
  } *__u = (void *) __dest;
  switch ((unsigned int) __srclen)
    {
    case 1:
      __u->__uc = '\0';
      break;
    case 2:
      __u->__usi = __src0_2;
      break;
    case 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((void *) __u + 2);
      __u->__uc = '\0';
      break;
    case 4:
      __u->__ui = __src0_4;
      break;
    case 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__uc = '\0';
      break;
    case 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__usi = __src4_2;
      break;
    case 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((void *) __u + 2);
      __u->__uc = '\0';
      break;
    case 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__ui = __src4_4;
      break;
    }
  return __dest;
}
# else
# 485 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#  ifndef _FORCE_INLINES
#   define __strcpy_args(src) \
     __extension__ ((__STRING2_COPY_ARR2)				      \
      { { ((const char *) (src))[0], '\0' } }),				      \
     __extension__ ((__STRING2_COPY_ARR3)				      \
      { { ((const char *) (src))[0], ((const char *) (src))[1],		      \
	  '\0' } }),							      \
     __extension__ ((__STRING2_COPY_ARR4)				      \
      { { ((const char *) (src))[0], ((const char *) (src))[1],		      \
	  ((const char *) (src))[2], '\0' } }),				      \
     __extension__ ((__STRING2_COPY_ARR5)				      \
      { { ((const char *) (src))[0], ((const char *) (src))[1],		      \
	  ((const char *) (src))[2], ((const char *) (src))[3],		      \
	  '\0' } }),							      \
     __extension__ ((__STRING2_COPY_ARR6)				      \
      { { ((const char *) (src))[0], ((const char *) (src))[1],		      \
	  ((const char *) (src))[2], ((const char *) (src))[3],		      \
	  ((const char *) (src))[4], '\0' } }),				      \
     __extension__ ((__STRING2_COPY_ARR7)				      \
      { { ((const char *) (src))[0], ((const char *) (src))[1],		      \
	  ((const char *) (src))[2], ((const char *) (src))[3],		      \
	  ((const char *) (src))[4], ((const char *) (src))[5],		      \
	  '\0' } }),							      \
     __extension__ ((__STRING2_COPY_ARR8)				      \
      { { ((const char *) (src))[0], ((const char *) (src))[1],		      \
	  ((const char *) (src))[2], ((const char *) (src))[3],		      \
	  ((const char *) (src))[4], ((const char *) (src))[5],		      \
	  ((const char *) (src))[6], '\0' } })
#  endif
# 514 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
__STRING_INLINE char *__strcpy_small (char *, __STRING2_COPY_ARR2,
				      __STRING2_COPY_ARR3,
				      __STRING2_COPY_ARR4,
				      __STRING2_COPY_ARR5,
				      __STRING2_COPY_ARR6,
				      __STRING2_COPY_ARR7,
				      __STRING2_COPY_ARR8, size_t);
__STRING_INLINE char *
__strcpy_small (char *__dest,
		__STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		__STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		__STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		__STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  union {
    char __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (void *) __dest;
  switch ((unsigned int) __srclen)
    {
    case 1:
      __u->__c = '\0';
      break;
    case 2:
      __extension__ __u->__sca2 = __src2;
      break;
    case 3:
      __extension__ __u->__sca3 = __src3;
      break;
    case 4:
      __extension__ __u->__sca4 = __src4;
      break;
    case 5:
      __extension__ __u->__sca5 = __src5;
      break;
    case 6:
      __extension__ __u->__sca6 = __src6;
      break;
    case 7:
      __extension__ __u->__sca7 = __src7;
      break;
    case 8:
      __extension__ __u->__sca8 = __src8;
      break;
  }
  return __dest;
}
# endif
# 568 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#endif
# 569 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4


/* Copy SRC to DEST, returning pointer to final NUL byte.  */
#ifdef __USE_GNU
# if !defined _HAVE_STRING_ARCH_stpcpy || defined _FORCE_INLINES
#  ifndef _HAVE_STRING_ARCH_stpcpy
#   if __GNUC_PREREQ (3, 4)
#    define __stpcpy(dest, src) __builtin_stpcpy (dest, src)
#   elif __GNUC_PREREQ (3, 0)
# 578 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#    define __stpcpy(dest, src) \
  (__extension__ (__builtin_constant_p (src)				      \
		  ? (__string2_1bptr_p (src) && strlen (src) + 1 <= 8	      \
		     ? __builtin_strcpy (dest, src) + strlen (src)	      \
		     : ((char *) (__mempcpy) (dest, src, strlen (src) + 1)    \
			- 1))						      \
		  : __stpcpy (dest, src)))
#   else
# 586 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#    define __stpcpy(dest, src) \
  (__extension__ (__builtin_constant_p (src)				      \
		  ? (__string2_1bptr_p (src) && strlen (src) + 1 <= 8	      \
		     ? __stpcpy_small (dest, __stpcpy_args (src),	      \
				       strlen (src) + 1)		      \
		     : ((char *) (__mempcpy) (dest, src, strlen (src) + 1)    \
			- 1))						      \
		  : __stpcpy (dest, src)))
#   endif
# 595 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
/* In glibc we use this function frequently but for namespace reasons
   we have to use the name `__stpcpy'.  */
#   define stpcpy(dest, src) __stpcpy (dest, src)
#  endif
# 599 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4

#  if !__GNUC_PREREQ (3, 0) || defined _FORCE_INLINES
#   if _STRING_INLINE_unaligned
#    ifndef _FORCE_INLINES
#     define __stpcpy_args(src) \
     __extension__ __STRING2_SMALL_GET16 (src, 0),			      \
     __extension__ __STRING2_SMALL_GET16 (src, 4),			      \
     __extension__ __STRING2_SMALL_GET32 (src, 0),			      \
     __extension__ __STRING2_SMALL_GET32 (src, 4)
#    endif
# 609 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
__STRING_INLINE char *__stpcpy_small (char *, __uint16_t, __uint16_t,
				      __uint32_t, __uint32_t, size_t);
__STRING_INLINE char *
__stpcpy_small (char *__dest,
		__uint16_t __src0_2, __uint16_t __src4_2,
		__uint32_t __src0_4, __uint32_t __src4_4,
		size_t __srclen)
{
  union {
    unsigned int __ui;
    unsigned short int __usi;
    unsigned char __uc;
    char __c;
  } *__u = (void *) __dest;
  switch ((unsigned int) __srclen)
    {
    case 1:
      __u->__uc = '\0';
      break;
    case 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((void *) __u + 1);
      break;
    case 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((void *) __u + 2);
      __u->__uc = '\0';
      break;
    case 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 3);
      break;
    case 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__uc = '\0';
      break;
    case 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((void *) __u + 1);
      break;
    case 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((void *) __u + 2);
      __u->__uc = '\0';
      break;
    case 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((void *) __u + 3);
      break;
    }
  return &__u->__c;
}
#   else
# 669 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#    ifndef _FORCE_INLINES
#     define __stpcpy_args(src) \
     __extension__ ((__STRING2_COPY_ARR2)				      \
      { { ((const char *) (src))[0], '\0' } }),				      \
     __extension__ ((__STRING2_COPY_ARR3)				      \
      { { ((const char *) (src))[0], ((const char *) (src))[1],		      \
	  '\0' } }),							      \
     __extension__ ((__STRING2_COPY_ARR4)				      \
      { { ((const char *) (src))[0], ((const char *) (src))[1],		      \
	  ((const char *) (src))[2], '\0' } }),				      \
     __extension__ ((__STRING2_COPY_ARR5)				      \
      { { ((const char *) (src))[0], ((const char *) (src))[1],		      \
	  ((const char *) (src))[2], ((const char *) (src))[3],		      \
	  '\0' } }),							      \
     __extension__ ((__STRING2_COPY_ARR6)				      \
      { { ((const char *) (src))[0], ((const char *) (src))[1],		      \
	  ((const char *) (src))[2], ((const char *) (src))[3],		      \
	  ((const char *) (src))[4], '\0' } }),				      \
     __extension__ ((__STRING2_COPY_ARR7)				      \
      { { ((const char *) (src))[0], ((const char *) (src))[1],		      \
	  ((const char *) (src))[2], ((const char *) (src))[3],		      \
	  ((const char *) (src))[4], ((const char *) (src))[5],		      \
	  '\0' } }),							      \
     __extension__ ((__STRING2_COPY_ARR8)				      \
      { { ((const char *) (src))[0], ((const char *) (src))[1],		      \
	  ((const char *) (src))[2], ((const char *) (src))[3],		      \
	  ((const char *) (src))[4], ((const char *) (src))[5],		      \
	  ((const char *) (src))[6], '\0' } })
#    endif
# 698 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
__STRING_INLINE char *__stpcpy_small (char *, __STRING2_COPY_ARR2,
				      __STRING2_COPY_ARR3,
				      __STRING2_COPY_ARR4,
				      __STRING2_COPY_ARR5,
				      __STRING2_COPY_ARR6,
				      __STRING2_COPY_ARR7,
				      __STRING2_COPY_ARR8, size_t);
__STRING_INLINE char *
__stpcpy_small (char *__dest,
		__STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		__STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		__STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		__STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  union {
    char __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (void *) __dest;
  switch ((unsigned int) __srclen)
    {
    case 1:
      __u->__c = '\0';
      break;
    case 2:
      __extension__ __u->__sca2 = __src2;
      break;
    case 3:
      __extension__ __u->__sca3 = __src3;
      break;
    case 4:
      __extension__ __u->__sca4 = __src4;
      break;
    case 5:
      __extension__ __u->__sca5 = __src5;
      break;
    case 6:
      __extension__ __u->__sca6 = __src6;
      break;
    case 7:
      __extension__ __u->__sca7 = __src7;
      break;
    case 8:
      __extension__ __u->__sca8 = __src8;
      break;
  }
  return __dest + __srclen - 1;
}
#   endif
# 752 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#  endif
# 753 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
# endif
# 754 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#endif
# 755 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4


/* Copy no more than N characters of SRC to DEST.  */
#ifndef _HAVE_STRING_ARCH_strncpy
# if __GNUC_PREREQ (3, 2)
#  define strncpy(dest, src, n) __builtin_strncpy (dest, src, n)
# else
# 762 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#  define strncpy(dest, src, n) \
  (__extension__ (__builtin_constant_p (src) && __builtin_constant_p (n)      \
		  ? (strlen (src) + 1 >= ((size_t) (n))			      \
		     ? (char *) memcpy (dest, src, n)			      \
		     : strncpy (dest, src, n))				      \
		  : strncpy (dest, src, n)))
# endif
# 769 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#endif
# 770 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4


/* Append no more than N characters from SRC onto DEST.  */
#ifndef _HAVE_STRING_ARCH_strncat
# ifdef _USE_STRING_ARCH_strchr
#  define strncat(dest, src, n) \
  (__extension__ ({ char *__dest = (dest);				      \
		    __builtin_constant_p (src) && __builtin_constant_p (n)    \
		    ? (strlen (src) < ((size_t) (n))			      \
		       ? strcat (__dest, src)				      \
		       : (*((char *) __mempcpy (strchr (__dest, '\0'),	      \
						src, n)) = '\0', __dest))     \
		    : strncat (dest, src, n); }))
# elif __GNUC_PREREQ (3, 2)
# 784 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#  define strncat(dest, src, n) __builtin_strncat (dest, src, n)
# else
# 786 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#  define strncat(dest, src, n) \
  (__extension__ (__builtin_constant_p (src) && __builtin_constant_p (n)      \
		  ? (strlen (src) < ((size_t) (n))			      \
		     ? strcat (dest, src)				      \
		     : strncat (dest, src, n))				      \
		  : strncat (dest, src, n)))
# endif
# 793 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#endif
# 794 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4


/* Compare characters of S1 and S2.  */
#ifndef _HAVE_STRING_ARCH_strcmp
# if __GNUC_PREREQ (3, 2)
#  define strcmp(s1, s2) \
  __extension__								      \
  ({ size_t __s1_len, __s2_len;						      \
     (__builtin_constant_p (s1) && __builtin_constant_p (s2)		      \
      && (__s1_len = __builtin_strlen (s1), __s2_len = __builtin_strlen (s2), \
	  (!__string2_1bptr_p (s1) || __s1_len >= 4)			      \
	  && (!__string2_1bptr_p (s2) || __s2_len >= 4))		      \
      ? __builtin_strcmp (s1, s2)					      \
      : (__builtin_constant_p (s1) && __string2_1bptr_p (s1)		      \
	 && (__s1_len = __builtin_strlen (s1), __s1_len < 4)		      \
	 ? (__builtin_constant_p (s2) && __string2_1bptr_p (s2)		      \
	    ? __builtin_strcmp (s1, s2)					      \
	    : __strcmp_cg (s1, s2, __s1_len))				      \
	 : (__builtin_constant_p (s2) && __string2_1bptr_p (s2)		      \
	    && (__s2_len = __builtin_strlen (s2), __s2_len < 4)		      \
	    ? (__builtin_constant_p (s1) && __string2_1bptr_p (s1)	      \
	       ? __builtin_strcmp (s1, s2)				      \
	       : __strcmp_gc (s1, s2, __s2_len))			      \
	    : __builtin_strcmp (s1, s2)))); })
# else
# 819 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#  define strcmp(s1, s2) \
  __extension__								      \
  ({ size_t __s1_len, __s2_len;						      \
     (__builtin_constant_p (s1) && __builtin_constant_p (s2)		      \
      && (__s1_len = strlen (s1), __s2_len = strlen (s2),		      \
	  (!__string2_1bptr_p (s1) || __s1_len >= 4)			      \
	  && (!__string2_1bptr_p (s2) || __s2_len >= 4))		      \
      ? memcmp ((const char *) (s1), (const char *) (s2),		      \
		(__s1_len < __s2_len ? __s1_len : __s2_len) + 1)	      \
      : (__builtin_constant_p (s1) && __string2_1bptr_p (s1)		      \
	 && (__s1_len = strlen (s1), __s1_len < 4)			      \
	 ? (__builtin_constant_p (s2) && __string2_1bptr_p (s2)		      \
	    ? __strcmp_cc (s1, s2, __s1_len)				      \
	    : __strcmp_cg (s1, s2, __s1_len))				      \
	 : (__builtin_constant_p (s2) && __string2_1bptr_p (s2)		      \
	    && (__s2_len = strlen (s2), __s2_len < 4)			      \
	    ? (__builtin_constant_p (s1) && __string2_1bptr_p (s1)	      \
	       ? __strcmp_cc (s1, s2, __s2_len)				      \
	       : __strcmp_gc (s1, s2, __s2_len))			      \
	    : strcmp (s1, s2)))); })
# endif
# 840 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4

# define __strcmp_cc(s1, s2, l) \
  (__extension__ ({ int __result =					      \
		      (((const unsigned char *) (const char *) (s1))[0]	      \
		       - ((const unsigned char *) (const char *)(s2))[0]);    \
		    if (l > 0 && __result == 0)				      \
		      {							      \
			__result = (((const unsigned char *)		      \
				     (const char *) (s1))[1]		      \
				    - ((const unsigned char *)		      \
				       (const char *) (s2))[1]);	      \
			if (l > 1 && __result == 0)			      \
			  {						      \
			    __result =					      \
			      (((const unsigned char *)			      \
				(const char *) (s1))[2]			      \
			       - ((const unsigned char *)		      \
				  (const char *) (s2))[2]);		      \
			    if (l > 2 && __result == 0)			      \
			      __result =				      \
				(((const unsigned char *)		      \
				  (const char *) (s1))[3]		      \
				 - ((const unsigned char *)		      \
				    (const char *) (s2))[3]);		      \
			  }						      \
		      }							      \
		    __result; }))

# define __strcmp_cg(s1, s2, l1) \
  (__extension__ ({ const unsigned char *__s2 =				      \
		      (const unsigned char *) (const char *) (s2);	      \
		    int __result =					      \
		      (((const unsigned char *) (const char *) (s1))[0]	      \
		       - __s2[0]);					      \
		    if (l1 > 0 && __result == 0)			      \
		      {							      \
			__result = (((const unsigned char *)		      \
				     (const char *) (s1))[1] - __s2[1]);      \
			if (l1 > 1 && __result == 0)			      \
			  {						      \
			    __result = (((const unsigned char *)	      \
					 (const char *) (s1))[2] - __s2[2]);  \
			    if (l1 > 2 && __result == 0)		      \
			      __result = (((const unsigned char *)	      \
					  (const char *)  (s1))[3]	      \
					  - __s2[3]);			      \
			  }						      \
		      }							      \
		    __result; }))

# define __strcmp_gc(s1, s2, l2) (- __strcmp_cg (s2, s1, l2))
#endif
# 892 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4


/* Compare N characters of S1 and S2.  */
#ifndef _HAVE_STRING_ARCH_strncmp
# define strncmp(s1, s2, n)						      \
  (__extension__ (__builtin_constant_p (n)				      \
		  && ((__builtin_constant_p (s1)			      \
		       && strlen (s1) < ((size_t) (n)))			      \
		      || (__builtin_constant_p (s2)			      \
			  && strlen (s2) < ((size_t) (n))))		      \
		  ? strcmp (s1, s2) : strncmp (s1, s2, n)))
#endif
# 904 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4


/* Return the length of the initial segment of S which
   consists entirely of characters not in REJECT.  */
#if !defined _HAVE_STRING_ARCH_strcspn || defined _FORCE_INLINES
# ifndef _HAVE_STRING_ARCH_strcspn
#  if __GNUC_PREREQ (3, 2)
#   define strcspn(s, reject) \
  __extension__								      \
  ({ char __r0, __r1, __r2;						      \
     (__builtin_constant_p (reject) && __string2_1bptr_p (reject)	      \
      ? ((__builtin_constant_p (s) && __string2_1bptr_p (s))		      \
	 ? __builtin_strcspn (s, reject)				      \
	 : ((__r0 = ((const char *) (reject))[0], __r0 == '\0')		      \
	    ? strlen (s)						      \
	    : ((__r1 = ((const char *) (reject))[1], __r1 == '\0')	      \
	       ? __strcspn_c1 (s, __r0)					      \
	       : ((__r2 = ((const char *) (reject))[2], __r2 == '\0')	      \
		  ? __strcspn_c2 (s, __r0, __r1)			      \
		  : (((const char *) (reject))[3] == '\0'		      \
		     ? __strcspn_c3 (s, __r0, __r1, __r2)		      \
		     : __builtin_strcspn (s, reject))))))		      \
      : __builtin_strcspn (s, reject)); })
#  else
# 928 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#   define strcspn(s, reject) \
  __extension__								      \
  ({ char __r0, __r1, __r2;						      \
     (__builtin_constant_p (reject) && __string2_1bptr_p (reject)	      \
      ? ((__r0 = ((const char *) (reject))[0], __r0 == '\0')		      \
	 ? strlen (s)							      \
	 : ((__r1 = ((const char *) (reject))[1], __r1 == '\0')		      \
	    ? __strcspn_c1 (s, __r0)					      \
	    : ((__r2 = ((const char *) (reject))[2], __r2 == '\0')	      \
	       ? __strcspn_c2 (s, __r0, __r1)				      \
	       : (((const char *) (reject))[3] == '\0'			      \
		  ? __strcspn_c3 (s, __r0, __r1, __r2)			      \
		  : strcspn (s, reject)))))				      \
      : strcspn (s, reject)); })
#  endif
# 943 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
# endif
# 944 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4

__STRING_INLINE size_t __strcspn_c1 (const char *__s, int __reject);
__STRING_INLINE size_t
__strcspn_c1 (const char *__s, int __reject)
{
  size_t __result = 0;
  while (__s[__result] != '\0' && __s[__result] != __reject)
    ++__result;
  return __result;
}

__STRING_INLINE size_t __strcspn_c2 (const char *__s, int __reject1,
				     int __reject2);
__STRING_INLINE size_t
__strcspn_c2 (const char *__s, int __reject1, int __reject2)
{
  size_t __result = 0;
  while (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2)
    ++__result;
  return __result;
}

__STRING_INLINE size_t __strcspn_c3 (const char *__s, int __reject1,
				     int __reject2, int __reject3);
__STRING_INLINE size_t
__strcspn_c3 (const char *__s, int __reject1, int __reject2,
	      int __reject3)
{
  size_t __result = 0;
  while (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2 && __s[__result] != __reject3)
    ++__result;
  return __result;
}
#endif
# 980 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4


/* Return the length of the initial segment of S which
   consists entirely of characters in ACCEPT.  */
#if !defined _HAVE_STRING_ARCH_strspn || defined _FORCE_INLINES
# ifndef _HAVE_STRING_ARCH_strspn
#  if __GNUC_PREREQ (3, 2)
#   define strspn(s, accept) \
  __extension__								      \
  ({ char __a0, __a1, __a2;						      \
     (__builtin_constant_p (accept) && __string2_1bptr_p (accept)	      \
      ? ((__builtin_constant_p (s) && __string2_1bptr_p (s))		      \
	 ? __builtin_strspn (s, accept)					      \
	 : ((__a0 = ((const char *) (accept))[0], __a0 == '\0')		      \
	    ? ((void) (s), (size_t) 0)					      \
	    : ((__a1 = ((const char *) (accept))[1], __a1 == '\0')	      \
	       ? __strspn_c1 (s, __a0)					      \
	       : ((__a2 = ((const char *) (accept))[2], __a2 == '\0')	      \
		  ? __strspn_c2 (s, __a0, __a1)				      \
		  : (((const char *) (accept))[3] == '\0'		      \
		     ? __strspn_c3 (s, __a0, __a1, __a2)		      \
		     : __builtin_strspn (s, accept))))))		      \
      : __builtin_strspn (s, accept)); })
#  else
# 1004 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#   define strspn(s, accept) \
  __extension__								      \
  ({ char __a0, __a1, __a2;						      \
     (__builtin_constant_p (accept) && __string2_1bptr_p (accept)	      \
      ? ((__a0 = ((const char *) (accept))[0], __a0 == '\0')		      \
	 ? ((void) (s), (size_t) 0)					      \
	 : ((__a1 = ((const char *) (accept))[1], __a1 == '\0')		      \
	    ? __strspn_c1 (s, __a0)					      \
	    : ((__a2 = ((const char *) (accept))[2], __a2 == '\0')	      \
	       ? __strspn_c2 (s, __a0, __a1)				      \
	       : (((const char *) (accept))[3] == '\0'			      \
		  ? __strspn_c3 (s, __a0, __a1, __a2)			      \
		  : strspn (s, accept)))))				      \
      : strspn (s, accept)); })
#  endif
# 1019 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
# endif
# 1020 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4

__STRING_INLINE size_t __strspn_c1 (const char *__s, int __accept);
__STRING_INLINE size_t
__strspn_c1 (const char *__s, int __accept)
{
  size_t __result = 0;
  /* Please note that __accept never can be '\0'.  */
  while (__s[__result] == __accept)
    ++__result;
  return __result;
}

__STRING_INLINE size_t __strspn_c2 (const char *__s, int __accept1,
				    int __accept2);
__STRING_INLINE size_t
__strspn_c2 (const char *__s, int __accept1, int __accept2)
{
  size_t __result = 0;
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  while (__s[__result] == __accept1 || __s[__result] == __accept2)
    ++__result;
  return __result;
}

__STRING_INLINE size_t __strspn_c3 (const char *__s, int __accept1,
				    int __accept2, int __accept3);
__STRING_INLINE size_t
__strspn_c3 (const char *__s, int __accept1, int __accept2, int __accept3)
{
  size_t __result = 0;
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  while (__s[__result] == __accept1 || __s[__result] == __accept2
	 || __s[__result] == __accept3)
    ++__result;
  return __result;
}
#endif
# 1057 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4


/* Find the first occurrence in S of any character in ACCEPT.  */
#if !defined _HAVE_STRING_ARCH_strpbrk || defined _FORCE_INLINES
# ifndef _HAVE_STRING_ARCH_strpbrk
#  if __GNUC_PREREQ (3, 2)
#   define strpbrk(s, accept) \
  __extension__								      \
  ({ char __a0, __a1, __a2;						      \
     (__builtin_constant_p (accept) && __string2_1bptr_p (accept)	      \
      ? ((__builtin_constant_p (s) && __string2_1bptr_p (s))		      \
	 ? __builtin_strpbrk (s, accept)				      \
	 : ((__a0 = ((const char  *) (accept))[0], __a0 == '\0')	      \
	    ? ((void) (s), (char *) NULL)				      \
	    : ((__a1 = ((const char *) (accept))[1], __a1 == '\0')	      \
	       ? __builtin_strchr (s, __a0)				      \
	       : ((__a2 = ((const char *) (accept))[2], __a2 == '\0')	      \
		  ? __strpbrk_c2 (s, __a0, __a1)			      \
		  : (((const char *) (accept))[3] == '\0'		      \
		     ? __strpbrk_c3 (s, __a0, __a1, __a2)		      \
		     : __builtin_strpbrk (s, accept))))))		      \
      : __builtin_strpbrk (s, accept)); })
#  else
# 1080 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#   define strpbrk(s, accept) \
  __extension__								      \
  ({ char __a0, __a1, __a2;						      \
     (__builtin_constant_p (accept) && __string2_1bptr_p (accept)	      \
      ? ((__a0 = ((const char  *) (accept))[0], __a0 == '\0')		      \
	 ? ((void) (s), (char *) NULL)					      \
	 : ((__a1 = ((const char *) (accept))[1], __a1 == '\0')		      \
	    ? strchr (s, __a0)						      \
	    : ((__a2 = ((const char *) (accept))[2], __a2 == '\0')	      \
	       ? __strpbrk_c2 (s, __a0, __a1)				      \
	       : (((const char *) (accept))[3] == '\0'			      \
		  ? __strpbrk_c3 (s, __a0, __a1, __a2)			      \
		  : strpbrk (s, accept)))))				      \
      : strpbrk (s, accept)); })
#  endif
# 1095 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
# endif
# 1096 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4

__STRING_INLINE char *__strpbrk_c2 (const char *__s, int __accept1,
				    int __accept2);
__STRING_INLINE char *
__strpbrk_c2 (const char *__s, int __accept1, int __accept2)
{
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  while (*__s != '\0' && *__s != __accept1 && *__s != __accept2)
    ++__s;
  return *__s == '\0' ? NULL : (char *) (size_t) __s;
}

__STRING_INLINE char *__strpbrk_c3 (const char *__s, int __accept1,
				    int __accept2, int __accept3);
__STRING_INLINE char *
__strpbrk_c3 (const char *__s, int __accept1, int __accept2, int __accept3)
{
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  while (*__s != '\0' && *__s != __accept1 && *__s != __accept2
	 && *__s != __accept3)
    ++__s;
  return *__s == '\0' ? NULL : (char *) (size_t) __s;
}
#endif
# 1120 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4


/* Find the first occurrence of NEEDLE in HAYSTACK.  Newer gcc versions
   do this itself.  */
#if !defined _HAVE_STRING_ARCH_strstr && !__GNUC_PREREQ (2, 97)
# define strstr(haystack, needle) \
  (__extension__ (__builtin_constant_p (needle) && __string2_1bptr_p (needle) \
		  ? (((const char *) (needle))[0] == '\0'		      \
		     ? (char *) (size_t) (haystack)			      \
		     : (((const char *) (needle))[1] == '\0'		      \
			? strchr (haystack,				      \
				  ((const char *) (needle))[0]) 	      \
			: strstr (haystack, needle)))			      \
		  : strstr (haystack, needle)))
#endif
# 1135 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4


#if !defined _HAVE_STRING_ARCH_strtok_r || defined _FORCE_INLINES
# ifndef _HAVE_STRING_ARCH_strtok_r
#  define __strtok_r(s, sep, nextp) \
  (__extension__ (__builtin_constant_p (sep) && __string2_1bptr_p (sep)	      \
		  && ((const char *) (sep))[0] != '\0'			      \
		  && ((const char *) (sep))[1] == '\0'			      \
		  ? __strtok_r_1c (s, ((const char *) (sep))[0], nextp)       \
		  : __strtok_r (s, sep, nextp)))
# endif
# 1146 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4

__STRING_INLINE char *__strtok_r_1c (char *__s, char __sep, char **__nextp);
__STRING_INLINE char *
__strtok_r_1c (char *__s, char __sep, char **__nextp)
{
  char *__result;
  if (__s == NULL)
    __s = *__nextp;
  while (*__s == __sep)
    ++__s;
  __result = NULL;
  if (*__s != '\0')
    {
      __result = __s++;
      while (*__s != '\0')
	if (*__s++ == __sep)
	  {
	    __s[-1] = '\0';
	    break;
	  }
    }
  *__nextp = __s;
  return __result;
}
# ifdef __USE_POSIX
#  define strtok_r(s, sep, nextp) __strtok_r (s, sep, nextp)
# endif
# 1173 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#endif
# 1174 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4


#if !defined _HAVE_STRING_ARCH_strsep || defined _FORCE_INLINES
# ifndef _HAVE_STRING_ARCH_strsep

extern char *__strsep_g (char **__stringp, const char *__delim);
#  define __strsep(s, reject) \
  __extension__								      \
  ({ char __r0, __r1, __r2;						      \
     (__builtin_constant_p (reject) && __string2_1bptr_p (reject)	      \
      && (__r0 = ((const char *) (reject))[0],				      \
	  ((const char *) (reject))[0] != '\0')				      \
      ? ((__r1 = ((const char *) (reject))[1],				      \
	 ((const char *) (reject))[1] == '\0')				      \
	 ? __strsep_1c (s, __r0)					      \
	 : ((__r2 = ((const char *) (reject))[2], __r2 == '\0')		      \
	    ? __strsep_2c (s, __r0, __r1)				      \
	    : (((const char *) (reject))[3] == '\0'			      \
	       ? __strsep_3c (s, __r0, __r1, __r2)			      \
	       : __strsep_g (s, reject))))				      \
      : __strsep_g (s, reject)); })
# endif
# 1196 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4

__STRING_INLINE char *__strsep_1c (char **__s, char __reject);
__STRING_INLINE char *
__strsep_1c (char **__s, char __reject)
{
  char *__retval = *__s;
  if (__retval != NULL && (*__s = strchr (__retval, __reject)) != NULL)
    *(*__s)++ = '\0';
  return __retval;
}

__STRING_INLINE char *__strsep_2c (char **__s, char __reject1, char __reject2);
__STRING_INLINE char *
__strsep_2c (char **__s, char __reject1, char __reject2)
{
  char *__retval = *__s;
  if (__retval != NULL)
    {
      char *__cp = __retval;
      while (1)
	{
	  if (*__cp == '\0')
	    {
	      __cp = NULL;
	  break;
	    }
	  if (*__cp == __reject1 || *__cp == __reject2)
	    {
	      *__cp++ = '\0';
	      break;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  return __retval;
}

__STRING_INLINE char *__strsep_3c (char **__s, char __reject1, char __reject2,
				   char __reject3);
__STRING_INLINE char *
__strsep_3c (char **__s, char __reject1, char __reject2, char __reject3)
{
  char *__retval = *__s;
  if (__retval != NULL)
    {
      char *__cp = __retval;
      while (1)
	{
	  if (*__cp == '\0')
	    {
	      __cp = NULL;
	  break;
	    }
	  if (*__cp == __reject1 || *__cp == __reject2 || *__cp == __reject3)
	    {
	      *__cp++ = '\0';
	      break;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  return __retval;
}
# ifdef __USE_MISC
#  define strsep(s, reject) __strsep (s, reject)
# endif
# 1264 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
#endif
# 1265 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4

/* We need the memory allocation functions for inline strdup().
   Referring to stdlib.h (even minimally) is not allowed
   in any of the tight standards compliant modes.  */
#ifdef __USE_MISC

# if !defined _HAVE_STRING_ARCH_strdup || !defined _HAVE_STRING_ARCH_strndup
#  define __need_malloc_and_calloc
#if 0 /* expanded by -frewrite-includes */
#  include <stdlib.h>
#endif /* expanded by -frewrite-includes */
# 1273 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
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
# 1 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 1 3 4
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
# 37 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#define __need_ptrdiff_t
#define __need_size_t
#define __need_wchar_t
#define __need_NULL
#define __need_STDDEF_H_misc
/* __need_wint_t is intentionally not defined here. */
#endif
# 44 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_ptrdiff_t)
#if !defined(_PTRDIFF_T) || __has_feature(modules)
/* Always define ptrdiff_t when modules are available. */
#if !__has_feature(modules)
#define _PTRDIFF_T
#endif
# 51 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif
# 53 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_ptrdiff_t
#endif /* defined(__need_ptrdiff_t) */
# 55 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_size_t)
#if !defined(_SIZE_T) || __has_feature(modules)
/* Always define size_t when modules are available. */
#if !__has_feature(modules)
#define _SIZE_T
#endif
# 62 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ size_t;
#endif
# 64 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_size_t
#endif /*defined(__need_size_t) */
# 66 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
/* ISO9899:2011 7.20 (C11 Annex K): Define rsize_t if __STDC_WANT_LIB_EXT1__ is
 * enabled. */
#if (defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ >= 1 && \
     !defined(_RSIZE_T)) || __has_feature(modules)
/* Always define rsize_t when modules are available. */
#if !__has_feature(modules)
#define _RSIZE_T
#endif
# 76 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ rsize_t;
#endif
# 78 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif /* defined(__need_STDDEF_H_misc) */
# 79 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_wchar_t)
#ifndef __cplusplus
/* Always define wchar_t when modules are available. */
#if !defined(_WCHAR_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WCHAR_T
#if defined(_MSC_EXTENSIONS)
#define _WCHAR_T_DEFINED
#endif
# 89 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 90 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WCHAR_TYPE__ wchar_t;
#endif
# 92 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 93 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wchar_t
#endif /* defined(__need_wchar_t) */
# 95 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_NULL)
#undef NULL
#ifdef __cplusplus
#  if !defined(__MINGW32__) && !defined(_MSC_VER)
#    define NULL __null
#  else
# 102 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#    define NULL 0
#  endif
# 104 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#else
# 105 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#  define NULL ((void*)0)
#endif
# 107 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#ifdef __cplusplus
#if defined(_MSC_EXTENSIONS) && defined(_NATIVE_NULLPTR_SUPPORTED)
namespace std { typedef decltype(nullptr) nullptr_t; }
using ::std::nullptr_t;
#endif
# 112 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 113 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_NULL
#endif /* defined(__need_NULL) */
# 115 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
#if __STDC_VERSION__ >= 201112L || __cplusplus >= 201103L
#if 0 /* expanded by -frewrite-includes */
#include "__stddef_max_align_t.h"
#endif /* expanded by -frewrite-includes */
# 118 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
# 119 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 120 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#define offsetof(t, d) __builtin_offsetof(t, d)
#undef __need_STDDEF_H_misc
#endif  /* defined(__need_STDDEF_H_misc) */
# 123 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

/* Some C libraries expect to see a wint_t here. Others (notably MinGW) will use
__WINT_TYPE__ directly; accommodate both by requiring __need_wint_t */
#if defined(__need_wint_t)
/* Always define wint_t when modules are available. */
#if !defined(_WINT_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WINT_T
#endif
# 132 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WINT_TYPE__ wint_t;
#endif
# 134 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wint_t
#endif /* __need_wint_t */
# 136 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#endif
# 138 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
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
# 42 "/usr/include/stdlib.h" 3 4
#if 0 /* expanded by -frewrite-includes */
# include <bits/waitstatus.h>
#endif /* expanded by -frewrite-includes */
# 42 "/usr/include/stdlib.h" 3 4
# 43 "/usr/include/stdlib.h" 3 4

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
# 315 "/usr/include/stdlib.h" 3 4

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
# 493 "/usr/include/stdlib.h" 3 4
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
# 760 "/usr/include/stdlib.h" 3 4
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
# 955 "/usr/include/stdlib.h" 3 4

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
# 1274 "/usr/include/x86_64-linux-gnu/bits/string2.h" 2 3 4
# endif
# 1275 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4

# ifndef _HAVE_STRING_ARCH_strdup

extern char *__strdup (const char *__string) __THROW __attribute_malloc__;
#  define __strdup(s) \
  (__extension__ (__builtin_constant_p (s) && __string2_1bptr_p (s)	      \
		  ? (((const char *) (s))[0] == '\0'			      \
		     ? (char *) calloc ((size_t) 1, (size_t) 1)		      \
		     : ({ size_t __len = strlen (s) + 1;		      \
			  char *__retval = (char *) malloc (__len);	      \
			  if (__retval != NULL)				      \
			    __retval = (char *) memcpy (__retval, s, __len);  \
			  __retval; }))					      \
		  : __strdup (s)))

#  if defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8
#   define strdup(s) __strdup (s)
#  endif
# 1293 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
# endif
# 1294 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4

# ifndef _HAVE_STRING_ARCH_strndup

extern char *__strndup (const char *__string, size_t __n)
     __THROW __attribute_malloc__;
#  define __strndup(s, n) \
  (__extension__ (__builtin_constant_p (s) && __string2_1bptr_p (s)	      \
		  ? (((const char *) (s))[0] == '\0'			      \
		     ? (char *) calloc ((size_t) 1, (size_t) 1)		      \
		     : ({ size_t __len = strlen (s) + 1;		      \
			  size_t __n = (n);				      \
			  char *__retval;				      \
			  if (__n < __len)				      \
			    __len = __n + 1;				      \
			  __retval = (char *) malloc (__len);		      \
			  if (__retval != NULL)				      \
			    {						      \
			      __retval[__len - 1] = '\0';		      \
			      __retval = (char *) memcpy (__retval, s,	      \
							  __len - 1);	      \
			    }						      \
			  __retval; }))					      \
		  : __strndup (s, n)))

#  ifdef __USE_XOPEN2K8
#   define strndup(s, n) __strndup (s, n)
#  endif
# 1321 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
# endif
# 1322 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4

#endif /* Use misc. or use GNU.  */
# 1324 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4

#ifndef _FORCE_INLINES
# undef __STRING_INLINE
#endif
# 1328 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4

#endif /* No string inlines.  */
# 1330 "/usr/include/x86_64-linux-gnu/bits/string2.h" 3 4
# 631 "/usr/include/string.h" 2 3 4
# endif
# 632 "/usr/include/string.h" 3 4

# if __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
/* Functions with security checks.  */
#if 0 /* expanded by -frewrite-includes */
#  include <bits/string3.h>
#endif /* expanded by -frewrite-includes */
# 635 "/usr/include/string.h" 3 4
# 636 "/usr/include/string.h" 3 4
# endif
# 637 "/usr/include/string.h" 3 4
#endif
# 638 "/usr/include/string.h" 3 4

#if defined __USE_GNU && defined __OPTIMIZE__ \
    && defined __extern_always_inline && __GNUC_PREREQ (3,2)
# if !defined _FORCE_INLINES && !defined _HAVE_STRING_ARCH_mempcpy

#undef mempcpy
#undef __mempcpy
#define mempcpy(dest, src, n) __mempcpy_inline (dest, src, n)
#define __mempcpy(dest, src, n) __mempcpy_inline (dest, src, n)

__extern_always_inline void *
__mempcpy_inline (void *__restrict __dest,
		  const void *__restrict __src, size_t __n)
{
  return (char *) memcpy (__dest, __src, __n) + __n;
}

# endif
# 656 "/usr/include/string.h" 3 4
#endif
# 657 "/usr/include/string.h" 3 4

__END_DECLS

#endif /* string.h  */
# 661 "/usr/include/string.h" 3 4
# 11 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/covariance.c" 2
#if 0 /* expanded by -frewrite-includes */
#include <math.h>
#endif /* expanded by -frewrite-includes */
# 11 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/covariance.c"
# 1 "/usr/include/math.h" 1 3 4
/* Declarations for math functions.
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
 *	ISO C99 Standard: 7.12 Mathematics	<math.h>
 */

#ifndef	_MATH_H
#define	_MATH_H	1

#if 0 /* expanded by -frewrite-includes */
#include <features.h>
#endif /* expanded by -frewrite-includes */
# 26 "/usr/include/math.h" 3 4
# 27 "/usr/include/math.h" 3 4

__BEGIN_DECLS

/* Get machine-dependent vector math functions declarations.  */
#if 0 /* expanded by -frewrite-includes */
#include <bits/math-vector.h>
#endif /* expanded by -frewrite-includes */
# 31 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/math-vector.h" 1 3 4
/* Platform-specific SIMD declarations of math functions.
   Copyright (C) 2014-2016 Free Software Foundation, Inc.
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

#ifndef _MATH_H
# error "Never include <bits/math-vector.h> directly;\
 include <math.h> instead."
#endif
# 23 "/usr/include/x86_64-linux-gnu/bits/math-vector.h" 3 4

/* Get default empty definitions for simd declarations.  */
#if 0 /* expanded by -frewrite-includes */
#include <bits/libm-simd-decl-stubs.h>
#endif /* expanded by -frewrite-includes */
# 25 "/usr/include/x86_64-linux-gnu/bits/math-vector.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/libm-simd-decl-stubs.h" 1 3 4
/* Empty definitions required for __MATHCALL_VEC unfolding in mathcalls.h.
   Copyright (C) 2014-2016 Free Software Foundation, Inc.
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

#ifndef _MATH_H
# error "Never include <bits/libm-simd-decl-stubs.h> directly;\
 include <math.h> instead."
#endif
# 23 "/usr/include/x86_64-linux-gnu/bits/libm-simd-decl-stubs.h" 3 4

/* Needed definitions could be generated with:
   for func in $(grep __MATHCALL_VEC math/bits/mathcalls.h |\
		 sed -r "s|__MATHCALL_VEC.?\(||; s|,.*||"); do
     echo "#define __DECL_SIMD_${func}";
     echo "#define __DECL_SIMD_${func}f";
     echo "#define __DECL_SIMD_${func}l";
   done
 */

#ifndef _BITS_LIBM_SIMD_DECL_STUBS_H
#define _BITS_LIBM_SIMD_DECL_STUBS_H 1

#define __DECL_SIMD_cos
#define __DECL_SIMD_cosf
#define __DECL_SIMD_cosl

#define __DECL_SIMD_sin
#define __DECL_SIMD_sinf
#define __DECL_SIMD_sinl

#define __DECL_SIMD_sincos
#define __DECL_SIMD_sincosf
#define __DECL_SIMD_sincosl

#define __DECL_SIMD_log
#define __DECL_SIMD_logf
#define __DECL_SIMD_logl

#define __DECL_SIMD_exp
#define __DECL_SIMD_expf
#define __DECL_SIMD_expl

#define __DECL_SIMD_pow
#define __DECL_SIMD_powf
#define __DECL_SIMD_powl
#endif
# 60 "/usr/include/x86_64-linux-gnu/bits/libm-simd-decl-stubs.h" 3 4
# 26 "/usr/include/x86_64-linux-gnu/bits/math-vector.h" 2 3 4

#if defined __x86_64__ && defined __FAST_MATH__
# if defined _OPENMP && _OPENMP >= 201307
/* OpenMP case.  */
#  define __DECL_SIMD_x86_64 _Pragma ("omp declare simd notinbranch")
# elif __GNUC_PREREQ (6,0)
# 32 "/usr/include/x86_64-linux-gnu/bits/math-vector.h" 3 4
/* W/o OpenMP use GCC 6.* __attribute__ ((__simd__)).  */
#  define __DECL_SIMD_x86_64 __attribute__ ((__simd__ ("notinbranch")))
# endif
# 35 "/usr/include/x86_64-linux-gnu/bits/math-vector.h" 3 4

# ifdef __DECL_SIMD_x86_64
#  undef __DECL_SIMD_cos
#  define __DECL_SIMD_cos __DECL_SIMD_x86_64
#  undef __DECL_SIMD_cosf
#  define __DECL_SIMD_cosf __DECL_SIMD_x86_64
#  undef __DECL_SIMD_sin
#  define __DECL_SIMD_sin __DECL_SIMD_x86_64
#  undef __DECL_SIMD_sinf
#  define __DECL_SIMD_sinf __DECL_SIMD_x86_64
#  undef __DECL_SIMD_sincos
#  define __DECL_SIMD_sincos __DECL_SIMD_x86_64
#  undef __DECL_SIMD_sincosf
#  define __DECL_SIMD_sincosf __DECL_SIMD_x86_64
#  undef __DECL_SIMD_log
#  define __DECL_SIMD_log __DECL_SIMD_x86_64
#  undef __DECL_SIMD_logf
#  define __DECL_SIMD_logf __DECL_SIMD_x86_64
#  undef __DECL_SIMD_exp
#  define __DECL_SIMD_exp __DECL_SIMD_x86_64
#  undef __DECL_SIMD_expf
#  define __DECL_SIMD_expf __DECL_SIMD_x86_64
#  undef __DECL_SIMD_pow
#  define __DECL_SIMD_pow __DECL_SIMD_x86_64
#  undef __DECL_SIMD_powf
#  define __DECL_SIMD_powf __DECL_SIMD_x86_64

# endif
# 63 "/usr/include/x86_64-linux-gnu/bits/math-vector.h" 3 4
#endif
# 64 "/usr/include/x86_64-linux-gnu/bits/math-vector.h" 3 4
# 32 "/usr/include/math.h" 2 3 4

/* Get machine-dependent HUGE_VAL value (returned on overflow).
   On all IEEE754 machines, this is +Infinity.  */
#if 0 /* expanded by -frewrite-includes */
#include <bits/huge_val.h>
#endif /* expanded by -frewrite-includes */
# 35 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/huge_val.h" 1 3 4
/* `HUGE_VAL' constant for IEEE 754 machines (where it is infinity).
   Used by <stdlib.h> and <math.h> functions for overflow.
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

#ifndef _MATH_H
# error "Never use <bits/huge_val.h> directly; include <math.h> instead."
#endif
# 23 "/usr/include/x86_64-linux-gnu/bits/huge_val.h" 3 4

/* IEEE positive infinity (-HUGE_VAL is negative infinity).  */

#if __GNUC_PREREQ(3,3)
# define HUGE_VAL	(__builtin_huge_val())
#elif __GNUC_PREREQ(2,96)
# 29 "/usr/include/x86_64-linux-gnu/bits/huge_val.h" 3 4
# define HUGE_VAL	(__extension__ 0x1.0p2047)
#elif defined __GNUC__
# 31 "/usr/include/x86_64-linux-gnu/bits/huge_val.h" 3 4

# define HUGE_VAL \
  (__extension__							      \
   ((union { unsigned __l __attribute__((__mode__(__DI__))); double __d; })   \
    { __l: 0x7ff0000000000000ULL }).__d)

#else /* not GCC */
# 38 "/usr/include/x86_64-linux-gnu/bits/huge_val.h" 3 4

#if 0 /* expanded by -frewrite-includes */
# include <endian.h>
#endif /* expanded by -frewrite-includes */
# 39 "/usr/include/x86_64-linux-gnu/bits/huge_val.h" 3 4
# 40 "/usr/include/x86_64-linux-gnu/bits/huge_val.h" 3 4

typedef union { unsigned char __c[8]; double __d; } __huge_val_t;

# if __BYTE_ORDER == __BIG_ENDIAN
#  define __HUGE_VAL_bytes	{ 0x7f, 0xf0, 0, 0, 0, 0, 0, 0 }
# endif
# 46 "/usr/include/x86_64-linux-gnu/bits/huge_val.h" 3 4
# if __BYTE_ORDER == __LITTLE_ENDIAN
#  define __HUGE_VAL_bytes	{ 0, 0, 0, 0, 0, 0, 0xf0, 0x7f }
# endif
# 49 "/usr/include/x86_64-linux-gnu/bits/huge_val.h" 3 4

static __huge_val_t __huge_val = { __HUGE_VAL_bytes };
# define HUGE_VAL	(__huge_val.__d)

#endif	/* GCC.  */
# 54 "/usr/include/x86_64-linux-gnu/bits/huge_val.h" 3 4
# 36 "/usr/include/math.h" 2 3 4
#ifdef __USE_ISOC99
#if 0 /* expanded by -frewrite-includes */
# include <bits/huge_valf.h>
#endif /* expanded by -frewrite-includes */
# 37 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/huge_valf.h" 1 3 4
/* `HUGE_VALF' constant for IEEE 754 machines (where it is infinity).
   Used by <stdlib.h> and <math.h> functions for overflow.
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

#ifndef _MATH_H
# error "Never use <bits/huge_valf.h> directly; include <math.h> instead."
#endif
# 23 "/usr/include/x86_64-linux-gnu/bits/huge_valf.h" 3 4

/* IEEE positive infinity (-HUGE_VAL is negative infinity).  */

#if __GNUC_PREREQ(3,3)
# define HUGE_VALF	(__builtin_huge_valf())
#elif __GNUC_PREREQ(2,96)
# 29 "/usr/include/x86_64-linux-gnu/bits/huge_valf.h" 3 4
# define HUGE_VALF	(__extension__ 0x1.0p255f)
#elif defined __GNUC__
# 31 "/usr/include/x86_64-linux-gnu/bits/huge_valf.h" 3 4

#   define HUGE_VALF \
  (__extension__							      \
   ((union { unsigned __l __attribute__((__mode__(__SI__))); float __d; })    \
    { __l: 0x7f800000UL }).__d)

#else /* not GCC */
# 38 "/usr/include/x86_64-linux-gnu/bits/huge_valf.h" 3 4

typedef union { unsigned char __c[4]; float __f; } __huge_valf_t;

# if __BYTE_ORDER == __BIG_ENDIAN
#  define __HUGE_VALF_bytes	{ 0x7f, 0x80, 0, 0 }
# endif
# 44 "/usr/include/x86_64-linux-gnu/bits/huge_valf.h" 3 4
# if __BYTE_ORDER == __LITTLE_ENDIAN
#  define __HUGE_VALF_bytes	{ 0, 0, 0x80, 0x7f }
# endif
# 47 "/usr/include/x86_64-linux-gnu/bits/huge_valf.h" 3 4

static __huge_valf_t __huge_valf = { __HUGE_VALF_bytes };
# define HUGE_VALF	(__huge_valf.__f)

#endif	/* GCC.  */
# 52 "/usr/include/x86_64-linux-gnu/bits/huge_valf.h" 3 4
# 38 "/usr/include/math.h" 2 3 4
#if 0 /* expanded by -frewrite-includes */
# include <bits/huge_vall.h>
#endif /* expanded by -frewrite-includes */
# 38 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/huge_vall.h" 1 3 4
/* `HUGE_VALL' constant for ix86 (where it is infinity).
   Used by <stdlib.h> and <math.h> functions for overflow.
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

#ifndef _MATH_H
# error "Never use <bits/huge_vall.h> directly; include <math.h> instead."
#endif
# 23 "/usr/include/x86_64-linux-gnu/bits/huge_vall.h" 3 4

#if __GNUC_PREREQ(3,3)
# define HUGE_VALL	(__builtin_huge_vall())
#elif __GNUC_PREREQ(2,96)
# 27 "/usr/include/x86_64-linux-gnu/bits/huge_vall.h" 3 4
# define HUGE_VALL	(__extension__ 0x1.0p32767L)
#else
# 29 "/usr/include/x86_64-linux-gnu/bits/huge_vall.h" 3 4

# define __HUGE_VALL_bytes	{ 0, 0, 0, 0, 0, 0, 0, 0x80, 0xff, 0x7f, 0, 0 }

# define __huge_vall_t	union { unsigned char __c[12]; long double __ld; }
# ifdef __GNUC__
#  define HUGE_VALL	(__extension__ \
			 ((__huge_vall_t) { __c: __HUGE_VALL_bytes }).__ld)
# else	/* Not GCC.  */
# 37 "/usr/include/x86_64-linux-gnu/bits/huge_vall.h" 3 4
static __huge_vall_t __huge_vall = { __HUGE_VALL_bytes };
#  define HUGE_VALL	(__huge_vall.__ld)
#  endif /* GCC.  */
# 40 "/usr/include/x86_64-linux-gnu/bits/huge_vall.h" 3 4

#endif /* GCC 2.95 */
# 42 "/usr/include/x86_64-linux-gnu/bits/huge_vall.h" 3 4
# 39 "/usr/include/math.h" 2 3 4

/* Get machine-dependent INFINITY value.  */
#if 0 /* expanded by -frewrite-includes */
# include <bits/inf.h>
#endif /* expanded by -frewrite-includes */
# 41 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/inf.h" 1 3 4
/* `INFINITY' constant for IEEE 754 machines.
   Copyright (C) 2004-2016 Free Software Foundation, Inc.
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

#ifndef _MATH_H
# error "Never use <bits/inf.h> directly; include <math.h> instead."
#endif
# 22 "/usr/include/x86_64-linux-gnu/bits/inf.h" 3 4

/* IEEE positive infinity.  */

#if __GNUC_PREREQ(3,3)
# define INFINITY	(__builtin_inff())
#else
# 28 "/usr/include/x86_64-linux-gnu/bits/inf.h" 3 4
# define INFINITY	HUGE_VALF
#endif
# 30 "/usr/include/x86_64-linux-gnu/bits/inf.h" 3 4
# 42 "/usr/include/math.h" 2 3 4

/* Get machine-dependent NAN value (returned for some domain errors).  */
#if 0 /* expanded by -frewrite-includes */
# include <bits/nan.h>
#endif /* expanded by -frewrite-includes */
# 44 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/nan.h" 1 3 4
/* `NAN' constant for IEEE 754 machines.
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

#ifndef _MATH_H
# error "Never use <bits/nan.h> directly; include <math.h> instead."
#endif
# 22 "/usr/include/x86_64-linux-gnu/bits/nan.h" 3 4


/* IEEE Not A Number.  */

#if __GNUC_PREREQ(3,3)

# define NAN	(__builtin_nanf (""))

#elif defined __GNUC__
# 31 "/usr/include/x86_64-linux-gnu/bits/nan.h" 3 4

# define NAN \
  (__extension__							      \
   ((union { unsigned __l __attribute__ ((__mode__ (__SI__))); float __d; })  \
    { __l: 0x7fc00000UL }).__d)

#else
# 38 "/usr/include/x86_64-linux-gnu/bits/nan.h" 3 4

#if 0 /* expanded by -frewrite-includes */
# include <endian.h>
#endif /* expanded by -frewrite-includes */
# 39 "/usr/include/x86_64-linux-gnu/bits/nan.h" 3 4
# 40 "/usr/include/x86_64-linux-gnu/bits/nan.h" 3 4

# if __BYTE_ORDER == __BIG_ENDIAN
#  define __qnan_bytes		{ 0x7f, 0xc0, 0, 0 }
# endif
# 44 "/usr/include/x86_64-linux-gnu/bits/nan.h" 3 4
# if __BYTE_ORDER == __LITTLE_ENDIAN
#  define __qnan_bytes		{ 0, 0, 0xc0, 0x7f }
# endif
# 47 "/usr/include/x86_64-linux-gnu/bits/nan.h" 3 4

static union { unsigned char __c[4]; float __d; } __qnan_union
  __attribute__ ((__unused__)) = { __qnan_bytes };
# define NAN	(__qnan_union.__d)

#endif	/* GCC.  */
# 53 "/usr/include/x86_64-linux-gnu/bits/nan.h" 3 4
# 45 "/usr/include/math.h" 2 3 4
#endif /* __USE_ISOC99 */
# 46 "/usr/include/math.h" 3 4

/* Get general and ISO C99 specific information.  */
#if 0 /* expanded by -frewrite-includes */
#include <bits/mathdef.h>
#endif /* expanded by -frewrite-includes */
# 48 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/mathdef.h" 1 3 4
/* Copyright (C) 2001-2016 Free Software Foundation, Inc.
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

#if !defined _MATH_H && !defined _COMPLEX_H
# error "Never use <bits/mathdef.h> directly; include <math.h> instead"
#endif
# 21 "/usr/include/x86_64-linux-gnu/bits/mathdef.h" 3 4

#if defined __USE_ISOC99 && defined _MATH_H && !defined _MATH_H_MATHDEF
# define _MATH_H_MATHDEF	1

# if defined __x86_64__ || (defined __FLT_EVAL_METHOD__ && __FLT_EVAL_METHOD__ == 0)
/* The x86-64 architecture computes values with the precission of the
   used type.  Similarly for -m32 -mfpmath=sse.  */
typedef float float_t;		/* `float' expressions are evaluated as `float'.  */
typedef double double_t;	/* `double' expressions are evaluated
				   as `double'.  */
# else
# 32 "/usr/include/x86_64-linux-gnu/bits/mathdef.h" 3 4
/* The ix87 FPUs evaluate all values in the 80 bit floating-point format
   which is also available for the user as `long double'.  Therefore we
   define:  */
typedef long double float_t;	/* `float' expressions are evaluated as
				   `long double'.  */
typedef long double double_t;	/* `double' expressions are evaluated as
				   `long double'.  */
# endif
# 40 "/usr/include/x86_64-linux-gnu/bits/mathdef.h" 3 4

/* The values returned by `ilogb' for 0 and NaN respectively.  */
# define FP_ILOGB0	(-2147483647 - 1)
# define FP_ILOGBNAN	(-2147483647 - 1)

/* The GCC 4.6 compiler will define __FP_FAST_FMA{,F,L} if the fma{,f,l}
   builtins are supported.  */
# ifdef __FP_FAST_FMA
#  define FP_FAST_FMA 1
# endif
# 50 "/usr/include/x86_64-linux-gnu/bits/mathdef.h" 3 4

# ifdef __FP_FAST_FMAF
#  define FP_FAST_FMAF 1
# endif
# 54 "/usr/include/x86_64-linux-gnu/bits/mathdef.h" 3 4

# ifdef __FP_FAST_FMAL
#  define FP_FAST_FMAL 1
# endif
# 58 "/usr/include/x86_64-linux-gnu/bits/mathdef.h" 3 4

#endif	/* ISO C99 */
# 60 "/usr/include/x86_64-linux-gnu/bits/mathdef.h" 3 4
# 49 "/usr/include/math.h" 2 3 4

/* The file <bits/mathcalls.h> contains the prototypes for all the
   actual math functions.  These macros are used for those prototypes,
   so we can easily declare each function as both `name' and `__name',
   and can declare the float versions `namef' and `__namef'.  */

#define __SIMD_DECL(function) __CONCAT (__DECL_SIMD_, function)

#define __MATHCALL_VEC(function, suffix, args) 	\
  __SIMD_DECL (__MATH_PRECNAME (function, suffix)) \
  __MATHCALL (function, suffix, args)

#define __MATHDECL_VEC(type, function,suffix, args) \
  __SIMD_DECL (__MATH_PRECNAME (function, suffix)) \
  __MATHDECL(type, function,suffix, args)

#define __MATHCALL(function,suffix, args)	\
  __MATHDECL (_Mdouble_,function,suffix, args)
#define __MATHDECL(type, function,suffix, args) \
  __MATHDECL_1(type, function,suffix, args); \
  __MATHDECL_1(type, __CONCAT(__,function),suffix, args)
#define __MATHCALLX(function,suffix, args, attrib)	\
  __MATHDECLX (_Mdouble_,function,suffix, args, attrib)
#define __MATHDECLX(type, function,suffix, args, attrib) \
  __MATHDECL_1(type, function,suffix, args) __attribute__ (attrib); \
  __MATHDECL_1(type, __CONCAT(__,function),suffix, args) __attribute__ (attrib)
#define __MATHDECL_1(type, function,suffix, args) \
  extern type __MATH_PRECNAME(function,suffix) args __THROW

#define _Mdouble_		double
#define __MATH_PRECNAME(name,r)	__CONCAT(name,r)
#define __MATH_DECLARING_DOUBLE  1
#define _Mdouble_BEGIN_NAMESPACE __BEGIN_NAMESPACE_STD
#define _Mdouble_END_NAMESPACE   __END_NAMESPACE_STD
#if 0 /* expanded by -frewrite-includes */
#include <bits/mathcalls.h>
#endif /* expanded by -frewrite-includes */
# 83 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 1 3 4
/* Prototype declarations for math functions; helper file for <math.h>.
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

/* NOTE: Because of the special way this file is used by <math.h>, this
   file must NOT be protected from multiple inclusion as header files
   usually are.

   This file provides prototype declarations for the math functions.
   Most functions are declared using the macro:

   __MATHCALL (NAME,[_r], (ARGS...));

   This means there is a function `NAME' returning `double' and a function
   `NAMEf' returning `float'.  Each place `_Mdouble_' appears in the
   prototype, that is actually `double' in the prototype for `NAME' and
   `float' in the prototype for `NAMEf'.  Reentrant variant functions are
   called `NAME_r' and `NAMEf_r'.

   Functions returning other types like `int' are declared using the macro:

   __MATHDECL (TYPE, NAME,[_r], (ARGS...));

   This is just like __MATHCALL but for a function returning `TYPE'
   instead of `_Mdouble_'.  In all of these cases, there is still
   both a `NAME' and a `NAMEf' that takes `float' arguments.

   Note that there must be no whitespace before the argument passed for
   NAME, to make token pasting work with -traditional.  */

#ifndef _MATH_H
# error "Never include <bits/mathcalls.h> directly; include <math.h> instead."
#endif
# 48 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4


/* Trigonometric functions.  */

_Mdouble_BEGIN_NAMESPACE
/* Arc cosine of X.  */
__MATHCALL (acos,, (_Mdouble_ __x));
/* Arc sine of X.  */
__MATHCALL (asin,, (_Mdouble_ __x));
/* Arc tangent of X.  */
__MATHCALL (atan,, (_Mdouble_ __x));
/* Arc tangent of Y/X.  */
__MATHCALL (atan2,, (_Mdouble_ __y, _Mdouble_ __x));

/* Cosine of X.  */
__MATHCALL_VEC (cos,, (_Mdouble_ __x));
/* Sine of X.  */
__MATHCALL_VEC (sin,, (_Mdouble_ __x));
/* Tangent of X.  */
__MATHCALL (tan,, (_Mdouble_ __x));

/* Hyperbolic functions.  */

/* Hyperbolic cosine of X.  */
__MATHCALL (cosh,, (_Mdouble_ __x));
/* Hyperbolic sine of X.  */
__MATHCALL (sinh,, (_Mdouble_ __x));
/* Hyperbolic tangent of X.  */
__MATHCALL (tanh,, (_Mdouble_ __x));
_Mdouble_END_NAMESPACE

#ifdef __USE_GNU
/* Cosine and sine of X.  */
__MATHDECL_VEC (void,sincos,,
		(_Mdouble_ __x, _Mdouble_ *__sinx, _Mdouble_ *__cosx));
#endif
# 84 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#if defined __USE_XOPEN_EXTENDED || defined __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Hyperbolic arc cosine of X.  */
__MATHCALL (acosh,, (_Mdouble_ __x));
/* Hyperbolic arc sine of X.  */
__MATHCALL (asinh,, (_Mdouble_ __x));
/* Hyperbolic arc tangent of X.  */
__MATHCALL (atanh,, (_Mdouble_ __x));
__END_NAMESPACE_C99
#endif
# 95 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

/* Exponential and logarithmic functions.  */

_Mdouble_BEGIN_NAMESPACE
/* Exponential function of X.  */
__MATHCALL_VEC (exp,, (_Mdouble_ __x));

/* Break VALUE into a normalized fraction and an integral power of 2.  */
__MATHCALL (frexp,, (_Mdouble_ __x, int *__exponent));

/* X times (two to the EXP power).  */
__MATHCALL (ldexp,, (_Mdouble_ __x, int __exponent));

/* Natural logarithm of X.  */
__MATHCALL_VEC (log,, (_Mdouble_ __x));

/* Base-ten logarithm of X.  */
__MATHCALL (log10,, (_Mdouble_ __x));

/* Break VALUE into integral and fractional parts.  */
__MATHCALL (modf,, (_Mdouble_ __x, _Mdouble_ *__iptr)) __nonnull ((2));
_Mdouble_END_NAMESPACE

#ifdef __USE_GNU
/* A function missing in all standards: compute exponent to base ten.  */
__MATHCALL (exp10,, (_Mdouble_ __x));
/* Another name occasionally used.  */
__MATHCALL (pow10,, (_Mdouble_ __x));
#endif
# 124 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#if defined __USE_XOPEN_EXTENDED || defined __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Return exp(X) - 1.  */
__MATHCALL (expm1,, (_Mdouble_ __x));

/* Return log(1 + X).  */
__MATHCALL (log1p,, (_Mdouble_ __x));

/* Return the base 2 signed integral exponent of X.  */
__MATHCALL (logb,, (_Mdouble_ __x));
__END_NAMESPACE_C99
#endif
# 137 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#ifdef __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Compute base-2 exponential of X.  */
__MATHCALL (exp2,, (_Mdouble_ __x));

/* Compute base-2 logarithm of X.  */
__MATHCALL (log2,, (_Mdouble_ __x));
__END_NAMESPACE_C99
#endif
# 147 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4


/* Power functions.  */

_Mdouble_BEGIN_NAMESPACE
/* Return X to the Y power.  */
__MATHCALL_VEC (pow,, (_Mdouble_ __x, _Mdouble_ __y));

/* Return the square root of X.  */
__MATHCALL (sqrt,, (_Mdouble_ __x));
_Mdouble_END_NAMESPACE

#if defined __USE_XOPEN || defined __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Return `sqrt(X*X + Y*Y)'.  */
__MATHCALL (hypot,, (_Mdouble_ __x, _Mdouble_ __y));
__END_NAMESPACE_C99
#endif
# 165 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#if defined __USE_XOPEN_EXTENDED || defined __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Return the cube root of X.  */
__MATHCALL (cbrt,, (_Mdouble_ __x));
__END_NAMESPACE_C99
#endif
# 172 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4


/* Nearest integer, absolute value, and remainder functions.  */

_Mdouble_BEGIN_NAMESPACE
/* Smallest integral value not less than X.  */
__MATHCALLX (ceil,, (_Mdouble_ __x), (__const__));

/* Absolute value of X.  */
__MATHCALLX (fabs,, (_Mdouble_ __x), (__const__));

/* Largest integer not greater than X.  */
__MATHCALLX (floor,, (_Mdouble_ __x), (__const__));

/* Floating-point modulo remainder of X/Y.  */
__MATHCALL (fmod,, (_Mdouble_ __x, _Mdouble_ __y));


/* Return 0 if VALUE is finite or NaN, +1 if it
   is +Infinity, -1 if it is -Infinity.  */
__MATHDECL_1 (int,__isinf,, (_Mdouble_ __value)) __attribute__ ((__const__));

/* Return nonzero if VALUE is finite and not NaN.  */
__MATHDECL_1 (int,__finite,, (_Mdouble_ __value)) __attribute__ ((__const__));
_Mdouble_END_NAMESPACE

#ifdef __USE_MISC
# if (!defined __cplusplus \
      || __cplusplus < 201103L /* isinf conflicts with C++11.  */ \
      || __MATH_DECLARING_DOUBLE == 0) /* isinff or isinfl don't.  */
/* Return 0 if VALUE is finite or NaN, +1 if it
   is +Infinity, -1 if it is -Infinity.  */
__MATHDECL_1 (int,isinf,, (_Mdouble_ __value)) __attribute__ ((__const__));
# endif
# 206 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

/* Return nonzero if VALUE is finite and not NaN.  */
__MATHDECL_1 (int,finite,, (_Mdouble_ __value)) __attribute__ ((__const__));

/* Return the remainder of X/Y.  */
__MATHCALL (drem,, (_Mdouble_ __x, _Mdouble_ __y));


/* Return the fractional part of X after dividing out `ilogb (X)'.  */
__MATHCALL (significand,, (_Mdouble_ __x));
#endif /* Use misc.  */
# 217 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#ifdef __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Return X with its signed changed to Y's.  */
__MATHCALLX (copysign,, (_Mdouble_ __x, _Mdouble_ __y), (__const__));
__END_NAMESPACE_C99
#endif
# 224 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#ifdef __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Return representation of qNaN for double type.  */
__MATHCALLX (nan,, (const char *__tagb), (__const__));
__END_NAMESPACE_C99
#endif
# 231 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4


/* Return nonzero if VALUE is not a number.  */
__MATHDECL_1 (int,__isnan,, (_Mdouble_ __value)) __attribute__ ((__const__));

#if defined __USE_MISC || (defined __USE_XOPEN && !defined __USE_XOPEN2K)
# if (!defined __cplusplus \
      || __cplusplus < 201103L /* isnan conflicts with C++11.  */ \
      || __MATH_DECLARING_DOUBLE == 0) /* isnanf or isnanl don't.  */
/* Return nonzero if VALUE is not a number.  */
__MATHDECL_1 (int,isnan,, (_Mdouble_ __value)) __attribute__ ((__const__));
# endif
# 243 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
#endif
# 244 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#if defined __USE_MISC || (defined __USE_XOPEN && __MATH_DECLARING_DOUBLE)
/* Bessel functions.  */
__MATHCALL (j0,, (_Mdouble_));
__MATHCALL (j1,, (_Mdouble_));
__MATHCALL (jn,, (int, _Mdouble_));
__MATHCALL (y0,, (_Mdouble_));
__MATHCALL (y1,, (_Mdouble_));
__MATHCALL (yn,, (int, _Mdouble_));
#endif
# 254 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4


#if defined __USE_XOPEN || defined __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Error and gamma functions.  */
__MATHCALL (erf,, (_Mdouble_));
__MATHCALL (erfc,, (_Mdouble_));
__MATHCALL (lgamma,, (_Mdouble_));
__END_NAMESPACE_C99
#endif
# 264 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#ifdef __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* True gamma function.  */
__MATHCALL (tgamma,, (_Mdouble_));
__END_NAMESPACE_C99
#endif
# 271 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#if defined __USE_MISC || (defined __USE_XOPEN && !defined __USE_XOPEN2K)
/* Obsolete alias for `lgamma'.  */
__MATHCALL (gamma,, (_Mdouble_));
#endif
# 276 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#ifdef __USE_MISC
/* Reentrant version of lgamma.  This function uses the global variable
   `signgam'.  The reentrant version instead takes a pointer and stores
   the value through it.  */
__MATHCALL (lgamma,_r, (_Mdouble_, int *__signgamp));
#endif
# 283 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4


#if defined __USE_XOPEN_EXTENDED || defined __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Return the integer nearest X in the direction of the
   prevailing rounding mode.  */
__MATHCALL (rint,, (_Mdouble_ __x));

/* Return X + epsilon if X < Y, X - epsilon if X > Y.  */
__MATHCALLX (nextafter,, (_Mdouble_ __x, _Mdouble_ __y), (__const__));
# if defined __USE_ISOC99 && !defined __LDBL_COMPAT
__MATHCALLX (nexttoward,, (_Mdouble_ __x, long double __y), (__const__));
# endif
# 296 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

/* Return the remainder of integer divison X / Y with infinite precision.  */
__MATHCALL (remainder,, (_Mdouble_ __x, _Mdouble_ __y));

# ifdef __USE_ISOC99
/* Return X times (2 to the Nth power).  */
__MATHCALL (scalbn,, (_Mdouble_ __x, int __n));
# endif
# 304 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

/* Return the binary exponent of X, which must be nonzero.  */
__MATHDECL (int,ilogb,, (_Mdouble_ __x));
#endif
# 308 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#ifdef __USE_ISOC99
/* Return X times (2 to the Nth power).  */
__MATHCALL (scalbln,, (_Mdouble_ __x, long int __n));

/* Round X to integral value in floating-point format using current
   rounding direction, but do not raise inexact exception.  */
__MATHCALL (nearbyint,, (_Mdouble_ __x));

/* Round X to nearest integral value, rounding halfway cases away from
   zero.  */
__MATHCALLX (round,, (_Mdouble_ __x), (__const__));

/* Round X to the integral value in floating-point format nearest but
   not larger in magnitude.  */
__MATHCALLX (trunc,, (_Mdouble_ __x), (__const__));

/* Compute remainder of X and Y and put in *QUO a value with sign of x/y
   and magnitude congruent `mod 2^n' to the magnitude of the integral
   quotient x/y, with n >= 3.  */
__MATHCALL (remquo,, (_Mdouble_ __x, _Mdouble_ __y, int *__quo));


/* Conversion functions.  */

/* Round X to nearest integral value according to current rounding
   direction.  */
__MATHDECL (long int,lrint,, (_Mdouble_ __x));
__extension__
__MATHDECL (long long int,llrint,, (_Mdouble_ __x));

/* Round X to nearest integral value, rounding halfway cases away from
   zero.  */
__MATHDECL (long int,lround,, (_Mdouble_ __x));
__extension__
__MATHDECL (long long int,llround,, (_Mdouble_ __x));


/* Return positive difference between X and Y.  */
__MATHCALL (fdim,, (_Mdouble_ __x, _Mdouble_ __y));

/* Return maximum numeric value from X and Y.  */
__MATHCALLX (fmax,, (_Mdouble_ __x, _Mdouble_ __y), (__const__));

/* Return minimum numeric value from X and Y.  */
__MATHCALLX (fmin,, (_Mdouble_ __x, _Mdouble_ __y), (__const__));


/* Classify given number.  */
__MATHDECL_1 (int, __fpclassify,, (_Mdouble_ __value))
     __attribute__ ((__const__));

/* Test for negative number.  */
__MATHDECL_1 (int, __signbit,, (_Mdouble_ __value))
     __attribute__ ((__const__));


/* Multiply-add function computed as a ternary operation.  */
__MATHCALL (fma,, (_Mdouble_ __x, _Mdouble_ __y, _Mdouble_ __z));
#endif /* Use ISO C99.  */
# 368 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#if defined __USE_XOPEN_EXTENDED || defined __USE_ISOC99
__END_NAMESPACE_C99
#endif
# 372 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#ifdef __USE_GNU
/* Test for signaling NaN.  */
__MATHDECL_1 (int, __issignaling,, (_Mdouble_ __value))
     __attribute__ ((__const__));
#endif
# 378 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#if defined __USE_MISC || (defined __USE_XOPEN_EXTENDED \
			   && __MATH_DECLARING_DOUBLE	\
			   && !defined __USE_XOPEN2K8)
/* Return X times (2 to the Nth power).  */
__MATHCALL (scalb,, (_Mdouble_ __x, _Mdouble_ __n));
#endif
# 385 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
# 84 "/usr/include/math.h" 2 3 4
#undef	_Mdouble_
#undef _Mdouble_BEGIN_NAMESPACE
#undef _Mdouble_END_NAMESPACE
#undef	__MATH_PRECNAME
#undef __MATH_DECLARING_DOUBLE

#ifdef __USE_ISOC99


/* Include the file of declarations again, this time using `float'
   instead of `double' and appending f to each function name.  */

# ifndef _Mfloat_
#  define _Mfloat_		float
# endif
# 99 "/usr/include/math.h" 3 4
# define _Mdouble_		_Mfloat_
# define __MATH_PRECNAME(name,r) name##f##r
# define __MATH_DECLARING_DOUBLE  0
# define _Mdouble_BEGIN_NAMESPACE __BEGIN_NAMESPACE_C99
# define _Mdouble_END_NAMESPACE   __END_NAMESPACE_C99
#if 0 /* expanded by -frewrite-includes */
# include <bits/mathcalls.h>
#endif /* expanded by -frewrite-includes */
# 104 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 1 3 4
/* Prototype declarations for math functions; helper file for <math.h>.
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

/* NOTE: Because of the special way this file is used by <math.h>, this
   file must NOT be protected from multiple inclusion as header files
   usually are.

   This file provides prototype declarations for the math functions.
   Most functions are declared using the macro:

   __MATHCALL (NAME,[_r], (ARGS...));

   This means there is a function `NAME' returning `double' and a function
   `NAMEf' returning `float'.  Each place `_Mdouble_' appears in the
   prototype, that is actually `double' in the prototype for `NAME' and
   `float' in the prototype for `NAMEf'.  Reentrant variant functions are
   called `NAME_r' and `NAMEf_r'.

   Functions returning other types like `int' are declared using the macro:

   __MATHDECL (TYPE, NAME,[_r], (ARGS...));

   This is just like __MATHCALL but for a function returning `TYPE'
   instead of `_Mdouble_'.  In all of these cases, there is still
   both a `NAME' and a `NAMEf' that takes `float' arguments.

   Note that there must be no whitespace before the argument passed for
   NAME, to make token pasting work with -traditional.  */

#ifndef _MATH_H
# error "Never include <bits/mathcalls.h> directly; include <math.h> instead."
#endif
# 48 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4


/* Trigonometric functions.  */

_Mdouble_BEGIN_NAMESPACE
/* Arc cosine of X.  */
__MATHCALL (acos,, (_Mdouble_ __x));
/* Arc sine of X.  */
__MATHCALL (asin,, (_Mdouble_ __x));
/* Arc tangent of X.  */
__MATHCALL (atan,, (_Mdouble_ __x));
/* Arc tangent of Y/X.  */
__MATHCALL (atan2,, (_Mdouble_ __y, _Mdouble_ __x));

/* Cosine of X.  */
__MATHCALL_VEC (cos,, (_Mdouble_ __x));
/* Sine of X.  */
__MATHCALL_VEC (sin,, (_Mdouble_ __x));
/* Tangent of X.  */
__MATHCALL (tan,, (_Mdouble_ __x));

/* Hyperbolic functions.  */

/* Hyperbolic cosine of X.  */
__MATHCALL (cosh,, (_Mdouble_ __x));
/* Hyperbolic sine of X.  */
__MATHCALL (sinh,, (_Mdouble_ __x));
/* Hyperbolic tangent of X.  */
__MATHCALL (tanh,, (_Mdouble_ __x));
_Mdouble_END_NAMESPACE

#ifdef __USE_GNU
/* Cosine and sine of X.  */
__MATHDECL_VEC (void,sincos,,
		(_Mdouble_ __x, _Mdouble_ *__sinx, _Mdouble_ *__cosx));
#endif
# 84 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#if defined __USE_XOPEN_EXTENDED || defined __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Hyperbolic arc cosine of X.  */
__MATHCALL (acosh,, (_Mdouble_ __x));
/* Hyperbolic arc sine of X.  */
__MATHCALL (asinh,, (_Mdouble_ __x));
/* Hyperbolic arc tangent of X.  */
__MATHCALL (atanh,, (_Mdouble_ __x));
__END_NAMESPACE_C99
#endif
# 95 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

/* Exponential and logarithmic functions.  */

_Mdouble_BEGIN_NAMESPACE
/* Exponential function of X.  */
__MATHCALL_VEC (exp,, (_Mdouble_ __x));

/* Break VALUE into a normalized fraction and an integral power of 2.  */
__MATHCALL (frexp,, (_Mdouble_ __x, int *__exponent));

/* X times (two to the EXP power).  */
__MATHCALL (ldexp,, (_Mdouble_ __x, int __exponent));

/* Natural logarithm of X.  */
__MATHCALL_VEC (log,, (_Mdouble_ __x));

/* Base-ten logarithm of X.  */
__MATHCALL (log10,, (_Mdouble_ __x));

/* Break VALUE into integral and fractional parts.  */
__MATHCALL (modf,, (_Mdouble_ __x, _Mdouble_ *__iptr)) __nonnull ((2));
_Mdouble_END_NAMESPACE

#ifdef __USE_GNU
/* A function missing in all standards: compute exponent to base ten.  */
__MATHCALL (exp10,, (_Mdouble_ __x));
/* Another name occasionally used.  */
__MATHCALL (pow10,, (_Mdouble_ __x));
#endif
# 124 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#if defined __USE_XOPEN_EXTENDED || defined __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Return exp(X) - 1.  */
__MATHCALL (expm1,, (_Mdouble_ __x));

/* Return log(1 + X).  */
__MATHCALL (log1p,, (_Mdouble_ __x));

/* Return the base 2 signed integral exponent of X.  */
__MATHCALL (logb,, (_Mdouble_ __x));
__END_NAMESPACE_C99
#endif
# 137 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#ifdef __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Compute base-2 exponential of X.  */
__MATHCALL (exp2,, (_Mdouble_ __x));

/* Compute base-2 logarithm of X.  */
__MATHCALL (log2,, (_Mdouble_ __x));
__END_NAMESPACE_C99
#endif
# 147 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4


/* Power functions.  */

_Mdouble_BEGIN_NAMESPACE
/* Return X to the Y power.  */
__MATHCALL_VEC (pow,, (_Mdouble_ __x, _Mdouble_ __y));

/* Return the square root of X.  */
__MATHCALL (sqrt,, (_Mdouble_ __x));
_Mdouble_END_NAMESPACE

#if defined __USE_XOPEN || defined __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Return `sqrt(X*X + Y*Y)'.  */
__MATHCALL (hypot,, (_Mdouble_ __x, _Mdouble_ __y));
__END_NAMESPACE_C99
#endif
# 165 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#if defined __USE_XOPEN_EXTENDED || defined __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Return the cube root of X.  */
__MATHCALL (cbrt,, (_Mdouble_ __x));
__END_NAMESPACE_C99
#endif
# 172 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4


/* Nearest integer, absolute value, and remainder functions.  */

_Mdouble_BEGIN_NAMESPACE
/* Smallest integral value not less than X.  */
__MATHCALLX (ceil,, (_Mdouble_ __x), (__const__));

/* Absolute value of X.  */
__MATHCALLX (fabs,, (_Mdouble_ __x), (__const__));

/* Largest integer not greater than X.  */
__MATHCALLX (floor,, (_Mdouble_ __x), (__const__));

/* Floating-point modulo remainder of X/Y.  */
__MATHCALL (fmod,, (_Mdouble_ __x, _Mdouble_ __y));


/* Return 0 if VALUE is finite or NaN, +1 if it
   is +Infinity, -1 if it is -Infinity.  */
__MATHDECL_1 (int,__isinf,, (_Mdouble_ __value)) __attribute__ ((__const__));

/* Return nonzero if VALUE is finite and not NaN.  */
__MATHDECL_1 (int,__finite,, (_Mdouble_ __value)) __attribute__ ((__const__));
_Mdouble_END_NAMESPACE

#ifdef __USE_MISC
# if (!defined __cplusplus \
      || __cplusplus < 201103L /* isinf conflicts with C++11.  */ \
      || __MATH_DECLARING_DOUBLE == 0) /* isinff or isinfl don't.  */
/* Return 0 if VALUE is finite or NaN, +1 if it
   is +Infinity, -1 if it is -Infinity.  */
__MATHDECL_1 (int,isinf,, (_Mdouble_ __value)) __attribute__ ((__const__));
# endif
# 206 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

/* Return nonzero if VALUE is finite and not NaN.  */
__MATHDECL_1 (int,finite,, (_Mdouble_ __value)) __attribute__ ((__const__));

/* Return the remainder of X/Y.  */
__MATHCALL (drem,, (_Mdouble_ __x, _Mdouble_ __y));


/* Return the fractional part of X after dividing out `ilogb (X)'.  */
__MATHCALL (significand,, (_Mdouble_ __x));
#endif /* Use misc.  */
# 217 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#ifdef __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Return X with its signed changed to Y's.  */
__MATHCALLX (copysign,, (_Mdouble_ __x, _Mdouble_ __y), (__const__));
__END_NAMESPACE_C99
#endif
# 224 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#ifdef __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Return representation of qNaN for double type.  */
__MATHCALLX (nan,, (const char *__tagb), (__const__));
__END_NAMESPACE_C99
#endif
# 231 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4


/* Return nonzero if VALUE is not a number.  */
__MATHDECL_1 (int,__isnan,, (_Mdouble_ __value)) __attribute__ ((__const__));

#if defined __USE_MISC || (defined __USE_XOPEN && !defined __USE_XOPEN2K)
# if (!defined __cplusplus \
      || __cplusplus < 201103L /* isnan conflicts with C++11.  */ \
      || __MATH_DECLARING_DOUBLE == 0) /* isnanf or isnanl don't.  */
/* Return nonzero if VALUE is not a number.  */
__MATHDECL_1 (int,isnan,, (_Mdouble_ __value)) __attribute__ ((__const__));
# endif
# 243 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
#endif
# 244 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#if defined __USE_MISC || (defined __USE_XOPEN && __MATH_DECLARING_DOUBLE)
/* Bessel functions.  */
__MATHCALL (j0,, (_Mdouble_));
__MATHCALL (j1,, (_Mdouble_));
__MATHCALL (jn,, (int, _Mdouble_));
__MATHCALL (y0,, (_Mdouble_));
__MATHCALL (y1,, (_Mdouble_));
__MATHCALL (yn,, (int, _Mdouble_));
#endif
# 254 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4


#if defined __USE_XOPEN || defined __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Error and gamma functions.  */
__MATHCALL (erf,, (_Mdouble_));
__MATHCALL (erfc,, (_Mdouble_));
__MATHCALL (lgamma,, (_Mdouble_));
__END_NAMESPACE_C99
#endif
# 264 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#ifdef __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* True gamma function.  */
__MATHCALL (tgamma,, (_Mdouble_));
__END_NAMESPACE_C99
#endif
# 271 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#if defined __USE_MISC || (defined __USE_XOPEN && !defined __USE_XOPEN2K)
/* Obsolete alias for `lgamma'.  */
__MATHCALL (gamma,, (_Mdouble_));
#endif
# 276 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#ifdef __USE_MISC
/* Reentrant version of lgamma.  This function uses the global variable
   `signgam'.  The reentrant version instead takes a pointer and stores
   the value through it.  */
__MATHCALL (lgamma,_r, (_Mdouble_, int *__signgamp));
#endif
# 283 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4


#if defined __USE_XOPEN_EXTENDED || defined __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Return the integer nearest X in the direction of the
   prevailing rounding mode.  */
__MATHCALL (rint,, (_Mdouble_ __x));

/* Return X + epsilon if X < Y, X - epsilon if X > Y.  */
__MATHCALLX (nextafter,, (_Mdouble_ __x, _Mdouble_ __y), (__const__));
# if defined __USE_ISOC99 && !defined __LDBL_COMPAT
__MATHCALLX (nexttoward,, (_Mdouble_ __x, long double __y), (__const__));
# endif
# 296 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

/* Return the remainder of integer divison X / Y with infinite precision.  */
__MATHCALL (remainder,, (_Mdouble_ __x, _Mdouble_ __y));

# ifdef __USE_ISOC99
/* Return X times (2 to the Nth power).  */
__MATHCALL (scalbn,, (_Mdouble_ __x, int __n));
# endif
# 304 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

/* Return the binary exponent of X, which must be nonzero.  */
__MATHDECL (int,ilogb,, (_Mdouble_ __x));
#endif
# 308 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#ifdef __USE_ISOC99
/* Return X times (2 to the Nth power).  */
__MATHCALL (scalbln,, (_Mdouble_ __x, long int __n));

/* Round X to integral value in floating-point format using current
   rounding direction, but do not raise inexact exception.  */
__MATHCALL (nearbyint,, (_Mdouble_ __x));

/* Round X to nearest integral value, rounding halfway cases away from
   zero.  */
__MATHCALLX (round,, (_Mdouble_ __x), (__const__));

/* Round X to the integral value in floating-point format nearest but
   not larger in magnitude.  */
__MATHCALLX (trunc,, (_Mdouble_ __x), (__const__));

/* Compute remainder of X and Y and put in *QUO a value with sign of x/y
   and magnitude congruent `mod 2^n' to the magnitude of the integral
   quotient x/y, with n >= 3.  */
__MATHCALL (remquo,, (_Mdouble_ __x, _Mdouble_ __y, int *__quo));


/* Conversion functions.  */

/* Round X to nearest integral value according to current rounding
   direction.  */
__MATHDECL (long int,lrint,, (_Mdouble_ __x));
__extension__
__MATHDECL (long long int,llrint,, (_Mdouble_ __x));

/* Round X to nearest integral value, rounding halfway cases away from
   zero.  */
__MATHDECL (long int,lround,, (_Mdouble_ __x));
__extension__
__MATHDECL (long long int,llround,, (_Mdouble_ __x));


/* Return positive difference between X and Y.  */
__MATHCALL (fdim,, (_Mdouble_ __x, _Mdouble_ __y));

/* Return maximum numeric value from X and Y.  */
__MATHCALLX (fmax,, (_Mdouble_ __x, _Mdouble_ __y), (__const__));

/* Return minimum numeric value from X and Y.  */
__MATHCALLX (fmin,, (_Mdouble_ __x, _Mdouble_ __y), (__const__));


/* Classify given number.  */
__MATHDECL_1 (int, __fpclassify,, (_Mdouble_ __value))
     __attribute__ ((__const__));

/* Test for negative number.  */
__MATHDECL_1 (int, __signbit,, (_Mdouble_ __value))
     __attribute__ ((__const__));


/* Multiply-add function computed as a ternary operation.  */
__MATHCALL (fma,, (_Mdouble_ __x, _Mdouble_ __y, _Mdouble_ __z));
#endif /* Use ISO C99.  */
# 368 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#if defined __USE_XOPEN_EXTENDED || defined __USE_ISOC99
__END_NAMESPACE_C99
#endif
# 372 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#ifdef __USE_GNU
/* Test for signaling NaN.  */
__MATHDECL_1 (int, __issignaling,, (_Mdouble_ __value))
     __attribute__ ((__const__));
#endif
# 378 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#if defined __USE_MISC || (defined __USE_XOPEN_EXTENDED \
			   && __MATH_DECLARING_DOUBLE	\
			   && !defined __USE_XOPEN2K8)
/* Return X times (2 to the Nth power).  */
__MATHCALL (scalb,, (_Mdouble_ __x, _Mdouble_ __n));
#endif
# 385 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
# 105 "/usr/include/math.h" 2 3 4
# undef	_Mdouble_
# undef _Mdouble_BEGIN_NAMESPACE
# undef _Mdouble_END_NAMESPACE
# undef	__MATH_PRECNAME
# undef __MATH_DECLARING_DOUBLE

# if !(defined __NO_LONG_DOUBLE_MATH && defined _LIBC) \
     || defined __LDBL_COMPAT \
     || defined _LIBC_TEST
#  ifdef __LDBL_COMPAT

#   ifdef __USE_ISOC99
extern float __nldbl_nexttowardf (float __x, long double __y)
				  __THROW __attribute__ ((__const__));
#    ifdef __REDIRECT_NTH
extern float __REDIRECT_NTH (nexttowardf, (float __x, long double __y),
			     __nldbl_nexttowardf)
     __attribute__ ((__const__));
extern double __REDIRECT_NTH (nexttoward, (double __x, long double __y),
			      nextafter) __attribute__ ((__const__));
extern long double __REDIRECT_NTH (nexttowardl,
				   (long double __x, long double __y),
				   nextafter) __attribute__ ((__const__));
#    endif
# 129 "/usr/include/math.h" 3 4
#   endif
# 130 "/usr/include/math.h" 3 4

#   undef __MATHDECL_1
#   define __MATHDECL_2(type, function,suffix, args, alias) \
  extern type __REDIRECT_NTH(__MATH_PRECNAME(function,suffix), \
			     args, alias)
#   define __MATHDECL_1(type, function,suffix, args) \
  __MATHDECL_2(type, function,suffix, args, __CONCAT(function,suffix))
#  endif
# 138 "/usr/include/math.h" 3 4

/* Include the file of declarations again, this time using `long double'
   instead of `double' and appending l to each function name.  */

#  ifndef _Mlong_double_
#   define _Mlong_double_	long double
#  endif
# 145 "/usr/include/math.h" 3 4
#  define _Mdouble_		_Mlong_double_
#  define __MATH_PRECNAME(name,r) name##l##r
#  define __MATH_DECLARING_DOUBLE  0
#  define _Mdouble_BEGIN_NAMESPACE __BEGIN_NAMESPACE_C99
#  define _Mdouble_END_NAMESPACE   __END_NAMESPACE_C99
#  define __MATH_DECLARE_LDOUBLE   1
#if 0 /* expanded by -frewrite-includes */
#  include <bits/mathcalls.h>
#endif /* expanded by -frewrite-includes */
# 151 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 1 3 4
/* Prototype declarations for math functions; helper file for <math.h>.
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

/* NOTE: Because of the special way this file is used by <math.h>, this
   file must NOT be protected from multiple inclusion as header files
   usually are.

   This file provides prototype declarations for the math functions.
   Most functions are declared using the macro:

   __MATHCALL (NAME,[_r], (ARGS...));

   This means there is a function `NAME' returning `double' and a function
   `NAMEf' returning `float'.  Each place `_Mdouble_' appears in the
   prototype, that is actually `double' in the prototype for `NAME' and
   `float' in the prototype for `NAMEf'.  Reentrant variant functions are
   called `NAME_r' and `NAMEf_r'.

   Functions returning other types like `int' are declared using the macro:

   __MATHDECL (TYPE, NAME,[_r], (ARGS...));

   This is just like __MATHCALL but for a function returning `TYPE'
   instead of `_Mdouble_'.  In all of these cases, there is still
   both a `NAME' and a `NAMEf' that takes `float' arguments.

   Note that there must be no whitespace before the argument passed for
   NAME, to make token pasting work with -traditional.  */

#ifndef _MATH_H
# error "Never include <bits/mathcalls.h> directly; include <math.h> instead."
#endif
# 48 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4


/* Trigonometric functions.  */

_Mdouble_BEGIN_NAMESPACE
/* Arc cosine of X.  */
__MATHCALL (acos,, (_Mdouble_ __x));
/* Arc sine of X.  */
__MATHCALL (asin,, (_Mdouble_ __x));
/* Arc tangent of X.  */
__MATHCALL (atan,, (_Mdouble_ __x));
/* Arc tangent of Y/X.  */
__MATHCALL (atan2,, (_Mdouble_ __y, _Mdouble_ __x));

/* Cosine of X.  */
__MATHCALL_VEC (cos,, (_Mdouble_ __x));
/* Sine of X.  */
__MATHCALL_VEC (sin,, (_Mdouble_ __x));
/* Tangent of X.  */
__MATHCALL (tan,, (_Mdouble_ __x));

/* Hyperbolic functions.  */

/* Hyperbolic cosine of X.  */
__MATHCALL (cosh,, (_Mdouble_ __x));
/* Hyperbolic sine of X.  */
__MATHCALL (sinh,, (_Mdouble_ __x));
/* Hyperbolic tangent of X.  */
__MATHCALL (tanh,, (_Mdouble_ __x));
_Mdouble_END_NAMESPACE

#ifdef __USE_GNU
/* Cosine and sine of X.  */
__MATHDECL_VEC (void,sincos,,
		(_Mdouble_ __x, _Mdouble_ *__sinx, _Mdouble_ *__cosx));
#endif
# 84 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#if defined __USE_XOPEN_EXTENDED || defined __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Hyperbolic arc cosine of X.  */
__MATHCALL (acosh,, (_Mdouble_ __x));
/* Hyperbolic arc sine of X.  */
__MATHCALL (asinh,, (_Mdouble_ __x));
/* Hyperbolic arc tangent of X.  */
__MATHCALL (atanh,, (_Mdouble_ __x));
__END_NAMESPACE_C99
#endif
# 95 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

/* Exponential and logarithmic functions.  */

_Mdouble_BEGIN_NAMESPACE
/* Exponential function of X.  */
__MATHCALL_VEC (exp,, (_Mdouble_ __x));

/* Break VALUE into a normalized fraction and an integral power of 2.  */
__MATHCALL (frexp,, (_Mdouble_ __x, int *__exponent));

/* X times (two to the EXP power).  */
__MATHCALL (ldexp,, (_Mdouble_ __x, int __exponent));

/* Natural logarithm of X.  */
__MATHCALL_VEC (log,, (_Mdouble_ __x));

/* Base-ten logarithm of X.  */
__MATHCALL (log10,, (_Mdouble_ __x));

/* Break VALUE into integral and fractional parts.  */
__MATHCALL (modf,, (_Mdouble_ __x, _Mdouble_ *__iptr)) __nonnull ((2));
_Mdouble_END_NAMESPACE

#ifdef __USE_GNU
/* A function missing in all standards: compute exponent to base ten.  */
__MATHCALL (exp10,, (_Mdouble_ __x));
/* Another name occasionally used.  */
__MATHCALL (pow10,, (_Mdouble_ __x));
#endif
# 124 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#if defined __USE_XOPEN_EXTENDED || defined __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Return exp(X) - 1.  */
__MATHCALL (expm1,, (_Mdouble_ __x));

/* Return log(1 + X).  */
__MATHCALL (log1p,, (_Mdouble_ __x));

/* Return the base 2 signed integral exponent of X.  */
__MATHCALL (logb,, (_Mdouble_ __x));
__END_NAMESPACE_C99
#endif
# 137 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#ifdef __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Compute base-2 exponential of X.  */
__MATHCALL (exp2,, (_Mdouble_ __x));

/* Compute base-2 logarithm of X.  */
__MATHCALL (log2,, (_Mdouble_ __x));
__END_NAMESPACE_C99
#endif
# 147 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4


/* Power functions.  */

_Mdouble_BEGIN_NAMESPACE
/* Return X to the Y power.  */
__MATHCALL_VEC (pow,, (_Mdouble_ __x, _Mdouble_ __y));

/* Return the square root of X.  */
__MATHCALL (sqrt,, (_Mdouble_ __x));
_Mdouble_END_NAMESPACE

#if defined __USE_XOPEN || defined __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Return `sqrt(X*X + Y*Y)'.  */
__MATHCALL (hypot,, (_Mdouble_ __x, _Mdouble_ __y));
__END_NAMESPACE_C99
#endif
# 165 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#if defined __USE_XOPEN_EXTENDED || defined __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Return the cube root of X.  */
__MATHCALL (cbrt,, (_Mdouble_ __x));
__END_NAMESPACE_C99
#endif
# 172 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4


/* Nearest integer, absolute value, and remainder functions.  */

_Mdouble_BEGIN_NAMESPACE
/* Smallest integral value not less than X.  */
__MATHCALLX (ceil,, (_Mdouble_ __x), (__const__));

/* Absolute value of X.  */
__MATHCALLX (fabs,, (_Mdouble_ __x), (__const__));

/* Largest integer not greater than X.  */
__MATHCALLX (floor,, (_Mdouble_ __x), (__const__));

/* Floating-point modulo remainder of X/Y.  */
__MATHCALL (fmod,, (_Mdouble_ __x, _Mdouble_ __y));


/* Return 0 if VALUE is finite or NaN, +1 if it
   is +Infinity, -1 if it is -Infinity.  */
__MATHDECL_1 (int,__isinf,, (_Mdouble_ __value)) __attribute__ ((__const__));

/* Return nonzero if VALUE is finite and not NaN.  */
__MATHDECL_1 (int,__finite,, (_Mdouble_ __value)) __attribute__ ((__const__));
_Mdouble_END_NAMESPACE

#ifdef __USE_MISC
# if (!defined __cplusplus \
      || __cplusplus < 201103L /* isinf conflicts with C++11.  */ \
      || __MATH_DECLARING_DOUBLE == 0) /* isinff or isinfl don't.  */
/* Return 0 if VALUE is finite or NaN, +1 if it
   is +Infinity, -1 if it is -Infinity.  */
__MATHDECL_1 (int,isinf,, (_Mdouble_ __value)) __attribute__ ((__const__));
# endif
# 206 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

/* Return nonzero if VALUE is finite and not NaN.  */
__MATHDECL_1 (int,finite,, (_Mdouble_ __value)) __attribute__ ((__const__));

/* Return the remainder of X/Y.  */
__MATHCALL (drem,, (_Mdouble_ __x, _Mdouble_ __y));


/* Return the fractional part of X after dividing out `ilogb (X)'.  */
__MATHCALL (significand,, (_Mdouble_ __x));
#endif /* Use misc.  */
# 217 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#ifdef __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Return X with its signed changed to Y's.  */
__MATHCALLX (copysign,, (_Mdouble_ __x, _Mdouble_ __y), (__const__));
__END_NAMESPACE_C99
#endif
# 224 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#ifdef __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Return representation of qNaN for double type.  */
__MATHCALLX (nan,, (const char *__tagb), (__const__));
__END_NAMESPACE_C99
#endif
# 231 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4


/* Return nonzero if VALUE is not a number.  */
__MATHDECL_1 (int,__isnan,, (_Mdouble_ __value)) __attribute__ ((__const__));

#if defined __USE_MISC || (defined __USE_XOPEN && !defined __USE_XOPEN2K)
# if (!defined __cplusplus \
      || __cplusplus < 201103L /* isnan conflicts with C++11.  */ \
      || __MATH_DECLARING_DOUBLE == 0) /* isnanf or isnanl don't.  */
/* Return nonzero if VALUE is not a number.  */
__MATHDECL_1 (int,isnan,, (_Mdouble_ __value)) __attribute__ ((__const__));
# endif
# 243 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
#endif
# 244 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#if defined __USE_MISC || (defined __USE_XOPEN && __MATH_DECLARING_DOUBLE)
/* Bessel functions.  */
__MATHCALL (j0,, (_Mdouble_));
__MATHCALL (j1,, (_Mdouble_));
__MATHCALL (jn,, (int, _Mdouble_));
__MATHCALL (y0,, (_Mdouble_));
__MATHCALL (y1,, (_Mdouble_));
__MATHCALL (yn,, (int, _Mdouble_));
#endif
# 254 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4


#if defined __USE_XOPEN || defined __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Error and gamma functions.  */
__MATHCALL (erf,, (_Mdouble_));
__MATHCALL (erfc,, (_Mdouble_));
__MATHCALL (lgamma,, (_Mdouble_));
__END_NAMESPACE_C99
#endif
# 264 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#ifdef __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* True gamma function.  */
__MATHCALL (tgamma,, (_Mdouble_));
__END_NAMESPACE_C99
#endif
# 271 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#if defined __USE_MISC || (defined __USE_XOPEN && !defined __USE_XOPEN2K)
/* Obsolete alias for `lgamma'.  */
__MATHCALL (gamma,, (_Mdouble_));
#endif
# 276 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#ifdef __USE_MISC
/* Reentrant version of lgamma.  This function uses the global variable
   `signgam'.  The reentrant version instead takes a pointer and stores
   the value through it.  */
__MATHCALL (lgamma,_r, (_Mdouble_, int *__signgamp));
#endif
# 283 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4


#if defined __USE_XOPEN_EXTENDED || defined __USE_ISOC99
__BEGIN_NAMESPACE_C99
/* Return the integer nearest X in the direction of the
   prevailing rounding mode.  */
__MATHCALL (rint,, (_Mdouble_ __x));

/* Return X + epsilon if X < Y, X - epsilon if X > Y.  */
__MATHCALLX (nextafter,, (_Mdouble_ __x, _Mdouble_ __y), (__const__));
# if defined __USE_ISOC99 && !defined __LDBL_COMPAT
__MATHCALLX (nexttoward,, (_Mdouble_ __x, long double __y), (__const__));
# endif
# 296 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

/* Return the remainder of integer divison X / Y with infinite precision.  */
__MATHCALL (remainder,, (_Mdouble_ __x, _Mdouble_ __y));

# ifdef __USE_ISOC99
/* Return X times (2 to the Nth power).  */
__MATHCALL (scalbn,, (_Mdouble_ __x, int __n));
# endif
# 304 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

/* Return the binary exponent of X, which must be nonzero.  */
__MATHDECL (int,ilogb,, (_Mdouble_ __x));
#endif
# 308 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#ifdef __USE_ISOC99
/* Return X times (2 to the Nth power).  */
__MATHCALL (scalbln,, (_Mdouble_ __x, long int __n));

/* Round X to integral value in floating-point format using current
   rounding direction, but do not raise inexact exception.  */
__MATHCALL (nearbyint,, (_Mdouble_ __x));

/* Round X to nearest integral value, rounding halfway cases away from
   zero.  */
__MATHCALLX (round,, (_Mdouble_ __x), (__const__));

/* Round X to the integral value in floating-point format nearest but
   not larger in magnitude.  */
__MATHCALLX (trunc,, (_Mdouble_ __x), (__const__));

/* Compute remainder of X and Y and put in *QUO a value with sign of x/y
   and magnitude congruent `mod 2^n' to the magnitude of the integral
   quotient x/y, with n >= 3.  */
__MATHCALL (remquo,, (_Mdouble_ __x, _Mdouble_ __y, int *__quo));


/* Conversion functions.  */

/* Round X to nearest integral value according to current rounding
   direction.  */
__MATHDECL (long int,lrint,, (_Mdouble_ __x));
__extension__
__MATHDECL (long long int,llrint,, (_Mdouble_ __x));

/* Round X to nearest integral value, rounding halfway cases away from
   zero.  */
__MATHDECL (long int,lround,, (_Mdouble_ __x));
__extension__
__MATHDECL (long long int,llround,, (_Mdouble_ __x));


/* Return positive difference between X and Y.  */
__MATHCALL (fdim,, (_Mdouble_ __x, _Mdouble_ __y));

/* Return maximum numeric value from X and Y.  */
__MATHCALLX (fmax,, (_Mdouble_ __x, _Mdouble_ __y), (__const__));

/* Return minimum numeric value from X and Y.  */
__MATHCALLX (fmin,, (_Mdouble_ __x, _Mdouble_ __y), (__const__));


/* Classify given number.  */
__MATHDECL_1 (int, __fpclassify,, (_Mdouble_ __value))
     __attribute__ ((__const__));

/* Test for negative number.  */
__MATHDECL_1 (int, __signbit,, (_Mdouble_ __value))
     __attribute__ ((__const__));


/* Multiply-add function computed as a ternary operation.  */
__MATHCALL (fma,, (_Mdouble_ __x, _Mdouble_ __y, _Mdouble_ __z));
#endif /* Use ISO C99.  */
# 368 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#if defined __USE_XOPEN_EXTENDED || defined __USE_ISOC99
__END_NAMESPACE_C99
#endif
# 372 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#ifdef __USE_GNU
/* Test for signaling NaN.  */
__MATHDECL_1 (int, __issignaling,, (_Mdouble_ __value))
     __attribute__ ((__const__));
#endif
# 378 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4

#if defined __USE_MISC || (defined __USE_XOPEN_EXTENDED \
			   && __MATH_DECLARING_DOUBLE	\
			   && !defined __USE_XOPEN2K8)
/* Return X times (2 to the Nth power).  */
__MATHCALL (scalb,, (_Mdouble_ __x, _Mdouble_ __n));
#endif
# 385 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
# 152 "/usr/include/math.h" 2 3 4
#  undef _Mdouble_
#  undef _Mdouble_BEGIN_NAMESPACE
#  undef _Mdouble_END_NAMESPACE
#  undef __MATH_PRECNAME
#  undef __MATH_DECLARING_DOUBLE

# endif /* !(__NO_LONG_DOUBLE_MATH && _LIBC) || __LDBL_COMPAT */
# 159 "/usr/include/math.h" 3 4

#endif	/* Use ISO C99.  */
# 161 "/usr/include/math.h" 3 4
#undef	__MATHDECL_1
#undef	__MATHDECL
#undef	__MATHCALL


#if defined __USE_MISC || defined __USE_XOPEN
/* This variable is used by `gamma' and `lgamma'.  */
extern int signgam;
#endif
# 170 "/usr/include/math.h" 3 4


/* ISO C99 defines some generic macros which work on any data type.  */
#ifdef __USE_ISOC99

/* Get the architecture specific values describing the floating-point
   evaluation.  The following symbols will get defined:

    float_t	floating-point type at least as wide as `float' used
		to evaluate `float' expressions
    double_t	floating-point type at least as wide as `double' used
		to evaluate `double' expressions

    FLT_EVAL_METHOD
		Defined to
		  0	if `float_t' is `float' and `double_t' is `double'
		  1	if `float_t' and `double_t' are `double'
		  2	if `float_t' and `double_t' are `long double'
		  else	`float_t' and `double_t' are unspecified

    INFINITY	representation of the infinity value of type `float'

    FP_FAST_FMA
    FP_FAST_FMAF
    FP_FAST_FMAL
		If defined it indicates that the `fma' function
		generally executes about as fast as a multiply and an add.
		This macro is defined only iff the `fma' function is
		implemented directly with a hardware multiply-add instructions.

    FP_ILOGB0	Expands to a value returned by `ilogb (0.0)'.
    FP_ILOGBNAN	Expands to a value returned by `ilogb (NAN)'.

    DECIMAL_DIG	Number of decimal digits supported by conversion between
		decimal and all internal floating-point formats.

*/

/* All floating-point numbers can be put in one of these categories.  */
enum
  {
    FP_NAN =
# define FP_NAN 0
      FP_NAN,
    FP_INFINITE =
# define FP_INFINITE 1
      FP_INFINITE,
    FP_ZERO =
# define FP_ZERO 2
      FP_ZERO,
    FP_SUBNORMAL =
# define FP_SUBNORMAL 3
      FP_SUBNORMAL,
    FP_NORMAL =
# define FP_NORMAL 4
      FP_NORMAL
  };

/* GCC bug 66462 means we cannot use the math builtins with -fsignaling-nan,
   so disable builtins if this is enabled.  When fixed in a newer GCC,
   the __SUPPORT_SNAN__ check may be skipped for those versions.  */

/* Return number of classification appropriate for X.  */
# if __GNUC_PREREQ (4,4) && !defined __SUPPORT_SNAN__			      \
     && !defined __OPTIMIZE_SIZE__
#  define fpclassify(x) __builtin_fpclassify (FP_NAN, FP_INFINITE,	      \
     FP_NORMAL, FP_SUBNORMAL, FP_ZERO, x)
# elif defined __NO_LONG_DOUBLE_MATH
# 238 "/usr/include/math.h" 3 4
#  define fpclassify(x) \
     (sizeof (x) == sizeof (float) ? __fpclassifyf (x) : __fpclassify (x))
# else
# 241 "/usr/include/math.h" 3 4
#  define fpclassify(x) \
     (sizeof (x) == sizeof (float)					      \
      ? __fpclassifyf (x)						      \
      : sizeof (x) == sizeof (double)					      \
      ? __fpclassify (x) : __fpclassifyl (x))
# endif
# 247 "/usr/include/math.h" 3 4

/* Return nonzero value if sign of X is negative.  */
# if __GNUC_PREREQ (4,0)
#  define signbit(x) \
     (sizeof (x) == sizeof (float)                                            \
      ? __builtin_signbitf (x)                                                        \
      : sizeof (x) == sizeof (double)                                         \
      ? __builtin_signbit (x) : __builtin_signbitl (x))
# else
# 256 "/usr/include/math.h" 3 4
#  ifdef __NO_LONG_DOUBLE_MATH
#   define signbit(x) \
     (sizeof (x) == sizeof (float) ? __signbitf (x) : __signbit (x))
#  else
# 260 "/usr/include/math.h" 3 4
#   define signbit(x) \
     (sizeof (x) == sizeof (float)					      \
      ? __signbitf (x)							      \
      : sizeof (x) == sizeof (double)					      \
      ? __signbit (x) : __signbitl (x))
#  endif
# 266 "/usr/include/math.h" 3 4
# endif
# 267 "/usr/include/math.h" 3 4

/* Return nonzero value if X is not +-Inf or NaN.  */
# if __GNUC_PREREQ (4,4) && !defined __SUPPORT_SNAN__
#  define isfinite(x) __builtin_isfinite (x)
# elif defined __NO_LONG_DOUBLE_MATH
# 272 "/usr/include/math.h" 3 4
#  define isfinite(x) \
     (sizeof (x) == sizeof (float) ? __finitef (x) : __finite (x))
# else
# 275 "/usr/include/math.h" 3 4
#  define isfinite(x) \
     (sizeof (x) == sizeof (float)					      \
      ? __finitef (x)							      \
      : sizeof (x) == sizeof (double)					      \
      ? __finite (x) : __finitel (x))
# endif
# 281 "/usr/include/math.h" 3 4

/* Return nonzero value if X is neither zero, subnormal, Inf, nor NaN.  */
# if __GNUC_PREREQ (4,4) && !defined __SUPPORT_SNAN__
#  define isnormal(x) __builtin_isnormal (x)
# else
# 286 "/usr/include/math.h" 3 4
#  define isnormal(x) (fpclassify (x) == FP_NORMAL)
# endif
# 288 "/usr/include/math.h" 3 4

/* Return nonzero value if X is a NaN.  We could use `fpclassify' but
   we already have this functions `__isnan' and it is faster.  */
# if __GNUC_PREREQ (4,4) && !defined __SUPPORT_SNAN__
#  define isnan(x) __builtin_isnan (x)
# elif defined __NO_LONG_DOUBLE_MATH
# 294 "/usr/include/math.h" 3 4
#  define isnan(x) \
     (sizeof (x) == sizeof (float) ? __isnanf (x) : __isnan (x))
# else
# 297 "/usr/include/math.h" 3 4
#  define isnan(x) \
     (sizeof (x) == sizeof (float)					      \
      ? __isnanf (x)							      \
      : sizeof (x) == sizeof (double)					      \
      ? __isnan (x) : __isnanl (x))
# endif
# 303 "/usr/include/math.h" 3 4

/* Return nonzero value if X is positive or negative infinity.  */
# if __GNUC_PREREQ (4,4) && !defined __SUPPORT_SNAN__
#  define isinf(x) __builtin_isinf_sign (x)
# elif defined __NO_LONG_DOUBLE_MATH
# 308 "/usr/include/math.h" 3 4
#  define isinf(x) \
     (sizeof (x) == sizeof (float) ? __isinff (x) : __isinf (x))
# else
# 311 "/usr/include/math.h" 3 4
#  define isinf(x) \
     (sizeof (x) == sizeof (float)					      \
      ? __isinff (x)							      \
      : sizeof (x) == sizeof (double)					      \
      ? __isinf (x) : __isinfl (x))
# endif
# 317 "/usr/include/math.h" 3 4

/* Bitmasks for the math_errhandling macro.  */
# define MATH_ERRNO	1	/* errno set by math functions.  */
# define MATH_ERREXCEPT	2	/* Exceptions raised by math functions.  */

/* By default all functions support both errno and exception handling.
   In gcc's fast math mode and if inline functions are defined this
   might not be true.  */
# ifndef __FAST_MATH__
#  define math_errhandling	(MATH_ERRNO | MATH_ERREXCEPT)
# endif
# 328 "/usr/include/math.h" 3 4

#endif /* Use ISO C99.  */
# 330 "/usr/include/math.h" 3 4

#ifdef __USE_GNU
/* Return nonzero value if X is a signaling NaN.  */
# ifdef __NO_LONG_DOUBLE_MATH
#  define issignaling(x) \
     (sizeof (x) == sizeof (float) ? __issignalingf (x) : __issignaling (x))
# else
# 337 "/usr/include/math.h" 3 4
#  define issignaling(x) \
     (sizeof (x) == sizeof (float)					      \
      ? __issignalingf (x)						      \
      : sizeof (x) == sizeof (double)					      \
      ? __issignaling (x) : __issignalingl (x))
# endif
# 343 "/usr/include/math.h" 3 4
#endif /* Use GNU.  */
# 344 "/usr/include/math.h" 3 4

#ifdef	__USE_MISC
/* Support for various different standard error handling behaviors.  */
typedef enum
{
  _IEEE_ = -1,	/* According to IEEE 754/IEEE 854.  */
  _SVID_,	/* According to System V, release 4.  */
  _XOPEN_,	/* Nowadays also Unix98.  */
  _POSIX_,
  _ISOC_	/* Actually this is ISO C99.  */
} _LIB_VERSION_TYPE;

/* This variable can be changed at run-time to any of the values above to
   affect floating point error handling behavior (it may also be necessary
   to change the hardware FPU exception settings).  */
extern _LIB_VERSION_TYPE _LIB_VERSION;
#endif
# 361 "/usr/include/math.h" 3 4


#ifdef __USE_MISC
/* In SVID error handling, `matherr' is called with this description
   of the exceptional condition.

   We have a problem when using C++ since `exception' is a reserved
   name in C++.  */
# ifdef __cplusplus
struct __exception
# else
# 372 "/usr/include/math.h" 3 4
struct exception
# endif
# 374 "/usr/include/math.h" 3 4
  {
    int type;
    char *name;
    double arg1;
    double arg2;
    double retval;
  };

# ifdef __cplusplus
extern int matherr (struct __exception *__exc) throw ();
# else
# 385 "/usr/include/math.h" 3 4
extern int matherr (struct exception *__exc);
# endif
# 387 "/usr/include/math.h" 3 4

# define X_TLOSS	1.41484755040568800000e+16

/* Types of exceptions in the `type' field.  */
# define DOMAIN		1
# define SING		2
# define OVERFLOW	3
# define UNDERFLOW	4
# define TLOSS		5
# define PLOSS		6

/* SVID mode specifies returning this large value instead of infinity.  */
# define HUGE		3.40282347e+38F

#else	/* !Misc.  */
# 402 "/usr/include/math.h" 3 4

# ifdef __USE_XOPEN
/* X/Open wants another strange constant.  */
#  define MAXFLOAT	3.40282347e+38F
# endif
# 407 "/usr/include/math.h" 3 4

#endif	/* Misc.  */
# 409 "/usr/include/math.h" 3 4


/* Some useful constants.  */
#if defined __USE_MISC || defined __USE_XOPEN
# define M_E		2.7182818284590452354	/* e */
# define M_LOG2E	1.4426950408889634074	/* log_2 e */
# define M_LOG10E	0.43429448190325182765	/* log_10 e */
# define M_LN2		0.69314718055994530942	/* log_e 2 */
# define M_LN10		2.30258509299404568402	/* log_e 10 */
# define M_PI		3.14159265358979323846	/* pi */
# define M_PI_2		1.57079632679489661923	/* pi/2 */
# define M_PI_4		0.78539816339744830962	/* pi/4 */
# define M_1_PI		0.31830988618379067154	/* 1/pi */
# define M_2_PI		0.63661977236758134308	/* 2/pi */
# define M_2_SQRTPI	1.12837916709551257390	/* 2/sqrt(pi) */
# define M_SQRT2	1.41421356237309504880	/* sqrt(2) */
# define M_SQRT1_2	0.70710678118654752440	/* 1/sqrt(2) */
#endif
# 427 "/usr/include/math.h" 3 4

/* The above constants are not adequate for computation using `long double's.
   Therefore we provide as an extension constants with similar names as a
   GNU extension.  Provide enough digits for the 128-bit IEEE quad.  */
#ifdef __USE_GNU
# define M_El		2.718281828459045235360287471352662498L /* e */
# define M_LOG2El	1.442695040888963407359924681001892137L /* log_2 e */
# define M_LOG10El	0.434294481903251827651128918916605082L /* log_10 e */
# define M_LN2l		0.693147180559945309417232121458176568L /* log_e 2 */
# define M_LN10l	2.302585092994045684017991454684364208L /* log_e 10 */
# define M_PIl		3.141592653589793238462643383279502884L /* pi */
# define M_PI_2l	1.570796326794896619231321691639751442L /* pi/2 */
# define M_PI_4l	0.785398163397448309615660845819875721L /* pi/4 */
# define M_1_PIl	0.318309886183790671537767526745028724L /* 1/pi */
# define M_2_PIl	0.636619772367581343075535053490057448L /* 2/pi */
# define M_2_SQRTPIl	1.128379167095512573896158903121545172L /* 2/sqrt(pi) */
# define M_SQRT2l	1.414213562373095048801688724209698079L /* sqrt(2) */
# define M_SQRT1_2l	0.707106781186547524400844362104849039L /* 1/sqrt(2) */
#endif
# 446 "/usr/include/math.h" 3 4


/* When compiling in strict ISO C compatible mode we must not use the
   inline functions since they, among other things, do not set the
   `errno' variable correctly.  */
#if defined __STRICT_ANSI__ && !defined __NO_MATH_INLINES
# define __NO_MATH_INLINES	1
#endif
# 454 "/usr/include/math.h" 3 4

#if defined __USE_ISOC99 && __GNUC_PREREQ(2,97)
/* ISO C99 defines some macros to compare number while taking care for
   unordered numbers.  Many FPUs provide special instructions to support
   these operations.  Generic support in GCC for these as builtins went
   in before 3.0.0, but not all cpus added their patterns.  We define
   versions that use the builtins here, and <bits/mathinline.h> will
   undef/redefine as appropriate for the specific GCC version in use.  */
# define isgreater(x, y)	__builtin_isgreater(x, y)
# define isgreaterequal(x, y)	__builtin_isgreaterequal(x, y)
# define isless(x, y)		__builtin_isless(x, y)
# define islessequal(x, y)	__builtin_islessequal(x, y)
# define islessgreater(x, y)	__builtin_islessgreater(x, y)
# define isunordered(u, v)	__builtin_isunordered(u, v)
#endif
# 469 "/usr/include/math.h" 3 4

/* Get machine-dependent inline versions (if there are any).  */
#ifdef __USE_EXTERN_INLINES
#if 0 /* expanded by -frewrite-includes */
# include <bits/mathinline.h>
#endif /* expanded by -frewrite-includes */
# 472 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 1 3 4
/* Inline math functions for i387 and SSE.
   Copyright (C) 1995-2016 Free Software Foundation, Inc.
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

#ifndef _MATH_H
# error "Never use <bits/mathinline.h> directly; include <math.h> instead."
#endif
# 22 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4

#ifndef __extern_always_inline
# define __MATH_INLINE __inline
#else
# 26 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
# define __MATH_INLINE __extern_always_inline
#endif
# 28 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4


#if defined __USE_ISOC99 && defined __GNUC__ && __GNUC__ >= 2
/* GCC 2.97 and up have builtins that actually can be used.  */
# if !__GNUC_PREREQ (2,97)
/* ISO C99 defines some macros to perform unordered comparisons.  The
   ix87 FPU supports this with special opcodes and we should use them.
   These must not be inline functions since we have to be able to handle
   all floating-point types.  */
#  undef isgreater
#  undef isgreaterequal
#  undef isless
#  undef islessequal
#  undef islessgreater
#  undef isunordered
#  ifdef __i686__
/* For the PentiumPro and more recent processors we can provide
   better code.  */
#   define isgreater(x, y) \
     ({ register char __result;						      \
	__asm__ ("fucomip %%st(1), %%st; seta %%al"			      \
		 : "=a" (__result) : "u" (y), "t" (x) : "cc", "st");	      \
	__result; })
#   define isgreaterequal(x, y) \
     ({ register char __result;						      \
	__asm__ ("fucomip %%st(1), %%st; setae %%al"			      \
		 : "=a" (__result) : "u" (y), "t" (x) : "cc", "st");	      \
	__result; })

#   define isless(x, y) \
     ({ register char __result;						      \
	__asm__ ("fucomip %%st(1), %%st; seta %%al"			      \
		 : "=a" (__result) : "u" (x), "t" (y) : "cc", "st");	      \
	__result; })

#   define islessequal(x, y) \
     ({ register char __result;						      \
	__asm__ ("fucomip %%st(1), %%st; setae %%al"			      \
		 : "=a" (__result) : "u" (x), "t" (y) : "cc", "st");	      \
	__result; })

#   define islessgreater(x, y) \
     ({ register char __result;						      \
	__asm__ ("fucomip %%st(1), %%st; setne %%al"			      \
		 : "=a" (__result) : "u" (y), "t" (x) : "cc", "st");	      \
	__result; })

#   define isunordered(x, y) \
     ({ register char __result;						      \
	__asm__ ("fucomip %%st(1), %%st; setp %%al"			      \
		 : "=a" (__result) : "u" (y), "t" (x) : "cc", "st");	      \
	__result; })
#  else
# 81 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
/* This is the dumb, portable code for i386 and above.  */
#   define isgreater(x, y) \
     ({ register char __result;						      \
	__asm__ ("fucompp; fnstsw; testb $0x45, %%ah; setz %%al"	      \
		 : "=a" (__result) : "u" (y), "t" (x) : "cc", "st", "st(1)"); \
	__result; })

#   define isgreaterequal(x, y) \
     ({ register char __result;						      \
	__asm__ ("fucompp; fnstsw; testb $0x05, %%ah; setz %%al"	      \
		 : "=a" (__result) : "u" (y), "t" (x) : "cc", "st", "st(1)"); \
	__result; })

#   define isless(x, y) \
     ({ register char __result;						      \
	__asm__ ("fucompp; fnstsw; testb $0x45, %%ah; setz %%al"	      \
		 : "=a" (__result) : "u" (x), "t" (y) : "cc", "st", "st(1)"); \
	__result; })

#   define islessequal(x, y) \
     ({ register char __result;						      \
	__asm__ ("fucompp; fnstsw; testb $0x05, %%ah; setz %%al"	      \
		 : "=a" (__result) : "u" (x), "t" (y) : "cc", "st", "st(1)"); \
	__result; })

#   define islessgreater(x, y) \
     ({ register char __result;						      \
	__asm__ ("fucompp; fnstsw; testb $0x44, %%ah; setz %%al"	      \
		 : "=a" (__result) : "u" (y), "t" (x) : "cc", "st", "st(1)"); \
	__result; })

#   define isunordered(x, y) \
     ({ register char __result;						      \
	__asm__ ("fucompp; fnstsw; sahf; setp %%al"			      \
		 : "=a" (__result) : "u" (y), "t" (x) : "cc", "st", "st(1)"); \
	__result; })
#  endif /* __i686__ */
# 118 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
# endif	/* GCC 2.97 */
# 119 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4

/* The gcc, version 2.7 or below, has problems with all this inlining
   code.  So disable it for this version of the compiler.  */
# if __GNUC_PREREQ (2, 8)
__BEGIN_NAMESPACE_C99

/* Test for negative number.  Used in the signbit() macro.  */
__MATH_INLINE int
__NTH (__signbitf (float __x))
{
#  ifdef __SSE2_MATH__
  int __m;
  __asm ("pmovmskb %1, %0" : "=r" (__m) : "x" (__x));
  return (__m & 0x8) != 0;
#  else
# 134 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
  __extension__ union { float __f; int __i; } __u = { __f: __x };
  return __u.__i < 0;
#  endif
# 137 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
}
__MATH_INLINE int
__NTH (__signbit (double __x))
{
#  ifdef __SSE2_MATH__
  int __m;
  __asm ("pmovmskb %1, %0" : "=r" (__m) : "x" (__x));
  return (__m & 0x80) != 0;
#  else
# 146 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
  __extension__ union { double __d; int __i[2]; } __u = { __d: __x };
  return __u.__i[1] < 0;
#  endif
# 149 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
}
__MATH_INLINE int
__NTH (__signbitl (long double __x))
{
  __extension__ union { long double __l; int __i[3]; } __u = { __l: __x };
  return (__u.__i[2] & 0x8000) != 0;
}

__END_NAMESPACE_C99
# endif
# 159 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
#endif
# 160 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4


/* The gcc, version 2.7 or below, has problems with all this inlining
   code.  So disable it for this version of the compiler.  */
#if __GNUC_PREREQ (2, 8)
# if !__GNUC_PREREQ (3, 4) && !defined __NO_MATH_INLINES \
     && defined __OPTIMIZE__
/* GCC 3.4 introduced builtins for all functions below, so
   there's no need to define any of these inline functions.  */

#  ifdef __USE_ISOC99
__BEGIN_NAMESPACE_C99

/* Round to nearest integer.  */
#   ifdef __SSE_MATH__
__MATH_INLINE long int
__NTH (lrintf (float __x))
{
  long int __res;
  /* Mark as volatile since the result is dependent on the state of
     the SSE control register (the rounding mode).  Otherwise GCC might
     remove these assembler instructions since it does not know about
     the rounding mode change and cannot currently be told.  */
  __asm __volatile__ ("cvtss2si %1, %0" : "=r" (__res) : "xm" (__x));
  return __res;
}
#   endif
# 187 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
#   ifdef __SSE2_MATH__
__MATH_INLINE long int
__NTH (lrint (double __x))
{
  long int __res;
  /* Mark as volatile since the result is dependent on the state of
     the SSE control register (the rounding mode).  Otherwise GCC might
     remove these assembler instructions since it does not know about
     the rounding mode change and cannot currently be told.  */
  __asm __volatile__ ("cvtsd2si %1, %0" : "=r" (__res) : "xm" (__x));
  return __res;
}
#   endif
# 200 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
#   ifdef __x86_64__
__extension__
__MATH_INLINE long long int
__NTH (llrintf (float __x))
{
  long long int __res;
  /* Mark as volatile since the result is dependent on the state of
     the SSE control register (the rounding mode).  Otherwise GCC might
     remove these assembler instructions since it does not know about
     the rounding mode change and cannot currently be told.  */
  __asm __volatile__ ("cvtss2si %1, %0" : "=r" (__res) : "xm" (__x));
  return __res;
}
__extension__
__MATH_INLINE long long int
__NTH (llrint (double __x))
{
  long long int __res;
  /* Mark as volatile since the result is dependent on the state of
     the SSE control register (the rounding mode).  Otherwise GCC might
     remove these assembler instructions since it does not know about
     the rounding mode change and cannot currently be told.  */
  __asm __volatile__ ("cvtsd2si %1, %0" : "=r" (__res) : "xm" (__x));
  return __res;
}
#   endif
# 226 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4

#   if defined __FINITE_MATH_ONLY__ && __FINITE_MATH_ONLY__ > 0 \
       && defined __SSE2_MATH__
/* Determine maximum of two values.  */
__MATH_INLINE float
__NTH (fmaxf (float __x, float __y))
{
#    ifdef __AVX__
  float __res;
  __asm ("vmaxss %2, %1, %0" : "=x" (__res) : "x" (x), "xm" (__y));
  return __res;
#    else
# 238 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
  __asm ("maxss %1, %0" : "+x" (__x) : "xm" (__y));
  return __x;
#    endif
# 241 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
}
__MATH_INLINE double
__NTH (fmax (double __x, double __y))
{
#    ifdef __AVX__
  float __res;
  __asm ("vmaxsd %2, %1, %0" : "=x" (__res) : "x" (x), "xm" (__y));
  return __res;
#    else
# 250 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
  __asm ("maxsd %1, %0" : "+x" (__x) : "xm" (__y));
  return __x;
#    endif
# 253 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
}

/* Determine minimum of two values.  */
__MATH_INLINE float
__NTH (fminf (float __x, float __y))
{
#    ifdef __AVX__
  float __res;
  __asm ("vminss %2, %1, %0" : "=x" (__res) : "x" (x), "xm" (__y));
  return __res;
#    else
# 264 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
  __asm ("minss %1, %0" : "+x" (__x) : "xm" (__y));
  return __x;
#    endif
# 267 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
}
__MATH_INLINE double
__NTH (fmin (double __x, double __y))
{
#    ifdef __AVX__
  float __res;
  __asm ("vminsd %2, %1, %0" : "=x" (__res) : "x" (x), "xm" (__y));
  return __res;
#    else
# 276 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
  __asm ("minsd %1, %0" : "+x" (__x) : "xm" (__y));
  return __x;
#    endif
# 279 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
}
#   endif
# 281 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4

__END_NAMESPACE_C99
#  endif
# 284 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4

#  if defined __SSE4_1__ && defined __SSE2_MATH__
#   if defined __USE_XOPEN_EXTENDED || defined __USE_ISOC99
__BEGIN_NAMESPACE_C99

/* Round to nearest integer.  */
__MATH_INLINE double
__NTH (rint (double __x))
{
  double __res;
  /* Mark as volatile since the result is dependent on the state of
     the SSE control register (the rounding mode).  Otherwise GCC might
     remove these assembler instructions since it does not know about
     the rounding mode change and cannot currently be told.  */
  __asm __volatile__ ("roundsd $4, %1, %0" : "=x" (__res) : "xm" (__x));
  return __res;
}
__MATH_INLINE float
__NTH (rintf (float __x))
{
  float __res;
  /* Mark as volatile since the result is dependent on the state of
     the SSE control register (the rounding mode).  Otherwise GCC might
     remove these assembler instructions since it does not know about
     the rounding mode change and cannot currently be told.  */
  __asm __volatile__ ("roundss $4, %1, %0" : "=x" (__res) : "xm" (__x));
  return __res;
}

#    ifdef __USE_ISOC99
/* Round to nearest integer without raising inexact exception.  */
__MATH_INLINE double
__NTH (nearbyint (double __x))
{
  double __res;
  /* Mark as volatile since the result is dependent on the state of
     the SSE control register (the rounding mode).  Otherwise GCC might
     remove these assembler instructions since it does not know about
     the rounding mode change and cannot currently be told.  */
  __asm __volatile__ ("roundsd $0xc, %1, %0" : "=x" (__res) : "xm" (__x));
  return __res;
}
__MATH_INLINE float
__NTH (nearbyintf (float __x))
{
  float __res;
  /* Mark as volatile since the result is dependent on the state of
     the SSE control register (the rounding mode).  Otherwise GCC might
     remove these assembler instructions since it does not know about
     the rounding mode change and cannot currently be told.  */
  __asm __volatile__ ("roundss $0xc, %1, %0" : "=x" (__res) : "xm" (__x));
  return __res;
}
#    endif
# 338 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4

__END_NAMESPACE_C99
#   endif
# 341 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4

__BEGIN_NAMESPACE_STD
/* Smallest integral value not less than X.  */
__MATH_INLINE double
__NTH (ceil (double __x))
{
  double __res;
  __asm ("roundsd $2, %1, %0" : "=x" (__res) : "xm" (__x));
  return __res;
}
__END_NAMESPACE_STD

__BEGIN_NAMESPACE_C99
__MATH_INLINE float
__NTH (ceilf (float __x))
{
  float __res;
  __asm ("roundss $2, %1, %0" : "=x" (__res) : "xm" (__x));
  return __res;
}
__END_NAMESPACE_C99

__BEGIN_NAMESPACE_STD
/* Largest integer not greater than X.  */
__MATH_INLINE double
__NTH (floor (double __x))
{
  double __res;
  __asm ("roundsd $1, %1, %0" : "=x" (__res) : "xm" (__x));
  return __res;
}
__END_NAMESPACE_STD

__BEGIN_NAMESPACE_C99
__MATH_INLINE float
__NTH (floorf (float __x))
{
  float __res;
  __asm ("roundss $1, %1, %0" : "=x" (__res) : "xm" (__x));
  return __res;
}
__END_NAMESPACE_C99
#  endif
# 384 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
# endif
# 385 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
#endif
# 386 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4

/* Disable x87 inlines when -fpmath=sse is passed and also when we're building
   on x86_64.  Older gcc (gcc-3.2 for example) does not define __SSE2_MATH__
   for x86_64.  */
#if !defined __SSE2_MATH__ && !defined __x86_64__
# if ((!defined __NO_MATH_INLINES || defined __LIBC_INTERNAL_MATH_INLINES) \
     && defined __OPTIMIZE__)

/* The inline functions do not set errno or raise necessarily the
   correct exceptions.  */
#  undef math_errhandling

/* A macro to define float, double, and long double versions of various
   math functions for the ix87 FPU.  FUNC is the function name (which will
   be suffixed with f and l for the float and long double version,
   respectively).  OP is the name of the FPU operation.
   We define two sets of macros.  The set with the additional NP
   doesn't add a prototype declaration.  */

#  ifdef __USE_ISOC99
#   define __inline_mathop(func, op) \
  __inline_mathop_ (double, func, op)					      \
  __inline_mathop_ (float, __CONCAT(func,f), op)			      \
  __inline_mathop_ (long double, __CONCAT(func,l), op)
#   define __inline_mathopNP(func, op) \
  __inline_mathopNP_ (double, func, op)					      \
  __inline_mathopNP_ (float, __CONCAT(func,f), op)			      \
  __inline_mathopNP_ (long double, __CONCAT(func,l), op)
#  else
# 415 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
#   define __inline_mathop(func, op) \
  __inline_mathop_ (double, func, op)
#   define __inline_mathopNP(func, op) \
  __inline_mathopNP_ (double, func, op)
#  endif
# 420 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4

#  define __inline_mathop_(float_type, func, op) \
  __inline_mathop_decl_ (float_type, func, op, "0" (__x))
#  define __inline_mathopNP_(float_type, func, op) \
  __inline_mathop_declNP_ (float_type, func, op, "0" (__x))


#  ifdef __USE_ISOC99
#   define __inline_mathop_decl(func, op, params...) \
  __inline_mathop_decl_ (double, func, op, params)			      \
  __inline_mathop_decl_ (float, __CONCAT(func,f), op, params)		      \
  __inline_mathop_decl_ (long double, __CONCAT(func,l), op, params)
#   define __inline_mathop_declNP(func, op, params...) \
  __inline_mathop_declNP_ (double, func, op, params)			      \
  __inline_mathop_declNP_ (float, __CONCAT(func,f), op, params)		      \
  __inline_mathop_declNP_ (long double, __CONCAT(func,l), op, params)
#  else
# 437 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
#   define __inline_mathop_decl(func, op, params...) \
  __inline_mathop_decl_ (double, func, op, params)
#   define __inline_mathop_declNP(func, op, params...) \
  __inline_mathop_declNP_ (double, func, op, params)
#  endif
# 442 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4

#  define __inline_mathop_decl_(float_type, func, op, params...) \
  __MATH_INLINE float_type func (float_type) __THROW;			      \
  __inline_mathop_declNP_ (float_type, func, op, params)

#  define __inline_mathop_declNP_(float_type, func, op, params...) \
  __MATH_INLINE float_type __NTH (func (float_type __x))		      \
  {									      \
    register float_type __result;					      \
    __asm __volatile__ (op : "=t" (__result) : params);			      \
    return __result;							      \
  }


#  ifdef __USE_ISOC99
#   define __inline_mathcode(func, arg, code) \
  __inline_mathcode_ (double, func, arg, code)				      \
  __inline_mathcode_ (float, __CONCAT(func,f), arg, code)		      \
  __inline_mathcode_ (long double, __CONCAT(func,l), arg, code)
#   define __inline_mathcodeNP(func, arg, code) \
  __inline_mathcodeNP_ (double, func, arg, code)			      \
  __inline_mathcodeNP_ (float, __CONCAT(func,f), arg, code)		      \
  __inline_mathcodeNP_ (long double, __CONCAT(func,l), arg, code)
#   define __inline_mathcode2(func, arg1, arg2, code) \
  __inline_mathcode2_ (double, func, arg1, arg2, code)			      \
  __inline_mathcode2_ (float, __CONCAT(func,f), arg1, arg2, code)	      \
  __inline_mathcode2_ (long double, __CONCAT(func,l), arg1, arg2, code)
#   define __inline_mathcodeNP2(func, arg1, arg2, code) \
  __inline_mathcodeNP2_ (double, func, arg1, arg2, code)		      \
  __inline_mathcodeNP2_ (float, __CONCAT(func,f), arg1, arg2, code)	      \
  __inline_mathcodeNP2_ (long double, __CONCAT(func,l), arg1, arg2, code)
#   define __inline_mathcode3(func, arg1, arg2, arg3, code) \
  __inline_mathcode3_ (double, func, arg1, arg2, arg3, code)		      \
  __inline_mathcode3_ (float, __CONCAT(func,f), arg1, arg2, arg3, code)	      \
  __inline_mathcode3_ (long double, __CONCAT(func,l), arg1, arg2, arg3, code)
#   define __inline_mathcodeNP3(func, arg1, arg2, arg3, code) \
  __inline_mathcodeNP3_ (double, func, arg1, arg2, arg3, code)		      \
  __inline_mathcodeNP3_ (float, __CONCAT(func,f), arg1, arg2, arg3, code)     \
  __inline_mathcodeNP3_ (long double, __CONCAT(func,l), arg1, arg2, arg3, code)
#  else
# 482 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
#   define __inline_mathcode(func, arg, code) \
  __inline_mathcode_ (double, func, (arg), code)
#   define __inline_mathcodeNP(func, arg, code) \
  __inline_mathcodeNP_ (double, func, (arg), code)
#   define __inline_mathcode2(func, arg1, arg2, code) \
  __inline_mathcode2_ (double, func, arg1, arg2, code)
#   define __inline_mathcodeNP2(func, arg1, arg2, code) \
  __inline_mathcodeNP2_ (double, func, arg1, arg2, code)
#   define __inline_mathcode3(func, arg1, arg2, arg3, code) \
  __inline_mathcode3_ (double, func, arg1, arg2, arg3, code)
#   define __inline_mathcodeNP3(func, arg1, arg2, arg3, code) \
  __inline_mathcodeNP3_ (double, func, arg1, arg2, arg3, code)
#  endif
# 495 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4

#  define __inline_mathcode_(float_type, func, arg, code) \
  __MATH_INLINE float_type func (float_type) __THROW;			      \
  __inline_mathcodeNP_(float_type, func, arg, code)

#  define __inline_mathcodeNP_(float_type, func, arg, code) \
  __MATH_INLINE float_type __NTH (func (float_type arg))		      \
  {									      \
    code;								      \
  }


#  define __inline_mathcode2_(float_type, func, arg1, arg2, code) \
  __MATH_INLINE float_type func (float_type, float_type) __THROW;	      \
  __inline_mathcodeNP2_ (float_type, func, arg1, arg2, code)

#  define __inline_mathcodeNP2_(float_type, func, arg1, arg2, code) \
  __MATH_INLINE float_type __NTH (func (float_type arg1, float_type arg2))    \
  {									      \
    code;								      \
  }

#  define __inline_mathcode3_(float_type, func, arg1, arg2, arg3, code) \
  __MATH_INLINE float_type func (float_type, float_type, float_type) __THROW; \
  __inline_mathcodeNP3_(float_type, func, arg1, arg2, arg3, code)

#  define __inline_mathcodeNP3_(float_type, func, arg1, arg2, arg3, code) \
  __MATH_INLINE float_type __NTH (func (float_type arg1, float_type arg2,     \
					float_type arg3))		      \
  {									      \
    code;								      \
  }
# endif
# 528 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4


# if !defined __NO_MATH_INLINES && defined __OPTIMIZE__
/* Miscellaneous functions  */

/* __FAST_MATH__ is defined by gcc -ffast-math.  */
#  ifdef __FAST_MATH__
#   ifdef __USE_GNU
#    define __sincos_code \
  register long double __cosr;						      \
  register long double __sinr;						      \
  register unsigned int __swtmp;					      \
  __asm __volatile__							      \
    ("fsincos\n\t"							      \
     "fnstsw	%w2\n\t"						      \
     "testl	$0x400, %2\n\t"						      \
     "jz	1f\n\t"							      \
     "fldpi\n\t"							      \
     "fadd	%%st(0)\n\t"						      \
     "fxch	%%st(1)\n\t"						      \
     "2: fprem1\n\t"							      \
     "fnstsw	%w2\n\t"						      \
     "testl	$0x400, %2\n\t"						      \
     "jnz	2b\n\t"							      \
     "fstp	%%st(1)\n\t"						      \
     "fsincos\n\t"							      \
     "1:"								      \
     : "=t" (__cosr), "=u" (__sinr), "=a" (__swtmp) : "0" (__x));	      \
  *__sinx = __sinr;							      \
  *__cosx = __cosr

__MATH_INLINE void
__NTH (__sincos (double __x, double *__sinx, double *__cosx))
{
  __sincos_code;
}

__MATH_INLINE void
__NTH (__sincosf (float __x, float *__sinx, float *__cosx))
{
  __sincos_code;
}

__MATH_INLINE void
__NTH (__sincosl (long double __x, long double *__sinx, long double *__cosx))
{
  __sincos_code;
}
#   endif
# 577 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4


/* Optimized inline implementation, sometimes with reduced precision
   and/or argument range.  */

#   if __GNUC_PREREQ (3, 5)
#    define __expm1_code \
  register long double __temp;						      \
  __temp = __builtin_expm1l (__x);					      \
  return __temp ? __temp : __x
#   else
# 588 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
#    define __expm1_code \
  register long double __value;						      \
  register long double __exponent;					      \
  register long double __temp;						      \
  __asm __volatile__							      \
    ("fldl2e			# e^x - 1 = 2^(x * log2(e)) - 1\n\t"	      \
     "fmul	%%st(1)		# x * log2(e)\n\t"			      \
     "fst	%%st(1)\n\t"						      \
     "frndint			# int(x * log2(e))\n\t"			      \
     "fxch\n\t"								      \
     "fsub	%%st(1)		# fract(x * log2(e))\n\t"		      \
     "f2xm1			# 2^(fract(x * log2(e))) - 1\n\t"	      \
     "fscale			# 2^(x * log2(e)) - 2^(int(x * log2(e)))\n\t" \
     : "=t" (__value), "=u" (__exponent) : "0" (__x));			      \
  __asm __volatile__							      \
    ("fscale			# 2^int(x * log2(e))\n\t"		      \
     : "=t" (__temp) : "0" (1.0), "u" (__exponent));			      \
  __temp -= 1.0;							      \
  __temp += __value;							      \
  return __temp ? __temp : __x
#   endif
# 609 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
__inline_mathcodeNP_ (long double, __expm1l, __x, __expm1_code)

#   if __GNUC_PREREQ (3, 4)
__inline_mathcodeNP_ (long double, __expl, __x, return __builtin_expl (__x))
#   else
# 614 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
#    define __exp_code \
  register long double __value;						      \
  register long double __exponent;					      \
  __asm __volatile__							      \
    ("fldl2e			# e^x = 2^(x * log2(e))\n\t"		      \
     "fmul	%%st(1)		# x * log2(e)\n\t"			      \
     "fst	%%st(1)\n\t"						      \
     "frndint			# int(x * log2(e))\n\t"			      \
     "fxch\n\t"								      \
     "fsub	%%st(1)		# fract(x * log2(e))\n\t"		      \
     "f2xm1			# 2^(fract(x * log2(e))) - 1\n\t"	      \
     : "=t" (__value), "=u" (__exponent) : "0" (__x));			      \
  __value += 1.0;							      \
  __asm __volatile__							      \
    ("fscale"								      \
     : "=t" (__value) : "0" (__value), "u" (__exponent));		      \
  return __value
__inline_mathcodeNP (exp, __x, __exp_code)
__inline_mathcodeNP_ (long double, __expl, __x, __exp_code)
#   endif
# 634 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4


#   if !__GNUC_PREREQ (3, 5)
__inline_mathcodeNP (tan, __x, \
  register long double __value;						      \
  register long double __value2 __attribute__ ((__unused__));		      \
  __asm __volatile__							      \
    ("fptan"								      \
     : "=t" (__value2), "=u" (__value) : "0" (__x));			      \
  return __value)
#   endif
# 645 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
#  endif /* __FAST_MATH__ */
# 646 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4


#  if __GNUC_PREREQ (3, 4)
__inline_mathcodeNP2_ (long double, __atan2l, __y, __x,
		       return __builtin_atan2l (__y, __x))
#  else
# 652 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
#   define __atan2_code \
  register long double __value;						      \
  __asm __volatile__							      \
    ("fpatan"								      \
     : "=t" (__value) : "0" (__x), "u" (__y) : "st(1)");		      \
  return __value
#   ifdef __FAST_MATH__
__inline_mathcodeNP2 (atan2, __y, __x, __atan2_code)
#   endif
# 661 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
__inline_mathcodeNP2_ (long double, __atan2l, __y, __x, __atan2_code)
#  endif
# 663 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4


#  if defined __FAST_MATH__ && !__GNUC_PREREQ (3, 5)
__inline_mathcodeNP2 (fmod, __x, __y, \
  register long double __value;						      \
  __asm __volatile__							      \
    ("1:	fprem\n\t"						      \
     "fnstsw	%%ax\n\t"						      \
     "sahf\n\t"								      \
     "jp	1b"							      \
     : "=t" (__value) : "0" (__x), "u" (__y) : "ax", "cc");		      \
  return __value)
#  endif
# 676 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4


#  ifdef __FAST_MATH__
#   if !__GNUC_PREREQ (3,3)
__inline_mathopNP (sqrt, "fsqrt")
__inline_mathopNP_ (long double, __sqrtl, "fsqrt")
#    define __libc_sqrtl(n) __sqrtl (n)
#   else
# 684 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
#    define __libc_sqrtl(n) __builtin_sqrtl (n)
#   endif
# 686 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
#  endif
# 687 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4

#  if __GNUC_PREREQ (2, 8)
__inline_mathcodeNP_ (double, fabs, __x, return __builtin_fabs (__x))
#   ifdef __USE_ISOC99
__inline_mathcodeNP_ (float, fabsf, __x, return __builtin_fabsf (__x))
__inline_mathcodeNP_ (long double, fabsl, __x, return __builtin_fabsl (__x))
#   endif
# 694 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
__inline_mathcodeNP_ (long double, __fabsl, __x, return __builtin_fabsl (__x))
#  else
# 696 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
__inline_mathop (fabs, "fabs")
__inline_mathop_ (long double, __fabsl, "fabs")
# endif
# 699 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4

#  ifdef __FAST_MATH__
#   if !__GNUC_PREREQ (3, 4)
/* The argument range of this inline version is reduced.  */
__inline_mathopNP (sin, "fsin")
/* The argument range of this inline version is reduced.  */
__inline_mathopNP (cos, "fcos")

__inline_mathop_declNP (log, "fldln2; fxch; fyl2x", "0" (__x) : "st(1)")
#   endif
# 709 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4

#   if !__GNUC_PREREQ (3, 5)
__inline_mathop_declNP (log10, "fldlg2; fxch; fyl2x", "0" (__x) : "st(1)")

__inline_mathcodeNP (asin, __x, return __atan2l (__x, __libc_sqrtl (1.0 - __x * __x)))
__inline_mathcodeNP (acos, __x, return __atan2l (__libc_sqrtl (1.0 - __x * __x), __x))
#   endif
# 716 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4

#   if !__GNUC_PREREQ (3, 4)
__inline_mathop_declNP (atan, "fld1; fpatan", "0" (__x) : "st(1)")
#   endif
# 720 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
#  endif /* __FAST_MATH__ */
# 721 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4

__inline_mathcode_ (long double, __sgn1l, __x, \
  __extension__ union { long double __xld; unsigned int __xi[3]; } __n =      \
    { __xld: __x };							      \
  __n.__xi[2] = (__n.__xi[2] & 0x8000) | 0x3fff;			      \
  __n.__xi[1] = 0x80000000;						      \
  __n.__xi[0] = 0;							      \
  return __n.__xld)


#  ifdef __FAST_MATH__
/* The argument range of the inline version of sinhl is slightly reduced.  */
__inline_mathcodeNP (sinh, __x, \
  register long double __exm1 = __expm1l (__fabsl (__x));		      \
  return 0.5 * (__exm1 / (__exm1 + 1.0) + __exm1) * __sgn1l (__x))

__inline_mathcodeNP (cosh, __x, \
  register long double __ex = __expl (__x);				      \
  return 0.5 * (__ex + 1.0 / __ex))

__inline_mathcodeNP (tanh, __x, \
  register long double __exm1 = __expm1l (-__fabsl (__x + __x));	      \
  return __exm1 / (__exm1 + 2.0) * __sgn1l (-__x))
#  endif
# 745 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4

__inline_mathcodeNP (floor, __x, \
  register long double __value;						      \
  register int __ignore;						      \
  unsigned short int __cw;						      \
  unsigned short int __cwtmp;						      \
  __asm __volatile ("fnstcw %3\n\t"					      \
		    "movzwl %3, %1\n\t"					      \
		    "andl $0xf3ff, %1\n\t"				      \
		    "orl $0x0400, %1\n\t"	/* rounding down */	      \
		    "movw %w1, %2\n\t"					      \
		    "fldcw %2\n\t"					      \
		    "frndint\n\t"					      \
		    "fldcw %3"						      \
		    : "=t" (__value), "=&q" (__ignore), "=m" (__cwtmp),	      \
		      "=m" (__cw)					      \
		    : "0" (__x));					      \
  return __value)

__inline_mathcodeNP (ceil, __x, \
  register long double __value;						      \
  register int __ignore;						      \
  unsigned short int __cw;						      \
  unsigned short int __cwtmp;						      \
  __asm __volatile ("fnstcw %3\n\t"					      \
		    "movzwl %3, %1\n\t"					      \
		    "andl $0xf3ff, %1\n\t"				      \
		    "orl $0x0800, %1\n\t"	/* rounding up */	      \
		    "movw %w1, %2\n\t"					      \
		    "fldcw %2\n\t"					      \
		    "frndint\n\t"					      \
		    "fldcw %3"						      \
		    : "=t" (__value), "=&q" (__ignore), "=m" (__cwtmp),	      \
		      "=m" (__cw)					      \
		    : "0" (__x));					      \
  return __value)

#  ifdef __FAST_MATH__
#   define __ldexp_code \
  register long double __value;						      \
  __asm __volatile__							      \
    ("fscale"								      \
     : "=t" (__value) : "0" (__x), "u" ((long double) __y));		      \
  return __value

__MATH_INLINE double
__NTH (ldexp (double __x, int __y))
{
  __ldexp_code;
}
#  endif
# 796 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4


/* Optimized versions for some non-standardized functions.  */
#  ifdef __USE_ISOC99

#   ifdef __FAST_MATH__
__inline_mathcodeNP (expm1, __x, __expm1_code)

/* We cannot rely on M_SQRT being defined.  So we do it for ourself
   here.  */
#    define __M_SQRT2	1.41421356237309504880L	/* sqrt(2) */

#    if !__GNUC_PREREQ (3, 5)
__inline_mathcodeNP (log1p, __x, \
  register long double __value;						      \
  if (__fabsl (__x) >= 1.0 - 0.5 * __M_SQRT2)				      \
    __value = logl (1.0 + __x);						      \
  else									      \
    __asm __volatile__							      \
      ("fldln2\n\t"							      \
       "fxch\n\t"							      \
       "fyl2xp1"							      \
       : "=t" (__value) : "0" (__x) : "st(1)");				      \
  return __value)
#    endif
# 821 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4


/* The argument range of the inline version of asinhl is slightly reduced.  */
__inline_mathcodeNP (asinh, __x, \
  register long double  __y = __fabsl (__x);				      \
  return (log1pl (__y * __y / (__libc_sqrtl (__y * __y + 1.0) + 1.0) + __y)   \
	  * __sgn1l (__x)))

__inline_mathcodeNP (acosh, __x, \
  return logl (__x + __libc_sqrtl (__x - 1.0) * __libc_sqrtl (__x + 1.0)))

__inline_mathcodeNP (atanh, __x, \
  register long double __y = __fabsl (__x);				      \
  return -0.5 * log1pl (-(__y + __y) / (1.0 + __y)) * __sgn1l (__x))

/* The argument range of the inline version of hypotl is slightly reduced.  */
__inline_mathcodeNP2 (hypot, __x, __y,
		      return __libc_sqrtl (__x * __x + __y * __y))

#    if !__GNUC_PREREQ (3, 5)
__inline_mathcodeNP(logb, __x, \
  register long double __value;						      \
  register long double __junk;						      \
  __asm __volatile__							      \
    ("fxtract\n\t"							      \
     : "=t" (__junk), "=u" (__value) : "0" (__x));			      \
  return __value)
#    endif
# 849 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4

#   endif
# 851 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
#  endif
# 852 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4

#  ifdef __USE_ISOC99
#   ifdef __FAST_MATH__

#    if !__GNUC_PREREQ (3, 5)
__inline_mathop_declNP (log2, "fld1; fxch; fyl2x", "0" (__x) : "st(1)")
#    endif
# 859 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4

__MATH_INLINE float
__NTH (ldexpf (float __x, int __y))
{
  __ldexp_code;
}

__MATH_INLINE long double
__NTH (ldexpl (long double __x, int __y))
{
  __ldexp_code;
}

__inline_mathopNP (rint, "frndint")
#   endif /* __FAST_MATH__ */
# 874 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4

#   define __lrint_code \
  long int __lrintres;							      \
  __asm__ __volatile__							      \
    ("fistpl %0"							      \
     : "=m" (__lrintres) : "t" (__x) : "st");				      \
  return __lrintres
__MATH_INLINE long int
__NTH (lrintf (float __x))
{
  __lrint_code;
}
__MATH_INLINE long int
__NTH (lrint (double __x))
{
  __lrint_code;
}
__MATH_INLINE long int
__NTH (lrintl (long double __x))
{
  __lrint_code;
}
#   undef __lrint_code

#   define __llrint_code \
  long long int __llrintres;						      \
  __asm__ __volatile__							      \
    ("fistpll %0"							      \
     : "=m" (__llrintres) : "t" (__x) : "st");				      \
  return __llrintres
__extension__
__MATH_INLINE long long int
__NTH (llrintf (float __x))
{
  __llrint_code;
}
__extension__
__MATH_INLINE long long int
__NTH (llrint (double __x))
{
  __llrint_code;
}
__extension__
__MATH_INLINE long long int
__NTH (llrintl (long double __x))
{
  __llrint_code;
}
#   undef __llrint_code

# endif
# 925 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4


#  ifdef __USE_MISC

#   if defined __FAST_MATH__ && !__GNUC_PREREQ (3, 5)
__inline_mathcodeNP2 (drem, __x, __y, \
  register double __value;						      \
  register int __clobbered;						      \
  __asm __volatile__							      \
    ("1:	fprem1\n\t"						      \
     "fstsw	%%ax\n\t"						      \
     "sahf\n\t"								      \
     "jp	1b"							      \
     : "=t" (__value), "=&a" (__clobbered) : "0" (__x), "u" (__y) : "cc");    \
  return __value)
#  endif
# 941 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4


/* This function is used in the `isfinite' macro.  */
__MATH_INLINE int
__NTH (__finite (double __x))
{
  return (__extension__
	  (((((union { double __d; int __i[2]; }) {__d: __x}).__i[1]
	     | 0x800fffffu) + 1) >> 31));
}

#  endif /* __USE_MISC  */
# 953 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4

/* Undefine some of the large macros which are not used anymore.  */
#  undef __atan2_code
#  ifdef __FAST_MATH__
#   undef __expm1_code
#   undef __exp_code
#   undef __sincos_code
#  endif /* __FAST_MATH__ */
# 961 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4

# endif /* __NO_MATH_INLINES  */
# 963 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4


/* This code is used internally in the GNU libc.  */
# ifdef __LIBC_INTERNAL_MATH_INLINES
__inline_mathop (__ieee754_sqrt, "fsqrt")
__inline_mathcode2_ (long double, __ieee754_atan2l, __y, __x,
		     register long double __value;
		     __asm __volatile__ ("fpatan\n\t"
					 : "=t" (__value)
					 : "0" (__x), "u" (__y) : "st(1)");
		     return __value;)
# endif
# 975 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4

#endif /* !__SSE2_MATH__ && !__x86_64__ */
# 977 "/usr/include/x86_64-linux-gnu/bits/mathinline.h" 3 4
# 473 "/usr/include/math.h" 2 3 4
#endif
# 474 "/usr/include/math.h" 3 4

/* Define special entry points to use when the compiler got told to
   only expect finite results.  */
#if defined __FINITE_MATH_ONLY__ && __FINITE_MATH_ONLY__ > 0
#if 0 /* expanded by -frewrite-includes */
# include <bits/math-finite.h>
#endif /* expanded by -frewrite-includes */
# 478 "/usr/include/math.h" 3 4
# 479 "/usr/include/math.h" 3 4
#endif
# 480 "/usr/include/math.h" 3 4

#ifdef __USE_ISOC99
/* If we've still got undefined comparison macros, provide defaults.  */

/* Return nonzero value if X is greater than Y.  */
# ifndef isgreater
#  define isgreater(x, y) \
  (__extension__							      \
   ({ __typeof__(x) __x = (x); __typeof__(y) __y = (y);			      \
      !isunordered (__x, __y) && __x > __y; }))
# endif
# 491 "/usr/include/math.h" 3 4

/* Return nonzero value if X is greater than or equal to Y.  */
# ifndef isgreaterequal
#  define isgreaterequal(x, y) \
  (__extension__							      \
   ({ __typeof__(x) __x = (x); __typeof__(y) __y = (y);			      \
      !isunordered (__x, __y) && __x >= __y; }))
# endif
# 499 "/usr/include/math.h" 3 4

/* Return nonzero value if X is less than Y.  */
# ifndef isless
#  define isless(x, y) \
  (__extension__							      \
   ({ __typeof__(x) __x = (x); __typeof__(y) __y = (y);			      \
      !isunordered (__x, __y) && __x < __y; }))
# endif
# 507 "/usr/include/math.h" 3 4

/* Return nonzero value if X is less than or equal to Y.  */
# ifndef islessequal
#  define islessequal(x, y) \
  (__extension__							      \
   ({ __typeof__(x) __x = (x); __typeof__(y) __y = (y);			      \
      !isunordered (__x, __y) && __x <= __y; }))
# endif
# 515 "/usr/include/math.h" 3 4

/* Return nonzero value if either X is less than Y or Y is less than X.  */
# ifndef islessgreater
#  define islessgreater(x, y) \
  (__extension__							      \
   ({ __typeof__(x) __x = (x); __typeof__(y) __y = (y);			      \
      !isunordered (__x, __y) && (__x < __y || __y < __x); }))
# endif
# 523 "/usr/include/math.h" 3 4

/* Return nonzero value if arguments are unordered.  */
# ifndef isunordered
#  define isunordered(u, v) \
  (__extension__							      \
   ({ __typeof__(u) __u = (u); __typeof__(v) __v = (v);			      \
      fpclassify (__u) == FP_NAN || fpclassify (__v) == FP_NAN; }))
# endif
# 531 "/usr/include/math.h" 3 4

#endif
# 533 "/usr/include/math.h" 3 4

__END_DECLS


#endif /* math.h  */
# 538 "/usr/include/math.h" 3 4
# 12 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/covariance.c" 2

/* Include polybench common header. */
#if 0 /* expanded by -frewrite-includes */
#include "../../utilities/polybench.h"
#endif /* expanded by -frewrite-includes */
# 14 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/covariance.c"
# 1 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h" 1
/**
 * polybench.h: This file is part of the PolyBench/C 3.2 test suite.
 *
 *
 * Contact: Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://polybench.sourceforge.net
 */
/*
 * Polybench header for instrumentation.
 *
 * Programs must be compiled with `-I utilities utilities/polybench.c'
 *
 * Optionally, one can define:
 *
 * -DPOLYBENCH_TIME, to report the execution time,
 *   OR (exclusive):
 * -DPOLYBENCH_PAPI, to use PAPI H/W counters (defined in polybench.c)
 *
 *
 * See README or utilities/polybench.c for additional options.
 *
 */
#ifndef POLYBENCH_H
# define POLYBENCH_H

#if 0 /* expanded by -frewrite-includes */
# include <stdlib.h>
#endif /* expanded by -frewrite-includes */
# 26 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
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
# 1 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 1 3 4
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
# 37 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#define __need_ptrdiff_t
#define __need_size_t
#define __need_wchar_t
#define __need_NULL
#define __need_STDDEF_H_misc
/* __need_wint_t is intentionally not defined here. */
#endif
# 44 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_ptrdiff_t)
#if !defined(_PTRDIFF_T) || __has_feature(modules)
/* Always define ptrdiff_t when modules are available. */
#if !__has_feature(modules)
#define _PTRDIFF_T
#endif
# 51 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif
# 53 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_ptrdiff_t
#endif /* defined(__need_ptrdiff_t) */
# 55 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_size_t)
#if !defined(_SIZE_T) || __has_feature(modules)
/* Always define size_t when modules are available. */
#if !__has_feature(modules)
#define _SIZE_T
#endif
# 62 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ size_t;
#endif
# 64 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_size_t
#endif /*defined(__need_size_t) */
# 66 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
/* ISO9899:2011 7.20 (C11 Annex K): Define rsize_t if __STDC_WANT_LIB_EXT1__ is
 * enabled. */
#if (defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ >= 1 && \
     !defined(_RSIZE_T)) || __has_feature(modules)
/* Always define rsize_t when modules are available. */
#if !__has_feature(modules)
#define _RSIZE_T
#endif
# 76 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ rsize_t;
#endif
# 78 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif /* defined(__need_STDDEF_H_misc) */
# 79 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_wchar_t)
#ifndef __cplusplus
/* Always define wchar_t when modules are available. */
#if !defined(_WCHAR_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WCHAR_T
#if defined(_MSC_EXTENSIONS)
#define _WCHAR_T_DEFINED
#endif
# 89 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 90 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WCHAR_TYPE__ wchar_t;
#endif
# 92 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 93 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wchar_t
#endif /* defined(__need_wchar_t) */
# 95 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_NULL)
#undef NULL
#ifdef __cplusplus
#  if !defined(__MINGW32__) && !defined(_MSC_VER)
#    define NULL __null
#  else
# 102 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#    define NULL 0
#  endif
# 104 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#else
# 105 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#  define NULL ((void*)0)
#endif
# 107 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#ifdef __cplusplus
#if defined(_MSC_EXTENSIONS) && defined(_NATIVE_NULLPTR_SUPPORTED)
namespace std { typedef decltype(nullptr) nullptr_t; }
using ::std::nullptr_t;
#endif
# 112 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 113 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_NULL
#endif /* defined(__need_NULL) */
# 115 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
#if __STDC_VERSION__ >= 201112L || __cplusplus >= 201103L
#if 0 /* expanded by -frewrite-includes */
#include "__stddef_max_align_t.h"
#endif /* expanded by -frewrite-includes */
# 118 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
# 119 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 120 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#define offsetof(t, d) __builtin_offsetof(t, d)
#undef __need_STDDEF_H_misc
#endif  /* defined(__need_STDDEF_H_misc) */
# 123 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

/* Some C libraries expect to see a wint_t here. Others (notably MinGW) will use
__WINT_TYPE__ directly; accommodate both by requiring __need_wint_t */
#if defined(__need_wint_t)
/* Always define wint_t when modules are available. */
#if !defined(_WINT_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WINT_T
#endif
# 132 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WINT_TYPE__ wint_t;
#endif
# 134 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wint_t
#endif /* __need_wint_t */
# 136 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#endif
# 138 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
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
# 65 "/usr/include/x86_64-linux-gnu/bits/waitstatus.h" 3 4

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
# 1 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 1 3 4
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
# 37 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#define __need_ptrdiff_t
#define __need_size_t
#define __need_wchar_t
#define __need_NULL
#define __need_STDDEF_H_misc
/* __need_wint_t is intentionally not defined here. */
#endif
# 44 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_ptrdiff_t)
#if !defined(_PTRDIFF_T) || __has_feature(modules)
/* Always define ptrdiff_t when modules are available. */
#if !__has_feature(modules)
#define _PTRDIFF_T
#endif
# 51 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif
# 53 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_ptrdiff_t
#endif /* defined(__need_ptrdiff_t) */
# 55 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_size_t)
#if !defined(_SIZE_T) || __has_feature(modules)
/* Always define size_t when modules are available. */
#if !__has_feature(modules)
#define _SIZE_T
#endif
# 62 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ size_t;
#endif
# 64 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_size_t
#endif /*defined(__need_size_t) */
# 66 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
/* ISO9899:2011 7.20 (C11 Annex K): Define rsize_t if __STDC_WANT_LIB_EXT1__ is
 * enabled. */
#if (defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ >= 1 && \
     !defined(_RSIZE_T)) || __has_feature(modules)
/* Always define rsize_t when modules are available. */
#if !__has_feature(modules)
#define _RSIZE_T
#endif
# 76 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ rsize_t;
#endif
# 78 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif /* defined(__need_STDDEF_H_misc) */
# 79 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_wchar_t)
#ifndef __cplusplus
/* Always define wchar_t when modules are available. */
#if !defined(_WCHAR_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WCHAR_T
#if defined(_MSC_EXTENSIONS)
#define _WCHAR_T_DEFINED
#endif
# 89 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 90 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WCHAR_TYPE__ wchar_t;
#endif
# 92 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 93 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wchar_t
#endif /* defined(__need_wchar_t) */
# 95 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_NULL)
#undef NULL
#ifdef __cplusplus
#  if !defined(__MINGW32__) && !defined(_MSC_VER)
#    define NULL __null
#  else
# 102 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#    define NULL 0
#  endif
# 104 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#else
# 105 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#  define NULL ((void*)0)
#endif
# 107 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#ifdef __cplusplus
#if defined(_MSC_EXTENSIONS) && defined(_NATIVE_NULLPTR_SUPPORTED)
namespace std { typedef decltype(nullptr) nullptr_t; }
using ::std::nullptr_t;
#endif
# 112 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 113 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_NULL
#endif /* defined(__need_NULL) */
# 115 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
#if __STDC_VERSION__ >= 201112L || __cplusplus >= 201103L
#if 0 /* expanded by -frewrite-includes */
#include "__stddef_max_align_t.h"
#endif /* expanded by -frewrite-includes */
# 118 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
# 119 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 120 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#define offsetof(t, d) __builtin_offsetof(t, d)
#undef __need_STDDEF_H_misc
#endif  /* defined(__need_STDDEF_H_misc) */
# 123 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

/* Some C libraries expect to see a wint_t here. Others (notably MinGW) will use
__WINT_TYPE__ directly; accommodate both by requiring __need_wint_t */
#if defined(__need_wint_t)
/* Always define wint_t when modules are available. */
#if !defined(_WINT_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WINT_T
#endif
# 132 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WINT_TYPE__ wint_t;
#endif
# 134 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wint_t
#endif /* __need_wint_t */
# 136 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#endif
# 138 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
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
# 1 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 1 3 4
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
# 37 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#define __need_ptrdiff_t
#define __need_size_t
#define __need_wchar_t
#define __need_NULL
#define __need_STDDEF_H_misc
/* __need_wint_t is intentionally not defined here. */
#endif
# 44 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_ptrdiff_t)
#if !defined(_PTRDIFF_T) || __has_feature(modules)
/* Always define ptrdiff_t when modules are available. */
#if !__has_feature(modules)
#define _PTRDIFF_T
#endif
# 51 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif
# 53 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_ptrdiff_t
#endif /* defined(__need_ptrdiff_t) */
# 55 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_size_t)
#if !defined(_SIZE_T) || __has_feature(modules)
/* Always define size_t when modules are available. */
#if !__has_feature(modules)
#define _SIZE_T
#endif
# 62 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ size_t;
#endif
# 64 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_size_t
#endif /*defined(__need_size_t) */
# 66 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
/* ISO9899:2011 7.20 (C11 Annex K): Define rsize_t if __STDC_WANT_LIB_EXT1__ is
 * enabled. */
#if (defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ >= 1 && \
     !defined(_RSIZE_T)) || __has_feature(modules)
/* Always define rsize_t when modules are available. */
#if !__has_feature(modules)
#define _RSIZE_T
#endif
# 76 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ rsize_t;
#endif
# 78 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif /* defined(__need_STDDEF_H_misc) */
# 79 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_wchar_t)
#ifndef __cplusplus
/* Always define wchar_t when modules are available. */
#if !defined(_WCHAR_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WCHAR_T
#if defined(_MSC_EXTENSIONS)
#define _WCHAR_T_DEFINED
#endif
# 89 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 90 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WCHAR_TYPE__ wchar_t;
#endif
# 92 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 93 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wchar_t
#endif /* defined(__need_wchar_t) */
# 95 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_NULL)
#undef NULL
#ifdef __cplusplus
#  if !defined(__MINGW32__) && !defined(_MSC_VER)
#    define NULL __null
#  else
# 102 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#    define NULL 0
#  endif
# 104 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#else
# 105 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#  define NULL ((void*)0)
#endif
# 107 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#ifdef __cplusplus
#if defined(_MSC_EXTENSIONS) && defined(_NATIVE_NULLPTR_SUPPORTED)
namespace std { typedef decltype(nullptr) nullptr_t; }
using ::std::nullptr_t;
#endif
# 112 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 113 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_NULL
#endif /* defined(__need_NULL) */
# 115 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
#if __STDC_VERSION__ >= 201112L || __cplusplus >= 201103L
#if 0 /* expanded by -frewrite-includes */
#include "__stddef_max_align_t.h"
#endif /* expanded by -frewrite-includes */
# 118 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
# 119 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 120 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#define offsetof(t, d) __builtin_offsetof(t, d)
#undef __need_STDDEF_H_misc
#endif  /* defined(__need_STDDEF_H_misc) */
# 123 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

/* Some C libraries expect to see a wint_t here. Others (notably MinGW) will use
__WINT_TYPE__ directly; accommodate both by requiring __need_wint_t */
#if defined(__need_wint_t)
/* Always define wint_t when modules are available. */
#if !defined(_WINT_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WINT_T
#endif
# 132 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WINT_TYPE__ wint_t;
#endif
# 134 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wint_t
#endif /* __need_wint_t */
# 136 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#endif
# 138 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
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
# 27 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h" 2

/* Array padding. By default, none is used. */
# ifndef POLYBENCH_PADDING_FACTOR
/* default: */
#  define POLYBENCH_PADDING_FACTOR 0
# endif
# 33 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"


/* C99 arrays in function prototype. By default, do not use. */
# ifdef POLYBENCH_USE_C99_PROTO
#  define POLYBENCH_C99_SELECT(x,y) y
# else
# 39 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
/* default: */
#  define POLYBENCH_C99_SELECT(x,y) x
# endif
# 42 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"


/* Scalar loop bounds in SCoPs. By default, use parametric loop bounds. */
# ifdef POLYBENCH_USE_SCALAR_LB
#  define POLYBENCH_LOOP_BOUND(x,y) x
# else
# 48 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
/* default: */
#  define POLYBENCH_LOOP_BOUND(x,y) y
# endif
# 51 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"


/* Macros to reference an array. Generic for heap and stack arrays
   (C99).  Each array dimensionality has his own macro, to be used at
   declaration or as a function argument.
   Example:
   int b[x] => POLYBENCH_1D_ARRAY(b, x)
   int A[N][N] => POLYBENCH_2D_ARRAY(A, N, N)
*/
# ifndef POLYBENCH_STACK_ARRAYS
#  define POLYBENCH_ARRAY(x) *x
#  define POLYBENCH_FREE_ARRAY(x) free((void*)x);
#  define POLYBENCH_DECL_VAR(x) (*x)
# else
# 65 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
#  define POLYBENCH_ARRAY(x) x
#  define POLYBENCH_FREE_ARRAY(x)
#  define POLYBENCH_DECL_VAR(x) x
# endif
# 69 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
/* Macros for using arrays in the function prototypes. */
# define POLYBENCH_1D(var, dim1,ddim1) var[POLYBENCH_C99_SELECT(dim1,ddim1) + POLYBENCH_PADDING_FACTOR]
# define POLYBENCH_2D(var, dim1, dim2, ddim1, ddim2) var[POLYBENCH_C99_SELECT(dim1,ddim1) + POLYBENCH_PADDING_FACTOR][POLYBENCH_C99_SELECT(dim2,ddim2) + POLYBENCH_PADDING_FACTOR]
# define POLYBENCH_3D(var, dim1, dim2, dim3, ddim1, ddim2, ddim3) var[POLYBENCH_C99_SELECT(dim1,ddim1) + POLYBENCH_PADDING_FACTOR][POLYBENCH_C99_SELECT(dim2,ddim2) + POLYBENCH_PADDING_FACTOR][POLYBENCH_C99_SELECT(dim3,ddim3) + POLYBENCH_PADDING_FACTOR]
# define POLYBENCH_4D(var, dim1, dim2, dim3, dim4, ddim1, ddim2, ddim3, ddim4) var[POLYBENCH_C99_SELECT(dim1,ddim1) + POLYBENCH_PADDING_FACTOR][POLYBENCH_C99_SELECT(dim2,ddim2) + POLYBENCH_PADDING_FACTOR][POLYBENCH_C99_SELECT(dim3,ddim3) + POLYBENCH_PADDING_FACTOR][POLYBENCH_C99_SELECT(dim4,ddim4) + POLYBENCH_PADDING_FACTOR]
# define POLYBENCH_5D(var, dim1, dim2, dim3, dim4, dim5, ddim1, ddim2, ddim3, ddim4, ddim5) var[POLYBENCH_C99_SELECT(dim1,ddim1) + POLYBENCH_PADDING_FACTOR][POLYBENCH_C99_SELECT(dim2,ddim2) + POLYBENCH_PADDING_FACTOR][POLYBENCH_C99_SELECT(dim3,ddim3) + POLYBENCH_PADDING_FACTOR][POLYBENCH_C99_SELECT(dim4,ddim4) + POLYBENCH_PADDING_FACTOR][POLYBENCH_C99_SELECT(dim5,ddim5) + POLYBENCH_PADDING_FACTOR]


/* Macros to allocate heap arrays.
   Example:
   polybench_alloc_2d_array(N, M, double) => allocates N x M x sizeof(double)
					  and returns a pointer to the 2d array
 */
# define POLYBENCH_ALLOC_1D_ARRAY(n1, type)	\
  (type(*)[n1 + POLYBENCH_PADDING_FACTOR])polybench_alloc_data (n1 + POLYBENCH_PADDING_FACTOR, sizeof(type))
# define POLYBENCH_ALLOC_2D_ARRAY(n1, n2, type)		\
  (type(*)[n1 + POLYBENCH_PADDING_FACTOR][n2 + POLYBENCH_PADDING_FACTOR])polybench_alloc_data ((n1 + POLYBENCH_PADDING_FACTOR) * (n2 + POLYBENCH_PADDING_FACTOR), sizeof(type))
# define POLYBENCH_ALLOC_3D_ARRAY(n1, n2, n3, type)		\
  (type(*)[n1 + POLYBENCH_PADDING_FACTOR][n2 + POLYBENCH_PADDING_FACTOR][n3 + POLYBENCH_PADDING_FACTOR])polybench_alloc_data ((n1 + POLYBENCH_PADDING_FACTOR) * (n2 + POLYBENCH_PADDING_FACTOR) * (n3 + POLYBENCH_PADDING_FACTOR), sizeof(type))
# define POLYBENCH_ALLOC_4D_ARRAY(n1, n2, n3, n4, type)			\
  (type(*)[n1 + POLYBENCH_PADDING_FACTOR][n2 + POLYBENCH_PADDING_FACTOR][n3 + POLYBENCH_PADDING_FACTOR][n4 + POLYBENCH_PADDING_FACTOR])polybench_alloc_data ((n1 + POLYBENCH_PADDING_FACTOR) * (n2 + POLYBENCH_PADDING_FACTOR) * (n3 + POLYBENCH_PADDING_FACTOR) * (n4 + POLYBENCH_PADDING_FACTOR), sizeof(type))
# define POLYBENCH_ALLOC_5D_ARRAY(n1, n2, n3, n4, n5, type)		\
  (type(*)[n1 + POLYBENCH_PADDING_FACTOR][n2 + POLYBENCH_PADDING_FACTOR][n3 + POLYBENCH_PADDING_FACTOR][n4 + POLYBENCH_PADDING_FACTOR][n5 + POLYBENCH_PADDING_FACTOR])polybench_alloc_data ((n1 + POLYBENCH_PADDING_FACTOR) * (n2 + POLYBENCH_PADDING_FACTOR) * (n3 + POLYBENCH_PADDING_FACTOR) * (n4 + POLYBENCH_PADDING_FACTOR) * (n5 + POLYBENCH_PADDING_FACTOR), sizeof(type))

/* Macros for array declaration. */
# ifndef POLYBENCH_STACK_ARRAYS
#  define POLYBENCH_1D_ARRAY_DECL(var, type, dim1, ddim1)		\
  type POLYBENCH_1D(POLYBENCH_DECL_VAR(var), dim1, ddim1); \
  var = POLYBENCH_ALLOC_1D_ARRAY(POLYBENCH_C99_SELECT(dim1, ddim1), type);
#  define POLYBENCH_2D_ARRAY_DECL(var, type, dim1, dim2, ddim1, ddim2)	\
  type POLYBENCH_2D(POLYBENCH_DECL_VAR(var), dim1, dim2, ddim1, ddim2); \
  var = POLYBENCH_ALLOC_2D_ARRAY(POLYBENCH_C99_SELECT(dim1, ddim1), POLYBENCH_C99_SELECT(dim2, ddim2), type);
#  define POLYBENCH_3D_ARRAY_DECL(var, type, dim1, dim2, dim3, ddim1, ddim2, ddim3) \
  type POLYBENCH_3D(POLYBENCH_DECL_VAR(var), dim1, dim2, dim3, ddim1, ddim2, ddim3); \
  var = POLYBENCH_ALLOC_3D_ARRAY(POLYBENCH_C99_SELECT(dim1, ddim1), POLYBENCH_C99_SELECT(dim2, ddim2), POLYBENCH_C99_SELECT(dim3, ddim3), type);
#  define POLYBENCH_4D_ARRAY_DECL(var, type, dim1, dim2, dim3, dim4, ddim1, ddim2, ddim3, ddim4) \
  type POLYBENCH_4D(POLYBENCH_DECL_VAR(var), dim1, dim2, ,dim3, dim4, ddim1, ddim2, ddim3, ddim4); \
  var = POLYBENCH_ALLOC_4D_ARRAY(POLYBENCH_C99_SELECT(dim1, ddim1), POLYBENCH_C99_SELECT(dim2, ddim2), POLYBENCH_C99_SELECT(dim3, ddim3), POLYBENCH_C99_SELECT(dim4, ddim4), type);
#  define POLYBENCH_5D_ARRAY_DECL(var, type, dim1, dim2, dim3, dim4, dim5, ddim1, ddim2, ddim3, ddim4, ddim5) \
  type POLYBENCH_5D(POLYBENCH_DECL_VAR(var), dim1, dim2, dim3, dim4, dim5, ddim1, ddim2, ddim3, ddim4, ddim5); \
  var = POLYBENCH_ALLOC_5D_ARRAY(POLYBENCH_C99_SELECT(dim1, ddim1), POLYBENCH_C99_SELECT(dim2, ddim2), POLYBENCH_C99_SELECT(dim3, ddim3), POLYBENCH_C99_SELECT(dim4, ddim4), POLYBENCH_C99_SELECT(dim5, ddim5), type);
# else
# 111 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
#  define POLYBENCH_1D_ARRAY_DECL(var, type, dim1, ddim1)		\
  type POLYBENCH_1D(POLYBENCH_DECL_VAR(var), dim1, ddim1);
#  define POLYBENCH_2D_ARRAY_DECL(var, type, dim1, dim2, ddim1, ddim2)	\
  type POLYBENCH_2D(POLYBENCH_DECL_VAR(var), dim1, dim2, ddim1, ddim2);
#  define POLYBENCH_3D_ARRAY_DECL(var, type, dim1, dim2, dim3, ddim1, ddim2, ddim3) \
  type POLYBENCH_3D(POLYBENCH_DECL_VAR(var), dim1, dim2, dim3, ddim1, ddim2, ddim3);
#  define POLYBENCH_4D_ARRAY_DECL(var, type, dim1, dim2, dim3, dim4, ddim1, ddim2, ddim3, ddim4) \
  type POLYBENCH_4D(POLYBENCH_DECL_VAR(var), dim1, dim2, dim3, dim4, ddim1, ddim2, ddim3, ddim4);
#  define POLYBENCH_5D_ARRAY_DECL(var, type, dim1, dim2, dim3, dim4, dim5, ddim1, ddim2, ddim3, ddim4, ddim5) \
  type POLYBENCH_5D(POLYBENCH_DECL_VAR(var), dim1, dim2, dim3, dim4, dim5, ddim1, ddim2, ddim3, ddim4, ddim5);
# endif
# 122 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"


/* Dead-code elimination macros. Use argc/argv for the run-time check. */
# ifndef POLYBENCH_DUMP_ARRAYS
#  define POLYBENCH_DCE_ONLY_CODE    if (argc > 42 && ! strcmp(argv[0], ""))
# else
# 128 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
#  define POLYBENCH_DCE_ONLY_CODE
# endif
# 130 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"

# define polybench_prevent_dce(func)		\
  POLYBENCH_DCE_ONLY_CODE			\
  func


/* Performance-related instrumentation. See polybench.c */
# define polybench_start_instruments
# define polybench_stop_instruments
# define polybench_print_instruments


/* PAPI support. */
# ifdef POLYBENCH_PAPI
extern const unsigned int polybench_papi_eventlist[];
#  undef polybench_start_instruments
#  undef polybench_stop_instruments
#  undef polybench_print_instruments
#  define polybench_set_papi_thread_report(x)	\
   polybench_papi_counters_threadid = x;
#  define polybench_start_instruments				\
  polybench_prepare_instruments();				\
  polybench_papi_init();					\
  int evid;							\
  for (evid = 0; polybench_papi_eventlist[evid] != 0; evid++)	\
    {								\
      if (polybench_papi_start_counter(evid))			\
	continue;						\

#  define polybench_stop_instruments		\
      polybench_papi_stop_counter(evid);	\
    }						\
  polybench_papi_close();			\

#  define polybench_print_instruments polybench_papi_print();
# endif
# 166 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"


/* Timing support. */
# if defined(POLYBENCH_TIME) || defined(POLYBENCH_GFLOPS)
#  undef polybench_start_instruments
#  undef polybench_stop_instruments
#  undef polybench_print_instruments
#  define polybench_start_instruments polybench_timer_start();
#  define polybench_stop_instruments polybench_timer_stop();
#  define polybench_print_instruments polybench_timer_print();
extern double polybench_program_total_flops;
extern void polybench_timer_start();
extern void polybench_timer_stop();
extern void polybench_timer_print();
# endif
# 181 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"

/* Function declaration. */
# ifdef POLYBENCH_TIME
extern void polybench_timer_start();
extern void polybench_timer_stop();
extern void polybench_timer_print();
# endif
# 188 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"

# ifdef POLYBENCH_PAPI
extern void polybench_prepare_instruments();
extern int polybench_papi_start_counter(int evid);
extern void polybench_papi_stop_counter(int evid);
extern void polybench_papi_init();
extern void polybench_papi_close();
extern void polybench_papi_print();
# endif
# 197 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"

/* Function prototypes. */
extern void* polybench_alloc_data(unsigned long long int n, int elt_size);

/*
 LLVM: I'm appending the content of the file polybench.c here. It'll avoid us
       to have to copy it to the folder being compiled in the LLVM test suite.
 */

/**
 * polybench.c: This file is part of the PolyBench/C 3.2 test suite.
 *
 *
 * Contact: Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://polybench.sourceforge.net
 */
#if 0 /* expanded by -frewrite-includes */
#include <stdio.h>
#endif /* expanded by -frewrite-includes */
# 213 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
# 214 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
#if 0 /* expanded by -frewrite-includes */
#include <string.h>
#endif /* expanded by -frewrite-includes */
# 214 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
# 215 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
#if 0 /* expanded by -frewrite-includes */
#include <stdlib.h>
#endif /* expanded by -frewrite-includes */
# 215 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
# 216 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
//#include <unistd.h>
#if 0 /* expanded by -frewrite-includes */
#include <assert.h>
#endif /* expanded by -frewrite-includes */
# 217 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
# 1 "/usr/include/assert.h" 1 3 4
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
 *	ISO C99 Standard: 7.2 Diagnostics	<assert.h>
 */

#ifdef	_ASSERT_H

# undef	_ASSERT_H
# undef	assert
# undef __ASSERT_VOID_CAST

# ifdef	__USE_GNU
#  undef assert_perror
# endif
# 31 "/usr/include/assert.h" 3 4

#endif /* assert.h	*/
# 33 "/usr/include/assert.h" 3 4

#define	_ASSERT_H	1
#if 0 /* expanded by -frewrite-includes */
#include <features.h>
#endif /* expanded by -frewrite-includes */
# 35 "/usr/include/assert.h" 3 4
# 36 "/usr/include/assert.h" 3 4

#if defined __cplusplus && __GNUC_PREREQ (2,95)
# define __ASSERT_VOID_CAST static_cast<void>
#else
# 40 "/usr/include/assert.h" 3 4
# define __ASSERT_VOID_CAST (void)
#endif
# 42 "/usr/include/assert.h" 3 4

/* void assert (int expression);

   If NDEBUG is defined, do nothing.
   If not, and EXPRESSION is zero, print an error message and abort.  */

#ifdef	NDEBUG

# define assert(expr)		(__ASSERT_VOID_CAST (0))

/* void assert_perror (int errnum);

   If NDEBUG is defined, do nothing.  If not, and ERRNUM is not zero, print an
   error message with the error text for ERRNUM and abort.
   (This is a GNU extension.) */

# ifdef	__USE_GNU
#  define assert_perror(errnum)	(__ASSERT_VOID_CAST (0))
# endif
# 61 "/usr/include/assert.h" 3 4

#else /* Not NDEBUG.  */
# 63 "/usr/include/assert.h" 3 4

#ifndef _ASSERT_H_DECLS
#define _ASSERT_H_DECLS
__BEGIN_DECLS

/* This prints an "Assertion failed" message and aborts.  */
extern void __assert_fail (const char *__assertion, const char *__file,
			   unsigned int __line, const char *__function)
     __THROW __attribute__ ((__noreturn__));

/* Likewise, but prints the error text for ERRNUM.  */
extern void __assert_perror_fail (int __errnum, const char *__file,
				  unsigned int __line, const char *__function)
     __THROW __attribute__ ((__noreturn__));


/* The following is not at all used here but needed for standard
   compliance.  */
extern void __assert (const char *__assertion, const char *__file, int __line)
     __THROW __attribute__ ((__noreturn__));


__END_DECLS
#endif /* Not _ASSERT_H_DECLS */
# 87 "/usr/include/assert.h" 3 4

# define assert(expr)							\
  ((expr)								\
   ? __ASSERT_VOID_CAST (0)						\
   : __assert_fail (#expr, __FILE__, __LINE__, __ASSERT_FUNCTION))

# ifdef	__USE_GNU
#  define assert_perror(errnum)						\
  (!(errnum)								\
   ? __ASSERT_VOID_CAST (0)						\
   : __assert_perror_fail ((errnum), __FILE__, __LINE__, __ASSERT_FUNCTION))
# endif
# 99 "/usr/include/assert.h" 3 4

/* Version 2.4 and later of GCC define a magical variable `__PRETTY_FUNCTION__'
   which contains the name of the function currently being defined.
   This is broken in G++ before version 2.6.
   C9x has a similar variable called __func__, but prefer the GCC one since
   it demangles C++ function names.  */
# if defined __cplusplus ? __GNUC_PREREQ (2, 6) : __GNUC_PREREQ (2, 4)
#   define __ASSERT_FUNCTION	__PRETTY_FUNCTION__
# else
# 108 "/usr/include/assert.h" 3 4
#  if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L
#   define __ASSERT_FUNCTION	__func__
#  else
# 111 "/usr/include/assert.h" 3 4
#   define __ASSERT_FUNCTION	((const char *) 0)
#  endif
# 113 "/usr/include/assert.h" 3 4
# endif
# 114 "/usr/include/assert.h" 3 4

#endif /* NDEBUG.  */
# 116 "/usr/include/assert.h" 3 4


#if defined __USE_ISOC11 && !defined __cplusplus
# undef static_assert
# define static_assert _Static_assert
#endif
# 122 "/usr/include/assert.h" 3 4
# 218 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h" 2
#if 0 /* expanded by -frewrite-includes */
#include <time.h>
#endif /* expanded by -frewrite-includes */
# 218 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
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
# 1 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 1 3 4
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
# 37 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#define __need_ptrdiff_t
#define __need_size_t
#define __need_wchar_t
#define __need_NULL
#define __need_STDDEF_H_misc
/* __need_wint_t is intentionally not defined here. */
#endif
# 44 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_ptrdiff_t)
#if !defined(_PTRDIFF_T) || __has_feature(modules)
/* Always define ptrdiff_t when modules are available. */
#if !__has_feature(modules)
#define _PTRDIFF_T
#endif
# 51 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif
# 53 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_ptrdiff_t
#endif /* defined(__need_ptrdiff_t) */
# 55 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_size_t)
#if !defined(_SIZE_T) || __has_feature(modules)
/* Always define size_t when modules are available. */
#if !__has_feature(modules)
#define _SIZE_T
#endif
# 62 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ size_t;
#endif
# 64 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_size_t
#endif /*defined(__need_size_t) */
# 66 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
/* ISO9899:2011 7.20 (C11 Annex K): Define rsize_t if __STDC_WANT_LIB_EXT1__ is
 * enabled. */
#if (defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ >= 1 && \
     !defined(_RSIZE_T)) || __has_feature(modules)
/* Always define rsize_t when modules are available. */
#if !__has_feature(modules)
#define _RSIZE_T
#endif
# 76 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __SIZE_TYPE__ rsize_t;
#endif
# 78 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif /* defined(__need_STDDEF_H_misc) */
# 79 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_wchar_t)
#ifndef __cplusplus
/* Always define wchar_t when modules are available. */
#if !defined(_WCHAR_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WCHAR_T
#if defined(_MSC_EXTENSIONS)
#define _WCHAR_T_DEFINED
#endif
# 89 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 90 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WCHAR_TYPE__ wchar_t;
#endif
# 92 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 93 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wchar_t
#endif /* defined(__need_wchar_t) */
# 95 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_NULL)
#undef NULL
#ifdef __cplusplus
#  if !defined(__MINGW32__) && !defined(_MSC_VER)
#    define NULL __null
#  else
# 102 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#    define NULL 0
#  endif
# 104 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#else
# 105 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#  define NULL ((void*)0)
#endif
# 107 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#ifdef __cplusplus
#if defined(_MSC_EXTENSIONS) && defined(_NATIVE_NULLPTR_SUPPORTED)
namespace std { typedef decltype(nullptr) nullptr_t; }
using ::std::nullptr_t;
#endif
# 112 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 113 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_NULL
#endif /* defined(__need_NULL) */
# 115 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#if defined(__need_STDDEF_H_misc)
#if __STDC_VERSION__ >= 201112L || __cplusplus >= 201103L
#if 0 /* expanded by -frewrite-includes */
#include "__stddef_max_align_t.h"
#endif /* expanded by -frewrite-includes */
# 118 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
# 119 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#endif
# 120 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#define offsetof(t, d) __builtin_offsetof(t, d)
#undef __need_STDDEF_H_misc
#endif  /* defined(__need_STDDEF_H_misc) */
# 123 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

/* Some C libraries expect to see a wint_t here. Others (notably MinGW) will use
__WINT_TYPE__ directly; accommodate both by requiring __need_wint_t */
#if defined(__need_wint_t)
/* Always define wint_t when modules are available. */
#if !defined(_WINT_T) || __has_feature(modules)
#if !__has_feature(modules)
#define _WINT_T
#endif
# 132 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
typedef __WINT_TYPE__ wint_t;
#endif
# 134 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
#undef __need_wint_t
#endif /* __need_wint_t */
# 136 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4

#endif
# 138 "/root/build/llvm/release/bin/../lib/clang/5.0.0/include/stddef.h" 3 4
# 38 "/usr/include/time.h" 2 3 4

/* This defines CLOCKS_PER_SEC, which is the number of processor clock
   ticks per second.  */
#if 0 /* expanded by -frewrite-includes */
# include <bits/time.h>
#endif /* expanded by -frewrite-includes */
# 41 "/usr/include/time.h" 3 4
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
# 42 "/usr/include/time.h" 2 3 4

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
# 219 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h" 2
//#include <sys/time.h>
//#include <sys/resource.h>
//#include <sched.h>
#if 0 /* expanded by -frewrite-includes */
#include <math.h>
#endif /* expanded by -frewrite-includes */
# 222 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
# 223 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
#ifdef _OPENMP
#if 0 /* expanded by -frewrite-includes */
# include <omp.h>
#endif /* expanded by -frewrite-includes */
# 224 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
# 225 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
#endif
# 226 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"

/* By default, collect PAPI counters on thread 0. */
#ifndef POLYBENCH_THREAD_MONITOR
# define POLYBENCH_THREAD_MONITOR 0
#endif
# 231 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"

/* Total LLC cache size. By default 32+MB.. */
#ifndef POLYBENCH_CACHE_SIZE_KB
# define POLYBENCH_CACHE_SIZE_KB 32770
#endif
# 236 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"


int polybench_papi_counters_threadid = POLYBENCH_THREAD_MONITOR;
double polybench_program_total_flops = 0;

#ifdef POLYBENCH_PAPI
#if 0 /* expanded by -frewrite-includes */
# include <papi.h>
#endif /* expanded by -frewrite-includes */
# 242 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
# 243 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
# define POLYBENCH_MAX_NB_PAPI_COUNTERS 96
char* _polybench_papi_eventlist[] = {
#if 0 /* expanded by -frewrite-includes */
#include "papi_counters.list"
#endif /* expanded by -frewrite-includes */
# 245 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
# 246 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
  NULL
};
int polybench_papi_eventset;
int polybench_papi_eventlist[POLYBENCH_MAX_NB_PAPI_COUNTERS];
long_long polybench_papi_values[POLYBENCH_MAX_NB_PAPI_COUNTERS];

#endif
# 253 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"


/* Timer code (gettimeofday). */
double polybench_t_start, polybench_t_end;
/* Timer code (RDTSC). */
unsigned long long int polybench_c_start, polybench_c_end;

static
double rtclock()
{
#ifdef POLYBENCH_TIME
  struct timeval Tp;
  int stat;
  stat = gettimeofday (&Tp, NULL);
  if (stat != 0)
    printf ("Error return from gettimeofday: %d", stat);
  return (Tp.tv_sec + Tp.tv_usec * 1.0e-6);
#else
# 271 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
  return 0;
#endif
# 273 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
}


#ifdef POLYBENCH_CYCLE_ACCURATE_TIMER
static
unsigned long long int rdtsc()
{
  unsigned long long int ret = 0;
  unsigned int cycles_lo;
  unsigned int cycles_hi;
  __asm__ volatile ("RDTSC" : "=a" (cycles_lo), "=d" (cycles_hi));
  ret = (unsigned long long int)cycles_hi << 32 | cycles_lo;
  
  return ret;
}
#endif
# 289 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"

void polybench_flush_cache()
{
  int cs = POLYBENCH_CACHE_SIZE_KB * 1024 / sizeof(double);
  double* flush = (double*) calloc (cs, sizeof(double));
  int i;
  double tmp = 0.0;
#ifdef _OPENMP
#pragma omp parallel for
#endif
# 299 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
  for (i = 0; i < cs; i++)
    tmp += flush[i];
  assert (tmp <= 10.0);
  free (flush);
}


#ifdef POLYBENCH_LINUX_FIFO_SCHEDULER
void polybench_linux_fifo_scheduler()
{
  /* Use FIFO scheduler to limit OS interference. Program must be run
   as root, and this works only for Linux kernels. */
  struct sched_param schedParam;
  schedParam.sched_priority = sched_get_priority_max (SCHED_FIFO);
  sched_setscheduler (0, SCHED_FIFO, &schedParam);
}


void polybench_linux_standard_scheduler()
{
  /* Restore to standard scheduler policy. */
  struct sched_param schedParam;
  schedParam.sched_priority = sched_get_priority_max (SCHED_OTHER);
  sched_setscheduler (0, SCHED_OTHER, &schedParam);
}
#endif
# 325 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"

#ifdef POLYBENCH_PAPI

static
void test_fail(char *file, int line, char *call, int retval)
{
  char buf[128];
  
  memset(buf, '\0', sizeof(buf));
  if (retval != 0)
    fprintf (stdout,"%-40s FAILED\nLine # %d\n", file, line);
  else
  {
    fprintf (stdout,"%-40s SKIPPED\n", file);
    fprintf (stdout,"Line # %d\n", line);
  }
  if (retval == PAPI_ESYS)
  {
    sprintf (buf, "System error in %s", call);
    perror (buf);
  }
  else if (retval > 0)
    fprintf (stdout,"Error: %s\n", call);
  else if (retval == 0)
    fprintf (stdout,"Error: %s\n", call);
  else
  {
    char errstring[PAPI_MAX_STR_LEN];
    PAPI_perror (retval, errstring, PAPI_MAX_STR_LEN);
    fprintf (stdout,"Error in %s: %s\n", call, errstring);
  }
  fprintf (stdout,"\n");
  if (PAPI_is_initialized ())
    PAPI_shutdown ();
  exit (1);
}


void polybench_papi_init()
{
# ifdef _OPENMP
#pragma omp parallel
  {
#pragma omp master
    {
      if (omp_get_max_threads () < polybench_papi_counters_threadid)
        polybench_papi_counters_threadid = omp_get_max_threads () - 1;
    }
#pragma omp barrier
    
    if (omp_get_thread_num () == polybench_papi_counters_threadid)
    {
# endif
# 378 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
      int retval;
      polybench_papi_eventset = PAPI_NULL;
      if ((retval = PAPI_library_init (PAPI_VER_CURRENT)) != PAPI_VER_CURRENT)
        test_fail (__FILE__, __LINE__, "PAPI_library_init", retval);
      if ((retval = PAPI_create_eventset (&polybench_papi_eventset))
          != PAPI_OK)
        test_fail (__FILE__, __LINE__, "PAPI_create_eventset", retval);
      int k;
      for (k = 0; _polybench_papi_eventlist[k]; ++k)
      {
        if ((retval =
             PAPI_event_name_to_code (_polybench_papi_eventlist[k],
                                      &(polybench_papi_eventlist[k])))
            != PAPI_OK)
          test_fail (__FILE__, __LINE__, "PAPI_event_name_to_code", retval);
      }
      polybench_papi_eventlist[k] = 0;
      
      
# ifdef _OPENMP
    }
  }
#pragma omp barrier
# endif
# 402 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
}


void polybench_papi_close()
{
# ifdef _OPENMP
#pragma omp parallel
  {
    if (omp_get_thread_num () == polybench_papi_counters_threadid)
    {
# endif
# 413 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
      int retval;
      if ((retval = PAPI_destroy_eventset (&polybench_papi_eventset))
          != PAPI_OK)
        test_fail (__FILE__, __LINE__, "PAPI_destroy_eventset", retval);
      if (PAPI_is_initialized ())
        PAPI_shutdown ();
# ifdef _OPENMP
    }
  }
#pragma omp barrier
# endif
# 424 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
}

int polybench_papi_start_counter(int evid)
{
# ifndef POLYBENCH_NO_FLUSH_CACHE
  polybench_flush_cache();
# endif
# 431 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
  
# ifdef _OPENMP
# pragma omp parallel
  {
    if (omp_get_thread_num () == polybench_papi_counters_threadid)
    {
# endif
# 438 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
      
      int retval = 1;
      char descr[PAPI_MAX_STR_LEN];
      PAPI_event_info_t evinfo;
      PAPI_event_code_to_name (polybench_papi_eventlist[evid], descr);
      if (PAPI_add_event (polybench_papi_eventset,
                          polybench_papi_eventlist[evid]) != PAPI_OK)
        test_fail (__FILE__, __LINE__, "PAPI_add_event", 1);
      if (PAPI_get_event_info (polybench_papi_eventlist[evid], &evinfo)
          != PAPI_OK)
        test_fail (__FILE__, __LINE__, "PAPI_get_event_info", retval);
      if ((retval = PAPI_start (polybench_papi_eventset)) != PAPI_OK)
        test_fail (__FILE__, __LINE__, "PAPI_start", retval);
# ifdef _OPENMP
    }
  }
#pragma omp barrier
# endif
# 456 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
  return 0;
}


void polybench_papi_stop_counter(int evid)
{
# ifdef _OPENMP
# pragma omp parallel
  {
    if (omp_get_thread_num () == polybench_papi_counters_threadid)
    {
# endif
# 468 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
      int retval;
      long_long values[1];
      values[0] = 0;
      if ((retval = PAPI_read (polybench_papi_eventset, &values[0]))
          != PAPI_OK)
        test_fail (__FILE__, __LINE__, "PAPI_read", retval);
      
      if ((retval = PAPI_stop (polybench_papi_eventset, NULL)) != PAPI_OK)
        test_fail (__FILE__, __LINE__, "PAPI_stop", retval);
      
      polybench_papi_values[evid] = values[0];
      
      if ((retval = PAPI_remove_event
           (polybench_papi_eventset,
            polybench_papi_eventlist[evid])) != PAPI_OK)
        test_fail (__FILE__, __LINE__, "PAPI_remove_event", retval);
# ifdef _OPENMP
    }
  }
#pragma omp barrier
# endif
# 489 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
}


void polybench_papi_print()
{
  int verbose = 0;
# ifdef _OPENMP
# pragma omp parallel
  {
    if (omp_get_thread_num() == polybench_papi_counters_threadid)
    {
#ifdef POLYBENCH_PAPI_VERBOSE
      verbose = 1;
#endif
# 503 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
      if (verbose)
        printf ("On thread %d:\n", polybench_papi_counters_threadid);
#endif
# 506 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
      int evid;
      for (evid = 0; polybench_papi_eventlist[evid] != 0; ++evid)
      {
        if (verbose)
          printf ("%s=", _polybench_papi_eventlist[evid]);
        printf ("%llu ", polybench_papi_values[evid]);
        if (verbose)
          printf ("\n");
      }
      printf ("\n");
# ifdef _OPENMP
    }
  }
#pragma omp barrier
# endif
# 521 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
}

#endif
# 524 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
/* ! POLYBENCH_PAPI */

void polybench_prepare_instruments()
{
#ifndef POLYBENCH_NO_FLUSH_CACHE
  polybench_flush_cache ();
#endif
# 531 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
#ifdef POLYBENCH_LINUX_FIFO_SCHEDULER
  polybench_linux_fifo_scheduler ();
#endif
# 534 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
}


void polybench_timer_start()
{
  polybench_prepare_instruments ();
#ifndef POLYBENCH_CYCLE_ACCURATE_TIMER
  polybench_t_start = rtclock ();
#else
# 543 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
  polybench_c_start = rdtsc ();
#endif
# 545 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
}


void polybench_timer_stop()
{
#ifndef POLYBENCH_CYCLE_ACCURATE_TIMER
  polybench_t_end = rtclock ();
#else
# 553 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
  polybench_c_end = rdtsc ();
#endif
# 555 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
#ifdef POLYBENCH_LINUX_FIFO_SCHEDULER
  polybench_linux_standard_scheduler ();
#endif
# 558 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
}


void polybench_timer_print()
{
#ifdef POLYBENCH_GFLOPS
  if  (__polybench_program_total_flops == 0)
	{
	  printf ("[PolyBench][WARNING] Program flops not defined, use polybench_set_program_flops(value)\n");
	  printf ("%0.6lf\n", polybench_t_end - polybench_t_start);
	}
  else
    printf ("%0.2lf\n",
            (__polybench_program_total_flops /
             (double)(polybench_t_end - polybench_t_start)) / 1000000000);
#else
# 574 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
# ifndef POLYBENCH_CYCLE_ACCURATE_TIMER
  printf ("%0.6f\n", polybench_t_end - polybench_t_start);
# else
# 577 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
  printf ("%Ld\n", polybench_c_end - polybench_c_start);
# endif
# 579 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
#endif
# 580 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
}



static
void *
xmalloc (size_t num)
{
  void* new = NULL;
  int ret = posix_memalign (&new, 32, num);
  if (! new || ret)
  {
    fprintf (stderr, "[PolyBench] posix_memalign: cannot allocate memory");
    exit (1);
  }
  return new;
}


void* polybench_alloc_data(unsigned long long int n, int elt_size)
{
  /// FIXME: detect overflow!
  size_t val = n;
  val *= elt_size;
  void* ret = xmalloc (val);
  
  return ret;
}

/* To avoid calling printf M*M times (and make it run
   for a long time), we split the output into an encoded string,
   and print it as a simple char pointer, M times. */
static inline
void print_element(double el, int pos, char *out)
{
  union {
    double datum;
    char bytes[8];
  } block;

  block.datum = el;
  /* each nibble as a char, within the printable range */
#ifdef __BIG_ENDIAN__
  *(out+pos+15) = (block.bytes[0]&0xF0>>4)+'0';
  *(out+pos+14) = (block.bytes[0]&0x0F)   +'0';
  *(out+pos+13) = (block.bytes[1]&0xF0>>4)+'0';
  *(out+pos+12) = (block.bytes[1]&0x0F)   +'0';
  *(out+pos+11) = (block.bytes[2]&0xF0>>4)+'0';
  *(out+pos+10) = (block.bytes[2]&0x0F)   +'0';
  *(out+pos+9) = (block.bytes[3]&0xF0>>4)+'0';
  *(out+pos+8) =   (block.bytes[3]&0x0F)   +'0';
  *(out+pos+7) = (block.bytes[4]&0xF0>>4)+'0';
  *(out+pos+6) = (block.bytes[4]&0x0F)   +'0';
  *(out+pos+5) = (block.bytes[5]&0xF0>>4)+'0';
  *(out+pos+4) = (block.bytes[5]&0x0F)   +'0';
  *(out+pos+3) = (block.bytes[6]&0xF0>>4)+'0';
  *(out+pos+2) = (block.bytes[6]&0x0F)   +'0';
  *(out+pos+1) = (block.bytes[7]&0xF0>>4)+'0';
  *(out+pos) =   (block.bytes[7]&0x0F)   +'0';
#else
# 640 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
  *(out+pos)   = (block.bytes[0]&0xF0>>4)+'0';
  *(out+pos+1) = (block.bytes[0]&0x0F)   +'0';
  *(out+pos+2) = (block.bytes[1]&0xF0>>4)+'0';
  *(out+pos+3) = (block.bytes[1]&0x0F)   +'0';
  *(out+pos+4) = (block.bytes[2]&0xF0>>4)+'0';
  *(out+pos+5) = (block.bytes[2]&0x0F)   +'0';
  *(out+pos+6) = (block.bytes[3]&0xF0>>4)+'0';
  *(out+pos+7) = (block.bytes[3]&0x0F)   +'0';
  *(out+pos+8) = (block.bytes[4]&0xF0>>4)+'0';
  *(out+pos+9) = (block.bytes[4]&0x0F)   +'0';
  *(out+pos+10) = (block.bytes[5]&0xF0>>4)+'0';
  *(out+pos+11) = (block.bytes[5]&0x0F)   +'0';
  *(out+pos+12) = (block.bytes[6]&0xF0>>4)+'0';
  *(out+pos+13) = (block.bytes[6]&0x0F)   +'0';
  *(out+pos+14) = (block.bytes[7]&0xF0>>4)+'0';
  *(out+pos+15) = (block.bytes[7]&0x0F)   +'0';
#endif
# 657 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
}

#endif /* !POLYBENCH_H */
# 660 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/../../utilities/polybench.h"
# 15 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/covariance.c" 2

/* Include benchmark-specific header. */
/* Default data type is double, default size is 4000. */
#if 0 /* expanded by -frewrite-includes */
#include "covariance.h"
#endif /* expanded by -frewrite-includes */
# 18 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/covariance.c"
# 1 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/covariance.h" 1
/**
 * covariance.h: This file is part of the PolyBench/C 3.2 test suite.
 *
 *
 * Contact: Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://polybench.sourceforge.net
 */
#ifndef COVARIANCE_H
# define COVARIANCE_H

/* Default to STANDARD_DATASET. */
# if !defined(MINI_DATASET) && !defined(SMALL_DATASET) && !defined(LARGE_DATASET) && !defined(EXTRALARGE_DATASET)
#  define STANDARD_DATASET
# endif
# 15 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/covariance.h"

/* Do not define anything if the user manually defines the size. */
# if !defined(N) && !defined(M)
/* Define the possible dataset sizes. */
#  ifdef MINI_DATASET
#   define N 32
#   define M 32
#  endif
# 23 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/covariance.h"

#  ifdef SMALL_DATASET
#   define N 500
#   define M 500
#  endif
# 28 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/covariance.h"

#  ifdef STANDARD_DATASET /* Default if unspecified. */
#   define N 1000
#   define M 1000
#  endif
# 33 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/covariance.h"

#  ifdef LARGE_DATASET
#   define N 2000
#   define M 2000
#  endif
# 38 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/covariance.h"

#  ifdef EXTRALARGE_DATASET
#   define N 4000
#   define M 4000
#  endif
# 43 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/covariance.h"
# endif /* !N */
# 44 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/covariance.h"

# define _PB_N POLYBENCH_LOOP_BOUND(N,n)
# define _PB_M POLYBENCH_LOOP_BOUND(M,m)

# ifndef DATA_TYPE
#  define DATA_TYPE double
#  define DATA_PRINTF_MODIFIER "%0.2lf "
# endif
# 52 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/covariance.h"


#endif /* !COVARIANCE_H */
# 55 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/covariance.h"
# 19 "/root/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/covariance/covariance.c" 2


/* Array initialization. */
static
void init_array (int m, int n,
		 DATA_TYPE *float_n,
		 DATA_TYPE POLYBENCH_2D(data,M,N,m,n))
{
#pragma STDC FP_CONTRACT OFF
  int i, j;

  *float_n = 1.2;

  for (i = 0; i < M; i++)
    for (j = 0; j < N; j++)
      data[i][j] = ((DATA_TYPE) i*j) / M;
}


/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
static
void print_array(int m,
		 DATA_TYPE POLYBENCH_2D(symmat,M,M,m,m))

{
  int i, j;
  char *printmat = malloc(m*16 + 1); printmat[m*16] = 0;

  for (i = 0; i < m; i++) {
    for (j = 0; j < m; j++)
      print_element(symmat[i][j], j*16, printmat);
    fputs(printmat, stderr);
  }
  free(printmat);
}


/* Main computational kernel. The whole function will be timed,
   including the call and return. */
static
void kernel_covariance(int m, int n,
		       DATA_TYPE float_n,
		       DATA_TYPE POLYBENCH_2D(data,M,N,m,n),
		       DATA_TYPE POLYBENCH_2D(symmat,M,M,m,m),
		       DATA_TYPE POLYBENCH_1D(mean,M,m))
{
  int i, j, j1, j2;

#pragma scop
  /* Determine mean of column vectors of input data matrix */
  for (j = 0; j < _PB_M; j++)
    {
      mean[j] = 0.0;
      for (i = 0; i < _PB_N; i++)
        mean[j] += data[i][j];
      mean[j] /= float_n;
    }

  /* Center the column vectors. */
  for (i = 0; i < _PB_N; i++)
    for (j = 0; j < _PB_M; j++)
      data[i][j] -= mean[j];

  /* Calculate the m * m covariance matrix. */
  for (j1 = 0; j1 < _PB_M; j1++)
    for (j2 = j1; j2 < _PB_M; j2++)
      {
        symmat[j1][j2] = 0.0;
        for (i = 0; i < _PB_N; i++)
	  symmat[j1][j2] += data[i][j1] * data[i][j2];
        symmat[j2][j1] = symmat[j1][j2];
      }
#pragma endscop

}

static void
kernel_covariance_StrictFP(int m, int n,
                           DATA_TYPE float_n,
                           DATA_TYPE POLYBENCH_2D(data,M,N,m,n),
                           DATA_TYPE POLYBENCH_2D(symmat,M,M,m,m),
                           DATA_TYPE POLYBENCH_1D(mean,M,m))
{
#pragma STDC FP_CONTRACT OFF
  int i, j, j1, j2;

  /* Determine mean of column vectors of input data matrix */
  for (j = 0; j < _PB_M; j++)
    {
      mean[j] = 0.0;
      for (i = 0; i < _PB_N; i++)
        mean[j] += data[i][j];
      mean[j] /= float_n;
    }

  /* Center the column vectors. */
  for (i = 0; i < _PB_N; i++)
    for (j = 0; j < _PB_M; j++)
      data[i][j] -= mean[j];

  /* Calculate the m * m covariance matrix. */
  for (j1 = 0; j1 < _PB_M; j1++)
    for (j2 = j1; j2 < _PB_M; j2++)
      {
        symmat[j1][j2] = 0.0;
        for (i = 0; i < _PB_N; i++)
	  symmat[j1][j2] += data[i][j1] * data[i][j2];
        symmat[j2][j1] = symmat[j1][j2];
      }
}

/* Return 0 when one of the elements of arrays A and B do not match within the
   allowed FP_ABSTOLERANCE.  Return 1 when all elements match.  */
static inline int
check_FP(int m,
         DATA_TYPE POLYBENCH_2D(A,M,M,m,m),
         DATA_TYPE POLYBENCH_2D(B,M,M,m,m)) {
  int i, j;
  double AbsTolerance = FP_ABSTOLERANCE;
  for (i = 0; i < _PB_M; i++)
    for (j = 0; j < _PB_M; j++)
      {
        double V1 = A[i][j];
        double V2 = B[i][j];
        double Diff = fabs(V1 - V2);
        if (Diff > AbsTolerance) {
          fprintf(stderr, "A[%d][%d] = %lf and B[%d][%d] = %lf differ more than"
                  " FP_ABSTOLERANCE = %lf\n", i, j, V1, i, j, V2, AbsTolerance);
          return 0;
        }
      }

  /* All elements are within the allowed FP_ABSTOLERANCE error margin.  */
  return 1;
}

int main(int argc, char** argv)
{
  /* Retrieve problem size. */
  int n = N;
  int m = M;

  /* Variable declaration/allocation. */
  DATA_TYPE float_n;
  POLYBENCH_2D_ARRAY_DECL(data,DATA_TYPE,M,N,m,n);
  POLYBENCH_2D_ARRAY_DECL(symmat,DATA_TYPE,M,M,m,m);
  POLYBENCH_2D_ARRAY_DECL(symmat_StrictFP,DATA_TYPE,M,M,m,m);
  POLYBENCH_1D_ARRAY_DECL(mean,DATA_TYPE,M,m);


  /* Initialize array(s). */
  init_array (m, n, &float_n, POLYBENCH_ARRAY(data));

  /* Start timer. */
  polybench_start_instruments;

  /* Run kernel. */
  kernel_covariance (m, n, float_n,
		     POLYBENCH_ARRAY(data),
		     POLYBENCH_ARRAY(symmat),
		     POLYBENCH_ARRAY(mean));

  /* Stop and print timer. */
  polybench_stop_instruments;
  polybench_print_instruments;

  init_array (m, n, &float_n, POLYBENCH_ARRAY(data));
  kernel_covariance (m, n, float_n,
		     POLYBENCH_ARRAY(data),
		     POLYBENCH_ARRAY(symmat_StrictFP),
		     POLYBENCH_ARRAY(mean));
  if (!check_FP(m, POLYBENCH_ARRAY(symmat), POLYBENCH_ARRAY(symmat_StrictFP)))
    return 1;

  /* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
  polybench_prevent_dce(print_array(m, POLYBENCH_ARRAY(symmat_StrictFP)));

  /* Be clean. */
  POLYBENCH_FREE_ARRAY(data);
  POLYBENCH_FREE_ARRAY(symmat);
  POLYBENCH_FREE_ARRAY(symmat_StrictFP);
  POLYBENCH_FREE_ARRAY(mean);

  return 0;
}
