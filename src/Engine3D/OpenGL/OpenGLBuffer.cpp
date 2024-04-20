#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/interfaces/Buffer.h>

namespace Engine3D{

    VertexBuffer::VertexBuffer(float* vertices, uint32_t size){
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::VertexBuffer(uint32_t size){
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, size * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);
    }

    VertexBuffer::~VertexBuffer(){
        glDeleteBuffers(1, &id);
    }

    void VertexBuffer::bind() const{
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void VertexBuffer::unbind() const{
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::setLayout(const BufferLayout& l){
        layout = l;
    }

    Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size){
        return CreateRef<VertexBuffer>(vertices, size);
    }

    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size){
        return CreateRef<VertexBuffer>(size);
    }




    IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t size) : count(size) {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer(){
        glDeleteBuffers(1, &id);
    }

    void IndexBuffer::bind() const{
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }

    void IndexBuffer::unbind() const{
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size){
        return CreateRef<IndexBuffer>(indices, size);
    }

};