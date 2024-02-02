#ifndef __Assimp
#define __Assimp

#include "pch.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Matrix aiMatToMat(const aiMatrix4x4& _aiMat)
{
	Matrix mat;
	memcpy(&mat, &_aiMat, sizeof(aiMatrix4x4));
	return mat.Transpose();
}

Vec3 aiVec3ToVec3(const aiVector3D& _aiV3)
{
	return Vec3(_aiV3.x, _aiV3.y, _aiV3.z);
}

Quaternion aiQuatToQuat(const aiQuaternion& _aiQuat)
{
	return Quaternion(_aiQuat.x, _aiQuat.y, _aiQuat.z, _aiQuat.w);
}

Vec4 aiColorToVec4(const aiColor4D& _aiCol)
{
	return Vec4(_aiCol.r, _aiCol.g, _aiCol.b, _aiCol.a);
}

Color aiColorToColor(const aiColor4D& _aiCol)
{
	return Color(_aiCol.r, _aiCol.g, _aiCol.b, _aiCol.a);
}

wstring aiStrToWstr(const aiString& _aiStr)
{
	string str = _aiStr.C_Str();
	return wstring(str.begin(), str.end());
}
#endif // ! __Assimp
