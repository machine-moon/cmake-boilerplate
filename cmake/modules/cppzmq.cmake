
add_library(libzmq ALIAS LIBZMQ::libzmq)
CPMAddPackage(
    NAME cppzmq
    VERSION 4.11.0
    GIT_TAG v4.11.0
    GITHUB_REPOSITORY zeromq/cppzmq
    OPTIONS
        "CPPZMQ_BUILD_TESTS OFF"
)

