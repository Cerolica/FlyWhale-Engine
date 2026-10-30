#pragma once

#include "FlyWhale/Core/Core.h"

#include "FlyWhale/Core/Window.h"
#include "FlyWhale/Core/LayerStack.h"
#include "FlyWhale/Events/Event.h"
#include "FlyWhale/Events/ApplicationEvent.h"

#include "FlyWhale/Core/Timestep.h"

#include "FlyWhale/ImGui/ImGuiLayer.h"

namespace FlyWhale 
{

    enum class UIMode
    {
        ImGuiEditor, 
        CustomEditor,
        GameRuntime
    };

    class Application 
    {
    public:
        Application(const std::string& name = "FlyWhale App");
        virtual ~Application();

        void Run(); // Run the application

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        inline Window& GetWindow() { return *m_Window; }
        
        void Close();

        inline static Application& Get() { return *s_Instance; }
    private:
        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);
    private:
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        bool m_Minimized = false;
        LayerStack m_LayerStack;
        float m_LastFrameTime = 0.0f;

        UIMode m_CurrentUIMode = UIMode::ImGuiEditor;
    private:
        static Application* s_Instance;
    };

    // To be defined in CLIENT
    Application* CreateApplication();

}