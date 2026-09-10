#include <FlyWhale.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}

class ExampleLayer : public FlyWhale::Layer
{
public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override
    {
        //FW_INFO("ExampleLayer::Update");

        if (FlyWhale::Input::IsKeyPressed(FW_KEY_TAB))
            FW_TRACE("Tab key is pressed (poll)!");
    }

    void OnEvent(FlyWhale::Event& event) override
    {
        //FW_TRACE("{0}", event);

        if (event.GetEventType() == FlyWhale::EventType::KeyPressed)
        {
            FlyWhale::KeyPressedEvent& e = (FlyWhale::KeyPressedEvent&)event;
            if (e.GetKeyCode() == FW_KEY_TAB)
                FW_TRACE("Tab key is pressed (event)!");

            FW_TRACE("{0}", (char)e.GetKeyCode());
        }
    } 
};

class Sandbox : public FlyWhale::Application 
{
public:
    Sandbox() 
    {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox() {}
};

FlyWhale::Application* FlyWhale::CreateApplication() 
{
    return new Sandbox();
}