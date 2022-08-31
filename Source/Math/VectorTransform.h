#pragma once
#include <Eigen/Eigen>

namespace Q3D
{
	using Eigen::Vector3f;
	using Eigen::Vector4f;
	using Eigen::Matrix4f;

	namespace Math
	{
		auto RotateZ(const Vector4f& pos, float rot)->Vector4f;
		auto RotateY(const Vector4f& pos, float rot)->Vector4f;
		auto RotateX(const Vector4f& pos, float rot)->Vector4f;
		auto RotateZ(float Rz)-> Matrix4f;
		auto RotateY(float Ry)-> Matrix4f;
		auto RotateX(float Rx)-> Matrix4f;
		auto Scale(float Sx,float Sy,float Sz)->Matrix4f;
		auto Scale(const Vector3f& scale)->Matrix4f;
		auto Translate(float Tx, float Ty, float Tz)->Matrix4f;
		auto Translate(const Vector3f& translation)->Matrix4f;
	}
}
