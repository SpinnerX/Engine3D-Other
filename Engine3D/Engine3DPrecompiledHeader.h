#pragma once
#define _CRT_SECURE_NO_WARNINGS

#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif

#include <cstdarg>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <sstream>
#include <fstream>

#include <array>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <thread>

// OpenGL includes
#ifndef __gl__h
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Engine3D/Image/stb_image.h>

#include <Engine3D/Core/Application.h>
#include <Engine3D/Core/EngineLogger.h>
#include <Engine3D/Event/InputPoll.h>

#include <Engine3D/Event/Event.h>
#include <Engine3D/Event/KeyEvent.h>
#include <Engine3D/Event/MouseEvent.h>
#include <Engine3D/Event/ApplicationEvent.h>

#include <Engine3D/interfaces/Buffer.h>
#include <Engine3D/interfaces/Shader.h>
#include <Engine3D/interfaces/VertexArray.h>
#include <Engine3D/Renderer/Renderer.h>

// #include <glm/glm.hpp>
// #include <Engine3D/Events/ApplicationEvent.h>

// #include <Engine3D/Core/EngineLogger.h>
// #include <Engine3D/Renderer/OrthographicCameraController.h>
// #include <Engine3D/Debug/Instrumentor.h>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <fmt/ostream.h>
#if ENGINE_PLATFORM_WINDOWS
    #include <Windows.h> // include Windows.h if we are in Windows platform
#endif