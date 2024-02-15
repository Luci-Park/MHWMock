#include "pch.h"
#include "CMonsterScript.h"


CMonsterScript::CMonsterScript()
	: CScript((UINT)SCRIPT_TYPE::MONSTERSCRIPT)
{
}

CMonsterScript::~CMonsterScript()
{
}

void CMonsterScript::tick()
{
}

void CMonsterScript::OnCollisionEnter(CCollider3D* _Other)
{
	if (L"Parent Object" == _Other->GetOwner()->GetName())
	{
		//Destroy();	

		SetLifeSpan(2.f);
	}
}

