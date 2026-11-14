#pragma once
#include "UIContainer.h"
#include "FlyWhale/Events/MouseEvent.h"

namespace FlyWhale::UI
{

    class SplitContainer : public Container
    {
    public:
        enum class MinimumMode
        {
            Pixels,
            Ratio
        };
    public:

        SplitContainer(const std::string& name = "SplitContainer")
            : Container(name) {}

        virtual void OnUpdate(Timestep ts) override;
        virtual void OnRender() override;
        virtual void OnEvent(Event& e) override;

        void SetSplitOffset(float offset) 
        { 
            m_SplitOffset = std::clamp(offset, 0.0f, 1.0f); 
            MarkLayoutDirty(); 
        };
        float GetSplitOffset() const { return m_SplitOffset; }

        void SetMinimumPaneSizes(float first, float second)
        {
            m_MinimumMode = MinimumMode::Pixels;
            m_FirstMinimum = std::max(0.0f, first);
            m_SecondMinimum = std::max(0.0f, second);
            MarkLayoutDirty();
        }

        bool SetMinimumPaneRatios(float first, float second)
        {
            if (!std::isfinite(first) || !std::isfinite(second) ||
                first < 0.0f || second < 0.0f ||
                first > 1.0f || second > 1.0f ||
                first + second > 1.0f)
            {
                return false;
            }

            m_MinimumMode = MinimumMode::Ratio;
            m_FirstMinimum = first;
            m_SecondMinimum = second;
            MarkLayoutDirty();
            return true;
        }
    public:
        // If true, order child vertically, else horizontally
        bool Vertical = false;
    protected:
        virtual void UpdateLayout(const Rect& parentRect) override;
        //virtual void UpdateTransform(const Matrix4& parentTransform) override;

        virtual Rect GetChildLayoutArea(size_t childIndex) const override;
    private:
        float GetSplitPosition() const;
        bool IsMouseOverGrabber(const Vector2& mousePos) const;
    private:
        float m_SplitOffset = 0.5f;
        float m_GrabberThickness = 8.0f;
        float m_FirstMinimum = 10.0f;
        float m_SecondMinimum = 10.0f;

        MinimumMode m_MinimumMode = MinimumMode::Pixels;

        bool m_IsDragging = false;
    };
}