cmake_minimum_required(VERSION 3.28)

# Set the C and C++ compilers to clang if not already set
if(NOT CMAKE_C_COMPILER)
  set(CMAKE_C_COMPILER "/usr/bin/clang")
endif()

if(NOT CMAKE_CXX_COMPILER)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
  set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
endif()

project(sysc VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Turn off compiler-specific extensions
set(CMAKE_CXX_EXTENSIONS OFF)

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler-specific settings
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # Use libc++ with Clang
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # Use libstdc++ with GCC
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")
endif()

# Define compiler flags for different build types
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -Werror -pedantic -fsanitize=address -fsanitize=undefined")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -Wall -Wextra -Werror -pedantic")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -Wall -Wextra -Werror -pedantic")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -Wall -Wextra -Werror -pedantic")

# Function to add a project
function(add_project projectPath)
  get_filename_component(dirPath ${projectPath} DIRECTORY)
  get_filename_component(projectName ${dirPath} NAME)
  message(STATUS "[HIT] Found project >>${projectName}<<")

  file(GLOB projectSources CONFIGURE_DEPENDS "${dirPath}/*.cpp")
  add_executable(${projectName} ${projectSources})
  target_include_directories(${projectName} PUBLIC "${dirPath}/include")
endfunction()

# Add all projects in the src directory
file(GLOB_RECURSE mainFiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} main.cpp)

foreach(mainFile ${mainFiles})
  add_project(${mainFile})
endforeach()

# Add Google Test
enable_testing()
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

# Add tests
file(GLOB test_sources tests/*.cpp)
add_executable(testMe ${test_sources})
target_link_libraries(testMe gtest_main)

# Discover tests
include(GoogleTest)
gtest_discover_tests(testMe)