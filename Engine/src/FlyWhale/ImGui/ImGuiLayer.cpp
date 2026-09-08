#include "ImGuiLayer.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

#include <GLFW/glfw3.h>

#include "FlyWhale/Application.h"

namespace FlyWhale
{
    static ImGuiKey GlfwKeyToImGuiKey(int keycode)
    {
        switch (keycode)
        {
            case GLFW_KEY_TAB:         return ImGuiKey_Tab;
            case GLFW_KEY_LEFT:        return ImGuiKey_LeftArrow;
            case GLFW_KEY_RIGHT:       return ImGuiKey_RightArrow;
            case GLFW_KEY_UP:          return ImGuiKey_UpArrow;
            case GLFW_KEY_DOWN:        return ImGuiKey_DownArrow;
            case GLFW_KEY_PAGE_UP:     return ImGuiKey_PageUp;
            case GLFW_KEY_PAGE_DOWN:   return ImGuiKey_PageDown;
            case GLFW_KEY_HOME:        return ImGuiKey_Home;
            case GLFW_KEY_END:         return ImGuiKey_End;
            case GLFW_KEY_INSERT:      return ImGuiKey_Insert;
            case GLFW_KEY_DELETE:      return ImGuiKey_Delete;
            case GLFW_KEY_BACKSPACE:   return ImGuiKey_Backspace;
            case GLFW_KEY_SPACE:       return ImGuiKey_Space;
            case GLFW_KEY_ENTER:       return ImGuiKey_Enter;
            case GLFW_KEY_ESCAPE:      return ImGuiKey_Escape;
            case GLFW_KEY_A:           return ImGuiKey_A;
            case GLFW_KEY_C:           return ImGuiKey_C;
            case GLFW_KEY_V:           return ImGuiKey_V;
            case GLFW_KEY_X:           return ImGuiKey_X;
            case GLFW_KEY_Y:           return ImGuiKey_Y;
            case GLFW_KEY_Z:           return ImGuiKey_Z;
            default:                   return ImGuiKey_None;
        }
    }

    ImGuiLayer::ImGuiLayer() 
        : Layer("ImGuiLayer") {}

    ImGuiLayer::~ImGuiLayer() {}

    void ImGuiLayer::OnAttach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        Application& app = Application::Get();
        GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
        ImGui_ImplGlfw_InitForOpenGL(window, true); // 'false' because we handle events manually

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach()
    {

    }

    void ImGuiLayer::OnUpdate() 
    {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        float time = (float)glfwGetTime();
        io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
        m_Time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(Event& event)
    {

    }
}