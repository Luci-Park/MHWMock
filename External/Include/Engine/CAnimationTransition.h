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

public:
	CAnimationTransition();
	~CAnimationTransition();
};
