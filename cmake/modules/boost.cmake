CPMAddPackage(
    NAME boost
    GITHUB_REPOSITORY boostorg/boost
    GIT_TAG boost-1.89.0
)

#target_include_directories(boost INTERFACE ${boost_SOURCE_DIR}/libs/beast)
