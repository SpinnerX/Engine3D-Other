# Unix may refer to either Mac or Linux builds
message("Running Unix (Linux) Build....")

find_package(glfw3 REQUIRED)

find_package(OpenGL REQUIRED)
# find_package(GLEW REQUIRED)
find_package(Vulkan REQUIRED)

find_package(imgui REQUIRED)
find_package(ImGuizmo REQUIRED)

find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(glad REQUIRED)
find_package(glm REQUIRED)

find_package(box2d REQUIRED)
find_package(yaml-cpp REQUIRED)

target_link_libraries(
    ${PROJECT_NAME}
    glfw
    OpenGL::GL
    Vulkan::Vulkan
    imgui::imgui
    ImGuizmo::ImGuizmo
    fmt::fmt
    glm::glm
    spdlog::spdlog
    glad::glad
    box2d::box2d
    yaml-cpp
)