#include "fwpch.h"
#include "UIPanel.h"

namespace FlyWhale::UI
{

    void Panel::OnRender()
    {

        //FW_CORE_WARN("Draw Position(Center): {0}, {1}", m_AbsolutePosition.x + m_Size.x / 2.0f, m_AbsolutePosition.y + m_Size.y / 2.0f);
        Renderer2D::DrawQuad({ m_AbsolutePosition.x + m_Size.x / 2.0f, m_AbsolutePosition.y + m_Size.y / 2.0f, 0.0f }, m_Size, m_Color);

        // Draw children on top
        Widget::OnRender();
    }
}