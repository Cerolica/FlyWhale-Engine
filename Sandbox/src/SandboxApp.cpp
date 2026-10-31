#include <FlyWhale.h>
#include <FlyWhale/Core/EntryPoint.h>

#include "Sandbox2D.h"

class Sandbox : public FlyWhale::Application 
{
public:
    Sandbox() 
    {
        //PushLayer(new ExampleLayer());
        PushLayer(new Sandbox2D());
    }

    ~Sandbox() {}
};

FlyWhale::Application* FlyWhale::CreateApplication() 
{
    return new Sandbox();
}