#pragma once
#include <filesystem>
#include <vector>
#include <Eigen/Eigen>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../Graphics/Types.h"
#include "../Core/Log.h"

namespace Q3D
{
	using Eigen::Vector2f;
	using Eigen::Vector3f;
	using Eigen::Vector3i;
	using Eigen::Vector4f;

	namespace AssetCore
	{
		struct MeshAssetContent
		{
			std::vector<Graphics::Vertex> Vertices{};
			std::vector<Graphics::Face> Faces{};
		};

		class MeshImporter
		{
		public:
			MeshImporter(std::filesystem::path path);
			[[nodiscard]] bool ImportSucceeded() const;

			MeshAssetContent operator*() const
			{
				return m_Data;
			}

		private:
			std::filesystem::path m_Path{};
			MeshAssetContent m_Data{};
			bool m_Success = true;
		};
	}
}