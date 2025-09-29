include(cmake/CPM.cmake)
set(CPM_SOURCE_CACHE "${CMAKE_SOURCE_DIR}/dependencies")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

set(${_P}_system_dependencies "")
set(${_P}_vendored_dependencies "")
set(${_P}_include_directories "")

# --- System Dependencies ---
include(openssl)
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

# Note to self: https://rocm.docs.amd.com/en/latest/reference/api-libraries.html or cuda-x-libraries