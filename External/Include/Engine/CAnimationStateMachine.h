#pragma once
#include "CAnimator3D.h"
#include "CAnimationState.h"


class CAnimationStateMachine
{
private:
	CAnimator3D*						m_pOwner;
	vector<tAnimationKeyFrame>			m_vecFrame;
	CAnimationState*					m_pCurrentState;
	CAnimationState*					m_pHead;
	set<CAnimationState*>				m_States;
	vector<AnimStateParam*>				m_vecParams;
public:
	vector<tAnimationKeyFrame>& GetFrame();
	CAnimationState* CreateState();
	void DeleteState(CAnimationState* _pState);
	AnimStateParam* CreateNewParam(AnimParamType _type);
	void DeleteParam(wstring _name);
	void DeleteParam(int _idx);
	AnimStateParam* GetParamByName(wstring _name);
	AnimStateParam* GetParamByIndex(int _idx);
	vector<AnimStateParam*>& GetAllParams() { return m_vecParams; }
	
public:
	void finaltick();
public:
	CAnimationStateMachine(CAnimator3D* _pAnimator);
	~CAnimationStateMachine();
};

