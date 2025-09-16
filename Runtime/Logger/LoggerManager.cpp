#include "LoggerManager.h"	

#include <memory>
#ifdef _WIN32
#include <Windows.h>
#endif

#include "spdlog/spdlog.h"
#include "spdlog/pattern_formatter.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/async.h"

namespace Helianthus::Runtime
{
	namespace Log
    {
		// Logger Formatter
		class HelianthusLogFormatter : public spdlog::custom_flag_formatter
		{
        public:
			// Override Format Function
			virtual void format(const spdlog::details::log_msg& Msg, const std::tm&, spdlog::memory_buf_t& Dest) override
			{
                std::string LevelString;
				switch (Msg.level)
				{
                    case spdlog::level::trace:
                        LevelString = "TRACE";
                        break;
                    case spdlog::level::debug:
                        LevelString = "DEBUG";
                        break;
                    case spdlog::level::info:
                        LevelString = "INFO";
                        break;
                    case spdlog::level::warn:
                        LevelString = "WARN";
                        break;
                    case spdlog::level::err:
                        LevelString = "ERROR";
                        break;
                    case spdlog::level::critical:
                        LevelString = "CRITICAL";
                        break;
                    case spdlog::level::off:
                        LevelString = "OFF";
                        break;
                    default:
                        LevelString = "UNKNOWN";
                        break;
				}
                Dest.append(LevelString.data(), LevelString.data() + LevelString.size());
			}

            std::unique_ptr<spdlog::custom_flag_formatter> clone() const override 
            {
                return spdlog::details::make_unique<HelianthusLogFormatter>();
            }
		};

		// Helper Functions
        static std::string Trim(const std::string& S)
        {
            auto StartPos = S.find_first_not_of(" \t\n\r");
            auto EndPos = S.find_last_not_of(" \t\n\r");
            if (StartPos == std::string::npos)
            {
                return "";
            }

            return S.substr(StartPos, EndPos - StartPos + 1);

        }

        spdlog::level::level_enum Logger::ConvertLogLevel(LogLevel Level)
        {
            switch (Level)
            {
                case LogLevel::Debug:
                    return spdlog::level::debug;
                case LogLevel::Info:
                    return spdlog::level::info;
                case LogLevel::Warn:
                    return spdlog::level::warn;
                case LogLevel::Error:
                    return spdlog::level::err;
                default:
                    return spdlog::level::info;
            }
        }

        LogLevel LoggerManager::ConvertLogLevel(spdlog::level::level_enum Level)
        {
            switch (Level)
            {
                case spdlog::level::debug:
                    return LogLevel::Debug;
                case spdlog::level::info:
                    return LogLevel::Info;
                case spdlog::level::warn:
                    return LogLevel::Warn;
                case spdlog::level::err:
                    return LogLevel::Error;
                default:
                    return LogLevel::Info;
            }
        }

        // Private Constructor And Destructor
        LoggerManager::LoggerManager() 
        {
            EnsureInitialized();
        }

        LoggerManager::~LoggerManager() 
        {
            EnsureShutdown();
        }

		// LifeCycle Function
        void LoggerManager::Initialize(const LoggerConfig& Config)
        {
            ShuttingDownFlag.store(false, std::memory_order_release);

            if (Config.EnableConsole)
            {
                auto ConsoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
                ConsoleSink->set_level(ConvertLogLevel(Config.Level));
                Sinks.push_back(ConsoleSink);
            }

            if (Config.EnableFile)
            {
                auto RotatingFileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(Config.FilePath, Config.MaxFileSize, Config.MaxFiles);
                RotatingFileSink->set_level(ConvertLogLevel(Config.Level));
                Sinks.push_back(RotatingFileSink);
            }

            if (Sinks.empty())
            {
                throw std::runtime_error("No sinks configured for logger.");
            }

            if (Config.UseAsync)
            {
                spdlog::init_thread_pool(Config.QueueSize, Config.WorkerThreads);
            }

            IsInitializedFlag = true;

        }

        void LoggerManager::Shutdown()
        {
            ShuttingDownFlag.store(true, std::memory_order_release);
            if (CurrentConfig.UseAsync)
            {
                // Ensure thread pool is stopped
                spdlog::shutdown();
            }

            IsInitializedFlag = false;
        }

        void LoggerManager::EnsureInitialized()
        {
            if (!IsInitializedFlag)
            {
                Initialize(CurrentConfig);
            }
        }

        void LoggerManager::EnsureShutdown()
        {
            if (IsInitializedFlag && !ShuttingDownFlag.load(std::memory_order_acquire))
            {
                Shutdown();
            }
        }

        bool LoggerManager::IsInitialized()
        {
            return IsInitializedFlag;
        }

        bool LoggerManager::IsShutdown()
        {
            return ShuttingDownFlag.load(std::memory_order_acquire);
        }

	} // namespace Log
} // namepsace Helianthus::Runtime
