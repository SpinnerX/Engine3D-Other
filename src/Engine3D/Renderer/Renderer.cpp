#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/Renderer/Renderer.h>


namespace Engine3D{
    Renderer* Renderer::instance = new Renderer();
    void Renderer::Initialize(Renderer::API other){
        auto& window = Application::Get();
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        instance->api = other;
        instance->SetViewport(0, 0, window.GetWidth(), window.GetHeight());
    }

    Renderer::API Renderer::CurrentAPI() {
        return instance->api;
    }

    void Renderer::SetClearColor(float r, float g, float b, float a){
        glClearColor(r, g, b, a);
    }

    void Renderer::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height){
        glViewport(x, y, width, height);
    }

    void Renderer::Clear(){
        //! @note GL_COLOR_BUFFER_BIT - indicates to OpenGL to currently enable writing mode to writing colors
        //! @note GL_DEPTH_BUFFER_BIT - indicates the depth buffer
        //! @note Depth buffer (known as Z buffer) - representing depth information of objects in 3D Space.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::DrawIndexed(Ref<VertexArray>& vertexArray){
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
};