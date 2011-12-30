#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([SIC], [0.1], [vabc3h@gmail.com])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE
# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB
# Checks for libraries.
# FIXME: Replace `main' with a function in `-lsicdb':
#AC_CHECK_LIB([sicdb], [main])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC

AC_CONFIG_FILES([Makefile
				 libsift/Makefile
                 libsic/Makefile
                 libsic/test/Makefile
				 src/Makefile
				 ])
#AC_SUBST(CFLAGS)
CFLAGS="-O2 -Wall -g"
AC_OUTPUT

