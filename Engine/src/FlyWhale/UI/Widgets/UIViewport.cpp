#include "fwpch.h"
#include "UIViewport.h"

namespace FlyWhale::UI
{

    void Viewport::OnUpdate(Timestep ts) 
    {
        Widget::OnUpdate(ts);
    }   

    void Viewport::OnRender() 
    {
        Ref<Texture2D> texture = m_Framebuffer->GetColorAttachmentTexture2D();

        // IMPORTANT: OpenGL textures are rendered upside down in UI space. 
        // Must pass custom UVs (or a negative scale/rotation) to flip it right-side up.
        const Vector2 uvs[4] = { {0, 0}, {1, 0}, {1, 1}, {0, 1} };

        const Vector3 center
        {
            m_AbsolutePosition.x + m_Size.x * 0.5f,
            m_AbsolutePosition.y + m_Size.y * 0.5f,
            0.0f
        };

        Renderer2D::DrawQuad(center, m_Size, texture, uvs);

        Widget::OnRender();
    }

    Vector2 Viewport::GetLocalMousePosition(const Vector2& osMousePos) const {
        // Converts global OS mouse coordinates to local 0,0 (top-left of viewport)
        return { osMousePos.x - m_AbsolutePosition.x, osMousePos.y - m_AbsolutePosition.y };
    }

}