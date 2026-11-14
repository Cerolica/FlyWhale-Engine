#pragma once

#include "FlyWhale/Core/Core.h"
#include "FlyWhale/Events/Event.h"
#include "FlyWhale/Core/Timestep.h"

namespace FlyWhale
{

    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep ts) {}
        virtual void OnRenderUI() {}
        virtual void OnEvent(Event& e) {}

        inline const std::string& GetName() const { return m_DebugName; }
    protected:
        std::string m_DebugName;
    };
}