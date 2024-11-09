CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp realization.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

realization.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -rf *.o $(EXECUTABLE)