#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/Graphics/Buffer.h>
#include <Engine3D/OpenGL/OpenGLBuffer.h>


namespace Engine3D{
    Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size){
        switch (Renderer::CurrentAPI()){
        case Renderer::API::OPENGL:
            return CreateRef<OpenGLVertexBuffer>(vertices, size);
        }
        coreLogFatal("Unsupported API was detected in VertexBuffer::Create(vertices, size)");
        assert(false);
        return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size){
        switch (Renderer::CurrentAPI()){
        case Renderer::API::OPENGL:
            return CreateRef<OpenGLVertexBuffer>(size);
        }
        coreLogFatal("Unsupported API was detected in VertexBuffer::Create(size)");
        assert(false);
        return nullptr;
    }

    void VertexBuffer::Bind() const { bind(); }
    void VertexBuffer::Unbind() const { unbind(); }

    void VertexBuffer::SetLayout(const BufferLayout& layout) { setLayout(layout); }

    BufferLayout VertexBuffer::GetLayout() const { return getLayout(); }



    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size){
        switch (Renderer::CurrentAPI()){
        case Renderer::API::OPENGL:
            return CreateRef<OpenGLIndexBuffer>(indices, size);
        }
        coreLogFatal("Unsupported API was detected in IndexBuffer::Create(indices, count)");
        assert(false);
        return nullptr;
    }

    void IndexBuffer::Bind() const { bind(); }

    void IndexBuffer::Unbind() const { unbind(); }

    uint32_t IndexBuffer::GetCount() const{ return getCount(); }
};