#pragma once

// Window (MSVC/MinGW)
#ifdef FW_PLATFORM_WINDOWS
    #ifdef FW_BUILD_DLL
        #define FLYWHALE_API __declspec(dllexport)
    #else 
        #define FLYWHALE_API __declspec(dllimport)
    #endif

// Linux and macOS (GCC/Clang)
#elif defined(FW_PLATFORM_LINUX) || defined(FW_PLATFORM_MAC)
    #ifdef FW_BUILD_DLL
        #define FLYWHALE_API __attribute__((visibility("default")))
    #else
        #define FLYWHALE_API
    #endif
#else
    #error FlyWhale currently only support Windows, Linux, and macOS!

#endif

#ifdef FW_ENABLE_ASSERTS
    #define FW_ASSERT(x, ...) { if (!(x)) { FW_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define FW_CORE_ASSERT(x, ...) { if (!(x)) { FW_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define FW_ASSERT(x, ...)
    #define FW_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define FW_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)