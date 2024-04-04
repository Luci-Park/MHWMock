#include "AnjAttack.h"

Rush::Rush(CAnjanath* _parent)
	: AnjAttack(ANJ_ATTACK::RUSH, _parent, 60)
{
}

Rush::~Rush()
{
}

bool Rush::Attackable()
{
	return true;
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

ANJ_MOVE_DIR Rush::GetDir()
{
	return ANJ_MOVE_DIR::FRONT;
}

bool Rush::Move()
{
	return false;
}

void Rush::Tick()
{
}

