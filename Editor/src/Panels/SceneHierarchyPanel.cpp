#include "SceneHierarchyPanel.h"

#include <imgui.h>

namespace FlyWhale
{

    SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context)
    {
        SetContext(context);
    }
    

    void SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
    {
        m_Context = context;
    }
    
    void SceneHierarchyPanel::OnUIRender()
    {
        if (m_UseImGui)
            RenderImGui();
        else
            RenderCustomUI();
    }

    void SceneHierarchyPanel::RenderImGui()
    {
        ImGui::Begin("Scene Hierarchy");

        m_Context->m_Registry.view<TagComponent>().each([&](auto entityID, auto& tc) 
        {
            Entity entity{ entityID, m_Context.get() };
            DrawEntityNode(entity);
        });

        ImGui::End();
    }

    void SceneHierarchyPanel::RenderCustomUI()
    {

    }

    void SceneHierarchyPanel::DrawEntityNode(Entity entity)
    {
        auto& tag = entity.GetComponent<TagComponent>().Tag;

        ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity)? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
        bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
        if (ImGui::IsItemClicked())
        {
            m_SelectionContext = entity;
        }

        if (opened)
        {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
            bool opened = ImGui::TreeNodeEx((void*)1000, flags, tag.c_str());
            if (opened)
                ImGui::TreePop();

            ImGui::TreePop();
        }
    }



}