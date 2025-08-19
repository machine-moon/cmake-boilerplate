# twiz

A simple, cross-platform OpenGL experimentation project.

## Building and Running

### Prerequisites

Before building, you need to install the appropriate system dependencies for your platform.

```bash
pip install glad jinja2
```

**Fedora:**
```bash
sudo dnf install gcc-c++ clang cmake ninja-build mesa-libGL-devel libX11-devel libXrandr-devel libXinerama-devel libXcursor-devel libXi-devel gmp-devel mpfr-devel wayland-devel wayland-protocols-devel libxkbcommon-devel
```

**Ubuntu:**
```bash
sudo apt-get install build-essential clang cmake ninja-build ccache libgl1-mesa-dev xorg-dev libgmp-dev libmpfr-dev libwayland-dev wayland-protocols libxkbcommon-dev
```

**macOS:**
```bash
xcode-select --install
brew install cmake ninja
```

**Windows:**

Install Visual Studio with the "Desktop development with C++" workload, CMake, and Ninja.

### Build

```bash
make build
```

### Run

```bash
make run
```

## Platform Independence

This project is designed to be platform-independent and should compile and run on Linux, Windows, and macOS. This is achieved by using cross-platform libraries like GLFW, GLM, and Dear ImGui, which abstract away the underlying operating system details.

### System Headers vs. Cloned Dependencies

This project uses a hybrid approach to dependencies:

- **System Dependencies:** OpenGL is expected to be provided by the system's graphics driver. You must install the appropriate headers and libraries for your platform (see Prerequisites).
- **Cloned Dependencies:** All other libraries (GLFW, GLM, Dear ImGui, Boost) are fetched automatically at configure time by CMake using `CPM.cmake`. This ensures that all developers are using the exact same version of these libraries, leading to more reproducible builds.

| Dependency        | Vendored/CPM | System Installed | Platform-Specific? |
|-------------------|:------------:|:----------------:|:------------------:|
| GLFW              |   Yes        |   No             |   No               |
| GLM               |   Yes        |   No             |   No               |
| ImGui             |   Yes        |   No             |   No               |
| Boost             |   Yes        |   No             |   No               |
| OpenGL (headers)  |   No         |   Yes            |   Yes (drivers)    |

### Cross-Compilation (Linux to Windows)

You can build a Windows executable from a Linux environment (like Fedora) by using the `mingw-w64` toolchain.

1.  **Install MinGW-w64 on Fedora:**
    ```bash
    sudo dnf install mingw64-gcc-c++
    ```

2.  **Build with the Windows toolchain file:**
    ```bash
    cmake -B build-windows -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/windows-x86_64.cmake
    cmake --build build-windows
    ```
# twiz
