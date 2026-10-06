#pragma once

#include "Core.h"

#include "Window.h"
#include "FlyWhale/LayerStack.h"
#include "FlyWhale/Events/Event.h"
#include "FlyWhale/Events/ApplicationEvent.h"

#include "FlyWhale/Core/Timestep.h"

#include "FlyWhale/ImGui/ImGuiLayer.h"

namespace FlyWhale 
{

    class Application 
    {
    public:
        Application();
        virtual ~Application();

        void Run(); // Run the application

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        inline Window& GetWindow() { return *m_Window; }
        

        inline static Application& Get() { return *s_Instance; }
    private:
        bool OnWindowClose(WindowCloseEvent& e);
    private:
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;
        float m_LastFrameTime = 0.0f;
    private:
        static Application* s_Instance;
    };

    // To be defined in CLIENT
    Application* CreateApplication();

}