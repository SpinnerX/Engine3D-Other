#include <Engine3D/Engine3DPrecompiledHeader.h>

namespace Engine3D{
class MyExampleLayer : public Layer{
public:
    MyExampleLayer() : Layer("MyExampleLayer") {}

    void OnAttach() override {
    }

    //! @note Used for handling cleanly detaching all of our properties for this specific layer.
    void OnDettach() override {}

    //! @note Handling all of our updated events
    void OnUpdate() override{
    }

    //! @note Handling all of our events
    void OnEvent(const Engine3D::Event& event) override {
    }

    //! @note This is used for any of the UI Rendering that will happening
    void OnUIRender() override{
    }

private:
};
};

class MyApplication : public Engine3D::Application{
public:
	MyApplication() : Engine3D::Application() {
		pushLayer(new Engine3D::MyExampleLayer());
	}
};




Engine3D::Application* Engine3D::CreateApplication(Engine3D::ApplicationCommandLineArgs args){
	return new MyApplication();
}