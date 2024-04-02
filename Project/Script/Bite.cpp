#include "AnjAttack.h"

Bite::Bite(CAnjanath* _parent)
	: AnjAttack(ANJ_ATTACK::BITE, _parent, 65)
{
}

Bite::~Bite()
{
}

int Bite::DamageContribution(SCRIPT_TYPE _attackPart)
{
	return AttackPower() * (SCRIPT_TYPE::ANJANATHHEAD == _attackPart);
}

void Bite::OnAttackStart()
{

}

void Bite::OnAttackEnd()
{
}

