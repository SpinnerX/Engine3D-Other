#pragma once
#include <Engine3D/Core/core.h>
#include <Engine3D/interfaces/VertexArray.h>

namespace Engine3D{
    //! @name Renderer
    //! @note Will have API-specific pipeline implementations
    //! @note Renderer will also know of what is happening within our environment
    //! @note TODO --- Having Renderer know information of our scene.
    class Renderer{
    public:
        enum class API{
            NONE = 0, OPENGL, VULKAN, DIRECTX
        };

        //! @note Initializing our renderer's runtime
        //! @note Specifying our Graphics API through initialization.
        static void Initialize(Renderer::API api);

        static Renderer::API CurrentAPI();

        static void SetClearColor(float r, float g, float b, float a);
        static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
        static void Clear();


    // private:
        static void DrawIndexed(Ref<VertexArray>& vertexArray, uint32_t indexCount);
        
    private:
        static Renderer* instance;
        Renderer::API api = API::NONE;
    };
};