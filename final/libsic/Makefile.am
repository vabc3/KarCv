AM_CFLAGS			= `pkg-config --cflags opencv` -I../libsift
lib_LTLIBRARIES		= libsic.la
libsic_la_SOURCES 	= dao.c dao_sqlite3.c sicmain.c log.c feat.c file.c
include_HEADERS		= sic.h
libsic_la_LDFLAGS 	= -version-info  0:1:0
