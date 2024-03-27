#pragma once
#include "CAnimStructures.h"
#include "IAnimationState.h"

class CAnimationStateMachine;
class CAnimationTransition
{
private:
	CAnimationStateMachine*				m_pStateMachine;
	IAnimationState*					m_pPrevState;
	IAnimationState*					m_pNextState;

	KeyFrames							m_rsltKeyFrames;
	vector<AnimCondition*>				m_vecConditions;

	bool								m_bHasExitTime;
	double								m_dExitTime; // percent
	bool								m_bFixedDuration;
	double								m_dTransitionDuration;
	double								m_dTransitionOffset;
	double								m_dTick;
	double								m_dTickPercent;
	tAnimationTransitionLink			m_tLinkInfo;


public:
	bool	GetHasExitTime()		{ return m_bHasExitTime; }
	double	GetExitTime()			{ return m_dExitTime; }
	bool	GetFixedDuration()		{ return m_bFixedDuration; }
	double	GetTransitionDuration()	{ return m_dTransitionDuration; }
	double	GetTransitionOffset()	{ return m_dTransitionOffset; }

	void SetHasExitTime(bool _exitTime) { m_bHasExitTime = _exitTime; }	
	void SetExitTime(double _exitTime) { m_dExitTime = _exitTime; }
	void SetFixedDuration(bool _isFixedDuration) { m_bFixedDuration = _isFixedDuration; }
	void SetTransitionDuration(double _duration) {m_dTransitionDuration = _duration;}
	void SetTransitionOffset(double _offset) { m_dTransitionOffset = _offset; }

	KeyFrames& GetTransitionKeyFrame();

	AnimCondition* CreateCondition();
	void DeleteCondition(int _idx);
	void DeleteCondition(AnimCondition* _condition);
	bool CheckCondition();
	void StartTransition();
	vector<AnimCondition*>& GetAllConditions() { return m_vecConditions; }
	void ChangeConditionParam(AnimCondition* _cond, AnimStateParam* _param);
	IAnimationState* GetPrevState() { return m_pPrevState; }
	IAnimationState* GetNextState() { return m_pNextState; }

	void Remove();

	tAnimationTransitionLink GetViewLink() { return m_tLinkInfo; }
	void UpdateLink(tAnimationTransitionLink _link) { m_tLinkInfo = _link; }
public:
	void tick();
	void SaveToLevelFile(FILE* _FILE);
	void LoadFromLevelFile(FILE* _FILE);
private:
	void EndTransition();
	void BlendKeyFrames(KeyFrames& _prevFrames, KeyFrames& _nextFrames, float _ratio);
public:
	CAnimationTransition(IAnimationState* _pPrevState, IAnimationState* _pNextState, CAnimationStateMachine* _pMachine);
	~CAnimationTransition();
};
