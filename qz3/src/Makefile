#CV Homework #2
#20111202

#CC		= clang
TARGETS = prog 
CFLAGS 	= $(shell pkg-config opencv --cflags) -Wall -O2 -g
CPPFLAGS 	= $(shell pkg-config opencv --cflags) -Wall -g
LDFLAGS = $(shell pkg-config opencv --libs)

.PHONY : all test clean

all : $(TARGETS)

test : $(TARGETS)
	find . -type f -perm /u+x -exec ./{} \;

clean :
	rm -rf $(TARGETS) *.o *~

$(TARGETS)	: hiutil.o canny.o

hiutil.o	: hiutil.h
