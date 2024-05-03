CC=g++
CFLAGS=
LDFLAGS=

SRCDIR=.
SOURCES=$(wildcard $(SRCDIR)/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=program

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRCDIR)/*.o $(EXECUTABLE)
