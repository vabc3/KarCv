AM_CFLAGS	= `pkg-config --cflags opencv`
AM_LDFLAGS	= `pkg-config --libs sqlite3 opencv`
LDADD		= -L../ -lsic -L../../libsift -lsift

#tdb tbf tm tq ad
bin_PROGRAMS = ad file


ad_DEPENDENCIES = ../libsic.a

../libsic.a :
		make -C ..
