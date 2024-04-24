include_directories(
	Engine3D
	../
)

set(
	INCLUDE_DIR
	Engine3D
)

set(
  all_src


  # Engine3D/Core/EntryPoint.cpp
  ${INCLUDE_DIR}/Core/Application.cpp
  ${INCLUDE_DIR}/Core/EngineLogger.cpp
  ${INCLUDE_DIR}/Core/EntryPoint.cpp

  ${INCLUDE_DIR}/OpenGL/OpenGLInputPoll.cpp
  ${INCLUDE_DIR}/OpenGL/OpenGLWindow.cpp

  ${INCLUDE_DIR}/Core/Layer.cpp
  ${INCLUDE_DIR}/Core/LayerStack.cpp

  ${INCLUDE_DIR}/Graphics/Buffer.cpp
  ${INCLUDE_DIR}/Graphics/VertexArray.cpp
  ${INCLUDE_DIR}/Graphics/Shader.cpp
  ${INCLUDE_DIR}/Graphics/Texture.cpp

  ${INCLUDE_DIR}/Renderer/Renderer.cpp

  ${INCLUDE_DIR}/Image/stb_image.cpp

  # OpenGL
  ${INCLUDE_DIR}/OpenGL/OpenGLBuffer.cpp
  ${INCLUDE_DIR}/OpenGL/OpenGLVertexArray.cpp
  ${INCLUDE_DIR}/OpenGL/OpenGLShader.cpp
  ${INCLUDE_DIR}/OpenGL/OpenGLTexture.cpp
  
  # Engine3D/Events/InputPoll.cpp
  # Engine3D/platforms/Windows/InputPoll.cpp
  # Engine3D/Core/Layer.cpp
  # Engine3D/Core/LayerStack.cpp

  # Engine3D/Imgui/ImGuiLayer.cpp

  # Engine3D/OpenGL/OpenGLContext.cpp
  # Engine3D/interfaces/Shader.cpp
  # Engine3D/interfaces/Buffer.cpp
  # Engine3D/OpenGL/OpenGLBuffer.cpp
  # Engine3D/Renderer/Renderer.cpp
  # Engine3D/interfaces/VertexArray.cpp
  # Engine3D/OpenGL/OpenGLVertexArray.cpp
  # Engine3D/interfaces/RendererAPI.cpp
  # Engine3D/Renderer/RendererCommand.cpp
  # Engine3D/OpenGL/OpenGLRendererAPI.cpp
  # Engine3D/Renderer/OrthographicCamera.cpp
  # Engine3D/OpenGL/OpenGLShader.cpp
  # Engine3D/interfaces/Texture.cpp
  # Engine3D/OpenGL/OpenGLTexture.cpp
  # Engine3D/Renderer/OrthographicCameraController.cpp

  # # Engine3D/OpenGL/OpenGLInputPoll.cpp
  
  # # Engine3D/OpenGL/OpenGLWindow.cpp
  # Engine3D/platforms/Windows/WindowsWindow.cpp
  # Engine3D/Renderer/Renderer2D.cpp
  # # Engine3D/interfaces/SubTexture2D.cpp
  # Engine3D/interfaces/Framebuffer.cpp
  # Engine3D/OpenGL/OpenGLFramebuffer.cpp
  # Engine3D/Scene/Scene.cpp
  # Engine3D/Scene/Entity.cpp
  # Engine3D/Scene/SceneCamera.cpp
  # Engine3D/Scene/SceneSerializer.cpp
  # Engine3D/image/stb_image.cpp

  # # Engine3D/platforms/Mac/MacPlatformUtils.cpp
  # Engine3D/Math/Math.cpp
  # Engine3D/Renderer/EditorCamera.cpp
  # Engine3D/interfaces/UniformBuffer.cpp
  # Engine3D/OpenGL/OpenGLUniformBuffer.cpp
)

