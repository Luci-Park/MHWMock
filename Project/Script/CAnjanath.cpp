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
}

CAnjanath::~CAnjanath()
{
	delete m_pAttackPicker;
}

void CAnjanath::Aggroed()
{
	Animator3D()->SetBool(aggroed, true);
	
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

void CAnjanath::StopAttack()
{
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
	if (m_State == ANJ_STATE::ATTACK) StopAttack();
	m_State = ANJ_STATE::STAGGER;
	Animator3D()->SetTrigger(stagger);
	Animator3D()->SetInt(staggerType, 0);
	Nose(false);
}

void CAnjanath::FallOver()
{
	if (m_State == ANJ_STATE::ATTACK) StopAttack();
	m_State = ANJ_STATE::STAGGER;
	Animator3D()->SetTrigger(stagger);
	Animator3D()->SetInt(staggerType, 1);
}

void CAnjanath::TailCut()
{
	m_bTailCut = true;
	if (m_State == ANJ_STATE::ATTACK) StopAttack();
	m_State = ANJ_STATE::STAGGER;
	Animator3D()->SetTrigger(stagger);
	Animator3D()->SetInt(staggerType, 1);
}

void CAnjanath::BodyShot()
{
	if (m_State == ANJ_STATE::ATTACK) StopAttack();
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

void CAnjanath::begin()
{
	Animator3D()->SetBool(aggroed, false);
	return;
	m_pNose->SetActive(false);
	m_pWings->SetActive(false);
}

void CAnjanath::tick()
{
	if (ANJ_STATE::PEACE == m_State) return;
	if (m_iHP <= 0) return;


}

void CAnjanath::OnAnimationBegin(IAnimationState* _pState)
{
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

void CAnjanath::LoadFromLevelFile(FILE* _File)
{
	LoadGameObjectParam(0, _File);
}
