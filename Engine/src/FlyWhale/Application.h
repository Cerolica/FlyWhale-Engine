#pragma once

#include "Core.h"

#include "Window.h"
#include "FlyWhale/LayerStack.h"
#include "FlyWhale/Events/Event.h"
#include "FlyWhale/Events/ApplicationEvent.h"

#include "FlyWhale/ImGui/ImGuiLayer.h"

#include "FlyWhale/Renderer/Shader.h"
#include "FlyWhale/Renderer/Buffer.h"
#include "FlyWhale/Renderer/VertexArray.h"

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

        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;

        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<VertexArray> m_VertexArray;

        std::shared_ptr<Shader> m_BlueShader;
        std::shared_ptr<VertexArray> m_SquareVA;
    private:
        static Application* s_Instance;
    };

    // To be defined in CLIENT
    Application* CreateApplication();

}