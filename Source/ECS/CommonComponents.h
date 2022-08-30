#pragma once
#include <Eigen/Eigen>
#include <utility>
#include <string>

namespace Q3D
{
    namespace ECS
    {
        using Eigen::Matrix4f;
        using Eigen::Vector4f;
        using Eigen::Vector3f;

        struct TransformComponent
        {
            TransformComponent() = default;
            TransformComponent(Vector4f translation,Vector3f rotation ,Vector3f scale)
            : Translation(std::move(translation)),Rotation(std::move(rotation)),Scale(std::move(scale))
            {}
            Vector4f Translation{};
            Vector3f Rotation{};
            Vector3f Scale{};
        };

        struct TagComponent
        {
            TagComponent() = default;
            TagComponent(std::string tag) : Tag(std::move(tag)) {}

            std::string Tag;
        };
    } // namespace ECS
    
} // namespace Q3D
