project(FlyWhaleCore)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Tell CMake to process spdlog's own CMakeLists.txt and other libraries
add_subdirectory(vendor/spdlog)

# --- GLFW Setup ---
# Disable GLFW tests, examples, and docs to speed up compilation
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/glfw)

# Recursively grab all source files (matches Premake's behavior)
file(GLOB_RECURSE FW_SRC "src/*.cpp" "src/*.h")

file(GLOB IMGUI_SRC
    "vendor/imgui/*.cpp"
    "vendor/imgui/backends/imgui_impl_glfw.cpp"
    "vendor/imgui/backends/imgui_impl_opengl3.cpp"
)

# Tell CMake to find the OpenGL libraries installed on the OS
find_package(OpenGL REQUIRED)

# Build FlyWhale as a Shared Library (.dll on Windows)
add_library(FlyWhale SHARED ${FW_SRC} vendor/glad/src/glad.c ${IMGUI_SRC})

# Skip pch specifically for glad.c (because it is not .cpp file duh)
set_source_files_properties(vendor/glad/src/glad.c PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
set_source_files_properties(IMGUI_SRC PROPERTIES SKIP_PRECOMPILE_HEADERS ON)

# Add precompiled header for all file to include
target_precompile_headers(FlyWhale PUBLIC "src/fwpch.h")

# Force GCC/Clang to hide symbols by default (matches Windows behavior)
set_target_properties(FlyWhale PROPERTIES CXX_VISIBILITY_PRESET hidden)
set_target_properties(FlyWhale PROPERTIES VISIBILITY_INLINES_HIDDEN 1)

# Tell Core.h to use dllexport or visibility("default")
target_compile_definitions(FlyWhale PRIVATE FW_BUILD_DLL GLFW_INCLUDE_NONE)

# Include directories (where to look for #include <...>)
target_include_directories(FlyWhale PUBLIC
    "src"
    "vendor/glad/include"
    "vendor/imgui"
    "vendor/imgui/backends"
    SYSTEM "vendor/glm"
    # Note: Add other vendor include paths here as you progress (GLFW, glad, glm, imgui)
)

# Setup Precompiled Headers (Native in CMake 3.16+)
#target_precompile_headers(FlyWhale PUBLIC "src/hzpch.h")
# Link spdlog to FlyWhale. 
# Using PUBLIC means Sandbox automatically gets the spdlog includes too!
target_link_libraries(FlyWhale PUBLIC spdlog glfw)
# Link vendor libraries here later (e.g., target_link_libraries(FlyWhale PRIVATE glfw glad))