CPMAddPackage(
	NAME jsoncons
    VERSION 1.3.2
    GIT_TAG v1.3.2
    GITHUB_REPOSITORY danielaparker/jsoncons
    DOWNLOAD_ONLY TRUE
)

add_library(jsoncons INTERFACE)
target_include_directories(jsoncons INTERFACE "${jsoncons_SOURCE_DIR}/include")

add_vendored_dependency(jsoncons)