#pragma once
#include "UISplitContainer.h"

namespace FlyWhale::UI
{

    class VSplitContainer : public SplitContainer
    {
        VSplitContainer() { Vertical = true; }
    };
}