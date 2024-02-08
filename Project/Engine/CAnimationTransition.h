#pragma once

class CAnimationState;
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
	double m_dTick;

public:
	bool GetHasExitTime() { return m_bHasExitTime; }
	double GetExitTime() { return m_dExitTime; }
	bool GetFixedDuration() { return m_bFixedDuration; }
	double GetTransitionDuration() { return m_dTransitionDuration; }
	double GetTransitionOffset() { return m_dTransitionOffset; }

	void SetHasExitTime(bool _exitTime) { m_bHasExitTime = _exitTime; }	
	void SetExitTime(double _exitTime) { m_dExitTime = _exitTime; }
	void SetFixedDuration(bool _isFixedDuration) { m_bFixedDuration = _isFixedDuration; }
	void SetTransitionDuration(double _duration) {
		m_dTransitionDuration = _duration;
	}
	void SetTransitionOffset(double _offset) { m_dTransitionOffset = _offset; }

	bool CheckCondition();
	void StartTransition();

public:
	void finaltick();
private:
	void EndTransition();
public:
	CAnimationTransition(CAnimationState* _pPrevState, CAnimationState* _p);
	~CAnimationTransition();
};
