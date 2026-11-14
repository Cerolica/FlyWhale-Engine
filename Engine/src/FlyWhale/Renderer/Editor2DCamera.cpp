#include "fwpch.h"
#include "Editor2DCamera.h"


namespace FlyWhale
{

    Editor2DCamera::Editor2DCamera(float left, float right, float bottom, float top)
        : Camera(Math::Orthographic(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
    {
        FW_PROFILE_FUNCTION();
        
        m_ViewProjectionMatrix = m_Projection * m_ViewMatrix;
    }

    void Editor2DCamera::SetProjection(float left, float right, float bottom, float top)
    {
        FW_PROFILE_FUNCTION();

        m_Projection = Math::Orthographic(left, right, bottom, top, -1.0f, 1.0f);
        m_ViewProjectionMatrix = m_Projection * m_ViewMatrix;
    }

    void Editor2DCamera::RecalculateViewMatrix()
    {
        FW_PROFILE_FUNCTION();

        Matrix4 transform = Math::Translate(Matrix4(1.0f), m_Position)
                          * Math::Rotate(Matrix4(1.0f), Math::Radians(m_Rotation), Vector3(0, 0, 1));
        
        m_ViewMatrix = Math::Inverse(transform);
        m_ViewProjectionMatrix = m_Projection * m_ViewMatrix;
    }
}