#include "pch.h"
#include "CAnjanathLeg.h"

CAnjanathLeg::CAnjanathLeg(SCRIPT_TYPE _type)
	: CAnjanathPart(_type, 100)
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
	//Parent()->FallOver();
	Anj()->OnDamaged(100);
	m_pScar->SetActive(true);
}

void CAnjanathLeg::begin()
{
	if (m_pScar)m_pScar->SetActive(false);
}

void CAnjanathLeg::SaveToLevelFile(FILE* _File)
{
	CAnjanathPart::SaveToLevelFile(_File);
	SaveGameObjectParam(m_pScar, _File);
}

void CAnjanathLeg::LoadFromLevelFile(FILE* _File)
{
	CAnjanathPart::LoadFromLevelFile(_File);
	LoadGameObjectParam(1, _File);
}