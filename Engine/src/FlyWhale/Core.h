#pragma once

// Window (MSVC/MinGW)
#ifdef FW_PLATFORM_WINDOWS
    #ifdef FW_BUILD_DLL
        #define FW_API __declspec(dllexport)
    #else 
        #define FW_API __declspec(dllimport)
    #endif

// Linux and macOS (GCC/Clang)
#elif defined(FW_PLATFORM_LINUX) || defined(FW_PLATFORM_MAC)
    #ifdef FW_BUILD_DLL
        #define FW_API __attribute__((visibility("default")))
    #else
        #define FW_API
    #endif
#else
    #error FlyWhale currently only support Windows, Linux, and macOS!

#endif