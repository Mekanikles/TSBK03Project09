HOMEPATH=../..
SRCPATH=$(HOMEPATH)/src
EXEPATH=$(HOMEPATH)/bin/project.exe

SOURCE=main.cpp
DEPS=


CFLAGS=-mno-cygwin -g -Wall
FULLSRC=$(SOURCE:%=$(SRCPATH)/%)
OBJECTS=$(FULLSRC:.c=.o)

.cpp.o:
	$(CXX) $(CFLAGS) -c $<

all: $(OBJECTS)
	gcc $(CFLAGS) $(OBJECTS) -o $(EXEPATH)



