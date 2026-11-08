#include "fwpch.h"
#include "Entity.h"

namespace FlyWhale
{

    Entity::Entity(entt::entity handle, Scene* scene)
        : m_EntityHandle(handle), m_Scene(scene)
    {

    }
}