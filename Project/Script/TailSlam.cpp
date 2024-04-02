#include "AnjAttack.h"
#include "CAnjanath.h"

TailSlam::TailSlam(CAnjanath* _parent)
	: AnjAttack(ANJ_ATTACK::TAIL_SLAM, _parent, 30)
{
}

TailSlam::~TailSlam()
{
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

