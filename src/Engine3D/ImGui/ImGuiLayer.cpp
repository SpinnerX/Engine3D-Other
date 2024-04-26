#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/ImGui/ImGuiLayer.h>

namespace Engine3D{
    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer"){}

    ImGuiLayer::~ImGuiLayer(){}

    void ImGuiLayer::OnAttach() {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

        float fontSize = 15.0f;
		// @note Loading fonts with ImGui
		/* std::string filename = "assets/opensans/static/OpenSans-Regular.ttf"; */
		std::string sansTtf = "Resources/assets/opensans/static/OpenSans-Regular.ttf";
		io.Fonts->AddFontFromFileTTF(sansTtf.c_str(), fontSize);
		io.FontDefault = io.Fonts->AddFontFromFileTTF(sansTtf.c_str(), fontSize);

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable){
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		SetDarkTheme();

        // Initializing the OpenGL3 ()
        GLFWwindow* window = static_cast<GLFWwindow *>(Application::Get().GetNativeWindow());

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410"); // We should check the version of GLSL (if there is an error with this version)

    }

    void ImGuiLayer::OnDettach(){
        ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
    }

    void ImGuiLayer::Begin(){
        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
		ImGuizmo::BeginFrame();
    }

    void ImGuiLayer::End(){
        ImGuiIO& io = ImGui::GetIO();
        auto app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWidth(), app.GetHeight());

        // We want this part to be controlled by the layers themselves.
        // (or whatever layer we have inside Sandbox)
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable){
            GLFWwindow* backup_current_ctx = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            
            glfwMakeContextCurrent(backup_current_ctx);
        }
    }

    void ImGuiLayer::SetBlockEvents(bool isBlocked){
        isEventBlocked = isBlocked;
    }

    void ImGuiLayer::OnUpdate(float ts){}


    void ImGuiLayer::OnEvent(Event& e) {
        // @note this is to prevent blocking.
		// @note Checking if viewport is not focused to block events.
		if(isEventBlocked){
			ImGuiIO& io = ImGui::GetIO();
			e |= e.inCategory(EventCategoryMouse) & io.WantCaptureMouse;
			e |= e.inCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
		}
    }

    void ImGuiLayer::OnUIRender(){}

    void ImGuiLayer::SetDarkTheme(){
        auto& colors = ImGui::GetStyle().Colors; // @note Colors is ImVec4
		
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		
		
		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };


		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };


		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.15f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		
		// Titles
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.15f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.1f, 0.150f, 0.951f, 1.0f };
    }
};