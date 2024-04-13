#pragma once
#include <Engine/CScript.h>
#include "CAnjanath.h"
class CAnjanath;
class CAnjanathPart
	: public CScript
{
private:
	const int		m_iMaxHP;
	int				m_iHP;
	bool			m_bHPZeroReached;

	CGameObject*	m_pAnjObj;
	CAnjanath*		m_pAnj;

private:
	bool CheckAnj();
protected:
	virtual int OnAttacked(int _damage) = 0;
	virtual void OnHPZero() = 0;
	int HP() { return m_iHP; }
	void ResetHP() { m_iHP = m_iMaxHP; }
	CAnjanath* Anj() { return m_pAnj; }

public:
	void Damaged(int _damage);
	virtual void begin();
	virtual void OnCollisionEnter(CCollider3D* _Other) override;

	virtual void SaveToLevelFile(FILE* _File) override;
	virtual void LoadFromLevelFile(FILE* _File) override;
	CAnjanathPart(SCRIPT_TYPE _type, int _maxHP);
	virtual ~CAnjanathPart();
};

