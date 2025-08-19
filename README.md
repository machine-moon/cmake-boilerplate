

# twiz: Modern CMake Project Template

**twiz** is a modern C++20 template for high-performance GPU-accelerated applications. It is modular, portable, and designed for clarity and performance.



## Features

- **C++20 & CUDA**: Modern C++ and GPU support
- **Modular CMake Build**: Clean, extensible, toolchain-selectable
- **Automatic Dependency Management**: [`CPM.cmake`](https://github.com/cpm-cmake/CPM.cmake)
- **Cross-Platform**: Linux, macOS, Windows
- **Sanitizer Support**: AddressSanitizer (ASan), ThreadSanitizer (TSan)
- **Developer Tooling**: Makefile wrapper, ccache, clang-format, clang-tidy, CPack packaging


## Getting Started



### Prerequisites

- C++20 compiler (GNU, Clang, MSVC; toolchain selectable)
- CMake >= 3.21
- Ninja (recommended)
- git
- CUDA toolkit (for GPU builds)


#### System Libraries

Install these system packages before building:

**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install libgl1-mesa-dev libssl-dev libzmq3-dev libsodium-dev libffmpeg-dev uuid-dev
```

**Fedora:**
```bash
sudo dnf install mesa-libGL-devel openssl-devel zeromq-devel libsodium-devel ffmpeg-devel libuuid-devel
```

**Other requirements:**
- CUDA toolkit (if using GPU features)




### Build & Run

```bash
# Clone and enter the repo
git clone <your-repo-url>
cd twiz

# Build (Release, fetches dependencies)
make release

# Build with AddressSanitizer
make asan

# Build with ThreadSanitizer
make tsan

# Run latest built binary
make run

# Run specific build
make run-release
make run-asan
make run-tsan

# Format code
make format

# Tidy code
make tidy

# Package (ZIP/DEB/RPM)
make package
```

#### Toolchain Selection
Select compiler toolchain and version via CMake cache variables:
```bash
cmake -B build/release -G Ninja -DCMAKE_BUILD_TYPE=Release -DTOOLCHAIN=GNU -DTOOLCHAIN_VERSION=12
```
Supported: GNU, Clang, MSVC. See `CMakeLists.txt`.



### Makefile Targets

| Target         | Description                                 |
|----------------|---------------------------------------------|
| all            | Show help message                           |
| clean          | Remove all build artifacts                   |
| release        | Build in Release mode                        |
| asan           | Build with AddressSanitizer                  |
| tsan           | Build with ThreadSanitizer                   |
| run            | Run latest built binary                      |
| run-release    | Run Release build                            |
| run-asan       | Run ASan build                               |
| run-tsan       | Run TSan build                               |
| format         | Format code with clang-format                |
| tidy           | Format code with clang-tidy                  |
| package        | Package Release build (ZIP/DEB/RPM)          |



## Build System Overview

```
Makefile (user wrapper)
  └─> CMakeLists.txt (main entry)
      ├─ Toolchain selection, project settings, targets
      └─ include(cmake/dependencies.cmake)
          ├─ Fetch CPM.cmake
          └─ include(cmake/modules/*.cmake) for each dependency
src/ (source code)
```

Dependencies are managed in `cmake/modules/` for modularity. System and vendored dependencies are linked in `cmake/dependencies.cmake`.



## Dependencies

**System:**
- OpenGL (libgl1-mesa-dev / mesa-libGL-devel)
- OpenSSL (libssl-dev / openssl-devel)
- ZeroMQ (libzmq3-dev / zeromq-devel)
- libsodium (libsodium-dev / libsodium-devel)
- FFmpeg (libffmpeg-dev / ffmpeg-devel)
- uuid (uuid-dev / libuuid-devel)
- CUDA toolkit (for GPU builds)

**Vendored (via CPM.cmake):**
- glad
- glfw
- glm
- imgui
- boost (boost, filesystem, regex, system)
- CGAL
- jsoncons
- lz4
- cppzmq
- spdlog

See `cmake/dependencies.cmake` and `cmake/modules/` for details.

## Versioning

Project versioning is managed via git and CMake. See `CMakeLists.txt` and `src/Headers/Version.h`.

## License

MIT License. See [LICENSE](LICENSE).
