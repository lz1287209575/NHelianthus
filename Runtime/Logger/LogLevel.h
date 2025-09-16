#pragma once

#include <stdint.h>

namespace Helianthus::Runtime
{
    namespace Log
    {
        #if HELIANTHUS_DEBUG
            #define HELIANTHUS_DEFAULT_LOG_LEVEL LogLevel::Debug 
        #else
            #define HELIANTHUS_DEFAULT_LOG_LEVEL LogLevel::Info 
        #endif

        enum class LogLevel : uint8_t
        {
            Debug,
            Info,
            Warn,
            Error,
        };
    } // namespace Log
} // namespace Helianthus::Runtime
