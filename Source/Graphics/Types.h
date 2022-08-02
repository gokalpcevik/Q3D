#pragma once
#include <Eigen/Eigen>
#include <vector>
#include <cstdint>
#include <utility>

namespace Q3D
{
	namespace Graphics
	{
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
			Vector3f Position{ 0.0f,0.0f,0.0f };

			float operator[](size_t i) const
			{
				return Position[i];
			}
		};

		struct Rectangle
		{
			uint32_t x, y, width, height, color;
		};

		struct Triangle
		{
			std::array<Vector2f, 3ULL> points{};
		};

		struct Mesh
		{
			std::vector<Vertex> vertices{};
			std::vector<Face> faces{};
		};
	}
}