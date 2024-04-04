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
	float angle = Parent()->GetPlayerAngle();
	ANJ_MOVE_DIR dir = ANJ_MOVE_DIR::SMALL_TURN;
	if (abs(angle) < 180 - 25)
	{
		if (angle < 0) dir = ANJ_MOVE_DIR::LEFT_BACK;
		else dir = ANJ_MOVE_DIR::RIGHT_BACK;
	}
	else if (abs(angle) < 90) dir = ANJ_MOVE_DIR::SMALL_TURN;
	else
	{
		if (angle < 0) dir = ANJ_MOVE_DIR::LEFT;
		else dir = ANJ_MOVE_DIR::RIGHT;
	}
	return dir;
}

bool Rush::Move()
{
	return Parent()->GetPlayerDist() > 87940.570;
}

void Rush::Tick()
{
}

