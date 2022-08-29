#pragma once
#include <Eigen/Eigen>

namespace Q3D
{
    namespace Math
    {
        using Eigen::Vector4f;
		using Eigen::Vector2f;

        auto ProjectPerspective(const Vector4f& pos)->Vector2f;
        // Returns a perspective projection matrix(column-major form)
        // auto PerspectiveProjectionMatrix() -> Eigen::Matrix<float,4ULL,4ULL>;
    } // namespace Math
    
} // namespace Q3D
