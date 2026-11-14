#pragma once

#include "FlyWhale/Renderer/Camera.h"

namespace FlyWhale
{

    class SceneCamera : public Camera
    {
    public:
        enum class ProjectionType
        {
            Perspective = 0,
            Orthographic = 1
        };
    public:
        SceneCamera();
        virtual ~SceneCamera() = default;
    
        void SetOrthographic(float size, float nearClip, float farClip);

        void SetViewportSize(uint32_t width, uint32_t height);

        float GetOrthographicSize() const { return m_OrthographicSize; }
        void SetOrthoGraphicSize(float size) { m_OrthographicSize = size; RecalculateProjection(); }

        float GetOrthographicNearClip() const { return m_OrthographicNear; }
        float GetOrthographicFarClip() const { return m_OrthographicFar; }
        void SetOrthographicNearClip(float nearClip) { m_OrthographicNear = nearClip; }
        void SetOrthographicFarClip(float farClip) { m_OrthographicFar = farClip; }

        ProjectionType GetProjectionType() const { return m_ProjectionType; } 
        void SetProjectionType(ProjectionType type) { m_ProjectionType = type; }
    private: 
        void RecalculateProjection();
    private:
        ProjectionType m_ProjectionType = ProjectionType::Orthographic;

        float m_OrthographicSize = 10.0f;
        float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;

        float m_AspectRatio = 0.0f;
    };
}