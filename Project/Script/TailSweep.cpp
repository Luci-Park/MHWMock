#include "AnjAttack.h"
#include "CAnjanath.h"

TailSweep::TailSweep(CAnjanath* _parent)
	: AnjAttack(ANJ_ATTACK::TAIL_SWEEP, _parent, 35)
{
}

TailSweep::~TailSweep()
{
}

bool TailSweep::Attackable()
{
	//if in range and behind(0 ~ 180)
	return (abs(Parent()->GetPlayerAngle()) > 90.f && Parent()->GetPlayerDist() < 17133.066);
}

int TailSweep::DamageContribution(SCRIPT_TYPE _attackPart)
{
	if (SCRIPT_TYPE::ANJANATHTAIL != _attackPart
		|| SCRIPT_TYPE::ANJANATHBODY != _attackPart) return 0;
	return AttackPower() * Parent()->HasTail() ? 1 : 0.7;
}

void TailSweep::OnAttackStart()
{

}

void TailSweep::OnAttackEnd()
{
}

ANJ_MOVE_DIR TailSweep::GetDir()
{
	return ANJ_MOVE_DIR::FRONT;
}

bool TailSweep::Move()
{
	return false;
}

void TailSweep::Tick()
{
}

