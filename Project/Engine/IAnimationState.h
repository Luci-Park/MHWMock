#pragma once
#include "CAnimStructures.h"

class CAnimationTransition;
class CAnimationStateMachine;
typedef unordered_set<CAnimationTransition*> HashTransition;

enum class eAnimationNodeType{StateMachine, State};

class IAnimationState
{
private:
	wstring					m_strName;
	eAnimationNodeType		m_eNodeType;
	HashTransition			m_Transitions;
	CAnimationTransition*	m_pCurrentTransition;
	tAnimationStateNode		m_tNodeInfo;
protected:
	CAnimationStateMachine* m_pRootMachine;
public:
	void SetName(wstring _name) { m_strName = _name; }
	wstring GetName() { return m_strName; }

	CAnimationStateMachine* GetRootMachine() { return m_pRootMachine; }
public:
	virtual double GetDurationInSeconds() = 0;
	virtual double GetTickPercentWithRepeat() = 0;

	virtual vector<tAnimationKeyFrame>& GetBoneTransforms() = 0;

	virtual void OnTransitionBegin(double _tickPercent) {};
	virtual void OnTransitionEnd();

	bool IsTransitioning() { return m_pCurrentTransition != nullptr; }
	HashTransition& GetAllTransitions() { return m_Transitions; }
	CAnimationTransition* GetCurrentTransition() { return m_pCurrentTransition; }
	void AddTransition(CAnimationTransition* _transit) { m_Transitions.insert(_transit); }
	void DeleteTransition(CAnimationTransition* _transit);

	tAnimationStateNode GetViewNode() { return m_tNodeInfo; }
	void UpdatePos(tAnimationStateNode _newPos) { m_tNodeInfo = _newPos; }

public:
	virtual void tick();
	virtual void SaveToLevelFile(FILE* _FILE);
	virtual void LoadFromLevelFile(FILE* _FILE);

	IAnimationState(eAnimationNodeType _type, CAnimationStateMachine* _root);
	~IAnimationState();
};

inline void IAnimationState::OnTransitionEnd()
{
	m_pCurrentTransition = nullptr;
}

inline void IAnimationState::DeleteTransition(CAnimationTransition* _transit)
{
	auto iter = m_Transitions.find(_transit);
	if (iter != m_Transitions.end())
		m_Transitions.erase(iter);
	delete _transit;
}

