#include "pch.h"
#include "CAnjanathTail.h"
#include <Engine/CCollider3D.h>

CAnjanathTail::CAnjanathTail()
	: CAnjanathPart(SCRIPT_TYPE::ANJANATHTAIL, 200)
{
}

CAnjanathTail::~CAnjanathTail()
{
}

int CAnjanathTail::OnAttacked(int _damage)
{
	return _damage;
}

void CAnjanathTail::OnHPZero()
{
	Anj()->OnDamaged(350);
	Anj()->Stagger();
}

void CAnjanathTail::begin()
{
	//Collider3D()->SetActive(true);
}

void CAnjanathTail::SaveToLevelFile(FILE* _File)
{
	CAnjanathPart::SaveToLevelFile(_File);
}

void CAnjanathTail::LoadFromLevelFile(FILE* _File)
{
	CAnjanathPart::LoadFromLevelFile(_File);
}