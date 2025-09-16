#pragma once

#include <string>

#include "LogLevel.h"

namespace Helianthus::Runtime
{
    namespace Log
    {
        struct LoggerConfig
        {
			LogLevel Level;
			bool EnableConsole;
			bool EnableFile;
			std::string FilePath;
			size_t MaxFileSize;
			size_t MaxFiles;
			std::string Pattern;
			bool UseAsync;
			size_t QueueSize;
			int WorkerThreads;

			// Constructor
			LoggerConfig(): 
				Level(HELIANTHUS_DEFAULT_LOG_LEVEL),
				EnableConsole(true),
				EnableFile(true),
				FilePath("logs/helianthus.log"),
				MaxFileSize(50 * 1024 * 1024),
				MaxFiles(5),
				Pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%L%$] [%P-%t-CID] [%n] [%s:%#] %v"),
				UseAsync(true),
				QueueSize(8192),
				WorkerThreads(1)
			{
			}
        };
    } // namespace Log
} // namespace Helianthus::Runtime
