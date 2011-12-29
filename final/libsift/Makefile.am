AM_CFLAGS		= `pkg-config --cflags opencv`
AM_LDFLAGS		= `pkg-config --libs opencv`
lib_LIBRARIES 	= libsift.a
libsift_a_SOURCES = imgfeatures.c utils.c sift.c kdtree.c minpq.c xform.c

clean:
	rm -f *~ *.o *.a

.PHONY: clean
