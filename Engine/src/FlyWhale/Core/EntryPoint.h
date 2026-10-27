#pragma once

#include "FlyWhale/Core/Application.h"
#include "FlyWhale/Core/Log.h"

#ifdef FW_PLATFORM_WINDOWS

extern FlyWhale::Application* FlyWhale::CreateApplication();

int main(int argc,  char** argv) 
{
    FlyWhale::Log::Init();

    FW_PROFILE_BEGIN_SESSION("Startup", "FlyWhale-Startup.json");
    auto app = FlyWhale::CreateApplication();
    FW_PROFILE_END_SESSION();

    FW_PROFILE_BEGIN_SESSION("Runtime", "FlyWhale-Runtime.json");
    app->Run();
    FW_PROFILE_END_SESSION();

    FW_PROFILE_BEGIN_SESSION("Shutdown", "FlyWhale-Shutdown.json");
    delete app;
    FW_PROFILE_END_SESSION();
}

#endif