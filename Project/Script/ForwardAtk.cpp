#include "AnjAttack.h"
#include "CAnjanath.h"


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

ANJ_MOVE_DIR ForwardAtk::GetRepositionDir()
{
	return GeneralDir();
}

bool ForwardAtk::Move()
{
	return Parent()->GetPlayerDist() > 46908.770;
}

void ForwardAtk::Tick()
{
}

