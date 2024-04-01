#pragma once
#include "CAnjanathPart.h"

class CAnjanathTail :
	public CAnjanathPart
{
private:
	CGameObject* m_pTail;
protected:
	virtual int OnAttacked(int _damage) override;
	virtual void OnHPZero() override;
public:
	virtual void begin() override;
public:
	CLONE(CAnjanathTail)
	CAnjanathTail();
	CAnjanathTail(const CAnjanathTail& _other);
	virtual ~CAnjanathTail();
};

