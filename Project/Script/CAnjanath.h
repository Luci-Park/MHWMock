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
	CGameObject*	m_pPlayer;
	bool			m_bAggroed;
	ANJ_ATTACK		m_Attack;
	Vec3			m_pRelativePos;
	Quaternion		m_pRelativeRot;

private:
	void CheckPlayerPos();
	void ChooseAttack();
public:
	virtual void begin() override;
	virtual void tick() override;
	virtual void OnCollisionEnter(CCollider3D* _Other);

public:
	CLONE(CAnjanath);
	CAnjanath();
	~CAnjanath();
};

