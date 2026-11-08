#include <FlyWhale.h>
#include <FlyWhale/Core/EntryPoint.h>

#include "EditorLayer.h"
#include "CustomEditorLayer.h"

namespace FlyWhale
{

    class FlyWhaleEditor : public Application
    {
    public:
        FlyWhaleEditor() 
            : Application("FlyWhale Editor")
        {
            PushLayer(new CustomEditorLayer());
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