AC_PREREQ([2.68])
AC_INIT([SIC], [0.1], [vabc3h@gmail.com])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CXX

AC_PROG_CC
AC_PROG_RANLIB
AC_LIBTOOL_DLOPEN
AC_PROG_LIBTOOL

AC_SEARCH_LIBS(sqlite3_open, sqlite3)
AC_SEARCH_LIBS(pow,m)
AC_SEARCH_LIBS(cvLine,opencv_core,,AC_MSG_ERROR([opencv lib needed]))
AC_SEARCH_LIBS(cvLoadImage,opencv_highgui,,AC_MSG_ERROR([opencv lib needed]))


AC_CONFIG_MACRO_DIR([m4])

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lsicdb':
#AC_CHECK_LIB([dl], [dlopen],[AC_MSG_NOTICE([Enabling support for SSL via OpenSSL (shared)])],[AC_MSG_ERROR([nof])])

# Checks for header files.
AC_CHECK_HEADERS([limits.h stdlib.h string.h sys/time.h unistd.h math.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([getcwd gettimeofday memset mkdir pow sqrt strrchr],[],[AC_MSG_ERROR([缺失所需函数])])

AC_CONFIG_FILES([Makefile
				 libsift/Makefile
                 libsic/Makefile
                 libsic/test/Makefile
				 src/Makefile
				 ])
#AC_SUBST(CFLAGS)
CFLAGS="-O2 -Wall -g"
AC_OUTPUT

