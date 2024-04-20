#pragma once
#include <Engine3D/Core/core.h>
#include <Engine3D/Event/KeyCodes.h>
#include <Engine3D/Event/MouseCodes.h>
#include <glm/glm.hpp>

namespace Engine3D{
    class ENGINE_API InputPoll{
    public:

        //! @note Key/Mouse event pressed!
        static bool IsKeyPressed(KeyCode keycode);

        static bool IsMousePressed(MouseCode mouseCode);

        //! @note Mouse Position
        inline static glm::vec2 GetMousePos();

        inline static float GetMouseX();

        inline static float GetMouseY();

    private:
        static InputPoll* instance;
        // inline virtual bool isKeyPressed(KeyCode keycode) = 0;
        // inline virtual bool isMousePressed(MouseCode mouseCode) = 0;

        // inline glm::vec2 getMousePos() = 0;

    };
};