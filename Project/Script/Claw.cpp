#include "AnjAttack.h"

Claw::Claw(CAnjanath* _parent)
	: AnjAttack(ANJ_ATTACK::CLAW, _parent, 20)
{
}

Claw::~Claw()
{
}

bool Claw::Attackable()
{
	//if behind and near
	return false;
}

int Claw::DamageContribution(SCRIPT_TYPE _attackPart)
{
	return AttackPower() * (SCRIPT_TYPE::ANJANATHLEG == _attackPart);
}

void Claw::OnAttackStart()
{

}

void Claw::OnAttackEnd()
{
}

ANJ_MOVE_DIR Claw::GetDir()
{
	return ANJ_MOVE_DIR();
}

bool Claw::Move()
{
	return false;
}

void Claw::Tick()
{
}

