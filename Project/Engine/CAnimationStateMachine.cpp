#include "pch.h"
#include "CAnimationStateMachine.h"
#include "CAnimationState.h"

CAnimationStateMachine::CAnimationStateMachine(CAnimationStateMachine* _root, CAnimationStateMachine* _parent)
	: IAnimationState(eAnimationNodeType::StateMachine, _root, _parent)
{
	if (m_pRootMachine == nullptr)
	{
		m_pRootMachine = this;
		m_pParentMachine = this;
	}
	m_pHead = CreateState();
	m_pHead->SetName(L"EntryPoint");
	m_pTail = CreateState();
	m_pTail->SetName(L"ExitPoint");
	Reset(0);
}


CAnimationStateMachine::~CAnimationStateMachine()
{
	for (auto state : m_States)
		delete state;

	for (auto param : m_vecParams)
		delete param;
}
double CAnimationStateMachine::GetDurationInSeconds()
{
	return m_pCurrentState->GetDurationInSeconds();
}
double CAnimationStateMachine::GetTickPercentWithRepeat()
{
	return m_pCurrentState->GetTickPercentWithRepeat();
}
vector<tAnimationKeyFrame>& CAnimationStateMachine::GetBoneTransforms()
{
	m_vecFrame.clear();
	//ifm_pCurrentState != m_pHead)
	if (m_pCurrentState->IsTransitioning())
	{
		map<wstring, tAnimationKeyFrame> mapFrame = m_pCurrentState->GetCurrentTransition()->GetTransitionKeyFrame();
		for (auto frame : mapFrame)
			m_vecFrame.push_back(frame.second);
		return m_vecFrame;
	}
	else
	{
		return m_pCurrentState->GetBoneTransforms();
	}
	return m_vecFrame;
}

void CAnimationStateMachine::OnTransitionBegin(double _tickPercent)
{
	Reset(_tickPercent);
}

void CAnimationStateMachine::OnTransitionEnd()
{
	IAnimationState::OnTransitionEnd();
}

Ptr<CAnimationClip> CAnimationStateMachine::GetClip()
{
	return m_pCurrentState->GetClip();
}

double CAnimationStateMachine::GetTickPercent()
{
	return m_pCurrentState->GetTickPercent();
}

CAnimationState* CAnimationStateMachine::CreateState()
{
	CAnimationState* pNewState = new CAnimationState(m_pRootMachine, this);
	wstring name = L"New State";
	int i = 0;
	while (GetStateByName(name) != nullptr)
	{
		name = L"New State" + std::to_wstring(i++);
	}
	pNewState->SetName(name);
	m_States.insert(pNewState);
	return pNewState;
}

CAnimationState* CAnimationStateMachine::CreateState(CAnimationState* _copyState)
{
	CAnimationState* pNewState = new CAnimationState(*_copyState);
	m_States.insert(pNewState);
	return pNewState;
}

CAnimationStateMachine* CAnimationStateMachine::CreateSubStateMachine()
{
	CAnimationStateMachine* pNewMachine = new CAnimationStateMachine(m_pRootMachine, this);
	wstring name = L"New Machine";
	int i = 0;
	while (GetStateByName(name) != nullptr)
	{
		name = L"New Machine" + std::to_wstring(i++);
	}
	pNewMachine->SetName(name);
	pNewMachine->Reset(0);
	m_States.insert(pNewMachine);
	return pNewMachine;
}

void CAnimationStateMachine::DeleteState(IAnimationState* _pState)
{
	Reset(0);
	auto iter = m_States.find(_pState);
	if (iter != m_States.end())
	{
		delete *iter;
		m_States.erase(iter);
	}
}
IAnimationState* CAnimationStateMachine::GetStateByName(wstring _name)
{
	for (auto s : m_States)
		if (s->GetName() == _name)
			return s;
	return nullptr;
}
void CAnimationStateMachine::Reset(double _tickPercent)
{
	ChangeState(m_pHead);
	m_pHead->OnTransitionBegin(_tickPercent);
}

