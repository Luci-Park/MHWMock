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
	pNewState->SetName(L"New State");
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
CAnimationState* CAnimationStateMachine::GetStateByName(wstring _name)
{
	for (auto s : m_States)
		if (s->GetName() == _name)
			return s;
	return nullptr;
}
void CAnimationStateMachine::Reset()
{
	ChangeState(m_pHead);
	m_pHead->SetTick(0);
}

AnimStateParam* CAnimationStateMachine::CreateNewParam(AnimParamType _type)
{
	if (AnimParamType::NONE == _type)
		return nullptr;

	auto param = new AnimStateParam();
	
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

	SetParamName(param, L"New " + GetAnimParamWStr(_type));	
	return param;
}

void CAnimationStateMachine::SetParamName(AnimStateParam* param, wstring _name)
{
	wstring newName = _name;
	int postFix = 0;
	bool noDuplicateFlag = false;
	while (!noDuplicateFlag)
	{
		noDuplicateFlag = true;
		for (int i = 0; i < m_vecParams.size(); i++)
		{
			if (m_vecParams[i] != param && m_vecParams[i]->name == newName)
			{
				noDuplicateFlag = false;
				break;
			}
		}
		if(!noDuplicateFlag)
			newName = _name + L" " + std::to_wstring(postFix++);
	}
	param->name = newName;
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

void CAnimationStateMachine::SetBool(wstring _param, bool _value)
{
	GetParamByName(_param)->value.BOOL = _value;
}

void CAnimationStateMachine::SetFloat(wstring _param, float _value)
{
	GetParamByName(_param)->value.FLOAT = _value;
}

void CAnimationStateMachine::SetInt(wstring _param, int _value)
{
	GetParamByName(_param)->value.INT = _value;
}

void CAnimationStateMachine::SetTrigger(wstring _param, bool _value)
{
	GetParamByName(_param)->value.TRIGGER = _value;
}

void CAnimationStateMachine::finaltick()
{
	m_pCurrentState->finaltick();
}

void CAnimationStateMachine::SaveToLevelFile(FILE* _FILE)
{
	
}

void CAnimationStateMachine::LoadFromLevelFile(FILE* _FILE)
{
}
