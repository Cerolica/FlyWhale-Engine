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

        virtual void OnUpdate(Timestep ts);
        virtual void OnRender();
        virtual void OnEvent(Event& e);

        Vector2 Position = { 0.0f, 0.0f };
        Vector2 Size = { 100.0f, 100.0f };
    protected:
        std::vector<Ref<UIWidget>> m_Children;
        UIWidget* m_Parent = nullptr;
    };
}