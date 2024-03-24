#include "pch.h"
#include "CPlayerCameraScript.h"

CPlayerCameraScript::CPlayerCameraScript()
	: CScript((UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT)
	, m_pTargetObj(nullptr)
	, m_fRadius(500.f)
{
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pTargetObj, "Target Obj");
}

CPlayerCameraScript::~CPlayerCameraScript()
{
}

void CPlayerCameraScript::begin()
{
	if (m_pTargetObj != nullptr)
	{
		Vector3 vTargetPos = m_pTargetObj->Transform()->GetRelativePos();
		GetOwner()->Transform()->SetRelativePos(vTargetPos);
	}
}

void CPlayerCameraScript::tick()
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

		if (KEY_PRESSED(KEY::RBTN))
		{
			Vec2 vMouseDir = CKeyMgr::GetInst()->GetMouseDir();
			vRot.y += DT * vMouseDir.x * 180.f;
			vRot.x -= DT * vMouseDir.y * 180.f;
		}
		// vFront 방향으로 distance 거리를 유지합니다.
		vPos = vObjPos - vFront * m_fRadius;

		Transform()->SetRelativePos(vPos);
		Transform()->SetRelativeRot(vRot);
	}
}

void CPlayerCameraScript::SaveToLevelFile(FILE* _File)
{
}

void CPlayerCameraScript::LoadFromLevelFile(FILE* _FILE)
{
}