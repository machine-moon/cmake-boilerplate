include(cmake/CPM.cmake)
set(CPM_SOURCE_CACHE "${CMAKE_SOURCE_DIR}/dependencies")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

# --- System Dependencies ---
find_package(OpenSSL COMPONENTS Crypto SSL REQUIRED)
include(opencv-cuda)
include(opengl)
find_package(PkgConfig REQUIRED)
include(ffmpeg)
include(libzmq)
include(libsodium)

# --- Vendored ---
include(glad)
include(glfw)
include(glm)
include(boost)
include(cgal)
include(imgui)
include(jsoncons)
include(lz4)
include(cppzmq)
include(spdlog)

# --- Aggregate Dependencies ---
set(system_dependencies
    OpenSSL::Crypto
    OpenSSL::SSL
    OpenGL::GL
    FFmpeg::FFmpeg
    LIBZMQ::libzmq
    SODIUM::libsodium
)

set(vendored_dependencies
    glad
    glfw
    glm
    Boost::boost
    Boost::filesystem
    Boost::regex
    Boost::system
    CGAL
    imgui
    jsoncons
    lz4
    cppzmq
    spdlog
)

# Note to self: https://rocm.docs.amd.com/en/latest/reference/api-libraries.html or cuda-x-libraries