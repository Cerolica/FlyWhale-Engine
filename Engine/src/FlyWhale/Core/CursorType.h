#pragma once
#include <stdint.h>

namespace FlyWhale
{

    enum class CursorType : uint8_t
    {
        Arrow = 0,
        IBeam,        // Text editing
        Crosshair,
        Hand,         // Clicking links/buttons
        HResize,      // Left-Right resizing (Horizontal SplitContainer)
        VResize,      // Up-Down resizing (Vertical SplitContainer)
        NumCursors
    };
}