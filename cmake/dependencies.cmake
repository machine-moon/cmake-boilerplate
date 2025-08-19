include(cmake/CPM.cmake)
set(CPM_SOURCE_CACHE "${CMAKE_SOURCE_DIR}/dependencies")

include(${CMAKE_SOURCE_DIR}/cmake/dependencies/glad.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/dependencies/glfw.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/dependencies/glm.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/dependencies/boost.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/dependencies/cgal.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/dependencies/imgui.cmake)

set(${TWIZ}_deps "${CGAL_PACKAGE_INCLUDES};${Boost_INCLUDE_DIRS};${glad_include_dir}")
