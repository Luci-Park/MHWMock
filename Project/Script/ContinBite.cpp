#include "AnjAttack.h"
#include "CAnjanath.h"


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

ANJ_MOVE_DIR ContinBite::GetRepositionDir()
{
	return GeneralDir();
}

bool ContinBite::Move()
{
	return Parent()->GetPlayerDist() > 28461.244;
}

void ContinBite::Tick()
{
}

