#include <Engine3D/Engine3DPrecompiledHeader.h>

namespace Engine3D{
class MyExampleLayer : public Layer{
public:
    MyExampleLayer() : Layer("MyExampleLayer"), controller(1280.0f/720.0f) {}

    void OnAttach() override {
        coreLogInfo("Layer -- {}", this->layerName);
    }

    //! @note Used for handling cleanly detaching all of our properties for this specific layer.
    void OnDettach() override {}

    //! @note Handling all of our updated events
    void OnUpdate(float ts) override{
        controller.OnUpdate(ts);

        Renderer::BeginScene(controller.GetCamera());
        // Renderer::DrawQuad({0.0f, 0.0f, 0.0f}, {5.f, 5.f}, {0.8, 0.2f, 0.3f, 1.0f});
        Renderer::DrawQuad({10.f, 10.f, 0.f}, {100.f, 100.f}, {0.8, 0.2f, 0.3f, 1.0f});
        Renderer::EndScene();
    }

    //! @note Handling all of our events
    void OnEvent(Event& event) override {
    }

    //! @note This is used for any of the UI Rendering that will happening
    void OnUIRender() override{

    }

private:
    OrthographicCameraController controller;
};
};

//! @note Playground for testing stuff or just building things
class MyApplication : public Engine3D::Application{
public:
	MyApplication() : Engine3D::Application() {
		pushLayer(new Engine3D::MyExampleLayer());
	}
};




Engine3D::Application* Engine3D::CreateApplication(Engine3D::ApplicationCommandLineArgs args){
	return new MyApplication();
}