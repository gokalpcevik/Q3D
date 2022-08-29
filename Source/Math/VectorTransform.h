#pragma once
#include <Eigen/Eigen>

namespace Q3D
{
	using Eigen::Vector4f;
	using Eigen::Matrix4f;

	namespace Math
	{
		auto RotateZ(const Vector4f& pos, float rot)->Vector4f;
		auto RotateY(const Vector4f& pos, float rot)->Vector4f;
		auto RotateX(const Vector4f& pos, float rot)->Vector4f;
		auto MatrixScale(float Sx,float Sy,float Sz)->Matrix4f;
	}
}
