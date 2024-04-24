#include <Engine3D/Core/Application.h>
#include <Engine3D/Core/EntryPoint.h>
#include <Engine3D/Graphics/Buffer.h>
#include <Engine3D/Core/Layer.h>

//! @note Playground for testing stuff or just building things
class MyApplication : public Engine3D::Application{
public:
	MyApplication() : Engine3D::Application() {
	}
};




Engine3D::Application* Engine3D::CreateApplication(Engine3D::ApplicationCommandLineArgs args){
	return new MyApplication();
}