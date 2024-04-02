#include "AnjAttack.h"
#include "CAnjanath.h"

Flame::Flame(CAnjanath* _parent)
	: AnjAttack(ANJ_ATTACK::RUSH, _parent, 40)
{
}

Flame::~Flame()
{
}

int Flame::DamageContribution(SCRIPT_TYPE _attackPart)
{
	return AttackPower();
}

void Flame::OnAttackStart()
{
	Parent()->Wing(true);
}

