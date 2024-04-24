#include <Engine3D/Engine3DPrecompiledHeader.h>

/**
 * 
 * \file Shader01
 * @note This example just shows how to create a basic shader program
 * @note Utilizing the basic shader system, I built there are two ways of creating a shader
 * @note Shader::Create(vertex, fragment)
 * @note This shader function allows you to create a shader program via as a string
 * @note And creating a shader that way if your a beginner learning about shaders
 * 
 * @note Keep in mind, this example is for if your learning OpenGL for the first time
 * @note Then this would be a good time to get use at making basic shaders and working with glsl and making your own shaders
 * @note Though if you are familar with OpenGL, there are features in Engine3D that will be easier to utilize
 * @note Like different draw functions that already do this work on the back-end
*/

namespace Engine3D{
class MyExampleLayer : public Layer{
public:
    MyExampleLayer() : Layer("MyExampleLayer") {}

    void OnAttach() override {
        //! @note This is saying that you want to render a triangle that has 3 indices and 4 positions each
        //! @note Uncomment this and comment the vertices below to see what the differences are?
        //! @note Another thing in mind is that when creating these positions change the type of the buffer layout for gl_Position
        //! @note As of right now It is float3, but if you comment that vertices and uncomment this one change it to Float4.
        // float vertices[] = {
        //     -0.5f, -0.5f, 0.0f, 0.8f,
        //     0.5f, -0.5f, 0.0f, 0.2f,
        //     0.0f,  0.5f, 0.0f, 0.8f
        // };

        //! @note n is the index that correspond with those positions
        // {n} - {x, y, z}
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f,
        };

        uint32_t indices[] = {0, 1, 2};
        // coreLogInfo("Size using sizeof = {}", sizeof(vertices));

        //! @note Creaing our vertex and index buffer.
        //! @note sizeof() gives us the size in bytes of our vertices
        vbo = VertexBuffer::Create(vertices, sizeof(vertices));
        ibo = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

        /**
         * @note We are specifying our input attributes for our shaders
         * @note That the vertex array will utilize these known attributes
         * @note By creating a buffer layout we structure what attributes we'd like to access
         * 
         * !@note Parameters that buffer layout takes.
         * 
         * @param ShaderDataType
         * @note Specifying the type we are getting the output from
         * 
         * @param string
         * @note Keep in mind that this is a string, where the string is the outputted variable from our shader
         * 
         * @param bool
         * @note This is indicating if we would like to normalize the our variables.
        */
        BufferLayout layout = {
            { ShaderDataType::Float3, "gl_Position", true },
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
        std::string redShaderSource = "Resources/shaders/basics/Red.glsl";
        Ref<Shader> shader = Shader::Create(redShaderSource);
        shader->Bind();
    }

    //! @note Used for handling cleanly detaching all of our properties for this specific layer.
    void OnDettach() override {}

    //! @note Handling all of our updated events
    void OnUpdate() override{
    }

    //! @note Handling all of our events
    void OnEvent(const Engine3D::Event& event) override {
    }

    //! @note This is used for any of the UI Rendering that will happening
    void OnUIRender() override{

        Renderer::DrawIndexed(vao);
    }

private:
    Ref<VertexBuffer> vbo;
    Ref<IndexBuffer> ibo;
    Ref<VertexArray> vao;
    Ref<Shader> shader;
};
};

class MyApplication : public Engine3D::Application{
public:
	MyApplication() : Engine3D::Application() {
		pushLayer(new Engine3D::MyExampleLayer());
	}
};




Engine3D::Application* Engine3D::CreateApplication(Engine3D::ApplicationCommandLineArgs args){
	return new MyApplication();
}