set(
  all_headers
  ../${INCLUDE_DIR}/Core/Application.h
  ../${INCLUDE_DIR}/Core/core.h
  ../${INCLUDE_DIR}/Core/EngineLogger.h
  ../${INCLUDE_DIR}/Core/EntryPoint.h

  ../${INCLUDE_DIR}/Event/Event.h
  ../${INCLUDE_DIR}/Event/KeyEvent.h
  ../${INCLUDE_DIR}/Event/MouseEvent.h
  ../${INCLUDE_DIR}/Event/ApplicationEvent.h

  ../${INCLUDE_DIR}/Event/KeyCodes.h
  ../${INCLUDE_DIR}/Event/MouseCodes.h
  ../${INCLUDE_DIR}/Event/InputPoll.h

  ../${INCLUDE_DIR}/Core/Window.h
  ../${INCLUDE_DIR}/Core/Layer.h
  ../${INCLUDE_DIR}/Core/LayerStack.h

  ../${INCLUDE_DIR}/Graphics/Buffer.h
  ../${INCLUDE_DIR}/Graphics/VertexArray.h
  ../${INCLUDE_DIR}/Graphics/Shader.h
  ../${INCLUDE_DIR}/Graphics/Texture.h

  ../${INCLUDE_DIR}/Renderer/Renderer.h
  ../${INCLUDE_DIR}/Graphics/RendererCommand.h

  ../${INCLUDE_DIR}/Image/stb_image.h

  ../${INCLUDE_DIR}/OpenGL/OpenGLBuffer.h
  ../${INCLUDE_DIR}/OpenGL/OpenGLVertexArray.h
  ../${INCLUDE_DIR}/OpenGL/OpenGLShader.h
  ../${INCLUDE_DIR}/OpenGL/OpenGLTexture.h

  # ../${INCLUDE_DIR}/Core/EngineLogger.h
  # ../${INCLUDE_DIR}/Core/EntryPoint.h
# #   ../${INCLUDE_DIR}/Core/GameEngine.h
#   ../${INCLUDE_DIR}/Events/InputPoll.h
#   ../${INCLUDE_DIR}/Core/Window.h
#   ../${INCLUDE_DIR}/Core/Layer.h
#   ../${INCLUDE_DIR}/Core/LayerStack.h
#   ../${INCLUDE_DIR}/Core/Timer.h
#   ../${INCLUDE_DIR}/Core/Timestep.h
#   ../${INCLUDE_DIR}/Entt/entt.h
#   ../${INCLUDE_DIR}/Imgui/ImGuiLayer.h

#   ../${INCLUDE_DIR}/OpenGL/OpenGLContext.h
#   ../${INCLUDE_DIR}/interfaces/Shader.h
#   ../${INCLUDE_DIR}/interfaces/Buffer.h
#   ../${INCLUDE_DIR}/OpenGL/OpenGLBuffer.h
#   ../${INCLUDE_DIR}/Renderer/Renderer.h
#   ../${INCLUDE_DIR}/interfaces/VertexArray.h
#   ../${INCLUDE_DIR}/OpenGL/OpenGLVertexArray.h
#   ../${INCLUDE_DIR}/interfaces/RendererAPI.h
#   ../${INCLUDE_DIR}/Renderer/RendererCommand.h
#   ../${INCLUDE_DIR}/OpenGL/OpenGLRendererAPI.h
#   ../${INCLUDE_DIR}/Renderer/OrthographicCamera.h
#   ../${INCLUDE_DIR}/OpenGL/OpenGLShader.h
#   ../${INCLUDE_DIR}/interfaces/Texture.h
#   ../${INCLUDE_DIR}/OpenGL/OpenGLTexture.h
#   ../${INCLUDE_DIR}/Renderer/OrthographicCameraController.h

#   ../${INCLUDE_DIR}/platforms/PlatformUtils.h

#   ../${INCLUDE_DIR}/Events/ApplicationEvent.h
#   ../${INCLUDE_DIR}/Events/Event.h
#   ../${INCLUDE_DIR}/Events/KeyEvent.h
#   ../${INCLUDE_DIR}/Events/MouseEvent.h
#   # ../${INCLUDE_DIR}/OpenGL/OpenGLInputPoll.h
#   ../${INCLUDE_DIR}/image/stb_image.h
)

# if(UNIX AND NOT APPLE)
# find_package(glfw3 REQUIRED)
# # endif(UNIX AND NOT APPLE)

# find_package(OpenGL REQUIRED)
# find_package(GLEW REQUIRED)
# # find_package(GLUT REQUIRED)

# find_package(imgui REQUIRED)
# find_package(ImGuizmo REQUIRED)
# # find_package(Vulkan REQUIRED)

# find_package(fmt REQUIRED)
# find_package(spdlog REQUIRED)
# find_package(glad REQUIRED)
# find_package(glm REQUIRED)

# find_package(box2d REQUIRED)
# find_package(yaml-cpp REQUIRED)

add_library( ${PROJECT_NAME} ${all_headers} ${all_src} )

# NOTE: Using {OPENGL_gl_LIBRARY}, if compiling on Apple.

# if(UNIX AND NOT APPLE)
# 	target_link_libraries(
# 		${PROJECT_NAME}
# 		glfw
# 		# ${OPENGL_gl_LIBRARY}
# 		OpenGL::GL
# 		# Vulkan::Vulkan
# 		imgui::imgui
# 		ImGuizmo::ImGuizmo
# 		fmt::fmt
# 		glm::glm
# 		spdlog::spdlog
# 		glad::glad
# 		box2d::box2d
# 		yaml-cpp
# 	)
# endif(UNIX AND NOT APPLE)

if(APPLE)
target_link_libraries(
	${PROJECT_NAME}
	glfw
	imgui::imgui
	ImGuizmo::ImGuizmo
	fmt::fmt
	glm::glm
	spdlog::spdlog
	glad::glad
	GLEW::GLEW
)
endif(APPLE)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../${INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)


set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

if(MSVC)
	set_target_properties(${PROJECT_NAME} PROPERTIES
    COMPILE_PDB_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
	COMPILE_PDB_NAME ${PROJECT_NAME}
  )

  install(
	  FILES "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/${PROJECT_NAME}.pdb"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    OPTIONAL
  )
endif()

if (BUILD_SHARED_LIBS)
	target_compile_definitions(${PROJECT_NAME}
    PUBLIC
	${PROJECT_NAME}_SHARED
  )
endif()

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "src" FILES ${all_src})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/../${INCLUDE_DIR}" PREFIX "include" FILES ${all_headers})

install(
	TARGETS ${PROJECT_NAME}
	EXPORT ${PROJECT_NAME}Config
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(
	EXPORT ${PROJECT_NAME}Config
	NAMESPACE Engine3D::
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  COMPATIBILITY SameMajorVersion
)

install(
	FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)
