#pragma once

#ifdef FW_PLATFORM_WINDOWS

extern FlyWhale::Application* FlyWhale::CreateApplication();

int main(int argc,  char** argv) {
    auto app = FlyWhale::CreateApplication();
    app->Run();
    delete app;
}

#endif