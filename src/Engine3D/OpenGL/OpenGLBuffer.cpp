#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/OpenGL/OpenGLBuffer.h>

namespace Engine3D{

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size){
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size){
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, size * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer(){
        glDeleteBuffers(1, &id);
    }

    void OpenGLVertexBuffer::bind() const{
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void OpenGLVertexBuffer::unbind() const{
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLVertexBuffer::setLayout(const BufferLayout& l){
        layout = l;
    }

    void OpenGLVertexBuffer::SetDataInternal(void* data, uint32_t size) {
        glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    BufferLayout OpenGLVertexBuffer::getLayout() const{ return layout; }

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t size) : count(size) {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer(){
        glDeleteBuffers(1, &id);
    }

    void OpenGLIndexBuffer::bind() const{
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }

    void OpenGLIndexBuffer::unbind() const{
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    uint32_t OpenGLIndexBuffer::getCount() const {
        return count;
    }

};