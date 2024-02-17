#include "pch.h"
#include "CAnimationState.h"
#include "CAnimationTransition.h"
#include "CTimeMgr.h"

CAnimationState::CAnimationState(CAnimationStateMachine* _pParent)
	: m_strName(L"New State")
	, m_vecTransitions()
	, m_pClip(nullptr)
	, m_fSpeed(1)
	, m_dTick(0)
	, m_pMachine(_pParent)
	, m_iRepeatNum(0)
{
}

CAnimationState::CAnimationState(const CAnimationState& _other)
	: m_strName(L"New State")
	, m_vecTransitions()
	, m_pClip(_other.m_pClip)
	, m_fSpeed(_other.m_fSpeed)
	, m_dTick(0)
	, m_pMachine(_other.m_pMachine)
	, m_iRepeatNum(0)
{
}

CAnimationState::~CAnimationState()
{
	for (size_t i = 0; i < m_vecTransitions.size(); i++)
	{
		delete m_vecTransitions[i];
	}
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

void CAnimationState::finaltick()
{
	m_dDuration = m_pClip != nullptr ? m_pClip->GetDuration() : 1;
	double offset = m_pClip != nullptr ? m_pClip->GetTicksPerSecond() : 1;

	m_dTick += CTimeMgr::GetInst()->GetDeltaTime() * offset * m_fSpeed;
	if (m_dTick > m_dDuration) { m_dTick = 0; m_iRepeatNum++; }
	if (m_dTick < 0) { m_dTick = m_dDuration; m_iRepeatNum++; }

	if (m_pCurrentTransition != nullptr)
	{
		for (auto t : m_vecTransitions)
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
		m_pCurrentTransition->finaltick();
	}
}
