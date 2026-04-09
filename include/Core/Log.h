#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>

namespace NullEngine
{
    class Log
    {
    public:
        static void Init();
        inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
    };
}

// 편하게 쓰기 위한 매크로
#define NE_CORE_INFO(...) ::NullEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NE_CORE_ERROR(...) ::NullEngine::Log::GetCoreLogger()->error(__VA_ARGS__)