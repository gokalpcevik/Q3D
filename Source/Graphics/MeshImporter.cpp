#include "MeshImporter.h"

namespace Q3D
{
	MeshImporter::MeshImporter(std::filesystem::path path)
	: m_Path(std::move(path))
	{
		Assimp::Importer importer;
		auto const* pScene = importer.ReadFile(m_Path.string().c_str(), aiProcess_Triangulate |
			aiProcess_ConvertToLeftHanded
		);

		if(!pScene)
		{
			Q3D_ERROR("Error while importing mesh: {0}", importer.GetErrorString());
			m_Success = false;
			return;
		}

		auto const* pMesh = pScene->mMeshes[0];
		m_Vertices.reserve(pMesh->mNumVertices);
		m_Faces.reserve(pMesh->mNumFaces);

		for(size_t i = 0; i < pMesh->mNumVertices; ++i)
		{
			m_Vertices[i].Position = *reinterpret_cast<Vector3f*>(&pMesh->mVertices[i]);
		}

		for(size_t i = 0; i < pMesh->mNumFaces; ++i)
		{
			auto const& face = pMesh->mFaces[i];
			m_Faces[i] = { face.mIndices[0],face.mIndices[1],face.mIndices[2] };
		}
	}

	bool MeshImporter::Success() const
	{
		return m_Success;
	}
}