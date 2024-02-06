#include "pch.h"
#include "SimpleMath.h"

const Vector2 Vector2::Zero = { 0.f, 0.f };
const Vector2 Vector2::One = { 1.f, 1.f };
const Vector2 Vector2::UnitX = { 1.f, 0.f };
const Vector2 Vector2::UnitY = { 0.f, 1.f };

const Vector3 Vector3::Zero = { 0.f, 0.f, 0.f };
const Vector3 Vector3::One = { 1.f, 1.f, 1.f };
const Vector3 Vector3::UnitX = { 1.f, 0.f, 0.f };
const Vector3 Vector3::UnitY = { 0.f, 1.f, 0.f };
const Vector3 Vector3::UnitZ = { 0.f, 0.f, 1.f };
const Vector3 Vector3::Up = { 0.f, 1.f, 0.f };
const Vector3 Vector3::Down = { 0.f, -1.f, 0.f };
const Vector3 Vector3::Right = { 1.f, 0.f, 0.f };
const Vector3 Vector3::Left = { -1.f, 0.f, 0.f };
const Vector3 Vector3::Forward = { 0.f, 0.f, 1.f };
const Vector3 Vector3::Backward = { 0.f, 0.f, -1.f };

const Vector4 Vector4::Zero = { 0.f, 0.f, 0.f, 0.f };
const Vector4 Vector4::One = { 1.f, 1.f, 1.f, 1.f };
const Vector4 Vector4::UnitX = { 1.f, 0.f, 0.f, 0.f };
const Vector4 Vector4::UnitY = { 0.f, 1.f, 0.f, 0.f };
const Vector4 Vector4::UnitZ = { 0.f, 0.f, 1.f, 0.f };
const Vector4 Vector4::UnitW = { 0.f, 0.f, 0.f, 1.f };

const Matrix Matrix::Identity = { 1.f, 0.f, 0.f, 0.f,
								  0.f, 1.f, 0.f, 0.f,
								  0.f, 0.f, 1.f, 0.f,
								  0.f, 0.f, 0.f, 1.f };

const Quaternion Quaternion::Identity = { 0.f, 0.f, 0.f, 1.f };

void Quaternion::FromToRotation(const Vector3& fromDir, const Vector3& toDir, Quaternion& result) noexcept
{
	// Melax, "The Shortest Arc Quaternion", Game Programming Gems, Charles River Media (2000).

	const XMVECTOR F = XMVector3Normalize(fromDir);
	const XMVECTOR T = XMVector3Normalize(toDir);

	const float dot = XMVectorGetX(XMVector3Dot(F, T));
	if (dot >= 1.f)
	{
		result = Identity;
	}
	else if (dot <= -1.f)
	{
		XMVECTOR axis = XMVector3Cross(F, Vector3::Right);
		if (XMVector3NearEqual(XMVector3LengthSq(axis), g_XMZero, g_XMEpsilon))
		{
			axis = XMVector3Cross(F, Vector3::Up);
		}

		const XMVECTOR Q = XMQuaternionRotationAxis(axis, XM_PI);
		XMStoreFloat4(&result, Q);
	}
	else
	{
		const XMVECTOR C = XMVector3Cross(F, T);
		XMStoreFloat4(&result, C);

		const float s = sqrtf((1.f + dot) * 2.f);
		result.x /= s;
		result.y /= s;
		result.z /= s;
		result.w = s * 0.5f;
	}
}

void Quaternion::LookRotation(const Vector3& forward, const Vector3& up, Quaternion& result) noexcept
{
	Quaternion q1;
	FromToRotation(Vector3::Forward, forward, q1);

	const XMVECTOR C = XMVector3Cross(forward, up);
	if (XMVector3NearEqual(XMVector3LengthSq(C), g_XMZero, g_XMEpsilon))
	{
		// forward and up are co-linear
		result = q1;
		return;
	}
}

