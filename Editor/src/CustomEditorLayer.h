#pragma once
#include <FlyWhale.h>

#include "Panels/SceneHierarchyPanel.h"

namespace FlyWhale
{

    class CustomEditorLayer : public Layer
    {
        public:
        CustomEditorLayer();
        virtual ~CustomEditorLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;

        void OnUpdate(Timestep ts) override;
        virtual void OnUIRender() override;
        void OnEvent(Event& e) override;
    private:
        void RenderImGui();
        void RenderCustomUI();
    private:
        OrthographicCameraController m_CameraController;
        OrthographicCamera m_CustomEditorCamera = { 0, 1280, 0, 720};

        bool m_UseImGui = false;

        // Temp
        Ref<VertexArray> m_SquareVA;
        Ref<Shader> m_FlatColorShader;

        Ref<Texture2D> m_CheckerboardTexture;
        Ref<Texture2D> m_SpriteSheet;
        Ref<SubTexture2D> m_TextureStairs;
        Ref<SubTexture2D> m_TextureBarrel;
        Ref<SubTexture2D> m_TextureTree;

        Ref<Framebuffer> m_Framebuffer;

        Ref<Scene> m_ActiveScene;
        Entity m_SquareEntity;
        Entity m_CameraEntity;
        Entity m_SecondCamera;

        bool m_PrimaryCamera = true;

        Ref<UI::Widget> m_RootUIWidget;

        bool m_ViewportFocused = false;
        bool m_ViewportHovered = false;
        Vector2 m_ViewportSize = { 0.0f, 0.0f };
        Vector2 m_ViewportPosition = { 0.0f, 0.0f };

        Vector4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

        uint32_t m_MapWidth, m_MapHeight;
        std::unordered_map<char, Ref<SubTexture2D>> s_TextureMap;

        // Panels
        SceneHierarchyPanel m_SceneHierarchyPanel;
    };
}