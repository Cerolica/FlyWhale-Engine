project(FlyWhaleEditor)

# Recursively grab all source files (matches Premake's behavior)
file(GLOB_RECURSE EDITOR_SRC "src/*.cpp" "src/*.h")

# Create the Editor Executable
add_executable(FlyWhaleEditor ${EDITOR_SRC})

# Tell the Editor where its own headers are
target_include_directories(FlyWhaleEditor PRIVATE "src")

# Link the Editor against the FlyWhale Engine
# This automatically brings in the Engine's includes, plus GLFW, Glad, ImGui, etc.
target_link_libraries(FlyWhaleEditor PRIVATE FlyWhale)

# Ensure the Editor runs from the correct working directory when debugging in VS Code
# (Requires CMake 3.20+, helps it find assets like fonts and shaders)
set_target_properties(FlyWhaleEditor PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Editor")