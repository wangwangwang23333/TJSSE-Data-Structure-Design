CFLAGS   = -c -Wall -Werror
COMPILE  = g++
RM       = rm -f
OBJ      = linux
SOURCE   = main.o
DEPEND   = main.cpp Maze.h

build : $(SOURCE)
	$(COMPILE) $(SOURCE) -o $(OBJ)

%.o:%cpp $(DEPEND)
	$(COMPILE) $(CFLAGS) -o $@ $<

clean:
	$(RM) *.bak $(SOURCE) $(OBJ)
	touch *.*