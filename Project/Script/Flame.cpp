#include "AnjAttack.h"
#include "CAnjanath.h"

Flame::Flame(CAnjanath* _parent)
	: AnjAttack(ANJ_ATTACK::RUSH, _parent, 40)
{
}

Flame::~Flame()
{
}

bool Flame::Attackable()
{
	//fire stat
	return false;
}

int Flame::DamageContribution(SCRIPT_TYPE _attackPart)
{
	return AttackPower() * (SCRIPT_TYPE::ANJANATHFIRE == _attackPart);
}

void Flame::OnAttackStart()
{
	Parent()->Wing(true);
}

void Flame::OnAttackEnd()
{
	Parent()->Wing(false);
}

ANJ_MOVE_DIR Flame::GetRepositionDir()
{
	return ANJ_MOVE_DIR::FRONT;
}

bool Flame::Move()
{
	return false;
}

void Flame::Tick()
{
}

