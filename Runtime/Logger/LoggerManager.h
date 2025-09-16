#pragma once

#include <memory>
#include <unordered_map>
#include <atomic>

#include "LoggerConfig.h"

namespace Helianthus::Runtime
{
    namespace Log
    {
        class LoggerManager
        {
            // Constructor And Destructor
        private:
            LoggerManager();
            virtual ~LoggerManager();

            // LifeCycle Function
            void Initialize(const LoggerConfig& Config);
            void Shutdown();
            void EnsureInitialized();
            void EnsureShutdown();
            bool IsInitialized();
            bool IsShutdown();
           
            // Category Logging File Configuration
            void ConfigureCategoryFile(const std::string& CatagroyName,
                                       const std::string& FilePath,
                                       size_t MaxFileSize = 50 * 1024 * 1024,
                                       size_t MaxFileCount = 10);

            void RemoveCategoryFile(const std::string& CatagroyName);
            void RemoveAllCategoryFiles();

        private:
            // Private Helper Function
            std::shared_ptr<spdlog::logger> LoggerInstance;
            LoggerConfig CurrentConfig;
            bool IsInitializedFlag;
            std::atomic<bool> ShuttingDownFlag;

            std::vector<std::shared_ptr<spdlog::sinks::sink>> Sinks;

            static spdlog::level::level_enum ConvertLogLevel(LogLevel Level);
            static LogLevel ConvertLogLevel(spdlog::level::level_enum Level);

            static void LoadCategoryFromEnv();

        public:
            static LoggerManager& GetInstance()
            {
                static LoggerManager Instance;
                Instance.EnsureInitialized();
                return Instance;
            }
        };
    } // namespace Log
} // namespace Helianthus::Runtime
