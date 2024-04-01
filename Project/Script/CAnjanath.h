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
	CGameObject*	m_pPlayer;
	bool			m_bAggroed;
	ANJ_ATTACK		m_Attack;
	Vec3			m_vRelativePos;
	Quaternion		m_qRelativeRot;

private:
	void CheckPlayerPos();
	void ChooseAttack();
public:
	void Attacked(int _damage);
	bool InStagger();
	void NoseBreak();
	void FallOver();
	void TailCut();
	void BodyShot();
	


public:
	virtual void begin() override;
	virtual void tick() override;
	virtual void OnCollisionEnter(CCollider3D* _Other);


public:
	CLONE(CAnjanath);
	CAnjanath();
	~CAnjanath();
};

