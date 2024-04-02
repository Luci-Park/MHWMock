#include "AnjAttack.h"
#include "CAnjanath.h"

TailSweep::TailSweep(CAnjanath* _parent)
	: AnjAttack(ANJ_ATTACK::TAIL_SWEEP, _parent, 35)
{
}

TailSweep::~TailSweep()
{
}

int TailSweep::DamageContribution(SCRIPT_TYPE _attackPart)
{
	if (SCRIPT_TYPE::ANJANATHTAIL != _attackPart) return 0;
	return AttackPower() * Parent()->HasTail() ? 1 : 0.7;
}

void TailSweep::OnAttackStart()
{

}

