#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "FlyWhale/Log.h"

namespace FlyWhale
{

    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle)
    {
        FW_CORE_ASSERT(windowHandle, "Window handle is null!");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        FW_CORE_ASSERT(status, "Failed to initialize Glad!");

        FW_CORE_INFO("OpenGL Info:");
        FW_CORE_INFO("  Vendor:  {0}", (const char*)glGetString(GL_VENDOR));
        FW_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
        FW_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }
}