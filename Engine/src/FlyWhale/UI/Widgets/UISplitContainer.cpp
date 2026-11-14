#include "fwpch.h"
#include "UISplitContainer.h"

#include "FlyWhale/Core/Input.h"
#include "FlyWhale/Core/Application.h"

#include "FlyWhale/Renderer/Renderer2D.h"


namespace FlyWhale::UI
{

    void SplitContainer::OnUpdate(Timestep ts) 
    {
        Widget::OnUpdate(ts);
    }

    void SplitContainer::OnRender() 
    {
        Widget::OnRender();

        // Draw divider(for some visual effect etc etc)
        const Vector3 center = Vertical
            ? Vector3
            {
                m_AbsolutePosition.x + m_Size.x * 0.5,
                m_AbsolutePosition.y + GetSplitPosition(),
                0.0f
            } 
            : Vector3
            {
                m_AbsolutePosition.x + GetSplitPosition(),
                m_AbsolutePosition.y + m_Size.y * 0.5f,
                0.0f
            };
        
        const Vector2 size = Vertical
            ? Vector2{ m_Size.x, m_GrabberThickness }
            : Vector2{ m_GrabberThickness, m_Size.y };
        
        Renderer2D::DrawQuad(center, size, Vector4{ 0.22f, 0.22f, 0.22f, 1.0f });

    }

    void SplitContainer::OnEvent(Event& e) 
    {
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<MouseButtonPressedEvent>([this](MouseButtonPressedEvent& e) 
        {
            // Might add posx and posy for mouse button event(or not)
            const Vector2 mousePos = { Input::GetMouseX(), Input::GetMouseY() };
            if (e.GetMouseButton() == FW_MOUSE_BUTTON_LEFT && IsMouseOverGrabber(mousePos))
            {
                m_IsDragging = true;
                return true; // Consume the event(very delicious!)
            }

            return false;
        });

        dispatcher.Dispatch<MouseButtonReleasedEvent>([this](MouseButtonReleasedEvent& e) 
        {
            if (e.GetMouseButton() == FW_MOUSE_BUTTON_LEFT)
            {
                m_IsDragging = false;
                return true;
            }
            
            return false;
        });

        dispatcher.Dispatch<MouseMovedEvent>([this](MouseMovedEvent& e) 
        {
            const Vector2 mousePos = { e.GetX(), e.GetY() };

            if (IsMouseOverGrabber(mousePos))
            {
                Application::Get().GetWindow().SetCursor(
                    Vertical ? CursorType::VResize : CursorType::HResize);
            }
            else
            {
                Application::Get().GetWindow().SetCursor(CursorType::Arrow);
            }

            if (m_IsDragging)
            {
                const float extent = Vertical? m_Size.y : m_Size.x;
                if (extent > 0.0f)
                {
                    const float localPosition = Vertical ?
                        e.GetY() - m_AbsolutePosition.y :
                        e.GetX() - m_AbsolutePosition.x;
                    
                    SetSplitOffset(localPosition / extent);
                }
                MarkLayoutDirty();
                return true;
            }

            return false;
        });

        if (!e.Handled)
            Widget::OnEvent(e);
    }

    void SplitContainer::UpdateLayout(const Rect& parentRect)
    {
        Widget::UpdateLayout(parentRect);
    }

    Rect SplitContainer::GetChildLayoutArea(size_t childIndex) const 
    {
        // Currently only support having 2 children(average family plan in Vietnam)
        if (childIndex > 1) return m_Rect;

        const float extent = Vertical ? m_Size.y : m_Size.x;
        const float grabber = std::min(m_GrabberThickness, extent);
        const float splitPosition = GetSplitPosition();

        if (!Vertical)
        {
            const float dividerX = m_Rect.min.x + splitPosition;

            if (childIndex == 0)
            {
                return { m_Rect.min, { dividerX - grabber * 0.5f, m_Rect.max.y } };
            }
            else
            {
                return { { dividerX + grabber * 0.5f, m_Rect.min.y }, m_Rect.max };
            }
        }
        else
        {
            const float dividerY = m_Rect.min.y + splitPosition;

            if (childIndex == 0)
            {
                return { m_Rect.min, { m_Rect.max.x, dividerY - grabber * 0.5f } };
            }
            else
            {
                return { { m_Rect.min.x, dividerY + grabber * 0.5f }, m_Rect.max };
            }
        }
    }

    float SplitContainer::GetSplitPosition() const
    {
        const float extent = Vertical ? m_Size.y : m_Size.x;
        if (extent <= 0.0f) return 0.0f;
        
        const float grabber = std::min(m_GrabberThickness, extent);
        const float paneSpace = std::max(0.0f, extent - grabber);

        float firstMinimum = 0.0f;
        float secondMinimum = 0.0f;

        if (m_MinimumMode == MinimumMode::Ratio)
        {
            // The minimum shrink with the available window size.
            firstMinimum = m_FirstMinimum * paneSpace;
            secondMinimum = m_SecondMinimum * paneSpace;
        }
        else
        {
            // Preserve the requested pixel ratio when there isn't enough room
            // for both. At normal sizes, scale is 1 and these remain pixel minima.
            const float requestedTotal = m_FirstMinimum + m_SecondMinimum;
            const float scale = requestedTotal > paneSpace && requestedTotal > 0.0f
                ? paneSpace / requestedTotal
                : 1.0f;

            firstMinimum = m_FirstMinimum * scale;
            secondMinimum = m_SecondMinimum * scale;
        }

        const float minCenter = firstMinimum + grabber * 0.5f;
        const float maxCenter = extent - secondMinimum - grabber * 0.5f;

        // Nothing too complicated if you know what I mean(idk what I mean)
        return std::clamp(extent * m_SplitOffset, minCenter, std::max(minCenter, maxCenter));
    }
    
    bool SplitContainer::IsMouseOverGrabber(const Vector2& mousePos) const
    {
        const float splitPosition = GetSplitPosition();

        if (!Vertical)
        {
            const float dividerX = m_AbsolutePosition.x + splitPosition;
            return mousePos.x >= dividerX - (m_GrabberThickness / 2.0f) &&
                   mousePos.x <= dividerX + (m_GrabberThickness / 2.0f) &&
                   mousePos.y >= m_AbsolutePosition.y &&
                   mousePos.y <= m_AbsolutePosition.y + m_Size.y;
        }
        else
        {
            const float dividerY = m_AbsolutePosition.y + splitPosition;
            return mousePos.y >= dividerY - (m_GrabberThickness / 2.0f) &&
                   mousePos.y <= dividerY + (m_GrabberThickness / 2.0f) &&
                   mousePos.x >= m_AbsolutePosition.x &&
                   mousePos.x <= m_AbsolutePosition.x + m_Size.x;
        }
    }
}