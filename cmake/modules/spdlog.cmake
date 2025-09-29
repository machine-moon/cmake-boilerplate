CPMAddPackage(
    NAME spdlog
    VERSION 1.15.3
    GIT_TAG v1.15.3
    GITHUB_REPOSITORY gabime/spdlog
    OPTIONS
        "SPDLOG_BUILD_ALL OFF"                      # Build all artifacts
        "SPDLOG_BUILD_SHARED OFF"                   # Build static library (not shared)
        "SPDLOG_ENABLE_PCH OFF"                     # Use precompiled header for faster compilation
        "SPDLOG_BUILD_PIC ON"                       # Build position independent code (-fPIC) for better compatibility
        "SPDLOG_DEBUG_POSTFIX \"d\""                # Filename postfix for debug builds
        "SPDLOG_BUILD_EXAMPLE OFF"                  # Build example (default: SPDLOG_MASTER_PROJECT, usually ON if standalone)
        "SPDLOG_BUILD_EXAMPLE_HO OFF"               # Build header only example
        "SPDLOG_BUILD_TESTS OFF"                    # Build tests
        "SPDLOG_BUILD_TESTS_HO OFF"                 # Build tests using header only version
        "SPDLOG_BUILD_BENCH OFF"                    # Build benchmarks
        "SPDLOG_SANITIZE_ADDRESS OFF"               # Enable address sanitizer in tests
        "SPDLOG_SANITIZE_THREAD OFF"                # Enable thread sanitizer in tests
        "SPDLOG_BUILD_WARNINGS OFF"                 # Enable compiler warnings
        "SPDLOG_SYSTEM_INCLUDES OFF"                # Include as system headers to reduce warnings
        "SPDLOG_INSTALL OFF"                        # Generate the install target (default: SPDLOG_MASTER_PROJECT, usually ON if standalone)
        "SPDLOG_USE_STD_FORMAT OFF"                 # Use std::format instead of fmt
        "SPDLOG_FMT_EXTERNAL OFF"                   # Use external fmt library
        "SPDLOG_FMT_EXTERNAL_HO OFF"                # Use external fmt header-only library
        "SPDLOG_NO_EXCEPTIONS OFF"                  # Compile with -fno-exceptions
        "SPDLOG_WCHAR_SUPPORT OFF"                  # Support wchar API (Windows only)
        "SPDLOG_WCHAR_FILENAMES OFF"                # Support wchar filenames (Windows only)
        "SPDLOG_WCHAR_CONSOLE OFF"                  # Support wchar console output (Windows only)
        "SPDLOG_MSVC_UTF8 ON"                       # Enable/disable MSVC /utf-8 flag (MSVC only, default: ON)
        "SPDLOG_CLOCK_COARSE ON"                    # Use CLOCK_REALTIME_COARSE (Linux only)
        "SPDLOG_PREVENT_CHILD_FD OFF"               # Prevent child process from inheriting log file descriptors
        "SPDLOG_NO_THREAD_ID OFF"                   # Prevent spdlog from querying thread id
        "SPDLOG_NO_TLS OFF"                         # Prevent spdlog from using thread local storage
        "SPDLOG_NO_ATOMIC_LEVELS OFF"               # Prevent spdlog from using atomic log levels
        "SPDLOG_DISABLE_DEFAULT_LOGGER OFF"         # Disable default logger creation
        "SPDLOG_FWRITE_UNLOCKED OFF"                # Use unlocked variant of fwrite for performance
        "SPDLOG_TIDY OFF"                           # Run clang-tidy
)

add_vendored_dependency(spdlog)