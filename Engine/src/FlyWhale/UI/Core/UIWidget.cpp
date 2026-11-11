#include "fwpch.h"
#include "UIWidget.h"

namespace FlyWhale::UI
{

    void Widget::AddChild(Ref<Widget> child)
    {
        child->m_Parent = this;
        m_Children.push_back(child);
        child->RecalculateTransform(); // Update absolute position immediately
    }

    // Default implementation
    void Widget::OnUpdate(Timestep ts)
    {
        for (auto& child : m_Children) child->OnUpdate(ts);
    }

    void Widget::OnRender() 
    {
        for (auto& child : m_Children) child->OnRender();
    }

    void Widget::OnEvent(Event& e)
    {
        for (auto& child : m_Children) child->OnEvent(e);
    }

    void Widget::RecalculateTransform()
    {
        if (m_Parent)
        {
            Vector2 pPos = m_Parent->m_AbsolutePosition;
            Vector2 pSize = m_Parent->m_MiniumSize;

            FW_CORE_WARN("{2} Parent position: {0}, {1}", pPos.x, pPos.y, m_Name);

            float leftAbsolutePosition = pSize.x * m_AnchorPoint.Left + m_AnchorOffset.Left;
            float rightAbsolutePosition = pSize.x * m_AnchorPoint.Right + m_AnchorOffset.Right;
            float bottomAbsolutePosition = pSize.y * m_AnchorPoint.Bottom + m_AnchorOffset.Bottom;
            float topAbsolutePosition = pSize.y * m_AnchorPoint.Top + m_AnchorOffset.Top;

            m_AbsolutePosition.x = pPos.x 
                                 + (leftAbsolutePosition + rightAbsolutePosition) / 2.0f
                                 - m_Size.x / 2.0f;
            m_AbsolutePosition.y = pPos.y 
                                 + (bottomAbsolutePosition + topAbsolutePosition) / 2.0f
                                 - m_Size.y / 2.0f;
            
            FW_CORE_WARN("{2} Absolute position: {0}, {1}", m_AbsolutePosition.x, m_AbsolutePosition.y, m_Name);

        }
        else   
            m_AbsolutePosition = m_Position; // Root node
        
        for (auto& child : m_Children)
            child->RecalculateTransform();
    }

    void Widget::LayoutIn(const Rect& parentRect)
    {
        const Vector2 parentSize = parentRect.Size();
        
        m_Rect.min.x = parentRect.min.x + parentSize.x * m_AnchorPoint.Left + m_AnchorOffset.Left;
        m_Rect.min.y = parentRect.min.y + parentSize.y * m_AnchorPoint.Bottom + m_AnchorOffset.Bottom;
        m_Rect.max.x = parentRect.min.x + parentSize.x * m_AnchorPoint.Right + m_AnchorOffset.Right;
        m_Rect.max.y = parentRect.min.y + parentSize.y * m_AnchorPoint.Top + m_AnchorOffset.Top;

        FW_CORE_WARN("{4} m_Rect size: {0}, {1}, {2}, {3}",
                     m_Rect.min.x, m_Rect.min.y, m_Rect.max.x, m_Rect.max.y, m_Name);

        m_AbsolutePosition = m_Rect.min;
        m_Size = m_Rect.Size();

        for (const auto& child : m_Children)
            child->LayoutIn(m_Rect);
    }

    bool Widget::IsPointInside(const Vector2& point) const
    {
        return point.x >= m_AbsolutePosition.x && point.x <= m_AbsolutePosition.x + m_Size.x &&
               point.y >= m_AbsolutePosition.y && point.y <= m_AbsolutePosition.y + m_Size.y;
    }

    void Widget::CalculateAnchorOffset()
    {
        m_AnchorOffset.Left = -m_AnchorPoint.Left * m_MiniumSize.x;
        m_AnchorOffset.Bottom = -m_AnchorPoint.Bottom * m_MiniumSize.y;
        m_AnchorOffset.Right = m_MiniumSize.x - m_AnchorPoint.Right * m_MiniumSize.x;
        m_AnchorOffset.Top = m_MiniumSize.y - m_AnchorPoint.Top * m_MiniumSize.y;
        
        FW_CORE_WARN("{4} Widget anchor offset: {0}, {1}, {2}, {3}", 
                     m_AnchorOffset.Left, m_AnchorOffset.Bottom, m_AnchorOffset.Right, m_AnchorOffset.Top, m_Name);
    }

    void Widget::SetAnchor(Anchor anchor)
    {
        m_Anchor = anchor;
        
        switch (m_Anchor)
        {
            case Anchor::BottomLeft:   m_AnchorPoint  = { 0.0f, 0.0f, 0.0f, 0.0f }; break;
            case Anchor::BottomCenter: m_AnchorPoint  = { 0.5f, 0.0f, 0.5f, 0.0f }; break;
            case Anchor::BottomRight:  m_AnchorPoint  = { 1.0f, 0.0f, 1.0f, 0.0f }; break;
            case Anchor::BottomWide:   m_AnchorPoint  = { 0.0f, 0.0f, 1.0f, 0.0f }; break;
            
            case Anchor::CenterLeft:   m_AnchorPoint  = { 0.0f, 0.5f, 0.0f, 0.5f }; break;
            case Anchor::Center:       m_AnchorPoint  = { 0.5f, 0.5f, 0.5f, 0.5f }; break;
            case Anchor::CenterRight:  m_AnchorPoint  = { 1.0f, 0.5f, 1.0f, 0.5f }; break;
            case Anchor::HCenterWide:  m_AnchorPoint  = { 0.0f, 0.5f, 1.0f, 0.5f }; break;
            
            case Anchor::TopLeft:      m_AnchorPoint  = { 0.0f, 1.0f, 0.0f, 1.0f }; break;
            case Anchor::TopCenter:    m_AnchorPoint  = { 0.5f, 1.0f, 0.5f, 1.0f }; break;
            case Anchor::TopRight:     m_AnchorPoint  = { 1.0f, 1.0f, 1.0f, 1.0f }; break;
            case Anchor::TopWide:      m_AnchorPoint  = { 0.0f, 1.0f, 1.0f, 1.0f }; break;

            case Anchor::LeftWide:     m_AnchorPoint  = { 0.0f, 0.0f, 0.0f, 1.0f }; break;
            case Anchor::VCenterWide:  m_AnchorPoint  = { 0.5f, 0.0f, 0.5f, 1.0f }; break;
            case Anchor::RightWide:    m_AnchorPoint  = { 1.0f, 0.0f, 1.0f, 1.0f }; break;

            case Anchor::Stretch:      m_AnchorPoint  = { 0.0f, 0.0f, 1.0f, 1.0f }; break;

            default: break;
        }
        
        CalculateAnchorOffset();
        m_FlagDirty = true;
    }

}