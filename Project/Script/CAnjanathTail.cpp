#include "pch.h"
#include "CAnjanathTail.h"
#include <Engine/CCollider3D.h>

CAnjanathTail::CAnjanathTail()
	: CAnjanathPart(SCRIPT_TYPE::ANJANATHTAIL, 200)
	, m_pTail(nullptr)
{
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pTail, "TailMesh");
}

CAnjanathTail::CAnjanathTail(const CAnjanathTail& _other)
	:CAnjanathPart(SCRIPT_TYPE::ANJANATHTAIL, 200)
	, m_pTail(nullptr)
{
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pTail, "TailMesh");
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
	if (m_pTail)m_pTail->SetActive(false);
	//Collider3D()->SetActive(false);-> size를 정하면 된다.
	Parent()->Attacked(350);
}

void CAnjanathTail::begin()
{
	if (m_pTail)m_pTail->SetActive(true);
	Collider3D()->SetActive(true);
}

void CAnjanathTail::SaveToLevelFile(FILE* _File)
{
	CAnjanathPart::SaveToLevelFile(_File);
	SaveGameObjectParam(m_pTail, _File);
}

void CAnjanathTail::LoadFromLevelFile(FILE* _File)
{
	CAnjanathPart::LoadFromLevelFile(_File);
	LoadGameObjectParam(1, _File);
}
