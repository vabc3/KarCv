#AM_CFLAGS	= -O2 -Wall -Dtc
AM_LDFLAGS	= `pkg-config sqlite3 --libs`
LDADD		= -L../ -lsicdb -L../../util -lsicutil

bin_PROGRAMS = tdb

tdb_DEPENDENCIES = ../libsicdb.a

../libsicdb.a :
		make -C ..
