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

        template<typename T, typename... Args>
        T* AddchildT(Args&&... args)
        {
            Ref<T> child = CreateRef<T>(std::forward<Args>(args)...);
            AddChild(child);
            return child.get();
        }

        // Core loop
        virtual void OnUpdate(Timestep ts);
        virtual void OnRender();
        virtual void OnEvent(Event& e);


        // Getter/Setter
        // -------------

        const std::string& GetName() const { return m_Name; }
        Widget* SetName(const std::string& name) { m_Name = name; return this; }

        const AnchorPreset GetAnchor() const { return m_AnchorPreset; }
        Widget* SetAnchor(AnchorPreset preset);
        
        Widget* SetAnchorPoint(const AnchorPoint& point);

        const Rect& GetRect() const { return m_Rect; }
        void SetRect(const Rect& rect) { m_Rect = rect; }
        void SetRectMax(const Vector2& max) { m_Rect.max = max; }
        void SetRectMin(const Vector2& min) { m_Rect.min = min; }

        const Vector2& GetPosition() const { return m_Position; }
        void SetPosition(const Vector2& position)
        {
            m_Position = position;
            
            MarkTransformDirty();
        }

        const Vector2& GetSize() const {  return m_Size; }
        void SetSize(const Vector2& size) { m_Size = size; MarkLayoutDirty(); }
        void SetSizeX(float x) { SetSize({ x, m_Size.y }); }
        void SetSizeY(float y) { SetSize({ m_Size.x, y }); }

        const Vector2& GetAbsolutePosition() const { return m_AbsolutePosition; }

        const Vector2& GetMiniumSize() const { return m_MiniumSize; }
        const float GetMiniumSizeX() const { return m_MiniumSize.x; }
        const float GetMiniumSizeY() const { return m_MiniumSize.y; }
        Widget* SetMiniumSize(const Vector2& size) { m_MiniumSize = size; MarkLayoutDirty(); return this; }
        Widget* SetMiniumSizeX(float sizeX) { m_MiniumSize.x = sizeX; MarkLayoutDirty(); return this; }
        Widget* SetMiniumSizeY(float sizeY) { m_MiniumSize.y = sizeY; MarkLayoutDirty(); return this; }


    protected:
        // Helper for Hit-Testing
        bool IsPointInside(const Vector2& point) const;
        void CalculateAnchorOffset();

        // Recalculates AbsolutePosition based on Parent's AbsolutePosition
        virtual void UpdateLayout(const Rect& parentRect);
        virtual void UpdateTransform(const Matrix4& parentTransform);

        virtual Rect GetChildLayoutArea(size_t childIndex) const
        {
            (void)childIndex;
            return m_Rect;
        }

        void MarkLayoutDirtyLocal()
        {
            m_LayoutDirty = true;
            m_TransformDirty = true;
        }

        void MarkLayoutDirty()
        {
            MarkLayoutDirtyLocal();
            if (m_Parent) m_Parent->MarkLayoutDirty();
        }

        void MarkTransformDirtyLocal()
        {
            m_TransformDirty = true;
        }

        void MarkTransformDirty()
        {
            MarkTransformDirtyLocal();
            if (m_Parent) m_Parent->MarkTransformDirty();
        }
    private:
        void ProcessUpdate(const Rect& parentRect, const Matrix4& parentTransform);

    protected:
        std::string m_Name = "";  
        
        // Layout
        // ------
        bool m_LayoutDirty = true;
        bool m_TransformDirty = true;

        Vector2 m_MiniumSize = { 0.0f, 0.0f };

        AnchorPreset m_AnchorPreset = AnchorPreset::BottomLeft;
        AnchorPoint m_AnchorPoint = { 0.0f, 0.0f, 0.0f, 0.0f};
        AnchorOffset m_AnchorOffset = { 0, 0, 0, 0};

        Rect m_Rect{ {0.0f, 0.0f}, {0.0f, 0.0f} };

        Vector2 m_Position = { 0.0f, 0.0f };
        Vector2 m_AbsolutePosition = { 0.0f, 0.0f }; // Screen coordinates

        Vector2 m_Size = { 0.0f, 0.0f };

        std::vector<Ref<Widget>> m_Children;
        Widget* m_Parent = nullptr;

        friend class Canvas;
    };
}