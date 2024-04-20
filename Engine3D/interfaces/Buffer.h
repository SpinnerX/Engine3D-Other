#pragma once
#include <Engine3D/Core/core.h>
#include <string>
#include <vector>

namespace Engine3D{

    enum class ShaderDataType : uint8_t{
        None = 0,
        Float, Float2, Float3, Float4,
        Mat3, Mat4,
        Int, Int2, Int3, Int4,
        Bool
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type){
        switch (type){
            case ShaderDataType::None:
                return 0;
            case ShaderDataType::Float: // A float is 4 bytes.
                return 4;
            case ShaderDataType::Float2: // A float2 is 4*2 bytes.
                return 4 * 2;
            case ShaderDataType::Float3: // A float3 is 4*3 bytes.
                return 4 * 3;
            case ShaderDataType::Float4: // A float4 is 4*4 bytes.
                return 4 * 4;
            case ShaderDataType::Mat3: // A Mat3 is 4*3*3 bytes.
                return 4 * 3 * 3;
            case ShaderDataType::Mat4: // A float4 is 4*4*4 bytes.
                return 4 * 4 * 4;
            case ShaderDataType::Int: // A Int is 4 bytes.
                return 4;
            case ShaderDataType::Int2: // A Int2 is 4*2 bytes.
                return 4 * 2;
            case ShaderDataType::Int3: // A Int3 is 4*3 bytes.
                return 4 * 3;
            case ShaderDataType::Int4: // A Int4 is 4 bytes.
                return 4;
            case ShaderDataType::Bool: // A Bool is 1 byte.
                return 1;
        }
        // static_assert(false, "Unknown ShaderDataType!");
        // coreLogWarn("Unknown ShaderDataType!");
        assert(false);
        return 0;
    }

    // Simply just for debugging purpose.
    static std::string ShaderDataTypeToString(ShaderDataType type){
        switch (type){
            case ShaderDataType::None: return "ShaderDataType::None";
            case ShaderDataType::Float:  return "ShaderDataType::Float";
            case ShaderDataType::Float2: return "ShaderDataType::Float2";
            case ShaderDataType::Float3: return "ShaderDataType::Float3";
            case ShaderDataType::Float4: return "ShaderDataType::Float4";
            case ShaderDataType::Mat3:   return "ShaderDataType::Mat3";
            case ShaderDataType::Mat4:   return "ShaderDataType::Mat4";
            case ShaderDataType::Int:    return "ShaderDataType::Int";
            case ShaderDataType::Int2:   return "ShaderDataType::Int2";
            case ShaderDataType::Int3:   return "ShaderDataType::Int3";
            case ShaderDataType::Int4:   return "ShaderDataType::Int4";
            case ShaderDataType::Bool:   return "ShaderDataType::Bool";
        }

        return "Default: meaning no type was given!";
    }


    /**
     * @name BufferElement
     * @note Formatting how we want to access our buffers
     * @note By setting a type a buffer layout
     * @example BufferElement{ ShaderDataType::Float3, "a_Position", true}
     * @note By doing the following we are checking for a few things, the type, variable, and if it is normalized (in this case it's true)
     * @note Like for example if we do Float, Float2, and even Float3. This would be equivalent to something like GL_FLOAT
     * 
     * @note What this does is tell the shader that we are reading in a float of vec3 that is referencing to variable called "a_Position", 
     * @note Which the boolean is for enabling if we would like to normalize this specific data that we are referencing too.
     * @param stride
     * @note Our stride is between our vertex (which is our size) so like an example is (3 * sizeof(float)) which is 3 bytes
     * @note Used to determine the byte offset from one vertex to the next
     * @note Enabling packing vertices and attributes into a single array or storage in seperate arrays
     * @note Usually means to point to beginning of first vertex in array
     * @note Where Stride should be 12, meaning moving from one vertex to the next.
     * 
     * @example glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
     * @example essentially doing, glVertexAttribPointer(0, 3, ShaderDataType, normalized, stride, offset);
     * @note This example shows the format BufferElement is formatting so it's easier to set these parameters.
     * @param offset
     * @note We are setting the offset
    */

