#include "pch.h"
#include "CAnjanath.h"
#include <Engine/CAnimator3D.h>


CAnjanath::CAnjanath()
	: CScript(SCRIPT_TYPE::ANJANATH)
	, m_bAggroed(false)
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

void CAnjanath::begin()
{
	Animator3D()->SetBool(L"Aggroed", false);
}

void CAnjanath::tick()
{
	if (!m_bAggroed)return;
	CheckPlayerPos();
	// check playerPos
	// if 
	
}

void CAnjanath::OnCollisionEnter(CCollider3D* _Other)
{
	Animator3D()->SetBool(L"Aggroed", true);
}