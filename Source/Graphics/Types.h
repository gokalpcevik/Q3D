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
			Vector3f Normal{ 0.0f,0.0f,0.0f };
		};

		struct Rectangle
		{
			uint32_t x, y, width, height, color;
		};

		struct Triangle
		{
			std::array<Vector2f, 3ULL> Points{};
			// Non linearized avergae depth of the triangle
			float AverageDepth = 0.5f;
			uint32_t Color = 0xFFFFFFFF;
		};

		struct Mesh
		{
			std::vector<Vertex> Vertices{};
			std::vector<Face> Faces{};
			Vector3f Translation{ 0.0f,0.0f,0.0f };
			//Euler angles for now
			Vector3f Rotation{ 0.0f,0.0f,0.0f };
		};
	}
}