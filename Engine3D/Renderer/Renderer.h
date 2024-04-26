#pragma once
#include <Engine3D/Core/core.h>
#include <Engine3D/Graphics/VertexArray.h>
#include <Engine3D/Scene/Camera.h>

namespace Engine3D{
    enum class Primitives : uint8_t {
        DEFAULT=0,
        Line,
        Triangle,
        QUAD
    };

    enum class API : uint8_t {
        NONE = 0,
        OPENGL, VULKAN
    };

    //! @name Renderer
    //! @note Will have API-specific pipeline implementations
    //! @note Renderer will also know of what is happening within our environment
    //! @note TODO --- Having Renderer know information of our scene.
    class Renderer{
    public:

        //! @note Initializing our renderer's runtime
        //! @note Specifying our Graphics API through initialization.
        static void Initialize(API api);

        static void ShutdownCleanup();

        static void Clear(uint32_t r, uint32_t g, uint32_t b, uint32_t a);

        static void BeginScene(Camera& camera);

        static void EndScene();

        static API CurrentAPI();


        static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);

         // static void DrawCommand(Ref<VertexArray>& vertexArray);


        //! @note Used for submitting tasks to our renderer command queue
        /*
        -- Example --
        * Submitting our tasks through this submit function
        * And then to be added into our renderer command queue
        Renderer::Submit([instance, vertexArray](){
        });
        */
        template<typename Command>
        static void Submit(const Command& function){
            function();
        }



    private:
        static void DrawQuadInternal(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuadInternalMat(const glm::mat4& transform, const glm::vec4& color);

    private:
        static void FlushReset();

    private:
        static Renderer* instance;
        API api = API::NONE;
    };
};