# Compiler and flags
CC = gcc
CFLAGS = -Wall
LDFLAGS = -lwiringPi -liconv

# Source files and executable
SOURCES = main.c
EXECUTABLE = matrix

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES) $(LDFLAGS)

clean:
	rm -f $(EXECUTABLE)

.PHONY: all clean
