AM_CFLAGS	= `pkg-config --cflags opencv` -I..
LDADD		= ../libsic.la

#tdb tbf tm tq ad
bin_PROGRAMS = plugc

plugc_DEPENDENCIES  = ../libsic.la
plugc_LDFLAGS		= -static
../libsic.la :
		make -C .. $@
