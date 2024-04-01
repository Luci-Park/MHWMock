#pragma once
#include "CAnjanathPart.h"
class CAnjanathBody :
	public CAnjanathPart
{
protected:
	virtual int OnAttacked(int _damage) override;
	virtual void OnHPZero() override;
public:
	CLONE(CAnjanathBody)
	CAnjanathBody();
	CAnjanathBody(const CAnjanathBody& _other);
	~CAnjanathBody();
};

