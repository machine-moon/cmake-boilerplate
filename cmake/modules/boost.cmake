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

add_library(boost_headers_only INTERFACE)
file(GLOB BOOST_INCLUDE_DIRS "${boost_SOURCE_DIR}/libs/*/include")
target_include_directories(boost_headers_only INTERFACE ${BOOST_INCLUDE_DIRS})
add_library(Boost::headers_only ALIAS boost_headers_only)
