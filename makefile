# Get the folder name
FOLDER_NAME := $(notdir $(CURDIR))

# Find all .c files in the folder
SRCS := $(wildcard *.c)

# Generate object file names from .c files
OBJS := $(SRCS:.c=.o)

# Compiler and flags
CC := gcc
CFLAGS := -Wall -O2

# The output binary
TARGET := $(FOLDER_NAME)

# Default rule to build the binary
all: $(TARGET)

# Rule to link the object files into the final binary
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile each .c file into an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove the binary and object files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

