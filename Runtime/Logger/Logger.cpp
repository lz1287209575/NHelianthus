#include "Logger.h"	

#include <memory>
#ifdef _WIN32
#include <Windows.h>
#endif

#include "spdlog/spdlog.h"
#include "spdlog/pattern_formatter.h"

namespace Helianthus::Runtime
{
	namespace Logger
	{
		#pragma region Static Variables

		std::shared_ptr<spdlog::logger> Logger::LoggerInstance;
		LoggerConfig Logger::CurrentConfig;
        bool Logger::IsInitializedFlag = false;
        std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> Logger::CategoryLoggers;
        std::atomic_bool Logger::ShuttingDownFlag;
        std::string Logger::ProcessName;

		#pragma endregion

		#pragma region Logger Formatter

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

		#pragma endregion

        #pragma region Helper Functions

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

        LogLevel Logger::ConvertLogLevel(spdlog::level::level_enum Level)
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

		#pragma endregion 

        #pragma region LifeCycle Function

        void Logger::Initialize(const LoggerConfig& Config)
        {
            ShuttingDownFlag.store(false, std::memory_order_release);

            #ifdef _WIN32
            char Path[MAX_PATH];
            if (GetModuleFileName(NULL, Path, MAX_PATH) != 0)
            {
                std::string FullProcessInfo = Trim(std::string(Path));
                auto Pos = FullProcessInfo.find_last_of("\\/");
                ProcessName = Pos == std::string::npos ? Path : FullProcessInfo.substr(Pos + 1);
            }
            #endif
        }

        #pragma endregion

	} // namespace Logger
} // namepsace Helianthus::Runtime
