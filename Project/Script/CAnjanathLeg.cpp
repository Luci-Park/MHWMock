#include "pch.h"
#include "CAnjanathLeg.h"

CAnjanathLeg::CAnjanathLeg(SCRIPT_TYPE _type)
	: CAnjanathPart(_type, 100)
{
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
	Anj()->Stagger();
	Anj()->OnDamaged(100);
}

void CAnjanathLeg::begin()
{
}

void CAnjanathLeg::SaveToLevelFile(FILE* _File)
{
	CAnjanathPart::SaveToLevelFile(_File);
}

void CAnjanathLeg::LoadFromLevelFile(FILE* _File)
{
	CAnjanathPart::LoadFromLevelFile(_File);
}