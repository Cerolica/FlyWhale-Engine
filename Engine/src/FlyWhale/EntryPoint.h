#pragma once

#include "Application.h"
#include "Log.h"

#ifdef FW_PLATFORM_WINDOWS

extern FlyWhale::Application* FlyWhale::CreateApplication();

int main(int argc,  char** argv) 
{
    FlyWhale::Log::Init();
    FW_CORE_WARN("Initialized Log!");
    int a = 5;
    FW_INFO("Hello! Var={0}", a);

    auto app = FlyWhale::CreateApplication();
    app->Run();
    delete app;
}

#endif