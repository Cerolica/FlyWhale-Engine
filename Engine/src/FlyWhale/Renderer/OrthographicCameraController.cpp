#include "fwpch.h"
#include "OrthographicCameraController.h"

#include "FlyWhale/Core/Input.h"
#include "FlyWhale/Core/KeyCodes.h"

namespace FlyWhale
{

    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
        : m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
    {
    }

    void OrthographicCameraController::OnUpdate(Timestep ts)
    {
        FW_PROFILE_FUNCTION();

        if (Input::IsKeyPressed(FW_KEY_A))
            m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
        
        if (Input::IsKeyPressed(FW_KEY_D))
            m_CameraPosition.x += m_CameraTranslationSpeed * ts;

        if (Input::IsKeyPressed(FW_KEY_S))
            m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
        
        if (Input::IsKeyPressed(FW_KEY_W))
            m_CameraPosition.y += m_CameraTranslationSpeed * ts;

        if (m_Rotation)
        {
            if (Input::IsKeyPressed(FW_KEY_Q))
                m_CameraRotation += m_CameraRotationSpeed * ts;
            
            if (Input::IsKeyPressed(FW_KEY_E))
                m_CameraRotation -= m_CameraRotationSpeed * ts;  
            
            m_Camera.SetRotation(m_CameraRotation);
        }

        m_Camera.SetPosition(m_CameraPosition);

        m_CameraTranslationSpeed = m_ZoomLevel;
    }

    void OrthographicCameraController::OnEvent(Event& e)
    {
        FW_PROFILE_FUNCTION();

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(FW_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(FW_BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));

    }

    void OrthographicCameraController::CalculateView()
    {
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        FW_PROFILE_FUNCTION();

        m_ZoomLevel -= e.GetYOffset();
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        CalculateView();

        FW_TRACE("ZoomLevel: {0}", m_ZoomLevel);

        return false;
    }
    
    bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
    {
        FW_PROFILE_FUNCTION();
        
        m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        CalculateView();

        return false;
    }
}