#include "pch.h"
#include "CAnimationState.h"
#include "CAnimationTransition.h"
#include "CAnimationStateMachine.h"
#include "CTimeMgr.h"

CAnimationState::CAnimationState(CAnimationStateMachine* _pParent)
	: m_Transitions()
	, m_pClip(nullptr)
	, m_fSpeed(1)
	, m_dTick(0)
	, m_pMachine(_pParent)
	, m_iRepeatNum(0)
{
}

CAnimationState::CAnimationState(const CAnimationState& _other)
	: m_Transitions()
	, m_pClip(_other.m_pClip)
	, m_fSpeed(_other.m_fSpeed)
	, m_dTick(0)
	, m_pMachine(_other.m_pMachine)
	, m_iRepeatNum(0)
{
}

CAnimationState::~CAnimationState()
{
	for (auto t : m_Transitions)
	{
		delete t;
	}
}
void CAnimationState::SetName(wstring _name)
{
	int postFix = 0;
	wstring newName = _name;
	while (m_pMachine->GetStateByName(newName) != nullptr)
		newName = _name + L" " + std::to_wstring(postFix++);
	m_strName = newName;
}
void CAnimationState::SetTick(double _percent)
{
	m_dDuration = m_pClip != nullptr ? m_pClip->GetDuration() : 1;
	m_dTick = m_dDuration * _percent;
}

double CAnimationState::GetTickPercent()
{
	return abs(m_dTick / m_dDuration);
}

void CAnimationState::DeleteTransition(CAnimationTransition* _transit)
{
	auto iter = m_Transitions.find(_transit);
	if (iter != m_Transitions.end())
		m_Transitions.erase(iter);
	delete _transit;
}

void CAnimationState::OnTransitionEnd()
{
	m_dTick = 0;
	m_pCurrentTransition = nullptr;
}

void CAnimationState::OnTransitionBegin(double _tickPercent)
{
	SetTick(_tickPercent);
	m_iRepeatNum = 0;
}

vector<tAnimationKeyFrame>& CAnimationState::GetBoneTransforms()
{
	vector<tAnimationKeyFrame> vecEmpty(0);
	if (m_pClip == nullptr)
		return vecEmpty;
	return m_pClip->GetTransformsAtFrame(m_dTick);
}

void CAnimationState::tick()
{
	m_dDuration = m_pClip != nullptr ? m_pClip->GetDuration() : 1;
	double offset = m_pClip != nullptr ? m_pClip->GetTicksPerSecond() : 1;

	m_dTick += CTimeMgr::GetInst()->GetDeltaTime() * offset * m_fSpeed;
	if (m_dTick > m_dDuration) { m_dTick = 0; m_iRepeatNum++; }
	if (m_dTick < 0) { m_dTick = m_dDuration; m_iRepeatNum++; }

	if (m_pCurrentTransition != nullptr)
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

void CAnimationState::SaveToLevelFile(FILE* _FILE)
{
	SaveResRef(m_pClip.Get(), _FILE);
	fwrite(&m_fSpeed, sizeof(float), 1, _FILE);

	int count = m_Transitions.size();
	fwrite(&count, sizeof(int), 1, _FILE);
	for (auto transit : m_Transitions)
	{
		SaveWString(transit->GetNextState()->GetName(), _FILE);
		transit->SaveToLevelFile(_FILE);
	}
}

void CAnimationState::LoadFromLevelFile(FILE* _FILE)
{
	LoadResRef(m_pClip, _FILE);
	fread(&m_fSpeed, sizeof(float), 1, _FILE);

	int count; 
	fread(&count, sizeof(int), 1, _FILE);
	while (count--)
	{
		wstring nextStateName;
		LoadWString(nextStateName, _FILE);
		auto nextState = m_pMachine->GetStateByName(nextStateName);
		auto newTransition = new CAnimationTransition(this, nextState, m_pMachine);
		m_Transitions.insert(newTransition);
		newTransition->LoadFromLevelFile(_FILE);
	}
}
