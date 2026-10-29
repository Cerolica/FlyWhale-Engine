#pragma once

#include "FlyWhale/Math/Math.h"

namespace FlyWhale
{

    class OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);
        
        void SetProjection(float left, float right, float bottom, float top);

        inline const Vector3& GetPosition() const { return m_Position; }
        inline void SetPosition(const Vector3& position) { m_Position = position; RecalculateViewMatrix(); }

        inline float GetRotation() const { return m_Rotation; }
        inline void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

        inline const Matrix4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        inline const Matrix4& GetViewMatrix() const { return m_ViewMatrix; }
        inline const Matrix4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
    private:
        void RecalculateViewMatrix();
    private:
        Matrix4 m_ProjectionMatrix;
        Matrix4 m_ViewMatrix;
        Matrix4 m_ViewProjectionMatrix;

        Vector3 m_Position = { 0.0f, 0.0f, 0.0f };
        float m_Rotation = 0.0f;
    };
}