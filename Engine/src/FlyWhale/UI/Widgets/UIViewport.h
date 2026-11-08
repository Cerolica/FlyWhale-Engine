#pragma once
#include "FlyWhale/UI/Core/UIWidget.h"
#include "FlyWhale/Renderer/Framebuffer.h"
#include "FlyWhale/Renderer/Renderer2D.h"

namespace FlyWhale::UI
{

    class Viewport : public Widget
    {
    public:
        Viewport(Ref<Framebuffer> framebuffer)
            : m_Framebuffer(framebuffer)
        {
        }

        virtual void OnUpdate(Timestep ts) override;
        virtual void OnRender() override;

        // Helper to get local mouse coordinates for scene picking
        Vector2 GetLocalMousePosition(const Vector2& osMousePos) const;

    private:
        Ref<Framebuffer> m_Framebuffer;

    };
}