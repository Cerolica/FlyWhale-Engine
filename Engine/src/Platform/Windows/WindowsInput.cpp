#include "fwpch.h"
#include "FlyWhale/Core/Input.h"

#include "FlyWhale/Core/Application.h"

#include <GLFW/glfw3.h>

namespace FlyWhale
{

    bool Input::IsKeyPressed(int keycode)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressed(int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> Input::GetMousePosition()
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());\
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return std::pair((float)xpos, (float)ypos);
    }

    float Input::GetMouseX()
    {
        auto[x, y] = GetMousePosition();
        return x;
    }

    float Input::GetMouseY()
    {
        auto[x, y] = GetMousePosition();
        return y;
    }
}