#pragma once
#include "FlyWhale/UI/Core/UIWidget.h"
#include "FlyWhale/Renderer/Renderer2D.h"
#include <functional>

#include "FlyWhale/Events/MouseEvent.h"

namespace FlyWhale::UI
{

    class Button : public Widget
    {
    public:
        Button() = default;

        virtual void OnUpdate(Timestep ts) override;
        virtual void OnRender() override;
        virtual void OnEvent(Event& e) override;

        // Callback for when the button is clicked
        std::function<void()> OnClick;

        Vector4 NormalColor = {0.3f, 0.3f, 0.3f, 1.0f};
        Vector4 HoverColor  = {0.4f, 0.4f, 0.4f, 1.0f};
        Vector4 PressColor  = {0.2f, 0.2f, 0.2f, 1.0f};
    
    private:
        bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
        bool OnMouseMoved(MouseMovedEvent& e);

        enum class ButtonState { Normal, Hovered, Pressed };
        ButtonState m_State = ButtonState::Normal;
    };
}