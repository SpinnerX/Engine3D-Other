#include <Engine3D/Engine3DPrecompiledHeader.h>

namespace Engine3D{
class MyExampleLayer : public Layer{
public:
    MyExampleLayer() : Layer("MyExampleLayer") {}

    void OnAttach() override {
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f,
        };

        uint32_t indices[] = {0, 1, 2};

        vbo = VertexBuffer::Create(vertices, sizeof(vertices));
        ibo = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
        };

        vbo->SetLayout(layout);

        //! @note Then creating our vertex array
        vao = VertexArray::Create();
        vao->AddVertexBuffer(vbo);
        vao->AddIndexBuffer(ibo);
        vao->Bind();

        // std::string redShaderSourceVert = "Resources/shaders/foo/Red0.vert";
        // std::string redShaderFrag = "Resources/shaders/foo/Red1.frag";
        std::string redShaderSource = "Resources/shaders/Basics/Red.glsl";
        Ref<Shader> shader = Shader::Create(redShaderSource);
        library.Add(shader);
    }

    //! @note Used for handling cleanly detaching all of our properties for this specific layer.
    void OnDettach() override {}

    //! @note Handling all of our updated events
    void OnUpdate() override{
        auto shader = library.Get("Red");
        shader->Bind();
        glm::vec4 squareColor = {0.2f, 0.3f, 0.8f, 1.0f};
        shader->SetFloat4("u_Color", squareColor); // Setting our u_Color in glsl
        
        Renderer::DrawIndexed(vao);
    }

    //! @note Handling all of our events
    void OnEvent(const Engine3D::Event& event) override {
    }

    //! @note This is used for any of the UI Rendering that will happening
    void OnUIRender() override{
    }

private:
    Ref<VertexBuffer> vbo;
    Ref<IndexBuffer> ibo;
    Ref<VertexArray> vao;
    ShaderLibrary library;
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