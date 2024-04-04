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
	return false;
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

ANJ_MOVE_DIR BodySlam::GetDir()
{
	return ANJ_MOVE_DIR();
}

bool BodySlam::Move()
{
	return false;
}

void BodySlam::Tick()
{
}

