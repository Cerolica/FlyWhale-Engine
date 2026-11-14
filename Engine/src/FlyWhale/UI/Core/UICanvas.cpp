#include "fwpch.h"
#include "UICanvas.h"

#include "FlyWhale/UI/Widgets/UIButton.h"
#include "FlyWhale/UI/Widgets/UIContainer.h"
#include "FlyWhale/UI/Widgets/UILabel.h"
#include "FlyWhale/UI/Widgets/UIPanel.h"
#include "FlyWhale/UI/Widgets/UIViewport.h"

namespace FlyWhale::UI
{

    Canvas::Canvas(uint32_t width, uint32_t height)
        : m_UICamera(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f),
          m_CanvasWidth(width), m_CanvasHeight(height)
    {
    }

    void Canvas::OnResize(uint32_t width, uint32_t height)
    {
        FW_CORE_WARN("Canvas Resize: {0}, {1}", width, height);

        m_CanvasWidth = width;
        m_CanvasHeight = height;

        m_UICamera.SetProjection(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f);
        m_RootWidget->SetMiniumSize({ width, height});
        m_RootWidget->SetSize({width, height});
    }

    void Canvas::OnUpdate(Timestep ts)
    {
        if (m_RootWidget->m_LayoutDirty || m_RootWidget->m_TransformDirty)
        {
            m_RootWidget->ProcessUpdate({ 
                { 0.0f, 0.0f },
                { static_cast<float>(m_CanvasWidth), static_cast<float>(m_CanvasHeight) } },
                Matrix4(1.0f));
        }
        
        m_RootWidget->OnUpdate(ts);
    }

    void Canvas::OnRender()
    {
        Renderer2D::BeginScene(m_UICamera);

        RenderCommand::SetViewport(0, 0, m_CanvasWidth, m_CanvasHeight);
        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.5f, 1.0f });
        RenderCommand::Clear();
        
        m_RootWidget->OnRender();

        Renderer2D::EndScene();
    }

    void Canvas::OnEvent(Event& e)
    {
        m_RootWidget->OnEvent(e);
    }

    void Canvas::SetRootWidget(Ref<UI::Widget> widget)
    {
        m_RootWidget = widget;
        m_RootWidget->ProcessUpdate({ { 0, 0 }, { m_CanvasWidth, m_CanvasHeight } }, Matrix4(1.0f));
    }

}