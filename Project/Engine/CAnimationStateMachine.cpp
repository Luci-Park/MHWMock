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

	for (auto param : m_vecParams)
		delete param;
}
vector<tAnimationKeyFrame>& CAnimationStateMachine::GetFrame()
{
	m_vecFrame.clear();
	if (1)//m_pCurrentState != m_pHead)
	{
		if (m_pCurrentState->IsTransitioning())
		{
			map<wstring, tAnimationKeyFrame> mapFrame = m_pCurrentState->GetCurrentTransition()->GetTransitionKeyFrame();
			for (auto frame : mapFrame)
				m_vecFrame.push_back(frame.second);
		}
		else
		{
			vector<tAnimationKeyFrame> frame = m_pCurrentState->GetBoneTransforms();
			for (int i = 0; i < frame.size(); i++)
				m_vecFrame.push_back(frame[i]);
		}		
	}
	return m_vecFrame;
}

CAnimationState* CAnimationStateMachine::CreateState()
{
	CAnimationState* pNewState = new CAnimationState(this);
	m_States.insert(pNewState);
	return pNewState;
}

CAnimationState* CAnimationStateMachine::CreateState(CAnimationState* _copyState)
{
	CAnimationState* pNewState = new CAnimationState(*_copyState);
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

AnimStateParam* CAnimationStateMachine::CreateNewParam(AnimParamType _type)
{
	if (AnimParamType::NONE == _type)
		return nullptr;

	auto param = new AnimStateParam();
	param->name = L"New " + GetAnimParamWStr(_type);
	
	param->type = _type;
	if (AnimParamType::FLOAT == _type)
		param->value.FLOAT = 0;
	else if (AnimParamType::INT == _type)
		param->value.INT = 0;
	else if (AnimParamType::BOOL == _type)
		param->value.BOOL = false;
	else if (AnimParamType::TRIGGER == _type)
		param->value.TRIGGER = false;

	m_vecParams.push_back(param);
	return param;
}

void CAnimationStateMachine::DeleteParam(wstring _name)
{
	for (int i = 0; i < m_vecParams.size(); i++)
	{
		if (m_vecParams[i]->name == _name)
		{
			DeleteParam(i);
			return;
		}
	}
}

void CAnimationStateMachine::DeleteParam(int _idx)
{
	if (0 <= _idx && _idx < m_vecParams.size())
	{
		delete m_vecParams[_idx];
		m_vecParams.erase(m_vecParams.begin() + _idx);
	}
}

AnimStateParam* CAnimationStateMachine::GetParamByName(wstring _name)
{
	for (int i = 0; i < m_vecParams.size(); i++)
	{
		if (m_vecParams[i]->name == _name)
			return m_vecParams[i];
	}
	return nullptr;
}

AnimStateParam* CAnimationStateMachine::GetParamByIndex(int _idx)
{
	if (0 <= _idx && _idx < m_vecParams.size())
		return m_vecParams[_idx];
	return nullptr;
}

void CAnimationStateMachine::finaltick()
{
	m_pCurrentState->finaltick();
}
