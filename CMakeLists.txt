cmake_minimum_required(VERSION 3.16)
project(twiz)
set(TWIZ ${PROJECT_NAME}) 


# Generate compile_commands.json for IDE integration
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find and use ccache if available to speed up builds
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    message(STATUS "Compiler cache found. Using ccache to speed up builds.")
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_FOUND})
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_FOUND})
endif()


# Compiler flags
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


# General settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Options
option(ENABLE_ASAN "Enable Address Sanitizer" OFF)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)

# Dependency management
include(cmake/dependencies.cmake)
find_package(OpenGL REQUIRED)

# --- Targets ---

set(sources
    src/Source/main.cpp
)

set(headers
    src/Headers
)


set(${TWIZ}_deps "${CGAL_PACKAGE_INCLUDES};${Boost_INCLUDE_DIRS};${glad_include_dir}")

add_library(${TWIZ}-lib STATIC ${sources} ${examples})
target_include_directories(${TWIZ}-lib PUBLIC ${headers} src/Examples ${Boost_INCLUDE_DIRS} PRIVATE ${TWIZ}_deps)

add_executable(${TWIZ} src/Source/main.cpp)
target_include_directories(${TWIZ} PUBLIC ${headers} src/Examples ${Boost_INCLUDE_DIRS})
target_link_libraries(${TWIZ}
    ${TWIZ}-lib
    glad
    glfw
    glm
    Boost::beast
    imgui
    OpenGL::GL
    CGAL
)




# --- Platform-specific settings ---

# On Apple, we might need to link against other frameworks
if(APPLE)
    # Add MacOS specific libraries here
# On Linux, we might need to link against other libraries
elseif(UNIX AND NOT APPLE)
    # Add linux specific libraries here
# On Windows, we might need to link against other libraries
elseif(WIN32)
    # Add windows specific libraries here
endif()

# --- Sanitizers ---
if(ENABLE_ASAN)
    message(STATUS "Building with AddressSanitizer enabled")
    set(ASAN_FLAGS -fsanitize=address -fno-omit-frame-pointer)
    target_compile_options(${TWIZ} PRIVATE ${ASAN_FLAGS})
    target_link_options(${TWIZ} PRIVATE -fsanitize=address)
endif()

install(TARGETS ${TWIZ}
    RUNTIME DESTINATION bin
)
install(DIRECTORY include/ DESTINATION include)


# Print configuration info
message(STATUS "Platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Testing enabled: ${ENABLE_TESTS}")
message(STATUS "Building executable: ${BUILD_EXECUTABLE}")
message(STATUS "All dependencies are obtained via CPM or bundled sources. System libraries for glfw, glm, boost, cgal, glad, imgui, ffmpeg are NOT used.")

# CPack configuration
include(cmake/cpack.cmake)