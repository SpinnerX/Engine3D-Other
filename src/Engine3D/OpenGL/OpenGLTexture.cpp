#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/OpenGL/OpenGLTexture.h>

namespace Engine3D{
    OpenGLTexture2D::OpenGLTexture2D(uint32_t w, uint32_t h) : width(w), height(h) {
        internalFormat = GL_RGBA8;
        formatData = GL_RGBA;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture2D::OpenGLTexture2D(const std::string& filename){
        int imageWidth, imageHeight, channels;
        stbi_set_flip_vertically_on_load(1);

        //! @note Loading our image before setting our data to glTexImage2D
        stbi_uc* data = stbi_load(filename.c_str(), &imageWidth, &imageHeight, &channels, 0);

        if(!data){
            coreLogError("Failed to load texture image!");
            // assert(false);
        }
        else coreLogInfo("Successfully loaded image!");

        int internalData = 0, formattedData = 0;
        if(channels == 4){
            internalData = GL_RGBA8;
            formattedData = GL_RGBA;
        }
        else if(channels == 3){
            internalData = GL_RGB8;
            formattedData = GL_RGB;
        }

        internalFormat = internalData;
        formatData = formattedData;

        width = imageWidth;
        height = imageHeight;

        //! @note Initializing our textures and preparing that data before loading the image
        glGenTextures(1, &id);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, id);
        // glCreateTextures(GL_TEXTURE_2D, 1, &id);
        // glTextureStorage2D(id, 1, internalFormat, width, height);
        glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);



        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, formatData, GL_UNSIGNED_BYTE, data); // In OpenGL how you can start generating your textures
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);

        // glBindTexture(GL_TEXTURE_2D, 0);
    }

    OpenGLTexture2D::~OpenGLTexture2D(){
        glDeleteTextures(1, &id);
    }
    
    void OpenGLTexture2D::BindInternal(GLenum slot) const{
        // glBindTextureUnit(slot, id);
        glBindTexture(slot, id); // Instead of using this we have to use glBindTexture on Mac
    }

    void OpenGLTexture2D::UnbindInternal() const{
    }

    void OpenGLTexture2D::SetDataInternal(void* data, uint32_t size){
        uint32_t bpp = formatData == GL_RGBA ? 4 : 3;
        glTexSubImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, formatData, GL_UNSIGNED_BYTE, data);
    }

    uint32_t OpenGLTexture2D::GetWidthInternal() const{ return height; }

    uint32_t OpenGLTexture2D::GetHeightInternal() const{ return width; }

    uint32_t OpenGLTexture2D::GetTextureIDInternal() const{ return id; }




    /////////////////////////////////////////////////////
    ////////////////////[ TEXTURE 3D ]///////////////////
    /////////////////////////////////////////////////////
    OpenGLTexture3D::OpenGLTexture3D(uint32_t w, uint32_t h) {}
    
    OpenGLTexture3D::OpenGLTexture3D(const std::string& filename){
        int imageWidth, imageHeight, channels;
        stbi_set_flip_vertically_on_load(1);

        //! @note Initializing our textures and preparing that data before loading the image
        glGenTextures(1, &id);
        // glCreateTextures(GL_TEXTURE_2D, 1, &id);
        glBindTexture(GL_TEXTURE_3D, id);
        // glTextureStorage2D(id, 1, GL_RGB8, width, height);
        
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        //! @note Loading our image before setting our data to glTexImage2D
        stbi_uc* data = stbi_load(filename.c_str(), &imageWidth, &imageHeight, &channels, 0);

        if(!data){
            coreLogError("Failed to load texture image!");
            // assert(false);
        }
        else coreLogInfo("Successfully loaded image!");

        width = imageWidth;
        height = imageHeight;


        glTexImage2D(GL_TEXTURE_3D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); // In OpenGL how you can start generating your textures
        glGenerateMipmap(GL_TEXTURE_3D);

        stbi_image_free(data);
    }

    OpenGLTexture3D::~OpenGLTexture3D(){
        glDeleteTextures(1, &id);
    }

    uint32_t OpenGLTexture3D::GetWidthInternal() const{ return width; }

    uint32_t OpenGLTexture3D::GetHeightInternal() const{ return height; }

    uint32_t OpenGLTexture3D::GetTextureIDInternal() const{ return id; }

    void OpenGLTexture3D::BindInternal(GLenum slot) const{
        glBindTexture(slot, id);
    }

    void OpenGLTexture3D::UnbindInternal() const {
    }

    void OpenGLTexture3D::SetDataInternal(void* data, uint32_t size){
        uint32_t bpp = formattedData == GL_RGBA ? 4 : 3;
        // glTexSubImage2D(GL_TEXTURE_3D, 0, internalFormat, width, height, 0, formattedData, GL_UNSIGNED_BYTE, data);
        // glTexSubImage3D(GL_TEXTURE_3D, 0, internalFormat, width, height, 0, formattedData, GL_UNSIGNED_BYTE, data);
        glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, width, height, 0, formattedData, GL_UNSIGNED_BYTE, data);
    }

};