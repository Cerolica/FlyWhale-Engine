#pragma once
#include "UISplitContainer.h"

namespace FlyWhale::UI
{

    class HSplitContainer : public SplitContainer
    {
       HSplitContainer() { Vertical = false; } 
    };
}