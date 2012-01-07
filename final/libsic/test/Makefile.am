AM_CFLAGS	= `pkg-config --cflags opencv` -I..
LDADD		= ../libsic.la

#tdb tbf tm tq ad
bin_PROGRAMS = tdb

tdb_DEPENDENCIES  = ../libsic.la
tdb_LDFLAGS		= -static
../libsic.la :
		make -C .. $@
