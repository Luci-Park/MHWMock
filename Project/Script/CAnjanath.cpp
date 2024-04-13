#include "pch.h"
#include "CAnjanath.h"
#include <Engine/CTimeMgr.h>
#include <Engine/IAnimationState.h>

CAnjanath::CAnjanath()
	:CScript(SCRIPT_TYPE::ANJANATH)
	, m_pPlayer(nullptr)
	, m_fRotateSpeed(90.f)
	, m_iMaxHP(3500)
	, m_iHP(3500)
	, m_bStagger(false)
{
	m_pPicker = new AnjActionPicker(this);

	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fRotateSpeed, "Rotate Speed");
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pPlayer, "Player");
}

CAnjanath::~CAnjanath()
{
	delete m_pPicker;
}

void CAnjanath::AttackHit(SCRIPT_TYPE _type, CMainPlayerScript* _player)
{
	if (m_pCurrentAction) m_pCurrentAction->OnAttack(_type, _player);
}

void CAnjanath::OnDamaged(int _damge)
{
	m_iHP -= _damge;
	Animator3D()->SetInt(L"HP", m_iHP);
	Animator3D()->SetBool(L"Aggroed", true);
}

void CAnjanath::OnPickAction(ANJ_ACTION _action)
{
	if (m_pCurrentAction != nullptr) m_pCurrentAction->AttackEnd();

	m_pCurrentAction = m_pPicker->PickAction(_action);
	REPOS_DIR dir = m_pCurrentAction->TurnDir();
	Animator3D()->SetInt(L"Action Type", (int)m_pCurrentAction->GetType());
	Animator3D()->SetInt(L"Turn Dir", (int)dir);
	bool move = m_pCurrentAction->KeepMoving();
	Animator3D()->SetTrigger(L"Stop Move", move);

	m_bStagger = false;
}

void CAnjanath::RotateTowardsPlayer()
{
	Vec3 playerPos = m_pPlayer->Transform()->GetWorldPos();
	Vec3 myPos = Transform()->GetWorldPos();
	playerPos.y = 0; myPos.y = 0;
	Vector3 front = Transform()->GetWorldDir(DIR_TYPE::FRONT) * -1;
	Vector3 playerDir = (playerPos - myPos).Normalize();
	float angle = Angles(front, playerDir);
	Vector3 rotation = Transform()->GetRelativeEulerRot();
	if (angle > 5.f)
		rotation.y += (front.Cross(playerDir).y < 0 ? -1 : 1) * m_fRotateSpeed * CTimeMgr::GetInst()->GetDeltaTime();
	else
		rotation.y += (front.Cross(playerDir).y < 0 ? -1 : 1) * angle;
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

void CAnjanath::LookAtPlayer()
{
	float angle = GetAngleBetweenPlayer();
	Vector3 rotation = Transform()->GetRelativeEulerRot();
	rotation.y += angle;
	Transform()->SetRelativeRot(rotation);
}

void CAnjanath::tick()
{
	double percentage;
	auto clip = Animator3D()->GetCurrentAnimation(percentage);
	if (clip != nullptr&& clip->GetName() == L"Animation 036") RotateTowardsPlayer();
	if (m_pCurrentAction)
	{
		bool move = m_pCurrentAction->KeepMoving();
		Animator3D()->SetTrigger(L"Stop Move", move);
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
	if (_pState->GetType() == eAnimationNodeType::State && _pState->GetName() == L"Check Action")
	{
		OnPickAction();
	}
	if (_pState->GetClip() != nullptr && m_pCurrentAction != nullptr)
		m_pCurrentAction->OnAnimationStart(_pState->GetClip()->GetName());
}

void CAnjanath::OnAnimationEndStart(IAnimationState* _pState)
{
	if (_pState->GetClip() != nullptr && m_pCurrentAction != nullptr)
		m_pCurrentAction->OnAnimationEnd(_pState->GetClip()->GetName());
	if (_pState->GetType() == eAnimationNodeType::State && _pState->GetName() == L"Check Action")
	{
		m_pCurrentAction = nullptr;
	}
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