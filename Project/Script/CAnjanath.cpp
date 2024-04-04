#include "pch.h"
#include "CAnjanath.h"
#include <Engine/CAnimator3D.h>
#include "CMainPlayerScript.h"

CAnjanath::CAnjanath()
	: CScript(SCRIPT_TYPE::ANJANATH)
#pragma region Keys
	, aggroed(L"Aggroed")
	, turnDir(L"Turn Dir")
	, stopMove(L"Stop Move")
	, attackType(L"Attack Type")
	, hp(L"HP")
	, stagger(L"Stagger")
	, staggerType(L"Stagger Type")
	, rage(L"Rage")
	, rageNum(L"Rage Number")
	, m_iMaxHP(3528)
	, m_iMaxRage(370)
#pragma endregion
	, m_iHP(3528)
	, m_State(ANJ_STATE::PEACE)
	, m_iRageGauge(150)
	, m_iRageNumber(0)
	, m_bTailCut(false)
{
	m_pAttackPicker = new AnjAttackPicker(this);
	//AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pNose, "Nose");
	//AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pWings, "Wing");
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pPlayer, "Player");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &testangle, "Angle");
}

CAnjanath::~CAnjanath()
{
	delete m_pAttackPicker;
}

void CAnjanath::Aggroed()
{
	Animator3D()->SetBool(aggroed, true);
	float angle = GetPlayerAngle();
	//if at front
	//if at left = left
	//if at back = left back
	//if at right = right
	// if small, small and instant rotate
}

void CAnjanath::begin()
{
	Animator3D()->SetBool(aggroed, false);
	return;
	m_pNose->SetActive(false);
	m_pWings->SetActive(false);
}

void CAnjanath::tick()
{
	//testangle = GetPlayerAngle();
	if (ANJ_STATE::PEACE == m_State) return;
	if (m_iHP <= 0) return;
	if (m_pCurrentAttack) m_pCurrentAttack->AttackTick(); // set dir, Move

}

void CAnjanath::ChooseAttack()
{
	if (m_iRageGauge <= 0)
	{
		EnRage();
		return;
	}
	m_pCurrentAttack = m_pAttackPicker->PickAttack();
	m_pCurrentAttack->AttackStart();
	Animator3D()->SetInt(attackType, (int)m_pCurrentAttack->GetType());

}

void CAnjanath::EnRage()
{
	m_iRageGauge = m_iMaxRage;
	m_iRageNumber += 1;
	Animator3D()->SetTrigger(rage);
	Animator3D()->SetInt(rageNum, m_iRageNumber);
}

void CAnjanath::Death()
{
	m_pNose->SetActive(false);
	m_pWings->SetActive(false);
}

void CAnjanath::CheckWing(IAnimationState* _currentState, bool _start)
{
	const vector<wstring> startanims = { L"model\\anjanath\\anim\\Animation 001.004.anim", 
		L"model\\anjanath\\anim\\Animation 144.anim"};
	const vector<wstring> endanims = { L"model\\anjanath\\anim\\Animation 146.anim", };
	if (_start)
	{
		for (int i = 0; i < startanims.size(); i++)
		{
			if (startanims[i] == _currentState->GetClip()->GetKey()) 
			{
				Wing(true);
				break;
			}
		}
	}
	else
	{
		for (int i = 0; i < endanims.size(); i++)
		{
			if (endanims[i] == _currentState->GetClip()->GetKey())
			{
				Wing(false);
				break;
			}
		}
	}
}

void CAnjanath::CheckNose(IAnimationState* _currentState, bool _start)
{
	const vector<wstring> startanims = { L"model\\anjanath\\anim\\Animation 021.002.anim", };
	const vector<wstring> endanims = { };
	if (_start)
	{
		for (int i = 0; i < startanims.size(); i++)
		{
			if (startanims[i] == _currentState->GetClip()->GetKey())
			{
				Nose(true);
				break;
			}
		}
	}
	else
	{
		for (int i = 0; i < endanims.size(); i++)
		{
			if (endanims[i] == _currentState->GetClip()->GetKey())
			{
				Nose(false);
				break;
			}
		}
	}
}

