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
            switch(m_UIMode)
            {
                case UIMode::ImGuiEditor: PushLayer(new EditorLayer());
                case UIMode::CustomEditor: PushLayer(new CustomEditorLayer());
                default: break;
            }
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