#pragma once
#include <Engine/CScript.h>
class CAnjanath :
	public CScript
{
private:
	int MaxHP;
	int KOGaugeThreshold;
	int ExhaustThreshold;
	int BaseAttack;
public:
	CLONE(CAnjanath)
	CAnjanath();
	~CAnjanath();
};

