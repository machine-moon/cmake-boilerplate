# --- Function to apply both sanitizer and compile flags to a target ---
# USAGE: apply_flags(<target>)
function(apply_flags target)
    # Target existence check
    if(NOT TARGET ${target})
        message(FATAL_ERROR "${target} is not a target, no flags can be added.")
    endif()

    apply_sanitizer_flags(${target})
    apply_compile_flags(${target})
endfunction()

# --- Function to apply sanitizer flags to a target ---
# USAGE: apply_sanitizer_flags(<target>)
function(apply_sanitizer_flags target)
    if(NOT DEFINED CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
        message(FATAL_ERROR "CMAKE_BUILD_TYPE must be set before applying sanitizer flags")
    endif()

    set(SANITIZER_COMPILE_FLAGS "")
    set(SANITIZER_LINK_FLAGS "")

    if(($(_p)_SANITIZER STREQUAL "asan" OR $(_p)_SANITIZER STREQUAL "tsan") AND NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Force Debug build for sanitizer" FORCE)
        message(STATUS "[Sanitizer] Switched to Debug build type for sanitizer")
    endif()

    if($(_p)_SANITIZER STREQUAL "asan")
        list(APPEND SANITIZER_COMPILE_FLAGS -fsanitize=address -fno-omit-frame-pointer)
        list(APPEND SANITIZER_LINK_FLAGS -fsanitize=address)
        if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            list(APPEND SANITIZER_LINK_FLAGS "LINKER:-shared-libasan")
        endif()
        message(STATUS "[Sanitizer] Building target ${target} with AddressSanitizer")
    elseif($(_p)_SANITIZER STREQUAL "tsan")
        list(APPEND SANITIZER_COMPILE_FLAGS -fsanitize=thread -fno-omit-frame-pointer)
        list(APPEND SANITIZER_LINK_FLAGS -fsanitize=thread)
        message(STATUS "[Sanitizer] Building target ${target} with ThreadSanitizer")
    elseif(NOT $(_p)_SANITIZER STREQUAL "off")
        message(SEND_ERROR "Unknown SANITIZER: ${_P}_SANITIZER. Must be one of off, asan, tsan.")
    endif()

    if(SANITIZER_COMPILE_FLAGS)
        target_compile_options(${target} PRIVATE ${SANITIZER_COMPILE_FLAGS})
    endif()
    if(SANITIZER_LINK_FLAGS)
        target_link_options(${target} PRIVATE ${SANITIZER_LINK_FLAGS})
    endif()
endfunction()

# --- Function to apply target-specific flags ---
# USAGE: apply_compile_flags(<target>)
function(apply_compile_flags target)
    
    # --- Debug/Optimization Flags ---
    if(TOOLCHAIN STREQUAL "MSVC")
        set(FLAGS_DEBUG "/Od /Zi")
        set(FLAGS_RELEASE "/Ox")
        set(FLAGS_RELWITHDEBINFO "/O2 /Zi")
        set(FLAGS_MINSIZEREL "/O1")
    elseif(TOOLCHAIN STREQUAL "GNU" OR TOOLCHAIN STREQUAL "Clang")
        set(FLAGS_DEBUG "-O0 -g3")
        set(FLAGS_RELEASE "-O3")
        set(FLAGS_RELWITHDEBINFO "-O2 -g3")
        set(FLAGS_MINSIZEREL "-Os")
    else()
        message(WARNING "Unknown TOOLCHAIN: ${TOOLCHAIN}. Supported: MSVC, GNU, Clang.")
        return()
    endif()

    # --- Warning Flags ---
    set(MSVC_WARNINGS
        /W4     # Baseline reasonable warnings
        /w14242 # 'identifier': conversion from 'type1' to 'type1', possible loss of data
        /w14254 # 'operator': conversion from 'type1:field_bits' to 'type2:field_bits', possible loss of data
        /w14263 # 'function': member function does not override any base class virtual member function
        /w14265 # 'classname': class has virtual functions, but destructor is not virtual; instances of this class may not be destructed correctly
        /w14287 # 'operator': unsigned/negative constant mismatch
        /we4289 # nonstandard extension used: 'variable': loop control variable declared in the for-loop is used outside the for-loop scope
        /w14296 # 'operator': expression is always 'boolean_value'
        /w14311 # 'variable': pointer truncation from 'type1' to 'type2'
        /w14545 # expression before comma evaluates to a function which is missing an argument list
        /w14546 # function call before comma missing argument list
        /w14547 # 'operator': operator before comma has no effect; expected operator with side-effect
        /w14549 # 'operator': operator before comma has no effect; did you intend 'operator'?
        /w14555 # expression has no effect; expected expression with side-effect
        /w14619 # pragma warning: there is no warning number 'number'
        /w14640 # Enable warning on thread un-safe static member initialization
        /w14826 # Conversion from 'type1' to 'type_2' is sign-extended. This may cause unexpected runtime behavior.
        /w14905 # wide string literal cast to 'LPSTR'
        /w14906 # string literal cast to 'LPWSTR'
        /w14928 # illegal copy-initialization; more than one user-defined conversion has been implicitly applied
        /permissive- # standards conformance mode for MSVC compiler.
    )

    set(CLANG_WARNINGS
        -Wall                # Enable all standard warnings
        -Wextra              # Reasonable and standard
        #-Wshadow             # Warn if a variable declaration shadows one from a parent context
        #-Wnon-virtual-dtor   # Warn if a class with virtual functions has a non-virtual destructor (memory errors)
        #-Wold-style-cast     # Warn for C-style casts
        -Wcast-align         # Warn for potential performance problem casts
        -Wno-unused-function # Warn on unused functions
        #-Woverloaded-virtual # Warn if you overload (not override) a virtual function
        #-Wpedantic           # Warn if non-standard C++ is used
        #-Wconversion         # Warn on type conversions that may lose data
        #-Wsign-conversion    # Warn on sign conversions
        #-Wnull-dereference   # Warn if a null dereference is detected
        #-Wdouble-promotion   # Warn if float is implicitly promoted to double
        -Wformat=2           # Warn on security issues around functions that format output (ie printf)
    )

    set(GCC_WARNINGS
        ${CLANG_WARNINGS}
        -Wmisleading-indentation # Warn if indentation implies blocks where blocks do not exist
        -Wduplicated-cond        # Warn if if/else chain has duplicated conditions
        #-Wduplicated-branches    # Warn if if/else branches have duplicated code
        -Wlogical-op             # Warn about logical operations being used where bitwise were probably wanted
        #-Wuseless-cast           # Warn if you perform a cast to the same type
    )

    # Optional: Warnings as errors
    if ($(_p)_WARNINGS_AS_ERRORS STREQUAL "on")
        set(CLANG_WARNINGS ${CLANG_WARNINGS} -Werror)
        set(MSVC_WARNINGS ${MSVC_WARNINGS} /WX)
    endif()

    # Choose warnings based on compiler
    if(TOOLCHAIN STREQUAL "MSVC")
        set(PROJECT_WARNINGS ${MSVC_WARNINGS})
    elseif(TOOLCHAIN STREQUAL "Clang")
        set(PROJECT_WARNINGS ${CLANG_WARNINGS})
    elseif(TOOLCHAIN STREQUAL "GNU")
        set(PROJECT_WARNINGS ${GCC_WARNINGS})
    else()
        message(FATAL_ERROR "No compiler warnings set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
    endif()

    # --- Apply Flags and Warnings ---
    target_compile_options(${target} PRIVATE
        $<$<CONFIG:Debug>:${FLAGS_DEBUG}>
        $<$<CONFIG:Release>:${FLAGS_RELEASE}>
        $<$<CONFIG:RelWithDebInfo>:${FLAGS_RELWITHDEBINFO}>
        $<$<CONFIG:MinSizeRel>:${FLAGS_MINSIZEREL}>
        ${PROJECT_WARNINGS}
    )
endfunction()

# --- Function to print all variables with a given prefix ---
# USAGE: print_variables_with_prefix(<prefix>)
# Example: print_variables_with_prefix("CMAKE_")
function(print_variables_with_prefix prefix)
    get_cmake_property(_variableNames VARIABLES)
    foreach(_variableName ${_variableNames})
        if(_variableName MATCHES "^${prefix}")
            message(STATUS "${_variableName} = ${${_variableName}}")
        endif()
    endforeach()
endfunction()

# --- Function to print a section header ---
# USAGE: section(<title>)
# Example: section("GPU Configuration")
function(section title)
    string(LENGTH "${title}" _len)
    math(EXPR _total_len "${_len} + 8")
    string(REPEAT "=" ${_total_len} _equals)
    message(STATUS "")
    message(STATUS "${_equals}")
    message(STATUS "=== ${title} ===")
    message(STATUS "${_equals}")
    message(STATUS "")
endfunction()

# --- Function to inspect target compile options ---
# USAGE: inspect_target(<target_name>)
function(inspect_target target)
    section("Inspecting Target: ${target}")

    get_target_property(flags   ${target} COMPILE_OPTIONS)
    get_target_property(iflags  ${target} INTERFACE_COMPILE_OPTIONS)
    get_target_property(cflags  ${target} COMPILE_FLAGS)

    section("COMPILE_OPTIONS")
    message(STATUS "${flags}")

    section("INTERFACE_COMPILE_OPTIONS")
    message(STATUS "${iflags}")

    section("COMPILE_FLAGS")
    message(STATUS "${cflags}")
endfunction()

#message(FATAL_ERROR "Stop")