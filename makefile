CC=g++
CFLAGS=-c  -Wall -Wextra -g -D_GLIBCXX_DEBUG -std=c++11
LDFLAGS=-fopenmp -lutil -lboost_iostreams -lboost_system -lboost_filesystem
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
	    $(CC) -o $@ $^ $(LDFLAGS) 

.cpp.o:
	    $(CC) $(CFLAGS) -c $< -o $@

clean:
				rm $(SOURCEPATH)/*.o
