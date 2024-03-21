#pragma once
#include "CAnimationClip.h"
#include "IAnimationState.h"

class CAnimationTransition;

class CAnimationState : 
	public IAnimationState
{
private:
	Ptr<CAnimationClip>				m_pClip;
	float							m_fSpeed;
	double							m_dTick;
	double							m_dDuration;
	int								m_iRepeatNum;
	int								m_iRootIdx;
	tAnimationKeyFrame				m_prevRootFrame;
	tAnimationKeyFrame				m_FirstRootFrame;
	bool							m_bIsFirstTick;

public:
	void SetClip(Ptr<CAnimationClip> _pClip);
	Ptr<CAnimationClip> GetClip() { return m_pClip; }
	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
	float GetSpeed() { return m_fSpeed; }
	double GetOffset() { return m_pClip != nullptr ? m_pClip->GetTicksPerSecond() : 1; }

	virtual double GetDurationInSeconds() override;
	virtual double GetTickPercentWithRepeat() override;

	void SetTick(double _percent = 0);
	double GetTickPercent();
	
	virtual void OnTransitionEnd() override;
	virtual void OnTransitionBegin(double _tickPercent) override;
	virtual vector<tAnimationKeyFrame>& GetBoneTransforms() override;
private:
	void Reset(double _percent, bool _isRepeat);
public:
	virtual void tick() override;
	virtual void SaveToLevelFile(FILE* _FILE) override;
	virtual void LoadFromLevelFile(FILE* _FILE) override;

public:
	CAnimationState(CAnimationStateMachine* _root, CAnimationStateMachine* _parent);
	CAnimationState(const CAnimationState& _other);
	virtual ~CAnimationState();
};
