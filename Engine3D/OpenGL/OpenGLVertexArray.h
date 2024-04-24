#pragma once
#include <Engine3D/Core/core.h>
#include <Engine3D/Graphics/VertexArray.h>

namespace Engine3D{
    class OpenGLVertexArray : public VertexArray{
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

    private:
        void bind() const override;
        void unbind() const override;

        void addVertexBuffer(const Ref<VertexBuffer>& buffer) override;
        void addIndexBuffer(const Ref<IndexBuffer>& buffer) override;

        const std::vector<Ref<VertexBuffer>> getVertexArraysInternal() const override;
        const Ref<IndexBuffer> getIndexBufferInternal() const override;

    private:
        uint32_t id; // Vertex Array Reference ID
        uint32_t index; // How vertex array keeps track of where we are at in the vao.
        std::vector<Ref<VertexBuffer> > vertexes;
        Ref<IndexBuffer> indexBuffer;
    };
};