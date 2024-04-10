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
	tAnimationKeyFrame				m_prevRootFrame;
	bool							m_bIsFirstTick;
	Vec3							m_vWorldDir[3];

public:
	void SetClip(Ptr<CAnimationClip> _pClip);
	virtual Ptr<CAnimationClip> GetClip() { return m_pClip; }
	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
	float GetSpeed() { return m_fSpeed; }
	double GetOffset() { return m_pClip != nullptr ? m_pClip->GetTicksPerSecond() : 1; }

	virtual double GetDurationInSeconds() override;
	virtual double GetTickPercentWithRepeat() override;

	void SetTick(double _percent = 0);
	virtual double GetTickPercent();
	
	virtual void OnTransitionEnd() override;
	virtual void OnTransitionBegin(double _tickPercent) override;
	virtual KeyFrames& GetBoneTransforms() override;
private:
	void Reset(double _percent, bool _addToRepeat);
public:
	virtual void tick() override;
	virtual void SaveToLevelFile(FILE* _FILE) override;
	virtual void LoadFromLevelFile(FILE* _FILE) override;

public:
	CAnimationState(CAnimator3D* _animator3D, CAnimationStateMachine* _root, CAnimationStateMachine* _parent);
	CAnimationState(const CAnimationState& _other);
	virtual ~CAnimationState();
};
