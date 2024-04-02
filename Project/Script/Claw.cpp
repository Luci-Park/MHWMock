#include "AnjAttack.h"

Claw::Claw(CAnjanath* _parent)
	: AnjAttack(ANJ_ATTACK::CLAW, _parent, 20)
{
}

Claw::~Claw()
{
}

int Claw::DamageContribution(SCRIPT_TYPE _attackPart)
{
	return AttackPower() * (SCRIPT_TYPE::ANJANATHLEG == _attackPart);
}

void Claw::OnAttackStart()
{

}

