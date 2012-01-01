AM_CFLAGS		= -I../libsic
AM_LDFLAGS		= `pkg-config --libs opencv`
LDADD			= ../libsic/libsic.la -L../libsift -lsift
bin_PROGRAMS	= sic
sic_SOURCES		= main.c arg.c func.c
#sic_LDFLAGS	= -static
