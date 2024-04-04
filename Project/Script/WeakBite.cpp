#include "AnjAttack.h"

WeakBite::WeakBite(CAnjanath* _parent)
	: AnjAttack(ANJ_ATTACK::WEAK_BITE, _parent, 30)
{
}

WeakBite::~WeakBite()
{
}

bool WeakBite::Attackable()
{
	//true if near(위치만 맞으면 됨)
	return false;
}

void WeakBite::AttackTick()
{
	if (m_bDirSet) return;
	m_bDirSet = true;
	//set dir
}

int WeakBite::DamageContribution(SCRIPT_TYPE _attackPart)
{
	return AttackPower() * (SCRIPT_TYPE::ANJANATHHEAD == _attackPart);
}

void WeakBite::OnAttackStart()
{
	m_bDirSet = false;
}

void WeakBite::OnAttackEnd()
{
	m_bDirSet = false;
}

