#pragma once
#include "CAnjanathPart.h"
class CAnjanathHead :
	public CAnjanathPart
{
protected:
	virtual int OnAttacked(int _damage) override;
	virtual void OnHPZero() override;
public:
	virtual void begin() override;
public:
	virtual void SaveToLevelFile(FILE* _File) override;
	virtual void LoadFromLevelFile(FILE* _File) override;
	CLONE(CAnjanathHead)
	CAnjanathHead();
	virtual ~CAnjanathHead();
};