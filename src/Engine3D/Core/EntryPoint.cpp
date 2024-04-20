#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/Core/EntryPoint.h>

#ifndef ENGINE_PLATFORMS_WINDOWS
extern Engine3D::Application* Engine3D::CreateApplication(Engine3D::ApplicationCommandLineArgs args);

int main(int argc, char** argv){
    Engine3D::EngineLogger::Init();
    auto app = Engine3D::CreateApplication({argc, argv});
    app->Run();
    delete app;
}
#else
extern Engine3D::Application* Engine3D::CreateApplication(Engine3D::ApplicationCommandLineArgs args);

int main(int argc, char** argv){
    auto app = Engine3D::CreateApplication();
    app->Run();
    delete app;
}
#endif