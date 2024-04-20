#pragma once
#include <Engine3D/Core/core.h>
#include <Engine3D/Core/Layer.h>
#include <vector>

namespace Engine3D{
    class ENGINE_API LayerStack{
        using iterator = std::vector<Layer *>::iterator;
        using const_iterator = std::vector<Layer *>::const_iterator;
    public:
        LayerStack();
        ~LayerStack();

        void pushlayer(Layer* layer);
        void pushOverlay(Layer* layer);

        void popLayer(Layer* layer);
        void popOverlay(Layer* layer);

        iterator begin() { return layers.begin(); }
        iterator end() { return layers.end(); }

    private:
        std::vector<Layer *> layers;
        uint32_t layerIndex = 0;
    };
};