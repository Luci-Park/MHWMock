#include "pch.h"
#include "CAnjanathPart.h"
#include "CAnjanath.h"
#include "CMainPlayerScript.h"

CAnjanathPart::CAnjanathPart(SCRIPT_TYPE _type, int _maxHP)
	:CScript(_type)
	, m_iMaxHP(_maxHP)
	, m_iHP(_maxHP)
	, m_pAnjObj(nullptr)
	, m_bReacted(true)
{
	AddScriptParam(SCRIPT_PARAM::GAMEOBJECT, &m_pAnjObj, "Anjanath");
}

CAnjanathPart::~CAnjanathPart()
{
}

void CAnjanathPart::Attacked(int _damage)
{
	if (!CheckBody()) return;
	_damage = OnAttacked(_damage);
	m_iHP -= _damage;
	if (m_iHP <= 0 && !m_bReacted && !m_pAnj->InStagger())
	{
		OnHPZero();
		m_bReacted = true;
	}

	m_pAnj->Attacked(_damage);
}
void CAnjanathPart::begin()
{
	CheckBody();
}
void CAnjanathPart::OnCollisionEnter(CCollider3D* _Other)
{
	if (!CheckBody()) return;
	CMainPlayerScript* script = _Other->GetOwner()->GetScript<CMainPlayerScript>();
	if(script)
		Parent()->AttackSuccess((SCRIPT_TYPE)GetScriptType(), script);
}
bool CAnjanathPart::CheckBody()
{
	if (m_pAnj) return true;
	if (!m_pAnjObj) return false;
	m_pAnj = m_pAnjObj->GetScript<CAnjanath>();
	return m_pAnj != nullptr;
}

void CAnjanathPart::SaveToLevelFile(FILE* _File)
{
	SaveGameObjectParam(m_pAnjObj, _File);
}

void CAnjanathPart::LoadFromLevelFile(FILE* _File)
{
	LoadGameObjectParam(0, _File);
}

