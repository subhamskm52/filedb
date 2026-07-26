#pragma once
#include <string>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <spdlog/sinks/basic_file_sink.h>


namespace filedb {

    class Logger {
    private:
        Logger() = default;
        inline static std::shared_ptr<spdlog::logger> logger_;
    public:
        static std::shared_ptr<spdlog::logger> instance() {
            if (!logger_) init();
            return logger_;
        }

        static void init() {
            if (logger_) return;
            logger_ = spdlog::stdout_color_mt("filedb");
            logger_->set_pattern(
                "[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");
            logger_->set_level(spdlog::level::info);
        }

        void set_level(int level)
        {
            if (!logger_)
                init();

            if (level < 0 || level >= 7)
                return;

            static constexpr std::array<spdlog::level::level_enum, 7> core_levels = {
                spdlog::level::trace,
                spdlog::level::debug,
                spdlog::level::info,
                spdlog::level::warn,
                spdlog::level::err,
                spdlog::level::critical,
                spdlog::level::off
            };

            logger_->set_level(core_levels[level]);
        }
        inline void set_log_file(const std::string& path)
        {
            auto file_logger =
                spdlog::basic_logger_mt("filedb_file_logger", path);
            file_logger->set_pattern(
                "[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");
            logger_ = std::move(file_logger);
        }

        template<typename... Args>
        void trace(const char* fmt, Args&&... args) {
            if (!logger_) return;
            logger_->trace(fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void debug(const char* fmt, Args&&... args) {
            if (!logger_) return;
            logger_->debug(fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void info(const char* fmt, Args&&... args) {
            if (!logger_) return;
            logger_->info(fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void warn(const char* fmt, Args&&... args) {
            if (!logger_) return;
            logger_->warn(fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void error(const char* fmt, Args&&... args) {
            if (!logger_) return;
            logger_->error(fmt, std::forward<Args>(args)...);
        }
    };

}
