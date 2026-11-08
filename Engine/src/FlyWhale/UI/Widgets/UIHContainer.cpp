#include "fwpch.h"
#include "UIHContainer.h"

namespace FlyWhale::UI
{

    void HContainer::RecalculateTransform()
    {
        if (m_Parent)
        {
            Vector2 pPos = m_Parent->GetAbsolutePosition();
            Vector2 pSize = m_Parent->GetSize();
            Vector2 anchorPoint = pPos;

            if (m_Anchor == Anchor::Stretch)
            {
                m_Size = pSize;
                m_AbsolutePosition = pPos;
            }
            else
            {
                switch (m_Anchor)
                {
                    case Anchor::BottomLeft:   anchorPoint = pPos; break;
                    case Anchor::BottomCenter: anchorPoint = { pPos.x + pSize.x * 0.5f, pPos.y }; break;
                    case Anchor::BottomRight:  anchorPoint = { pPos.x + pSize.x, pPos.y }; break;
                    
                    case Anchor::CenterLeft:   anchorPoint = { pPos.x, pPos.y + pSize.y * 0.5f }; break;
                    case Anchor::Center:       anchorPoint = { pPos.x + pSize.x * 0.5f, pPos.y + pSize.y * 0.5f }; break;
                    case Anchor::CenterRight:  anchorPoint = { pPos.x + pSize.x, pPos.y + pSize.y * 0.5f }; break;
                    
                    case Anchor::TopLeft:      anchorPoint = { pPos.x, pPos.y + pSize.y }; break;
                    case Anchor::TopCenter:    anchorPoint = { pPos.x + pSize.x * 0.5f, pPos.y + pSize.y }; break;
                    case Anchor::TopRight:     anchorPoint = { pPos.x + pSize.x, pPos.y + pSize.y }; break;
                }

                m_AbsolutePosition.x = anchorPoint.x + m_Position.x - (m_Size.x * m_Pivot.x);
                m_AbsolutePosition.y = anchorPoint.y + m_Position.y - (m_Size.y * m_Pivot.y);
            }

        }
        else   
            m_AbsolutePosition = m_Position; // Root node
        
        // Force children into a horizontal line
        float currentX = Padding;
        
        for (auto& child : m_Children)
        {
            child->SetAnchor(Anchor::BottomLeft);
            
            child->SetPosition({ currentX, Padding });

            currentX  += child->GetSize().x  + Spacing;
        }

        //for (auto& child : m_Children)
        //    child->RecalculateTransform();
    }
}