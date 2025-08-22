cmake_minimum_required(VERSION 3.16)
project(twiz)

# -- Find and use ccache if available to speed up builds --
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    message(STATUS "[Compiler cache found. Using ccache to speed up builds.]")
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_FOUND})
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_FOUND})
endif()

# --- General Settings ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- Options ---
option(ENABLE_ASAN "Enable Address Sanitizer" OFF)

# --- Output Directories ---
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# --- Dependencies ---
include(cmake/dependencies.cmake)
find_package(OpenGL REQUIRED)

# --- Project Library ---
set(sources
    src/Source/boost_example.cpp
    src/Source/cgal_example.cpp
    src/Source/glad_example.cpp
    src/Source/glfw_example.cpp
    src/Source/glm_example.cpp
    src/Source/imgui_example.cpp
    src/Source/something.cpp
    src/Source/jsoncons_example.cpp
    src/Source/lz4_example.cpp
)

add_library(${PROJECT_NAME}-lib STATIC ${sources})
target_include_directories(${PROJECT_NAME}-lib PUBLIC src/Headers)
target_link_libraries(${PROJECT_NAME}-lib PUBLIC
    Boost::filesystem 
    Boost::regex 
    Boost::system # shared libs
    Boost::headers_only
    CGAL
    glad
    glfw
    glm
    imgui
    OpenGL::GL
    lz4
    jsoncons
)

# --- Compiler Flags ---
if(MSVC)
    set(COMMON_CXX_FLAGS "/W4")
    set(CMAKE_CXX_FLAGS_DEBUG "/Od /Zi ${COMMON_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 ${COMMON_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/O2 /Zi ${COMMON_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "/O1 ${COMMON_CXX_FLAGS}")
else()
    set(COMMON_CXX_FLAGS "-Wall -Wextra -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "-g ${COMMON_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 ${COMMON_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g ${COMMON_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os ${COMMON_CXX_FLAGS}")
endif()

# --- Executable ---
add_executable(${PROJECT_NAME} src/Source/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)

# --- Platform-Specific Settings ---
if(APPLE)
    # Add MacOS specific libraries here
elseif(UNIX AND NOT APPLE)
    # Add linux specific libraries here
elseif(WIN32)
    # Add windows specific libraries here
endif()

# --- Sanitizers ---
option(ENABLE_ASAN "Build with address sanitizer" OFF)
option(ENABLE_TSAN "Build with thread sanitizer" OFF)
option(ENABLE_UBSAN "Build with undefined behavior sanitizer" OFF)

set(SANITIZER_COMPILE_FLAGS)
set(SANITIZER_LINK_FLAGS)

if(MSVC)
    if(ENABLE_ASAN)
        set(CMAKE_BUILD_TYPE "RelWithDebInfo")
    message(STATUS "[Instrumenting with Address Sanitizer (MSVC)]")
        list(APPEND SANITIZER_COMPILE_FLAGS /fsanitize=address)
        list(APPEND SANITIZER_LINK_FLAGS /fsanitize=address)
    endif()
    if(ENABLE_TSAN)
        set(CMAKE_BUILD_TYPE "RelWithDebInfo")
    message(WARNING "[ThreadSanitizer is not supported for MSVC.]")
    endif()
    if(ENABLE_UBSAN)
        set(CMAKE_BUILD_TYPE "Debug")
    message(WARNING "[UBSan is not supported for MSVC.]")
    endif()
else()
    # Clang/GNU
    if(ENABLE_ASAN)
        set(CMAKE_BUILD_TYPE "RelWithDebInfo")
    message(STATUS "[Instrumenting with Address Sanitizer (Clang/GNU)]")
        list(APPEND SANITIZER_COMPILE_FLAGS -fsanitize=address -fno-omit-frame-pointer)
        list(APPEND SANITIZER_LINK_FLAGS -fsanitize=address -fno-omit-frame-pointer)
        if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
            list(APPEND SANITIZER_COMPILE_FLAGS -fsanitize-address-use-after-scope)
            list(APPEND SANITIZER_LINK_FLAGS -fsanitize-address-use-after-scope)
        endif()
    endif()
    if(ENABLE_TSAN)
        set(CMAKE_BUILD_TYPE "RelWithDebInfo")
    message(STATUS "[Instrumenting with Thread Sanitizer (Clang/GNU)]")
        list(APPEND SANITIZER_COMPILE_FLAGS -fsanitize=thread -fno-omit-frame-pointer)
        list(APPEND SANITIZER_LINK_FLAGS -fsanitize=thread)
        if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
            list(APPEND SANITIZER_COMPILE_FLAGS -mllvm -tsan-instrument-memory-accesses=0 -mllvm -tsan-instrument-atomics=0 -mllvm -tsan-instrument-func-entry-exit=1 -fPIE)
            list(APPEND SANITIZER_LINK_FLAGS -pie -Qunused-arguments)
        endif()
    endif()
    if(ENABLE_UBSAN)
        set(CMAKE_BUILD_TYPE "Debug")
    message(STATUS "[Instrumenting with Undefined Behavior Sanitizer (Clang/GNU)]")
        list(APPEND SANITIZER_COMPILE_FLAGS -fsanitize=undefined -fno-omit-frame-pointer)
        list(APPEND SANITIZER_LINK_FLAGS -fsanitize=undefined -fno-omit-frame-pointer)
        if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
            list(APPEND SANITIZER_COMPILE_FLAGS -fsanitize=implicit-conversion -fsanitize=implicit-integer-truncation -fsanitize=integer -fsanitize=nullability -fsanitize=vptr)
            list(APPEND SANITIZER_LINK_FLAGS -fsanitize=implicit-conversion -fsanitize=implicit-integer-truncation -fsanitize=integer -fsanitize=nullability -fsanitize=vptr)
        endif()
    endif()
endif()

if(SANITIZER_COMPILE_FLAGS)
    target_compile_options(${PROJECT_NAME} PRIVATE ${SANITIZER_COMPILE_FLAGS})
    target_compile_options(${PROJECT_NAME}-lib PRIVATE ${SANITIZER_COMPILE_FLAGS})
endif()
if(SANITIZER_LINK_FLAGS)
    target_link_options(${PROJECT_NAME} PRIVATE ${SANITIZER_LINK_FLAGS})
    target_link_options(${PROJECT_NAME}-lib PRIVATE ${SANITIZER_LINK_FLAGS})
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin )
# install(DIRECTORY src/Headers/ DESTINATION include)

# --- Configuration Info ---
message(STATUS "[Platform: ${CMAKE_SYSTEM_NAME}]")
message(STATUS "[Compiler: ${CMAKE_CXX_COMPILER_ID}]")
message(STATUS "[C++ Standard: ${CMAKE_CXX_STANDARD}]")
message(STATUS "[Build Type: ${CMAKE_BUILD_TYPE}]")

# --- CPack Configuration ---
include(cmake/cpack.cmake)