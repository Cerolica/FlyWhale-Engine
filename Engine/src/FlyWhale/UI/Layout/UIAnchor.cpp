#include "fwpch.h"
#include "UIAnchor.h"


namespace FlyWhale::UI
{

    AnchorPoint AnchorUtils::GetPointForPreset(AnchorPreset preset)
    {
        switch (preset)
        {
            case AnchorPreset::BottomLeft:   return { 0.0f, 1.0f, 0.0f, 1.0f }; 
            case AnchorPreset::BottomCenter: return { 0.5f, 1.0f, 0.5f, 1.0f }; 
            case AnchorPreset::BottomRight:  return { 1.0f, 1.0f, 1.0f, 1.0f }; 
            case AnchorPreset::BottomWide:   return { 0.0f, 1.0f, 1.0f, 1.0f }; 
            
            case AnchorPreset::CenterLeft:   return { 0.0f, 0.5f, 0.0f, 0.5f }; 
            case AnchorPreset::Center:       return { 0.5f, 0.5f, 0.5f, 0.5f }; 
            case AnchorPreset::CenterRight:  return { 1.0f, 0.5f, 1.0f, 0.5f }; 
            case AnchorPreset::HCenterWide:  return { 0.0f, 0.5f, 1.0f, 0.5f }; 
            
            case AnchorPreset::TopLeft:      return { 0.0f, 0.0f, 0.0f, 0.0f }; 
            case AnchorPreset::TopCenter:    return { 0.5f, 0.0f, 0.5f, 0.0f }; 
            case AnchorPreset::TopRight:     return { 1.0f, 0.0f, 1.0f, 0.0f }; 
            case AnchorPreset::TopWide:      return { 0.0f, 0.0f, 1.0f, 0.0f }; 

            case AnchorPreset::LeftWide:     return { 0.0f, 0.0f, 0.0f, 1.0f }; 
            case AnchorPreset::VCenterWide:  return { 0.5f, 0.0f, 0.5f, 1.0f }; 
            case AnchorPreset::RightWide:    return { 1.0f, 0.0f, 1.0f, 1.0f }; 

            case AnchorPreset::Stretch:      return { 0.0f, 0.0f, 1.0f, 1.0f }; 

            default:                         return { 0.0f, 0.0f, 0.0f, 0.0f };
        }
    }
}