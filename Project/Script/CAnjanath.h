#pragma once
#include <Engine/CScript.h>
#include "AnjStruct.h"
#include "AnjActionPicker.h"
class CAnjanath :
	public CScript
{
private:
	CGameObject* m_pPlayer;
	float m_fRotateSpeed;
	float m_fDistance;
	float m_fAngle;

	bool m_bMoving;

	AnjActionPicker* m_pPicker;
	AnjAction* m_pCurrentAction;

	
private:
	void OnPickAction(ANJ_ACTION _action = ANJ_ACTION::NONE);
	void RotateTowardsPlayer();
public:
	float GetAngleBetweenPlayer();
	float GetDistanceBetweenPlayer();
	
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

