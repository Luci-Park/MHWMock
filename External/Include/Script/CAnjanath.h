#pragma once
#include <Engine/CScript.h>
#include "AnjStruct.h"
#include "AnjActionPicker.h"

class CMainPlayerScript;
class CAnjanath :
	public CScript
{
private:
	const int			m_iMaxHP;
	int					m_iHP;
	float				m_fRotateSpeed;
	bool				m_bStagger;

	AnjActionPicker*	m_pPicker;
	AnjAction*			m_pCurrentAction;

	CGameObject*		m_pPlayer;
public:
	void AttackHit(SCRIPT_TYPE _type, CMainPlayerScript* _player);
	void OnDamaged(int _damge);
	bool InStagger() { return m_bStagger; }
	
private:
	void OnPickAction(ANJ_ACTION _action = ANJ_ACTION::NONE);
	void RotateTowardsPlayer();
public:

	float GetAngleBetweenPlayer();
	float GetDistanceBetweenPlayer();
	void LookAtPlayer();
	
	virtual void tick() override;

	virtual void OnAnimationBegin(IAnimationState* _pState) override;
	virtual void OnAnimationEndStart(IAnimationState* _pState) override;
	virtual void OnAnimationEndFinished(IAnimationState* _pState) override;


	virtual void SaveToLevelFile(FILE* _File) override;
	virtual void LoadFromLevelFile(FILE* _FILE) override;
public:
	CLONE(CAnjanath)
	CAnjanath();
	~CAnjanath();
};

