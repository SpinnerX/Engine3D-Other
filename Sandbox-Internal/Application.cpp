#include <Engine3D/Core/Application.h>
#include <Engine3D/Core/EntryPoint.h>
#include <Engine3D/interfaces/Buffer.h>
#include <Engine3D/Core/Layer.h>

class MyApplication : public Engine3D::Application{
public:
	MyApplication() : Engine3D::Application() {
		// pushLayer(new Engine3D::ExampleLayer3D());
	}
};




Engine3D::Application* Engine3D::CreateApplication(Engine3D::ApplicationCommandLineArgs args){
	return new MyApplication();
}