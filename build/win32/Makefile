include ../Makefile.config

HOMEPATH=../..
SRCPATH=$(HOMEPATH)/src
EXEPATH=$(HOMEPATH)/bin/project.exe

CFLAGS=-mno-cygwin -o2 #-g -Wall
CFLAGS+= -I$(GLFWPATH)/include
LFLAGS=-L$(GLFWPATH)/lib/win32 -lglfw -lopengl32 -lglu32

FULLSRC=$(SOURCE:%=$(SRCPATH)/%)
FULLDEPS=$(DEPS:%=$(SRCPATH)/%)
OBJECTS=$(FULLSRC:.cpp=.o)

%.o: %.cpp $(FULLDEPS)
	g++ -c $(CFLAGS) $< -o $@

all: $(OBJECTS)
	g++ $(CFLAGS) $(OBJECTS) $(LFLAGS) -o $(EXEPATH)

clean:
	rm -f $(OBJECTS)


