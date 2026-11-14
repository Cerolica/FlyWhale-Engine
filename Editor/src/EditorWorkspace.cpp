#include "fwpch.h"
#include "EditorWorkspace.h"

namespace FlyWhale
{

    void EditorWorkspace::Build(EditorContext& context, 
                                const Ref<Framebuffer>& sceneFramebuffer,
                                uint32_t width,
                                uint32_t height)
    {
        m_Context = &context;
        m_Canvas = CreateRef<UI::Canvas>(width, height);

        auto editorRoot = CreateRef<UI::Widget>("EditorRoot");
        editorRoot->SetAnchor(UI::AnchorPreset::Stretch); 

        auto mainSplit = CreateRef<UI::SplitContainer>("SidebarViewportSplit");
        mainSplit->SetAnchor(UI::AnchorPreset::Stretch);
        mainSplit->Vertical = false;
        mainSplit->SetSplitOffset(0.25f);
        mainSplit->SetMinimumPaneSizes(200.0f, 120.0f);

        auto sidebar = CreateRef<UI::Panel>("Sidebar");
        sidebar->SetAnchor(UI::AnchorPreset::Stretch);

        m_Viewport = CreateRef<UI::Viewport>(sceneFramebuffer);
        m_Viewport->SetAnchor(UI::AnchorPreset::Stretch);

        mainSplit->AddChild(sidebar);
        mainSplit->AddChild(m_Viewport);
        editorRoot->AddChild(mainSplit);

        m_Canvas->SetRootWidget(editorRoot);
    }

    void EditorWorkspace::OnResize(uint32_t width, uint32_t height)
    {
        if (m_Canvas)
            m_Canvas->OnResize(width, height);
    }

    void EditorWorkspace::OnUpdate(Timestep ts)
    {
        if (m_Canvas)
            m_Canvas->OnUpdate(ts);
    }

    void EditorWorkspace::OnRender()
    {
        if (m_Canvas)
            m_Canvas->OnRender();
    }

    void EditorWorkspace::OnEvent(Event& e)
    {
        if (m_Canvas)
            m_Canvas->OnEvent(e);
    }

}