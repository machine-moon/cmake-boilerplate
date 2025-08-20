CPMAddPackage(
    NAME boost
    GITHUB_REPOSITORY boostorg/boost
    GIT_TAG boost-1.89.0
    OPTIONS
        "BOOST_ENABLE_CMAKE ON"
        "BOOST_ENABLE_TESTS OFF"
        "BOOST_ENABLE_EXAMPLES OFF"
)

add_library(boost_all_headers INTERFACE)

file(GLOB BOOST_INCLUDE_DIRS "${boost_SOURCE_DIR}/libs/*/include")
target_include_directories(boost_all_headers INTERFACE ${BOOST_INCLUDE_DIRS})

add_library(Boost::all_headers ALIAS boost_all_headers)
