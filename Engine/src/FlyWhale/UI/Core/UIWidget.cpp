#include "fwpch.h"
#include "UIWidget.h"

namespace FlyWhale::UI
{

    void UIWidget::AddChild(Ref<UIWidget> child)
    {
        child->m_Parent = this;
        m_Children.push_back(child);
        child->RecalculateTransform(); // Update absolute position immediately
    }

    // Default implementation
    void UIWidget::OnUpdate(Timestep ts)
    {
        for (auto& child : m_Children) child->OnUpdate(ts);
    }

    void UIWidget::OnRender() 
    {
        for (auto& child : m_Children) child->OnRender();
    }

    void UIWidget::OnEvent(Event& e)
    {
        for (auto& child : m_Children) child->OnEvent(e);
    }

    void UIWidget::RecalculateTransform()
    {
        if (m_Parent)
            AbsolutePosition = m_Parent->AbsolutePosition + Position;
        else   
            AbsolutePosition = Position; // Root node
        
        for (auto& child : m_Children)
            child->RecalculateTransform();
    }

    bool UIWidget::IsPointInside(const Vector2& point) const
    {
        return point.x >= AbsolutePosition.x && point.x <= AbsolutePosition.x + Size.x &&
               point.y >= AbsolutePosition.y && point.y <= AbsolutePosition.y + Size.y;
    }

}