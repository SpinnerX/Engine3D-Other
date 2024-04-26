#pragma once
#include <Engine3D/Core/core.h>
#include <Engine3D/Graphics/VertexArray.h>

namespace Engine3D{
    /**
     * @name Pipeline
     * @note This will handle our actual graphics pipeline
     * @note Such as dealing with how things may be rendered
     * @note Rendering commands to do the actual rendering
     * 
    */
    class Pipeline{
    public:

        static void InitializePipeline();

        static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

        static void Clear(float r, float g, float b, float a);


        /**
         * @name DrawCommand
         * @note Calling this function is only if you do not have a max indices, and simply just want to provide the indices count users provide
         * @note Really great for testing the vao without using the second parameter
        */
        static void DrawCommand(const Ref<VertexArray>& vao);

        /**
         * @param DrawCommand(vao, maxIndices)
         * @note This is a draw command for the actual rendering of our elements
         * @note We allow users to provide the max indices of the elements we are going to be rendering
         * @note Used for if you want to draw elements up to a specific max of indices that user provides
         * @note Great use for when you know you have more indices then the count of your vao
        */
        static void DrawCommand(const Ref<VertexArray>& vao, uint32_t maxIndicesCount);

    };
};