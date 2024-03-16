#pragma once
#include "CAnimationClip.h"
#include "CAnimStructures.h"

class CAnimationTransition;
class CAnimationStateMachine;

typedef unordered_set<CAnimationTransition*> HashTransition;

class CAnimationState
{
private:
	wstring							m_strName;
	Ptr<CAnimationClip>				m_pClip;
	float							m_fSpeed;
	HashTransition					m_Transitions;
	double							m_dTick;
	double							m_dDuration;
	int								m_iRepeatNum;
	CAnimationTransition*			m_pCurrentTransition;
	CAnimationStateMachine*			m_pMachine;
	tAnimationStateNode				m_tNodeInfo;
	vector<tAnimationKeyFrame>		m_vecKeyFrames;
	tAnimationKeyFrame				m_prevRootFrame;
	tAnimationKeyFrame				m_FirstRootFrame;
	bool m_bIsFirstTick;

public:
	void SetName(wstring _name);
	wstring GetName() { return m_strName; }
	void SetClip(Ptr<CAnimationClip> _pClip);
	Ptr<CAnimationClip> GetClip() { return m_pClip; }
	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
	float GetSpeed() { return m_fSpeed; }
	double GetDurationInSeconds();
	double GetOffset() { return m_pClip != nullptr ? m_pClip->GetTicksPerSecond() : 1; }

	void SetTick(double _percent = 0);
	double GetTickPercent();
	double GetTickPercentWithRepeat();
	bool IsTransitioning() { return m_pCurrentTransition != nullptr; }

	HashTransition& GetAllTransitions() { return m_Transitions; }
	CAnimationTransition* GetCurrentTransition() { return m_pCurrentTransition; }
	void AddTransition(CAnimationTransition* _transit) { m_Transitions.insert(_transit); }
	void DeleteTransition(CAnimationTransition* _transit);
	
	void OnTransitionEnd();
	void OnTransitionBegin(double _tickPercent);
	vector<tAnimationKeyFrame>& GetBoneTransforms();

	tAnimationStateNode GetViewNode() { return m_tNodeInfo; }
	void UpdatePos(tAnimationStateNode _newPose) { m_tNodeInfo = _newPose; }
private:
	void Reset(double _percent, bool _isRepeat);
public:
	void tick();
	void SaveToLevelFile(FILE* _FILE);
	void LoadFromLevelFile(FILE* _FILE);

public:
	CAnimationState(CAnimationStateMachine* _pParent);
	CAnimationState(const CAnimationState& _other);
	~CAnimationState();
};
