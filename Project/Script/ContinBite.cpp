#include "AnjAttack.h"

ContinBite::ContinBite(CAnjanath* _parent)
	: AnjAttack(ANJ_ATTACK::CONTIN_BITE, _parent, 55)
{
}

ContinBite::~ContinBite()
{
}

bool ContinBite::Attackable()
{
	//�� ������ ���ߴ� Ÿ��
	return true;
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

ANJ_MOVE_DIR ContinBite::GetDir()
{
	return ANJ_MOVE_DIR();
}

bool ContinBite::Move()
{
	return false;
}

void ContinBite::Tick()
{
}

