CPMAddPackage(
    NAME boost
    GITHUB_REPOSITORY boostorg/boost
    GIT_TAG boost-1.89.0
    OPTIONS
        "BOOST_ENABLE_CMAKE ON"
)

# Create comprehensive boost headers interface target with a different name
add_library(boost_all_headers INTERFACE)

# Include all boost library headers using glob
file(GLOB BOOST_INCLUDE_DIRS "${boost_SOURCE_DIR}/libs/*/include")
target_include_directories(boost_all_headers INTERFACE ${BOOST_INCLUDE_DIRS})

# Create an alias for convenience
add_library(Boost::all_headers ALIAS boost_all_headers)
