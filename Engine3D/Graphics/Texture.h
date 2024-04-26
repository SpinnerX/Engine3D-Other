#pragma once
#include <Engine3D/Core/core.h>
#include <GLFW/glfw3.h>

namespace Engine3D{

    /**
     * @file Texture.h
     * @note Texture loads an image
     * @note Then in OpenGL we attach this image to our object
    */
    class Texture2D{
    public:
        static Ref<Texture2D> Create(uint32_t w, uint32_t h);
        static Ref<Texture2D> Create(const std::string& filename);

        void Bind(GLenum slot = GL_TEXTURE_2D);

        void Unbind();

        void SetData(void* data, uint32_t size);

        uint32_t GetWidth() const;
        uint32_t GetHeight() const;

        uint32_t GetTextureID() const;

    private:
        virtual uint32_t GetWidthInternal() const = 0;
        virtual uint32_t GetHeightInternal() const = 0;

        virtual uint32_t GetTextureIDInternal() const = 0;
        virtual void BindInternal(GLenum slot) const = 0;

        virtual void UnbindInternal() const = 0;

        virtual void SetDataInternal(void* data, uint32_t size) = 0;
    };

    class Texture3D{
    public:
        static Ref<Texture3D> Create(uint32_t w, uint32_t h);
        static Ref<Texture3D> Create(const std::string& filepath);

        void Bind(GLenum slot = GL_TEXTURE_3D);

        void Unbind();

        void SetData(void* data, uint32_t size);

        uint32_t GetWidth() const;
        uint32_t GetHeight() const;

        uint32_t GetTextureID() const;

    private:
        virtual uint32_t GetWidthInternal() const = 0;
        virtual uint32_t GetHeightInternal() const = 0;

        virtual uint32_t GetTextureIDInternal() const = 0;
        virtual void BindInternal(GLenum slot) const = 0;

        virtual void UnbindInternal() const = 0;

        virtual void SetDataInternal(void* data, uint32_t size) = 0;
    };
};