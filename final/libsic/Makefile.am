AM_CFLAGS			= `pkg-config --cflags opencv` -Isift
lib_LTLIBRARIES		= libsic.la
libsic_la_SOURCES 	= dao.c dao_sqlite3.c sicmain.c log.c feat.c file.c \
					  sift/imgfeatures.c  sift/kdtree.c  sift/minpq.c \
					  sift/sift.c  sift/utils.c  sift/xform.c

#libsic_la_LIBADD	= sift/libsift.la
libsic_la_LDFLAGS 	= -version-info  0:1:0
include_HEADERS		= sic.h
