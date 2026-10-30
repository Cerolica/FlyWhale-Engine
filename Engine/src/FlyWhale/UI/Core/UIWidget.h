#pragma once

#include "FlyWhale/Core/Timestep.h"
#include "FlyWhale/Events/Event.h"
#include "FlyWhale/Math/Math.h"

namespace FlyWhale::UI
{

    class UIWidget
    {
    public:
        UIWidget() = default;
        virtual ~UIWidget() = default;

        void AddChild(Ref<UIWidget> child);

        // Core loop
        virtual void OnUpdate(Timestep ts);
        virtual void OnRender();
        virtual void OnEvent(Event& e);

        // Recalculates AbsolutePosition based on Parent's AbsolutePosition
        virtual void RecalculateTransform();

        Vector2 Position = { 0.0f, 0.0f };
        Vector2 Size = { 100.0f, 100.0f };
        Vector2 AbsolutePosition = { 0.0f, 0.0f }; // Screen coordinates
    protected:
        // Helper for Hit-Testing
        bool IsPointInside(const Vector2& point) const;

        std::vector<Ref<UIWidget>> m_Children;
        UIWidget* m_Parent = nullptr;
    };
}