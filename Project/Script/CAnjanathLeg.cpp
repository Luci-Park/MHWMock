#include "pch.h"
#include "CAnjanathLeg.h"

CAnjanathLeg::CAnjanathLeg()
	: CAnjanathPart(SCRIPT_TYPE::ANJANATHLEG, 100)
	, m_pScar(nullptr)
{
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pScar, "Scar");
}
CAnjanathLeg::CAnjanathLeg(const CAnjanathLeg& _other)
	: CAnjanathPart(SCRIPT_TYPE::ANJANATHLEG, 100)
	, m_pScar(nullptr)
{
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pScar, "Scar");
}

CAnjanathLeg::~CAnjanathLeg()
{
}

int CAnjanathLeg::OnAttacked(int _damage)
{
	if (HP() <= 0) return _damage * 1.2;
	return _damage;
}

void CAnjanathLeg::OnHPZero()
{
	Parent()->FallOver();
	m_pScar->SetActive(true);
}

void CAnjanathLeg::begin()
{
	if (m_pScar)m_pScar->SetActive(false);
}

