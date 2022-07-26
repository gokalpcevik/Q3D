#include "VectorTransform.h"

namespace Q3D
{
	namespace Math
	{
		auto RotateZ(const Vector3f& pos, float rot) -> Vector3f
		{
			Vector3f newPos = {};
			newPos[0] = pos[0] * std::cosf(rot) - pos[1] * std::sinf(rot);
			newPos[1] = pos[0] * std::sinf(rot) + pos[1] * std::cosf(rot);
			newPos[2] = pos[2];
			return newPos;
		}

		auto RotateY(const Vector3f& pos, float rot) -> Vector3f
		{
			Vector3f newPos = {};
			newPos[0] = pos[0] * std::cosf(rot) - pos[2] * std::sinf(rot);
			newPos[1] = pos[1];
			newPos[2] = pos[0] * std::sinf(rot) + pos[2] * std::cosf(rot);
			return newPos;
		}

		auto RotateX(const Vector3f& pos, float rot) -> Vector3f
		{
			Vector3f newPos = {};
			newPos[0] = pos[0];
			newPos[1] = pos[1] * std::cosf(rot) - pos[2] * std::sinf(rot);
			newPos[2] = pos[1] * std::sinf(rot) + pos[2] * std::cosf(rot);
			return newPos;
		}
	}
}
