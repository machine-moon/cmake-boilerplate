pkg_check_modules(FFMPEG REQUIRED IMPORTED_TARGET
    libavcodec      # Audio/video codec library (encoding/decoding)
    libavformat     # Audio/video container format library (mux/demux)
    libavutil       # Utility functions for FFmpeg
    libswscale      # Image scaling and colorspace conversion
    libswresample   # Audio resampling, conversion, and mixing
    libavfilter     # Audio/video filtering (optional, advanced filters)
    libavdevice     # Device handling (capture/playback, optional)
    libpostproc     # Post-processing (optional, mostly for video)
)

if(FFMPEG_FOUND)
    add_library(FFmpeg::FFmpeg ALIAS PkgConfig::FFMPEG)
else()
    message(FATAL_ERROR "FFmpeg not found. Please install FFmpeg development libraries.")
endif()