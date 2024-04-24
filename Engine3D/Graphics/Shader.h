#pragma once
#include <Engine3D/Core/core.h>

namespace Engine3D{
    /**
     * @name Shader
     * @note Since we are going to be supporting multiple different Graphics API
     * @note Because when users run on multiple different platforms will be dependent on our API available
     * 
     * @name ShaderLibrary (TODO)
     * @note Abstraction layers for extracting the different types of layers
    */
    class Shader{
    public:
        virtual ~Shader() = default;

        //! @note This is to take in the vertex and fragment shader as a string
        //! @note For testing
        static Ref<Shader> Create(const std::string& name, const std::string& vertex, const std::string& fragment);

        static Ref<Shader> Create(const std::string& filename);

        void Bind() const;
        void Unbind() const;

        uint32_t GetShaderID() const;
        const std::string& GetShaderName() const;
        
        void SetFloat3(const std::string& name, const glm::vec3& value);

        void SetFloat4(const std::string& name, const glm::vec4& color);

        void SetMat4(const std::string& name, const glm::mat4& matrix);
    private:
        //! @note Using shader program
        virtual void bind() const = 0;

        //! @note Deleting shader program
        virtual void unbind() const = 0;

        virtual void UploadFloat3(const std::string& name, const glm::vec3& value) = 0;

        virtual void UploadFloat4(const std::string& name, const glm::vec4& value) = 0;

        virtual void UploadMat4(const std::string& name, const glm::mat4& transform) = 0;

        virtual uint32_t getShaderIDInternal() const = 0;
        virtual const std::string& getShaderNameInternal() const = 0;

    private:
        std::string shaderName;
        uint32_t rendererID; // shader ID
    };

    /**
     * @name ShaderLibrary
     * @note Automating retrieving specific loaded shaders
     * @note Handle in loading, creating, and modifying shaders.
    */
    class ShaderLibrary{
    public:
        void Add(const Ref<Shader>& shader);
        void Add(const std::string& name, const Ref<Shader>& shader);

        Ref<Shader> Get(const std::string& name);

        Ref<Shader> Load(const std::string& filename);

        void Load(const std::string& name, const std::string& path);

        bool contains(const std::string& name);

    private:
        //! @note Creating a shader and it's name we parsed from the file as it's "unique" key
        std::unordered_map<std::string, Ref<Shader> > shaders;
    };
};