#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/OpenGL/OpenGLTexture.h>
#include <Engine3D/Renderer/Renderer.h>

namespace Engine3D{
    Ref<Texture2D> Texture2D::Create(const std::string& filename){
        switch (Renderer::CurrentAPI()){
        case API::OPENGL:
            return CreateRef<OpenGLTexture2D>(filename);
        }

        assert(false);
        return nullptr;
    }

    Ref<Texture2D> Texture2D::Create(uint32_t w, uint32_t h){
        switch (Renderer::CurrentAPI()){
        case API::OPENGL:
            return CreateRef<OpenGLTexture2D>(w, h);
        }

        assert(false);
        return nullptr;
    }

    uint32_t Texture2D::GetWidth() const { return GetWidthInternal(); }
    uint32_t Texture2D::GetHeight() const { return GetHeightInternal(); }

    uint32_t Texture2D::GetTextureID() const { return GetTextureIDInternal(); }

    void Texture2D::Bind(GLenum slot) { BindInternal(slot); }

    void Texture2D::Unbind() { UnbindInternal(); }

    void Texture2D::SetData(void* data, uint32_t size){
        SetDataInternal(data, size);
    }

    /////////////////////////////////////////////////////
    ////////////////////[ TEXTURE 3D ]///////////////////
    /////////////////////////////////////////////////////
    Ref<Texture3D> Texture3D::Create(uint32_t w, uint32_t h){
    }
    
    Ref<Texture3D> Texture3D::Create(const std::string& filename){
        // switch (Renderer::CurrentAPI()){
        // case API::OPENGL:
        //     return CreateRef<OpenGLTexture3D>(filename);
        // }

        // assert(false);
        // return nullptr;
    }

    uint32_t Texture3D::GetWidth() const { return GetWidthInternal(); }
    uint32_t Texture3D::GetHeight() const { return GetHeightInternal(); }

    uint32_t Texture3D::GetTextureID() const { return GetTextureIDInternal(); }

    void Texture3D::Bind(GLenum slot) { BindInternal(slot); }

    void Texture3D::Unbind() { UnbindInternal(); }

    void Texture3D::SetData(void* data, uint32_t size){
        SetDataInternal(data, size);
    }
};
