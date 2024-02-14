#pragma once
class CAnimationStateMachine;
class CAnimationState;
class CAnimationTransition
{
private:
	CAnimationStateMachine*				m_pStateMachine;
	CAnimationState*					m_pPrevState;
	CAnimationState*					m_pNextState;

	map<wstring, tAnimationKeyFrame>	m_mapKeyFrame;
	vector<tAnimationKeyFrame>			m_vecKeyFrames;
	vector<AnimCondition*>				m_vecConditions;

	bool								m_bHasExitTime;
	double								m_dExitTime; // percent
	bool								m_bFixedDuration;
	double								m_dTransitionDuration;
	double								m_dTransitionOffset;
	double								m_dTick;
	double								m_dTickPercent;


public:
	bool GetHasExitTime() { return m_bHasExitTime; }
	double GetExitTime() { return m_dExitTime; }
	bool GetFixedDuration() { return m_bFixedDuration; }
	double GetTransitionDuration() { return m_dTransitionDuration; }
	double GetTransitionOffset() { return m_dTransitionOffset; }

	void SetHasExitTime(bool _exitTime) { m_bHasExitTime = _exitTime; }	
	void SetExitTime(double _exitTime) { m_dExitTime = _exitTime; }
	void SetFixedDuration(bool _isFixedDuration) { m_bFixedDuration = _isFixedDuration; }
	void SetTransitionDuration(double _duration) {m_dTransitionDuration = _duration;}
	void SetTransitionOffset(double _offset) { m_dTransitionOffset = _offset; }

	map<wstring, tAnimationKeyFrame>& GetTransitionKeyFrame();



	bool CheckCondition();
	void StartTransition();

public:
	void finaltick();
private:
	void EndTransition();
	void BlendKeyFrame(vector<tAnimationKeyFrame>& frames, bool minus);
public:
	CAnimationTransition(CAnimationState* _pPrevState, CAnimationState* _pNextState, CAnimationStateMachine* _pMachine);
	~CAnimationTransition();
};
