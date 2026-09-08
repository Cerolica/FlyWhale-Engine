#include <FlyWhale.h>

class ExampleLayer : public FlyWhale::Layer
{
public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override
    {
        //FW_INFO("ExampleLayer::Update");
    }

    void OnEvent(FlyWhale::Event& event) override
    {
        FW_TRACE("{0}", event);
    } 
};

class Sandbox : public FlyWhale::Application 
{
public:
    Sandbox() 
    {
        PushLayer(new ExampleLayer());
        PushOverlay(new FlyWhale::ImGuiLayer());
    }

    ~Sandbox() {}
};

FlyWhale::Application* FlyWhale::CreateApplication() 
{
    return new Sandbox();
}