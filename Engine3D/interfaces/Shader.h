#pragma once
#include <Engine3D/Core/core.h>
#include <unordered_map>

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
        // Shader(const std::string& filename);
        // Shader(const std::string& vertex, const std::string& fragment);
    public:
        Shader(const std::string& filename);
        Shader(const std::string& vertex, const std::string& fragment);
        //! @note Using shader program
        void bind();

        //! @note Deleting shader program
        void unbind();

        //! @note This is to take in the vertex and fragment shader as a string
        //! @note For testing
        static Ref<Shader> Create(const std::string& vertex, const std::string& fragment);

        static Ref<Shader> Create(const std::string& filename);

        uint32_t GetShaderID() const { return id; }

    private:
        void InitializeShaders(std::unordered_map<GLenum, std::string>& sources);
        void initializeShaders(bool isEnabled=false, const std::string& vertex="", const std::string fragment="");
        bool compileShaders(std::unordered_map<GLenum, std::string>&);
        void linkShaders(uint32_t& programID);

    private:
        // IO

        //! @note Reading in our shaders that we input into this shader class
        std::string read(const std::string& filename);

        //! @note Processing our shader sources
        std::unordered_map<GLenum, std::string> preProcess(const std::string& src);

    private:
        std::string filename;
        uint32_t id; // shader ID
        std::array<GLenum, 3> shaderIds;
    };
};