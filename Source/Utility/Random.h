#pragma once
#include <random>

namespace Q3D
{
    namespace Util
    {

        // Probably not a very good random implementation but it does the job for now.
        class Random
        {
        public:
            Random() = default;
            static int64_t RandomInt64();
            static uint64_t RandomUInt64();
        };
    } // namespace Util
    
} // namespace Q3D
