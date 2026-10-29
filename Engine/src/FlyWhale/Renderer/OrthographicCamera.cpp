#include "fwpch.h"
#include "OrthographicCamera.h"


namespace FlyWhale
{

    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : m_ProjectionMatrix(Math::Orthographic(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
    {
        FW_PROFILE_FUNCTION();
        
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
    {
        FW_PROFILE_FUNCTION();

        m_ProjectionMatrix = Math::Orthographic(left, right, bottom, top, -1.0f, 1.0f);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::RecalculateViewMatrix()
    {
        FW_PROFILE_FUNCTION();

        Matrix4 transform = Math::Translate(Matrix4(1.0f), m_Position)
                          * Math::Rotate(Matrix4(1.0f), Math::Radians(m_Rotation), Vector3(0, 0, 1));
        
        m_ViewMatrix = Math::Inverse(transform);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
}