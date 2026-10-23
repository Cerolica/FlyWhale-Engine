#pragma once

#include "FlyWhale/Renderer/OrthographicCamera.h"
#include "FlyWhale/Core/Timestep.h"

#include "FlyWhale/Events/ApplicationEvent.h"
#include "FlyWhale/Events/MouseEvent.h"


namespace FlyWhale
{

    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);

        inline OrthographicCamera& GetCamera() { return m_Camera; }
        inline const OrthographicCamera& GetCamera() const { return m_Camera; }

        inline float GetZoomLevel() { return m_ZoomLevel; }
        inline void SetZoomLevel(float level) { m_ZoomLevel = level; }
    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);
    private:
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        OrthographicCamera m_Camera;

        bool m_Rotation = false;

        glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
        float m_CameraRotation = 0.0f;
        float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
    };
}