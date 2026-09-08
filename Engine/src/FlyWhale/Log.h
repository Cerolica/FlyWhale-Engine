#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace FlyWhale 
{

    class FLYWHALE_API Log 
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

// Core log macros
#define FW_CORE_TRACE(...)    ::FlyWhale::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FW_CORE_INFO(...)     ::FlyWhale::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FW_CORE_WARN(...)     ::FlyWhale::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FW_CORE_ERROR(...)    ::FlyWhale::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FW_CORE_CRITICAL(...) ::FlyWhale::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define FW_TRACE(...)         ::FlyWhale::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FW_INFO(...)          ::FlyWhale::Log::GetClientLogger()->info(__VA_ARGS__)
#define FW_WARN(...)          ::FlyWhale::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FW_ERROR(...)         ::FlyWhale::Log::GetClientLogger()->error(__VA_ARGS__)
#define FW_CRITICAL(...)      ::FlyWhale::Log::GetClientLogger()->critical(__VA_ARGS__)