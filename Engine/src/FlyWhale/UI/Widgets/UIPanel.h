#pragma once
#include "FlyWhale/UI/Core/UIWidget.h"
#include "FlyWhale/Renderer/Renderer2D.h"

namespace FlyWhale::UI
{

    class Panel : public Widget
    {
    public:
        Panel(const Vector4& color = { 0.015625f, 0.1328125f, 0.2265625f, 1.0f })
            : m_Color(color) {}

        Panel(const std::string& name, const Vector4& color = { 0.015625f, 0.1328125f, 0.2265625f, 1.0f })
            : Widget(name), m_Color(color) {}

        virtual void OnRender() override;

        Vector4 GetColor() const { return m_Color; }
    private:
        Vector4 m_Color;
    };
}