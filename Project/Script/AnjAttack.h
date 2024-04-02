#pragma once
#include "CMainPlayerScript.h"
enum class ANJ_ATTACK
{
	WEAK_BITE, BITE, CONTIN_BITE, CLAW, TAIL_SLAM, TAIL_SWEEP, BODY_SLAM, FORWARD, RUSH, FLAME
};

class CGameObject;
class AnjAttack
{
private:
	ANJ_ATTACK m_type;
	CGameObject* m_pParent;

	bool m_bAttacked;
public:
	ANJ_ATTACK GetType() { return m_type; }

	void AttackStart();
	void AttackSuccess(SCRIPT_TYPE _type, CMainPlayerScript* _player);
protected:
	virtual int DamageContribution(SCRIPT_TYPE _attackPart) = 0;
	virtual void OnAttackStart() = 0;

public:
	AnjAttack(ANJ_ATTACK _type, CGameObject* _parent);
	virtual ~AnjAttack();
};

