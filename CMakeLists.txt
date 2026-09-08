cmake_minimum_required(VERSION 3.16)
project(FlyWhaleWorkspace)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Force C++17 Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generates compile_commands.json for VS Code IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define platform macros automatically
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_compile_definitions(FW_PLATFORM_WINDOWS)
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    add_compile_definitions(FW_PLATFORM_MAC)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_compile_definitions(FW_PLATFORM_LINUX)
endif()

# Output directories: forces the Sandbox.exe and FlyWhale.dll into the same bin folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include sub-projects
add_subdirectory(Engine)
add_subdirectory(Sandbox)