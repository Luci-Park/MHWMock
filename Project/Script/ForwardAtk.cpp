#include "AnjAttack.h"

ForwardAtk::ForwardAtk(CAnjanath* _parent)
	: AnjAttack(ANJ_ATTACK::FORWARD, _parent, 50)
{
}

ForwardAtk::~ForwardAtk()
{
}

bool ForwardAtk::Attackable()
{
	//any time
	return true;
}

int ForwardAtk::DamageContribution(SCRIPT_TYPE _attackPart)
{
	return AttackPower() * (SCRIPT_TYPE::ANJANATHHEAD == _attackPart);
}

void ForwardAtk::OnAttackStart()
{

}

void ForwardAtk::OnAttackEnd()
{
}

