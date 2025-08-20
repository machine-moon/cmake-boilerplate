
CPMAddPackage(
    NAME glm
    VERSION 1.0.1
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
    OPTIONS
        "GLM_ENABLE_CXX_20 ON"
)

target_include_directories(glm INTERFACE ${glm_SOURCE_DIR})