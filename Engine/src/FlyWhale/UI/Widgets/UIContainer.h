#pragma once
#include "FlyWhale/UI/Core/UIWidget.h"

namespace FlyWhale::UI
{

    class Container : public Widget
    {
    public:
        Container(const std::string& name = "Container")
            : Widget(name) {}
    };
}