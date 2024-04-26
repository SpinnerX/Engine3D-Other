#include <Engine3D/Core/core.h>
#include <Engine3D/Graphics/Texture.h>

namespace Engine3D{

    /**
     * @name OpenGLTexture.h
     * @note Loads in a texture
     * @note Handle different image pixel formatting (RGB, RGB8, RGBA, RGBA8)
     * 
    */
    class OpenGLTexture2D : public Texture2D {
    public:
        OpenGLTexture2D(uint32_t w, uint32_t h);
        OpenGLTexture2D(const std::string& filename);
        ~OpenGLTexture2D();

    private:
        uint32_t GetWidthInternal() const override;
        uint32_t GetHeightInternal() const override;

        uint32_t GetTextureIDInternal() const override;
        void BindInternal(GLenum slot) const override;

        void UnbindInternal() const override;

        void SetDataInternal(void* data, uint32_t size) override;

    private:
        uint32_t id=0; // Texture ID
        uint32_t width=0, height=0; // Size of image being loaded
        uint32_t internalFormat=0, formatData=0;
    };

    class OpenGLTexture3D : public Texture3D {
    public:
        OpenGLTexture3D(uint32_t w, uint32_t h);
        OpenGLTexture3D(const std::string& filename);
        ~OpenGLTexture3D();

    private:
        uint32_t GetWidthInternal() const override;
        uint32_t GetHeightInternal() const override;

        uint32_t GetTextureIDInternal() const override;
        void BindInternal(GLenum slot) const override;
        void UnbindInternal() const override;

        void SetDataInternal(void* data, uint32_t size) override;
    private:
        uint32_t id; // Texture ID
        uint32_t width=0, height=0; // Size of image being loaded
        uint32_t internalFormat=0, formattedData=0;
    };
};