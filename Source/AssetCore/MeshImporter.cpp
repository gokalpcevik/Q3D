#include "MeshImporter.h"

namespace Q3D
{
	namespace AssetCore
	{

		MeshImporter::MeshImporter(std::filesystem::path path)
			: m_Path(std::move(path))
		{
			Assimp::Importer importer;
			auto const *pScene = importer.ReadFile(m_Path.string().c_str(), aiProcess_Triangulate |
																				aiProcess_ConvertToLeftHanded);

			if (!pScene)
			{
				Q3D_ERROR("Error while importing mesh: {0}", importer.GetErrorString());
				m_Success = false;
				return;
			}

			auto const *pMesh = pScene->mMeshes[0];
			m_Data.Vertices.reserve(pMesh->mNumVertices);
			m_Data.Faces.reserve(pMesh->mNumFaces);

			for (size_t i = 0; i < pMesh->mNumVertices; ++i)
			{
				Vector4f pos = {pMesh->mVertices[i].x, pMesh->mVertices[i].y, pMesh->mVertices[i].z, 1.0f};
				Vector4f normal = {pMesh->mNormals[i].x, pMesh->mNormals[i].y, pMesh->mNormals[i].z, 0.0f};
				m_Data.Vertices.emplace_back(Graphics::Vertex{pos, normal});
			}

			for (size_t i = 0; i < pMesh->mNumFaces; ++i)
			{
				auto const &face = pMesh->mFaces[i];
				m_Data.Faces.emplace_back(Graphics::Face{face.mIndices[0], face.mIndices[1], face.mIndices[2]});
			}
		}

		bool MeshImporter::ImportSucceeded() const
		{
			return m_Success;
		}
	} // namespace AssetUtils
}
