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
	virtual void SaveToLevelFile(FILE* _File) override;
	virtual void LoadFromLevelFile(FILE* _File) override;
	CLONE(CAnjanathHead)
	CAnjanathHead();
	virtual ~CAnjanathHead();
};