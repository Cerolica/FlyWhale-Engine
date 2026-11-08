#pragma once

#include "FlyWhale/Math/Math.h"
#include "FlyWhale/Renderer/SceneCamera.h"

namespace FlyWhale
{

    struct TagComponent
    {
        std::string Tag;

        TagComponent() = default;
        TagComponent(const TagComponent&) = default;
        TagComponent(const std::string& tag)
            : Tag(tag) {}
    };

    struct TransformComponent
    {
        Matrix4 Transform{ 1.0f };

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const Matrix4& transform)
            : Transform(transform) {}

        operator Matrix4& () { return Transform; }
        operator const Matrix4& () const { return Transform; }
    };

    struct SpriteRendererComponent
    {
        Vector4 Color{ 1.0f };

        SpriteRendererComponent() = default;
        SpriteRendererComponent(const SpriteRendererComponent&) = default;
        SpriteRendererComponent(const Vector4& color)
            : Color(color) {}
    };

    struct CameraComponent
    {
        SceneCamera Camera;
        bool Primary = true; // TODO: moving to scene
        bool FixedAspectRatio = false;

        CameraComponent() = default;
        CameraComponent(const CameraComponent&) = default;
    };

    struct MeshComponent
    {

    };
}