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
	CAnimationTransition*			m_pCurrentTransition;


public:
	void SetName(wstring _name) { m_strName = _name; }
	void SetClip(Ptr<CAnimationClip> _pClip) { m_pClip = _pClip; }
	Ptr<CAnimationClip> GetClip() { return m_pClip; }
	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
	float GetSpeed() { return m_fSpeed; }
	bool IsTransitioning() { return m_pCurrentTransition != nullptr; }
	void SetTick(double _percent);
	vector<tAnimationKeyFrame>& GetBoneTransforms();
public:
	void finaltick();

public:
	CAnimationState();
	CAnimationState(const CAnimationState& _other);
	~CAnimationState();
};
