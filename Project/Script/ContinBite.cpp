#include "AnjAttack.h"

ContinBite::ContinBite(CAnjanath* _parent)
	: AnjAttack(ANJ_ATTACK::CONTIN_BITE, _parent, 55)
{
}

ContinBite::~ContinBite()
{
}

int ContinBite::DamageContribution(SCRIPT_TYPE _attackPart)
{
	return AttackPower() * (SCRIPT_TYPE::ANJANATHHEAD == _attackPart);
}

void ContinBite::OnAttackStart()
{

}

void ContinBite::OnAttackEnd()
{
}

