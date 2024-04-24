#pragma once
#include <Engine3D/Core/core.h>
#include <Engine3D/Graphics/Buffer.h>

namespace Engine3D{

    class OpenGLVertexBuffer : public VertexBuffer{
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        OpenGLVertexBuffer(uint32_t size);
        ~OpenGLVertexBuffer();

    private:
        void bind() const override;
        void unbind() const override;

        void setLayout(const BufferLayout& layout) override;

        BufferLayout getLayout() const override;

    private:
        uint32_t id; //! @note Vertex Buffer ID
        BufferLayout layout; // Layout of our buffered data.
    };

    class OpenGLIndexBuffer : public IndexBuffer{
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
        ~OpenGLIndexBuffer();

    private:
        void bind() const override;
        void unbind() const override;

        uint32_t getCount() const override;

    private:
        uint32_t id; // Index Buffer ID
        uint32_t count; // Count of our indices
    };
};