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
	return false;
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

