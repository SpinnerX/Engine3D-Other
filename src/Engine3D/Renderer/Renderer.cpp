#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/Renderer/Renderer.h>
#include <Engine3D/Graphics/Pipeline.h>

namespace Engine3D{
    //! @note TODO remove static instance, and just create an either Render2D Data or some data structure in src file to handle all of this being done
    Renderer* Renderer::instance = new Renderer();

    struct Statistics{
        uint32_t drawCalls = 0; // number of draw calls
        uint32_t quadCount = 0;

        uint32_t getTotalVertexCount() { return quadCount * 4; }
        uint32_t getTotalIndexCount() { return quadCount * 6; }
    };

    struct QuadVertex{
        glm::vec3 pos;
        glm::vec4 color;
        glm::vec2 texCoord;
        float texIndex;
        float tilingFactor;
    };

    struct Renderer2DProperties{
        static const uint32_t maxQuads = 10000; // max for how many quads we can Render
		static const uint32_t maxVertices = maxQuads * 4; // max of vertices we can have every single draw quad
		static const uint32_t maxIndices = maxQuads * 6; // Since we have around 6 indices per quad
		static const uint32_t maxTextureSlots = 16; // Mac = 16, Windows maybe = 32.
        
        //! @note Quad information
        Ref<VertexArray> quadVao;
        Ref<VertexBuffer> quadVbo;
        uint32_t quadIndexCount = 0;
        Ref<Shader> quadTextureShader;
        Ref<Texture2D> whiteTexture;
        Ref<Texture2D> quadTexture;

        QuadVertex* quadVertBufferBase = nullptr;
        QuadVertex* quadVertBufferPtr = nullptr;

        std::array<Ref<Texture2D>, maxTextureSlots> textureSlots;
        uint32_t textureSlotIndex = 0;
        std::array<glm::vec4, 4> quadVertexPositions;

        Statistics rendererStats;
    };
    

    static Renderer2DProperties renderProperties;


    void Renderer::Initialize(API other){
        instance->api = other;
        
        auto& window = Application::Get();

        Pipeline::InitializePipeline();
        Pipeline::SetViewport(0, 0, window.GetWidth(), window.GetHeight());

        //! @note Initializing our quad data
        renderProperties.quadVao = VertexArray::Create();
        renderProperties.quadVbo = VertexBuffer::Create(renderProperties.maxVertices * sizeof(QuadVertex));

        renderProperties.quadVertBufferBase = new QuadVertex[renderProperties.maxVertices * sizeof(QuadVertex)];

        renderProperties.quadVbo->SetLayout({
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float, "a_TexIndex" },
			{ ShaderDataType::Float, "a_TilingFactor" },
			{ ShaderDataType::Int, "a_EntityID" }
        });

        renderProperties.quadVao->AddVertexBuffer(renderProperties.quadVbo);

        //! @note Setting up our quad indices.
        uint32_t* indices =  new uint32_t[renderProperties.maxIndices];
        uint32_t offset = 0;

        for(uint32_t i = 0; i < renderProperties.maxIndices; i += 6){
            indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
			
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
        }

        Ref<IndexBuffer> ibo = IndexBuffer::Create(indices, renderProperties.maxIndices);
        renderProperties.quadVao->AddIndexBuffer(ibo);

        delete[] indices;

        renderProperties.whiteTexture = Texture2D::Create(1,1);
		uint32_t whiteTextureData = 0xffffffff; // four f's for every channel
		renderProperties.whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

        int32_t samplers[renderProperties.maxTextureSlots];

        for(uint32_t i = 0; i < renderProperties.maxTextureSlots; i++)
            samplers[i] = i;

        renderProperties.quadTextureShader = Shader::Create("Resources/shaders/engine/Render2D_Texture2.glsl");
		renderProperties.quadTextureShader->Bind();
		renderProperties.quadTextureShader->Set("u_Textures", samplers, renderProperties.maxTextureSlots);

		// Texture slot at 0 to white texture
		renderProperties.textureSlots[0] = renderProperties.whiteTexture;
		renderProperties.quadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f};
		renderProperties.quadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f};
		renderProperties.quadVertexPositions[2] = { 0.5f, 0.5f, 0.0f, 1.0f};
		renderProperties.quadVertexPositions[3] = { -0.5f, 0.5f, 0.0f, 1.0f};
    }

    void Renderer::Clear(uint32_t r, uint32_t g, uint32_t b, uint32_t a){
        memset(&renderProperties.rendererStats, 0, sizeof(Statistics));
        Pipeline::Clear(r, g, b, a);
    }

    void Renderer::BeginScene(Camera& camera){
        renderProperties.quadTextureShader->Bind();
        renderProperties.quadTextureShader->Set("u_ViewProjection", camera.GetViewProjectionMatrix());

        renderProperties.quadIndexCount = 0;
		renderProperties.quadVertBufferPtr = renderProperties.quadVertBufferBase; // Keeping track o our base memory allocations
		
		renderProperties.textureSlotIndex = 1;
    }

    void Renderer::EndScene(){
        uint32_t dataSize = (uint8_t *)renderProperties.quadVertBufferPtr - (uint8_t *)renderProperties.quadVertBufferBase;
		renderProperties.quadVbo->SetData(renderProperties.quadVertBufferBase, dataSize);
        FlushReset();
    }

    void Renderer::ShutdownCleanup(){}

    API Renderer::CurrentAPI() {
        return instance->api;
    }

    void Renderer::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color){
        DrawQuadInternal({pos.x, pos.y, 0.0f}, size, color);
    }

    void Renderer::DrawQuadInternal(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color){
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
                        * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
        DrawQuadInternalMat(transform, color);
    }

    void Renderer::DrawQuadInternalMat(const glm::mat4& transform, const glm::vec4& color){
        if(renderProperties.quadIndexCount >= Renderer2DProperties::maxIndices){
            FlushReset();
        }

        constexpr size_t quadVertexCount = 4;
        constexpr glm::vec2 textureCoords[] = { {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};
		
		const float textureIndex = 0.0f; // Being our white texture
		const float tilingFactor = 1.0f;

        for(size_t i = 0; i < quadVertexCount; i++){
            // renderProperties.quadVertBufferPtr->pos = transform * renderProperties.quadVertexPositions[i];
            renderProperties.quadVertBufferPtr->pos = transform * renderProperties.quadVertexPositions[i];
			renderProperties.quadVertBufferPtr->color = color;
			renderProperties.quadVertBufferPtr->texCoord = textureCoords[i];
			renderProperties.quadVertBufferPtr->texIndex = textureIndex;
			renderProperties.quadVertBufferPtr->tilingFactor = tilingFactor;
			// renderProperties.quadVertBufferPtr->entityID = entityID;

			renderProperties.quadVertBufferPtr++;
        }

        renderProperties.quadIndexCount += 6;
        renderProperties.rendererStats.quadCount++;
    }

    void Renderer::FlushReset(){
        for(uint32_t i = 0; i < renderProperties.textureSlotIndex; i++){
            renderProperties.textureSlots[i]->Bind(i);
        }

        Pipeline::DrawCommand(renderProperties.quadVao, renderProperties.quadIndexCount);

        renderProperties.rendererStats.drawCalls++;
    }
};