AnimStateParam* CAnimationStateMachine::CreateNewParam(AnimParamType _type)
{
	if (m_pRootMachine != this) return m_pRootMachine->CreateNewParam(_type);

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

void CAnimationStateMachine::SetParamName(AnimStateParam* _param, wstring _name)
{
	if (m_pRootMachine != this) return m_pRootMachine->SetParamName(_param, _name);
	
	wstring newName = _name;
	int postFix = 0;
	bool noDuplicateFlag = false;
	while (!noDuplicateFlag)
	{
		noDuplicateFlag = true;
		for (int i = 0; i < m_vecParams.size(); i++)
		{
			if (m_vecParams[i] != _param && m_vecParams[i]->name == newName)
			{
				noDuplicateFlag = false;
				break;
			}
		}
		if(!noDuplicateFlag)
			newName = _name + L" " + std::to_wstring(postFix++);
	}
	_param->name = newName;
}

void CAnimationStateMachine::DeleteParam(wstring _name)
{
	if (m_pRootMachine != this) return m_pRootMachine->DeleteParam(_name);

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
	if (m_pRootMachine != this) return m_pRootMachine->DeleteParam(_idx);

	if (0 <= _idx && _idx < m_vecParams.size())
	{
		delete m_vecParams[_idx];
		m_vecParams.erase(m_vecParams.begin() + _idx);
	}
}

AnimStateParam* CAnimationStateMachine::GetParamByName(wstring _name)
{
	if (m_pRootMachine != this) return m_pRootMachine->GetParamByName(_name);

	for (int i = 0; i < m_vecParams.size(); i++)
	{
		if (m_vecParams[i]->name == _name)
			return m_vecParams[i];
	}
	return nullptr;
}

AnimStateParam* CAnimationStateMachine::GetParamByIndex(int _idx)
{
	if (m_pRootMachine != this) return m_pRootMachine->GetParamByIndex(_idx);

	if (0 <= _idx && _idx < m_vecParams.size())
		return m_vecParams[_idx];
	return nullptr;
}

vector<AnimStateParam*>& CAnimationStateMachine::GetAllParams()
{
	if (m_pRootMachine != this) return m_pRootMachine->GetAllParams();
	return m_vecParams;
}

void CAnimationStateMachine::SetBool(wstring _param, bool _value)
{
	if (m_pRootMachine != this) return m_pRootMachine->SetBool(_param, _value);

	GetParamByName(_param)->value.BOOL = _value;
}

void CAnimationStateMachine::SetFloat(wstring _param, float _value)
{
	if (m_pRootMachine != this) return m_pRootMachine->SetFloat(_param, _value);
	
	GetParamByName(_param)->value.FLOAT = _value;
}

void CAnimationStateMachine::SetInt(wstring _param, int _value)
{
	if (m_pRootMachine != this) return m_pRootMachine->SetInt(_param, _value);

	GetParamByName(_param)->value.INT = _value;
}

void CAnimationStateMachine::SetTrigger(wstring _param, bool _value)
{
	if (m_pRootMachine != this) return m_pRootMachine->SetTrigger(_param, _value);

	GetParamByName(_param)->value.TRIGGER = _value;
}

void CAnimationStateMachine::tick()
{
	IAnimationState::tick();
	m_pCurrentState->tick();

}

void CAnimationStateMachine::SaveToLevelFile(FILE* _FILE)
{
	int count = m_vecParams.size();
	fwrite(&count, sizeof(int), 1, _FILE);
	for (int i = 0; i < count; i++)
	{
		auto param = m_vecParams[i];
		SaveWString(param->name, _FILE);
		int type = (int)param->type;
		fwrite(&type, sizeof(int), 1, _FILE);
		if (AnimParamType::FLOAT == param->type)
			fwrite(&param->value.FLOAT, sizeof(float), 1, _FILE);
		else if (AnimParamType::INT == param->type)
			fwrite(&param->value.INT, sizeof(int), 1, _FILE);
		else if (AnimParamType::BOOL == param->type)
			fwrite(&param->value.BOOL, sizeof(bool), 1, _FILE);
		else if (AnimParamType::TRIGGER == param->type)
			fwrite(&param->value.TRIGGER, sizeof(bool), 1, _FILE);
	}
	count = m_States.size();
	fwrite(&count, sizeof(int), 1, _FILE);
	for (auto state : m_States)
	{
		SaveWString(state->GetName(), _FILE);
		int type = (int)state->GetType();
		fwrite(&type, sizeof(int), 1, _FILE);
	}
	for (auto state : m_States)
	{
		SaveWString(state->GetName(), _FILE);
		state->SaveToLevelFile(_FILE);
	}

	SaveWString(m_pHead->GetName(), _FILE);
	IAnimationState::SaveToLevelFile(_FILE);
}

void CAnimationStateMachine::LoadFromLevelFile(FILE* _FILE)
{
	delete m_pHead;
	m_States.clear();

	int count; fread(&count, sizeof(int), 1, _FILE);
	m_vecParams.resize(count);

	for (int i = 0; i < count; i++)
	{
		auto param = new AnimStateParam();
		LoadWString(param->name, _FILE);
		
		int type; fread(&type, sizeof(int), 1, _FILE);
		param->type = (AnimParamType)type;
		if (AnimParamType::FLOAT == param->type)
			fread(&param->value.FLOAT, sizeof(float), 1, _FILE);
		else if (AnimParamType::INT == param->type)
			fread(&param->value.INT, sizeof(int), 1, _FILE);
		else if (AnimParamType::BOOL == param->type)
			fread(&param->value.BOOL, sizeof(bool), 1, _FILE);
		else if (AnimParamType::TRIGGER == param->type)
			fread(&param->value.TRIGGER, sizeof(bool), 1, _FILE);
		m_vecParams[i] = param;
	}
	fread(&count, sizeof(int), 1, _FILE);
	for (size_t i = 0; i < count; i++)
	{
		wstring name;
		LoadWString(name, _FILE);
		IAnimationState* state;
		int type;
		fread(&type, sizeof(int), 1, _FILE);
		if (type == (int)eAnimationNodeType::StateMachine) state = new CAnimationStateMachine(m_pRootMachine, this);
		else state = new CAnimationState(m_pRootMachine, this);
		state->SetName(name);
		m_States.insert(state);
	}
	for (size_t i = 0; i < count; i++)
	{
		wstring name;
		LoadWString(name, _FILE);
		auto state = GetStateByName(name);
		state->LoadFromLevelFile(_FILE);
	}

	wstring name;
	LoadWString(name, _FILE);
	m_pHead = GetStateByName(name);

	IAnimationState::LoadFromLevelFile(_FILE);

	Reset(0);
}
