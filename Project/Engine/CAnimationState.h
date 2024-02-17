#pragma once
#include "CAnimationClip.h"
class CAnimationTransition;
class CAnimationStateMachine;
class CAnimationState
{
private:
	wstring							m_strName;
	Ptr<CAnimationClip>				m_pClip;
	float							m_fSpeed;
	vector<CAnimationTransition*>	m_vecTransitions;
	double							m_dTick;
	double							m_dDuration;
	int								m_iRepeatNum;
	CAnimationTransition*			m_pCurrentTransition;
	CAnimationStateMachine*			m_pMachine;

public:
	void SetName(wstring _name) { m_strName = _name; }
	wstring GetName() { return m_strName; }
	void SetClip(Ptr<CAnimationClip> _pClip) { m_pClip = _pClip; }
	Ptr<CAnimationClip> GetClip() { return m_pClip; }
	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
	float GetSpeed() { return m_fSpeed; }

	void SetTick(double _percent);
	double GetTickPercent();
	bool IsTransitioning() { return m_pCurrentTransition != nullptr; }
	vector<CAnimationTransition*>& GetAllTransitions() { return m_vecTransitions; }
	CAnimationTransition* GetCurrentTransition() { return m_pCurrentTransition; }
	void OnTransitionEnd();
	void OnTransitionBegin(double _tickPercent);
	vector<tAnimationKeyFrame>& GetBoneTransforms();
public:
	void finaltick();

public:
	CAnimationState(CAnimationStateMachine* _pParent);
	CAnimationState(const CAnimationState& _other);
	~CAnimationState();
};
