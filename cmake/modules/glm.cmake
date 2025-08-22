CPMAddPackage(
    NAME glm
    VERSION 1.0.1
    GIT_TAG 1.0.1
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    OPTIONS
        "GLM_ENABLE_CXX_20 ON"
        "GLM_BUILD_LIBRARY ON" # Shared | Header-Only
        "GLM_BUILD_TESTS 0"
        "GLM_BUILD_INSTALL 0"
        "GLM_ENABLE_FAST_MATH ON"
)