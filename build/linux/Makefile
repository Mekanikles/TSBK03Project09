HOMEPATH=../..
SRCPATH=$(HOMEPATH)/src
EXEPATH=$(HOMEPATH)/bin/project

SOURCE=main.cpp
DEPS=


CFLAGS=-g -Wall
LFLAGS= -lglfw
FULLSRC=$(SOURCE:%=$(SRCPATH)/%)
OBJECTS=$(FULLSRC:.c=.o)

.cpp.o:
	$(CXX) $(CFLAGS) -c $<

all: $(OBJECTS)
	g++ $(CFLAGS) $(LFLAGS) $(OBJECTS) -o $(EXEPATH)



