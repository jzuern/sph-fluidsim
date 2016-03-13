CC=g++
INC=-I/home/jzuern/Dropbox/develop/C++/Libraries/gnuplot/
CFLAGS=-c  -Wall -std=c++11 $(INC)
LDFLAGS=-fopenmp
LDLIBS=
SOURCEPATH=src
SOURCES=$(SOURCEPATH)/main.cpp \
						$(SOURCEPATH)/sph_funcs.cpp \
						$(SOURCEPATH)/integrate.cpp \
						$(SOURCEPATH)/linked_list.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=fluidsim

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	    $(CC) $(LDFLAGS) $(OBJECTS) $(LDLIBS)-o $@

.cpp.o:
	    $(CC) $(CFLAGS) $< -o $@

clean:
				rm $(SOURCEPATH)/*.o
