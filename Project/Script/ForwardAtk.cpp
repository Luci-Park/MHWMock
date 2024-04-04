#include "AnjAttack.h"
#include "CAnjanath.h"


ForwardAtk::ForwardAtk(CAnjanath* _parent)
	: AnjAttack(ANJ_ATTACK::FORWARD, _parent, 50)
{
}

ForwardAtk::~ForwardAtk()
{
}

bool ForwardAtk::Attackable()
{
	//any time
	return true;
}

int ForwardAtk::DamageContribution(SCRIPT_TYPE _attackPart)
{
	return AttackPower() * (SCRIPT_TYPE::ANJANATHHEAD == _attackPart);
}

void ForwardAtk::OnAttackStart()
{

}

void ForwardAtk::OnAttackEnd()
{
}

ANJ_MOVE_DIR ForwardAtk::GetRepositionDir()
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

bool ForwardAtk::Move()
{
	return Parent()->GetPlayerDist() > 46908.770;
}

void ForwardAtk::Tick()
{
}

