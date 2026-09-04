#pragma once

#include "Core.h"

namespace FlyWhale {

    class FW_API Application {
    public:
        Application();
        virtual ~Application();

        void Run(); // Run the application
    };

    // To be defined in CLIENT
    Application* CreateApplication();

}