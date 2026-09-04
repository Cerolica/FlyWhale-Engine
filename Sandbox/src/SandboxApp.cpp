#include <FlyWhale.h>

class Sandbox : public FlyWhale::Application {
public:
    Sandbox() {

    }

    ~Sandbox() {

    }
};

FlyWhale::Application* FlyWhale::CreateApplication() {
    return new Sandbox();
}