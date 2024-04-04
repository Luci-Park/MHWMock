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
	//�� ������ ���ߴ� Ÿ��
	return true;
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

ANJ_MOVE_DIR WeakBite::GetDir()
{
}

bool WeakBite::Move()
{
	return false;
}

void WeakBite::Tick()
{
}

