#pragma once

#include "FlyWhale/Core/Core.h"
#include "FlyWhale/Scene/Scene.h"
#include "FlyWhale/Scene/Components.h"
#include "FlyWhale/Scene/Entity.h"

namespace FlyWhale
{

    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel() = default;
        SceneHierarchyPanel(const Ref<Scene>& context);

        void SetContext(const Ref<Scene>& context);

        void OnRenderUI();
    private:
        void DrawEntityNode(Entity entity);
        void DrawComponents(Entity entity);
    private:
        Ref<Scene> m_Context;
        Entity m_SelectionContext;
    };
}