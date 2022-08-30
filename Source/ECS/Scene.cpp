#include "Scene.h"
#include "Entity.h"

namespace Q3D
{
    namespace ECS
    {
        auto Scene::CreateEntity() -> Entity
        {
            entt::entity e = m_Registry.create();
            m_Registry.emplace<TransformComponent>(e);
            return {this, e};
        }

        void Scene::Destroy(Entity entity)
        {
            m_Registry.destroy(entity);
        }

        void Scene::Update()
        {
        }

        void Scene::Draw(Graphics::Renderer& renderer)
        {
            auto const meshView = m_Registry.view<MeshComponent, TransformComponent>();

            for (auto const entity : meshView)
            {
                auto&& [mc, tc] = m_Registry.get<MeshComponent, TransformComponent>(entity);
                renderer.DrawMesh(mc, tc);
            }
        }
    } // namespace ECS

}