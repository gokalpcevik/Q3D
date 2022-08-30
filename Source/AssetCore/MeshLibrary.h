#pragma once
#include <filesystem>
#include <unordered_map>
#include <tuple>
#include <optional>
#include "MeshImporter.h"
#include "../Core/Log.h"

namespace Q3D
{
    namespace AssetCore
    {
        using MeshAssetId = size_t;

        namespace fls = std::filesystem;

        // Not needed but keeping it for now.
        struct FlsPathHashFn
        {
            auto operator()(const std::filesystem::path &path) const -> std::size_t
            {
                return std::filesystem::hash_value(path);
            }
        };

        class MeshLibrary
        {
        public:
            MeshLibrary() = default;
            MeshLibrary(const MeshLibrary &) = delete;

            // USAGE NOTE: Check the imported mesh data vector sizes to confirm the import succeded.
            static std::tuple<MeshAssetId,MeshAssetContent> Load(const fls::path &path);
            static std::optional<MeshAssetContent> CheckedCopy(MeshAssetId id);
            static void Remove(MeshAssetId id);
            static bool IsLoaded(MeshAssetId id);
            static MeshAssetId GetIdFromPath(const fls::path& path);
            static MeshAssetContent& Retrieve(MeshAssetId id);
            static MeshAssetContent&& Move(MeshAssetId id);
            static MeshAssetContent Copy(MeshAssetId id);
        private:
            static std::unordered_map<MeshAssetId, MeshAssetContent> s_MeshIdMap;
        };
    }

} // namespace Q3D
