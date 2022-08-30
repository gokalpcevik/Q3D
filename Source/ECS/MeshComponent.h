#pragma once
#include <cstdint>
#include "../Graphics/Types.h"
#include "../AssetCore/MeshLibrary.h"

namespace Q3D
{
    namespace ECS
    {
        struct MeshComponent
        {
            AssetCore::MeshAssetId MeshAssetId = 0;
            uint32_t Color = 0xFFFF00F0;
        };
    } // namespace ECS
    
} // namespace Q3D
