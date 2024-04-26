#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/OpenGL/OpenGLVertexArray.h>

namespace Engine3D{
    static GLenum shaderDatatTypeToOpenGlBaseTypeConversion(ShaderDataType type){
        switch (type){
            case ShaderDataType::Float:  return GL_FLOAT;
            case ShaderDataType::Float2: return GL_FLOAT;
            case ShaderDataType::Float3: return GL_FLOAT;
            case ShaderDataType::Float4: return GL_FLOAT;
            case ShaderDataType::Mat3:   return GL_FLOAT;
            case ShaderDataType::Mat4:   return GL_FLOAT;
            case ShaderDataType::Int:    return GL_INT;
            case ShaderDataType::Int2:   return GL_INT;
            case ShaderDataType::Int3:   return GL_INT;
            case ShaderDataType::Int4:   return GL_INT;
            case ShaderDataType::Bool:   return GL_BOOL;
        }

        // render_core_assert(false, "Unknown ShaderDataType!");
        assert(false);
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray(){
        glGenVertexArrays(1, &id);
    }

    OpenGLVertexArray::~OpenGLVertexArray(){
        glDeleteVertexArrays(1, &id);
    }

    void OpenGLVertexArray::bind() const{
        glBindVertexArray(id);
    }

    void OpenGLVertexArray::unbind() const{
        glBindVertexArray(0);
    }

    const std::vector<Ref<VertexBuffer>> OpenGLVertexArray::getVertexArraysInternal() const{ return vertexes; }
    const Ref<IndexBuffer> OpenGLVertexArray::getIndexBufferInternal() const{ return indexBuffer; }

    void OpenGLVertexArray::addVertexBuffer(const Ref<VertexBuffer>& buffer){
        glBindVertexArray(id);

        buffer->Bind();

        //! @note We take in our layout and then we set our actual vertex array based on our vertex array layout
        index = 0;
        const auto& layout = buffer->GetLayout();
        coreLogWarn("Buffer Elements Size = {}", layout.getElements().size());
        // assert(buffer->GetLayout().getElements().size());
        for(const auto& element : layout){
            switch (element.type){
            case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
                {
                    glEnableVertexAttribArray(index);
                    glVertexAttribPointer(index, element.getComponentCount(), shaderDatatTypeToOpenGlBaseTypeConversion(element.type), element.isNormalized ? GL_TRUE : GL_FALSE, layout.getStride(), (const void*)element.offset);
                    index++;
                }
                break;
            case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			case ShaderDataType::Bool:
                {
                    glEnableVertexAttribArray(index);
                    glVertexAttribIPointer(index, element.getComponentCount(), shaderDatatTypeToOpenGlBaseTypeConversion(element.type), layout.getStride(), (const void*)element.offset);
                    index++;
                }
                break;
            default:
                break;
            }
        }

        vertexes.push_back(buffer);
    }

    void OpenGLVertexArray::addIndexBuffer(const Ref<IndexBuffer>& buffer){
        glBindVertexArray(id);
        buffer->Bind();
        indexBuffer = buffer;
    }
};