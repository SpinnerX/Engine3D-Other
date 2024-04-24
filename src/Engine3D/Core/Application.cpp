#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <filesystem>
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
        Renderer::SetViewport(0, 0, window->GetWidth(), window->GetHeight());
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
        
        while(isRunning){
            float time = (float)glfwGetTime();
            Renderer::SetClearColor(0.1f, 0.1f, 0.1f, 1);
            Renderer::Clear();

            for(Layer* layer : layerStack){
                layer->OnUpdate();
            }

            for(Layer* layer : layerStack){
                layer->OnUIRender();
            }

            window->OnUpdate();
        }
    }
};