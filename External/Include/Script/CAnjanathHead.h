#pragma once
#include "CAnjanathPart.h"
class CAnjanathHead :
	public CAnjanathPart
{
private:
	CGameObject* m_pScar1;
	CGameObject* m_pScar2;
protected:
	virtual int OnAttacked(int _damage) override;
	virtual void OnHPZero() override;
public:
	virtual void begin() override;
public:
	CLONE(CAnjanathHead)
	CAnjanathHead();
	CAnjanathHead(const CAnjanathHead& _other);
	virtual ~CAnjanathHead();
};

