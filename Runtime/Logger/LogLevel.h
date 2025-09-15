#pragma once

#include <stdint.h>

namespace Helianthus::Runtime
{
    namespace Logger
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
    } // namespace Logger
} // namespace Helianthus::Runtime
