#pragma once
#include "CAnimator3D.h"
#include "CAnimationState.h"
class CAnimationStateMachine
{
private:
	CAnimator3D*						m_pOwner;
	map<wstring, tAnimationKeyFrame>	m_mapFrame;
	CAnimationState*					m_pCurrentState;
	CAnimationState*					m_pHead;
	set<CAnimationState*>				m_States;

public:
	map<wstring, tAnimationKeyFrame>& GetFrame();
	CAnimationState* CreateState();
	void DeleteState(CAnimationState* _pState);
public:
	CAnimationStateMachine(CAnimator3D* _pAnimator);
	~CAnimationStateMachine();
};

