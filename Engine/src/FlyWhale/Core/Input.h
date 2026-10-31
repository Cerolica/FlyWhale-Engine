#pragma once

#include "FlyWhale/Core/Core.h"
#include "FlyWhale/Core/KeyCodes.h"
#include "FlyWhale/Core/MouseCodes.h"

namespace FlyWhale
{

    class Input
    {
    public:
        static bool IsKeyPressed(int keycode);

        static bool IsMouseButtonPressed(int button);
        static std::pair<float, float> GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();
    };
}