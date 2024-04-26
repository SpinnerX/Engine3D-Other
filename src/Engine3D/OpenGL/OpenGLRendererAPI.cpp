#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/Renderer/RendererAPI.h>

namespace Engine3D{
    RendererAPI* RendererAPI::instance = new RendererAPI();

    void  RendererAPI::Initialize(API api){
        this->api = api;
        glEnable(GL_BLEND | GL_DEPTH);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    API Renderer::CurrentAPI() {
        return instance->api;
    }

    void RendererAPI::SetClearColor(float r, float g, float b, float a){
        glClearColor(r, g, b, a);
    }

    void RendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height){
        glViewport(x, y, width, height);
    }

    void RendererAPI::Clear(){
        //! @note GL_COLOR_BUFFER_BIT - indicates to OpenGL to currently enable writing mode to writing colors
        //! @note GL_DEPTH_BUFFER_BIT - indicates the depth buffer
        //! @note Depth buffer (known as Z buffer) - representing depth information of objects in 3D Space.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RendererAPI::DrawIndexed(uint32_t count){
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }

};