#pragma once
#include <FlyWhale.h>

namespace FlyWhale
{
    struct EditorContext
    {
        Ref<Scene> ActiveScene;
        Entity SelectedEntity;
    };

    class EditorWorkspace
    {
    public:
        //EditorWorkspace() = default;
        void Build(EditorContext& context, 
                   const Ref<Framebuffer>& sceneFramebuffer,
                   uint32_t width,
                   uint32_t height);
        void OnResize(uint32_t width, uint32_t height);
        void OnUpdate(Timestep ts);
        void OnRender();
        void OnEvent(Event& e);

        Vector2 GetViewportSize() const
        {
            return m_Viewport ? m_Viewport->GetSize() : Vector2{ 0.0f, 0.0f };
        }
    private:
        EditorContext* m_Context = nullptr;
        Ref<UI::Canvas> m_Canvas;
        Ref<UI::Viewport> m_Viewport;
    };
}