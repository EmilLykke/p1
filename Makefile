CC = gcc
CFLAGS = 

# List of C source files
SOURCES = csv_read.c scan_user_input.c
MAIN = main.c
# Derive object files from source files
OBJECTS = $(SOURCES:.c=.o)

# The final executable
TARGET = main

# Rule for compiling C source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rules for building the executable
$(TARGET): $(OBJECTS)
	$(CC) $(MAIN) -o $(TARGET) $(OBJECTS)

# Phony target to clean object files and the executable
.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET)
