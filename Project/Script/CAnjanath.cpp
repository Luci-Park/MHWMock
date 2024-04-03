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
	, m_iRageGauge(150)
	, m_iRageNumber(0)
	, m_bAggroed(false)
	, m_bStaggered(false)
	, m_bTailCut(false)
{
	m_pAttackPicker = new AnjAttackPicker(this);
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pNose, "Nose");
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pWings, "Wing");
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pPlayer, "Player");
}

CAnjanath::~CAnjanath()
{
	delete m_pAttackPicker;
}

void CAnjanath::CheckPlayerPos()
{
	if (m_pPlayer == nullptr) return;
	Vec3 relativePos = m_pPlayer->Transform()->GetWorldPos() - Transform()->GetWorldPos();
	Quaternion lookRotation;
	Quaternion::LookRotation(relativePos, Vector3::Up, lookRotation);
	Vec3 angles = lookRotation.ToEuler();


}

void CAnjanath::ChooseAttack()
{
	Animator3D()->SetInt(attackType, (int)ANJ_ATTACK::BITE);
}

void CAnjanath::EnRage()
{
}

void CAnjanath::Death()
{
	m_pNose->SetActive(false);
	m_pWings->SetActive(false);
}

void CAnjanath::Attacked(int _damage)
{
	if (!m_bAggroed)
	{
		m_bAggroed = true;
		Animator3D()->SetBool(aggroed, true);
	}
	m_iHP -= _damage;
	Animator3D()->SetInt(hp, m_iHP);
	if (m_iHP <= 0)
	{
		Death();
		return;
	}
	m_iRageGauge -= _damage;
	if (m_iRageGauge <= 0)
	{
		m_iRageGauge = m_iMaxRage;
		m_iRageNumber += 1;
		Animator3D()->SetTrigger(rage);
		Animator3D()->SetInt(rageNum, m_iRageNumber);
	}
}

void CAnjanath::AttackSuccess(SCRIPT_TYPE _type, CMainPlayerScript* _player)
{
	if (!m_pCurrentAttack) return;
	m_pCurrentAttack->AttackSuccess(_type, _player);
}

void CAnjanath::NoseBreak()
{
	m_bStaggered = true;
	Animator3D()->SetTrigger(stagger);
	Animator3D()->SetInt(staggerType, 0);
	Nose(false);
}

void CAnjanath::FallOver()
{
	m_bStaggered = true;
	Animator3D()->SetTrigger(stagger);
	Animator3D()->SetInt(staggerType, 1);
}

void CAnjanath::TailCut()
{
	m_bTailCut = true;
	m_bStaggered = true;
	Animator3D()->SetTrigger(stagger);
	Animator3D()->SetInt(staggerType, 1);
}

void CAnjanath::BodyShot()
{
	m_bStaggered = true;
	Animator3D()->SetTrigger(stagger);
	Animator3D()->SetInt(staggerType, 0);
}

void CAnjanath::Nose(bool _show)
{
	m_pNose->SetActive(_show);
}

void CAnjanath::Wing(bool _show)
{
	m_pWings->SetActive(_show);
}

void CAnjanath::begin()
{
	Animator3D()->SetBool(aggroed, false);
	m_pNose->SetActive(false);
	m_pWings->SetActive(false);
}

void CAnjanath::tick()
{
	if (!m_bAggroed)return;
	if (m_iHP <= 0) return;
	if (IsAttacking())return;
	if (!m_pCurrentAttack)
	{
		m_pCurrentAttack = m_pAttackPicker->PickAttack();
		m_pCurrentAttack->AttackStart();
	}


}

void CAnjanath::OnAnimationBegin(IAnimationState* _pState)
{
}

void CAnjanath::OnAnimationEndStart(IAnimationState* _pState)
{
	if (_pState->GetName() == L"Stagger") m_bStaggered = false;
	else if (_pState->GetName() == L"Show Nose") Nose(true);
	else if (_pState->GetName() == L"Flash Wings") Wing(true);
	else if (_pState->GetName() == L"Attack")
	{
		assert(m_pCurrentAttack != nullptr);
		m_pCurrentAttack->AttackEnd();
		m_pCurrentAttack = nullptr;
	}
}

void CAnjanath::OnAnimationEndFinished(IAnimationState* _pState)
{
}
