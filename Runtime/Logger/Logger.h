#pragma once

#include <memory>
#include <unordered_map>
#include <atomic>

#include "LoggerConfig.h"

namespace Helianthus::Runtime
{
    namespace Logger
    {
        class Logger
        {
            #pragma region LifeCycle Function
            static void Initialize(const LoggerConfig& Config);
            static void Shutdown();
            static void EnsureInitialized();
            static void EnsureShutdown();
            static bool IsInitialized();
            static bool IsShutdown();
            #pragma endregion

            #pragma region Catagory Logging File Configuration
            static void ConfigureCatagoryFile(const std::string& CatagroyName,
                                              const std::string& FilePath,
                                              size_t MaxFileSize = 50 * 1024 * 1024,
                                              size_t MaxFileCount = 10);
            
            static void RemoveCatagoryFile(const std::string& CatagroyName);
            static void RemoveAllCatagoryFiles();
            #pragma endregion

            #pragma region Logging Function
            static void Debug(const std::string& Message);
            static void Info(const std::string& Message);
            static void Warn(const std::string& Message);
            static void Error(const std::string& Message);
            #pragma endregion
            
            #pragma region Template Format Logging Function
            template <typename... Args>
            static void Debug(fmt::format_string<Args...> Format, Args&&... Arguments)
            {
                if (LoggerInstance && !ShuttingDownFlag.load(std::memory_order_acquire))
                    LoggerInstance->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION},
                                        spdlog::level::debug,
                                        Format,
                                        std::forward<Args>(Arguments)...);
            }

            template <typename... Args>
            static void Info(fmt::format_string<Args...> Format, Args&&... Arguments)
            {
                if (LoggerInstance && !ShuttingDownFlag.load(std::memory_order_acquire))
                    LoggerInstance->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION},
                                        spdlog::level::info,
                                        Format,
                                        std::forward<Args>(Arguments)...);
            }

            template <typename... Args>
            static void Warn(fmt::format_string<Args...> Format, Args&&... Arguments)
            {
                if (LoggerInstance && !ShuttingDownFlag.load(std::memory_order_acquire))
                    LoggerInstance->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION},
                                        spdlog::level::warn,
                                        Format,
                                        std::forward<Args>(Arguments)...);
            }

            template <typename... Args>
            static void Error(fmt::format_string<Args...> Format, Args&&... Arguments)
            {
                if (LoggerInstance && !ShuttingDownFlag.load(std::memory_order_acquire))
                    LoggerInstance->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION},
                                        spdlog::level::err,
                                        Format,
                                        std::forward<Args>(Arguments)...);
            }

            // Category logging API (called by macros) - 使用统一的 Logger 接口
            template <typename... Args>
            static void CategoryLog(const char* CategoryName,
                                    spdlog::level::level_enum Level,
                                    const spdlog::source_loc& SourceLoc,
                                    fmt::format_string<Args...> Format,
                                    Args&&... Arguments)
            {
                // 使用 Logger 类的统一管理，包括关闭检查
                if (ShuttingDownFlag.load(std::memory_order_acquire))
                    return;

                // 通过 Logger 类获取或创建分类 logger
                auto CategoryLogger = GetOrCreateCategory(CategoryName);
                // 使用 CategoryLogger 进行日志记录，传递源位置信息
                CategoryLogger.Log(Level, SourceLoc, Format, std::forward<Args>(Arguments)...);
            }
            #pragma endregion

            #pragma region Configuration Function
            static void SetLevel(LogLevel Level);
            static LogLevel GetLevel();
            static void Flush();
            #pragma endregion

        private:
            #pragma region Private Helper Function
            static std::shared_ptr<spdlog::logger> LoggerInstance;
            static LoggerConfig CurrentConfig;
            static bool IsInitializedFlag;
            static std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> CategoryLoggers;
            static std::atomic<bool> ShuttingDownFlag;

            // 获取或创建分类logger（控制台+可选分类文件 logs/<Category>.log）
            static CategoryLogger GetOrCreateCategory(const std::string& CategoryName);

            // 进程名缓存
            static std::string ProcessName;
            static std::string DetectProcessName();

            static spdlog::level::level_enum ConvertLogLevel(LogLevel Level);
            static LogLevel ConvertLogLevel(spdlog::level::level_enum Level);

            static void LoadCategoryFromEnv();
            #pragma endregion
        };
    } // namespace Logger
} // namespace Helianthus::Runtime
