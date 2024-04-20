#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/interfaces/VertexArray.h>

namespace Engine3D{
    static GLenum shaderDatatTypeToOpenGlBaseTypeConversion(ShaderDataType type){
        switch (type){
            case ShaderDataType::None: 
                coreLogInfo("Switch Case: None");
                return 0;
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

    VertexArray::VertexArray(){
        glGenVertexArrays(1, &id);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    }

    VertexArray::~VertexArray(){
        glDeleteVertexArrays(1, &id);
    }

    void VertexArray::bind() const{
        glBindVertexArray(id);
    }

    void VertexArray::unbind() const{
        glBindVertexArray(0);
    }

    void VertexArray::addVertexBuffer(const Ref<VertexBuffer>& buffer){
        coreLogWarn("Size = {}", buffer->getLayout().getElements().size());
        assert(buffer->getLayout().getElements().size());

        glBindVertexArray(id);

        buffer->bind();

        //! @note We take in our layout and then we set our actual vertex array based on our vertex array layout
        const auto& layout = buffer->getLayout();
        for(const auto& element : layout){
            switch (element.type){
            case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
                {
                    glEnableVertexAttribArray(index);
                    glVertexAttribPointer(index, element.getComponentCount(), shaderDatatTypeToOpenGlBaseTypeConversion(element.type), element.isNormalized ? GL_TRUE : GL_FALSE, buffer->getLayout().getStride(), (const void*)element.offset);
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

        vertexBuffers.push_back(buffer);
    }

    void VertexArray::addIndexBuffer(const Ref<IndexBuffer>& buffer){
        glBindVertexArray(id);
        buffer->bind();

        indexBuffer = buffer;
    }

    Ref<VertexArray> VertexArray::Create(){
        return CreateRef<VertexArray>();
    }
};