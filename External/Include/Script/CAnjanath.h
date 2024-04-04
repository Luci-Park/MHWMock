#pragma once
#include <Engine/CScript.h>
#include "CMainPlayerScript.h"
#include "AnjAttackPicker.h"
#include "AnjStruct.h"
enum class ANJ_STATE{ATTACK, STAGGER, RAGE, PEACE, NONE};
class CAnjanath :
	public CScript
{
#pragma region Keys
private:
	const int m_iMaxHP;
	const int m_iMaxRage;
public:
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
	ANJ_STATE m_State;
	bool			m_bTailCut;
	bool m_bMove;

	CGameObject* m_pNose;
	CGameObject* m_pWings;

	AnjAttackPicker* m_pAttackPicker;
	AnjAttack*		m_pCurrentAttack;

	CGameObject*	m_pPlayer;
	float testangle;
private:
	void Aggroed();
	void ChooseAttack();
	void StopAttack();
	void EnRage();
	void Death();
	void CheckWing(IAnimationState* _currentState, bool _start);
	void CheckNose(IAnimationState* _currentState, bool _start);
	void LookAt();
public:
	int HP() { return m_iHP; }
	void Attacked(int _damage);
	void AttackSuccess(SCRIPT_TYPE _type, CMainPlayerScript* _player);
	bool InStagger() { return m_State == ANJ_STATE::STAGGER; }
	void NoseBreak();
	void FallOver();
	void TailCut();
	void BodyShot();

	void Nose(bool _show);
	void Wing(bool _show);
	bool OnFire() { return m_pWings->IsActive(); }
	bool HasTail() { return !m_bTailCut; }

	float GetPlayerAngle();
	float GetPlayerDist();
	Vec3 GetPlayerPos();
public:
	virtual void begin() override;
	virtual void tick() override;
	virtual void OnAnimationBegin(IAnimationState* _pState) override;
	virtual void OnAnimationEndStart(IAnimationState* _pState) override;
	virtual void OnAnimationEndFinished(IAnimationState* _pState) override;

	virtual void SaveToLevelFile(FILE* _File) override;
	virtual void LoadFromLevelFile(FILE* _File) override;
public:
	CLONE(CAnjanath);
	CAnjanath();
	~CAnjanath();
};

