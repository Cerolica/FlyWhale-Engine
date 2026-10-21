project(SandboxApp)

# Grab Sandbox source files
file(GLOB_RECURSE SANDBOX_SRC "src/*.cpp" "src/*.h")

# Build as an executable
add_executable(Sandbox ${SANDBOX_SRC})

# Automatically copy the assets folder to the executable directory after building
add_custom_command(TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:Sandbox>/assets"
)

set_property(TARGET Sandbox PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:Sandbox>")

# Let Sandbox know where its own source headers are
target_include_directories(Sandbox PRIVATE "src")

# Link the Sandbox to the FlyWhale engine
target_link_libraries(Sandbox FlyWhale)