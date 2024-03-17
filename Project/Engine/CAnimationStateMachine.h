#pragma once
#include "CAnimator3D.h"
#include "IAnimationState.h"
#include "CAnimationTransition.h"

typedef std::unordered_set<IAnimationState*> HashState;
class CAnimationStateMachine :
	public IAnimationState
{
private:
	vector<tAnimationKeyFrame>			m_vecFrame;
	IAnimationState*					m_pCurrentState;
	IAnimationState*					m_pHead;
	HashState							m_States;
	vector<AnimStateParam*>				m_vecParams;
public: //for other scripts
	void SetBool(wstring _param, bool _value);
	void SetFloat(wstring _param, float _value);
	void SetInt(wstring _param, int _value);
	void SetTrigger(wstring _param, bool _value = true);

public: //for client & engine scripts
	vector<tAnimationKeyFrame>& GetFrame();

	HashState& GetAllStates() { return m_States; }
	CAnimationState* CreateState();
	CAnimationState* CreateState(CAnimationState* _copyState);
	CAnimationStateMachine* CreateStateMachine();
	void DeleteState(CAnimationState* _pState);

	IAnimationState* GetHead() { return m_pHead; }
	IAnimationState* GetCurrentState() { return m_pCurrentState; }
	IAnimationState* GetStateByName(wstring _name);
	void ChangeState(IAnimationState* _pNewState) { m_pCurrentState = _pNewState; }
	void Reset();

	AnimStateParam* CreateNewParam(AnimParamType _type);
	void SetParamName(AnimStateParam* param, wstring _name);
	void DeleteParam(wstring _name);
	void DeleteParam(int _idx);
	AnimStateParam* GetParamByName(wstring _name);
	AnimStateParam* GetParamByIndex(int _idx);
	vector<AnimStateParam*>& GetAllParams() { return m_vecParams; }


public:
	virtual void tick() override;
	virtual void SaveToLevelFile(FILE* _FILE) override;
	virtual void LoadFromLevelFile(FILE* _FILE) override;

private:
public:
	CAnimationStateMachine(CAnimationStateMachine* _root);
	~CAnimationStateMachine();
};

