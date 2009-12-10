include ../Makefile.config

HOMEPATH=../..
SRCPATH=$(HOMEPATH)/src
EXEPATH=$(HOMEPATH)/bin/project.exe

CFLAGS=-mno-cygwin -O3 #-g -Wall
CFLAGS+= -I$(GLFWPATH)/include -I$(GLEWPATH)/include
LFLAGS=-L$(GLFWPATH)/lib/win32 -L$(GLEWPATH)/lib/ $(GLEWPATH)/bin/glew32.dll -lglfw -lopengl32 -lglu32 -lglew32

FULLSRC=$(SOURCE:%=$(SRCPATH)/%)
FULLDEPS=$(DEPS:%=$(SRCPATH)/%)
OBJECTS=$(FULLSRC:.cpp=.o)

%.o: %.cpp $(FULLDEPS)
	g++ -c $(CFLAGS) $< -o $@

all: $(OBJECTS)
	g++ $(CFLAGS) $(OBJECTS) $(LFLAGS) -o $(EXEPATH)

clean:
	rm -f $(OBJECTS)


