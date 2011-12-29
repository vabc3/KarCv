AM_CFLAGS	= `pkg-config --cflags opencv`
AM_LDFLAGS	= `pkg-config --libs sqlite3 opencv`
LDADD		= -L../ -lsic -L../../libsift -lsift

bin_PROGRAMS = tdb tbf tm tq

tm_DEPENDENCIES = ../libsic.a

../libsic.a :
		make -C ..
