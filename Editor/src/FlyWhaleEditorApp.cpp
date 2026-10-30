#include <FlyWhale.h>
#include <FlyWhale/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace FlyWhale
{

    class FlyWhaleEditor : public Application
    {
    public:
        FlyWhaleEditor() 
            : Application("FlyWhale Editor")
        {
            PushLayer(new EditorLayer());
        }

        ~FlyWhaleEditor()
        {
        }
    };

    Application* CreateApplication()
    {
        return new FlyWhaleEditor();
    }
}