#pragma once
#include "FlyWhale/UI/Core/UIWidget.h"

namespace FlyWhale::UI
{

    class HContainer : public Widget
    {
    public:
        float Spacing = 5.0f;
        float Padding = 5.0f; // Padding from the edge
    };
}