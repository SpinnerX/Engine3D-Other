#pragma once
#include <Engine3D/Core/Application.h>
#include <Engine3D/Core/Layer.h>
#include <Engine3D/OpenGL/OpenGLInputPoll.h>
// #include <Engine3D/OpenGL/OpenGLBuffer3D.h>
#include <Engine3D/OpenGL/OpenGLTexture.h>
#include <Engine3D/Renderer2D/OrthographicCameraController.h>
#include <Engine3D/OpenGL/OpenGLBuffer.h>
#include <Engine3D/OpenGL/OpenGLVertexArray.h>
#include <Engine3D/OpenGL/OpenGLShader.h>
#include <Engine3D/interfaces/Framebuffer.h>
#include <Engine3D/Renderer2D/Renderer2D.h>

namespace Engine3DLinux{
	class ExampleLayer3D : public Layer{
	public:
		ExampleLayer3D() : Layer("Layer #1"), camController(1280.0f/720.0f){
			checkboardTexture = Texture2D::Create("assets/Checkerboard.png");
			camController.setZoomLevel(5.0f); // @note Higher the offset, the wider we zoom outwards.
			FrameBufferSpecifications frameBufferData{};
			frameBufferData.width = 1280;
			frameBufferData.height = 720;
		}

		void onAttach() override {
		}

		void onDetach() override {}

		void onUpdate(Timestep ts) override {
			camController.onUpdate(ts);
	
			Renderer2D::setClearColor();

			Renderer2D::beginScene(camController.getCamera());
			
			static float  rotation = 0.0f;
			rotation += ts * 50.0f;


	
			// @note format of the parameters
			//						pos				size			color (r, g, b, a)
			/* Renderer2D::drawQuad({0.0f, 0.0f}, {5.f, 5.f}, {0.8, 0.2f, 0.3f, 1.0f}); */ // @note Rendering a red square
			Renderer2D::drawRotatedQuad({ -2.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, glm::radians(rotation), checkboardTexture, 20.0f); //@note Checkerboard texture shape (and making this texture specifically rotate)

			// @note This will draw tiles squares as color gradients
			for(float y = -5.0f; y < 5.0f; y += 0.5f){
				for(float x = -5.0f; x < 5.0f; x += 0.5f){
					glm::vec4 color = { (x + 0.5f) / 10.f, 0.4f, (y + 5.0f) / 10.0f, 0.7f};
					Renderer2D::drawQuad({x, y}, {0.45f, 0.45f}, color);
				}
			}

			Renderer2D::endScene();

		}

		void onEvent(Event& e) override {
			if(InputPoll::isKeyPressed(ENGINE_KEY_ESCAPE)){
				Application::Get().close();
			}

			camController.onEvent(e);
		}
		
		void onUIRender() override {}

	private:
		Ref<VertexBuffer3D> vertexBuffer;
		Engine3DLinux::OrthographicCameraController camController;
		Engine3DLinux::Ref<Engine3DLinux::VertexArray> vertexArr;
		Engine3DLinux::Ref<Engine3DLinux::Shader> shader;

		Engine3DLinux::Ref<Engine3DLinux::Texture2D> checkboardTexture;
		glm::vec4 squareColor = {0.2f, 0.3f, 0.8f, 1.0f};
	};
};
