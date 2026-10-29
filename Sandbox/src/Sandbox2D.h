#pragma once

#include <FlyWhale.h>

class Sandbox2D : public FlyWhale::Layer
{
public:
    Sandbox2D();
    virtual ~Sandbox2D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnUpdate(FlyWhale::Timestep ts) override;
    virtual void OnImGuiRender() override;
    void OnEvent(FlyWhale::Event& e) override;
private:
    FlyWhale::OrthographicCameraController m_CameraController;

    // Temp
    FlyWhale::Ref<FlyWhale::VertexArray> m_SquareVA;
    FlyWhale::Ref<FlyWhale::Shader> m_FlatColorShader;

    FlyWhale::Ref<FlyWhale::Texture2D> m_CheckerboardTexture;
    FlyWhale::Ref<FlyWhale::Texture2D> m_SpriteSheet;
    FlyWhale::Ref<FlyWhale::SubTexture2D> m_TextureStairs;
    FlyWhale::Ref<FlyWhale::SubTexture2D> m_TextureBarrel;
    FlyWhale::Ref<FlyWhale::SubTexture2D> m_TextureTree;

    glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

    uint32_t m_MapWidth, m_MapHeight;
    std::unordered_map<char, FlyWhale::Ref<FlyWhale::SubTexture2D>> s_TextureMap;
};