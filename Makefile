.PHONY: help all clean build build-debug build-release asan run run-debug run-asan

APP_NAME ?= twiz

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
	@cmake -B build/release -DCMAKE_BUILD_TYPE=Release -G Ninja -Wno-deprecated
	@cmake --build build/release
	@cp build/release/compile_commands.json build/compile_commands.json || true

build-debug:
	@echo "Building in Debug mode..."
	@cmake -B build/debug -DCMAKE_BUILD_TYPE=Debug -G Ninja -Wno-deprecated
	@cmake --build build/debug
	@cp build/debug/compile_commands.json build/compile_commands.json || true

asan:
	@echo "Building with AddressSanitizer..."
	@cmake -B build/asan -DCMAKE_BUILD_TYPE=Debug -DENABLE_ASAN=ON -G Ninja -Wno-deprecated
	@cmake --build build/asan
	@cp build/asan/compile_commands.json build/compile_commands.json || true

# --- Run Targets ---

run: build
	@echo "Scanning for latest binary in build/*/bin/ ..."
	@bins=$$(ls -1 build/*/bin/$(APP_NAME) 2>/dev/null); \
	if [ -z "$$bins" ]; then \
		echo "No binaries named '$(APP_NAME)' found in build/*/bin/."; \
		exit 1; \
	else \
		latest_bin=$$(ls -1t build/*/bin/$(APP_NAME) 2>/dev/null | head -n1); \
		echo "Running the latest built binary: $$latest_bin"; \
		"$$latest_bin"; \
	fi
	
run-release: build-release
	@echo "Running the Release build..."
	@./build/release/bin/twiz

run-debug: build-debug
	@echo "Running the Debug build..."
	@./build/debug/bin/twiz

run-asan: asan
	@echo "Running the ASan-enabled build..."
	@./build/asan/bin/twiz

# --- Utils & Tooling ---

format:
	@find src/ \( -name "*.cpp" -o -name "*.hpp" -o -name "*.cc" -o -name "*.cxx" -o -name "*.c" -o -name "*.h" \) -exec clang-format -style=file -i {} +


package: build
	@cd build/release && cpack && cpack -G DEB && cpack -G RPM
# todo rpm 
# sudo dpkg -i /path/to/twiz/build/release/twiz-1.0.0-linux.deb
# list files dpkg-deb -c build/release/twiz-1.0.0-linux.deb 