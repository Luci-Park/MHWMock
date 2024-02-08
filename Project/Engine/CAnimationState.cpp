#include "pch.h"
#include "CAnimationState.h"
#include "CAnimationTransition.h"
#include "CTimeMgr.h"


CAnimationState::CAnimationState()
	: m_strName(L"New State")
	, m_vecTransitions()
	, m_pClip(nullptr)
	, m_fSpeed(1)
	, m_dTick(0)
{
}

CAnimationState::CAnimationState(const CAnimationState& _other)
	: m_strName(L"New State")
	, m_vecTransitions()
	, m_pClip(_other.m_pClip)
	, m_fSpeed(_other.m_fSpeed)
	, m_dTick(0)
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
	if(m_pClip != nullptr)
	{
		m_dTick = m_pClip->GetDuration() * _percent;
	}
	else
	{
		m_dTick = 0;
	}
}

vector<tAnimationKeyFrame>& CAnimationState::GetBoneTransforms()
{
	vector<tAnimationKeyFrame> vecEmpty;
	if (m_pClip == nullptr)
		return vecEmpty;
	m_dTick += CTimeMgr::GetInst()->GetDeltaTime() * m_pClip->GetTicksPerSecond() * m_fSpeed;
	return m_pClip->GetTransformsAtFrame(m_dTick);
}

void CAnimationState::finaltick()
{
	if (m_pClip != nullptr)
		m_dTick += CTimeMgr::GetInst()->GetDeltaTime() * m_pClip->GetTicksPerSecond() * m_fSpeed;
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
	else if(m_pClip!= nullptr && m_dTick > m_pClip->GetDuration())
	{
		m_dTick = 0;
	}
}
