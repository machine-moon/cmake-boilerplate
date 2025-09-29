set(CMAKE_CXX_FLAGS_RELEASE "-w")
CPMAddPackage(
    NAME boost
    VERSION 1.89.0
    GIT_TAG boost-1.89.0
    GITHUB_REPOSITORY boostorg/boost
    OPTIONS
        "Boost_VERBOSE OFF"
        "BUILD_SHARED_LIBS 1" # SHARED (1) = .so/.dll  | STATIC(0) = .a/.lib 
        "BUILD_TESTING OFF"
        "BOOST_ENABLE_CMAKE 1" 
)
unset(CMAKE_CXX_FLAGS_RELEASE)

add_library(boost_headers_only INTERFACE)
file(GLOB BOOST_INCLUDE_DIRS "${boost_SOURCE_DIR}/libs/*/include")
target_include_directories(boost_headers_only INTERFACE ${BOOST_INCLUDE_DIRS})

add_library(Boost::headers_only ALIAS boost_headers_only)
add_library(Boost::boost ALIAS boost_headers_only)

# Reference for available Boost CMake targets that require linking to compiled libraries (non header-only)
set(ALL_BOOST_TARGETS
    Boost::filesystem
    Boost::system
    Boost::thread
    Boost::chrono
    Boost::regex
    Boost::date_time
    Boost::atomic
    Boost::iostreams
    Boost::program_options
    Boost::serialization
    Boost::random
    Boost::timer
    Boost::log
    Boost::log_setup
    Boost::unit_test_framework
    Boost::test_exec_monitor
    Boost::container
    Boost::context
    Boost::coroutine
    Boost::fiber
    Boost::graph
    Boost::math
    Boost::wave
    Boost::stacktrace
    Boost::type_erasure
    Boost::contract
    Boost::locale
    Boost::nowide
    #Boost::python
    #Boost::mpi
)

add_vendored_dependency(Boost::boost)
add_vendored_dependency(Boost::filesystem)
add_vendored_dependency(Boost::regex)
add_vendored_dependency(Boost::system)