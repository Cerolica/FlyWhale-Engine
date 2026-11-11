#include "CustomEditorLayer.h"

#include <imgui.h>

namespace FlyWhale
    {

    static const uint32_t s_MapWidth = 24;
    static const char* s_MapTiles = "WWWWWWWWWWWWWWWWWWWWWWWW" 
                                    "WWWWWWWDDDDDDWWWWWWWWWWW"
                                    "WWWWWDDDDDDDDDDDWWWWWWWW"
                                    "WWWWDDDDDDDDDDDDDDDWWWWW"
                                    "WWWDDDDDDDDDDDDDDDDDDWWW"
                                    "WWDDDDWWWDDDDDDDDDDDDWWW"
                                    "WDDDDDWWWDDDDDDDDDDDDDWW"
                                    "WWDDDDDDDDDDDDDDDDDDDWWW"
                                    "WWWWDDDDDDDDDDDDDDDDWWWW"
                                    "WWWWWDDDDDDDDDDDDDDWWWWW"
                                    "WWWWWWDDDDDDDDDDDWWWWWWW"
                                    "WWWWWWWDDDDDDDDDWWWWWWWW"
                                    "WWWWWWWWWWDDDDWWWWWWWWWW"
                                    "WWWWWWWWWWWWWWWWWWWWWWWW";

    CustomEditorLayer::CustomEditorLayer()
        : Layer("CustomEditorLayer"), m_CameraController(1280.0f / 720.0f, true)
    {

    }

    void CustomEditorLayer::OnAttach() 
    {
        FW_PROFILE_FUNCTION();

        m_CheckerboardTexture = Texture2D::Create("assets/textures/Checkerboard.png");
        m_SpriteSheet = Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");

        m_TextureStairs = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 0, 11 }, { 128, 128 });
        m_TextureTree = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 1 }, { 128, 128 }, { 1, 2 });
        
        m_MapWidth = s_MapWidth;
        m_MapHeight = strlen(s_MapTiles) / m_MapWidth;
        s_TextureMap['D'] = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 6, 11 }, { 128, 128 });
        s_TextureMap['W'] = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 11, 11 }, { 128, 128 });

        m_CameraController.SetZoomLevel(5.0f);

        FramebufferSpecification fbSpec;
        fbSpec.Width = 1280;
        fbSpec.Height = 720;
        m_Framebuffer = Framebuffer::Create(fbSpec);

        auto& window = Application::Get().GetWindow();

        if (!m_UseImGui)
        {   
            m_CustomEditorCamera.SetProjection(0, window.GetWidth(), 0, window.GetHeight());

            m_RootUIWidget = CreateRef<UI::Widget>();
        
            m_RootUIWidget->SetMiniumSize({ window.GetWidth(), window.GetHeight() });
            m_RootUIWidget->SetAnchor(UI::Anchor::BottomLeft); 

            Ref<UI::Panel> panel = CreateRef<UI::Panel>("Panel");
            panel->SetMiniumSize({ 128.0f, 128.0f });
            panel->SetAnchor(UI::Anchor::TopLeft);
            m_RootUIWidget->AddChild(panel);

            Ref<UI::Panel> panel2 = CreateRef<UI::Panel>("Panel 2");
            panel2->SetMiniumSize({ 128.0f, 128.0f });
            panel2->SetAnchor(UI::Anchor::TopCenter);
            m_RootUIWidget->AddChild(panel2);

            Ref<UI::Panel> panel3 = CreateRef<UI::Panel>("Panel 3");
            panel3->SetMiniumSize({ 128.0f, 128.0f });
            panel3->SetAnchor(UI::Anchor::TopRight);
            m_RootUIWidget->AddChild(panel3);

            Ref<UI::Panel> panel4 = CreateRef<UI::Panel>("Panel 4");
            panel4->SetMiniumSize({ 128.0f, 128.0f });
            panel4->SetAnchor(UI::Anchor::BottomWide);
            m_RootUIWidget->AddChild(panel4);

            m_RootUIWidget->LayoutIn({ { 0.0f, 0.0f }, { window.GetWidth(), window.GetHeight() } });
            m_RootUIWidget->RecalculateTransform();

            FW_CORE_WARN("Root position: {0}, {1}", m_RootUIWidget->GetAbsolutePosition().x, m_RootUIWidget->GetAbsolutePosition().y);
            FW_CORE_WARN("Panel position: {0}, {1}", panel->GetAbsolutePosition().x, panel->GetAbsolutePosition().y);

        }

        // Scene
        // -----
        m_ActiveScene = CreateRef<Scene>();

        auto square = m_ActiveScene->CreateEntity("Green Square");
        square.AddComponent<SpriteRendererComponent>(Vector4{0.0f, 1.0f, 0.0f, 1.0f });
        
        m_SquareEntity = square;

        m_CameraEntity = m_ActiveScene->CreateEntity("Camera Entity");
        m_CameraEntity.AddComponent<CameraComponent>();

        m_SecondCamera = m_ActiveScene->CreateEntity("Clip-Space Entity");
        auto& cc = m_SecondCamera.AddComponent<CameraComponent>();
        cc.Primary = false;

        class CameraController : public ScriptableEntity
        {

        public:
            void OnCreate()
            {
                auto& transform = GetComponent<TransformComponent>().Transform;
                transform[3][0] = rand() % 10 - 5.0f;
            }
            
            void OnDestroy()
            {
            }

            void OnUpdate(Timestep ts)
            {
                auto& transform = GetComponent<TransformComponent>().Transform;
                float speed = 5.0f;

                if (Input::IsKeyPressed(Key::A))
                    transform[3][0] -= speed * ts;
                if (Input::IsKeyPressed(Key::D))
                    transform[3][0] += speed * ts;
                if (Input::IsKeyPressed(Key::W))
                    transform[3][1] += speed * ts;
                if (Input::IsKeyPressed(Key::S))
                    transform[3][1] -= speed * ts;
            }
        };

        m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
        m_SecondCamera.AddComponent<NativeScriptComponent>().Bind<CameraController>();

        m_SceneHierarchyPanel.SetContext(m_ActiveScene);
    }

    void CustomEditorLayer::OnDetach()
    {
        FW_PROFILE_FUNCTION();
    }

    void CustomEditorLayer::OnUpdate(Timestep ts)
    {

        FW_PROFILE_FUNCTION();

        // Update
        // ------
        if (m_ViewportFocused)
            m_CameraController.OnUpdate(ts);
        
        if (!m_UseImGui && m_RootUIWidget)
            m_RootUIWidget->OnUpdate(ts);

        // Render
        // ------
        // Reset stats here
        Renderer2D::ResetStats();

        auto& spec = m_Framebuffer->GetSpecification();
        auto& window = Application::Get().GetWindow();

        if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f &&
            (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
        {
            m_Framebuffer->Resize(m_ViewportSize);
            m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
            m_CustomEditorCamera.SetProjection(0.0f, window.GetWidth(), 0.0f, window.GetHeight());
            m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
        }

        m_Framebuffer->Bind();

        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        RenderCommand::Clear();

        // Update scene
        m_ActiveScene->OnUpdate(ts);

        m_Framebuffer->Unbind();
        
    }

    void CustomEditorLayer::OnUIRender()
    {
        FW_PROFILE_FUNCTION();

        if (m_UseImGui)
            RenderImGui();
        else
            RenderCustomUI();
        
    }

    void CustomEditorLayer::OnEvent(Event& e)
    {
        m_CameraController.OnEvent(e);

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent& e)
        {
            m_RootUIWidget->SetSize({ (float)e.GetWidth(), (float)e.GetHeight() });

            m_RootUIWidget->RecalculateTransform();

            return false;
        });

        if (!m_UseImGui  && m_RootUIWidget)
        {
            m_RootUIWidget->OnEvent(e);
        }
    }

    void CustomEditorLayer::RenderImGui()
    {
        static bool dockspaceOpen = true;
        static bool opt_fullscreen_persistant = true;
        bool opt_fullscreen = opt_fullscreen_persistant;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui :: PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui :: GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                //ImGui :: MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

                if (ImGui::MenuItem("Exit")) Application::Get().Close();
                if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) dockspace_flags ^= ImGuiDockNodeFlags_NoSplit;
                if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) dockspace_flags ^= ImGuiDockNodeFlags_NoResize;
                if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode;
                if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0)) dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode;
                if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar;
                ImGui::Separator();
                if (ImGui::MenuItem("Close DockSpace", NULL, false))
                    dockspaceOpen = false;
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        // Scene hierarchy panel
        // ---------------------
        m_SceneHierarchyPanel.OnUIRender();

        // Setting menu
        // ------------

        ImGui::Begin("Settings");

        auto stats = Renderer2D::GetStats();
        ImGui::Text("Renderer2D Stats:");
        ImGui::Text("Draw Calls: %d", stats.DrawCalls);
        ImGui::Text("Quads: %d", stats.QuadCount);
        ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
        ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

        if (m_SquareEntity) 
        {
            ImGui::Separator();
            ImGui::Text("%s", m_SquareEntity.GetComponent<TagComponent>().Tag.c_str());

            auto& squareColor = m_SquareEntity.GetComponent<SpriteRendererComponent>().Color;
            ImGui::ColorEdit4("Square Color", Math::ValuePtr(squareColor));
        }
        
        ImGui::DragFloat3("Camera transform",
            Math::ValuePtr(m_CameraEntity.GetComponent<TransformComponent>().Transform[3]));

        if (ImGui::Checkbox("Camera A", &m_PrimaryCamera))
        {
            m_CameraEntity.GetComponent<CameraComponent>().Primary = m_PrimaryCamera;
            m_SecondCamera.GetComponent<CameraComponent>().Primary = !m_PrimaryCamera;
        }

        {
            auto& camera = m_SecondCamera.GetComponent<CameraComponent>().Camera;
            float orthoSize = camera.GetOrthographicSize();
            if (ImGui::DragFloat("Second camera ortho size", &orthoSize))
            {
                camera.SetOrthoGraphicSize(orthoSize);
            }
        }
        
        ImGui::End();
    
        // Viewport
        // --------

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("Viewport");

        //FW_CORE_WARN("Focused: {0}", ImGui::IsWindowFocused());
        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();
        Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);
        
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        
        m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
        
        //FW_WARN("Viewport Size: {0}, {1}", viewportPanelSize.x, viewportPanelSize.y);
        uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();

        ImDrawList* drawList = ImGui::GetWindowDrawList();
        ImGuiPlatformIO& platformIO = ImGui::GetPlatformIO();

        drawList->AddCallback(platformIO.DrawCallback_SetSamplerNearest, nullptr);
        ImGui::Image(reinterpret_cast<void*>(static_cast<std::uintptr_t>(textureID)), ImVec2( m_ViewportSize.x, m_ViewportSize.y ), ImVec2( 0, 1 ), ImVec2( 1, 0 ));
        drawList->AddCallback(platformIO.DrawCallback_SetSamplerLinear, nullptr);

        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::End();
    }

    void CustomEditorLayer::RenderCustomUI()
    {
        FW_PROFILE_FUNCTION();

        auto& window = Application::Get().GetWindow();
        const float windowWidth = static_cast<float>(window.GetWidth());
        const float windowHeight = static_cast<float>(window.GetHeight());

        if (windowWidth <= 0.0f || windowHeight <= 0.0f) 
            return;

        const float aspectRatio = windowWidth / windowHeight;
        const float maxWidth = windowWidth - 64.0f;
        const float maxHeight = windowHeight - 96.0f;
        
        float displayWidth = std::min(maxWidth, maxHeight * aspectRatio);
        displayWidth = std::max(displayWidth, 1.0f);
        const float displayHeight = displayWidth / aspectRatio;

        m_ViewportPosition = { 0.0f, 0.0f }; // Example: X:200, Y:50
        m_ViewportSize = { displayWidth, displayHeight };    // Example: 800x600 resolution
        
        // Calculate Hover State manually using OS mouse position
        const auto [mouseX, mouseY] = Input::GetMousePosition();
        const float uiMouseX = mouseX - windowWidth * 0.5f;
        const float uiMouseY = windowHeight * 0.5f - mouseY;

        //FW_CORE_WARN("Mouse position: {0}, {1}", mouseX, windowHeight - mouseY);

        m_ViewportHovered =
            std::abs(uiMouseX - m_ViewportPosition.x) <= displayWidth * 0.5f &&
            std::abs(uiMouseY - m_ViewportPosition.y) <= displayHeight * 0.5f;
        
        m_ViewportFocused = m_ViewportHovered;

        Renderer2D::BeginScene(m_CustomEditorCamera);

        RenderCommand::SetViewport(0, 0, window.GetWidth(), window.GetHeight());
        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.5f, 1.0f });
        RenderCommand::Clear();

        
        Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

        if (m_RootUIWidget)
            m_RootUIWidget->OnRender();
        
        Renderer2D::EndScene();
    }
}