#pragma once
#include <Eigen/Eigen>
#include <vector>
#include <cstdint>
#include <utility>

namespace Q3D
{
	namespace Graphics
	{
		using Eigen::Vector4f;
		using Eigen::Vector3f;
		using Eigen::Vector2f;
		using Eigen::Vector3i;

		struct Face
		{
			Face() = default;
			// Indices
			uint32_t i0, i1, i2;
		};

		struct Vertex
		{
			Vector4f Position{ 0.0f,0.0f,0.0f,1.0f };
			Vector4f Normal{ 0.0f,0.0f,0.0f,0.0f };
		};

		struct Rectangle
		{
			uint32_t X, Y, Width, Height, Color;
		};

		struct Triangle
		{
			std::array<Vector2f, 3ULL> Points{};
			// Non linearized average depth of the triangle
			float AverageDepth = 0.5f;
			uint32_t Color = 0xFFFFFFFF;
		};
	}
}