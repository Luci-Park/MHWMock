#pragma once
#include "CAnimationClip.h"
class CAnimationTransition;
class CAnimationState
{
private:
	wstring							m_strName;
	Ptr<CAnimationClip>				m_pClip;
	float							m_fSpeed;
	vector<CAnimationTransition*>	m_vecTransitions;
	double							m_dTick;
public:
	void SetName(wstring _name) { m_strName = _name; }
	void SetClip(Ptr<CAnimationClip> _pClip) { m_pClip = _pClip; }
	Ptr<CAnimationClip> GetClip() { return m_pClip; }
	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
	
	vector<tAnimationKeyFrame>& GetBoneTransforms();
	void SetTickByPercent();
public:
	CAnimationState();
	CAnimationState(const CAnimationState& _other);
	~CAnimationState();
};

class CAnimationTransition
{
private:
	CAnimationState* m_pPrevState;
	CAnimationState* m_pNextState;
	
	bool m_bHasExitTime;
	double m_dExitTime; // percent
	bool m_bFixedDuration;
	double m_dTransitionDuration;
	double m_dTransitionOffset;

public:
	CAnimationTransition();
	~CAnimationTransition();
};
