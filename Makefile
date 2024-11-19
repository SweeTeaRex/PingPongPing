# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g 
RELEASE_FLAGS = -Wall -Wextra -s      # Enable debugging with -g flag
LDFLAGS = -lraylib -lm -lpthread -ldl -lrt -lX11  # Link against Raylib and other required libraries

# Paths (modify these based on your setup)
INCLUDE_PATH = /usr/local/include
LIBRARY_PATH = /usr/local/lib

# Project files
SOURCES = main.c                 # Add additional source files as needed
OBJECTS = $(SOURCES:.c=.o)
TARGET = my_game                 # Output executable name

# Compilation rules
all: debug                       # Default to debug build

# Build target with debugging info
debug: CFLAGS = $(DEBUG_FLAGS)
debug: $(TARGET)

# Build target with symbols stripped (release mode)
release: CFLAGS = $(RELEASE_FLAGS)
release: $(TARGET)

# Build the target executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(CFLAGS) -I$(INCLUDE_PATH) -L$(LIBRARY_PATH) $(LDFLAGS)

# Compile .c files into .o object files
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) -I$(INCLUDE_PATH)

# Clean up build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Run memory leak check with Valgrind
valgrind: debug
	valgrind --leak-check=full ./$(TARGET)

# Run the game
run: $(TARGET)
	./$(TARGET)
