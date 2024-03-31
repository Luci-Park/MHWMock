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

void CAnjanath::begin()
{
	Animator3D()->SetBool(L"Aggroed", false);
}

void CAnjanath::tick()
{
	if (!m_bAggroed)return;
}

void CAnjanath::OnCollisionEnter(CCollider3D* _Other)
{
	Animator3D()->SetBool(L"Aggroed", true);
}