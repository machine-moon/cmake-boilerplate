cmake_minimum_required(VERSION 3.16)
project(twiz)

# -- Find and use ccache if available to speed up builds --
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    message(STATUS "Compiler cache found. Using ccache to speed up builds.")
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
)

add_library(${PROJECT_NAME}-lib STATIC ${sources})
target_include_directories(${PROJECT_NAME}-lib PUBLIC src/Headers)
target_link_libraries(${PROJECT_NAME}-lib PUBLIC
    Boost::beast
    CGAL
    glad
    glfw
    glm
    imgui
    OpenGL::GL
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
if(ENABLE_ASAN)
    message(STATUS "Building with AddressSanitizer enabled")
    set(ASAN_FLAGS -fsanitize=address -fno-omit-frame-pointer)
    target_compile_options(${PROJECT_NAME} PRIVATE ${ASAN_FLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address)
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin )
# install(DIRECTORY src/Headers/ DESTINATION include)

# --- Configuration Info ---
message(STATUS "Platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

# --- CPack Configuration ---
include(cmake/cpack.cmake)