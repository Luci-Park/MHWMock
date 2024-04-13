#include "pch.h"
#include "CAnjanathBody.h"

CAnjanathBody::CAnjanathBody()
	: CAnjanathPart(SCRIPT_TYPE::ANJANATHBODY, 100)
{
}

CAnjanathBody::~CAnjanathBody()
{
}

int CAnjanathBody::OnAttacked(int _damage)
{
	return _damage;
}

void CAnjanathBody::OnHPZero()
{
	Anj()->Stagger();
}

void CAnjanathBody::SaveToLevelFile(FILE* _File)
{
	CAnjanathPart::SaveToLevelFile(_File);
}

void CAnjanathBody::LoadFromLevelFile(FILE* _File)
{
	CAnjanathPart::LoadFromLevelFile(_File);
}