#include "pch.h"
#include "AnjAttack.h"

AnjAttack::AnjAttack(ANJ_ATTACK _type, CGameObject* _parent)
	: m_type(_type)
	, m_pParent(_parent)
{
}

void AnjAttack::AttackStart()
{
	m_bAttacked = false;
	OnAttackStart();
}

void AnjAttack::AttackSuccess(SCRIPT_TYPE _type, CMainPlayerScript* _player)
{
	if (m_bAttacked) return;
	int damage = DamageContribution(_type);
	if (damage == 0) return;
	m_bAttacked = true;
	_player->Attacked(damage, m_pParent);
}