void CAnjanath::StopAttack()
{
	if (m_pCurrentAttack)
	{
		m_pCurrentAttack->AttackEnd();
		m_pCurrentAttack = nullptr;
	}
}

void CAnjanath::Attacked(int _damage)
{
	if (ANJ_STATE::PEACE == m_State)
		Aggroed();
	m_iHP -= _damage;
	Animator3D()->SetInt(hp, m_iHP);
	if (m_iHP <= 0)
	{
		Death();
		return;
	}
	m_iRageGauge -= _damage;
}

void CAnjanath::AttackSuccess(SCRIPT_TYPE _type, CMainPlayerScript* _player)
{
	if (!m_pCurrentAttack) return;
	m_pCurrentAttack->AttackSuccess(_type, _player);
}

void CAnjanath::NoseBreak()
{
	m_State = ANJ_STATE::STAGGER;
	Animator3D()->SetTrigger(stagger);
	Animator3D()->SetInt(staggerType, 0);
	Nose(false);
}

void CAnjanath::FallOver()
{
	m_State = ANJ_STATE::STAGGER;
	Animator3D()->SetTrigger(stagger);
	Animator3D()->SetInt(staggerType, 1);
}

void CAnjanath::TailCut()
{
	m_bTailCut = true;
	m_State = ANJ_STATE::STAGGER;
	Animator3D()->SetTrigger(stagger);
	Animator3D()->SetInt(staggerType, 1);
}

void CAnjanath::BodyShot()
{
	m_State = ANJ_STATE::STAGGER;
	Animator3D()->SetTrigger(stagger);
	Animator3D()->SetInt(staggerType, 0);
}

void CAnjanath::Nose(bool _show)
{
	if(m_pNose)
		m_pNose->SetActive(_show);
}

void CAnjanath::Wing(bool _show)
{
	if(m_pWings)
		m_pWings->SetActive(_show);
}

float CAnjanath::GetPlayerAngle()
{
	Vec3 playerPos = m_pPlayer->Transform()->GetWorldPos();
	Vec3 selfPos = Transform()->GetWorldPos();
	Vec3 forward = Transform()->GetWorldDir(DIR_TYPE::FRONT);
	Vec3 direction = playerPos - selfPos;
	direction.Normalize();

	float dot = forward.Dot(direction);
	float cross = forward.Cross(direction).Length();
	float radian = std::atan2(cross, dot);

	float degrees = XMConvertToDegrees(radian);

	// Adjust degrees to be between -180 and 180
	while (degrees > 180.0f)
		degrees -= 360.0f;
	while (degrees < -180.0f)
		degrees += 360.0f;
	return degrees;
}

float CAnjanath::GetPlayerDist()
{
	return (m_pPlayer->Transform()->GetWorldPos() - Transform()->GetWorldPos()).Length();
}

Vec3 CAnjanath::GetPlayerPos()
{
	return m_pPlayer->Transform()->GetWorldPos();
}

void CAnjanath::OnAnimationBegin(IAnimationState* _pState)
{
	if (_pState->GetType() == eAnimationNodeType::StateMachine && _pState->GetName() == L"Attack")	ChooseAttack();
}

void CAnjanath::OnAnimationEndStart(IAnimationState* _pState)
{
	if (_pState->GetType() == eAnimationNodeType::StateMachine && _pState->GetName() == L"Attack")StopAttack();
}

void CAnjanath::OnAnimationEndFinished(IAnimationState* _pState)
{
}

void CAnjanath::SaveToLevelFile(FILE* _File)
{
	SaveGameObjectParam(m_pPlayer, _File);
}

void CAnjanath::LoadFromLevelFile(FILE* _File)
{
	LoadGameObjectParam(0, _File);
}
