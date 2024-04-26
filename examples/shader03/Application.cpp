#include <Engine3D/Engine3DPrecompiledHeader.h>

/**
 * @name Shader Example 03
 * @note In this example im gonna treat shaders as strings for this example
 * @note Showcasing how to utilize BufferLayouts to get data from shaders (glsl)
 * @note Since we know shaders can read from file
*/

namespace Engine3D{
class MyExampleLayer : public Layer{
public:
    MyExampleLayer() : Layer("Shader Example 03") {}

    void OnAttach() override {
        //! @note What our vertices look like without using v_TexCoord
        // {n} - {x, y, z}
        // float vertices[] = {
        //     -0.5f, -0.5f, 0.0f,
        //     0.5f, -0.5f, 0.0f,
        //     0.0f,  0.5f, 0.0f,
        // };

        //! @note These vertices are after we add our Texture Coordinates
        // Here we add our texture coordinates
        // {n} = {pos.x, pos.y, pos.z, texCoord.x, texCoord.y}
		float vertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.f, 0.f,
            0.5f, -0.5f, 0.0f, 1.f, 0.f,
            0.5f,  0.5f, 0.0f, 1.f, 1.f
            -5.0f,  0.5f, 0.0f, 1.f, 1.f
        };

        uint32_t indices[6] = {0, 1, 2, 2, 3, 0};
        
        vbo = VertexBuffer::Create(vertices, sizeof(vertices));
        ibo = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		//! @note Buffer Layout for sending data to our vertex shader
        //! @note Variables specified with layout(location = 0) will be utilized here
        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position", true },
            { ShaderDataType::Float2, "a_TexCoord" }
        };

        vbo->SetLayout(layout);

        //! @note Then creating our vertex array
        vao = VertexArray::Create();
        vao->AddVertexBuffer(vbo);
        vao->AddIndexBuffer(ibo);

        //! @note When calling bind you are indicating 
        vao->Bind();

        //! @note Then we create our shader
        //! @note Rule of thumb if you create a shader manually in this way to bind
        //! @note THis indicates to OpenGL that to use this shader with the buffer data above!
        // Square Color
        glm::vec4 squareColor = {0.2f, 0.3f, 0.8f, 1.0f};

        std::string vertex = R"(
            #version 330 core

            // These are the locations that we specify in our vertex array attributes
            // Keep in mind setting this up you must specify these in your buffer layouts
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec2 a_TexCoord;

            // This is what is specified in OpenGL Code.
            out vec2 v_TexCoord;

            void main(){
                v_TexCoord = a_TexCoord;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";
        std::string fragment = R"(
            #version 330 core

            // This is what will be your output that you'll be using in your OpenGL code.
            layout(location = 0) out vec4 color;

            in vec2 v_TexCoord;
            uniform vec3 u_Color;

            void main(){
                color = vec4(v_TexCoord, 0.0, 1.0);
            }
        )";

        shader = Shader::Create("TextureShader", vertex, fragment);
        shader->Bind();
    }

    //! @note Used for handling cleanly detaching all of our properties for this specific layer.
    void OnDettach() override {}

    //! @note Handling all of our updated events
    void OnUpdate(float ts) override{
    }

    //! @note Handling all of our events
    void OnEvent(Event& event) override {
    }

    //! @note This is used for any of the UI Rendering that will happening
    void OnUIRender() override{
        Pipeline::DrawCommand(vao);
    }

private:
    Ref<VertexBuffer> vbo;
    Ref<IndexBuffer> ibo;
    Ref<VertexArray> vao;
    Ref<Shader> shader;
};
};

//! @note Playground for testing stuff or just building things
class MyApplication : public Engine3D::Application{
public:
	MyApplication() : Engine3D::Application() {
		pushLayer(new Engine3D::MyExampleLayer());
	}
};




Engine3D::Application* Engine3D::CreateApplication(Engine3D::ApplicationCommandLineArgs args){
	return new MyApplication();
}