#include "pch.h"
#include "AnjAction.h"
#include "CAnjanath.h"
#include "CMainPlayerScript.h"


AnjAction::AnjAction(ANJ_ACTION _type, CAnjanath* _parent, int _atkPwr)
	: m_type(_type)
	, m_pParent(_parent)
	, m_iAttackPower(_atkPwr)
	, m_bAttacked(false)
	, m_bAttacking(false)
{
}

AnjAction::~AnjAction()
{
}

void AnjAction::OnAttack(SCRIPT_TYPE _type, CMainPlayerScript* _player)
{
	if (!m_bAttacking) return;
	if (m_bAttacked) return;
	int damage = CalculateDamage(_type);

	if (damage > 0)
	{
		m_bAttacked = true;
		_player->Attacked(damage, m_pParent->GetOwner());
	}
}

void AnjAction::OnAnimationStart(wstring _animationName)
{
	if (IsStartAnimation(_animationName)) m_bAttacking = true;
}

void AnjAction::OnAnimationEnd(wstring _animationName)
{
	if (IsEndAnimation(_animationName)) m_bAttacking = false;
}
