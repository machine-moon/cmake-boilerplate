include(cmake/CPM.cmake)
set(CPM_SOURCE_CACHE "${CMAKE_SOURCE_DIR}/dependencies")

include(${CMAKE_SOURCE_DIR}/cmake/modules/glad.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/modules/glfw.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/modules/glm.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/modules/boost.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/modules/cgal.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/modules/imgui.cmake)

set(${TWIZ}_deps "${CGAL_PACKAGE_INCLUDES};${Boost_INCLUDE_DIRS};${glad_include_dir}")
