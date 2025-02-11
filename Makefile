# Define the build directory and the binary directory
BUILD_DIR = build 
BIN_DIR =   bin
LATEST = latest

all: build

build:
	@echo "[Configuring and building with Ninja]"
	@cmake -S . -B $(BUILD_DIR) -G Ninja
	@cmake --build $(BUILD_DIR)

clean:
	@echo "[Cleaning bin directory]"
	@rm -rf $(BIN_DIR)
	@echo "[Cleaning build directory]"
	@rm -rf $(BUILD_DIR)

fresh: clean build 

# Run the latest executable (stat -c '%Y' to get the last modified time)
run:
	@latest_file=$$(find $(BIN_DIR) -type f -printf '%T@ %p\n' | sort -k1,1nr | head -n 1 | cut -d' ' -f2); \
	if [ -n "$$latest_file" ]; then \
		echo "[Running project $$latest_file]"; \
		$$latest_file; \
	else \
		echo "No executable found."; \
	fi

test:
	@echo "Running tests..."
	@cmake -S . -B $(BUILD_DIR) -DENABLE_TESTING=ON -G Ninja 
	@cmake --build $(BUILD_DIR)
	@ctest --test-dir $(BUILD_DIR)

.PHONY: all build clean run fresh test