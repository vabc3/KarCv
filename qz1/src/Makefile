#CV Homework #1

TARGETS = jpg_show vid_show cjk_test
CFLAGS 	= $(shell pkg-config opencv freetype2 --cflags) -Wall
LDFLAGS = $(shell pkg-config opencv freetype2 --libs)

.PHONY : all test clean

all : $(TARGETS)

test : $(TARGETS)
	find . -type f -perm /u+x -exec ./{} \;

clean :
	rm -rf $(TARGETS) *.o *~

vid_show cjk_test : cjk_font.o

