#pragma once
#include "CAnjanathPart.h"

class CAnjanathLeg :
	public CAnjanathPart
{
private:
protected:
	virtual int OnAttacked(int _damage) override;
	virtual void OnHPZero() override;

public:
	virtual void begin() override;
public:
	virtual void SaveToLevelFile(FILE* _File) override;
	virtual void LoadFromLevelFile(FILE* _File) override;
	CAnjanathLeg(SCRIPT_TYPE _type);
	virtual ~CAnjanathLeg();
};