project(FlyWhaleCore)

# Recursively grab all source files (matches Premake's behavior)
file(GLOB_RECURSE FW_SRC "src/*.cpp" "src/*.h")

# Build FlyWhale as a Shared Library (.dll on Windows)
add_library(FlyWhale SHARED ${FW_SRC})

# Force GCC/Clang to hide symbols by default (matches Windows behavior)
set_target_properties(FlyWhale PROPERTIES CXX_VISIBILITY_PRESET hidden)
set_target_properties(FlyWhale PROPERTIES VISIBILITY_INLINES_HIDDEN 1)

# Tell Core.h to use dllexport or visibility("default")
target_compile_definitions(FlyWhale PRIVATE FW_BUILD_DLL)

# Include directories (where to look for #include <...>)
target_include_directories(FlyWhale PUBLIC
    "src"
    "vendor/spdlong/include"
    # Note: Add other vendor include paths here as you progress (GLFW, glad, glm, imgui)
)

# Setup Precompiled Headers (Native in CMake 3.16+)
#target_precompile_headers(FlyWhale PUBLIC "src/hzpch.h")

# Link vendor libraries here later (e.g., target_link_libraries(FlyWhale PRIVATE glfw glad))