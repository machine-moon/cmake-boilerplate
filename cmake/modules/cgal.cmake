set(CMAKE_MESSAGE_LOG_LEVEL WARNING)
CPMAddPackage(
    NAME CGAL
    GITHUB_REPOSITORY CGAL/cgal
    VERSION 6.0.1
)
set(CMAKE_MESSAGE_LOG_LEVEL STATUS)

file(GLOB CGAL_PACKAGE_INCLUDES
        "${CGAL_SOURCE_DIR}/*/include"
)

add_library(CGAL INTERFACE)

target_include_directories(CGAL INTERFACE ${CGAL_PACKAGE_INCLUDES})
target_link_libraries(CGAL INTERFACE boost_all_headers)
