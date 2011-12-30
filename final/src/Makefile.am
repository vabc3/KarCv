AM_CFLAGS		= -I../libsic
AM_LDFLAGS		= `pkg-config --libs opencv sqlite3`
LDADD			= -L../libsic -lsic -L../libsift -lsift
bin_PROGRAMS	= sic
sic_SOURCES		= sic.c arg.c func.c
