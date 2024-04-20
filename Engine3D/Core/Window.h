#pragma once
#include <Engine3D/Core/core.h>
#include <Engine3D/Event/Event.h>
#include <functional>

class GLFWwindow;

namespace Engine3D{
    struct WindowProperties{
        WindowProperties(const std::string& title="Engine3D", uint32_t w = 1600, uint32_t h = 900) : title(title), width(w), height(h){}

        std::string title;
        uint32_t width;
        uint32_t height;
        bool vsync;
        std::function<void(Event& event)> callback;
    };

    class ENGINE_API Window{
        using EventCallbackFn = std::function<void(Event& event)>;

        Window(const WindowProperties& properties);
    public:
        ~Window();

        static Window* Create(const WindowProperties& properties = WindowProperties());

        void setEventCallback(const EventCallbackFn& callback) {
            properties.callback = callback;
        }

        void OnUpdate();

        uint32_t GetWidth() const { return properties.width; }
        uint32_t GetHeight() const { return properties.height; }

        void SetVSync(bool enabled);

        void* GetNativeWindow() const;

    private:
        //! @note Cleanly initializing or setting up our application
        void InitializeCore();

        //! @note Cleanup for any deallocations and handling cleanly exiting application
        void Cleanup();

    private:
        GLFWwindow* windowHandler;
        WindowProperties properties;
        static Window* instance;
    };
};