cmake_minimum_required (VERSION 3.15)

set(PROJECT_NAME Sandbox-Internal)

set(CMAKE_CXX_STANDARD 20)
# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works (in creating the compile_commands.json file)
project(${PROJECT_NAME})

include_directories(
    ../
    ../Engine3D/
)

# This will copy assets into build dir
file(COPY assets2 DESTINATION ${CMAKE_BINARY_DIR})

# Create the executable
add_executable(${PROJECT_NAME} Application.cpp)

target_link_libraries(
    ${PROJECT_NAME}
	Engine3D
    ${OPENGL_LIBRARIES}
    glfw
    ${Vulkan_LIBRARIES}
    fmt::fmt
    spdlog::spdlog
    glm::glm
    tobanteGaming::Box2D
    yaml-cpp::yaml-cpp
    imgui
	glad
)
