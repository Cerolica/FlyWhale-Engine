#pragma once

#include "FlyWhale/Core/Core.h"
#include "FlyWhale/Core/Log.h"
#include "FlyWhale/Core/Window.h"
#include "FlyWhale/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>


namespace FlyWhale 
{

    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        void SetSizeLimits(int minWidth, int minHeight, int maxWidth, int maxHeight) override;
        inline uint32_t GetWidth() const override { return m_Data.Width; }
        inline uint32_t GetHeight() const override { return m_Data.Height; }

        // Window attributes
        inline void SetEventCallback(const EventCallbackFn& callback) override 
        {
            m_Data.EventCallback = callback;
        }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        virtual void SetCursor(CursorType type) override;

        inline virtual void* GetNativeWindow() const { return m_Window; }
    private: // For functions 
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();
    private: // For datas
        GLFWwindow* m_Window;
        GraphicsContext*  m_Context;

        std::array<GLFWcursor*, (size_t)CursorType::NumCursors> m_Cursors = { nullptr };

        struct WindowData
        {
            std::string Title;
            uint32_t Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };
}