    struct BufferElement{
        BufferElement() = default;
        BufferElement(ShaderDataType t, const std::string& n, bool normalized = false) : name(n), type(t), size(ShaderDataTypeSize(type)), offset(0), isNormalized(normalized) {}

        uint32_t getComponentCount() const {
            switch (type){
                case ShaderDataType::None: return 0;
                case ShaderDataType::Float:  return 1;
                case ShaderDataType::Float2: return 2;
                case ShaderDataType::Float3: return 3;
                case ShaderDataType::Float4: return 4;
                case ShaderDataType::Mat3:   return 3 * 3;
                case ShaderDataType::Mat4:   return 4 * 4;
                case ShaderDataType::Int:    return 1;
                case ShaderDataType::Int2:   return 2;
                case ShaderDataType::Int3:   return 3;
                case ShaderDataType::Int4:   return 4;
                case ShaderDataType::Bool:   return 1;
            }

            // static_assert(false, "Unknown ShaderDataType!");
            // coreLogWarn("Unknown ShaderDataType!");
            assert(false);
            return 0;
        }
        friend inline std::ostream& operator<<(std::ostream& outs, BufferElement& element);

        std::string name;
        ShaderDataType type;
        uint32_t offset; // Offset is going to be the offset of this elemenmt inside our BufferLayout class below
        uint32_t size; // size of buffer
        bool isNormalized;
    };

    /**
     * @name BufferLayout
     * @note Handling the layout of our buffer
     * @note Such as instead of handling a single buffer element
     * @note This allows us to handle multiple buffer elmenet and formatting.
     * 
     * @param std::initializer_list<T>
     * @note We should take in a specific amount of formatted elements into our layout
     * @note Specifying that whatever we give this layout is how we want to handle our data.
     * @note Specifying what data to bind our vertex arrays with based on our layout for our vertex buffers!
    */
    class BufferLayout{
        using iterator = std::vector<BufferElement>::iterator;
        using const_iterator = std::vector<BufferElement>::const_iterator;
    public:
        BufferLayout() = default;
        BufferLayout(const std::initializer_list<BufferElement>& list) : elements(list) {
            // Once we have our data, now we can calculate the offset
            calculateOffsetAndStride();
        }

        inline uint32_t getStride() const {
            return stride;
        }

        iterator begin() {
            return elements.begin();
        }

        iterator end() {
            return elements.end();
        }

        // NOTE: To iterate using for range loops, we need const_iterator
        const_iterator begin() const {
            return elements.begin();
        }

        const_iterator end() const {
            return elements.end();
        }

        inline const std::vector<BufferElement>& getElements() const {
            return elements;
        }

    private:
        void calculateOffsetAndStride(){
            uint32_t offset = 0;
            stride = 0;

            // For every element we compute the offset, and while fetching the offset we get the stride.
            for(auto& element : elements){
                element.offset = offset;
                offset += element.size;
                stride += element.size;
            }
        }

    private:
        std::vector<BufferElement> elements;
        uint32_t stride = 0;
    };
    
    class VertexBuffer{
    public:
        VertexBuffer(float* vertices, uint32_t size);
        VertexBuffer(uint32_t size);
        ~VertexBuffer();

        void setLayout(const BufferLayout& layout);

        BufferLayout getLayout() const { return layout; }

        void bind() const;
        void unbind() const;

        static Ref<VertexBuffer> Create(float* vertices, uint32_t size);

        static Ref<VertexBuffer> Create(uint32_t size);

    private:
        uint32_t id;
        BufferLayout layout;
    };

    class IndexBuffer{
    public:
        IndexBuffer(uint32_t* indices, uint32_t size);

        ~IndexBuffer();

        void bind() const;
        void unbind() const;

        uint32_t getCount() const { return count; }

        static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t size);

    private:
        uint32_t id;
        uint32_t count;
    };
};