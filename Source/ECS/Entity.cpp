#include "Entity.h"

namespace Q3D
{
    namespace ECS
    {
        Entity::Entity(Scene *pScene, entt::entity entity) : m_EntityHandle(entity), m_Scene(pScene)
        {
            
        }
    } // namespace Scene

} // namespace Q3D
