#include "AnjAttack.h"
#include "CAnjanath.h"

WeakBite::WeakBite(CAnjanath* _parent)
	: AnjAttack(ANJ_ATTACK::WEAK_BITE, _parent, 30)
{
}

WeakBite::~WeakBite()
{
}

bool WeakBite::Attackable()
{
	//안 맞으면 맞추는 타입
	return true;
}

int WeakBite::DamageContribution(SCRIPT_TYPE _attackPart)
{
	return AttackPower() * (SCRIPT_TYPE::ANJANATHHEAD == _attackPart);
}

void WeakBite::OnAttackStart()
{
}

void WeakBite::OnAttackEnd()
{
}

ANJ_MOVE_DIR WeakBite::GetRepositionDir()
{
	return GeneralDir();
}

bool WeakBite::Move()
{
	Parent()->Animator3D()->SetInt(Parent()->turnDir, (int)ANJ_MOVE_DIR::FRONT);
	return Parent()->GetPlayerDist() > 24043.f;
}

void WeakBite::Tick()
{
}

