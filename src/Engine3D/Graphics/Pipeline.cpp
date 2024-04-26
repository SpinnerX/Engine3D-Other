#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/Graphics/Pipeline.h>

namespace Engine3D{
    void Pipeline::InitializePipeline(){
        // glEnable(GL_BLEND | GL_DEPTH_TEST);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);

        // glEnable(GL_DEPTH_TEST);
    }

    void Pipeline::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height){
        glViewport(x, y, width, height);
    }
    void Pipeline::Clear(float r, float g, float b, float a){
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Pipeline::DrawCommand(const Ref<VertexArray>& vao){
        vao->Bind();

        // glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), nullptr);
        glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void Pipeline::DrawCommand(const Ref<VertexArray>& vao, uint32_t maxIndicesCount){
        uint32_t count = maxIndicesCount ? vao->GetIndexBuffer()->GetCount() : maxIndicesCount;
        vao->Bind();
        // glDrawElements(GL_TRIANGLES, count, nullptr);
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }
}