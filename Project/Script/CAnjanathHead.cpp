#include "pch.h"
#include "CAnjanathHead.h"

CAnjanathHead::CAnjanathHead()
	: CAnjanathPart(SCRIPT_TYPE::ANJANATHHEAD, 240)
	, m_pScar1(nullptr)
	, m_pScar2(nullptr)
{
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pScar1, "Scar1");
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pScar2, "Scar2");
}

CAnjanathHead::CAnjanathHead(const CAnjanathHead& _other)
	: CAnjanathPart(SCRIPT_TYPE::ANJANATHHEAD, 240)
	, m_pScar1(nullptr)
	, m_pScar2(nullptr)
{
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pScar1, "Scar1");
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pScar2, "Scar2");
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
	Parent()->NoseBreak();
	Parent()->Attacked(480);

	if (m_pScar1) m_pScar1->SetActive(true);
	if (m_pScar2) m_pScar2->SetActive(true);
}

void CAnjanathHead::begin()
{
	if (m_pScar1) m_pScar1->SetActive(false);
	if (m_pScar2) m_pScar2->SetActive(false);
}

void CAnjanathHead::SaveToLevelFile(FILE* _File)
{
	CAnjanathPart::SaveToLevelFile(_File);
	SaveGameObjectParam(m_pScar1, _File);
	SaveGameObjectParam(m_pScar2, _File);
}

void CAnjanathHead::LoadFromLevelFile(FILE* _File)
{
	CAnjanathPart::LoadFromLevelFile(_File);
	LoadGameObjectParam(1, _File);
	LoadGameObjectParam(2, _File);
}