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
	, m_tNodeInfo({Vec2(0, 0)})
{
}

CAnimationState::CAnimationState(const CAnimationState& _other)
	: m_Transitions()
	, m_pClip(_other.m_pClip)
	, m_fSpeed(_other.m_fSpeed)
	, m_dTick(0)
	, m_pMachine(_other.m_pMachine)
	, m_iRepeatNum(0)
	, m_tNodeInfo({ Vec2(0, 0) })
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

void CAnimationState::SetClip(Ptr<CAnimationClip> _pClip)
{
	m_pClip = _pClip;
	if (m_pClip != nullptr) m_FirstRootFrame = m_pClip->GetRootTransformAtFirstFrame("Root");
}

double CAnimationState::GetDurationInSeconds()
{
	if (m_pClip != nullptr)
		return m_pClip->GetDuration() / m_pClip->GetTicksPerSecond();
	return m_dDuration;
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

double CAnimationState::GetTickPercentWithRepeat()
{
	float duration = m_dTick + m_dDuration * m_iRepeatNum;
	return abs(duration / m_dDuration);
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
	Reset(_tickPercent, false);
}

vector<tAnimationKeyFrame>& CAnimationState::GetBoneTransforms()
{
	m_vecKeyFrames.clear();
	if (m_pClip != nullptr)
	{
		m_vecKeyFrames = m_pClip->GetTransformsAtFrame(m_dTick);
		for (int i = 0; i < m_vecKeyFrames.size(); i++)
		{
			if (m_vecKeyFrames[i].strBoneName == L"Root")
			{
				if (m_bIsFirstTick)
				{
					m_prevRootFrame = m_FirstRootFrame;
					m_bIsFirstTick = false;
				}
				auto tempFrame = m_vecKeyFrames[i];
				m_vecKeyFrames[i].vPos -= m_prevRootFrame.vPos;
				m_vecKeyFrames[i].qRot -= m_prevRootFrame.qRot;

				m_prevRootFrame = tempFrame;
				break;
			}
		}
	}
	return m_vecKeyFrames;
}

void CAnimationState::Reset(double _percent, bool _repeat)
{
	SetTick(_percent);
	if (_repeat)m_iRepeatNum += 1;
	else m_iRepeatNum = 0;
	m_bIsFirstTick = true;
}

void CAnimationState::tick()
{
	m_dDuration = m_pClip != nullptr ? m_pClip->GetDuration() : 1;
	double offset = m_pClip != nullptr ? m_pClip->GetTicksPerSecond() : 1;

	m_dTick += CTimeMgr::GetInst()->GetDeltaTime() * offset * m_fSpeed;
	if (m_dTick > m_dDuration) Reset(0, true);
	if (m_dTick < 0) Reset(m_dDuration, true);

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

void CAnimationState::SaveToLevelFile(FILE* _FILE)
{
	SaveResRef(m_pClip.Get(), _FILE);
	fwrite(&m_fSpeed, sizeof(float), 1, _FILE);
	fwrite(&m_tNodeInfo, sizeof(tAnimationStateNode), 1, _FILE);

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
	fread(&m_tNodeInfo, sizeof(tAnimationStateNode), 1, _FILE);

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
