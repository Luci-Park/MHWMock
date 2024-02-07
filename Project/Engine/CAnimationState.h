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
public:
	CAnimationState();
	CAnimationState(const CAnimationState& _other);
	~CAnimationState();
};
