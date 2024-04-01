#pragma once
#include <Engine/CScript.h>

enum class ANJ_ATTACK
{
	WEAK_BITE, BITE, CONTIN_BITE, CLAW, TAIL_SLAM, TAIL_SWEEP, BODY_SLAM, FORWARD, RUSH, FLAME
};

class CAnjanath :
	public CScript
{
private:
	int m_iHP;
	bool			m_bAggroed;
	bool			m_bStaggered;
	ANJ_ATTACK		m_Attack;
	Vec3			m_vRelativePos;
	Quaternion		m_qRelativeRot;

	CGameObject*	m_pPlayer;

private:
	void CheckPlayerPos();
	void ChooseAttack();
public:
	void Attacked(int _damage);
	void AttackSuccess(SCRIPT_TYPE _type);
	bool InStagger() { return m_bStaggered; }
	void NoseBreak();
	void FallOver();
	void TailCut();
	void BodyShot();

public:
	virtual void begin() override;
	virtual void tick() override;
	virtual void OnAnimationBegin(IAnimationState* _pState) override;
	virtual void OnAnimationEndStart(IAnimationState* _pState) override;
	virtual void OnAnimationEndFinished(IAnimationState* _pState) override;


public:
	CLONE(CAnjanath);
	CAnjanath();
	~CAnjanath();
};

