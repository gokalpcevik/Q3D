#pragma once
#include <filesystem>
#include <vector>
#include <Eigen/Eigen>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Types.h"
#include "../Core/Log.h"

namespace Q3D
{
	using Eigen::Vector3f;
	using Eigen::Vector2f;
	using Eigen::Vector3i;

	class MeshImporter
	{
	public:
		MeshImporter(std::filesystem::path path);
		[[nodiscard]] bool Success() const;

		void Move(std::vector<Graphics::Vertex>& vertices,std::vector<Graphics::Face>& faces);
	private:
		std::filesystem::path m_Path{};
		std::vector<Graphics::Vertex> m_Vertices{};
		std::vector<Graphics::Face> m_Faces{};
		bool m_Success = true;
	};
}