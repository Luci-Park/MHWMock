#include "pch.h"
#include "CAnjanathHead.h"

CAnjanathHead::CAnjanathHead()
	: CAnjanathPart(SCRIPT_TYPE::ANJANATHHEAD, 240)
{
}

CAnjanathHead::~CAnjanathHead()
{
}


int CAnjanathHead::OnAttacked(int _damage)
{
	if (HP() <= 0) return _damage * 1.2;
	return _damage;
}

void CAnjanathHead::OnHPZero()
{
	Anj()->Stagger();
	Anj()->OnDamaged(480);
}

void CAnjanathHead::begin()
{
}

void CAnjanathHead::SaveToLevelFile(FILE* _File)
{
	CAnjanathPart::SaveToLevelFile(_File);
}

void CAnjanathHead::LoadFromLevelFile(FILE* _File)
{
	CAnjanathPart::LoadFromLevelFile(_File);
}