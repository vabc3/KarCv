AM_CFLAGS			= `pkg-config --cflags opencv` -Isift -Ihistogram
lib_LTLIBRARIES		= libsic.la
libsic_la_SOURCES 	= dao.c dao_sqlite3.c sicmain.c log.c file.c \
					  	service.c hiutil.c\
					  	sift/imgfeatures.c  sift/kdtree.c  sift/minpq.c \
					  	sift/sift.c  sift/utils.c  sift/xform.c	\
					  	plugins.c plugins/pfix.c plugins/pall.c \
						plugins/pfeat_save.c plugins/pfeat.c plugins/pdoc.c \
						plugins/pfeat_sift.c plugins/pfeat_hist.c \
						histogram/histogram.c 

libsic_la_LDFLAGS 	= -version-info  1:0:0
include_HEADERS		= sic.h
