#pragma once
#include "Version.h"
#include <cstddef>
#include <cstdint>

namespace Constants
{
    constexpr inline const char* appName = "TwizApp";
    constexpr inline const char* appVersion = TWIZ_VERSION;
    constexpr inline const char* logFile = "twizapp.log";

    // -- Thread Base
    constexpr inline int heartbeatIntervalMs = 500;
    constexpr inline int tickIntervalMs = 1;

    // -- processing thread --
    constexpr inline size_t maxQueueSize = 20;
    constexpr inline bool blockingPush = true;

    // -- Stabilization
    enum class Flavour : std::uint8_t
    {
        NONE = 0,
        EIGEN = 1,
        HIP = 2,
        CUDA = 3,
        MDSPAN = 4,
        OTHER = 5
    };
    constexpr inline Flavour chosenFlavour = Flavour::HIP;
} // namespace Constants
