#include "AnjAttack.h"

WeakBite::WeakBite(CAnjanath* _parent)
	: AnjAttack(ANJ_ATTACK::WEAK_BITE, _parent, 30)
{
}

WeakBite::~WeakBite()
{
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

