#pragma once
#include <Engine3D/Core/core.h>
#include <Engine3D/Core/Window.h>
#include <Engine3D/Core/LayerStack.h>
#include <cassert>

#include <Engine3D/Event/MouseEvent.h>

namespace Engine3D{

    struct ApplicationCommandLineArgs{
		int count = 0;
		char** args = nullptr;

		const char* operator[](int index) const {
			assert(index < count);
			return args[index];
		}
	};

    class Application{
    public:
        Application();
        
        template<typename T>
        void pushLayer(Layer* layer){
            layerStack.pushlayer(layer);
        }

        template<typename T>
        void pushOverlay(Layer* layer){
            layerStack.pushOverlay(layer);
        }

        static Window& Get();

        void Run();

    private:

        void OnUpdate(float ts);

        void OnEvent(Event& event);

    private:
        Ref<Window> window;
        bool isRunning;
        bool isMinimized;

        ApplicationCommandLineArgs commandLineArguments;

    private:
        static Application* instance;
        LayerStack layerStack;
    };

    Application* CreateApplication(ApplicationCommandLineArgs commandLineArgs);
};