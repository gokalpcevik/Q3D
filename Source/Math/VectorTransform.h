#pragma once
#include <Eigen/Eigen>

namespace Q3D
{
	using Eigen::Vector3f;

	namespace Math
	{
		auto RotateZ(const Vector3f& pos, float rot)->Vector3f;
		auto RotateY(const Vector3f& pos, float rot)->Vector3f;
		auto RotateX(const Vector3f& pos, float rot)->Vector3f;
	}
}
