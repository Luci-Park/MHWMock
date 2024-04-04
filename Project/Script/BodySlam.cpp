#include "AnjAttack.h"
#include "CAnjanath.h"

BodySlam::BodySlam(CAnjanath* _parent)
	: AnjAttack(ANJ_ATTACK::BODY_SLAM, _parent, 30)
{
}

BodySlam::~BodySlam()
{
}

bool BodySlam::Attackable()
{
	//if left and near
	return abs(Parent()->GetPlayerAngle() <= 0 && Parent()->GetPlayerDist() < 13682.726);
}

int BodySlam::DamageContribution(SCRIPT_TYPE _attackPart)
{
	return AttackPower() * (SCRIPT_TYPE::ANJANATHBODY == _attackPart);
}

void BodySlam::OnAttackStart()
{

}

void BodySlam::OnAttackEnd()
{
}

ANJ_MOVE_DIR BodySlam::GetRepositionDir()
{
	return ANJ_MOVE_DIR::FRONT;
}

bool BodySlam::Move()
{
	return false;
}

void BodySlam::Tick()
{
}

