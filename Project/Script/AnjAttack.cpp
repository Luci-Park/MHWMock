#include "pch.h"
#include "AnjAttack.h"
#include "CAnjanath.h"

AnjAttack::AnjAttack(ANJ_ATTACK _type, CAnjanath* _parent, int _power)
	: m_type(_type)
	, m_pParent(_parent)
	, m_iAttackPower(_power)
	, m_State(ATK_STATE::DIR)
{
}

AnjAttack::~AnjAttack()
{
}

void AnjAttack::AttackStart()
{
	m_bAttacked = false;
	m_State = ATK_STATE::DIR;
	OnAttackStart();
}

void AnjAttack::AttackTick()
{
	if (m_State == ATK_STATE::DIR)
	{
		m_pParent->Animator3D()->SetInt(m_pParent->turnDir, (int)GetDir());
		m_State = ATK_STATE::MOVE;
	}
	if (m_State == ATK_STATE::MOVE)
	{
		bool move = Move();
		if (move) return;
		m_pParent->Animator3D()->SetTrigger(m_pParent->stopMove);
		m_State == ATK_STATE::TICK;
	}
	if (m_State == ATK_STATE::TICK)
	{
		Tick();
	}
}

void AnjAttack::AttackSuccess(SCRIPT_TYPE _type, CMainPlayerScript* _player)
{
	if (m_bAttacked) return;
	int damage = DamageContribution(_type);
	if (damage == 0) return;
	m_bAttacked = true;
	_player->Attacked(damage, m_pParent->GetOwner());
}

void AnjAttack::AttackEnd()
{
	m_bAttacked = false;
	OnAttackEnd();
}
