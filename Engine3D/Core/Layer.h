#pragma once
#include <Engine3D/Core/core.h>
#include <string>
#include <Engine3D/Event/Event.h>

namespace Engine3D{
    //! @note Helping us keep share a monostate for all layers.
    //! @note Have a common BaseLayer for all.
    struct BaseLayer {};
    
    //! @note Layer is implemented by the user
    //! @note Virtual functions are required when implementing these layers.
    class ENGINE_API Layer : public BaseLayer {
    public:
        Layer(const std::string& name = "Default Layer Name");

        virtual ~Layer();

        virtual void OnAttach() = 0;
        virtual void OnDettach() = 0;

        virtual void OnUpdate() = 0;

        virtual void OnEvent(const Event& event) = 0;

        virtual void OnUIRender() = 0;

        inline const std::string& getName() const { return layerName; }

    protected:
        std::string layerName;
    };
};