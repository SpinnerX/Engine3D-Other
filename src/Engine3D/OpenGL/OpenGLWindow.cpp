#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/Core/Window.h>

namespace Engine3D{
    static void glfw_error_callback(int error, const char* description){
        coreLogError("Error Code -- [{}] and description -- [{}]", error, description);
    }

    Window* Window::Create(const WindowProperties& properties){
        return new Window(properties);
    }

    Window::Window(const WindowProperties& p) : properties(p) {
        InitializeCore();
    }

    Window::~Window(){
        Cleanup();
    }

    void Window::OnUpdate(){
        glfwSwapBuffers(windowHandler);
        glfwPollEvents();
    }

    void Window::InitializeCore(){
        coreLogInfo("Instantiating Window {}: ({} x {})", properties.title, properties.width, properties.height);

        if(!glfwInit()){
            coreLogWarn("Could not initialize GLFW in {}", __FILE__);
            glfwSetErrorCallback(glfw_error_callback);
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);

        windowHandler = glfwCreateWindow((int)properties.width, (int)properties.height, properties.title.c_str(), nullptr, nullptr);

        glfwMakeContextCurrent(windowHandler);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        coreLogInfo("OpenGL Info:");
		coreLogInfo("  Vendor: {0}", (const char *)glGetString(GL_VENDOR));
		coreLogInfo("  Renderer: {0}", (const char *)glGetString(GL_RENDERER));
		coreLogInfo("  Version: {0}", (const char *)glGetString(GL_VERSION));

        glfwSetWindowUserPointer(windowHandler, &properties);
        SetVSync(true);

        //! @note Setting up callbacks for resizing events
        glfwSetWindowSizeCallback(windowHandler, [](GLFWwindow* window, int w, int h){
            WindowProperties& data = *(WindowProperties *)glfwGetWindowUserPointer(window);

            data.width = w;
            data.height = h;

            WindowResizeEvent event(w, h);
            data.callback(event);
        });

        glfwSetWindowCloseCallback(windowHandler, [](GLFWwindow* window){
            WindowProperties& data = *(WindowProperties *)glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data.callback(event);
        });

        glfwSetKeyCallback(windowHandler, [](GLFWwindow* window, int key, int scancode, int action, int modes){
            WindowProperties& data = *(WindowProperties *)glfwGetWindowUserPointer(window);

            switch (action){
            case GLFW_PRESS:
                {
                    KeyPressedEvent event(static_cast<KeyCode>(key), 0);
                    data.callback(event);
                }
                break;
            case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(static_cast<KeyCode>(key));
                    data.callback(event);
                }
                break;
            case GLFW_REPEAT:
                {
                    KeyPressedEvent event(static_cast<KeyCode>(key), 1);
                    data.callback(event);
                }
                break;
            }
        });

        glfwSetCharCallback(windowHandler, [](GLFWwindow* window, uint32_t keycode){
            WindowProperties& data = *(WindowProperties *)glfwGetWindowUserPointer(window);

            KeyTypedEvent event(static_cast<KeyCode>(keycode));
            data.callback(event);
        });

        glfwSetMouseButtonCallback(windowHandler, [](GLFWwindow* window, int button, int action, int modes){
            WindowProperties& data = *(WindowProperties *)glfwGetWindowUserPointer(window);

            switch (action){
            case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(static_cast<MouseCode>(button));
                    data.callback(event);
                }
                break;
            case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
                    data.callback(event);
                }
                break;
            }
        });

        glfwSetScrollCallback(windowHandler, [](GLFWwindow* window, double xOffset, double yOffset){
            WindowProperties& data = *(WindowProperties *)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.callback(event);
        });
    }

    void* Window::GetNativeWindow() const{
        return windowHandler;
    }

    void Window::Cleanup(){
        glfwDestroyWindow(windowHandler);
    }

    void Window::SetVSync(bool enabled){
        if(enabled){
            glfwSwapInterval(1);
        }
        else{
            glfwSwapInterval(0);
        }

        properties.vsync = enabled;
    }
};