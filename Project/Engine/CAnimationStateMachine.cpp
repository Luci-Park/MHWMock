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
map<wstring, tAnimationKeyFrame>& CAnimationStateMachine::GetFrame()
{
	m_mapFrame.clear();
	if (m_pCurrentState != m_pHead)
	{
	}
	return m_mapFrame;
}

CAnimationState* CAnimationStateMachine::CreateState()
{
	CAnimationState* pNewState = new CAnimationState();
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
