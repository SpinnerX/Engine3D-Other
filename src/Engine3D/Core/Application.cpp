#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/Core/Application.h>


namespace Engine3D{
    Application* Application::instance = nullptr;

    Application::Application(){
        isRunning = true;
        instance = this;
        window = std::unique_ptr<Window>(Window::Create());
        window->setEventCallback(bind(this, &Application::OnEvent));

        //! @note Initializing our renderer with a specified Rendering API
        //! @note Foreshadowing utilizing multiple Graphics API support
        Renderer::Initialize(Engine3D::Renderer::API::OPENGL);
    }

    Window& Application::Get(){
        return *instance->window;
    }

    void Application::OnUpdate(float ts){
    }

    void Application::OnEvent(Event& event){
        if(InputPoll::IsKeyPressed(ENGINE_KEY_ESCAPE)){
            coreLogInfo("Escape Pressed!");
            isRunning = false;
        }

        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowResizeEvent>([](auto& event){
            return false;
        });

        dispatcher.Dispatch<WindowCloseEvent>([&](auto& event){
            isRunning = false;
            return true;
        });

        auto iter = layerStack.end();

        while(iter != layerStack.begin()){
            (*--iter)->OnEvent(event);

            if(event.IsEventHandled()) break;
        }
    }

    void Application::Run(){
        //! @note Our vertices data format
        // {pos.x, pos.y, pos.z, r, g, b, a}
        float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 0.1f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

        uint32_t indices[3] = {0, 1, 2};

        BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position", true},
            {ShaderDataType::Float4, "a_Color", true},
       };

		Ref<VertexBuffer> vbo = VertexBuffer::Create(vertices, sizeof(vertices));

		Ref<IndexBuffer> ibo = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        Ref<VertexArray> vao = VertexArray::Create();
        
        vbo->setLayout(layout);
        vao->addVertexBuffer(vbo);
        vao->addIndexBuffer(ibo);

        std::string vertex = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragment = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

        Ref<Shader> shader = Shader::Create(vertex, fragment);
        
        while(isRunning){
            float time = (float)glfwGetTime();
            Renderer::SetClearColor(0.1f, 0.1f, 0.1f, 1);
            Renderer::Clear();

            shader->bind();
            
            // glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
            Renderer::DrawIndexed(vao, vao->GetIndexBuffer()->getCount());

            for(Layer* layer : layerStack){
                layer->onUIRender();
            }

            window->OnUpdate();
        }
    }
};