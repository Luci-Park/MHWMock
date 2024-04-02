#include "AnjAttack.h"

Rush::Rush(CAnjanath* _parent)
	: AnjAttack(ANJ_ATTACK::RUSH, _parent, 60)
{
}

Rush::~Rush()
{
}

int Rush::DamageContribution(SCRIPT_TYPE _attackPart)
{
	return AttackPower();
}

void Rush::OnAttackStart()
{

}

void Rush::OnAttackEnd()
{
}

