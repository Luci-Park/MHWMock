#include "AnjAttack.h"

Bite::Bite(CAnjanath* _parent)
	: AnjAttack(ANJ_ATTACK::BITE, _parent, 65)
{
}

Bite::~Bite()
{
}

bool Bite::Attackable()
{
	//안 맞으면 맞추는 타입
	return true;
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

ANJ_MOVE_DIR Bite::GetDir()
{
	return ANJ_MOVE_DIR();
}

bool Bite::Move()
{
	return false;
}

void Bite::Tick()
{
}

