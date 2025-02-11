# cmake boilerplate

## Overview

This project is a C++ boilerplate that uses CMake to compile multiple projects. Each project is compiled into a binary named after its directory in the `src/*` folder. The setup includes support for Clang, Ninja, and Google Test.

I built this to keep up with my C++ class, allowing me to write code as notes.

## Requirements

To build and run this project, you need the following tools installed on your system:

- **LLVM**: [Release Notes](https://releases.llvm.org/)
- **Clang**: [Release Notes](https://releases.llvm.org/)
- **clang-tools-extra**: [Release Notes](https://releases.llvm.org/)
- **LLD**: [Release Notes](https://releases.llvm.org/)
- **libc++**: [Release Notes](https://releases.llvm.org/)
- **CMake**: [Installation Guide](https://cmake.org/install/)
- **Make**: [Installation Guide](https://www.gnu.org/software/make/)
- **Ninja**: [Installation Guide](https://ninja-build.org/)
- **Google Test**: [GitHub Repository](https://github.com/google/googletest)

### Installation on Ubuntu

```sh
sudo apt update
sudo apt install llvm clang clang-tools-extra lld libc++-dev cmake make ninja-build
```

## Makefile Usage
The provided `Makefile` includes several useful targets to streamline your workflow:

1. **Configures and builds the project using CMake and Ninja.**:
    ```sh
    make
    ```

2. **Clean the build and bin directories**:
    ```sh
    make clean
    ```
3. **Rebuild the project from scratch**:
    ```sh
    make fresh
    ```

4. **Run the latest executable**:
    ```sh
    make run
    ```

5. **Run the tests**:
    ```sh
    make test
    ```

These commands help automate the build and test process, making it easier to manage the project.


## Project Structure

- `src/`: Contains the source code for multiple projects. Each subdirectory represents a separate project.
- `tests/`: Contains the test cases.
- `build/`: Directory where the build files are generated.
- `bin/`: Directory where the compiled binaries are placed.

## CMake Configuration

The `CMakeLists.txt` file is configured to:

- Set the C and C++ compilers to Clang.
- Use C++23 standard.
- Compile each project in the `src/*` directory into a separate binary.
- Enable Google Test for unit testing.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.