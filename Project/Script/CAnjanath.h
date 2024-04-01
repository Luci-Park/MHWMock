#pragma once
#include <Engine/CScript.h>
#include "CMainPlayerScript.h"
#include "AnjAttack.h"

class CAnjanath :
	public CScript
{
private:
	int m_iHP;
	bool			m_bAggroed;
	bool			m_bStaggered;
	AnjAttack*		m_pCurrentAttack;

	Vec3			m_vRelativePos;
	Quaternion		m_qRelativeRot;

	CGameObject*	m_pPlayer;

private:
	void CheckPlayerPos();
	void ChooseAttack();
public:
	void Attacked(int _damage);
	void AttackSuccess(SCRIPT_TYPE _type, CMainPlayerScript* _player);
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

