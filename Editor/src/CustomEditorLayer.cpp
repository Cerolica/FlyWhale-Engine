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
        : Layer("CustomEditorLayer")
    {

    }

    void CustomEditorLayer::OnAttach() 
    {
        FW_PROFILE_FUNCTION();

        auto& window = Application::Get().GetWindow();
        window.SetCursor(CursorType::Arrow);

        m_CheckerboardTexture = Texture2D::Create("assets/textures/Checkerboard.png");
        m_SpriteSheet = Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");

        m_TextureStairs = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 0, 11 }, { 128, 128 });
        m_TextureTree = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 1 }, { 128, 128 }, { 1, 2 });
        
        m_MapWidth = s_MapWidth;
        m_MapHeight = strlen(s_MapTiles) / m_MapWidth;
        s_TextureMap['D'] = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 6, 11 }, { 128, 128 });
        s_TextureMap['W'] = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 11, 11 }, { 128, 128 });

        FramebufferSpecification fbSpec;
        fbSpec.Width = 1280;
        fbSpec.Height = 720;
        m_Framebuffer = Framebuffer::Create(fbSpec);

        // Scene
        // -----
        m_EditorContext.ActiveScene = CreateRef<Scene>();
        m_EditorWorkspace.Build(m_EditorContext, m_Framebuffer, window.GetWidth(), window.GetHeight());

        auto square = m_EditorContext.ActiveScene->CreateEntity("Green Square");
        square.AddComponent<SpriteRendererComponent>(Vector4{0.0f, 1.0f, 0.0f, 1.0f });
        
        m_SquareEntity = square;

        m_CameraEntity = m_EditorContext.ActiveScene->CreateEntity("Camera Entity");
        m_CameraEntity.AddComponent<CameraComponent>();

        m_SecondCamera = m_EditorContext.ActiveScene->CreateEntity("Clip-Space Entity");
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

        m_SceneHierarchyPanel.SetContext(m_EditorContext.ActiveScene);
    }

    void CustomEditorLayer::OnDetach()
    {
        FW_PROFILE_FUNCTION();
    }

    void CustomEditorLayer::OnUpdate(Timestep ts)
    {
        FW_PROFILE_FUNCTION();

        auto& window = Application::Get().GetWindow();

        // Update
        // ------
        
        m_EditorWorkspace.OnUpdate(ts);

        const Vector2 size = m_EditorWorkspace.GetViewportSize();
        if (size.x > 0.0f && size.y > 0.0f)
        {
            const uint32_t width = static_cast<uint32_t>(size.x);
            const uint32_t height = static_cast<uint32_t>(size.y);
            const auto& spec = m_Framebuffer->GetSpecification();

            if (spec.Width != width || spec.Height != height)
            {
                m_Framebuffer->Resize(width, height);
                m_EditorContext.ActiveScene->OnViewportResize(width, height);
            }
        }

        // Render
        // ------
        // Reset stats here
        Renderer2D::ResetStats();

        auto& spec = m_Framebuffer->GetSpecification();

        if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f &&
            (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
        {
            m_Framebuffer->Resize(m_ViewportSize);
            m_EditorContext.ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
        }

        m_Framebuffer->Bind();

        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        RenderCommand::Clear();

        // Update scene
        m_EditorContext.ActiveScene->OnUpdate(ts);

        m_Framebuffer->Unbind();
        
    }

    void CustomEditorLayer::OnRenderUI()
    {
        FW_PROFILE_FUNCTION();

        m_EditorWorkspace.OnRender();
    }

    void CustomEditorLayer::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent& e)
        {
            m_EditorWorkspace.OnResize(e.GetWidth(), e.GetHeight());

            return false;
        });

    
        m_EditorWorkspace.OnEvent(e);
        
    }
}