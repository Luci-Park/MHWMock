#include "pch.h"
#include "CAnimationStateMachine.h"

CAnimationStateMachine::CAnimationStateMachine(CAnimator3D* _pAnimator)
	: m_pOwner(_pAnimator)
{
	auto pHead = CreateState();
	pHead->SetName(L"EntryPoint");
	m_pHead = pHead;
	m_pCurrentState = m_pHead;
}

CAnimationStateMachine::~CAnimationStateMachine()
{
	for (auto state : m_States)
		delete state;
}
vector<tAnimationKeyFrame>& CAnimationStateMachine::GetFrame()
{
	m_vecFrame.clear();
	if (m_pCurrentState != m_pHead)
	{
		if (m_pCurrentState->IsTransitioning())
		{

		}
		else
		{
			m_vecFrame = m_pCurrentState->GetBoneTransforms();
		}		
	}
	return m_vecFrame;
}

CAnimationState* CAnimationStateMachine::CreateState()
{
	CAnimationState* pNewState = new CAnimationState();hg
	m_States.insert(pNewState);
	return pNewState;
}

void CAnimationStateMachine::DeleteState(CAnimationState* _pState)
{
	auto iter = m_States.find(_pState);
	if (iter != m_States.end())
	{
		delete *iter;
		m_States.erase(iter);
	}
}
