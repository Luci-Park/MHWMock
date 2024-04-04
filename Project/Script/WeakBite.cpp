#include "AnjAttack.h"
#include "CAnjanath.h"

WeakBite::WeakBite(CAnjanath* _parent)
	: AnjAttack(ANJ_ATTACK::WEAK_BITE, _parent, 30)
{
}

WeakBite::~WeakBite()
{
}

bool WeakBite::Attackable()
{
	//안 맞으면 맞추는 타입
	return true;
}

int WeakBite::DamageContribution(SCRIPT_TYPE _attackPart)
{
	return AttackPower() * (SCRIPT_TYPE::ANJANATHHEAD == _attackPart);
}

void WeakBite::OnAttackStart()
{
}

void WeakBite::OnAttackEnd()
{
}

ANJ_MOVE_DIR WeakBite::GetRepositionDir()
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

bool WeakBite::Move()
{
	Parent()->Animator3D()->SetInt(Parent()->turnDir, (int)ANJ_MOVE_DIR::FRONT);
	return Parent()->GetPlayerDist() > 24043.f;
}

void WeakBite::Tick()
{
}

