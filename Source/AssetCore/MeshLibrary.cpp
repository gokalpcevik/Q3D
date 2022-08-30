#include "MeshLibrary.h"

namespace Q3D
{
    namespace AssetCore
    {
        std::unordered_map<MeshAssetId, MeshAssetContent> MeshLibrary::s_MeshIdMap{};

        std::tuple<MeshAssetId, MeshAssetContent> MeshLibrary::Load(const fls::path &path)
        {
            MeshAssetId id = std::filesystem::hash_value(path);
            if (MeshLibrary::IsLoaded(MeshLibrary::GetIdFromPath(path)))
            {
                return {id, s_MeshIdMap[id]};
            }
            MeshImporter const importer(path);
            if(!importer.ImportSucceeded()) 
            {
                Q3D_ERROR("Error loading mesh into the mesh library cache: {0}",path.string());
                return {0,{}};
            }
            s_MeshIdMap[id] = *importer;
            return {id, *importer};
        }

        std::optional<MeshAssetContent> MeshLibrary::CheckedCopy(MeshAssetId id)
        {
            return MeshLibrary::IsLoaded(id) ? std::optional<MeshAssetContent>(s_MeshIdMap[id]) : std::nullopt;
        }

        void MeshLibrary::Remove(MeshAssetId id)
        {
            s_MeshIdMap.erase(id);
        }

        bool MeshLibrary::IsLoaded(MeshAssetId id)
        {
            return s_MeshIdMap.find(id) != s_MeshIdMap.end();
        }

        MeshAssetId MeshLibrary::GetIdFromPath(const fls::path &path)
        {
            return std::filesystem::hash_value(path);
        }

        MeshAssetContent& MeshLibrary::Retrieve(MeshAssetId id)
        {
            return s_MeshIdMap[id];
        }

        MeshAssetContent&& MeshLibrary::Move(MeshAssetId id)
        {
            auto&& data = std::move(s_MeshIdMap[id]);
            MeshLibrary::Remove(id);
            return std::move(data);
        }

        MeshAssetContent MeshLibrary::Copy(MeshAssetId id)
        {
            return s_MeshIdMap[id];
        }
    }
} // namespace Q3D
