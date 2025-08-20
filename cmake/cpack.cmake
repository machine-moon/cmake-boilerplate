# --- CPack Configuration ---
set(CPACK_PACKAGE_NAME "twiz")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A network visualization application")
set(CPACK_PACKAGE_VENDOR "Tarek Ibrahim")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")

# Required for Debian packaging
set(CPACK_PACKAGE_CONTACT "tarek@mydomain.com")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libgl1")

# --- Package Generator ---
if(APPLE)
    set(CPACK_GENERATOR "ZIP")
    set(CPACK_PACKAGE_FILE_NAME "twiz-${CPACK_PACKAGE_VERSION}-macos")
elseif(WIN32)
    set(CPACK_GENERATOR "ZIP")
    set(CPACK_PACKAGE_FILE_NAME "twiz-${CPACK_PACKAGE_VERSION}-windows")
elseif(UNIX AND NOT APPLE)
    set(CPACK_GENERATOR "ZIP")
    set(CPACK_PACKAGE_FILE_NAME "twiz-${CPACK_PACKAGE_VERSION}-linux")
endif()

include(CPack)