#include "fwpch.h"
#include "UIWidget.h"

namespace FlyWhale::UI
{

    void Widget::AddChild(Ref<Widget> child)
    {
        child->m_Parent = this;
        m_Children.push_back(child);
        MarkLayoutDirty();        
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

    bool Widget::IsPointInside(const Vector2& point) const
    {
        return point.x >= m_AbsolutePosition.x && point.x <= m_AbsolutePosition.x + m_Size.x &&
               point.y >= m_AbsolutePosition.y && point.y <= m_AbsolutePosition.y + m_Size.y;
    }

    void Widget::CalculateAnchorOffset()
    {
        if (m_Size.x < m_MiniumSize.x) m_Size.x = m_MiniumSize.x;
        if (m_Size.y < m_MiniumSize.y) m_Size.y = m_MiniumSize.y;

        m_AnchorOffset.Left = -m_AnchorPoint.Left * m_Size.x;
        m_AnchorOffset.Top = -m_AnchorPoint.Top * m_Size.y;
        m_AnchorOffset.Right = m_Size.x - m_AnchorPoint.Right * m_Size.x;
        m_AnchorOffset.Bottom = m_Size.y - m_AnchorPoint.Bottom * m_Size.y;
        
        FW_CORE_WARN("{4} Widget anchor offset: {0}, {1}, {2}, {3}", 
                     m_AnchorOffset.Left, m_AnchorOffset.Bottom, m_AnchorOffset.Right, m_AnchorOffset.Top, m_Name);
    }

    Widget* Widget::SetAnchor(AnchorPreset preset)
    {
        m_AnchorPreset = preset;
        
        m_AnchorPoint = AnchorUtils::GetPointForPreset(m_AnchorPreset);
        
        MarkLayoutDirty();

        return this;
    }

    Widget* Widget::SetAnchorPoint(const AnchorPoint& point)
    {
        m_AnchorPreset = AnchorPreset::Custom;
        m_AnchorPoint = point;

        MarkLayoutDirty();

        return this;
    }

    void Widget::UpdateLayout(const Rect& parentRect)
    {
        const Vector2 parentSize = parentRect.Size();
        
        m_Rect.min.x = parentRect.min.x + parentSize.x * m_AnchorPoint.Left + m_AnchorOffset.Left;
        m_Rect.min.y = parentRect.min.y + parentSize.y * m_AnchorPoint.Top + m_AnchorOffset.Top;
        m_Rect.max.x = parentRect.min.x + parentSize.x * m_AnchorPoint.Right + m_AnchorOffset.Right;
        m_Rect.max.y = parentRect.min.y + parentSize.y * m_AnchorPoint.Bottom + m_AnchorOffset.Bottom;

        FW_CORE_WARN("{4} m_Rect size: {0}, {1}, {2}, {3}",
                     m_Rect.min.x, m_Rect.min.y, m_Rect.max.x, m_Rect.max.y, m_Name);

        m_Size = m_Rect.Size();
    }

    void Widget::UpdateTransform(const Matrix4& parentTransform)
    {
        if (m_Parent)
        {
            Vector2 pPos = m_Parent->m_AbsolutePosition;
            Vector2 pSize = m_Parent->m_MiniumSize;

            FW_CORE_WARN("{2} Parent position: {0}, {1}", pPos.x, pPos.y, m_Name);

            m_AbsolutePosition = m_Rect.min;
            FW_CORE_WARN("{2} Absolute position: {0}, {1}", m_AbsolutePosition.x, m_AbsolutePosition.y, m_Name);

        }
        else   
            m_AbsolutePosition = m_Position; // Root node
    }

    void Widget::ProcessUpdate(const Rect& parentRect, const Matrix4& parentTransform)
    {
        if (!m_LayoutDirty && !m_TransformDirty) return;

        if (m_LayoutDirty)
        {
            CalculateAnchorOffset();
            UpdateLayout(parentRect);
            m_LayoutDirty = false;

            for (auto& child : m_Children)
                child->MarkLayoutDirtyLocal();
        }

        if (m_TransformDirty)
        {
            UpdateTransform(parentTransform);
            m_TransformDirty = false;

            for (auto& child : m_Children)
                child->MarkTransformDirtyLocal();
        }

        for (size_t i = 0; i < m_Children.size(); i++)
        {
            m_Children[i]->ProcessUpdate(GetChildLayoutArea(i), Matrix4(1.0f));
        }
    }

}