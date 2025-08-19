.PHONY: help all clean build debug release san run run-debug run-san run-release run-asan run-tsan format tidy package

APP_NAME ?= twiz
COMPILER=GNU 
args = ./foo.json

# --- General Targets ---

all:
	@echo "Usage: make <target>"
	@echo ""
	@echo "Targets:"
	@echo "  all                                 Show this help message."
	@echo "  clean                               Remove all build artifacts."
	@echo "  build                               Alias for any build."
	@echo ""
	@echo "  release                             Build in Release mode."
	@echo "  asan                                Build in AddressSanitizer mode."
	@echo "  tsan                                Build with ThreadSanitizer enabled."
	@echo ""
	@echo "  run                                 Run the latest executable."
	@echo "  run-{release|asan|tsan}             Run the specified build executable."
	@echo ""
	@echo "  format                              Format source files using clang-format."
	@echo "  tidy                                Format source files using clang-tidy."
	@echo "  package                             Package the Release build (ZIP/DEB/RPM)."

clean:
	@echo "Cleaning up build directories..."
	@rm -rf build

build: release

# --- Build Targets ---

release:
	@echo "Building in Release mode..."
	@cmake -B build/release -G Ninja -DCMAKE_BUILD_TYPE=Release
	@cmake --build build/release
	@cp build/release/compile_commands.json build/compile_commands.json || true

asan:
	@echo "Building in AddressSanitizer mode..."
	@cmake -B build/asan -G Ninja -DSANITIZER=asan
	@cmake --build build/asan
	@cp build/asan/compile_commands.json build/compile_commands.json || true

tsan:
	@echo "Building with ThreadSanitizer..."
	@cmake -B build/tsan -G Ninja -DSANITIZER=tsan
	@cmake --build build/tsan
	@cp build/tsan/compile_commands.json build/compile_commands.json || true


# --- Run Targets ---

run: build
	@echo "Scanning for latest binary..."
	@bins=$$(ls -1 build/*/bin/$(APP_NAME) 2>/dev/null); \
	if [ -z "$$bins" ]; then \
		echo "No binaries named '$(APP_NAME)' found in build/*/bin/."; \
		exit 1; \
	else \
		latest_bin=$$(ls -1t build/*/bin/$(APP_NAME) 2>/dev/null | head -n1); \
		echo "Running the latest built binary: $$latest_bin"; \
		"$$latest_bin" $(args); \
	fi
	
run-release: release
	@echo "Running the Release build..."
	@./build/release/bin/twiz $(args)

run-asan: asan
	@echo "Running the AddressSanitizer build..."
	@./build/asan/bin/twiz $(args)

run-tsan: tsan
	@echo "Running the ThreadSanitizer-enabled build..."
	@./build/tsan/bin/twiz $(args)

# --- Utils & Tooling ---

format:
	@echo "Running clang-format..."
	@find src/ \( -name "*.cpp" -o -name "*.hpp" -o -name "*.cc" -o -name "*.cxx" -o -name "*.c" -o -name "*.h" \) -exec clang-format -style=file -i {} +

tidy:
	@echo "Running clang-tidy with -fix and -fix-errors..."
	@find src/ \( -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) -exec clang-tidy -p build -fix -fix-errors --quiet --header-filter='^src/.*' {} \;

package: release
	@cd build/release && cpack && cpack -G DEB && cpack -G RPM
# todo rpm 
# sudo dpkg -i /path/to/twiz/build/release/twiz-1.0.0-linux.deb
# list files dpkg-deb -c build/release/twiz-1.0.0-linux.deb