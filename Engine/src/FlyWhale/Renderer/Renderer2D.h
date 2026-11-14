#pragma once

#include "FlyWhale/Renderer/Editor2DCamera.h"
#include "FlyWhale/Renderer/Camera.h"

#include "FlyWhale/Renderer/Texture.h"
#include "FlyWhale/Renderer/SubTexture2D.h"

#include "FlyWhale/Math/Math.h"

namespace FlyWhale
{

    class Renderer2D
    {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const Camera& camera, const Matrix4& transform);
        static void BeginScene(const Editor2DCamera& camera); // TODO: Remove
        static void EndScene();
        static void Flush();

        // Primitives
        static void DrawQuad(const Vector2& position, const Vector2& size, const Vector4& color);
        static void DrawQuad(const Vector3& position, const Vector2& size, const Vector4& color);
        static void DrawQuad(const Vector2& position, const Vector2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const Vector4& tintColor = Vector4(1.0f));
        static void DrawQuad(const Vector3& position, const Vector2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const Vector4& tintColor = Vector4(1.0f));
        static void DrawQuad(const Vector2& position, const Vector2& size, const Ref<Texture2D>& texture, const Vector2* texCoords, float tilingFactor = 1.0f, const Vector4& tintColor = Vector4(1.0f));
        static void DrawQuad(const Vector3& position, const Vector2& size, const Ref<Texture2D>& texture, const Vector2* texCoords, float tilingFactor = 1.0f, const Vector4& tintColor = Vector4(1.0f));
        static void DrawQuad(const Vector2& position, const Vector2& size, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const Vector4& tintColor = Vector4(1.0f));
        static void DrawQuad(const Vector3& position, const Vector2& size, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const Vector4& tintColor = Vector4(1.0f));

        static void DrawQuad(const Matrix4& transform, const Vector4& color);
        static void DrawQuad(const Matrix4& transform, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const Vector4& tintColor = Vector4(1.0f));
        static void DrawQuad(const Matrix4& transform, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const Vector4& tintColor = Vector4(1.0f));

        static void DrawRotatedQuad(const Vector2& position, const Vector2& size, float rotation, const Vector4& color);
        static void DrawRotatedQuad(const Vector3& position, const Vector2& size, float rotation, const Vector4& color);
        static void DrawRotatedQuad(const Vector2& position, const Vector2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const Vector4& tintColor = Vector4(1.0f));
        static void DrawRotatedQuad(const Vector3& position, const Vector2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const Vector4& tintColor = Vector4(1.0f));
        static void DrawRotatedQuad(const Vector2& position, const Vector2& size, float rotation, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const Vector4& tintColor = Vector4(1.0f));
        static void DrawRotatedQuad(const Vector3& position, const Vector2& size, float rotation, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const Vector4& tintColor = Vector4(1.0f));

        // Stats
        struct Statistics
        {
            uint32_t DrawCalls = 0;
            uint32_t QuadCount = 0;

            uint32_t GetTotalVertexCount() { return QuadCount * 4; }
            uint32_t GetTotalIndexCount() { return QuadCount * 6; }
        };

        static void ResetStats();
        static Statistics GetStats();
    private:
        static void FlushAndReset();
    };
}