#include "Projection.h"

namespace Q3D
{
    namespace Math
    {
        auto ProjectPerspective(const Vector4f& pos) -> Vector2f
        {
            return Vector2f{pos[0] * 640.0f / pos[2], pos[1] * 640.0f / pos[2]};
        }
    } // namespace Math
    
} // namespace Q3D
