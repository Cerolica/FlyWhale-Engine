#pragma once

#include <memory>

// Window (MSVC/MinGW)
#define FLYWHALE_API

#ifdef FW_DEBUG
    #define FW_ENABLE_ASSERTS
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

namespace FlyWhale
{

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }


    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}