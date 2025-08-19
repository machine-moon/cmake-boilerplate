cmake_minimum_required(VERSION 3.21)

# --- Toolchain Selection ---
set(TOOLCHAIN "GNU" CACHE STRING "Compiler toolchain (GNU, Clang, MSVC)")
set(TOOLCHAIN_VERSION "12" CACHE STRING "Version of selected toolchain")
# between 6.x and 15.x for GNU & between 7.x and 20.x for Clang

if(TOOLCHAIN STREQUAL "GNU")
    set(CMAKE_C_COMPILER "gcc-${TOOLCHAIN_VERSION}")
    set(CMAKE_CXX_COMPILER "g++-${TOOLCHAIN_VERSION}")
    add_compile_options($<$<COMPILE_LANGUAGE:CXX,C>:-fdiagnostics-color=always>)
elseif(TOOLCHAIN STREQUAL "Clang")
    set(CMAKE_C_COMPILER "clang-${TOOLCHAIN_VERSION}")
    set(CMAKE_CXX_COMPILER "clang++-${TOOLCHAIN_VERSION}")
    add_compile_options($<$<COMPILE_LANGUAGE:CXX,C>:-fcolor-diagnostics>)
elseif(TOOLCHAIN STREQUAL "MSVC")
    set(CMAKE_C_COMPILER "cl")
    set(CMAKE_CXX_COMPILER "cl")
else()
    message(FATAL_ERROR "Unknown toolchain: ${TOOLCHAIN}. Supported: GNU, Clang, MSVC.")
endif()

# --- Project Name ---
project(twiz VERSION 0.0.2)
string(TOUPPER "${PROJECT_NAME}" _P)

# --- Output Directories ---
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# --- Generate version info ---
configure_file(
  ${CMAKE_SOURCE_DIR}/cmake/version.h.cmake
  ${CMAKE_SOURCE_DIR}/src/Headers/Version.h
)

# --- Find and use ccache if available to speed up builds ---
find_program(${_P}_CCACHE_FOUND ccache)
if(${_P}_CCACHE_FOUND)
    message(STATUS "[Compiler cache found. Using ccache to speed up builds.]")
    set(CMAKE_CXX_COMPILER_LAUNCHER ${${_P}_CCACHE_FOUND})
    set(CMAKE_C_COMPILER_LAUNCHER ${${_P}_CCACHE_FOUND})
    set(CMAKE_CUDA_COMPILER_LAUNCHER ${${_P}_CCACHE_FOUND})
    set(CMAKE_HIP_COMPILER_LAUNCHER ${${_P}_CCACHE_FOUND})
endif()

# --- General Settings ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# --- Options ---
set($(_p)_SANITIZER "off" CACHE STRING "Sanitizer: one of off, asan, tsan")
set_property(CACHE $(_p)_SANITIZER PROPERTY STRINGS "off;asan;tsan")

set($(_p)_WARNINGS_AS_ERRORS "off" CACHE STRING "Treat warnings as errors")
set_property(CACHE $(_p)_WARNINGS_AS_ERRORS PROPERTY STRINGS "off;on")

# --- Dependencies ---
include(cmake/functions.cmake)
include(cmake/dependencies.cmake)
set(external_dependencies ${system_dependencies} ${vendored_dependencies})

# --- Source Files ---
include(cmake/gpu.cmake)
file(GLOB_RECURSE gpu_sources CONFIGURE_DEPENDS src/Source/*.cu)
set_source_files_properties(${gpu_sources} PROPERTIES LANGUAGE ${${_P}_GPU_RUNTIME} COMPILE_DEFINITIONS "${${_P}_GPU_COMPILE_DEFS}")
file(GLOB_RECURSE cpu_sources CONFIGURE_DEPENDS src/Source/*.cpp)
set(source_files ${cpu_sources} ${gpu_sources})

# --- Library ---
add_library(${_P}-lib STATIC ${source_files})
target_include_directories(${_P}-lib PUBLIC src/Headers)
target_link_libraries(${_P}-lib PRIVATE ${external_dependencies})
apply_flags(${_P}-lib)
# --- Platform-Specific Settings ---
if(APPLE)
    # Add MacOS specific libraries here
elseif(UNIX AND NOT APPLE)
    target_link_libraries(${_P}-lib PRIVATE uuid)
elseif(WIN32)
    target_link_libraries(${_P}-lib PRIVATE Rpcrt4)
endif()

# --- Unified Executable ---
add_executable(${PROJECT_NAME} src/Source/main.cpp)
target_link_libraries(${PROJECT_NAME} ${_P}-lib)
apply_flags(${PROJECT_NAME})

# --- Installation ---
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin )
# install(DIRECTORY src/Headers/ DESTINATION include)

# --- Configuration Info ---
message(STATUS "[Platform: ${CMAKE_SYSTEM_NAME}]")
message(STATUS "[Compiler: ${CMAKE_CXX_COMPILER_ID}]")
message(STATUS "[C++ Standard: ${CMAKE_CXX_STANDARD}]")
message(STATUS "[Build Type: ${CMAKE_BUILD_TYPE}]")

# --- CPack Configuration ---
include(cmake/cpack.cmake)