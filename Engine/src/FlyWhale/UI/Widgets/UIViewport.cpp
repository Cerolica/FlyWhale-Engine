#include "fwpch.h"
#include "UIViewport.h"

namespace FlyWhale::UI
{

    void Viewport::OnUpdate(Timestep ts) 
    {
        auto spec = m_Framebuffer->GetSpecification();
        if (m_Size.x > 0.0f && m_Size.y > 0.0f &&
            (spec.Width != m_Size.x || spec.Height != m_Size.y))
        {
            m_Framebuffer->Resize((uint32_t)m_Size.x, (uint32_t)m_Size.y);
            // TODO: Notify the scene/camera that aspect ratio changed
        }

        Widget::OnUpdate(ts);
    }   

    void Viewport::OnRender() 
    {
        Ref<Texture2D> texture = m_Framebuffer->GetColorAttachmentTexture2D();

        // IMPORTANT: OpenGL textures are rendered upside down in UI space. 
        // Must pass custom UVs (or a negative scale/rotation) to flip it right-side up.
        Vector2 uvs[4] = { {0, 0}, {1, 0}, {1, 1}, {0, 1} };

        Renderer2D::DrawQuad(m_AbsolutePosition, m_Size, texture, uvs);

        Widget::OnRender();
    }

    Vector2 Viewport::GetLocalMousePosition(const Vector2& osMousePos) const {
        // Converts global OS mouse coordinates to local 0,0 (top-left of viewport)
        return { osMousePos.x - m_AbsolutePosition.x, osMousePos.y - m_AbsolutePosition.y };
    }

}