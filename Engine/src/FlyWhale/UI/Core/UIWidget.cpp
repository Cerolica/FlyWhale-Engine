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
            Vector2 pSize = m_Parent->m_Size;
            Vector2 anchorPoint = pPos;

            m_AbsolutePosition.x = pSize.x * (m_AnchorPoint.Left + m_AnchorPoint.Right) / 2.0f;
            m_AbsolutePosition.y = pSize.y * (m_AnchorPoint.Bottom + m_AnchorPoint.Top) / 2.0f;

        }
        else   
            m_AbsolutePosition = m_Position; // Root node
        
        for (auto& child : m_Children)
            child->RecalculateTransform();
    }

    void Widget::LayoutIn(const Rect& parent)
    {
        const Vector2 parentSize = parent.Size();
        /*
        m_Rect.min = parent.min + parentSize * m_AnchorMin + m_OffsetMin;
        m_Rect.max = parent.min + parentSize * m_AnchorMax + m_OffsetMax;
        */
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

    void Widget::UpdateLayout()
    {
        Vector2 miniumSizeNeeded(0.0f, 0.0f);
        for (auto& child : m_Children)
        {
            miniumSizeNeeded += child->GetMiniumSize();
        }
    }

    void Widget::SetAnchor(Anchor anchor)
    {
        m_Anchor = anchor;
        m_Pivot = AnchorToPivot(m_Anchor);
        
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
        

        m_FlagDirty = true;
    }

}