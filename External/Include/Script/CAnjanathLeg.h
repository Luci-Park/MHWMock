#pragma once
#include "CAnjanathPart.h"
class CAnjanathLeg :
	public CAnjanathPart
{
private:
	CGameObject* m_pScar;
protected:
	virtual int OnAttacked(int _damage) override;
	virtual void OnHPZero() override;

public:
	virtual void begin() override;
public:
	CLONE(CAnjanathLeg)
	CAnjanathLeg();
	CAnjanathLeg(const CAnjanathLeg& _other);
	virtual ~CAnjanathLeg();
};

