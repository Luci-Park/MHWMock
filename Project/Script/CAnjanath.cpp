#include "pch.h"
#include "CAnjanath.h"


CAnjanath::CAnjanath()
	:CScript(SCRIPT_TYPE::ANJANATH)
	, m_pPlayer(nullptr)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fRotateSpeed, "Rotate Speed");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fDistance, "Distance");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fAngle, "Angle");
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pPlayer, "Player");
}

CAnjanath::~CAnjanath()
{
}


void CAnjanath::RotateTowardsPlayer()
{
	Vec3 playerPos = m_pPlayer->Transform()->GetWorldPos();
	Vec3 myPos = Transform()->GetWorldPos();
	playerPos.y = 0; myPos.y = 0;
	Vector3 front = Transform()->GetWorldDir(DIR_TYPE::FRONT) * -1;
	Vector3 playerDir = (playerPos - myPos).Normalize();
	m_fAngle = Angles(front, playerDir);
	Vector3 rotation = Transform()->GetRelativeEulerRot();
	rotation.y += m_fAngle * (front.Cross(playerDir).y < 0 ? -1 : 1);

	Transform()->SetRelativeRot(rotation);


}

void CAnjanath::tick()
{
	m_fDistance = Vector3::Distance(m_pPlayer->Transform()->GetWorldPos(), Transform()->GetWorldPos());
	RotateTowardsPlayer();

	//if (m_fDistance >= 100)
	//{
	//	Animator3D()->SetTrigger(L"Stop Move");
	//}
}

void CAnjanath::SaveToLevelFile(FILE* _File)
{
	SaveGameObjectParam(m_pPlayer, _File);
}

void CAnjanath::LoadFromLevelFile(FILE* _FILE)
{
	LoadGameObjectParam(0, _FILE);
}