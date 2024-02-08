#include "pch.h"
#include "CAnimationTransition.h"
#include "CAnimationState.h"
#include "CTimeMgr.h"


CAnimationTransition::CAnimationTransition(CAnimationState* _pPrevState, CAnimationState* _pNextState)
	: m_pPrevState(_pPrevState)
	, m_pNextState(_pNextState)
	, m_bHasExitTime(true)
	, m_dExitTime(1)
	, m_bFixedDuration(false)
	, m_dTransitionDuration(0.25)
	, m_dTransitionOffset(0)
{
}

CAnimationTransition::~CAnimationTransition()
{
}

map<wstring, tAnimationKeyFrame>& CAnimationTransition::GetTransitionKeyFrame()
{
	m_mapKeyFrame.clear();
	BlendKeyFrame(m_pPrevState->GetBoneTransforms(), true);
	BlendKeyFrame(m_pNextState->GetBoneTransforms(), false);

	return m_mapKeyFrame;
}

bool CAnimationTransition::CheckCondition()
{
	return false;
}

void CAnimationTransition::StartTransition()
{
	m_dTick = 0;
	m_pNextState->SetTick(m_dTransitionOffset);
}

void CAnimationTransition::finaltick()
{
	double offset = 1;
	if (!m_bFixedDuration)
	{
		offset = m_pPrevState->GetClip()->GetTicksPerSecond()
			* m_pPrevState->GetSpeed();
	}
	m_dTick += CTimeMgr::GetInst()->GetDeltaTime() * offset;

	if (m_bFixedDuration)
		m_dTickPercent = m_dTick / m_dTransitionDuration;
	else
		m_dTickPercent = m_dTick / m_pPrevState->GetClip()->GetDuration();

	if (m_dTickPercent >= 1)
		EndTransition();
		
}

void CAnimationTransition::EndTransition()
{
	//change to nextstate
}

void CAnimationTransition::BlendKeyFrame(vector<tAnimationKeyFrame>& frames, bool minus)
{
	double percent = minus ? 1 - m_dTickPercent : m_dTickPercent;
	for (int i = 0; i < frames.size(); i++)
	{
		tAnimationKeyFrame newFrame = frames[i] * percent;
		auto iter = m_mapKeyFrame.find(frames[i].strBoneName);
		if (iter == m_mapKeyFrame.end())
		{
			m_mapKeyFrame.insert(make_pair(frames[i].strBoneName, newFrame));
		}
		else
		{
			iter->second += newFrame;
		}
	}
}
