# Define the build directory and the binary directory
BUILD_DIR = build
BIN_DIR = bin

# Default target
all: build

# Build the project
build:
	@echo "[Configuring and building with Ninja]"
	@cmake -S . -B $(BUILD_DIR) -G Ninja
	@cmake --build $(BUILD_DIR)

# Build the project with tests and debug messages enabled
build_all:
	@echo "[Building tests with debug messages]"
	@cmake -S . -B $(BUILD_DIR) -G Ninja -DENABLE_TESTING=ON -DENABLE_DEBUG_MESSAGES=ON
	@cmake --build $(BUILD_DIR)

# Run the latest executable
run: build
	@echo "[Looking for latest executable]"
	@latest_file=$$(find $(BIN_DIR) -type f -printf '%T@ %p\n' | sort -nr | head -n 1 | cut -d' ' -f2); \
	[ -n "$$latest_file" ] && echo "[Running $$latest_file]" && $$latest_file || echo "[No executable found]"

# Run tests
test: build_all
	@echo "[Running tests]"
	@ctest --test-dir $(BUILD_DIR)

# Clean build and binary directories
clean:
	@echo "[Cleaning bin and build directories]"
	@rm -rf $(BIN_DIR) $(BUILD_DIR)

# Clean and all(build) the project
fresh: clean all

.PHONY: all build build_all run test clean fresh