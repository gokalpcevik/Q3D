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
			m_Vertices.emplace_back(
				Graphics::Vertex{ *(Vector3f*)&pMesh->mVertices[i]
					,*(Vector3f*)&pMesh->mNormals[i] });
		}

		for(size_t i = 0; i < pMesh->mNumFaces; ++i)
		{
			auto const& face = pMesh->mFaces[i];
			m_Faces.emplace_back(Graphics::Face{ face.mIndices[0],face.mIndices[1],face.mIndices[2] });
		}
	}

	bool MeshImporter::Success() const
	{
		return m_Success;
	}

	void MeshImporter::Move(std::vector<Graphics::Vertex>& vertices, std::vector<Graphics::Face>& faces)
	{
		vertices = std::move(m_Vertices);
		faces = std::move(m_Faces);
	}

	void MeshImporter::Copy(std::vector<Graphics::Vertex>& vertices, std::vector<Graphics::Face>& faces) const
	{
		vertices = m_Vertices;
		faces = m_Faces;
	}
}
