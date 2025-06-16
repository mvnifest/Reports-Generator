# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g $(INCLUDES)

# Include directories (recursive)
INCLUDES = $(foreach dir,$(shell find include -type d),-I$(dir))

# Source files from all src/ and src/** subfolders
SRC = $(wildcard src/*.c) $(wildcard src/**/*.c)
SRC := $(subst \,/,$(SRC))
OBJ = $(patsubst src/%.c,build/%.o,$(SRC)) \
    build/input/configs/config_reader.o \
    build/input/entries/entry_reader.o \
    build/input/absences/absence_reader.o \
    build/input/configs/config_storage.o \
    build/input/entries/entry_parser.o \
    build/input/entries/entry_storage.o \
    build/input/absences/absence_storage.o

# Output binary name
EXEC = rcp_app

# Detect OS for Windows-specific linker flags
ifeq ($(OS),Windows_NT)
    WINFLAGS = -Wl,-subsystem,console
else
    WINFLAGS =
endif

# Link all object files into executable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(WINFLAGS) -o $@ $^

# Compile .c files to .o files into corresponding build folder (handles subdirectories)
build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean generated files
clean:
	rm -rf build
	rm -f $(EXEC)

# Convenience phony targets
.PHONY: all clean
