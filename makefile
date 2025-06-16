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

.PHONY: test

test:
	$(CC) -Wall -Wextra -g -Iinclude \
		tests/test_runner.c \
		tests/configs/test_config_storage.c \
		tests/configs/test_config_reader.c \
		tests/entries/test_entry_storage.c \
		tests/entries/test_entry_parser.c \
		tests/entries/test_entry_reader.c \
		tests/absences/test_absence_storage.c \
		tests/absences/test_absence_reader.c \
		tests/user/test_user_db.c \
		tests/user/test_user_storage.c \
		tests/reports/test_report_writer.c \
		src/input/configs/config_storage.c \
		src/input/configs/config_reader.c \
		src/input/entries/entry_storage.c \
		src/input/entries/entry_parser.c \
		src/input/entries/entry_reader.c \
		src/input/absences/absence_storage.c \
		src/input/absences/absence_reader.c \
		src/user/user_db.c \
		src/user/user_storage.c \
		src/reports/report_writer.c \
		-o bin/test_runner
	./bin/test_runner

