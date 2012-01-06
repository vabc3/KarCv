AM_CFLAGS	= `pkg-config --cflags opencv` -I..
AM_LDFLAGS	= `pkg-config --libs sqlite3 opencv`
LDADD		= -L../ -lsic

#tdb tbf tm tq ad
bin_PROGRAMS = fd

fd_DEPENDENCIES = ../libsic.a

../libsic.a :
		make -C ..
