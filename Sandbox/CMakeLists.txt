project(SandboxApp)

# Grab Sandbox source files
file(GLOB_RECURSE SANDBOX_SRC "src/*.cpp" "src/*.h")

# Build as an executable
add_executable(Sandbox ${SANDBOX_SRC})

# Let Sandbox know where its own source headers are
target_include_directories(Sandbox PRIVATE "src")

# Link the Sandbox to the FlyWhale engine
target_link_libraries(Sandbox FlyWhale)