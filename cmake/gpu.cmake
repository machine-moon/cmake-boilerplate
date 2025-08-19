# --- GPU Runtime Selection ---
set(${_P}_GPU_RUNTIME "CUDA" CACHE STRING "GPU runtime: CUDA or HIP")
set(${_P}_GPU_ARCHITECTURE "86" CACHE STRING "GPU architecture")

# --- Environment Variables ---
set(${_P}_CUDA_ROOT "/usr/local/cuda/bin" CACHE STRING "Path to CUDA")
set(${_P}_ROCM_ROOT "/opt/rocm/bin" CACHE STRING "Path to ROCm")
set(${_P}_HIP_PLATFORM "nvidia" CACHE STRING "HIP platform (nvidia or amd)")

# --- Validation ---
if(NOT ${${_P}_GPU_RUNTIME} STREQUAL "HIP" AND NOT ${${_P}_GPU_RUNTIME} STREQUAL "CUDA")
    message(FATAL_ERROR "GPU_RUNTIME must be HIP or CUDA, got \"${${_P}_GPU_RUNTIME}\"")
endif()
if(${${_P}_GPU_RUNTIME} STREQUAL "HIP" AND NOT ${${_P}_HIP_PLATFORM} STREQUAL "nvidia" AND NOT ${${_P}_HIP_PLATFORM} STREQUAL "amd")
    message(FATAL_ERROR "HIP_PLATFORM must be nvidia or amd, got \"${${_P}_HIP_PLATFORM}\"")
endif()

# --- CXX Settings ---
set(CMAKE_${${_P}_GPU_RUNTIME}_STANDARD 20)
set(CMAKE_${${_P}_GPU_RUNTIME}_STANDARD_REQUIRED ON)
set(CMAKE_${${_P}_GPU_RUNTIME}_EXTENSIONS OFF)

# --- Runtime-specific Configuration ---
if(${${_P}_GPU_RUNTIME} STREQUAL "HIP")
    set(ENV{PATH} "${${_P}_ROCM_ROOT}:${${_P}_HIP_PLATFORM}:$ENV{PATH}")
    set(CMAKE_HIP_ARCHITECTURES "${${_P}_GPU_ARCHITECTURE}")

    # Find device compiler
    set(${_P}_HIP_PLATFORM_NVIDIA "/usr/local/cuda-12/bin" CACHE STRING "Path to CUDA binaries")

    if(${${_P}_HIP_PLATFORM} STREQUAL "nvidia")
        set(ENV{PATH} "${${_P}_HIP_PLATFORM_NVIDIA}:$ENV{PATH}")
        if(NOT TOOLCHAIN STREQUAL "GNU")
            message(FATAL_ERROR "HIP on NVIDIA requires GNU toolchain")
        endif()
    elseif(${${_P}_HIP_PLATFORM} STREQUAL "amd")
        # amdclang++ already in PATH via ROCM_ROOT
        message(FATAL_ERROR "AMD GPU is not yet supported")
    endif()
elseif(${${_P}_GPU_RUNTIME} STREQUAL "CUDA")
    set(ENV{PATH} "${${_P}_CUDA_ROOT}:$ENV{PATH}")
    set(CMAKE_CUDA_ARCHITECTURES "${${_P}_GPU_ARCHITECTURE}")

    # Find host compiler
    set(CMAKE_CUDA_HOST_COMPILER "${CMAKE_CXX_COMPILER}")

    find_package(CUDAToolkit REQUIRED)
endif()

# --- Enable & Find Language ---
enable_language(${${_P}_GPU_RUNTIME})

# --- Definitions ---
set(${_P}_GPU_COMPILE_DEFS
    "${_P}_GPU_RUNTIME_${${_P}_GPU_RUNTIME}=1"
    "${_P}_GPU_ARCH_${${_P}_GPU_ARCHITECTURE}=1"
    $<$<STREQUAL:${${_P}_GPU_RUNTIME},HIP>:${_P}_HIP_PLATFORM_${${_P}_HIP_PLATFORM}=1>
)