#include "AnjAttack.h"
#include "CAnjanath.h"

BodySlam::BodySlam(CAnjanath* _parent)
	: AnjAttack(ANJ_ATTACK::BODY_SLAM, _parent, 30)
{
}

BodySlam::~BodySlam()
{
}

int BodySlam::DamageContribution(SCRIPT_TYPE _attackPart)
{
	return AttackPower() * (SCRIPT_TYPE::ANJANATHBODY == _attackPart);
}

void BodySlam::OnAttackStart()
{

}

