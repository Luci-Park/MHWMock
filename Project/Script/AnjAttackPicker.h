#pragma once
#include "AnjAttack.h"
class CAnjanath;
class AnjAttackPicker
{
private:
	AnjAttack* m_pAttacks[(UINT)ANJ_ATTACK::NONE];
	CAnjanath* m_pParent;
public:
	AnjAttack* PickAttack();

public:
	AnjAttackPicker(CAnjanath* _parent);
	virtual ~AnjAttackPicker();
};

