#CV Homework #2
#20111202

CC		= clang
TARGETS = color_transfer te jh
CFLAGS 	= $(shell pkg-config opencv --cflags) -Wall
CPPFLAGS 	= $(shell pkg-config opencv --cflags) -Wall
LDFLAGS = $(shell pkg-config opencv --libs)

.PHONY : all test clean

all : $(TARGETS)

test : $(TARGETS)
	find . -type f -perm /u+x -exec ./{} \;

clean :
	rm -rf $(TARGETS) *.o *~

$(TARGETS)	: histogram.o
