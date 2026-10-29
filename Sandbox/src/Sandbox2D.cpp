#include "Sandbox2D.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{

}

void Sandbox2D::OnAttach() 
{
    FW_PROFILE_FUNCTION();

    m_CheckerboardTexture = FlyWhale::Texture2D::Create("assets/textures/Checkerboard.png");
    m_SpriteSheet = FlyWhale::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");

    m_TextureStairs = FlyWhale::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 0, 11 }, { 128, 128 });
    m_TextureTree = FlyWhale::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 1 }, { 128, 128 }, { 1, 2 });
    
    m_MapWidth = s_MapWidth;
    m_MapHeight = strlen(s_MapTiles) / m_MapWidth;
    s_TextureMap['D'] = FlyWhale::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 6, 11 }, { 128, 128 });
    s_TextureMap['W'] = FlyWhale::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 11, 11 }, { 128, 128 });

    m_CameraController.SetZoomLevel(5.0f);
}

void Sandbox2D::OnDetach()
{
    FW_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(FlyWhale::Timestep ts)
{

    FW_PROFILE_FUNCTION();

    // Update
    m_CameraController.OnUpdate(ts);
    

    // Render
    // Reset stats here
    FlyWhale::Renderer2D::ResetStats();
    {
        FW_PROFILE_SCOPE("Renderer Prep");
        FlyWhale::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        FlyWhale::RenderCommand::Clear();
    }
#if 0
    {

        static float rotation = 0.0f;
        rotation += ts * 20.0f;

        FW_PROFILE_SCOPE("Renderer Draw");
        FlyWhale::Renderer2D::BeginScene(m_CameraController.GetCamera());

        FlyWhale::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, {0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
        FlyWhale::Renderer2D::DrawQuad({ -1.0f, 0.0f }, {0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
        FlyWhale::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
        FlyWhale::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
        FlyWhale::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 20.0f);

        FlyWhale::Renderer2D::EndScene();

        FlyWhale::Renderer2D::BeginScene(m_CameraController.GetCamera());

        for (float y = -5.0f; y < 5.0f; y += 0.5f)
        {
            for (float x = -5.0f; x < 5.0f; x += 0.5f)
            {
                FlyWhale::Vector4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };

                FlyWhale::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
            }
        }

        FlyWhale::Renderer2D::EndScene();
    }
#endif

    FlyWhale::Renderer2D::BeginScene(m_CameraController.GetCamera());

    for (uint32_t y = 0; y < m_MapHeight; y++)
    {
        for (uint32_t x = 0; x < m_MapWidth; x++)
        {
            char tileType = s_MapTiles[x + y * m_MapWidth];
            FlyWhale::Ref<FlyWhale::SubTexture2D> texture;

            if (s_TextureMap.find(tileType) != s_TextureMap.end())
                texture = s_TextureMap[tileType];
            else 
                texture = m_TextureStairs;
            FlyWhale::Renderer2D::DrawQuad({ x - m_MapWidth / 2.0f, m_MapHeight - y - m_MapHeight / 2.0f, 0.5f }, { 1.0f, 1.0f }, texture);
        }

    }

    //FlyWhale::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_TextureStairs);
    //FlyWhale::Renderer2D::DrawQuad({ 1.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_TextureBarrel);
    //FlyWhale::Renderer2D::DrawQuad({ -1.0f, 0.0f, 0.5f }, { 1.0f, 2.0f }, m_TextureTree);


    FlyWhale::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
    FW_PROFILE_FUNCTION();

    ImGui::Begin("Settings");

    auto stats = FlyWhale::Renderer2D::GetStats();
    ImGui::Text("Renderer2D Stats:");
    ImGui::Text("Draw Calls: %d", stats.DrawCalls);
    ImGui::Text("Quads: %d", stats.QuadCount);
    ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
    ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

    ImGui::End();
}

void Sandbox2D::OnEvent(FlyWhale::Event& e)
{
    m_CameraController.OnEvent(e);
}