#pragma once
#include <entt/entt.hpp>
#include "CommonComponents.h"
#include "MeshComponent.h"
#include "../Graphics/Renderer.h"
#include "../AssetCore/MeshLibrary.h"

namespace Q3D
{
    namespace ECS
    {
        class Entity;

        class Scene
        {
        public:
            Scene() = default;
            Scene(Scene&&) = default;
            Scene(const Scene&) = delete;

            auto CreateEntity() -> Entity;
            void Destroy(Entity entity);
            void Update();
            void Draw(Graphics::Renderer& renderer);

            template <typename T>
            auto GetComponent(entt::entity entity) -> T &;

            template <typename T, typename... Args>
            auto AddComponent(entt::entity entity, Args &&...args) -> T &;

            template <typename T>
            auto RemoveComponent(entt::entity entity) -> void;
        private:
            entt::registry m_Registry{};
			
        };
        template <typename T>
        inline auto Scene::GetComponent(entt::entity entity) -> T &
        {
            return m_Registry.get<T>(entity);
        }
        template <typename T, typename... Args>
        inline auto Scene::AddComponent(entt::entity entity, Args &&...args) -> T &
        {
            return m_Registry.emplace<T>(entity, std::forward<Args>(args)...);
        }

        template <typename T>
        auto Scene::RemoveComponent(entt::entity entity) -> void
        {
            m_Registry.remove<T>(entity);
        }
    } // namespace Scene
} // namespace Q3D
