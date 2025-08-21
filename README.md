# twiz: A Modern C++ OpenGL Project Template

Welcome to **twiz**! This isn't just another project; it's a meticulously crafted, modern C++ template designed for building high-performance OpenGL applications. It serves as a powerful and clean foundation for graphics experiments, game development, or any creative coding project.

We are incredibly proud of the clean, modular, and portable architecture of this template. It's built with best practices to be robust, easy to use, and a joy to develop with.

## Features

- **Modern C++:** Utilizes C++20 for modern, clean, and expressive code.
- **Powerful & Modular CMake Build System:** A clean, easy-to-understand CMake setup that is both powerful and extensible.
- **Automatic Dependency Management:** Uses [`CPM.cmake`](https://github.com/cpm-cmake/CPM.cmake) to automatically fetch and manage all dependencies. No more manual downloading or submodule wrestling!
- **Cross-Platform Ready:** Designed from the ground up to support Linux, macOS, and Windows.
- **Batteries-Included Dependencies:** Comes pre-configured with a suite of essential libraries:
    - **`glad`**: For loading modern OpenGL functions.
    - **`glfw`**: For windowing, contexts, and input.
    - **`glm`**: For all your mathematics needs (vectors, matrices, etc.).
    - **`imgui`**: For creating beautiful and simple immediate-mode graphical user interfaces.
    - **`boost`**: For a wide range of high-quality, peer-reviewed portable C++ source libraries.
    - **`CGAL`**: For powerful computational geometry algorithms.
- **Developer-Friendly Tooling:**
    - **Convenience `Makefile`**: Simple commands (`make build`, `make run`) to abstract away CMake's complexities.
    - **`ccache` Integration**: Automatically detects and uses `ccache` to dramatically speed up rebuilds.
    - **Address Sanitizer (ASan)**: Integrated target (`make asan`) to find memory errors with ease.
    - **Packaging Ready**: Pre-configured with `CPack` to generate installers and packages for distribution.

## Getting Started

### System Dependencies

Before you begin, you'll need a few things installed on your system:

- A modern C++ compiler (GCC, Clang, or MSVC)
- `CMake` (version 3.16 or higher)
- `Ninja` (recommended for faster builds)
- `git`
- **OpenGL** drivers for your graphics card.
- **For CGAL:** You will need to install `gmp` and `mpfr`.
    - On Debian/Ubuntu: `sudo apt-get install libgmp-dev libmpfr-dev`
    - On macOS (with Homebrew): `brew install gmp mpfr`

### Building the Project

Building is designed to be as simple as possible thanks to the `Makefile` wrapper.

```bash
# 1. Clone the repository
git clone <your-repo-url>
cd twiz

# 2. Build the project (this will also fetch all dependencies)
make build

# 3. Run the application
make run
```

### Available Make Targets

The `Makefile` provides several targets for common tasks:

| Command         | Description                                                 |
| --------------- | ----------------------------------------------------------- |
| `make build`    | Build the project in **Release** mode.                      |
| `make run`      | Run the Release executable.                                 |
| `make build-debug`| Build the project in **Debug** mode for easier debugging.   |
| `make run-debug`| Run the Debug executable.                                   |
| `make asan`     | Build in Debug mode with **AddressSanitizer** enabled.      |
| `make run-asan` | Run the ASan-enabled executable to find memory errors.      |
| `make clean`    | Remove all build artifacts.                                 |
| `make format`   | Automatically format all source code with `clang-format`.   |
| `make package`  | Generate a distributable package using `CPack`.             |

## Build System Architecture

The heart of this project is its clean and modular CMake setup. We've designed it to be easy to understand and extend.

The architecture follows a clear hierarchy:

```
  Makefile (User-friendly wrapper)
      │
      └─> Calls cmake to configure and build
            │
            ├─> CMakeLists.txt (The main entry point)
            │   │
            │   ├─ Sets up project-wide settings (C++ standard, compiler flags)
            │   ├─ Defines the library and executable targets
            │   └─ Includes the central dependency file:
            │        │
            │        └─> include(cmake/dependencies.cmake)
            │              │
            │              ├─ Fetches CPM.cmake (our package manager)
            │              └─ Includes individual modules for each dependency:
            │                    │
            │                    ├─> include(cmake/modules/glad.cmake) ───> CPMAddPackage(glad)
            │                    ├─> include(cmake/modules/glfw.cmake) ───> CPMAddPackage(glfw)
            │                    ├─> include(cmake/modules/glm.cmake)  ───> CPMAddPackage(glm)
            │                    └─> ... (and so on for each dependency)
            │
            └─> src/ (Your source code)
```

### Key Components Explained

- **`Makefile`**: Provides simple, top-level commands for users. It intelligently detects `ninja` for faster builds and creates separate build directories (`build/release`, `build/debug`) for each configuration.

- **`CMakeLists.txt` (Root)**: This is the conductor of the orchestra. It sets global project settings, defines the final executable and library, and includes the main dependency file. It remains clean and high-level.

- **`cmake/dependencies.cmake`**: This file is the central hub for managing dependencies. It's responsible for including `CPM.cmake` and then including a separate module for each library we depend on. This keeps our main `CMakeLists.txt` from getting cluttered with package details.

- **`cmake/modules/*.cmake`**: This is where the magic of modularity happens. Each dependency has its own `.cmake` file (e.g., `glfw.cmake`, `imgui.cmake`). This file contains the `CPMAddPackage()` call and any specific configuration, include directories, or linking logic needed for that single library. This makes it incredibly easy to add, remove, or update a dependency without touching any other part of the build system.

This architecture ensures that our project is **scalable**, **maintainable**, and a pleasure to work on.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
