#pragma once

#include"FlyWhale/Math/Math.h"

namespace FlyWhale::UI
{

    enum class AnchorPreset
    {
        BottomLeft, BottomCenter, BottomRight, BottomWide,
        CenterLeft, Center,       CenterRight, HCenterWide,
        TopLeft,    TopCenter,    TopRight,    TopWide,
        LeftWide,   VCenterWide,  RightWide,   Stretch, // automatically matches the parent's size
        Custom
    };

    struct AnchorPoint
    {
        float Left, Top, Right, Bottom;
    };

    struct AnchorOffset
    {
        int32_t Left, Top, Right, Bottom;
    };

    class AnchorUtils
    {
    public:
        static AnchorPoint GetPointForPreset(AnchorPreset preset);
    };
}