#include "pch.h"
#include "CPlayerCameraScript.h"

CPlayerCameraScript::CPlayerCameraScript()
	: CScript((UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT)
	, m_pTargetObj(nullptr)
	, m_fRadius(500.f)
	, m_fRotationSpeed(60.f)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fRadius, "Radius");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fRotationSpeed, "RotationSpeed");
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pTargetObj, "Target Obj");
}

CPlayerCameraScript::~CPlayerCameraScript()
{
}

void CPlayerCameraScript::begin()
{
	if (m_pTargetObj != nullptr)
	{
		Vector3 vObjPos = m_pTargetObj->Transform()->GetRelativePos();
		Vec3 vObjFront = m_pTargetObj->Transform()->GetRelativeDir(DIR_TYPE::FRONT);

		Vec3 vPos = Transform()->GetRelativePos();
		Vec3 vFront = Transform()->GetRelativeDir(DIR_TYPE::FRONT);
		Quaternion qRot = Transform()->GetRelativeRot();
		Vec3 vRot = qRot.ToEuler();

		vPos = vObjPos - vObjFront * m_fRadius;

		//Transform()->SetRelativeRot(vRot);
		Transform()->SetRelativePos(vPos);
	}
}

void CPlayerCameraScript::tick()
{
	if (CKeyMgr::GetInst()->GetKeyState(KEY::P) == KEY_STATE::PRESSED)
	{
	}
	else
	{

		if (m_pTargetObj != nullptr)
		{
			Vector3 vObjPos;
			vObjPos = m_pTargetObj->Transform()->GetRelativePos();

			Vec3 vPos = Transform()->GetRelativePos();
			Quaternion qRot = Transform()->GetRelativeRot();
			Vec3 vRot = qRot.ToEuler();

			Vec3 vFront = Transform()->GetRelativeDir(DIR_TYPE::FRONT);
			Vec3 vUp = Transform()->GetRelativeDir(DIR_TYPE::UP);
			Vec3 vRight = Transform()->GetRelativeDir(DIR_TYPE::RIGHT);

			Vec2 vMouseDir = CKeyMgr::GetInst()->GetMouseDir();

			vRot.y += DT * vMouseDir.x * m_fRotationSpeed;
			vRot.x -= DT * vMouseDir.y * m_fRotationSpeed;

			//if (vMouseDir.x == 0 && vMouseDir.y == 0)
			//{
			//	vRot = Vec3(0.0f, vRot.y, 0.0f);
			//}

			vPos = vObjPos - vFront * m_fRadius;

			Transform()->SetRelativePos(vPos);
			Transform()->SetRelativeRot(vRot);
		}
	}
}

void CPlayerCameraScript::SaveToLevelFile(FILE* _File)
{
}

void CPlayerCameraScript::LoadFromLevelFile(FILE* _FILE)
{
}