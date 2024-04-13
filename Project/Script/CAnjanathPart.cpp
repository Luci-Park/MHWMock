#include "pch.h"
#include "CAnjanathPart.h"
#include "CMainPlayerScript.h"

CAnjanathPart::CAnjanathPart(SCRIPT_TYPE _type, int _maxHP)
	: CScript(_type)
	, m_iMaxHP(_maxHP)
	, m_iHP(_maxHP)
	, m_bHPZeroReached(false)
	, m_pAnjObj(nullptr)
	, m_pAnj(nullptr)
{
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pAnjObj, "Anjanath");
}

CAnjanathPart::~CAnjanathPart()
{
}

void CAnjanathPart::Damaged(int _damage)
{
	if (CheckAnj()) return;

	_damage = OnAttacked(_damage);
	m_iHP -= _damage;
	if (m_iHP <= 0 && !m_bHPZeroReached/* && !m_pAnj->InStagger()*/)
	{
		OnHPZero();
		m_bHPZeroReached = true;
	}

	//m_pAnj->Attacked(_damage);
}

void CAnjanathPart::begin()
{
	CheckAnj();
}

void CAnjanathPart::OnCollisionEnter(CCollider3D* _Other)
{
	if (!CheckAnj()) return;
	CMainPlayerScript* script = _Other->GetOwner()->GetScript<CMainPlayerScript>();
	//if (script)
	//	Parent()->AttackSuccess((SCRIPT_TYPE)GetScriptType(), script);
}

void CAnjanathPart::SaveToLevelFile(FILE* _File)
{
}

void CAnjanathPart::LoadFromLevelFile(FILE* _File)
{
}

bool CAnjanathPart::CheckAnj()
{
	if (m_pAnj) return true;
	if (!m_pAnjObj) return false;
	m_pAnj = m_pAnjObj->GetScript<CAnjanath>();
	return m_pAnj != nullptr;
}