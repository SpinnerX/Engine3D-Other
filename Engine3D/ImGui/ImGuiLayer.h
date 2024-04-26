#pragma once
#include <Engine3D/Core/Layer.h>

namespace Engine3D{
    class ImGuiLayer : public Layer{
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;

        virtual void OnDettach() override;
        virtual void OnUpdate(float ts) override;
        virtual void OnEvent(Event& event) override;

        virtual void OnUIRender() override;

        void Begin();
        void End();

        void SetBlockEvents(bool isBlocked);

        void SetDarkTheme();

    private:
        bool isEventBlocked = true;
        float time = 0.f;
    };
};