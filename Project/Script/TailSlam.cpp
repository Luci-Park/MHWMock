#include "AnjAttack.h"
#include "CAnjanath.h"

TailSlam::TailSlam(CAnjanath* _parent)
	: AnjAttack(ANJ_ATTACK::TAIL_SLAM, _parent, 30)
{
}

TailSlam::~TailSlam()
{
}

bool TailSlam::Attackable()
{
	//if behind and in range(45~)
	return (abs(Parent()->GetPlayerAngle()) > 90.f && Parent()->GetPlayerDist() < 17133.066);
}

int TailSlam::DamageContribution(SCRIPT_TYPE _attackPart)
{
	if (SCRIPT_TYPE::ANJANATHTAIL != _attackPart) return 0;
	return AttackPower() * Parent()->HasTail() ? 1 : 0.7;
}

void TailSlam::OnAttackStart()
{

}

void TailSlam::OnAttackEnd()
{
}

ANJ_MOVE_DIR TailSlam::GetRepositionDir()
{
	return ANJ_MOVE_DIR::FRONT;
}

bool TailSlam::Move()
{
	return false;
}

void TailSlam::Tick()
{
}

