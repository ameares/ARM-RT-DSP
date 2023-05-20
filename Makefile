CC := gcc
CFLAGS := -Wall -Wextra -std=c11 -I./include
LIBS := -lcunit

# Directories
SRC_DIR := src
TEST_DIR := tests

# Source and test files
SOURCES := $(wildcard $(SRC_DIR)/*.c)
TESTS := $(wildcard $(TEST_DIR)/*.c)

# Object files
OBJECTS := $(SOURCES:.c=.o)
TEST_OBJECTS := $(TESTS:.c=.o)

# Executables
EXECUTABLE := arm_rt_dsp
TEST_EXECUTABLE := rt_dsp_test_runner

.PHONY: all clean test

all: $(EXECUTABLE)

# Build the main library
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

# Build the test runner
$(TEST_EXECUTABLE): $(TEST_OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Rule for building object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the tests
test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

clean:
	rm -f $(OBJECTS) $(TEST_OBJECTS) $(EXECUTABLE) $(TEST_EXECUTABLE)