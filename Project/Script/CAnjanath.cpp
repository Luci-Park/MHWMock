#include "pch.h"
#include "CAnjanath.h"
#include <Engine/CTimeMgr.h>
#include <Engine/IAnimationState.h>

CAnjanath::CAnjanath()
	:CScript(SCRIPT_TYPE::ANJANATH)
	, m_pPlayer(nullptr)
{
	m_pPicker = new AnjActionPicker(this);

	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fRotateSpeed, "Rotate Speed");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fDistance, "Distance");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fAngle, "Angle");
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pPlayer, "Player");
}

CAnjanath::~CAnjanath()
{
	delete m_pPicker;
}

void CAnjanath::OnPickAction(ANJ_ACTION _action)
{
	m_pCurrentAction = m_pPicker->PickAction(_action);
	REPOS_DIR dir = m_pCurrentAction->TurnDir();
	m_bMoving = m_pCurrentAction->KeepMoving();
	Animator3D()->SetInt(L"Action Type", (int)_action);
	Animator3D()->SetInt(L"Turn Dir", (int)dir);
	if (!m_bMoving) Animator3D()->SetTrigger(L"Stop Move");
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
	if (m_fAngle > 5.f)
		rotation.y += (front.Cross(playerDir).y < 0 ? -1 : 1) * m_fRotateSpeed * CTimeMgr::GetInst()->GetDeltaTime();
	else
		rotation.y += (front.Cross(playerDir).y < 0 ? -1 : 1) * m_fAngle;
	Transform()->SetRelativeRot(rotation);
}

float CAnjanath::GetAngleBetweenPlayer()
{
	Vec3 playerPos = m_pPlayer->Transform()->GetWorldPos();
	Vec3 myPos = Transform()->GetWorldPos();
	playerPos.y = 0; myPos.y = 0;
	Vector3 front = Transform()->GetWorldDir(DIR_TYPE::FRONT) * -1;
	Vector3 playerDir = (playerPos - myPos).Normalize();
	return Angles(front, playerDir) * (front.Cross(playerDir).y < 0 ? -1 : 1);
}

float CAnjanath::GetDistanceBetweenPlayer()
{
	Vec3 playerPos = m_pPlayer->Transform()->GetWorldPos();
	Vec3 myPos = Transform()->GetWorldPos();
	playerPos.y = 0; myPos.y = 0;
	return Vector3::Distance(playerPos, myPos);
}

void CAnjanath::tick()
{
	if (m_bMoving) RotateTowardsPlayer();
	if (m_pCurrentAction && m_bMoving)
	{
		m_bMoving = m_pCurrentAction->KeepMoving();
		if(!m_bMoving) Animator3D()->SetTrigger(L"Stop Move");
	}
}
void CAnjanath::OnAnimationBegin(IAnimationState* _pState)
{
	if (_pState->GetType() == eAnimationNodeType::StateMachine && _pState->GetName() == L"Aggroed")
	{		
		OnPickAction(ANJ_ACTION::ROAR);
	}
	if (_pState->GetType() == eAnimationNodeType::StateMachine && _pState->GetName() == L"Action")
	{
		OnPickAction();
	}

}

void CAnjanath::OnAnimationEndStart(IAnimationState* _pState)
{
}

void CAnjanath::OnAnimationEndFinished(IAnimationState* _pState)
{
}


void CAnjanath::SaveToLevelFile(FILE* _File)
{
	SaveGameObjectParam(m_pPlayer, _File);
}

void CAnjanath::LoadFromLevelFile(FILE* _FILE)
{
	LoadGameObjectParam(0, _FILE);
}