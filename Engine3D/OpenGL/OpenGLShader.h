#pragma once
#include <Engine3D/Core/core.h>
#include <Engine3D/Graphics/Shader.h>
#include <unordered_map>
#include <glm/glm.hpp>

namespace Engine3D{
    class OpenGLShader : public Shader{
    public:
        OpenGLShader(const std::string& name, const std::string& vertex, const std::string& fragment);
        OpenGLShader(const std::string& shaderFilename);
        ~OpenGLShader();

    private:
        void bind() const override;
        void unbind() const override;

        uint32_t getShaderIDInternal() const override;
        const std::string& getShaderNameInternal() const override;

        void UploadFloat1(const std::string& name, const float& value) override;
        void UploadFloat2(const std::string& name, const glm::vec2& value) override;
        void UploadFloat3(const std::string& name, const glm::vec3& value) override;
        void UploadFloat4(const std::string& name, const glm::vec4& value) override;

        void UploadInt(const std::string& name, const int value) override;

        void UploadIntArray(const std::string& name, int* array, uint32_t count) override;

        void UploadMat3(const std::string& name, const glm::mat3& transform) override;

        void UploadMat4(const std::string& name, const glm::mat4& transform) override;
    private:
        
        //! @note Reading in our shaders that we input into this shader class
        std::string read(const std::string& filename);

        //! @note Processing our shader sources
        std::unordered_map<GLenum, std::string> preProcess(const std::string& src);

        void CompileShaders(const std::unordered_map<GLenum, std::string>& sources);

        // void Compile(std::unordered_map<GLenum, std::string>& sources);


    private:
        uint32_t id; // shader ID
        std::string name; // name of the shader we are creating
        std::string filepath; // Keeping track of the path to our shader
    };
};