CPMAddPackage(
    NAME lz4
    VERSION 1.10.0
    GIT_TAG v1.10.0
    GITHUB_REPOSITORY lz4/lz4
    DOWNLOAD_ONLY TRUE
)

add_library(lz4 STATIC ${lz4_SOURCE_DIR}/lib/lz4.c)
target_include_directories(lz4 PUBLIC ${lz4_SOURCE_DIR}/lib)

add_vendored_dependency(lz4)