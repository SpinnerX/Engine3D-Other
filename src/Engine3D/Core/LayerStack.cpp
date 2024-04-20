#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/Core/LayerStack.h>

namespace Engine3D{
    LayerStack::LayerStack(){}

    LayerStack::~LayerStack(){
        for(Layer* layer : layers){
            delete layer;
        }
    }

    void LayerStack::pushlayer(Layer* layer){
        layers.emplace(layers.begin() + layerIndex, layer);
        layerIndex++;
    }

    void LayerStack::pushOverlay(Layer* layer){
        layers.emplace_back(layer);
    }

    void LayerStack::popLayer(Layer* layer){
        auto iter = std::find(layers.begin(), layers.end(), layer);

        if(iter != layers.end()){
            layers.erase(iter);
            layerIndex--;
        }
    }

    void LayerStack::popOverlay(Layer* layer){
        auto iter = std::find(layers.begin(), layers.end(), layer);

        if(iter != layers.end()){
            layers.erase(iter);
        }
    }
};