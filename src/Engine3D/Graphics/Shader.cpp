#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/Graphics/Shader.h>
#include <Engine3D/OpenGL/OpenGLShader.h>
#include <Engine3D/Renderer/Renderer.h>

namespace Engine3D{
    Ref<Shader> Shader::Create(const std::string& name, const std::string& vertex, const std::string& fragment){
        switch (Renderer::CurrentAPI()){
        case Renderer::API::OPENGL:
            return CreateRef<OpenGLShader>(name, vertex, fragment);
        }

        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& filename){
        switch (Renderer::CurrentAPI()){
        case Renderer::API::OPENGL:
            return CreateRef<OpenGLShader>(filename);
        }

        return nullptr;
    }

    void Shader::Bind() const { bind(); }

    void Shader::Unbind() const { unbind(); }

    uint32_t Shader::GetShaderID() const { return getShaderIDInternal(); }

    const std::string& Shader::GetShaderName() const { return getShaderNameInternal(); }

    void Shader::SetFloat3(const std::string& name, const glm::vec3& values){
        UploadFloat3(name, values);
    }

    void Shader::SetFloat4(const std::string& name, const glm::vec4& values){
        UploadFloat4(name, values);
    }
};