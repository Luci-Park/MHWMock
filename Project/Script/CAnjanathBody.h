#pragma once
#include "CAnjanathPart.h"
class CAnjanathBody :
	public CAnjanathPart
{
protected:
	virtual int OnAttacked(int _damage) override;
	virtual void OnHPZero() override;
public:
	virtual void SaveToLevelFile(FILE* _File) override;
	virtual void LoadFromLevelFile(FILE* _File) override;
	CLONE(CAnjanathBody)
	CAnjanathBody();
	CAnjanathBody(const CAnjanathBody& _other);
	~CAnjanathBody();
};

