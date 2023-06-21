CC := gcc
CFLAGS := -Wall -Wextra -std=c11 -I./include -fprofile-arcs -ftest-coverage
LIBS := -lcunit

# Directories
SRC_DIR := src
TEST_DIR := tests
OBJ_DIR := obj
TEST_OUT_DIR := tests_out
SCRIPT_DIR := scripts

# Source and test files
SOURCES := $(wildcard $(SRC_DIR)/*.c)
TESTS := $(wildcard $(TEST_DIR)/*.c)

# Object files
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))
TEST_OBJECTS := $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/%.o,$(TESTS))

# Executables
EXECUTABLE := arm_rt_dsp
TEST_EXECUTABLE := rt_dsp_test_runner

.PHONY: all clean test coverage plot

all: $(EXECUTABLE)

# Build the main library
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ -fprofile-arcs -ftest-coverage

# Build the test runner
$(TEST_EXECUTABLE): $(TEST_OBJECTS) $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS) -fprofile-arcs -ftest-coverage

# Rule for building object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Run the tests
test: clean $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

# Run coverage
coverage: test
	gcov -r $(OBJ_DIR)/*.gcda

# Generate plots from CSV files
plot:
	for csv in $(TEST_OUT_DIR)/*.csv; do \
		png="$${csv%.csv}.png"; \
		python3 $(SCRIPT_DIR)/plot_csv.py "$$csv" "$$png"; \
	done

clean:
	rm -f $(OBJECTS) $(TEST_OBJECTS) $(EXECUTABLE) $(TEST_EXECUTABLE)
	rm -f $(OBJ_DIR)/*.gcda $(OBJ_DIR)/*.gcno $(OBJ_DIR)/*.gcov