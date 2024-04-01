#include "pch.h"
#include "CAnjanath.h"
#include <Engine/CAnimator3D.h>

CAnjanath::CAnjanath()
	: CScript(SCRIPT_TYPE::ANJANATH)
	, m_bAggroed(false)
	, m_bStaggered(false)
	, m_iHP(3528)
{
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pPlayer, "Player");
}

CAnjanath::~CAnjanath()
{
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
	Animator3D()->SetInt(L"Attack Type", (int)ANJ_ATTACK::BITE);
}

void CAnjanath::Attacked(int _damage)
{
	if (!m_bAggroed)
	{
		m_bAggroed = true;
		Animator3D()->SetBool(L"Aggroed", true);
	}
	m_iHP -= _damage;
	Animator3D()->SetInt(L"HP", m_iHP);
}

void CAnjanath::AttackSuccess(SCRIPT_TYPE _type)
{
}

void CAnjanath::NoseBreak()
{
}

void CAnjanath::FallOver()
{
}

void CAnjanath::TailCut()
{
}

void CAnjanath::BodyShot()
{
}

void CAnjanath::begin()
{
	Animator3D()->SetBool(L"Aggroed", false);
}

void CAnjanath::tick()
{
	if (!m_bAggroed)return;
	if (m_iHP <= 0) return;
	CheckPlayerPos();
	// check playerPos
	// if 
}

void CAnjanath::OnAnimationBegin(IAnimationState* _pState)
{
	//if staggered state machine => staggeredZ
}

void CAnjanath::OnAnimationEndStart(IAnimationState* _pState)
{
	//if staggered state machine => staggered end
}

void CAnjanath::OnAnimationEndFinished(IAnimationState* _pState)
{
}
