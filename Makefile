# Compiler and flags
CC = gcc
CFLAGS = -Wall
LDFLAGS = -lwiringPi -liconv

# Source files and executable
SOURCES = your_program.c
EXECUTABLE = your_program

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES) $(LDFLAGS)

clean:
	rm -f $(EXECUTABLE)

.PHONY: all clean
