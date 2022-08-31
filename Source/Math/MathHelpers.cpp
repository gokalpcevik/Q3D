#include "MathHelpers.h"

namespace Q3D
{
    namespace Math
    {
        bool IsNearlyEqual(float a,float b)
        {
            return std::abs( a - b ) < std::numeric_limits<float>::epsilon();
        }
    } // namespace Math
    
} // namespace Q3D
