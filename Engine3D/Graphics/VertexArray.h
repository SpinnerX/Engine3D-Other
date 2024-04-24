#pragma once
#include <Engine3D/Core/core.h>
#include <vector>
#include <Engine3D/Graphics/Buffer.h>

namespace Engine3D{
    /**
     * @name VertexArray
     * @note Contains a bunch of vertices
     * @note Reusing vertices with the use of IndexBuffers
     * 
     * 
    */
    class VertexArray{
    public:
        virtual ~VertexArray(){}

        static Ref<VertexArray> Create();

        const std::vector<Ref<VertexBuffer>> GetVertexArray() const;
        const Ref<IndexBuffer> GetIndexBuffer() const;

        void Bind() const;
        void Unbind() const;

        void AddVertexBuffer(const Ref<VertexBuffer>& buffer);
        void AddIndexBuffer(const Ref<IndexBuffer>& buffer);

    private:
        virtual void bind() const = 0;

        virtual void unbind() const = 0;

        virtual void addVertexBuffer(const Ref<VertexBuffer>& buffer) = 0;

        virtual void addIndexBuffer(const Ref<IndexBuffer>& buffer) = 0;

        virtual const std::vector<Ref<VertexBuffer>> getVertexArraysInternal() const = 0;
        virtual const Ref<IndexBuffer> getIndexBufferInternal() const = 0;
    };
};