#pragma once
#include "CAnimStructures.h"

class CAnimationTransition;
class CAnimationStateMachine;
class CAnimationClip;
class CAnimator3D;
typedef unordered_set<CAnimationTransition*> HashTransition;

enum class eAnimationNodeType{StateMachine, State};

class IAnimationState
{
private:
	wstring					m_strName;
	eAnimationNodeType		m_eNodeType;
	HashTransition			m_Transitions;
	CAnimationTransition* m_pCurrentTransition;
	tAnimationStateNode		m_tNodeInfo;
protected:
	CAnimator3D*			m_pAnimator;
	CAnimationStateMachine* m_pRootMachine;
	CAnimationStateMachine* m_pParentMachine;
public:
	void SetName(wstring _name) { m_strName = _name; }
	wstring GetName() { return m_strName; }
	virtual Ptr<CAnimationClip> GetClip() = 0;

	eAnimationNodeType GetType() { return m_eNodeType; }
	CAnimator3D* GetAnimator() { return m_pAnimator; }

	CAnimationStateMachine* GetRootMachine() { return m_pRootMachine; }
public:
	virtual double GetDurationInSeconds() = 0;
	virtual double GetTickPercentWithRepeat() = 0;
	virtual double GetTickPercent() = 0;

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

	IAnimationState(eAnimationNodeType _type, CAnimator3D* _animator3D, CAnimationStateMachine* _root, CAnimationStateMachine* _parent);
	virtual ~IAnimationState();
};

inline void IAnimationState::OnTransitionEnd()
{
	m_pCurrentTransition = nullptr;
}

