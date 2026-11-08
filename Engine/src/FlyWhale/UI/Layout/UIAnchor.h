#pragma once

#include"FlyWhale/Math/Math.h"

namespace FlyWhale::UI
{

    enum class Anchor
    {
        BottomLeft, BottomCenter, BottomRight, BottomWide,
        CenterLeft, Center,       CenterRight, HCenterWide,
        TopLeft,    TopCenter,    TopRight,    TopWide,
        LeftWide,   VCenterWide,  RightWide,   Stretch, // automatically matches the parent's size
        Custom
    };

    struct AnchorPoint
    {
        float Left, Bottom, Right, Top;
    };

    struct AnchorOffset
    {
        int32_t Left, Bottom, Right, Top;
    };

    inline Vector2 AnchorToPivot(Anchor anchor)
    {
        switch (anchor)
        {
            case Anchor::BottomLeft:   return { 0.0f, 0.0f }; break;
            case Anchor::BottomCenter: return { 0.5f, 0.0f }; break;
            case Anchor::BottomRight:  return { 1.0f, 0.0f }; break;
            
            case Anchor::CenterLeft:   return { 0.0f, 0.5f }; break;
            case Anchor::Center:       return { 0.5f, 0.5f }; break;
            case Anchor::CenterRight:  return { 1.0f, 0.5f }; break;
            
            case Anchor::TopLeft:      return { 0.0f, 1.0f }; break;
            case Anchor::TopCenter:    return { 0.5f, 1.0f }; break;
            case Anchor::TopRight:     return { 1.0f, 1.0f }; break;

            case Anchor::Stretch:      return { 0.0f, 0.0f }; break;
            
            default: return { 0.0f, 0.0f }; break;
        }
    }
}