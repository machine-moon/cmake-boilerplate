CPMAddPackage(
    NAME glfw
    VERSION 3.4
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    OPTIONS
        "GLFW_BUILD_EXAMPLES OFF"
        "GLFW_BUILD_TESTS OFF"
        "GLFW_BUILD_DOCS OFF"
        "GLFW_BUILD_WAYLAND OFF"    # libdecor-gtk-WARNING: Failed to initialize GTK
                                    # Failed to load plugin 'libdecor-gtk.so': failed to init
)
