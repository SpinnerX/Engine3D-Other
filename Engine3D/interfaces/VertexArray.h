#pragma once
#include <Engine3D/Core/core.h>
#include <vector>
#include <Engine3D/interfaces/Buffer.h>

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
        VertexArray();
        ~VertexArray();

        void bind() const;

        void unbind() const;

        void addVertexBuffer(const Ref<VertexBuffer>& buffer);

        void addIndexBuffer(const Ref<IndexBuffer>& buffer);

        static Ref<VertexArray> Create();

        const std::vector<Ref<VertexBuffer>> GetVertexArray() const { return vertexBuffers; }
        const Ref<IndexBuffer> GetIndexBuffer() const { return indexBuffer; }

    private:
        uint32_t id; // ! @note Our VAO ID.
        uint32_t index = 0; //! @note Keeping track of our current index.
        std::vector<Ref<VertexBuffer> > vertexBuffers;
        Ref<IndexBuffer> indexBuffer;
    };
};