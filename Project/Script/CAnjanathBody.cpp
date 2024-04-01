#include "pch.h"
#include "CAnjanathBody.h"

CAnjanathBody::CAnjanathBody()
	: CAnjanathPart(SCRIPT_TYPE::ANJANATHBODY, 100)
{
}

CAnjanathBody::CAnjanathBody(const CAnjanathBody& _other)
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
	Parent()->BodyShot();
}
