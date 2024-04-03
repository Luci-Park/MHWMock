#pragma once
#include <Engine/CScript.h>
#include "CMainPlayerScript.h"
#include "AnjAttackPicker.h"
#include "AnjStruct.h"
enum class ANJ_STATE{ATTACK, STAGGER, RAGE, NONE};
class CAnjanath :
	public CScript
{
#pragma region Keys
private:
	const int m_iMaxHP;
	const int m_iMaxRage;
	const wstring aggroed;//bool
	const wstring turnDir;//int
	const wstring stopMove;//trigger
	const wstring attackType;//int
	const wstring hp;// int
	const wstring stagger; //trigger
	const wstring staggerType; // int
	const wstring rage;//triggger
	const wstring rageNum;// int
#pragma endregion
private:
	int m_iHP;
	int m_iRageGauge;
	int m_iRageNumber;
	ANJ_STATE m_state;
	bool			m_bAggroed;
	bool			m_bTailCut;

	CGameObject* m_pNose;
	CGameObject* m_pWings;

	AnjAttackPicker* m_pAttackPicker;
	AnjAttack*		m_pCurrentAttack;

	CGameObject*	m_pPlayer;

private:
	void CheckPlayerPos();
	void ChooseAttack();
	void EnRage();
	void Death();
	bool IsAttacking() { return m_pCurrentAttack != nullptr; }
public:
	void Attacked(int _damage);
	void AttackSuccess(SCRIPT_TYPE _type, CMainPlayerScript* _player);
	bool InStagger() { return m_bStaggered; }
	void NoseBreak();
	void FallOver();
	void TailCut();
	void BodyShot();

	void Nose(bool _show);
	void Wing(bool _show);
	bool OnFire() { return m_pWings->IsActive(); }
	bool HasTail() { return !m_bTailCut; }

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

