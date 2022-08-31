#include "VectorTransform.h"

namespace Q3D
{
	namespace Math
	{
		auto RotateZ(const Vector4f& pos, float rot) -> Vector4f
		{
			Vector4f newPos = {};
			newPos[0] = pos[0] * std::cosf(rot) - pos[1] * std::sinf(rot);
			newPos[1] = pos[0] * std::sinf(rot) + pos[1] * std::cosf(rot);
			newPos[2] = pos[2];
			newPos[3] = pos[3];
			return newPos;
		}

		auto RotateY(const Vector4f& pos, float rot) -> Vector4f
		{
			Vector4f newPos = {};
			newPos[0] = pos[0] * std::cosf(rot) - pos[2] * std::sinf(rot);
			newPos[1] = pos[1];
			newPos[2] = pos[0] * std::sinf(rot) + pos[2] * std::cosf(rot);
			newPos[3] = pos[3];
			return newPos;
		}

		auto RotateX(const Vector4f& pos, float rot) -> Vector4f
		{
			Vector4f newPos = {};
			newPos[0] = pos[0];
			newPos[1] = pos[1] * std::cosf(rot) - pos[2] * std::sinf(rot);
			newPos[2] = pos[1] * std::sinf(rot) + pos[2] * std::cosf(rot);
			newPos[3] = pos[3];
			return newPos;
		}

		auto Scale(float Sx,float Sy,float Sz) -> Matrix4f
		{
			Matrix4f mat;
			mat.row(0) << Sx,  0.0f,0.0f,0.0f;
			mat.row(1) << 0.0f,Sy,  0.0f,0.0f;
			mat.row(2) << 0.0f,0.0f,Sz,  0.0f;
			mat.row(3) << 0.0f,0.0f,0.0f,1.0f;
			return mat;
		}

		auto Translate(float Tx, float Ty, float Tz) -> Matrix4f
		{
			Matrix4f mat;
			mat.row(0) << 1.0f,0.0f,0.0f,Tx;
			mat.row(1) << 0.0f,1.0f,0.0f,Ty;
			mat.row(2) << 0.0f,0.0f,1.0f,Tz;
			mat.row(3) << 0.0f,0.0f,0.0f,1.0f;
			return mat;
		}

		auto Translate(const Vector3f& translation) -> Matrix4f
		{
			Matrix4f mat;
			mat.row(0) << 1.0f,0.0f,0.0f,translation[0];
			mat.row(1) << 0.0f,1.0f,0.0f,translation[1];
			mat.row(2) << 0.0f,0.0f,1.0f,translation[2];
			mat.row(3) << 0.0f,0.0f,0.0f,1.0f;
			return mat;
		}
	}
}
