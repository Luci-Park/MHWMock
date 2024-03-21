#include "pch.h"
#include "IAnimationState.h"
#include "CAnimationTransition.h"
#include "CAnimationStateMachine.h"

IAnimationState::IAnimationState(eAnimationNodeType _type, CAnimationStateMachine* _root, CAnimationStateMachine* _parent)
	: m_eNodeType(_type)
	, m_pRootMachine(_root)
	, m_pParentMachine(_parent)
	, m_tNodeInfo({ Vec2(0, 0) })
{
}

IAnimationState::~IAnimationState()
{
	for (auto t : m_Transitions)
	{
		delete t;
	}
}

void IAnimationState::tick()
{
	if (m_pCurrentTransition == nullptr)
	{
		for (auto t : m_Transitions)
		{
			if (t->CheckCondition())
			{
				m_pCurrentTransition = t;
				m_pCurrentTransition->StartTransition();
				break;
			}
		}
	}
	if (m_pCurrentTransition != nullptr)
	{
		m_pCurrentTransition->tick();
	}
}

void IAnimationState::DeleteTransition(CAnimationTransition* _transit)
{
	m_pRootMachine->Reset(0);
	auto iter = m_Transitions.find(_transit);
	if (iter != m_Transitions.end())
		m_Transitions.erase(iter);
	delete _transit;
}

void IAnimationState::SaveToLevelFile(FILE* _FILE)
{
	int count = m_Transitions.size();
	fwrite(&count, sizeof(int), 1, _FILE);
	for (auto transit : m_Transitions)
	{
		SaveWString(transit->GetNextState()->GetName(), _FILE);
		transit->SaveToLevelFile(_FILE);
	}
	fwrite(&m_tNodeInfo, sizeof(tAnimationStateNode), 1, _FILE);

}

void IAnimationState::LoadFromLevelFile(FILE* _FILE)
{
	int count;
	fread(&count, sizeof(int), 1, _FILE);
	while (count--)
	{
		wstring nextStateName;
		LoadWString(nextStateName, _FILE);
		auto nextState = m_pParentMachine->GetStateByName(nextStateName);
		auto newTransition = new CAnimationTransition(this, nextState, m_pRootMachine);
		m_Transitions.insert(newTransition);
		newTransition->LoadFromLevelFile(_FILE);
	}
	fread(&m_tNodeInfo, sizeof(tAnimationStateNode), 1, _FILE);
}
