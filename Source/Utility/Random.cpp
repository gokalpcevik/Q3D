#include "Random.h"

namespace Q3D
{
    namespace Util
    {
        int64_t Random::RandomInt64()
        {
            std::random_device rd;
            std::mt19937_64 mte(rd());

            std::uniform_int_distribution<int64_t> dist(std::numeric_limits<int64_t>::min(),std::numeric_limits<int64_t>::max());
            return dist(mte);
        }

        uint64_t Random::RandomUInt64()
        {
            std::random_device rd;
            std::mt19937_64 mte(rd());

            std::uniform_int_distribution<uint64_t> dist(std::numeric_limits<uint64_t>::min(),std::numeric_limits<uint64_t>::max());
            return dist(mte);
        }
        
    } // namespace Util
    
} // namespace Q3D
