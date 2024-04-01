#pragma once
#include <Engine/CScript.h>
#include "CMainPlayerScript.h"
#include "AnjAttack.h"

class CAnjanath :
	public CScript
{
private:
	const int m_iMaxHP;
	const int m_iRageGauge;
	int m_iHP;
	int m_iRage;
	bool			m_bAggroed;
	bool			m_bStaggered;

	CGameObject* m_pNose;
	CGameObject* m_pWings;

	AnjAttack*		m_pCurrentAttack;

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

