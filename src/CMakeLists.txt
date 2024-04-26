include_directories(
  ../external/
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

  ${INCLUDE_DIR}/ImGui/ImGuiLayer.cpp

  ${INCLUDE_DIR}/Graphics/Pipeline.cpp
  ${INCLUDE_DIR}/Renderer/Renderer.cpp

  ${INCLUDE_DIR}/Image/stb_image.cpp

  # OpenGL
  ${INCLUDE_DIR}/OpenGL/OpenGLBuffer.cpp
  ${INCLUDE_DIR}/OpenGL/OpenGLVertexArray.cpp
  ${INCLUDE_DIR}/OpenGL/OpenGLShader.cpp
  ${INCLUDE_DIR}/OpenGL/OpenGLTexture.cpp

  ${INCLUDE_DIR}/ImGuizmo/ImCurveEdit.cpp
  ${INCLUDE_DIR}/ImGuizmo/ImGradient.cpp
  ${INCLUDE_DIR}/ImGuizmo/ImGuizmo.cpp
  ${INCLUDE_DIR}/ImGuizmo/ImSequencer.cpp

  ${INCLUDE_DIR}/Scene/Camera.cpp
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

  ../${INCLUDE_DIR}/ImGui/ImGuiLayer.h

  ../${INCLUDE_DIR}/Graphics/Pipeline.h
  ../${INCLUDE_DIR}/Renderer/Renderer.h

  ../${INCLUDE_DIR}/Image/stb_image.h

  ../${INCLUDE_DIR}/OpenGL/OpenGLBuffer.h
  ../${INCLUDE_DIR}/OpenGL/OpenGLVertexArray.h
  ../${INCLUDE_DIR}/OpenGL/OpenGLShader.h
  ../${INCLUDE_DIR}/OpenGL/OpenGLTexture.h

  ../${INCLUDE_DIR}/ImGuizmo/ImCurveEdit.h
  ../${INCLUDE_DIR}/ImGuizmo/ImGradient.h
  ../${INCLUDE_DIR}/ImGuizmo/ImGuizmo.h
  ../${INCLUDE_DIR}/ImGuizmo/ImSequencer.h

  ../${INCLUDE_DIR}/Scene/Camera.h
)

add_library( ${PROJECT_NAME} ${all_headers} ${all_src} )

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
