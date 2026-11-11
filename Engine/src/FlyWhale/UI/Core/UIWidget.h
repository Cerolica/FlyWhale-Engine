#pragma once

#include "FlyWhale/Core/Timestep.h"
#include "FlyWhale/Events/Event.h"
#include "FlyWhale/Math/Math.h"

#include "FlyWhale/UI/Layout/UIAnchor.h"

namespace FlyWhale::UI
{

    struct Rect
    {
        Vector2 min;
        Vector2 max;

        Vector2 Size() const { return max - min; };
        float SizeX() const { return max.x - min.x; };
        float SizeY() const { return max.y - min.y; };
    };

    class Widget
    {
    public:
        Widget() = default;
        Widget(const std::string& name)
            : m_Name(name) {}
        virtual ~Widget() = default;

        void AddChild(Ref<Widget> child);

        // Core loop
        virtual void OnUpdate(Timestep ts);
        virtual void OnRender();
        virtual void OnEvent(Event& e);

        // Recalculates AbsolutePosition based on Parent's AbsolutePosition
        virtual void RecalculateTransform();

        virtual void LayoutIn(const Rect& parentRect);

        const std::string& GetName() const { return m_Name; }
        void SetName(const std::string& name)
        {
            m_Name = name;
        }

        const Anchor GetAnchor() const { return m_Anchor; }
        void SetAnchor(Anchor anchor);        

        const Rect& GetRect() const { return m_Rect; }
        void SetRect(const Rect& rect)
        {
            m_Rect = rect;
        }
        void SetRectMax(const Vector2& max)
        {
            m_Rect.max = max;
        }
        void SetRectMin(const Vector2& min)
        {
            m_Rect.min = min;
        }

        const Vector2& GetPosition() const { return m_Position; }
        void SetPosition(const Vector2& position)
        {
            m_Position = position;
            
            m_FlagDirty = true;
        }

        const Vector2& GetSize() const {  return m_Size; }
        void SetSize(const Vector2& size)
        {
            m_Size = size;

            m_FlagDirty = true;
        }
        void SetSizeX(float x) { SetSize({ x, m_Size.y }); }
        void SetSizeY(float y) { SetSize({ m_Size.x, y }); }

        const Vector4& GetMargin() const { return m_Margin; }
        void SetMargin(const Vector4& margin)
        {
            m_Margin = margin;
            m_FlagDirty = true;
        }

        const Vector2& GetAbsolutePosition() const { return m_AbsolutePosition; }

        const Vector2& GetMiniumSize() const { return m_MiniumSize; }
        const float GetMiniumSizeX() const { return m_MiniumSize.x; }
        const float GetMiniumSizeY() const { return m_MiniumSize.y; }
        void SetMiniumSize(const Vector2& size) { m_MiniumSize = size; CalculateAnchorOffset(); }
        void SetMiniumSizeX(float sizeX) { m_MiniumSize.x = sizeX; CalculateAnchorOffset(); }
        void SetMiniumSizeY(float sizeY) { m_MiniumSize.y = sizeY; CalculateAnchorOffset(); }


    protected:
        // Helper for Hit-Testing
        bool IsPointInside(const Vector2& point) const;
        void CalculateAnchorOffset();
    protected:
        std::string m_Name = "";    

        Anchor m_Anchor = Anchor::BottomLeft;
        AnchorPoint m_AnchorPoint = { 0.0f, 0.0f, 0.0f, 0.0f};
        AnchorOffset m_AnchorOffset = { 0, 0, 0, 0};

        Rect m_Rect{ {0.0f, 0.0f}, {0.0f, 0.0f} };

        Vector2 m_Position = { 0.0f, 0.0f };
        Vector2 m_AbsolutePosition = { 0.0f, 0.0f }; // Screen coordinates

        Vector2 m_MiniumSize = { 0.0f, 0.0f };
        Vector2 m_Size = { 100.0f, 100.0f };

        Vector4 m_Margin = { 0.0f,  0.0f, 0.0f, 0.0f };

        bool m_FlagDirty = false;

        std::vector<Ref<Widget>> m_Children;
        Widget* m_Parent = nullptr;
    };
}