pkg_check_modules(LIBZMQ REQUIRED libzmq)

add_library(LIBZMQ::libzmq INTERFACE IMPORTED)
set_target_properties(LIBZMQ::libzmq PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${LIBZMQ_INCLUDE_DIRS}"
    INTERFACE_LINK_LIBRARIES "${LIBZMQ_LIBRARIES}"
)

add_system_dependency(LIBZMQ::libzmq)