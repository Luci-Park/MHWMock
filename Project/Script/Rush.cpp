#include "AnjAttack.h"
#include "CAnjanath.h"


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

ANJ_MOVE_DIR Rush::GetRepositionDir()
{
	return GeneralDir();
}

bool Rush::Move()
{
	return Parent()->GetPlayerDist() > 87940.570;
}

void Rush::Tick()
{
}

