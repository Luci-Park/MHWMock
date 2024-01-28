#pragma once
#include "pch.h"
#include "assimp/scene.h"

inline Matrix aiMatToMat(const aiMatrix4x4& _aiMat)
{
	Matrix mat;
	std::memcpy(&mat, &_aiMat, sizeof(aiMatrix4x4));
	mat.Transpose();
	return mat;
}

inline Vec3 aiVec3ToVec3(const aiVector3D& _aiVec3)
{
	return Vec3
	{
		_aiVec3.x,
		_aiVec3.y,
		_aiVec3.z,
	};
}

inline Vec3 aiColor4ToVec4(const aiColor4D& _aiColor)
{
	return Vec4
	{
		_aiColor.r,
		_aiColor.g,
		_aiColor.b,
		_aiColor.a,
	};
}

inline Quaternion aiQuatToQuat(const aiQuaternion& _aiQuat)
{
	return Quaternion
	{
		_aiQuat.x,
		_aiQuat.y,
		_aiQuat.z,
		_aiQuat.w,
	};
}