.PHONY: help all clean build build-debug build-release asan run run-debug run-asan

# Default goal when no target is specified
.DEFAULT_GOAL := help

# --- Configuration ---
# Use Ninja for faster builds if available, otherwise default to make
ifeq ($(shell command -v ninja),)
    CMAKE_GENERATOR := "Unix Makefiles"
else
    CMAKE_GENERATOR := "Ninja"
endif

# --- Primary Targets ---

help:
	@echo "Usage: make <target>"
	@echo ""
	@echo "Targets:"
	@echo "  help            Show this help message."
	@echo "  all             Build release, debug, and ASan configurations."
	@echo "  clean           Remove all build artifacts."
	@echo ""
	@echo "  build           Build the project in Release mode (default)."
	@echo "  build-debug     Build the project in Debug mode."
	@echo "  build-release   Alias for 'build'."
	@echo "  asan            Build the project in Debug mode with AddressSanitizer enabled."
	@echo ""
	@echo "  run             Run the Release build executable."
	@echo "  run-debug       Run the Debug build executable."
	@echo "  run-asan        Run the ASan-enabled executable."

all: build-release build-debug asan

clean:
	@echo "Cleaning up build directories..."
	@rm -rf build

# --- Build Targets ---

build: build-release

build-release:
	@echo "Building in Release mode..."
	@cmake -B build/release -DCMAKE_BUILD_TYPE=Release -G $(CMAKE_GENERATOR)
	@cmake --build build/release

build-debug:
	@echo "Building in Debug mode..."
	@cmake -B build/debug -DCMAKE_BUILD_TYPE=Debug -G $(CMAKE_GENERATOR)
	@cmake --build build/debug

asan:
	@echo "Building with AddressSanitizer..."
	@cmake -B build/asan -DCMAKE_BUILD_TYPE=Debug -DENABLE_ASAN=ON -G $(CMAKE_GENERATOR)
	@cmake --build build/asan

# --- Run Targets ---

run: build-release
	@echo "Running the Release build..."
	@./build/release/bin/twiz

run-debug: build-debug
	@echo "Running the Debug build..."
	@./build/debug/bin/twiz

run-asan: asan
	@echo "Running the ASan-enabled build..."
	@./build/asan/bin/twiz