#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/OpenGL/OpenGLVertexArray.h>

namespace Engine3D{
    Ref<VertexArray> VertexArray::Create(){
        switch (Renderer::CurrentAPI()){
        case Renderer::API::OPENGL:
            return CreateRef<OpenGLVertexArray>();
        }

        coreLogFatal("Unsupported API was detected in VertexArray::Create()");
        assert(false);
        return nullptr;
    }

    const std::vector<Ref<VertexBuffer>> VertexArray::GetVertexArray() const { return getVertexArraysInternal(); }
    const Ref<IndexBuffer> VertexArray::GetIndexBuffer() const { return getIndexBufferInternal(); }
    
    void VertexArray::Bind() const { bind(); }
    void VertexArray::Unbind() const { unbind(); }

    void VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& buffer){ addVertexBuffer(buffer); }

    void VertexArray::AddIndexBuffer(const Ref<IndexBuffer>& buffer){ addIndexBuffer(buffer); }

};