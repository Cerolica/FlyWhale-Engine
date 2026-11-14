#pragma once

#include "UIWidget.h"
#include "FlyWhale/Renderer/Editor2DCamera.h"
#include "FlyWhale/Renderer/RenderCommand.h"

namespace FlyWhale::UI
{

    class Canvas
    {
    public:
        Canvas() = default;
        Canvas(uint32_t width, uint32_t height);
        virtual ~Canvas() = default;

        void OnResize(uint32_t width, uint32_t height);
        void OnUpdate(Timestep ts);
        void OnRender();
        void OnEvent(Event& e);

        void SetRootWidget(Ref<UI::Widget> widget);

        uint32_t GetCanvasWidth() const { return m_CanvasWidth; }
        uint32_t GetCanvasHeight() const { return m_CanvasHeight; }

    private:
        Ref<Widget> m_RootWidget;
        Editor2DCamera m_UICamera;

        uint32_t m_CanvasWidth, m_CanvasHeight;
    };
}