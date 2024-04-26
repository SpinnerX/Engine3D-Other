project(Texture02)

# set(EXAMPLE_NAME Shader01)
add_executable(Texture02 Application.cpp)

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
