#pragma once

#include "FlyWhale/Core.h"
#include "FlyWhale/Log.h"
#include "FlyWhale/Window.h"

#include <GLFW/glfw3.h>

namespace FlyWhale 
{

    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        inline unsigned int GetWidth() const override { return m_Data.Width; }
        inline unsigned int GetHeight() const override { return m_Data.Height; }

        // Window attributes
        inline void SetEventCallback(const EventCallbackFn& callback) override 
        {
            m_Data.EventCallback = callback;
        }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        inline virtual void* GetNativeWindow() const { return m_Window; }
    private: // For functions 
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();
    private: // For datas
        GLFWwindow* m_Window;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };
}