#pragma once
#include "CAnimator3D.h"
#include "CAnimationState.h"

typedef std::unordered_set<CAnimationState*> HashState;
class CAnimationStateMachine
{
private:
	CAnimator3D*						m_pOwner;
	vector<tAnimationKeyFrame>			m_vecFrame;
	CAnimationState*					m_pCurrentState;
	CAnimationState*					m_pHead;
	HashState							m_States;
	vector<AnimStateParam*>				m_vecParams;
public:
	vector<tAnimationKeyFrame>& GetFrame();

	HashState& GetAllStates() { return m_States; }
	CAnimationState* CreateState();
	CAnimationState* CreateState(CAnimationState* _copyState);
	void DeleteState(CAnimationState* _pState);

	CAnimationState* GetHead() { return m_pHead; }
	CAnimationState* GetCurrentState() { return m_pCurrentState; }
	void ChangeState(CAnimationState* _pNewState) { m_pCurrentState = _pNewState; }

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

