#include "fwpch.h"
#include "UIButton.h"

namespace FlyWhale::UI
{

    void Button::OnUpdate(Timestep ts)
    {
        Widget::OnUpdate(ts);
    }

    void Button::OnRender() 
    {
        Vector4 currentColor = NormalColor;
        if (m_State == ButtonState::Hovered) currentColor = HoverColor;
        if (m_State == ButtonState::Pressed) currentColor = PressColor;

        Renderer2D::DrawQuad({ GetAbsolutePosition() }, GetSize(), currentColor);

        Widget::OnRender();
    }

    void Button::OnEvent(Event& e) 
    {
        // Let children handle event first(button in button kind of stuff)
        Widget::OnEvent(e);
        if (e.Handled) return;

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseButtonPressedEvent>(FW_BIND_EVENT_FN(Button::OnMouseButtonPressed));
        dispatcher.Dispatch<MouseMovedEvent>(FW_BIND_EVENT_FN(Button::OnMouseMoved));
    }

    bool Button::OnMouseButtonPressed(MouseButtonPressedEvent& e) 
    {
        if (m_State == ButtonState::Hovered)
        {
            m_State = ButtonState::Pressed;

            if (OnClick)
                OnClick(); // Execute user code
            
            return true;
        }

        return false;
    }

    bool Button::OnMouseMoved(MouseMovedEvent& e) 
    {
        if (IsPointInside({ e.GetX(), e.GetY() }))
        {
            if (m_State != ButtonState::Pressed) m_State = ButtonState::Hovered;
        } 
        else m_State = ButtonState::Normal;

        return false;
    }


}