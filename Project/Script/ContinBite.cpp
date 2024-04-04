#include "AnjAttack.h"
#include "CAnjanath.h"


ContinBite::ContinBite(CAnjanath* _parent)
	: AnjAttack(ANJ_ATTACK::CONTIN_BITE, _parent, 55)
{
}

ContinBite::~ContinBite()
{
}

bool ContinBite::Attackable()
{
	//안 맞으면 맞추는 타입
	return true;
}

int ContinBite::DamageContribution(SCRIPT_TYPE _attackPart)
{
	return AttackPower() * (SCRIPT_TYPE::ANJANATHHEAD == _attackPart);
}

void ContinBite::OnAttackStart()
{

}

void ContinBite::OnAttackEnd()
{
}

ANJ_MOVE_DIR ContinBite::GetRepositionDir()
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

bool ContinBite::Move()
{
	return Parent()->GetPlayerDist() > 28461.244;
}

void ContinBite::Tick()
{
}

