CPMAddPackage(
    NAME CGAL
    GITHUB_REPOSITORY CGAL/cgal
    VERSION 6.0.1
    DOWNLOAD_ONLY TRUE
)

add_library(CGAL INTERFACE)
file(GLOB CGAL_PACKAGE_INCLUDES "${CGAL_SOURCE_DIR}/*/include")
target_include_directories(CGAL INTERFACE ${CGAL_PACKAGE_INCLUDES})
# INTERFACE linkage propagates to dependents; link Boost::headers_only to twiz, not CGAL.
