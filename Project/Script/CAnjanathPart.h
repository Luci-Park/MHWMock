#pragma once
#include <Engine/CScript.h>
#include "CAnjanath.h"

class CAnjanathPart
	: public CScript
{
private:
	int m_iMaxHP;
	int m_iHP;
	bool m_bReacted;
	CGameObject* m_pAnjObj;
	CAnjanath* m_pAnj;
public:
	void Attacked(int _damage);
	virtual void OnCollisionEnter(CCollider3D* _Other) override;
protected:
	virtual int OnAttacked(int _damage) = 0;
	virtual void OnHPZero() = 0;
	int HP() { return m_iHP; }
	void ResetHP() { m_iHP = m_iMaxHP; }
	CAnjanath* Parent() { return m_pAnj; }
private:
	bool CheckBody();
public:
	CAnjanathPart(SCRIPT_TYPE _type, int _maxHP);
	virtual ~CAnjanathPart();
};

