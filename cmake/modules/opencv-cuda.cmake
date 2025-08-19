set(CUDA_ROOT "/usr/local/cuda-12" CACHE STRING "Path to CUDA")
find_package(OpenCV REQUIRED COMPONENTS core imgproc imgcodecs videoio highgui video calib3d videostab)